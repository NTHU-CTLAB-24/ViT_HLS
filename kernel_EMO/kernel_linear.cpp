// Includes
#include <hls_math.h>
#include <hls_stream.h>
#include <stdint.h>
#include "kernel_EMO.hpp"

void LayerNorm_Linear(float* X_data, float* Y_data, int* X_num, float* mean_buf, float* var_buf, float* weight, float* bias) {
    int N = X_num[0]; 
    int C = X_num[1];
    int H = X_num[2];
    int W = X_num[3];

    int pos = 0;
    float sum = 0;
    float sum2 = 0;
    float diff = 0;
    float value = 0;
    float mean = 0;
    for (int n = 0; n < N; n++) {
        for (int h = 0; h < H; h++) {
            for (int w = 0; w < W; w++) {
                pos = h * W + w;
                sum = 0;
                sum2 = 0;
                for (int c = 0; c < C; c++) {
                    value = X_data[n*C*H*W + c*H*W + pos];
                    sum += value/ C;
                }
                mean = sum ;
                for (int c = 0; c < C; c++) {
                    value = X_data[n*C*H*W + c*H*W + pos];
                    diff = value - mean;
                    sum2 += diff / C * diff ;
                }
                mean_buf[pos] = mean;
                var_buf[pos] = sum2 ;
            }
        }
    }
    
    for (int n = 0; n < N; n++) {
        for (int h = 0; h < H; h++) {
            for (int w = 0; w < W; w++) {
                pos = h * W + w;
                for (int c = 0; c < C; c++) {
                     Y_data[n*C*H*W + c*H*W + pos] = (X_data[n*C*H*W + c*H*W + pos] - mean_buf[pos]) / sqrt(var_buf[pos] + 1e-6) * weight[c] + bias[c];
                }
            }
        }
   }
}

extern "C"
{
    void kernel_linear(float* X_data, float* Y_linear_norm, float* linear_norm_mean, float* linear_norm_var, float* linear_norm_weight, float* linear_norm_bias,
                       float* Y_linear_reduce, float* linear_weight, float* linear_bias, float* Y_out)
    {
        int linear_norm_num[4] = {1, 168, 7, 7};
        int linear_num[5] = {1, 168, 7, 7, 1000};

        // LayerNorm_Linear(X_data, Y_linear_norm, linear_norm_num, linear_norm_mean, linear_norm_var, linear_norm_weight, linear_norm_bias);
        LayerNorm(X_data, Y_linear_norm, linear_norm_num, linear_norm_mean, linear_norm_var, linear_norm_weight, linear_norm_bias);
        Linear(Y_linear_norm, Y_linear_reduce, linear_weight, linear_bias, linear_num, Y_out);
    }
}