// Includes
#include <iostream>
#include <ap_int.h>
#include <hls_stream.h>


extern "C" {
void SE(float* X_data, float* Y_data, int* X_num, float* X_mean, float* X_reduce, float* X_relu, float* X_expand, float* X_sigmoid, float* reduce_filter, float* reduce_bias, float* expand_filter, float* expand_bias);
//暫時用relu取代silu (pretrain用silu)
//之後需要的話再改回silu
}

