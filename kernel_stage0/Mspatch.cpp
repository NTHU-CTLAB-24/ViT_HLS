#include "kernel_stage0.hpp"
#include <iostream>
#include <cmath>
using namespace std;

//X_num = {1, 3, 112, 112}
//filter_num = {24, 3, 3, 3, 1, 2, 0}, padding=1, stride=2, isBias=0

void Mspatch(float* X_data, int* X_num, float* X_pad, float* X_conv, float* Y_data, int* Y_num, float* filter, int* filter_num, float* bias, float* mean, float* var, float* gamma, float* beta) {

    int padding = filter_num[4];
    int stride = filter_num[5];

    Padding(X_data, X_pad, X_num, padding);

    int x_pad_num[4];
    x_pad_num[0] = X_num[0];
    x_pad_num[1] = X_num[1];
    x_pad_num[2] = X_num[2] + 2*padding;
    x_pad_num[3] = X_num[3] + 2*padding;

    Convolution(X_pad, x_pad_num, X_conv, Y_num, filter, filter_num, bias);
    BatchNorm(X_conv, Y_data, Y_num, mean, var, gamma, beta);
}