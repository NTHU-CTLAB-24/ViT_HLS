#include <array>
#include <iostream>

#define CHANNEL_IN 3
#define CHANNEL_OUT 2
#define HEIGHT_IN 16
#define WIDTH_IN 16

#define KERNEL_SIZE 3
#define PADDING 0
#define STRIDE 1

int main()
{
    const int HEIGHT_OUT = (HEIGHT_IN - KERNEL_SIZE + 2 * PADDING) / STRIDE + 1;
    const int WIDTH_OUT = (WIDTH_IN - KERNEL_SIZE + 2 * PADDING) / STRIDE + 1;
    std::cout << "Check output size: " << HEIGHT_OUT << " * " << WIDTH_OUT << std::endl;

    float In[HEIGHT_IN][WIDTH_IN][CHANNEL_IN];
    float Out[HEIGHT_OUT][WIDTH_OUT][CHANNEL_OUT];
    float Kernel[KERNEL_SIZE][KERNEL_SIZE][CHANNEL_OUT];

Initalize_In:
    for (int i = 0; i < HEIGHT_IN; i++)
    {
        for (int j = 0; j < WIDTH_IN; j++)
        {
            for (int k = 0; k < CHANNEL_IN; k++)
            {
                In[i][j][k] = i;
                // if (k == CHANNEL_IN - 1)
                //     std::cout << In[i][j][k] << std::endl;
                // else
                //     std::cout << In[i][j][k] << " ";
            }
        }
    }

    std::cout << "Reshape into CHANNEL_IN * HEIGHT_IN * WIDTH*IN" << std::endl;
    float in_reshape[CHANNEL_IN][HEIGHT_IN][WIDTH_IN];
Reshape:
    for (int k = 0; k < CHANNEL_IN; k++)
    {
        for (int i = 0; i < HEIGHT_IN; i++)
        {
            for (int j = 0; j < WIDTH_IN; j++)
            {
                in_reshape[k][i][j] = In[i][j][k];
                // if (j == WIDTH_IN - 1)
                //     std::cout << in_reshape[k][i][j] << std::endl;
                // else
                //     std::cout << in_reshape[k][i][j] << " ";
            }
        }
    }

    std::cout << "In padding: " << std::endl;
Padding:
    if (PADDING > 0)
    {
        const int new_height_in = HEIGHT_IN + 2 * PADDING;
        const int new_width_in = WIDTH_IN + 2 * PADDING;
        float in_pad[new_height_in][new_width_in][CHANNEL_IN];
        for (int i = 0; i < new_height_in; i++)
        {
            for (int j = 0; j < new_width_in; j++)
            {
                for (int k = 0; k < CHANNEL_IN; k++)
                {
                    if (i < PADDING || i >= HEIGHT_IN + PADDING || j < PADDING || j >= WIDTH_IN + PADDING)
                        in_pad[i][j][k] = 0;
                    else
                        in_pad[i][j][k] = In[i - PADDING][j - PADDING][k];
                    // if (j == new_width_in - 1)
                    //     std::cout << in_pad[i][j][k] << std::endl;
                    // else
                    //     std::cout << in_pad[i][j][k] << " ";
                }
            }
        }
    }

Initalize_Kernel:

    for (int i = 0; i < KERNEL_SIZE; i++)
    {
        for (int j = 0; j < KERNEL_SIZE; j++)
        {
            for (int k = 0; k < CHANNEL_OUT; k++)
            {
                Kernel[i][j][k] = j;
            }
        }
    }

Intialize_Out:

    for (int i = 0; i < HEIGHT_OUT; i++)
    {
        for (int j = 0; j < WIDTH_OUT; j++)
        {
            for (int k = 0; k < CHANNEL_OUT; k++)
            {
                Out[i][j][k] = 0;
            }
        }
    }

// 該版本為unroll和pipeline的3D版本
Convolution:
Kernel_Row:
    for (int kernel_row = 0; kernel_row < KERNEL_SIZE; kernel_row++)
    {
    Kernel_Col:
        for (int kernel_col = 0; kernel_col < KERNEL_SIZE; kernel_col++)
        {
        Out_Row:
            for (int row = 0; row < HEIGHT_OUT; row++)
            {
            Out_Column:
                for (int col = 0; col < WIDTH_OUT; col++)
                {
#pragma HLS PIPELINE
                Out_channel:
                    for (int ch_out = 0; ch_out < CHANNEL_OUT; ch_out++)
                    {
                    In_channel:
                        for (int ch_in = 0; ch_in < CHANNEL_IN; ch_in++)
                        {
                            Out[row][col][ch_out] += In[row * STRIDE + kernel_row][col * STRIDE + kernel_col][ch_in] * Kernel[kernel_row][kernel_col][ch_out];
                        }
                    }
                }
            }
        }
    }

    std::cout << "Output array: " << std::endl;

    Output:
        for (int i = 0; i < HEIGHT_OUT; i++)
        {
            for (int j = 0; j < WIDTH_OUT; j++)
            {
                for (int k = 0; k < CHANNEL_OUT; k++)
                {
                    if (k == CHANNEL_OUT - 1)
                        std::cout << Out[i][j][k] << std::endl;
                    else
                        std::cout << Out[i][j][k] << " ";
                }
            }
        }

    // In pooling, in/out channel should be same
    float pooling[HEIGHT_OUT][WIDTH_OUT][CHANNEL_IN];

    int Max = 0;

Max_Pooling:
    for (int row = 0; row < HEIGHT_OUT; row++)
    {
        for (int col = 0; col < WIDTH_OUT; col++)
        {
            for (int ch_in = 0; ch_in < CHANNEL_IN; ch_in++)
            {
                Max = 0;
                for (int kernel_row = 0; kernel_row < KERNEL_SIZE; kernel_row++)
                {
                    for (int kernel_col = 0; kernel_col < KERNEL_SIZE; kernel_col++)
                    {
                        if (Max < In[row * STRIDE + kernel_row][col * STRIDE + kernel_col][ch_in])
                            Max = In[row * STRIDE + kernel_row][col * STRIDE + kernel_col][ch_in];
                    }
                }
                pooling[row][col][ch_in] = Max;
                // if (ch_in == CHANNEL_IN - 1)
                //     std::cout << pooling[row][col][ch_in] << std::endl;
                // else
                //     std::cout << pooling[row][col][ch_in] << " ";
            }
        }
    }

    int sum = 0;

AVG_pooling:
    for (int row = 0; row < HEIGHT_OUT; row++)
    {
        for (int col = 0; col < WIDTH_OUT; col++)
        {
            for (int ch_in = 0; ch_in < CHANNEL_IN; ch_in++)
            {
                sum = 0;
                for (int kernel_row = 0; kernel_row < KERNEL_SIZE; kernel_row++)
                {
                    for (int kernel_col = 0; kernel_col < KERNEL_SIZE; kernel_col++)
                    {
                        sum += In[row * STRIDE + kernel_row][col * STRIDE + kernel_col][ch_in];
                    }
                }
                pooling[row][col][ch_in] = sum / KERNEL_SIZE / KERNEL_SIZE;
                // if (ch_in == CHANNEL_IN - 1)
                //     std::cout << pooling[row][col][ch_in] << std::endl;
                // else
                //     std::cout << pooling[row][col][ch_in] << " ";
            }
        }
    }
}