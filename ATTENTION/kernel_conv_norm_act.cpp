// Includes
#include <stdint.h>
#include<cmath>
/* Remember to modify test file */

// TODO: modify size
// TRIPCOUNT identifie
const int BATCH_SIZE1 = 1;
const int CHANNEL_IN1 = 4;
const int CHANNEL_OUT1 = 8;
const int HEIGHT_IN1 = 7;
const int WIDTH_IN1 = 7;

// TODO: modify conv parameters
// Convolution parameters
const int KERNEL_SIZE1 = 1;
const int STRIDE1 = 1;
const int GROUP1 = 1;

// PADDING1 and size
const int PADDING1 = (KERNEL_SIZE1 - STRIDE1) % 2 == 0 ? (KERNEL_SIZE1 - STRIDE1) / 2 : (KERNEL_SIZE1 - STRIDE1) / 2 + 1;
const int new_HEIGHT_IN1 = HEIGHT_IN1 + 2 * PADDING1;
const int new_WIDTH_IN1 = WIDTH_IN1 + 2 * PADDING1;
const int HEIGHT_OUT1 = (HEIGHT_IN1 - KERNEL_SIZE1 + 2 * PADDING1) / STRIDE1 + 1;
const int WIDTH_OUT1 = (WIDTH_IN1 - KERNEL_SIZE1 + 2 * PADDING1) / STRIDE1 + 1;

// For Convolution
const int KERNEL_CHANNEL1 = CHANNEL_IN1 / GROUP1;
const int inGROUP1Nums1 = CHANNEL_IN1 / GROUP1;
const int outGROUP1Nums1 = CHANNEL_OUT1 / GROUP1;
const bool isBias1 = true;

// Normalization parameters
const float EPS1 = 1e-5;

// TODO: modify hyperparameters
// Hyperparameters
const int NORM_LAYER1 = 1; // 0:batch_norm, 1: layer_norm
const int ACT_LAYER1 = 2;  // 0: relu, 1: silu, 2:gelu
const bool isSkip1 = false;

// Coding Style: function宣告要為static，遇到for迴圈前可以取error_type的名稱(ex: mem_rd)

static void load_input1(float *buffer_DataIn_1,
                       float in[BATCH_SIZE1][CHANNEL_IN1][HEIGHT_IN1][WIDTH_IN1])
{
init_in:
    for (int n = 0; n < BATCH_SIZE1; n++)
    {
        for (int c = 0; c < CHANNEL_IN1; c++)
        {
            for (int h = 0; h < HEIGHT_IN1; h++)
            {
                for (int w = 0; w < WIDTH_IN1; w++)
                {
                    in[n][c][h][w] = buffer_DataIn_1[n * CHANNEL_IN1 * HEIGHT_IN1 * WIDTH_IN1 + c * HEIGHT_IN1 * WIDTH_IN1 + h * WIDTH_IN1 + w];
                }
            }
        }
    }
}
static void compute_PADDING1(float in[BATCH_SIZE1][CHANNEL_IN1][HEIGHT_IN1][WIDTH_IN1],
                            float in_pad[BATCH_SIZE1][CHANNEL_IN1][new_HEIGHT_IN1][new_WIDTH_IN1])
{
PADDING1:
    for (int n = 0; n < BATCH_SIZE1; n++)
    {
        for (int c = 0; c < CHANNEL_IN1; c++)
        {
            for (int h = 0; h < new_HEIGHT_IN1; h++)
            {
                for (int w = 0; w < new_WIDTH_IN1; w++)
                {
                    if (h < PADDING1 || h >= HEIGHT_IN1 + PADDING1 || w < PADDING1 || w >= WIDTH_IN1 + PADDING1)
                        in_pad[n][c][h][w] = 0;
                    else
                        in_pad[n][c][h][w] = in[n][c][h - PADDING1][w - PADDING1];
                }
            }
        }
    }
}

static void compute_conv(float in_pad[BATCH_SIZE1][CHANNEL_IN1][new_HEIGHT_IN1][new_WIDTH_IN1],
                         float afterConv[BATCH_SIZE1][CHANNEL_OUT1][HEIGHT_OUT1][WIDTH_OUT1])
{
    float kernel[CHANNEL_OUT1][KERNEL_CHANNEL1][KERNEL_SIZE1][KERNEL_SIZE1];
    float bias[CHANNEL_OUT1];

init_kernel_bias:
    for (int k = 0; k < CHANNEL_OUT1; k++)
    {
        bias[k] = k + 0.5;
        for (int l = 0; l < KERNEL_CHANNEL1; l++)
        {
            for (int i = 0; i < KERNEL_SIZE1; i++)
            {
                for (int j = 0; j < KERNEL_SIZE1; j++)
                {
                    kernel[k][l][i][j] = (k+j+i+l)*0.1;
                }
            }
        }
    }

init_output:
    for (int n = 0; n < BATCH_SIZE1; n++)
    {
        for (int c = 0; c < CHANNEL_OUT1; c++)
        {
            for (int h = 0; h < HEIGHT_OUT1; h++)
            {
                for (int w = 0; w < WIDTH_OUT1; w++)
                {
                    if (isBias1)
                        afterConv[n][c][h][w] = bias[c];
                    else
                        afterConv[n][c][h][w] = 0;
                }
            }
        }
    }

execute:
Batch:
    for (int batch = 0; batch < BATCH_SIZE1; batch++)
    {
    Out_Row:
        for (int row = 0; row < HEIGHT_OUT1; row++)
        {
        Out_Column:
            for (int col = 0; col < WIDTH_OUT1; col++)
            {
            Kernel_Row:
                for (int kernel_row = 0; kernel_row < KERNEL_SIZE1; kernel_row++)
                {
                Kernel_Col:
                    for (int kernel_col = 0; kernel_col < KERNEL_SIZE1; kernel_col++)
                    {
                        int GROUP1Index = 0;
                    Output_Channel:
                        for (int out_ch = 0; out_ch < CHANNEL_OUT1; out_ch++)
                        {
                            int kernelChannelIdx = 0;
                        In_Channel:
                            for (int in_ch = GROUP1Index * inGROUP1Nums1; in_ch < CHANNEL_IN1; in_ch++)
                            {
                                afterConv[batch][out_ch][row][col] += in_pad[batch][in_ch][row * STRIDE1 + kernel_row][col * STRIDE1 + kernel_col] * kernel[out_ch][kernelChannelIdx][kernel_row][kernel_col];
                                kernelChannelIdx++;
                                if ((in_ch + 1) % inGROUP1Nums1 == 0)
                                    break;
                            }
                            if ((out_ch + 1) % outGROUP1Nums1 == 0)
                                GROUP1Index++;
                        }
                    }
                }
            }
        }
    }
}

static void compute_norm(float afterConv[BATCH_SIZE1][CHANNEL_OUT1][HEIGHT_OUT1][WIDTH_OUT1],
                         float afterNorm[BATCH_SIZE1][CHANNEL_OUT1][HEIGHT_OUT1][WIDTH_OUT1])
{
init_output:
    for (int n = 0; n < BATCH_SIZE1; n++)
    {
        for (int c = 0; c < CHANNEL_OUT1; c++)
        {
            for (int h = 0; h < HEIGHT_OUT1; h++)
            {
                for (int w = 0; w < WIDTH_OUT1; w++)
                {
                    afterNorm[n][c][h][w] = 0;
                }
            }
        }
    }

    switch (NORM_LAYER1)
    {
    case 0: {
        float RUNNING_MEAN[CHANNEL_OUT1];
        float RUNNING_VAR[CHANNEL_OUT1];
        float weight[CHANNEL_OUT1];
        float bias[CHANNEL_OUT1];

    init_parameters:
        for (int c = 0; c < CHANNEL_OUT1; c++)
        {
            RUNNING_MEAN[c] = 8;
            RUNNING_VAR[c] = 21.5;
            weight[c] = 0.5;
            bias[c] = 0.2;
        }

    Batch_norm:
        for (int n = 0; n < BATCH_SIZE1; n++)
        {
            for (int c = 0; c < CHANNEL_OUT1; c++)
            {
                for (int h = 0; h < HEIGHT_OUT1; h++)
                {
                    for (int w = 0; w < WIDTH_OUT1; w++)
                    {
                        afterNorm[n][c][h][w] = ((afterConv[n][c][h][w] - RUNNING_MEAN[c]) / sqrt(RUNNING_VAR[c] + EPS1)) * weight[c] + bias[c];
                    }
                }
            }
        }
        break;
    }

    case 1: {
        float ln_in[BATCH_SIZE1][HEIGHT_OUT1][WIDTH_OUT1][CHANNEL_OUT1];
        float weight[HEIGHT_OUT1][WIDTH_OUT1][CHANNEL_OUT1];
        float bias[HEIGHT_OUT1][WIDTH_OUT1][CHANNEL_OUT1];
        float mean[BATCH_SIZE1];
        float var[BATCH_SIZE1];

    Reshape:
        for (int n = 0; n < BATCH_SIZE1; n++)
        {
            for (int c = 0; c < CHANNEL_OUT1; c++)
            {
                for (int h = 0; h < HEIGHT_OUT1; h++)
                {
                    for (int w = 0; w < WIDTH_OUT1; w++)
                    {
                        ln_in[n][h][w][c] = afterConv[n][c][h][w];
                    }
                }
            }
        }

        int total = HEIGHT_OUT1 * WIDTH_OUT1 * CHANNEL_OUT1;
    Layer_Norm_Init:
        for (int n = 0; n < BATCH_SIZE1; n++)
        {
            float sum = 0;
            float squareSum = 0;
            for (int h = 0; h < HEIGHT_OUT1; h++)
            {
                for (int w = 0; w < WIDTH_OUT1; w++)
                {
                    for (int c = 0; c < CHANNEL_OUT1; c++)
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
        for (int n = 0; n < BATCH_SIZE1; n++)
        {
            for (int h = 0; h < HEIGHT_OUT1; h++)
            {
                for (int w = 0; w < WIDTH_OUT1; w++)
                {
                    for (int c = 0; c < CHANNEL_OUT1; c++)
                    {
                        afterNorm[n][c][h][w] = (ln_in[n][h][w][c] - mean[n]) / sqrt(var[n] + EPS1) * weight[h][w][c] + bias[h][w][c];
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

static void compute_act(float afterNorm[BATCH_SIZE1][CHANNEL_OUT1][HEIGHT_OUT1][WIDTH_OUT1],
                        float afterAct[BATCH_SIZE1][CHANNEL_OUT1][HEIGHT_OUT1][WIDTH_OUT1])
{
    switch (ACT_LAYER1)
    {
    case 0: {
        for (int n = 0; n < BATCH_SIZE1; n++)
        {
            for (int c = 0; c < CHANNEL_OUT1; c++)
            {
                for (int h = 0; h < HEIGHT_OUT1; h++)
                {
                    for (int w = 0; w < WIDTH_OUT1; w++)
                    {
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
        for (int n = 0; n < BATCH_SIZE1; n++)
        {
            for (int c = 0; c < CHANNEL_OUT1; c++)
            {
                for (int h = 0; h < HEIGHT_OUT1; h++)
                {
                    for (int w = 0; w < WIDTH_OUT1; w++)
                    {
                        afterAct[n][c][h][w] = afterNorm[n][c][h][w] * (1 / (1 + exp(-afterNorm[n][c][h][w])));
                    }
                }
            }
        }
        break;
    }
    case 2: {
        for (int n = 0; n < BATCH_SIZE1; n++)
        {
            for (int c = 0; c < CHANNEL_OUT1; c++)
            {
                for (int h = 0; h < HEIGHT_OUT1; h++)
                {
                    for (int w = 0; w < WIDTH_OUT1; w++)
                    {
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

static void compute_skip(float afterAct[BATCH_SIZE1][CHANNEL_OUT1][HEIGHT_OUT1][WIDTH_OUT1],
                         float in[BATCH_SIZE1][CHANNEL_IN1][HEIGHT_IN1][WIDTH_IN1],
                         float *buffer_result)
{
Skip:
    for (int n = 0; n < BATCH_SIZE1; n++)
    {
        for (int c = 0; c < CHANNEL_OUT1; c++)
        {
            for (int h = 0; h < HEIGHT_OUT1; h++)
            {
                for (int w = 0; w < WIDTH_OUT1; w++)
                {
                    if (isSkip1 && (CHANNEL_IN1 == CHANNEL_OUT1) && (HEIGHT_IN1 == HEIGHT_OUT1) && (WIDTH_IN1 == WIDTH_OUT1))
                        buffer_result[n * CHANNEL_OUT1 * HEIGHT_OUT1 * WIDTH_OUT1 + c * HEIGHT_OUT1 * WIDTH_OUT1 + h * WIDTH_OUT1 + w] = afterAct[n][c][h][w] + in[n][c][h][w];
                    else
                        buffer_result[n * CHANNEL_OUT1 * HEIGHT_OUT1 * WIDTH_OUT1 + c * HEIGHT_OUT1 * WIDTH_OUT1 + h * WIDTH_OUT1 + w] = afterAct[n][c][h][w];
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
        // #pragma HLS dataflow
        // dataflow僅可以接受single reader and single writer
        // dataflow pragma instruct compiler to run following three APIs in parallel
        float in[BATCH_SIZE1][CHANNEL_IN1][HEIGHT_IN1][WIDTH_IN1];
        float in_pad[BATCH_SIZE1][CHANNEL_IN1][new_HEIGHT_IN1][new_WIDTH_IN1];
        float afterConv[BATCH_SIZE1][CHANNEL_OUT1][HEIGHT_OUT1][WIDTH_OUT1];
        float afterNorm[BATCH_SIZE1][CHANNEL_OUT1][HEIGHT_OUT1][WIDTH_OUT1];
        float afterAct[BATCH_SIZE1][CHANNEL_OUT1][HEIGHT_OUT1][WIDTH_OUT1];
        load_input1(buffer_DataIn_1, in);

        compute_PADDING1(in, in_pad);
        compute_conv(in_pad, afterConv);

       /* std::cout<<"2";
        compute_norm(afterConv, afterNorm);
        std::cout<<"2";
        compute_act(afterNorm, afterAct);*/
        compute_skip(afterConv, in, buffer_result);
    }
}
