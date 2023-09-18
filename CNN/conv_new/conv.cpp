#include <array>
#include <iostream>

#define BATCH_SIZE 2
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

    float In[BATCH_SIZE][CHANNEL_IN][HEIGHT_IN][WIDTH_IN];
    float Out[BATCH_SIZE][CHANNEL_OUT][HEIGHT_OUT][WIDTH_OUT];
    float Kernel[CHANNEL_OUT][KERNEL_SIZE][KERNEL_SIZE];

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

    //     std::cout << "Reshape into CHANNEL_IN * HEIGHT_IN * WIDTH*IN" << std::endl;
    //     float in_reshape[CHANNEL_IN][HEIGHT_IN][WIDTH_IN];
    // Reshape:
    //     for (int k = 0; k < CHANNEL_IN; k++)
    //     {
    //         for (int i = 0; i < HEIGHT_IN; i++)
    //         {
    //             for (int j = 0; j < WIDTH_IN; j++)
    //             {
    //                 in_reshape[k][i][j] = In[i][j][k];
    //                 // if (j == WIDTH_IN - 1)
    //                 //     std::cout << in_reshape[k][i][j] << std::endl;
    //                 // else
    //                 //     std::cout << in_reshape[k][i][j] << " ";
    //             }
    //         }
    //     }

    std::cout << "In padding: " << std::endl;
Padding:
    if (PADDING > 0)
    {
        const int new_height_in = HEIGHT_IN + 2 * PADDING;
        const int new_width_in = WIDTH_IN + 2 * PADDING;
        float in_pad[BATCH_SIZE][CHANNEL_IN][new_height_in][new_width_in];
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
    }

Initalize_Kernel:

    for (int k = 0; k < CHANNEL_OUT; k++)
    {
        for (int i = 0; i < KERNEL_SIZE; i++)
        {
            for (int j = 0; j < KERNEL_SIZE; j++)
            {

                Kernel[k][i][j] = j + k;
            }
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

                    Out[n][c][h][w] = 0;
                }
            }
        }
    }

// 該版本為unroll和pipeline的4D版本
Convolution:
Batch:
    for (int batch = 0; batch < BATCH_SIZE; batch++)
    {
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
                                Out[batch][ch_out][row][col] += In[batch][ch_in][row * STRIDE + kernel_row][col * STRIDE + kernel_col] * Kernel[ch_out][kernel_row][kernel_col];
                            }
                        }
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

    // In pooling, in/out channel should be same
    float pooling[BATCH_SIZE][CHANNEL_IN][HEIGHT_OUT][WIDTH_OUT];

    int Max = 0;

Max_Pooling:
    for (int batch = 0; batch < BATCH_SIZE; batch++)
    {
        for (int ch_in = 0; ch_in < CHANNEL_IN; ch_in++)
        {
            for (int row = 0; row < HEIGHT_OUT; row++)
            {
                for (int col = 0; col < WIDTH_OUT; col++)
                {
                    Max = 0;
                    for (int kernel_row = 0; kernel_row < KERNEL_SIZE; kernel_row++)
                    {
                        for (int kernel_col = 0; kernel_col < KERNEL_SIZE; kernel_col++)
                        {
                            if (Max < In[batch][ch_in][row * STRIDE + kernel_row][col * STRIDE + kernel_col])
                                Max = In[batch][ch_in][row * STRIDE + kernel_row][col * STRIDE + kernel_col];
                        }
                    }
                    pooling[batch][ch_in][row][col] = Max;
                    // if (col == WIDTH_OUT - 1)
                    //     std::cout << pooling[batch][ch_in][row][col] << std::endl;
                    // else
                    //     std::cout << pooling[batch][ch_in][row][col] << " ";
                }
            }
        }
    }

    int sum = 0;

AVG_pooling:
    for (int batch = 0; batch < BATCH_SIZE; batch++)
    {
        for (int ch_in = 0; ch_in < CHANNEL_IN; ch_in++)
        {
            for (int row = 0; row < HEIGHT_OUT; row++)
            {
                for (int col = 0; col < WIDTH_OUT; col++)
                {
                    sum = 0;
                    for (int kernel_row = 0; kernel_row < KERNEL_SIZE; kernel_row++)
                    {
                        for (int kernel_col = 0; kernel_col < KERNEL_SIZE; kernel_col++)
                        {
                                sum += In[batch][ch_in][row * STRIDE + kernel_row][col * STRIDE + kernel_col];
                        }
                    }
                    pooling[batch][ch_in][row][col] = sum / KERNEL_SIZE / KERNEL_SIZE;
                    // if (col == WIDTH_OUT - 1)
                    //     std::cout << pooling[batch][ch_in][row][col] << std::endl;
                    // else
                    //     std::cout << pooling[batch][ch_in][row][col] << " ";
                }
            }
        }
    }

    return 0;
}