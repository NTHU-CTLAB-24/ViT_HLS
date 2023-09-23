#include "kernel_stage0.hpp"
#include <iostream>
#include <cmath>
using namespace std;

void Compute_mean(float* X_data, int* X_num, float* Y_data) {
    int XN = X_num[0];
    int XC = X_num[1];
    int XH = X_num[2];
    int XW = X_num[3];

    int total_num = XH * XW;
    for (int n = 0; n < XN; n++) {
        for (int c = 0; c < XC; c++) {
            float temp = 0;
            for (int h = 0; h < XH; h++) {
                for (int w = 0; w < XW; w++) {
                    temp += X_data[n*XC*XH*XW + c*XH*XW + h*XW + w];
                }
            }
            Y_data[n*XC + c] = temp / total_num;
        }
    }
}
void Compute_mul(float* X_data, float* feature, float* Y_data, int* X_num) {
    int XN = X_num[0];
    int XC = X_num[1];
    int XH = X_num[2];
    int XW = X_num[3];

    for (int h = 0; h < XH; h++) {
        for (int w = 0; w < XW; w++) {
            for (int n = 0; n < XN; n++) {
                for (int c = 0; c < XC; c++) {
                    int pos = n*XC*XH*XW + c*XH*XW + h*XW + w;
                    float val = feature[n*XC + c];
                    Y_data[pos] = X_data[pos] * val;
                }
            }
        }
    }
}


//X_num = {1, 24, 112, 112}
//reduce_filter_num = {24, 24, 1, 1, 0, 1, 1}, padding=0, stride=1, isBias=1
void SE(float* X_data, float* Y_data, int* X_num, float* X_mean, float* X_reduce, float* X_relu, float* X_expand, float* X_sigmoid, float* reduce_filter, float* reduce_bias, float* expand_filter, float* expand_bias) {
    float se_ratio = 1;
    Compute_mean(X_data, X_num, X_mean);
    int X_mean_num[4] = {X_num[0], X_num[1], 1, 1};
    int XC = X_num[1];
    int SEC = int(XC * se_ratio);
    int reduce_filter_num[7] = {SEC, XC, 1, 1, 0, 1, 1};
    int expand_filter_num[7] = {XC, SEC, 1, 1, 0, 1, 1};

    int X_reduce_num[4];
    X_reduce_num[0] = X_num[0];
    X_reduce_num[1] = reduce_filter_num[0];
    X_reduce_num[2] = (X_mean_num[2] - reduce_filter_num[2]) + 1;
    X_reduce_num[3] = (X_mean_num[3] - reduce_filter_num[3]) + 1;

    int X_expand_num[4];
    X_expand_num[0] = X_num[0];
    X_expand_num[1] = expand_filter_num[0];
    X_expand_num[2] = (X_reduce_num[2] - expand_filter_num[2]) + 1;
    X_expand_num[3] = (X_reduce_num[3] - expand_filter_num[3]) + 1;

    //reduce convolution
    Convolution(X_mean, X_mean_num, X_reduce, X_reduce_num, reduce_filter, reduce_filter_num, reduce_bias);
    ReLU(X_reduce, X_relu, X_reduce_num, 0);
    //expand convolution
    Convolution(X_relu, X_reduce_num, X_expand, X_expand_num, expand_filter, expand_filter_num, expand_bias);
    Sigmoid(X_expand, X_sigmoid, X_expand_num);
    Compute_mul(X_data, X_sigmoid, Y_data, X_num);
}
