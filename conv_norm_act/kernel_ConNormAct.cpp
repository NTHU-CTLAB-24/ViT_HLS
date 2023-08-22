// Includes
#include <hls_math.h>
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
const bool isBias = true;
const bool isSkip = false;
const int NORM_LAYER = 0; // 0:batch_norm;
const int ACT_LAYER = 0;  // 0: relu, 1: silu, 2:gelu
const int DROP_PATH = 0;
const int HEIGHT_OUT = (HEIGHT_IN - KERNEL_SIZE + 2 * PADDING) / STRIDE + 1;
const int WIDTH_OUT = (WIDTH_IN - KERNEL_SIZE + 2 * PADDING) / STRIDE + 1;
const int KERNEL_CHANNEL = CHANNEL_IN / GROUP;
const int inGroupNums = CHANNEL_IN / GROUP;
const int outGroupNums = CHANNEL_OUT / GROUP;
const bool isRelu = false;
const bool isSilu = false;
const bool isGelu = true;

// Normalization parameters
const float EPS = 1e-6;
const float GAMMA = 0.5;
const float BETA = 0.2;

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
                         float afterConv[BATCH_SIZE][CHANNEL_OUT][HEIGHT_OUT][WIDTH_OUT])
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

init_output:
    for (int n = 0; n < BATCH_SIZE; n++)
    {
#pragma HLS LOOP_TRIPCOUNT min = BATCH_SIZE max = BATCH_SIZE
        for (int c = 0; c < CHANNEL_OUT; c++)
        {
#pragma HLS LOOP_TRIPCOUNT min = CHANNEL_OUT max = CHANNEL_OUT
            for (int h = 0; h < HEIGHT_OUT; h++)
            {
#pragma HLS LOOP_TRIPCOUNT min = HEIGHT_OUT max = HEIGHT_OUT
                for (int w = 0; w < WIDTH_OUT; w++)
                {
#pragma HLS LOOP_TRIPCOUNT min = WIDTH_OUT max = WIDTH_OUT
                    afterConv[n][c][h][w] = 0;
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
                    // float sum = 0.0;
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
                                afterConv[batch][out_ch][row][col] += in[batch][in_ch][row * STRIDE + kernel_row][col * STRIDE + kernel_col] * kernel[out_ch][kernelChannelIdx][kernel_row][kernel_col];
                            }
                        }
                        kernelChannelIdx++;
                        if ((in_ch + 1) % inGroupNums == 0)
                            break;
                    }
                    if ((out_ch + 1) % outGroupNums == 0)
                        groupIndex++;
                    if (isBias)
                        afterConv[batch][out_ch][row][col] += bias[out_ch];
                    // buffer_result[batch * CHANNEL_OUT * HEIGHT_OUT * WIDTH_OUT + out_ch * HEIGHT_OUT * WIDTH_OUT + row * WIDTH_OUT + col] = sum;
                }
            }
        }
    }
}

static void compute_norm(float afterConv[BATCH_SIZE][CHANNEL_OUT][HEIGHT_OUT][WIDTH_OUT],
                         float afterNorm[BATCH_SIZE][CHANNEL_OUT][HEIGHT_OUT][WIDTH_OUT],
                         float *buffer_result)
{
    const float RUNNING_MEAN[CHANNEL_OUT] = {82, 227, 444};
#pragma HLS array_partition variable = RUNNING_MEAN complete dim = 1
    const float RUNNING_VAR[CHANNEL_OUT] = {945, 3780, 8505};
#pragma HLS array_partition variable = RUNNING_VAR complete dim = 1

init_output:
    for (int n = 0; n < BATCH_SIZE; n++)
    {
#pragma HLS LOOP_TRIPCOUNT min = BATCH_SIZE max = BATCH_SIZE
        for (int c = 0; c < CHANNEL_OUT; c++)
        {
#pragma HLS LOOP_TRIPCOUNT min = CHANNEL_OUT max = CHANNEL_OUT
            for (int h = 0; h < HEIGHT_OUT; h++)
            {
#pragma HLS LOOP_TRIPCOUNT min = HEIGHT_OUT max = HEIGHT_OUT
                for (int w = 0; w < WIDTH_OUT; w++)
                {
#pragma HLS LOOP_TRIPCOUNT min = WIDTH_OUT max = WIDTH_OUT
                    afterNorm[n][c][h][w] = 0;
                }
            }
        }
    }

Batch_norm:
    for (int n = 0; n < BATCH_SIZE; n++)
    {
#pragma HLS LOOP_TRIPCOUNT min = BATCH_SIZE max = BATCH_SIZE
        for (int c = 0; c < CHANNEL_OUT; c++)
        {
#pragma HLS LOOP_TRIPCOUNT min = CHANNEL_OUT max = CHANNEL_OUT
            for (int h = 0; h < HEIGHT_OUT; h++)
            {
#pragma HLS LOOP_TRIPCOUNT min = HEIGHT_OUT max = HEIGHT_OUT
                for (int w = 0; w < WIDTH_OUT; w++)
                {
#pragma HLS LOOP_TRIPCOUNT min = WIDTH_OUT max = WIDTH_OUT
                    afterNorm[n][c][h][w] = ((afterConv[n][c][h][w] - RUNNING_MEAN[c]) / sqrt(RUNNING_VAR[c] + EPS)) * GAMMA + BETA;
                }
            }
        }
    }
}

static void compute_act(float afterNorm[BATCH_SIZE][CHANNEL_OUT][HEIGHT_OUT][WIDTH_OUT],
                        float *buffer_result)
{
    switch (ACT_LAYER)
    {
    case 0:
        for (int n = 0; n < BATCH_SIZE; n++)
        {
#pragma HLS LOOP_TRIPCOUNT min = BATCH_SIZE max = BATCH_SIZE
            for (int c = 0; c < CHANNEL_OUT; c++)
            {
#pragma HLS LOOP_TRIPCOUNT min = CHANNEL_OUT max = CHANNEL_OUT
                for (int h = 0; h < HEIGHT_OUT; h++)
                {
#pragma HLS LOOP_TRIPCOUNT min = HEIGHT_OUT max = HEIGHT_OUT
                    for (int w = 0; w < WIDTH_OUT; w++)
                    {
#pragma HLS LOOP_TRIPCOUNT min = WIDTH_OUT max = WIDTH_OUT
                        if (afterNorm[n][c][h][w] < 0)
                            buffer_result[n * CHANNEL_OUT * HEIGHT_OUT * WIDTH_OUT + c * HEIGHT_OUT * WIDTH_OUT + h * WIDTH_OUT + w] = 0;
                        else
                            buffer_result[n * CHANNEL_OUT * HEIGHT_OUT * WIDTH_OUT + c * HEIGHT_OUT * WIDTH_OUT + h * WIDTH_OUT + w] = afterNorm[n][c][h][w];
                    }
                }
            }
        }
        break;
    case 1:
        for (int n = 0; n < BATCH_SIZE; n++)
        {
#pragma HLS LOOP_TRIPCOUNT min = BATCH_SIZE max = BATCH_SIZE
            for (int c = 0; c < CHANNEL_OUT; c++)
            {
#pragma HLS LOOP_TRIPCOUNT min = CHANNEL_OUT max = CHANNEL_OUT
                for (int h = 0; h < HEIGHT_OUT; h++)
                {
#pragma HLS LOOP_TRIPCOUNT min = HEIGHT_OUT max = HEIGHT_OUT
                    for (int w = 0; w < WIDTH_OUT; w++)
                    {
#pragma HLS LOOP_TRIPCOUNT min = WIDTH_OUT max = WIDTH_OUT
                            buffer_result[n * CHANNEL_OUT * HEIGHT_OUT * WIDTH_OUT + c * HEIGHT_OUT * WIDTH_OUT + h * WIDTH_OUT + w] = afterNorm[n][c][h][w] * (1 / (1 + exp(-afterNorm[n][c][h][w])));;
                    }
                }
            }
        }
        break;
    case 2:
    for (int n = 0; n < BATCH_SIZE; n++)
        {
#pragma HLS LOOP_TRIPCOUNT min = BATCH_SIZE max = BATCH_SIZE
            for (int c = 0; c < CHANNEL_OUT; c++)
            {
#pragma HLS LOOP_TRIPCOUNT min = CHANNEL_OUT max = CHANNEL_OUT
                for (int h = 0; h < HEIGHT_OUT; h++)
                {
#pragma HLS LOOP_TRIPCOUNT min = HEIGHT_OUT max = HEIGHT_OUT
                    for (int w = 0; w < WIDTH_OUT; w++)
                    {
#pragma HLS LOOP_TRIPCOUNT min = WIDTH_OUT max = WIDTH_OUT
                            float x = afterNorm[n][c][h][w];
                            buffer_result[n * CHANNEL_OUT * HEIGHT_OUT * WIDTH_OUT + c * HEIGHT_OUT * WIDTH_OUT + h * WIDTH_OUT + w] = 0.5 * x * (1.0 + tanh(sqrt(2.0 / 3.14159265358979323846) * (x + 0.044715 * pow(x, 3))));
                    }
                }
            }
        }
        break;
    default:
        break;
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

    void kernel_conv_norm_act(float *buffer_DataIn_1,
                              float *buffer_result)
    {
#pragma HLS INTERFACE m_axi port = buffer_DataIn_1 bundle = gmem0
#pragma HLS INTERFACE m_axi port = buffer_result bundle = gmem0

        // static hls::stream<float> in_stream("input_stream");
        // static hls::stream<float> kernel_stream("kernel_stream");
        // static hls::stream<float> out_stream("output_stream");

// #pragma HLS dataflow
        // dataflow pragma instruct compiler to run following three APIs in parallel
        // load_input(in1, in1_stream, size);
        // load_input(in2, in2_stream, size);
        float in[BATCH_SIZE][CHANNEL_IN][HEIGHT_IN][WIDTH_IN];
#pragma HLS array_partition variable = in complete dim = 1
        float afterConv[BATCH_SIZE][CHANNEL_OUT][HEIGHT_OUT][WIDTH_OUT];
#pragma HLS array_partition variable = afterConv complete dim = 1
        float afterNorm[BATCH_SIZE][CHANNEL_OUT][HEIGHT_OUT][WIDTH_OUT];
#pragma HLS array_partition variable = afterNorm complete dim = 1
        load_input(buffer_DataIn_1, in);
        compute_conv(in, afterConv);
        compute_norm(afterConv, afterNorm, buffer_result);
        compute_act(afterNorm, buffer_result);
        // store_result(buffer_result, out);
        // store_result(out, out_stream, size);
    }
}
