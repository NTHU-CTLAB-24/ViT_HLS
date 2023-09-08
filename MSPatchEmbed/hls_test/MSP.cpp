#include <array>
#include <iostream>
#include <cmath>
#define BATCH_SIZE 1
#define CHANNEL_IN 3
#define CHANNEL_OUT 16
#define HEIGHT_IN 14
#define WIDTH_IN 14

#define KERNEL_SIZE 3
#define PADDING 1
#define STRIDE 2

int main() {
    const int HEIGHT_OUT = (HEIGHT_IN - KERNEL_SIZE + 2 * PADDING) / STRIDE + 1;
    const int WIDTH_OUT = (WIDTH_IN - KERNEL_SIZE + 2 * PADDING) / STRIDE + 1;
    std::cout << "Check output size: " << HEIGHT_OUT << " * " << WIDTH_OUT
        << std::endl;

    float In[BATCH_SIZE][CHANNEL_IN][HEIGHT_IN][WIDTH_IN];
    float Out[BATCH_SIZE][CHANNEL_OUT][HEIGHT_OUT][WIDTH_OUT];
    float Kernel[CHANNEL_OUT][KERNEL_SIZE][KERNEL_SIZE];

    //init image data
    for (int b = 0; b < BATCH_SIZE; b++) {
        for (int c = 0; c < CHANNEL_IN; c++) {
            for (int i = 0; i < HEIGHT_IN; i++) {
                for (int j = 0; j < WIDTH_IN; j++) {
                    In[b][c][i][j] = float((b + c + i + j) % 256);
                }
            }
        }
    }
    //init kernel
    for (int c = 0; c < CHANNEL_OUT; c++) {
        for (int i = 0; i < KERNEL_SIZE; i++) {
            for (int j = 0; j < KERNEL_SIZE; j++) {
                Kernel[c][i][j] = 0.1;
            }
        }
    }

    //padding

    const int new_height_in = HEIGHT_IN + 2 * PADDING;
    const int new_width_in = WIDTH_IN + 2 * PADDING;
    float in_pad[BATCH_SIZE][CHANNEL_IN][new_height_in][new_width_in];
    for (int b = 0; b < BATCH_SIZE; b++) {
        for (int c = 0; c < CHANNEL_IN; c++) {
            for (int i = 0; i < new_height_in; i++) {
                for (int j = 0; j < new_width_in; j++) {
                    if (i < PADDING || i >= HEIGHT_IN + PADDING || j < PADDING ||
                        j >= WIDTH_IN + PADDING)
                        in_pad[b][c][i][j] = 0;
                    else
                        in_pad[b][c][i][j] = In[b][c][i - PADDING][j - PADDING];
                }
            }
        }
    }

    //convolution

    for (int batch = 0; batch < BATCH_SIZE; batch++) {
        for (int kernel_row = 0; kernel_row < KERNEL_SIZE; kernel_row++) {
            for (int kernel_col = 0; kernel_col < KERNEL_SIZE; kernel_col++) {
                for (int row = 0; row < HEIGHT_OUT; row++) {
                    for (int col = 0; col < WIDTH_OUT; col++) {
                        for (int ch_out = 0; ch_out < CHANNEL_OUT; ch_out++) {
                            for (int ch_in = 0; ch_in < CHANNEL_IN; ch_in++) {
                                Out[batch][ch_out][row][col] += in_pad[batch][ch_in][row * STRIDE + kernel_row][col * STRIDE + kernel_col] * Kernel[ch_out][kernel_row][kernel_col];
                            }
                        }
                    }
                }
            }
        }
    }

    //check conv
    //print [0, 0, :, :]
    std::cout << "after conv" << std::endl;
    for (int i=0; i<HEIGHT_OUT; i++) {
        for (int j=0; j<WIDTH_OUT; j++) {
            std::cout << Out[0][0][i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

    //BatchNorm
    float running_mean[CHANNEL_OUT];
    float running_var[CHANNEL_OUT];
    float gamma = 0.5;
    float beta = 0.2;

    for (int c=0; c<CHANNEL_OUT; c++) {
        running_mean[c] = 8;
        running_var[c] = 21.5;
    }

    for (int b = 0; b < BATCH_SIZE; b++) {
        for (int c = 0; c < CHANNEL_OUT; c++) {
            for (int i = 0; i < HEIGHT_OUT; i++) {
                for (int j = 0; j < WIDTH_OUT; j++) {
                    Out[b][c][i][j] = (Out[b][c][i][j] - running_mean[c]) / sqrt(running_var[c] + 1e-5) * gamma + beta;
                }
            }
        }
    }



    //print result[0, 0, :, :]
    for (int b = 0; b < 1; b++) {
        for (int c = 0; c < 1; c++) {
            for (int i = 0; i < HEIGHT_OUT; i++) {
                for (int j = 0; j < WIDTH_OUT; j++) {
                    std::cout << Out[b][c][i][j] << " ";
                }
                std::cout << std::endl;
            }
        }
    }
}