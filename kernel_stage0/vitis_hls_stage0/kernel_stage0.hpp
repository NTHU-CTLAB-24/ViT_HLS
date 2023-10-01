#ifndef _KRNL_STAGE0_H_
#define _KRNL_STAGE0_H_

#include <iostream>
#include <ap_int.h>
#include <hls_math.h>
#include <hls_stream.h>

const int size = 4096;

extern "C" {
    void kernel_stage0(float* X_data, float* msp_filter, float* msp_bias, float* dw_filter, float* dw_bias,
                        float* reduce_filter, float* reduce_bias, float* expand_filter, float* expand_bias, float* proj_filter,
                        float* mean1, float* var1, float* gamma1, float* beta1,
                        float* mean2, float* var2, float* gamma2, float* beta2,
                        float* X_conv, float* X_dwconv, 
                        float* X_mean, float* X_reduce, float* X_relu, float* X_expand, float* X_sigmoid,
                        float* Y_msp, float* Y_dwact, float* Y_se, float* Y_proj);
    void DW_conv(float *in, float *kernel, float *bias, int *shape_para, int *conv_para, float *out);
    void BatchNorm(float *X_data, float *Y_data, int *X_num, float *mean, float *var, float *gamma, float *beta);
    void ReLU(float *X_data, float *Y_data, int *X_num, int zp);
    void Pointwise_conv(float *buffer_DataIn_1, float *out, float *buffer_kernel, float *buffer_bias,
                        int batch_size, int channel_in, int channel_out, int height_in, int width_in,
                        bool is_conv_bias);
    void Compute_mean(float* X_data, int* X_num, float* Y_data);
    void Convolution(float* X_data, int* X_num, float* Y_data, int* Y_num,  float* filter, int* filter_num, float* bias);
}

#endif