#include "kernel_stage0.hpp"
#include <iostream>
#include <cmath>
using namespace std;


void BatchNorm(float* X_data, float* Y_data, int* X_num, float* mean, float* var, float* gamma, float* beta) {
    //get X(input) size
    int N = X_num[0];
    int C = X_num[1];
    int H = X_num[2];
    int W = X_num[3];

    /*
    for(int_t n = 0; n < N; n++)
		for(int_t c = 0; c < C; c++)
			for(int_t d = 0; d < D; d++)
				for(int_t h = 0; h < H; h++)
					for(int_t w = 0; w < W; w++){
						int_t tmp_X = (int_t)roundf((((ftype((int_t)X_data[n*C*D*H*W + c*D*H*W + d*H*W + h*W + w]-zp_in)*scale_in - mu_[c]) / sqrtf(var_[c]+0.00001)) * r[c] + b[c])/scale_out) + zp_out;
						Y_data[n*C*D*H*W + c*D*H*W + d*H*W + h*W + w] = (tmp_X > 255) ? 255 : (tmp_X < 0) ? 0 : (dtype)tmp_X;
					}
    */
   for (int n = 0; n < N; n++) {
        for (int c = 0; c < C; c++) {
            for (int h = 0; h < H; h++) {
                for (int w = 0; w < W; w++) {
                    Y_data[n*C*H*W + c*H*W + h*W + w] = (X_data[n*C*H*W + c*H*W + h*W + w] - mean[c]) / sqrt(var[c] + 1e-5) * gamma[c] + beta[c];
                }
            }
        }
   }
}

