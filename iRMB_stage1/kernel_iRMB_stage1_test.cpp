#include "kernel_iRMB_stage1.hpp"
#include <cmath>
#include <math.h>

// TODO: modify parameters
const int BATCH_SIZE = 1;
const int CHANNEL_IN = 24;
const int CHANNEL_OUT = 32;
const int HEIGHT_IN = 8;
const int WIDTH_IN = 8;

const int KERNEL_SIZE = 3;
const int STRIDE = 2;
const int GROUP = 1;

const int PADDING = ceil((float)(KERNEL_SIZE - STRIDE) / 2);
const int HEIGHT_OUT = (HEIGHT_IN - KERNEL_SIZE + 2 * PADDING) / STRIDE + 1;
const int WIDTH_OUT = (WIDTH_IN - KERNEL_SIZE + 2 * PADDING) / STRIDE + 1;

int main()
{

    float in[BATCH_SIZE * CHANNEL_IN * HEIGHT_IN * WIDTH_IN];
    float out[BATCH_SIZE * CHANNEL_OUT * HEIGHT_OUT * WIDTH_OUT];

    std::cout << BATCH_SIZE * CHANNEL_IN * HEIGHT_IN * WIDTH_IN << std::endl;
    std::cout << BATCH_SIZE * CHANNEL_OUT * HEIGHT_OUT * WIDTH_OUT << std::endl;
    // init in
    for (int n = 0; n < BATCH_SIZE; n++)
    {
        for (int c = 0; c < CHANNEL_IN; c++)
        {
            for (int h = 0; h < HEIGHT_IN; h++)
            {
                for (int w = 0; w < WIDTH_IN; w++)
                {
                    in[n * CHANNEL_IN * HEIGHT_IN * WIDTH_IN + c * HEIGHT_IN * WIDTH_IN + h * WIDTH_IN + w] = h + c;
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

    // execution
    kernel_irmb_stage1(in, out);


    // print output
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
