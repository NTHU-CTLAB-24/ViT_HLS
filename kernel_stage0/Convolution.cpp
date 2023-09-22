#include "kernel_stage0.hpp"
#include <iostream>
#include <cmath>
using namespace std;


void Convolution(float* X_data, int* X_num, float* Y_data, int* Y_num,  float* filter, int* filter_num, float* bias) {
    //get X(input) size
    int XN = X_num[0];
    int XC = X_num[1];
    int XH = X_num[2];
    int XW = X_num[3];

    //get filter size
    int KC = filter_num[0];
    int KD = filter_num[1];
    int KH = filter_num[2];
    int KW = filter_num[3];
    int padding = filter_num[4];
    int stride = filter_num[5];
    int isBias = filter_num[6];

    //get Y(output) size
    int YN = Y_num[0];
    int YC = Y_num[1];
    int YH = Y_num[2];
    int YW = Y_num[3];

    for (int yn = 0; yn < YN; yn++) {
        for (int yh = 0; yh < YH; yh++) {
            for (int yw = 0; yw < YW++) {
                for (int kh = 0; kh < KH; kh++) {
                    for (int kw = 0; kw < KW; kw++) {
                        for (int yc = 0; yc < YC; yc++) {
                            int x_pos, k_pos, y_pos;
                            for (int xc = 0; xc < XC; xc++) {
                                x_pos = yn*XC*XH*XW + xc*XH*XW + (yh*stride+kh)*XW + (yw*stride+kw);
                                k_pos = yc*KD*KH*KW + xc*KW*KW + kh*KW + kw;
                                y_pos = yn*YC*YH*YW + yc*YH*YW + yh*YW + yw;
                                Y_data[y_pos] += in_pad[x_pos] * filter[k_pos];
                            }
                            if (isBias) Y_data[y_pos] += bias[yc];
                        }
                    }
                }
            }
        }
    }
}

