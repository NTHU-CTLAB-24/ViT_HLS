#include <stdint.h>
#include "kernel_stage1_2.hpp"
using namespace std;

void SiLU(float* X_data, float* Y_data, int* X_num){
	// #pragma HLS INTERFACE mode=ap_fifo port=X_data
	// #pragma HLS INTERFACE mode=ap_fifo port=Y_data
    SiLU:
	for(int i = X_num[0] * X_num[1] * X_num[2] * X_num[3] - 1; i >= 0; i--){ // traverse all data
        // #pragma HLS UNROLL
        float x = X_data[i];
        Y_data[i] = x * (1 / (1 + exp(-x)));
    } 
		
        
	
	return;
}