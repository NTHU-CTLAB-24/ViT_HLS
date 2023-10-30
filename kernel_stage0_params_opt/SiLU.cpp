#include <stdint.h>
#include "kernel_stage0.hpp"
using namespace std;

void SiLU(float* img, int* X_num){
	// #pragma HLS INTERFACE mode=ap_fifo port=X_data
	// #pragma HLS INTERFACE mode=ap_fifo port=Y_data
	for(int i = X_num[0] * X_num[1] * X_num[2] * X_num[3] - 1; i >= 0; i--){ // traverse all data
        // #pragma HLS UNROLL
        float x = img[i];
        img[i] *= (1 / (1 + exp(-x)));
    } 
		
        
	
	return;
}