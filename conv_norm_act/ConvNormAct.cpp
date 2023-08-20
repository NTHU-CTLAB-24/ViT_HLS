#include <math.h>
#include <cmath>
#include <iostream>

// In and out parameters
#define BATCH_SIZE 2
#define CHANNEL_IN 6
#define CHANNEL_OUT 3
#define HEIGHT_IN 8
#define WIDTH_IN 8
// Convolution parameters
#define KERNEL_SIZE 3
#define PADDING 0
#define STRIDE 1
#define GROUP 3
// BatchNorm parameters
#define EPS 1e-5
#define GAMMA 0.5
#define BETA 0.2

int main()
{
    // For convolution
    const int HEIGHT_OUT = (HEIGHT_IN - KERNEL_SIZE + 2 * PADDING) / STRIDE + 1;
    const int WIDTH_OUT = (WIDTH_IN - KERNEL_SIZE + 2 * PADDING) / STRIDE + 1;
    const int KERNEL_CHANNEL = CHANNEL_IN / GROUP;
    const int inGroupNums = CHANNEL_IN / GROUP;
    const int outGroupNums = CHANNEL_OUT / GROUP;
    std::cout << "Check output size: " << HEIGHT_OUT << " * " << WIDTH_OUT << std::endl << std::endl;;
    // For BatchNorm
    const float RUNNING_MEAN[CHANNEL_IN] = {82, 227, 444};
    const float RUNNING_VAR[CHANNEL_IN] = {945, 3780, 8505}; 

    // declare array
    float In[BATCH_SIZE][CHANNEL_IN][HEIGHT_IN][WIDTH_IN];
    float afterConv[BATCH_SIZE][CHANNEL_OUT][HEIGHT_OUT][WIDTH_OUT];
    float afterBN[BATCH_SIZE][CHANNEL_OUT][HEIGHT_OUT][WIDTH_OUT];
    float Out[BATCH_SIZE][CHANNEL_OUT][HEIGHT_OUT][WIDTH_OUT];
    float Kernel[CHANNEL_OUT][KERNEL_CHANNEL][KERNEL_SIZE][KERNEL_SIZE];
    float Bias[CHANNEL_OUT];

    bool isBias = true;
    bool isRelu = false;
    bool isSilu = false;
    bool isGelu = true;

Initalize_In:
    for (int n = 0; n < BATCH_SIZE; n++)
    {
        for (int c = 0; c < CHANNEL_IN; c++)
        {
            for (int h = 0; h < HEIGHT_IN; h++)
            {
                for (int w = 0; w < WIDTH_IN; w++)
                {

                    In[n][c][h][w] = h + c;
                    // if (w == WIDTH_IN - 1)
                    //     std::cout << In[n][c][h][w] << std::endl;
                    // else
                    //     std::cout << In[n][c][h][w] << " ";
                }
            }
        }
    }

Initalize_Kernel:

    for (int k = 0; k < CHANNEL_OUT; k++)
    {
        for (int l = 0; l < KERNEL_CHANNEL; l++)
        {
            for (int i = 0; i < KERNEL_SIZE; i++)
            {
                for (int j = 0; j < KERNEL_SIZE; j++)
                {

                    Kernel[k][l][i][j] = j + k;
                    // if(j == KERNEL_SIZE - 1)
                    //     std::cout << Kernel[k][l][i][j] << std::endl;
                    // else
                    //     std::cout <<Kernel[k][l][i][j] << " ";
                }
            }
        }
    }

Initialize_Bias:
    if (isBias)
    {
        for (int c = 0; c < CHANNEL_OUT; c++)
        {

            Bias[c] = c + 10;
        }
    }

Intialize_Out:
    for (int n = 0; n < BATCH_SIZE; n++)
    {
        for (int c = 0; c < CHANNEL_OUT; c++)
        {
            for (int h = 0; h < HEIGHT_OUT; h++)
            {
                for (int w = 0; w < WIDTH_OUT; w++)
                {

                    afterConv[n][c][h][w] = 0;
                    afterBN[n][c][h][w] = 0;
                    Out[n][c][h][w] = 0;
                }
            }
        }
    }


Convolution:
Batch:
    for (int batch = 0; batch < BATCH_SIZE; batch++)
    {
    Out_Row:
        for (int row = 0; row < HEIGHT_OUT; row++)
        {
        Out_Column:
            for (int col = 0; col < WIDTH_OUT; col++)
            {
                int groupIndex = 0;
            Out_channel:
                for (int ch_out = 0; ch_out < CHANNEL_OUT; ch_out++)
                {
                    int kernelChannelIdx = 0;
                In_channel:
                    for (int ch_in = groupIndex * inGroupNums; ch_in < CHANNEL_IN; ch_in++)
                    {
                    Kernel_Row:
                        for (int kernel_row = 0; kernel_row < KERNEL_SIZE; kernel_row++)
                        {
                        Kernel_Col:
                            for (int kernel_col = 0; kernel_col < KERNEL_SIZE; kernel_col++)
                            {
                                afterConv[batch][ch_out][row][col] += In[batch][ch_in][row * STRIDE + kernel_row][col * STRIDE + kernel_col] * Kernel[ch_out][kernelChannelIdx][kernel_row][kernel_col];
                            }
                        }
                        kernelChannelIdx++;
                        if ((ch_in + 1) % inGroupNums == 0)
                            break;
                    }
                    if ((ch_out + 1) % outGroupNums == 0)
                        groupIndex++;
                    if (isBias)
                        afterConv[batch][ch_out][row][col] += Bias[ch_out];
                }
            }
        }
    }

std::cout << "afterConv array: " << std::endl;
for (int n = 0; n < BATCH_SIZE; n++)
    {
        for (int c = 0; c < CHANNEL_OUT; c++)
        {
            for (int h = 0; h < HEIGHT_OUT; h++)
            {
                for (int w = 0; w < WIDTH_OUT; w++)
                {

                    if (w == WIDTH_OUT - 1)
                        std::cout << afterConv[n][c][h][w] << std::endl;
                    else
                        std::cout << afterConv[n][c][h][w] << " ";
                }
            }
        }
    }
std::cout << std::endl;

Batch_Norm:
BATCH:
        for (int n = 0; n < BATCH_SIZE; n++)
        {
CHANNEL:
    for (int c = 0; c < CHANNEL_IN; c++)
    {
        HEIGHT:
            for (int h = 0; h < HEIGHT_IN; h++)
            {
            WIDTH:
                for (int w = 0; w < WIDTH_IN; w++)
                {
                    afterBN[n][c][h][w] = ((afterConv[n][c][h][w] - RUNNING_MEAN[c]) / sqrt(RUNNING_VAR[c] + EPS)) * GAMMA + BETA;
                }
            }
        }
    }

std::cout << "afterBN array: " << std::endl;
    for (int n = 0; n < BATCH_SIZE; n++)
    {
        for (int c = 0; c < CHANNEL_OUT; c++)
        {
            for (int h = 0; h < HEIGHT_OUT; h++)
            {
                for (int w = 0; w < WIDTH_OUT; w++)
                {
                    if (w == WIDTH_OUT - 1)
                        std::cout << afterBN[n][c][h][w] << std::endl;
                    else
                        std::cout << afterBN[n][c][h][w] << " ";
                }
            }
        }
    }

std::cout << std::endl;
Relu:
if(isRelu){
for (int n = 0; n < BATCH_SIZE; n++)
        {
    for (int c = 0; c < CHANNEL_OUT; c++)
    {
            for (int h = 0; h < HEIGHT_OUT; h++)
            {
                for (int w = 0; w < WIDTH_OUT; w++)
                {
                    if(afterBN[n][c][h][w] < 0)
                        Out[n][c][h][w] = 0;
                    else
                        Out[n][c][h][w] = afterBN[n][c][h][w];
                }
            }
        }
    }
}

Silu:
if(isSilu){
    for (int n = 0; n < BATCH_SIZE; n++)
    {
        for (int c = 0; c < CHANNEL_OUT; c++)
        {
            for (int h = 0; h < HEIGHT_OUT; h++)
            {
                for (int w = 0; w < WIDTH_OUT; w++)
                {
                    Out[n][c][h][w] = afterBN[n][c][h][w] * (1 / (1 + exp(-afterBN[n][c][h][w])));
                }
            }
        }
    }
}

Gelu:
if(isGelu){
     for (int n = 0; n < BATCH_SIZE; n++)
    {
        for (int c = 0; c < CHANNEL_OUT; c++)
        {
            for (int h = 0; h < HEIGHT_OUT; h++)
            {
                for (int w = 0; w < WIDTH_OUT; w++)
                {
                    float x = afterBN[n][c][h][w];
                    Out[n][c][h][w] = 0.5 * x * (1.0 + tanh(sqrt(2.0 / M_PI) * (x + 0.044715 * pow(x, 3))));
                }
            }
        }
    }
}

    std::cout << "Output array: " << std::endl;

Output:
    for (int n = 0; n < BATCH_SIZE; n++)
    {
        for (int c = 0; c < CHANNEL_OUT; c++)
        {
            for (int h = 0; h < HEIGHT_OUT; h++)
            {
                for (int w = 0; w < WIDTH_OUT; w++)
                {

                    if (w == WIDTH_OUT - 1)
                        std::cout << Out[n][c][h][w] << std::endl;
                    else
                        std::cout << Out[n][c][h][w] << " ";
                }
            }
        }
    }

    return 0;
}