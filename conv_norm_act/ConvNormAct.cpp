#include <cmath>
#include <iostream>
#include <math.h>

// In and out parameters
#define BATCH_SIZE 2
#define CHANNEL_IN 3
#define CHANNEL_OUT 3
#define HEIGHT_IN 4
#define WIDTH_IN 4
// Convolution parameters
#define KERNEL_SIZE 3
#define STRIDE 1
#define GROUP 1
// Normalization parameters
#define EPS 1e-5

int main()
{
    // Padding and size
    const int PADDING = ceil((float)(KERNEL_SIZE - STRIDE) / 2);
    const int new_height_in = HEIGHT_IN + 2 * PADDING;
    const int new_width_in = WIDTH_IN + 2 * PADDING;
    const int HEIGHT_OUT = (HEIGHT_IN - KERNEL_SIZE + 2 * PADDING) / STRIDE + 1;
    const int WIDTH_OUT = (WIDTH_IN - KERNEL_SIZE + 2 * PADDING) / STRIDE + 1;

    // For convolution
    const int KERNEL_CHANNEL = CHANNEL_IN / GROUP;
    const int inGroupNums = CHANNEL_IN / GROUP;
    const int outGroupNums = CHANNEL_OUT / GROUP;

    // For BatchNorm
    const float RUNNING_MEAN[CHANNEL_OUT] = {82, 227, 444};
    const float RUNNING_VAR[CHANNEL_OUT] = {945, 3780, 8505};
    const float gamma[CHANNEL_OUT] = {0.5, 0.5, 0.5};
    const float beta[CHANNEL_OUT] = {0.2, 0.2, 0.2};

    // For LayerNorm
    int total = HEIGHT_OUT * WIDTH_OUT * CHANNEL_OUT;
    float ln_in[BATCH_SIZE][HEIGHT_OUT][WIDTH_OUT][CHANNEL_OUT];
    float weight[HEIGHT_OUT][WIDTH_OUT][CHANNEL_OUT];
    float bias[HEIGHT_OUT][WIDTH_OUT][CHANNEL_OUT];
    float mean[HEIGHT_OUT];
    float var[HEIGHT_OUT];

    // declare array
    float In[BATCH_SIZE][CHANNEL_IN][HEIGHT_IN][WIDTH_IN];
    float in_pad[BATCH_SIZE][CHANNEL_IN][new_height_in][new_width_in];
    float afterConv[BATCH_SIZE][CHANNEL_OUT][HEIGHT_OUT][WIDTH_OUT];
    float afterNorm[BATCH_SIZE][CHANNEL_OUT][HEIGHT_OUT][WIDTH_OUT];
    float afterAct[BATCH_SIZE][CHANNEL_OUT][HEIGHT_OUT][WIDTH_OUT];
    float Out[BATCH_SIZE][CHANNEL_OUT][HEIGHT_OUT][WIDTH_OUT];
    float Kernel[CHANNEL_OUT][KERNEL_CHANNEL][KERNEL_SIZE][KERNEL_SIZE];
    float Bias[CHANNEL_OUT];

    bool isBias = true;
    bool isBN = true;
    bool isLN = false;
    bool isRelu = true;
    bool isSilu = false;
    bool isGelu = false;
    bool isSkip = true;

    std::cout << "Check output shape: ("
              << BATCH_SIZE << ", "
              << CHANNEL_OUT << ", "
              << HEIGHT_OUT << ", "
              << WIDTH_OUT << ")" << std::endl;

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
                    afterNorm[n][c][h][w] = 0;
                    afterAct[n][c][h][w] = 0;
                    Out[n][c][h][w] = 0;
                }
            }
        }
    }

Padding:
    for (int n = 0; n < BATCH_SIZE; n++)
    {
        for (int c = 0; c < CHANNEL_IN; c++)
        {
            for (int h = 0; h < new_height_in; h++)
            {
                for (int w = 0; w < new_width_in; w++)
                {

                    if (h < PADDING || h >= HEIGHT_IN + PADDING || w < PADDING || w >= WIDTH_IN + PADDING)
                        in_pad[n][c][h][w] = 0;
                    else
                        in_pad[n][c][h][w] = In[n][c][h - PADDING][w - PADDING];
                    // if (w == new_width_in - 1)
                    //     std::cout << in_pad[n][c][h][w] << std::endl;
                    // else
                    //     std::cout << in_pad[n][c][h][w] << " ";
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
                                afterConv[batch][ch_out][row][col] += in_pad[batch][ch_in][row * STRIDE + kernel_row][col * STRIDE + kernel_col] * Kernel[ch_out][kernelChannelIdx][kernel_row][kernel_col];
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
afterConv:
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
            break;
        }
        break;
    }
    std::cout << std::endl;

    if (isBN)
    {
    Batch_Norm:
    BATCH:
        for (int n = 0; n < BATCH_SIZE; n++)
        {
        CHANNEL:
            for (int c = 0; c < CHANNEL_OUT; c++)
            {
            HEIGHT:
                for (int h = 0; h < HEIGHT_OUT; h++)
                {
                WIDTH:
                    for (int w = 0; w < WIDTH_OUT; w++)
                    {
                        afterNorm[n][c][h][w] = ((afterConv[n][c][h][w] - RUNNING_MEAN[c]) / sqrt(RUNNING_VAR[c] + EPS)) * gamma[c] + beta[c];
                    }
                }
            }
        }
    }

    if(isLN){
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
    }

    std::cout << "afterNorm array: " << std::endl;
afterNorm:
    for (int n = 0; n < BATCH_SIZE; n++)
    {
        for (int c = 0; c < CHANNEL_OUT; c++)
        {
            for (int h = 0; h < HEIGHT_OUT; h++)
            {
                for (int w = 0; w < WIDTH_OUT; w++)
                {
                    if (w == WIDTH_OUT - 1)
                        std::cout << afterNorm[n][c][h][w] << std::endl;
                    else
                        std::cout << afterNorm[n][c][h][w] << " ";
                }
            }
            break;
        }
        break;
    }

    std::cout << std::endl;
Relu:
    if (isRelu)
    {
        for (int n = 0; n < BATCH_SIZE; n++)
        {
            for (int c = 0; c < CHANNEL_OUT; c++)
            {
                for (int h = 0; h < HEIGHT_OUT; h++)
                {
                    for (int w = 0; w < WIDTH_OUT; w++)
                    {
                        if (afterNorm[n][c][h][w] < 0)
                            afterAct[n][c][h][w] = 0;
                        else
                            afterAct[n][c][h][w] = afterNorm[n][c][h][w];
                    }
                }
            }
        }
    }

Silu:
    if (isSilu)
    {
        for (int n = 0; n < BATCH_SIZE; n++)
        {
            for (int c = 0; c < CHANNEL_OUT; c++)
            {
                for (int h = 0; h < HEIGHT_OUT; h++)
                {
                    for (int w = 0; w < WIDTH_OUT; w++)
                    {
                        afterAct[n][c][h][w] = afterNorm[n][c][h][w] * (1 / (1 + exp(-afterNorm[n][c][h][w])));
                    }
                }
            }
        }
    }

Gelu:
    if (isGelu)
    {
        for (int n = 0; n < BATCH_SIZE; n++)
        {
            for (int c = 0; c < CHANNEL_OUT; c++)
            {
                for (int h = 0; h < HEIGHT_OUT; h++)
                {
                    for (int w = 0; w < WIDTH_OUT; w++)
                    {
                        float x = afterNorm[n][c][h][w];
                        afterAct[n][c][h][w] = 0.5 * x * (1.0 + tanh(sqrt(2.0 / M_PI) * (x + 0.044715 * pow(x, 3))));
                    }
                }
            }
        }
    }
   std::cout << "afterAct array: " << std::endl;

afterAct:
    for (int n = 0; n < BATCH_SIZE; n++)
    {
        for (int c = 0; c < CHANNEL_OUT; c++)
        {
            for (int h = 0; h < HEIGHT_OUT; h++)
            {
                for (int w = 0; w < WIDTH_OUT; w++)
                {

                    if (w == WIDTH_OUT - 1)
                        std::cout << afterAct[n][c][h][w] << std::endl;
                    else
                        std::cout << afterAct[n][c][h][w] << " ";
                }
            }
            break;
        }
        break;
    }

    std::cout << std::endl;

Skip:
    for (int n = 0; n < BATCH_SIZE; n++)
        {
            for (int c = 0; c < CHANNEL_OUT; c++)
            {
                for (int h = 0; h < HEIGHT_OUT; h++)
                {
                    for (int w = 0; w < WIDTH_OUT; w++)
                    {
                        if(isSkip && (CHANNEL_IN == CHANNEL_OUT) && (HEIGHT_IN == HEIGHT_OUT) && (WIDTH_IN == WIDTH_OUT))
                            Out[n][c][h][w] = afterAct[n][c][h][w] + In[n][c][h][w]; 
                        else 
                            Out[n][c][h][w] = afterAct[n][c][h][w];
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
            break;
        }
        break;
    }

    return 0;
}