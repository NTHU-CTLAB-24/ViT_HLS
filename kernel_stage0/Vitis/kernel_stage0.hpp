#ifndef _KRNL_STAGE0_H_
#define _KRNL_STAGE0_H_

// Includes
#include <ap_int.h>
#include <hls_stream.h>
#include <iostream>

void BatchNorm(float* X_data, float* Y_data, int* X_num, float* mean, float* var, float* gamma, float* beta);
void ReLU(float* X_data, float* Y_data, int* X_num, int zp);
void Sigmoid(float* X_data, float* Y_data, int* X_num);
void Padding(float* X_data, float* Y_data, int* X_num, int padding);
void Compute_mean(float* X_data, int* X_num, float* Y_data);
void Compute_mul(float* X_data, float* feature, float* Y_data, int* X_num);
void Convolution(float* X_data, int* X_num, float* Y_data, int* Y_num, float* filter, int* filter_num, float* bias);
void Mspatch(float* X_data, int* X_num, float* X_pad, float* X_conv, int* msp_num, float* msp_filter, int* msp_filter_num, float* msp_bias,
            float* mean, float* var, float* gamma, float* beta, float* Y_msp);
void DW_conv(float *in, float *kernel, float *bias, int *shape_para, int *conv_para, float *out);
void SE(float* X_data, float* Y_data, int* X_num, float* X_mean, float* X_reduce, float* X_relu, float* X_expand, float* X_sigmoid, float* reduce_filter, float* reduce_bias, float* expand_filter, float* expand_bias);

#endif
