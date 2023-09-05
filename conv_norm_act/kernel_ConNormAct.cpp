// Includes
#include <hls_math.h>
#include <hls_stream.h>
#include <stdint.h>

/* Remember to modify test file */

// TODO: modify size
// TRIPCOUNT identifie
const int BATCH_SIZE = 2;
const int CHANNEL_IN = 3;
const int CHANNEL_OUT = 3;
const int HEIGHT_IN = 4;
const int WIDTH_IN = 4;

// TODO: modify conv parameters
// Convolution parameters
const int KERNEL_SIZE = 3;
const int STRIDE = 1;
const int GROUP = 1;

// Padding and size
const int PADDING = (KERNEL_SIZE - STRIDE) % 2 == 0 ? (KERNEL_SIZE - STRIDE) / 2 : (KERNEL_SIZE - STRIDE) / 2 + 1;
const int new_height_in = HEIGHT_IN + 2 * PADDING;
const int new_width_in = WIDTH_IN + 2 * PADDING;
const int HEIGHT_OUT = (HEIGHT_IN - KERNEL_SIZE + 2 * PADDING) / STRIDE + 1;
const int WIDTH_OUT = (WIDTH_IN - KERNEL_SIZE + 2 * PADDING) / STRIDE + 1;

// For Convolution
const int KERNEL_CHANNEL = CHANNEL_IN / GROUP;
const int inGroupNums = CHANNEL_IN / GROUP;
const int outGroupNums = CHANNEL_OUT / GROUP;
const bool isBias = true;

// Normalization parameters
const float EPS = 1e-5;

// TODO: modify hyperparameters
// Hyperparameters
const int NORM_LAYER = 0; // 0:batch_norm, 1: layer_norm
const int ACT_LAYER = 1;  // 0: relu, 1: silu, 2:gelu
const bool isSkip = true;

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
#pragma HLS LOOP_TRIPCOUNT min = WIDTH_IN max = WIDTH_IN
                    in[n][c][h][w] = buffer_DataIn_1[n * CHANNEL_IN * HEIGHT_IN * WIDTH_IN + c * HEIGHT_IN * WIDTH_IN + h * WIDTH_IN + w];
                }
            }
        }
    }
}
static void compute_padding(float in[BATCH_SIZE][CHANNEL_IN][HEIGHT_IN][WIDTH_IN],
                         float in_pad[BATCH_SIZE][CHANNEL_IN][new_height_in][new_width_in])
{
Padding:
    for (int n = 0; n < BATCH_SIZE; n++)
    {
#pragma HLS LOOP_TRIPCOUNT min = BATCH_SIZE max = BATCH_SIZE
        for (int c = 0; c < CHANNEL_IN; c++)
        {
#pragma HLS LOOP_TRIPCOUNT min = CHANNEL_IN max = CHANNEL_IN
            for (int h = 0; h < new_height_in; h++)
            {
#pragma HLS LOOP_TRIPCOUNT min = new_height_in max = new_height_in
                for (int w = 0; w < new_width_in; w++)
                {
#pragma HLS LOOP_TRIPCOUNT min = new_width_in max = new_width_in
                    if (h < PADDING || h >= HEIGHT_IN + PADDING || w < PADDING || w >= WIDTH_IN + PADDING)
                        in_pad[n][c][h][w] = 0;
                    else
                        in_pad[n][c][h][w] = in[n][c][h - PADDING][w - PADDING];
                }
            }
        }
    }
}

static void compute_conv(float in_pad[BATCH_SIZE][CHANNEL_IN][new_height_in][new_width_in],
                         float afterConv[BATCH_SIZE][CHANNEL_OUT][HEIGHT_OUT][WIDTH_OUT])
{
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
                                afterConv[batch][out_ch][row][col] += in_pad[batch][in_ch][row * STRIDE + kernel_row][col * STRIDE + kernel_col] * kernel[out_ch][kernelChannelIdx][kernel_row][kernel_col];
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
                }
            }
        }
    }
}

static void compute_norm(float afterConv[BATCH_SIZE][CHANNEL_OUT][HEIGHT_OUT][WIDTH_OUT],
                         float afterNorm[BATCH_SIZE][CHANNEL_OUT][HEIGHT_OUT][WIDTH_OUT])
{
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

    switch (NORM_LAYER)
    {
    case 0: {
        const float RUNNING_MEAN[CHANNEL_OUT] = {82, 227, 444};
#pragma HLS array_partition variable = RUNNING_MEAN complete dim = 1
        const float RUNNING_VAR[CHANNEL_OUT] = {945, 3780, 8505};
#pragma HLS array_partition variable = RUNNING_VAR complete dim = 1
        const float weight[CHANNEL_OUT] = {0.5, 0.5, 0.5};
#pragma HLS array_partition variable = weight complete dim = 1
        const float bias[CHANNEL_OUT] = {0.2, 0.2, 0.2};
#pragma HLS array_partition variable = bias complete dim = 1

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
                        afterNorm[n][c][h][w] = ((afterConv[n][c][h][w] - RUNNING_MEAN[c]) / sqrt(RUNNING_VAR[c] + EPS)) * weight[c] + bias[c];
                    }
                }
            }
        }
        break;
    }

    case 1: {
        float ln_in[BATCH_SIZE][HEIGHT_OUT][WIDTH_OUT][CHANNEL_OUT];
#pragma HLS array_partition variable = ln_in complete dim = 1
        float weight[HEIGHT_OUT][WIDTH_OUT][CHANNEL_OUT];
#pragma HLS array_partition variable = weight complete dim = 1
        float bias[HEIGHT_OUT][WIDTH_OUT][CHANNEL_OUT];
#pragma HLS array_partition variable = bias complete dim = 1
        float mean[BATCH_SIZE];
#pragma HLS array_partition variable = mean complete dim = 1
        float var[BATCH_SIZE];
#pragma HLS array_partition variable = var complete dim = 1

    Reshape:
        for (int n = 0; n < BATCH_SIZE; n++)
        {
            for (int c = 0; c < CHANNEL_OUT; c++)
            {
                for (int h = 0; h < HEIGHT_OUT; h++)
                {
                    for (int w = 0; w < WIDTH_OUT; w++)
                    {
                        ln_in[n][h][w][c] = afterConv[n][c][h][w];
                    }
                }
            }
        }

        int total = HEIGHT_OUT * WIDTH_OUT * CHANNEL_OUT;
    Layer_Norm_Init:
        for (int n = 0; n < BATCH_SIZE; n++)
        {
            float sum = 0;
            float squareSum = 0;
            for (int h = 0; h < HEIGHT_OUT; h++)
            {
                for (int w = 0; w < WIDTH_OUT; w++)
                {
                    for (int c = 0; c < CHANNEL_OUT; c++)
                    {
                        sum += afterConv[n][c][h][w];
                        squareSum += afterConv[n][c][h][w] * afterConv[n][c][h][w];
                        weight[h][w][c] = h;
                        bias[h][w][c] = w;
                    }
                }
            }
            mean[n] = sum / total;
            var[n] = (squareSum / total) - (mean[n] * mean[n]);
        }

    Layer_Norm:
        for (int n = 0; n < BATCH_SIZE; n++)
        {
            for (int h = 0; h < HEIGHT_OUT; h++)
            {
                for (int w = 0; w < WIDTH_OUT; w++)
                {
                    for (int c = 0; c < CHANNEL_OUT; c++)
                    {
                        afterNorm[n][c][h][w] = (ln_in[n][h][w][c] - mean[n]) / sqrt(var[n] + EPS) * weight[h][w][c] + bias[h][w][c];
                    }
                }
            }
        }
        break;
    }

    default:
        break;
    }
}

static void compute_act(float afterNorm[BATCH_SIZE][CHANNEL_OUT][HEIGHT_OUT][WIDTH_OUT],
                        float afterAct[BATCH_SIZE][CHANNEL_OUT][HEIGHT_OUT][WIDTH_OUT])
{
    switch (ACT_LAYER)
    {
    case 0: {
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
                            afterAct[n][c][h][w] = 0;
                        else
                            afterAct[n][c][h][w] = afterNorm[n][c][h][w];
                    }
                }
            }
        }
        break;
    }
    case 1: {
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
                        afterAct[n][c][h][w] = afterNorm[n][c][h][w] * (1 / (1 + exp(-afterNorm[n][c][h][w])));
                    }
                }
            }
        }
        break;
    }
    case 2: {
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
                        afterAct[n][c][h][w] = 0.5 * x * (1.0 + tanh(sqrt(2.0 / 3.14159265358979323846) * (x + 0.044715 * pow(x, 3))));
                    }
                }
            }
        }
        break;
    }
    default:
        break;
    }
}

static void compute_skip(float afterAct[BATCH_SIZE][CHANNEL_OUT][HEIGHT_OUT][WIDTH_OUT],
                        float in[BATCH_SIZE][CHANNEL_IN][HEIGHT_IN][WIDTH_IN],
                        float *buffer_result)
{
Skip:
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
                        if(isSkip && (CHANNEL_IN == CHANNEL_OUT) && (HEIGHT_IN == HEIGHT_OUT) && (WIDTH_IN == WIDTH_OUT))
                            buffer_result[n * CHANNEL_OUT * HEIGHT_OUT * WIDTH_OUT + c * HEIGHT_OUT * WIDTH_OUT + h * WIDTH_OUT + w] = afterAct[n][c][h][w] + in[n][c][h][w]; 
                        else 
                            buffer_result[n * CHANNEL_OUT * HEIGHT_OUT * WIDTH_OUT + c * HEIGHT_OUT * WIDTH_OUT + h * WIDTH_OUT + w] = afterAct[n][c][h][w];
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

    void kernel_conv_norm_act(float *buffer_DataIn_1,
                              float *buffer_result)
    {
// TODO: modify depth
#pragma HLS INTERFACE m_axi port = buffer_DataIn_1 bundle = gmem0 depth = 96
#pragma HLS INTERFACE m_axi port = buffer_result bundle = gmem0 depth = 96

// #pragma HLS dataflow
// dataflow僅可以接受single reader and single writer
        // dataflow pragma instruct compiler to run following three APIs in parallel
        float in[BATCH_SIZE][CHANNEL_IN][HEIGHT_IN][WIDTH_IN];
#pragma HLS array_partition variable = in complete dim = 1
        float in_pad[BATCH_SIZE][CHANNEL_IN][new_height_in][new_width_in];
#pragma HLS array_partition variable = in_pad complete dim = 1
        float afterConv[BATCH_SIZE][CHANNEL_OUT][HEIGHT_OUT][WIDTH_OUT];
#pragma HLS array_partition variable = afterConv complete dim = 1
        float afterNorm[BATCH_SIZE][CHANNEL_OUT][HEIGHT_OUT][WIDTH_OUT];
#pragma HLS array_partition variable = afterNorm complete dim = 1
        float afterAct[BATCH_SIZE][CHANNEL_OUT][HEIGHT_OUT][WIDTH_OUT];
#pragma HLS array_partition variable = afterAct complete dim = 1
        load_input(buffer_DataIn_1, in);
        compute_padding(in, in_pad);
        compute_conv(in_pad, afterConv);
        compute_norm(afterConv, afterNorm);
        compute_act(afterNorm, afterAct);
        compute_skip(afterAct, in, buffer_result);
    }
}
