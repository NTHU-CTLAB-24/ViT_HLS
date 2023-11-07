#include "kernel_EMO.hpp"
#include <stdint.h>
using namespace std;

void BatchNorm(float *X_data, float *Y_data, int *X_num, float *running_mean, float *running_var, float *gamma, float *beta)
{
    // get X(input) size
    int N = X_num[0];
    int C = X_num[1];
    int H = X_num[2];
    int W = X_num[3];

    for (int n = 0; n < N; n++)
    {
        for (int c = 0; c < C; c++)
        {
            for (int h = 0; h < H; h++)
            {
                for (int w = 0; w < W; w++)
                {
                    Y_data[n * C * H * W + c * H * W + h * W + w] = (X_data[n * C * H * W + c * H * W + h * W + w] - running_mean[c]) / sqrt(running_var[c] + 1e-6) * gamma[c] + beta[c];
                }
            }
        }
    }
}