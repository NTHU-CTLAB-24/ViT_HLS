// Includes
#include <hls_stream.h>
#include <stdint.h>
// TRIPCOUNT identifier
const int BATCH_SIZE = 2;
const int HEIGHT_IN = 16;
const int WIDTH_IN = 16;
const int CHANNEL_IN = 3;
const int KERNEL_SIZE = 3;
const int PADDING = 0;
const int STRIDE = 1;
const int HEIGHT_OUT = (HEIGHT_IN - KERNEL_SIZE + 2 * PADDING) / STRIDE + 1;
const int WIDTH_OUT = (WIDTH_IN - KERNEL_SIZE + 2 * PADDING) / STRIDE + 1;
const int CHANNEL_OUT = 2;
const int IN_SIZE = BATCH_SIZE * HEIGHT_IN * WIDTH_IN * CHANNEL_IN;
const int OUT_SIZE = BATCH_SIZE * HEIGHT_OUT * WIDTH_OUT * CHANNEL_OUT;

// Coding Style: function宣告要為static，遇到for迴圈前可以取error_type的名稱(ex: mem_rd)
// static void load_input(float* in, hls::stream<float>& inStream, int size) {
// mem_rd:
//     for (int i = 0; i < size; i++) {
// #pragma HLS LOOP_TRIPCOUNT min = in_size max = in_size
//         inStream << in[i];
//     }
// }

static void load_input(float *buffer_DataIn_1,
                       float *buffer_DataIn_2,
                       float *buffer_result,
                       float in[BATCH_SIZE][CHANNEL_IN][HEIGHT_IN][WIDTH_IN],
                       float kernel[CHANNEL_OUT][KERNEL_SIZE][KERNEL_SIZE],
                       float out[BATCH_SIZE][CHANNEL_OUT][HEIGHT_OUT][WIDTH_OUT])
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

init_kernel:
    for (int k = 0; k < CHANNEL_OUT; k++)
    {
#pragma HLS LOOP_TRIPCOUNT min = CHANNEL_OUT max = CHANNEL_OUT
        for (int i = 0; i < KERNEL_SIZE; i++)
        {
#pragma HLS LOOP_TRIPCOUNT min = KERNEL_SIZE max = KERNEL_SIZE
            for (int j = 0; j < KERNEL_SIZE; j++)
            {
#pragma HLS LOOP_TRIPCOUNT min = KERNEL_SIZE max = KERNEL_SIZE

                kernel[k][i][j] = buffer_DataIn_2[k * KERNEL_SIZE * KERNEL_SIZE + i * KERNEL_SIZE + j];
            }
        }
    }

    // init_output:
    //     for (int l = 0; l < BATCH_SIZE; l++)
    //     {
    // #pragma HLS LOOP_TRIPCOUNT min = BATCH_SIZE max = BATCH_SIZE
    //         for (int i = 0; i < HEIGHT_OUT; i++)
    //         {
    // #pragma HLS LOOP_TRIPCOUNT min = HEIGHT_OUT max = HEIGHT_OUT
    //             for (int j = 0; j < WIDTH_OUT; j++)
    //             {
    // #pragma HLS LOOP_TRIPCOUNT min = WIDTH_OUT max = WIDTH_OUT
    //                 for (int k = 0; k < CHANNEL_OUT; k++)
    //                 {
    // #pragma HLS LOOP_TRIPCOUNT min = CHANNEL_OUT max = CHANNEL_OUT
    //                     out[l][i][j][k] = buffer_result[l * HEIGHT_OUT * WIDTH_OUT * CHANNEL_OUT + i * WIDTH_OUT * CHANNEL_OUT + j * CHANNEL_OUT + k];
    //                 }
    //             }
    //         }
    //     }
}

static void compute_conv(float in[BATCH_SIZE][CHANNEL_IN][HEIGHT_IN][WIDTH_IN],
                         float kernel[CHANNEL_OUT][KERNEL_SIZE][KERNEL_SIZE],
                         float *buffer_result)
{
    // The kernel is operating with vector of NUM_WORDS integers. The + operator performs
    // an element-wise add, resulting in NUM_WORDS parallel additions.

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
            Output_Channel:
                for (int out_ch = 0; out_ch < CHANNEL_OUT; out_ch++)
                {
#pragma HLS LOOP_TRIPCOUNT min = CHANNEL_OUT max = CHANNEL_OUT
                	float sum = 0.0;
                In_Channel:
                    for (int in_ch = 0; in_ch < CHANNEL_IN; in_ch++)
                    {
#pragma HLS LOOP_TRIPCOUNT min = CHANNEL_IN max = CHANNEL_IN
                    Kernel_Row:
                        for (int kernel_row = 0; kernel_row < KERNEL_SIZE; kernel_row++)
                        {
#pragma HLS LOOP_TRIPCOUNT min = KERNEL_SIZE max = KERNEL_SIZE
                        Kernel_Col:
                            for (int kernel_col = 0; kernel_col < KERNEL_SIZE; kernel_col++)
                            {
#pragma HLS LOOP_TRIPCOUNT min = KERNEL_SIZE max = KERNEL_SIZE
                                sum += in[batch][in_ch][row * STRIDE + kernel_row][col * STRIDE + kernel_col] * kernel[out_ch][kernel_row][kernel_col];
                            }
                        }
                    }
                    buffer_result[batch * CHANNEL_OUT * HEIGHT_OUT * WIDTH_OUT + out_ch * HEIGHT_OUT * WIDTH_OUT + row * WIDTH_OUT + col] = sum;
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
                     float *buffer_DataIn_2,
                     float *buffer_result)
    {
#pragma HLS INTERFACE m_axi port = buffer_DataIn_1 bundle = gmem0
#pragma HLS INTERFACE m_axi port = buffer_DataIn_2 bundle = gmem1
#pragma HLS INTERFACE m_axi port = buffer_result bundle = gmem0

        // static hls::stream<float> in_stream("input_stream");
        // static hls::stream<float> kernel_stream("kernel_stream");
        // static hls::stream<float> out_stream("output_stream");

#pragma HLS dataflow
        // dataflow pragma instruct compiler to run following three APIs in parallel
        // load_input(in1, in1_stream, size);
        // load_input(in2, in2_stream, size);
        float in[BATCH_SIZE][CHANNEL_IN][HEIGHT_IN][WIDTH_IN];
#pragma HLS array_partition variable = in complete dim = 1
        float kernel[CHANNEL_OUT][KERNEL_SIZE][KERNEL_SIZE];
#pragma HLS array_partition variable = kernel complete dim = 1
        float out[BATCH_SIZE][CHANNEL_OUT][HEIGHT_OUT][WIDTH_OUT];
#pragma HLS array_partition variable = out complete dim = 1
        load_input(buffer_DataIn_1, buffer_DataIn_2, buffer_result, in, kernel, out);
        compute_conv(in, kernel, buffer_result);
        // store_result(buffer_result, out);
        // store_result(out, out_stream, size);
    }
}
