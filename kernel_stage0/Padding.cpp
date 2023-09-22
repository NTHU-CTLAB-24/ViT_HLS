#include "kernel_stage0.hpp"
#include <iostream>
#include <cmath>
using namespace std;


void Padding(float* X_data, float* Y_data, int* X_num, int padding) {
    //get X(input) size
    int XN = X_num[0];
    int XC = X_num[1];
    int XH = X_num[2];
    int XW = X_num[3];

    int YH = XH + 2*padding;
    int YW = XW + 2*padding;
   
   for (int n = 0; n < XN; n++) {
        for (int c = 0; c < XC; c++) {
            for (int h = 0; h < YH; h++) {
                for (int w = 0; w < YW; w++) {
                    int y_pos = n*XC*YH*YW + c*YH*YW + h*YW + w;
                    if (h<padding || h>=XH+padding || w<padding || w>=XW+padding) Y_data[y_pos] = 0;
                    else Y_data[y_pos] = X_data[n*XC*XH*XW + c*XH*XW + (h-padding)*XW + w-padding];
                }
            }
        }
   }
}

