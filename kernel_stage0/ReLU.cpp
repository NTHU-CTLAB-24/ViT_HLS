#include "kernel_stage0.hpp"
#include<iostream>
using namespace std;

void ReLU(float* X_data, float* Y_data, int* X_num, int zp){
	
	for(int i = X_num[0] * X_num[1] * X_num[2] * X_num[3] - 1; i >= 0; i--) // traverse all data
		Y_data[i] = (X_data[i] > zp) ? X_data[i] : zp;
	
	return;
}
