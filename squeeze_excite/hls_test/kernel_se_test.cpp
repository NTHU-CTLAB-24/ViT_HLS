#include "kernel_se.hpp"
const int BATCH_SIZE = 1;
const int IMAGE_H = 112;
const int IMAGE_W = 112;
const float RATIO = 1;
const int HEIGHT_IN = 1;
const int WIDTH_IN = 1;
const int CHANNEL_IN = 24;
const int CHANNEL_OUT = int(CHANNEL_IN * RATIO); // REDUCE_CHS
const int KERNEL_SIZE = 1;
const int PADDING = 0;
const int STRIDE = 1;
const int HEIGHT_OUT = (HEIGHT_IN - KERNEL_SIZE + 2 * PADDING) / STRIDE + 1;
const int WIDTH_OUT = (WIDTH_IN - KERNEL_SIZE + 2 * PADDING) / STRIDE + 1;

int main()
{

    float in1[BATCH_SIZE * CHANNEL_IN * IMAGE_H * IMAGE_W];
    float out[BATCH_SIZE * CHANNEL_IN];

    // init image
    for (int b = 0; b < BATCH_SIZE; b++)
    {
        for (int c = 0; c < CHANNEL_IN; c++)
        {
            for (int i = 0; i < IMAGE_H; i++)
            {
                for (int j = 0; j < IMAGE_W; j++)
                {
                    in1[b * CHANNEL_IN * IMAGE_H * IMAGE_W + c * IMAGE_H * IMAGE_W + i * IMAGE_W + j] = (c + i + j) % 256;
                }
            }
        }
    }

    kernel_se(in1, out);

    std::cout << "result" << std::endl;
    for (int i = 0; i < IMAGE_H; i++)
    {
        if (i == 8)
            break;
        for (int j = 0; j < IMAGE_W; j++)
        {
            if (j == 8)
                break;
            std::cout << out[i * IMAGE_W + j] << " ";
        }
        
        std::cout << std::endl;
    }
    std::cout << std::endl;

    return EXIT_SUCCESS;
}
