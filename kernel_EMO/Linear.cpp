#include "kernel_EMO.hpp"
#include <stdint.h>
using namespace std;

void Linear(float* x, float* x_reduce, float* weight, float* bias, int* X_num, float* y){
    int N = X_num[0];
    int C_in = X_num[1];
    int H = X_num[2];
    int W = X_num[3];
    int C_out = X_num[4];

    for (int n = 0; n < N; n++)
    {
        for (int c = 0; c < C_in; c++)
        {
            float sum = 0;
            for (int h = 0; h < H; h++)
            {
                for (int w = 0; w < W; w++)
                {
                    sum += x[n * C_in * H * W + c * H * W + h * W + w];
                }
            }
            x_reduce[n * C_in + c] = sum / (H * W);
        }
    }

    for (int n = 0; n < N; n++)
    {
        for (int c_out = 0; c_out < C_out; c_out++)
        {
            float sum = 0;
            for (int c_in = 0; c_in < C_in; c_in++)
            {
                sum += x_reduce[n * C_in + c_in] * weight[c_out * C_in + c_in];
            }
            y[n * C_out + c_out] = sum + bias[c_out];
        }
    }

    return;
}

