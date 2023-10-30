#include <stdint.h>
#include "kernel_stage0.hpp"
using namespace std;

void ReLU(float* img, int* X_num, int zp){
	
	for(int i = X_num[0] * X_num[1] * X_num[2] * X_num[3] - 1; i >= 0; i--) // traverse all data
		img[i] = (img[i] > zp) ? img[i] : zp;
	
	return;
}