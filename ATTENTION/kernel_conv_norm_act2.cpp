// Includes
#include <stdint.h>
#include<cmath>
#include<iostream>
/* Remember to modify test file */

// TODO: modify size
// TRIPCOUNT identifie
const int BATCH_SIZE2 = 1;
const int CHANNEL_IN2 = 4;
const int CHANNEL_OUT2 = 12;
const int HEIGHT_IN2 = 7;
const int WIDTH_IN2 = 7;

// TODO: modify conv parameters
// Convolution parameters
const int KERNEL_SIZE2 = 1;
const int STRIDE2 = 1;
const int GROUP2 = 1;

// PADDING2 and size
const int PADDING2 = (KERNEL_SIZE2 - STRIDE2) % 2 == 0 ? (KERNEL_SIZE2 - STRIDE2) / 2 : (KERNEL_SIZE2 - STRIDE2) / 2 + 1;
const int new_HEIGHT_IN2 = HEIGHT_IN2 + 2 * PADDING2;
const int new_WIDTH_IN2 = WIDTH_IN2 + 2 * PADDING2;
const int HEIGHT_OUT2 = (HEIGHT_IN2 - KERNEL_SIZE2 + 2 * PADDING2) / STRIDE2 + 1;
const int WIDTH_OUT2 = (WIDTH_IN2 - KERNEL_SIZE2 + 2 * PADDING2) / STRIDE2 + 1;

// For Convolution
const int KERNEL_CHANNEL2 = CHANNEL_IN2 / GROUP2;
const int inGROUP2Nums2 = CHANNEL_IN2 / GROUP2;
const int outGROUP2Nums2 = CHANNEL_OUT2 / GROUP2;
const bool isBias2 = true;

// Normalization parameters
const float EPS2 = 1e-5;

// TODO: modify hyperparameters
// Hyperparameters
const int NORM_LAYER2 = 1; // 0:batch_norm, 1: layer_norm
const int ACT_LAYER2 = 2;  // 0: relu, 1: silu, 2:gelu
const bool isSkip2 = false;

// Coding Style: function宣告要為static，遇到for迴圈前可以取error_type的名稱(ex: mem_rd)

static void load_input2(float *buffer_DataIn_1,
                       float in[BATCH_SIZE2][CHANNEL_IN2][HEIGHT_IN2][WIDTH_IN2])
{
init_in:
    for (int n = 0; n < BATCH_SIZE2; n++)
    {
        for (int c = 0; c < CHANNEL_IN2; c++)
        {
            for (int h = 0; h < HEIGHT_IN2; h++)
            {
                for (int w = 0; w < WIDTH_IN2; w++)
                {
                    in[n][c][h][w] = buffer_DataIn_1[n * CHANNEL_IN2 * HEIGHT_IN2 * WIDTH_IN2 + c * HEIGHT_IN2 * WIDTH_IN2 + h * WIDTH_IN2 + w];
                }
            }
        }
    }
}
static void compute_PADDING2(float in[BATCH_SIZE2][CHANNEL_IN2][HEIGHT_IN2][WIDTH_IN2],
                            float in_pad[BATCH_SIZE2][CHANNEL_IN2][new_HEIGHT_IN2][new_WIDTH_IN2])
{
PADDING2:
    for (int n = 0; n < BATCH_SIZE2; n++)
    {
        for (int c = 0; c < CHANNEL_IN2; c++)
        {
            for (int h = 0; h < new_HEIGHT_IN2; h++)
            {
                for (int w = 0; w < new_WIDTH_IN2; w++)
                {
                    if (h < PADDING2 || h >= HEIGHT_IN2 + PADDING2 || w < PADDING2 || w >= WIDTH_IN2 + PADDING2)
                        in_pad[n][c][h][w] = 0;
                    else
                        in_pad[n][c][h][w] = in[n][c][h - PADDING2][w - PADDING2];
                }
            }
        }
    }
}

static void compute_conv(float in_pad[BATCH_SIZE2][CHANNEL_IN2][new_HEIGHT_IN2][new_WIDTH_IN2],
                         float afterConv[BATCH_SIZE2][CHANNEL_OUT2][HEIGHT_OUT2][WIDTH_OUT2])
{
    float kernel[CHANNEL_OUT2][KERNEL_CHANNEL2][KERNEL_SIZE2][KERNEL_SIZE2];
    float bias[CHANNEL_OUT2];

init_kernel_bias:
    for (int k = 0; k < CHANNEL_OUT2; k++)
    {
        bias[k] = 2;
        for (int l = 0; l < KERNEL_CHANNEL2; l++)
        {
            for (int i = 0; i < KERNEL_SIZE2; i++)
            {
                for (int j = 0; j < KERNEL_SIZE2; j++)
                {
                    kernel[k][l][i][j] = 1.2;
                }
            }
        }
    }

init_output:
    for (int n = 0; n < BATCH_SIZE2; n++)
    {
        for (int c = 0; c < CHANNEL_OUT2; c++)
        {
            for (int h = 0; h < HEIGHT_OUT2; h++)
            {
                for (int w = 0; w < WIDTH_OUT2; w++)
                {
                    if (isBias2)
                        afterConv[n][c][h][w] = bias[c];
                    else
                        afterConv[n][c][h][w] = 0;
                }
            }
        }
    }

execute:
Batch:
    for (int batch = 0; batch < BATCH_SIZE2; batch++)
    {
    Out_Row:
        for (int row = 0; row < HEIGHT_OUT2; row++)
        {
        Out_Column:
            for (int col = 0; col < WIDTH_OUT2; col++)
            {
            Kernel_Row:
                for (int kernel_row = 0; kernel_row < KERNEL_SIZE2; kernel_row++)
                {
                Kernel_Col:
                    for (int kernel_col = 0; kernel_col < KERNEL_SIZE2; kernel_col++)
                    {
                        int GROUP2Index = 0;
                    Output_Channel:
                        for (int out_ch = 0; out_ch < CHANNEL_OUT2; out_ch++)
                        {
                            int kernelChannelIdx = 0;
                        In_Channel:
                            for (int in_ch = GROUP2Index * inGROUP2Nums2; in_ch < CHANNEL_IN2; in_ch++)
                            {
                                afterConv[batch][out_ch][row][col] += in_pad[batch][in_ch][row * STRIDE2 + kernel_row][col * STRIDE2 + kernel_col] * kernel[out_ch][kernelChannelIdx][kernel_row][kernel_col];
                                kernelChannelIdx++;
                                if ((in_ch + 1) % inGROUP2Nums2 == 0)
                                    break;
                            }
                            if ((out_ch + 1) % outGROUP2Nums2 == 0)
                                GROUP2Index++;
                        }
                    }
                }
            }
        }
    }
}

static void compute_norm(float afterConv[BATCH_SIZE2][CHANNEL_OUT2][HEIGHT_OUT2][WIDTH_OUT2],
                         float afterNorm[BATCH_SIZE2][CHANNEL_OUT2][HEIGHT_OUT2][WIDTH_OUT2])
{
init_output:
    for (int n = 0; n < BATCH_SIZE2; n++)
    {
        for (int c = 0; c < CHANNEL_OUT2; c++)
        {
            for (int h = 0; h < HEIGHT_OUT2; h++)
            {
                for (int w = 0; w < WIDTH_OUT2; w++)
                {
                    afterNorm[n][c][h][w] = 0;
                }
            }
        }
    }

    switch (NORM_LAYER2)
    {
    case 0: {
        float RUNNING_MEAN[CHANNEL_OUT2];
        float RUNNING_VAR[CHANNEL_OUT2];
        float weight[CHANNEL_OUT2];
        float bias[CHANNEL_OUT2];

    init_parameters:
        for (int c = 0; c < CHANNEL_OUT2; c++)
        {
            RUNNING_MEAN[c] = 8;
            RUNNING_VAR[c] = 21.5;
            weight[c] = 0.5;
            bias[c] = 0.2;
        }

    Batch_norm:
        for (int n = 0; n < BATCH_SIZE2; n++)
        {
            for (int c = 0; c < CHANNEL_OUT2; c++)
            {
                for (int h = 0; h < HEIGHT_OUT2; h++)
                {
                    for (int w = 0; w < WIDTH_OUT2; w++)
                    {
                        afterNorm[n][c][h][w] = ((afterConv[n][c][h][w] - RUNNING_MEAN[c]) / sqrt(RUNNING_VAR[c] + EPS2)) * weight[c] + bias[c];
                    }
                }
            }
        }
        break;
    }

    case 1: {
        float ln_in[BATCH_SIZE2][HEIGHT_OUT2][WIDTH_OUT2][CHANNEL_OUT2];
        float weight[HEIGHT_OUT2][WIDTH_OUT2][CHANNEL_OUT2];
        float bias[HEIGHT_OUT2][WIDTH_OUT2][CHANNEL_OUT2];
        float mean[BATCH_SIZE2];
        float var[BATCH_SIZE2];

    Reshape:
        for (int n = 0; n < BATCH_SIZE2; n++)
        {
            for (int c = 0; c < CHANNEL_OUT2; c++)
            {
                for (int h = 0; h < HEIGHT_OUT2; h++)
                {
                    for (int w = 0; w < WIDTH_OUT2; w++)
                    {
                        ln_in[n][h][w][c] = afterConv[n][c][h][w];
                    }
                }
            }
        }

        int total = HEIGHT_OUT2 * WIDTH_OUT2 * CHANNEL_OUT2;
    Layer_Norm_Init:
        for (int n = 0; n < BATCH_SIZE2; n++)
        {
            float sum = 0;
            float squareSum = 0;
            for (int h = 0; h < HEIGHT_OUT2; h++)
            {
                for (int w = 0; w < WIDTH_OUT2; w++)
                {
                    for (int c = 0; c < CHANNEL_OUT2; c++)
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
        for (int n = 0; n < BATCH_SIZE2; n++)
        {
            for (int h = 0; h < HEIGHT_OUT2; h++)
            {
                for (int w = 0; w < WIDTH_OUT2; w++)
                {
                    for (int c = 0; c < CHANNEL_OUT2; c++)
                    {
                        afterNorm[n][c][h][w] = (ln_in[n][h][w][c] - mean[n]) / sqrt(var[n] + EPS2) * weight[h][w][c] + bias[h][w][c];
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

static void compute_act(float afterNorm[BATCH_SIZE2][CHANNEL_OUT2][HEIGHT_OUT2][WIDTH_OUT2],
                        float afterAct[BATCH_SIZE2][CHANNEL_OUT2][HEIGHT_OUT2][WIDTH_OUT2])
{
    switch (ACT_LAYER2)
    {
    case 0: {
        for (int n = 0; n < BATCH_SIZE2; n++)
        {
            for (int c = 0; c < CHANNEL_OUT2; c++)
            {
                for (int h = 0; h < HEIGHT_OUT2; h++)
                {
                    for (int w = 0; w < WIDTH_OUT2; w++)
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
        for (int n = 0; n < BATCH_SIZE2; n++)
        {
            for (int c = 0; c < CHANNEL_OUT2; c++)
            {
                for (int h = 0; h < HEIGHT_OUT2; h++)
                {
                    for (int w = 0; w < WIDTH_OUT2; w++)
                    {
                        afterAct[n][c][h][w] = afterNorm[n][c][h][w] * (1 / (1 + exp(-afterNorm[n][c][h][w])));
                    }
                }
            }
        }
        break;
    }
    case 2: {
        for (int n = 0; n < BATCH_SIZE2; n++)
        {
            for (int c = 0; c < CHANNEL_OUT2; c++)
            {
                for (int h = 0; h < HEIGHT_OUT2; h++)
                {
                    for (int w = 0; w < WIDTH_OUT2; w++)
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

static void compute_skip(float afterAct[BATCH_SIZE2][CHANNEL_OUT2][HEIGHT_OUT2][WIDTH_OUT2],
                         float in[BATCH_SIZE2][CHANNEL_IN2][HEIGHT_IN2][WIDTH_IN2],
                         float *buffer_result)
{
Skip:
    for (int n = 0; n < BATCH_SIZE2; n++)
    {
        for (int c = 0; c < CHANNEL_OUT2; c++)
        {
            for (int h = 0; h < HEIGHT_OUT2; h++)
            {
                for (int w = 0; w < WIDTH_OUT2; w++)
                {
                    if (isSkip2 && (CHANNEL_IN2 == CHANNEL_OUT2) && (HEIGHT_IN2 == HEIGHT_OUT2) && (WIDTH_IN2 == WIDTH_OUT2))
                        buffer_result[n * CHANNEL_OUT2 * HEIGHT_OUT2 * WIDTH_OUT2 + c * HEIGHT_OUT2 * WIDTH_OUT2 + h * WIDTH_OUT2 + w] = afterAct[n][c][h][w] + in[n][c][h][w];
                    else
                        buffer_result[n * CHANNEL_OUT2 * HEIGHT_OUT2 * WIDTH_OUT2 + c * HEIGHT_OUT2 * WIDTH_OUT2 + h * WIDTH_OUT2 + w] = afterAct[n][c][h][w];
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

    void kernel_conv_norm_act2(float *buffer_DataIn_1,
                              float *buffer_result)
    {
// TODO: modify depth
        // #pragma HLS dataflow
        // dataflow僅可以接受single reader and single writer
        // dataflow pragma instruct compiler to run following three APIs in parallel
        float in[BATCH_SIZE2][CHANNEL_IN2][HEIGHT_IN2][WIDTH_IN2];
        float in_pad[BATCH_SIZE2][CHANNEL_IN2][new_HEIGHT_IN2][new_WIDTH_IN2];
        float afterConv[BATCH_SIZE2][CHANNEL_OUT2][HEIGHT_OUT2][WIDTH_OUT2];
        float afterNorm[BATCH_SIZE2][CHANNEL_OUT2][HEIGHT_OUT2][WIDTH_OUT2];
        float afterAct[BATCH_SIZE2][CHANNEL_OUT2][HEIGHT_OUT2][WIDTH_OUT2];
        /*for(int i=0;i<BATCH_SIZE2 * CHANNEL_IN2 * HEIGHT_IN2 * WIDTH_IN2;i++){
            std::cout<<buffer_DataIn_1[i]<<" ";
            if(i%7==6)std::cout<<"\n";
        }*/
        load_input2(buffer_DataIn_1, in);
        compute_PADDING2(in, in_pad);
        compute_conv(in_pad, afterConv);

        //compute_norm(afterConv, afterNorm);
        compute_act(afterConv, afterAct);
        /*for(int i=0;i<BATCH_SIZE2;i++){
            for(int j=0;j<CHANNEL_OUT2;j++){
                for(int k=0;k<HEIGHT_OUT2;k++){
                    for(int l=0;l<WIDTH_OUT2;l++){
                        std::cout<<afterAct[i][j][k][l]<<" ";
                    }
                    std::cout<<"\n";
                }
                std::cout<<"\n";
            }
        }*/
        compute_skip(afterAct, in, buffer_result);

    }
}

