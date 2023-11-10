#include "kernel_EMO.hpp"
#include <stdint.h>
using namespace std;

void Compute_skip(float *in1, float *in2, float *out, int *X_num)
{
    int BATCH_SIZE = X_num[0];
    int CHANNEL_OUT = X_num[1];
    int HEIGHT_OUT = X_num[2];
    int WIDTH_OUT = X_num[3];

    int pos;
Skip:
    for (int n = 0; n < BATCH_SIZE; n++)
    {
#pragma HLS LOOP_TRIPCOUNT min = 1 max = 1
        for (int c = 0; c < CHANNEL_OUT; c++)
        {
#pragma HLS LOOP_TRIPCOUNT min = 32 max = 588
            for (int h = 0; h < HEIGHT_OUT; h++)
            {
#pragma HLS LOOP_TRIPCOUNT min = 7 max = 56
                for (int w = 0; w < WIDTH_OUT; w++)
                {
#pragma HLS LOOP_TRIPCOUNT min = 7 max = 56
                    pos = n * CHANNEL_OUT * HEIGHT_OUT * WIDTH_OUT + c * HEIGHT_OUT * WIDTH_OUT + h * WIDTH_OUT + w;
                    out[pos] = in1[pos] + in2[pos];
                }
            }
        }
    }
}