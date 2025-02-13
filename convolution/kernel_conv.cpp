// Includes
#include <hls_stream.h>
#include <stdint.h>
// TRIPCOUNT identifier
const int BATCH_SIZE = 2;
const int CHANNEL_IN = 6;
const int CHANNEL_OUT = 3;
const int HEIGHT_IN = 8;
const int WIDTH_IN = 8;

// Convolution parameters
const int KERNEL_SIZE = 3;
const int PADDING = 0;
const int STRIDE = 1;
const int GROUP = 3;
const bool isConvBias = true;
const int HEIGHT_OUT = (HEIGHT_IN - KERNEL_SIZE + 2 * PADDING) / STRIDE + 1;
const int WIDTH_OUT = (WIDTH_IN - KERNEL_SIZE + 2 * PADDING) / STRIDE + 1;
const int KERNEL_CHANNEL = CHANNEL_IN / GROUP;
const int inGroupNums = CHANNEL_IN / GROUP;
const int outGroupNums = CHANNEL_OUT / GROUP;

// Coding Style: function宣告要為static，遇到for迴圈前可以取error_type的名稱(ex: mem_rd)
// static void load_input(float* in, hls::stream<float>& inStream, int size) {
// mem_rd:
//     for (int i = 0; i < size; i++) {
// #pragma HLS LOOP_TRIPCOUNT min = in_size max = in_size
//         inStream << in[i];
//     }
// }

static void load_input(float *buffer_DataIn_1,
                       float in[BATCH_SIZE][CHANNEL_IN][HEIGHT_IN][WIDTH_IN])
{
init_in:
    for (int n = 0; n < BATCH_SIZE; n++)
    {
#pragma HLS LOOP_TRIPCOUNT min = BATCH_SIZE max = BATCH_SIZE
        for (int c = 0; c < CHANNEL_IN; c++)
        {
#pragma HLS LOOP_TRIPCOUNT min = CHANNEL_IN max = CHANNEL_IN
            for (int h = 0; h < HEIGHT_IN; h++)
            {
#pragma HLS LOOP_TRIPCOUNT min = HEIGHT_IN max = HEIGHT_IN
                for (int w = 0; w < WIDTH_IN; w++)
                {
#pragma HLS LOOP_TRIPCOUNT min = WIDTH_IN max = WIDTH_IN
                    in[n][c][h][w] = buffer_DataIn_1[n * CHANNEL_IN * HEIGHT_IN * WIDTH_IN + c * HEIGHT_IN * WIDTH_IN + h * WIDTH_IN + w];
                }
            }
        }
    }
}

static void compute_conv(float in[BATCH_SIZE][CHANNEL_IN][HEIGHT_IN][WIDTH_IN],
                         float *buffer_result)
{
    // The kernel is operating with vector of NUM_WORDS integers. The + operator performs
    // an element-wise add, resulting in NUM_WORDS parallel additions.

    float kernel[CHANNEL_OUT][KERNEL_CHANNEL][KERNEL_SIZE][KERNEL_SIZE];
#pragma HLS array_partition variable = kernel complete dim = 1
    float bias[CHANNEL_OUT];
#pragma HLS array_partition variable = bias complete dim = 1

init_kernel_bias:
    for (int k = 0; k < CHANNEL_OUT; k++)
    {
#pragma HLS LOOP_TRIPCOUNT min = CHANNEL_OUT max = CHANNEL_OUT
        bias[k] = k + 10;
        for (int l = 0; l < KERNEL_CHANNEL; l++)
        {
#pragma HLS LOOP_TRIPCOUNT min = KERNEL_CHANNEL max = KERNEL_CHANNEL
            for (int i = 0; i < KERNEL_SIZE; i++)
            {
#pragma HLS LOOP_TRIPCOUNT min = KERNEL_SIZE max = KERNEL_SIZE
                for (int j = 0; j < KERNEL_SIZE; j++)
                {
#pragma HLS LOOP_TRIPCOUNT min = KERNEL_SIZE max = KERNEL_SIZE

                    kernel[k][l][i][j] = j + k;
                }
            }
        }
    }

execute:
Batch:
    for (int batch = 0; batch < BATCH_SIZE; batch++)
    {
#pragma HLS LOOP_TRIPCOUNT min = BATCH_SIZE max = BATCH_SIZE
    Out_Row:
        for (int row = 0; row < HEIGHT_OUT; row++)
        {
#pragma HLS LOOP_TRIPCOUNT min = HEIGHT_OUT max = HEIGHT_OUT
        Out_Column:
            for (int col = 0; col < WIDTH_OUT; col++)
            {
// #pragma HLS PIPELINE
#pragma HLS LOOP_TRIPCOUNT min = WIDTH_OUT max = WIDTH_OUT
                int groupIndex = 0;
            Output_Channel:
                for (int out_ch = 0; out_ch < CHANNEL_OUT; out_ch++)
                {
#pragma HLS LOOP_TRIPCOUNT min = CHANNEL_OUT max = CHANNEL_OUT
                    int kernelChannelIdx = 0;
                In_Channel:
                    for (int in_ch = groupIndex * inGroupNums; in_ch < CHANNEL_IN; in_ch++)
                    {
#pragma HLS LOOP_TRIPCOUNT min = KERNEL_CHANNEL max = KERNEL_CHANNEL
                    Kernel_Row:
                        for (int kernel_row = 0; kernel_row < KERNEL_SIZE; kernel_row++)
                        {
#pragma HLS LOOP_TRIPCOUNT min = KERNEL_SIZE max = KERNEL_SIZE
                        Kernel_Col:
                            for (int kernel_col = 0; kernel_col < KERNEL_SIZE; kernel_col++)
                            {
#pragma HLS LOOP_TRIPCOUNT min = KERNEL_SIZE max = KERNEL_SIZE
                                buffer_result[batch * CHANNEL_OUT * HEIGHT_OUT * WIDTH_OUT + out_ch * HEIGHT_OUT * WIDTH_OUT + row * WIDTH_OUT + col] += in[batch][in_ch][row * STRIDE + kernel_row][col * STRIDE + kernel_col] * kernel[out_ch][kernelChannelIdx][kernel_row][kernel_col];
                            }
                        }
                        kernelChannelIdx++;
                        if ((in_ch + 1) % inGroupNums == 0)
                            break;
                    }
                    if ((out_ch + 1) % outGroupNums == 0)
                        groupIndex++;
                    if (isConvBias)
                       buffer_result[batch * CHANNEL_OUT * HEIGHT_OUT * WIDTH_OUT + out_ch * HEIGHT_OUT * WIDTH_OUT + row * WIDTH_OUT + col] += bias[out_ch];
                }
            }
        }
    }
}

// static void store_result(uint32_t* out, hls::stream<uint32_t>& out_stream, int size) {
// mem_wr:
//     for (int i = 0; i < size; i++) {
// #pragma HLS LOOP_TRIPCOUNT min = c_size max = c_size
//         out[i] = out_stream.read();
//     }
// }

// static void store_result(float *buffer_result, float out[HEIGHT_OUT][WIDTH_OUT])
// {
//     for (int i = 0; i < HEIGHT_OUT; i++)
//     {
// #pragma HLS LOOP_TRIPCOUNT min = HEIGHT_OUT max = HEIGHT_OUT
//         for (int j = 0; j < WIDTH_OUT; j++)
//         {
// #pragma HLS LOOP_TRIPCOUNT min = WIDTH_OUT max = WIDTH_OUT
//             buffer_result[i * WIDTH_OUT + j] = out[i][j];
//         }
//     }
// }

extern "C"
{

    /*
        Vector Addition Kernel

        Arguments:
            in1  (input)  --> Input vector 1
            in2  (input)  --> Input vector 2
            out  (output) --> Output vector
            size (input)  --> Number of elements in vector
    */

    void kernel_conv(float *buffer_DataIn_1,
                     float *buffer_result)
    {
#pragma HLS INTERFACE m_axi port = buffer_DataIn_1 bundle = gmem0
#pragma HLS INTERFACE m_axi port = buffer_result bundle = gmem1


#pragma HLS dataflow
        // dataflow pragma instruct compiler to run following three APIs in parallel
        float in[BATCH_SIZE][CHANNEL_IN][HEIGHT_IN][WIDTH_IN];
#pragma HLS array_partition variable = in complete dim = 1
        float out[BATCH_SIZE][CHANNEL_OUT][HEIGHT_OUT][WIDTH_OUT];
#pragma HLS array_partition variable = out complete dim = 1
        load_input(buffer_DataIn_1, in);
        compute_conv(in, buffer_result);
        // store_result(buffer_result, out);
        // store_result(out, out_stream, size);
    }
}
