#include <stdint.h>
#include "kernel_EMO.hpp"
using namespace std;

void GeLU(float* X_data, float* Y_data, int* X_num){
	// #pragma HLS INTERFACE mode=ap_fifo port=X_data
	// #pragma HLS INTERFACE mode=ap_fifo port=Y_data
	for(int i = X_num[0] * X_num[1] * X_num[2] * X_num[3] - 1; i >= 0; i--){ // traverse all data
        // #pragma HLS UNROLL
        float x = X_data[i];
        //Y_data[i] = x * (1 / (1 + exp(-1.702*x)));
        Y_data[i] = x/2*(1+erf(x/1.4142135623730951));
    } 
		
        
	
	return;
}