#include "kernel_stage0.hpp"
#include<iostream>
#include <hls_math.h>

using namespace std;

void Sigmoid(float* X_data, float* Y_data, int* X_num){
    int XN = X_num[0];
    int XC = X_num[1];
    int XH = X_num[2];
    int XW = X_num[3];

    for (int n = 0; n < XN; n++) {
        for (int c = 0; c < XC; c++) {
            for (int h = 0; h < XH; h++) {
                for (int w = 0; w < XW; w++) {
                    int y_pos = n*XC*XH*XW + c*XH*XW + h*XW + w;
                    float temp = X_data[n*XC*XH*XW + c*XH*XW + h*XW + w];
                    Y_data[y_pos] = 1 / (1 + exp(-temp));
                }
            }
        }
    }
}
