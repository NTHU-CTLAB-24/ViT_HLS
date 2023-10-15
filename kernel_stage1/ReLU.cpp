#include <stdint.h>
#include "kernel_stage1.hpp"
using namespace std;

void ReLU(float* X_data, float* Y_data, int* X_num, int zp){
	// #pragma HLS INTERFACE mode=ap_fifo port=X_data
	// #pragma HLS INTERFACE mode=ap_fifo port=Y_data
	ReLU:
	for(int i = X_num[0] * X_num[1] * X_num[2] * X_num[3] - 1; i >= 0; i--) // traverse all data
		// #pragma HLS UNROLL
		Y_data[i] = (X_data[i] > zp) ? X_data[i] : zp;
	
	return;
}