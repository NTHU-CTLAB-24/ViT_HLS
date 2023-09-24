#include "DW_conv.hpp"
#include <cmath>
#include <math.h>

// TODO: modify parameters
const int BATCH_SIZE = 2;
const int CHANNEL_IN = 24;
const int CHANNEL_OUT = 24;
const int HEIGHT_IN = 8;
const int WIDTH_IN = 8;

const int KERNEL_SIZE = 3;
const int isConvBias = 1;
const int STRIDE = 1;
const int PADDING = ceil((float)(KERNEL_SIZE - STRIDE) / 2);
// const int PADDING = 0;
const int GROUP = 24;
const int KERNEL_CHANNEL = CHANNEL_IN / GROUP;

const int HEIGHT_OUT = (HEIGHT_IN - KERNEL_SIZE + 2 * PADDING) / STRIDE + 1;
const int WIDTH_OUT = (WIDTH_IN - KERNEL_SIZE + 2 * PADDING) / STRIDE + 1;

int main()
{

    float in1[BATCH_SIZE * CHANNEL_IN * HEIGHT_IN * WIDTH_IN];
    float out[BATCH_SIZE * CHANNEL_OUT * HEIGHT_OUT * WIDTH_OUT];
    float kernel[CHANNEL_OUT * KERNEL_CHANNEL * KERNEL_SIZE * KERNEL_SIZE];
    float bias[CHANNEL_OUT];

    int shape_para[7] = {BATCH_SIZE, CHANNEL_IN, HEIGHT_IN, WIDTH_IN, CHANNEL_OUT, HEIGHT_OUT, WIDTH_OUT};
    int conv_para[6] = {KERNEL_SIZE, isConvBias, STRIDE, PADDING, GROUP, KERNEL_CHANNEL};

    // init in
    for (int n = 0; n < BATCH_SIZE; n++)
    {
        for (int c = 0; c < CHANNEL_IN; c++)
        {
            for (int h = 0; h < HEIGHT_IN; h++)
            {
                for (int w = 0; w < WIDTH_IN; w++)
                {
                    in1[n * CHANNEL_IN * HEIGHT_IN * WIDTH_IN + c * HEIGHT_IN * WIDTH_IN + h * WIDTH_IN + w] = h + c;
                }
            }
        }
    }

    // init kernel and bias
    for (int k = 0; k < CHANNEL_OUT; k++)
    {
        bias[k] = k + 0.01;
        for (int l = 0; l < KERNEL_CHANNEL; l++)
        {
            for (int i = 0; i < KERNEL_SIZE; i++)
            {
                for (int j = 0; j < KERNEL_SIZE; j++)
                {
                    kernel[k * KERNEL_CHANNEL * KERNEL_SIZE * KERNEL_SIZE + l * KERNEL_SIZE * KERNEL_SIZE + i * KERNEL_SIZE + j] = 0.002;
                }
            }
        }
    }

    // init out
    for (int n = 0; n < BATCH_SIZE; n++)
    {
        for (int c = 0; c < CHANNEL_OUT; c++)
        {
            for (int h = 0; h < HEIGHT_OUT; h++)
            {
                for (int w = 0; w < WIDTH_OUT; w++)
                {
                    out[n * CHANNEL_OUT * HEIGHT_OUT * WIDTH_OUT + c * HEIGHT_OUT * WIDTH_OUT + h * WIDTH_OUT + w] = 0;
                }
            }
        }
    }
    std::cout << PADDING << std::endl;
    std::cout << BATCH_SIZE * CHANNEL_IN * HEIGHT_IN * WIDTH_IN << std::endl;
    std::cout << BATCH_SIZE * CHANNEL_OUT * HEIGHT_OUT * WIDTH_OUT << std::endl;
    

    DW_conv(in1, kernel, bias, shape_para, conv_para, out);
    for (int n = 0; n < BATCH_SIZE; n++)
    {
        for (int c = 0; c < CHANNEL_OUT; c++)
        {
            for (int h = 0; h < HEIGHT_OUT; h++)
            {
                for (int w = 0; w < WIDTH_OUT; w++)
                {
                    if (w == WIDTH_OUT - 1)
                        std::cout << out[n * CHANNEL_OUT * HEIGHT_OUT * WIDTH_OUT + c * HEIGHT_OUT * WIDTH_OUT + h * WIDTH_OUT + w] << std::endl;
                    else
                        std::cout << out[n * CHANNEL_OUT * HEIGHT_OUT * WIDTH_OUT + c * HEIGHT_OUT * WIDTH_OUT + h * WIDTH_OUT + w] << " ";
                
                }
            }
            break;
        }
        break;
    }

    return EXIT_SUCCESS;
}
