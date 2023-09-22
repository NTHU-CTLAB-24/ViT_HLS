// Includes
#include <hls_math.h>
#include <hls_stream.h>
#include <stdint.h>

/* Remember to modify test file */

// TODO: modify size
// TRIPCOUNT identifie
const int BATCH_SIZE = 1;
const int CHANNEL_IN = 64;
const int CHANNEL_OUT = 32;
const int HEIGHT_IN = 4;
const int WIDTH_IN = 4;

// TODO: modify conv parameters
// Convolution parameters
const int KERNEL_SIZE = 1;
const int STRIDE = 1;
const int GROUP = 1;

// Padding and size
const int PADDING = 0;
const int HEIGHT_OUT = (HEIGHT_IN - KERNEL_SIZE + 2 * PADDING) / STRIDE + 1;
const int WIDTH_OUT = (WIDTH_IN - KERNEL_SIZE + 2 * PADDING) / STRIDE + 1;

// For Convolution
const int KERNEL_CHANNEL = CHANNEL_IN / GROUP;
const int inGroupNums = CHANNEL_IN / GROUP;
const int outGroupNums = CHANNEL_OUT / GROUP;
const bool isBias = false;

// Coding Style: function宣告要為static，遇到for迴圈前可以取error_type的名稱(ex: mem_rd)

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
#pragma HLS UNROLL
                    in[n][c][h][w] = buffer_DataIn_1[n * CHANNEL_IN * HEIGHT_IN * WIDTH_IN + c * HEIGHT_IN * WIDTH_IN + h * WIDTH_IN + w];
                }
            }
        }
    }
}

static void compute_conv(float in[BATCH_SIZE][CHANNEL_IN][HEIGHT_IN][WIDTH_IN],
                         float* buffer_result)
{
    float kernel[CHANNEL_OUT][KERNEL_CHANNEL][KERNEL_SIZE][KERNEL_SIZE];
#pragma HLS array_partition variable = kernel complete dim = 1
    float bias[CHANNEL_OUT];
#pragma HLS array_partition variable = bias complete dim = 1

init_kernel_bias:
    for (int k = 0; k < CHANNEL_OUT; k++)
    {
#pragma HLS LOOP_TRIPCOUNT min = CHANNEL_OUT max = CHANNEL_OUT
        bias[k] = 2;
        for (int l = 0; l < KERNEL_CHANNEL; l++)
        {
#pragma HLS LOOP_TRIPCOUNT min = KERNEL_CHANNEL max = KERNEL_CHANNEL
            for (int i = 0; i < KERNEL_SIZE; i++)
            {
#pragma HLS UNROLL
                for (int j = 0; j < KERNEL_SIZE; j++)
                {
#pragma HLS UNROLL
                    kernel[k][l][i][j] = 1.2;
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
#pragma HLS LOOP_TRIPCOUNT min = WIDTH_OUT max = WIDTH_OUT
            Kernel_Row:
                for (int kernel_row = 0; kernel_row < KERNEL_SIZE; kernel_row++)
                {
#pragma HLS LOOP_TRIPCOUNT min = KERNEL_SIZE max = KERNEL_SIZE
                Kernel_Col:
                    for (int kernel_col = 0; kernel_col < KERNEL_SIZE; kernel_col++)
                    {
#pragma HLS LOOP_TRIPCOUNT min = KERNEL_SIZE max = KERNEL_SIZE
                        int groupIndex = 0;
                    Output_Channel:
                        for (int out_ch = 0; out_ch < CHANNEL_OUT; out_ch++)
                        {
#pragma HLS UNROLL
                            int kernelChannelIdx = 0;
                        In_Channel:
                            for (int in_ch = groupIndex * inGroupNums; in_ch < CHANNEL_IN; in_ch++)
                            {
#pragma HLS UNROLL
                                buffer_result[batch * CHANNEL_OUT * HEIGHT_OUT * WIDTH_OUT + out_ch * HEIGHT_OUT * WIDTH_OUT + row * WIDTH_OUT + col] += in[batch][in_ch][row * STRIDE + kernel_row][col * STRIDE + kernel_col] * kernel[out_ch][kernelChannelIdx][kernel_row][kernel_col];
                                kernelChannelIdx++;
                                if ((in_ch + 1) % inGroupNums == 0)
                                    break;
                            }
                            if ((out_ch + 1) % outGroupNums == 0)
                                groupIndex++;
                            if (isBias)
                                buffer_result[batch * CHANNEL_OUT * HEIGHT_OUT * WIDTH_OUT + out_ch * HEIGHT_OUT * WIDTH_OUT + row * WIDTH_OUT + col] += bias[out_ch];
                        }
                    }
                }
            }
        }
    }
}


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

    void kernel_proj_1(float *buffer_DataIn_1,
                     float *buffer_result)
    {
// TODO: modify depth
#pragma HLS INTERFACE m_axi port = buffer_DataIn_1 bundle = gmem0 depth = 1024
#pragma HLS INTERFACE m_axi port = buffer_result bundle = gmem0 depth = 512

// #pragma HLS dataflow
// dataflow僅可以接受single reader and single writer
        // dataflow pragma instruct compiler to run following three APIs in parallel
        float in[BATCH_SIZE][CHANNEL_IN][HEIGHT_IN][WIDTH_IN];
#pragma HLS array_partition variable = in complete dim = 1
        load_input(buffer_DataIn_1, in);
        compute_conv(in, buffer_result);
    }
}
