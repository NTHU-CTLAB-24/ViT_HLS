#include "linear.hpp"
#include <stdint.h>
using namespace std;


void linear(float* x, float* x_reduce, float* weight, float* bias, float* y){
    #pragma HLS INTERFACE m_axi port = x bundle = gmem0 depth = 8232
    #pragma HLS INTERFACE m_axi port = x_reduce bundle = gmem1 depth = 168
    #pragma HLS INTERFACE m_axi port = weight bundle = gmem0 depth = 168000
    #pragma HLS INTERFACE m_axi port = bias bundle = gmem0 depth = 1000
    #pragma HLS INTERFACE m_axi port = y bundle = gmem2 depth = 1000

    const int N = 1;
    const int C_in = 168;
    const int H = 7;
    const int W = 7;
    const int C_out = 1000;

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

