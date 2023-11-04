#include <stdint.h>
#include "kernel_EMO.hpp"
using namespace std;

void LayerNorm(float* X_data, float* Y_data, int* X_num, float* mean_buf, float* var_buf, float* weight, float* bias) {
    //get X(input) size
    int N = X_num[0]; //1
    int C = X_num[1];
    int H = X_num[2];
    int W = X_num[3];

    int pos = 0;
    float sum = 0;
    float sum2 = 0;
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
                    sum += value;
                    sum2 += value * value;
                }
                mean = sum / C;
                mean_buf[pos] = mean;
                var_buf[pos] = sum2 / C - (mean * mean);
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

