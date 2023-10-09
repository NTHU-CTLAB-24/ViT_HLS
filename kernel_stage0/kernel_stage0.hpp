#ifndef _KRNL_STAGE0_H_
#define _KRNL_STAGE0_H_

#include <iostream>
#include <ap_int.h>
#include <hls_math.h>
#include <hls_stream.h>

const int size = 4096;

extern "C" {
    void kernel_stage0(float* X_data, float* msp_conv_weight, float* msp_conv_bias, float* msp_norm_weight, float* msp_norm_bias, float* msp_norm_running_mean, float* msp_norm_running_var,
                    float* dw_conv_weight, float* norm_1_weight, float* norm_1_bias, float* norm_1_running_mean, float* norm_1_running_var,
                    float* se_conv_reduce_weight, float* se_conv_reduce_bias, float* se_conv_expand_weight, float* se_conv_expand_bias,
                    float* proj_conv_weight, float* Y_msp_conv, float* Y_msp_norm, float* Y_dw_conv, float* Y_dw_norm, float* Y_dw_act, float* Y_se_mean, float* Y_se_reduce, 
                    float* Y_se_silu, float* Y_se_expand, float* Y_se_sigmoid, float* Y_se, float* Y_proj);
    void DW_conv(float *in, float *kernel, float *bias, int *shape_para, int *conv_para, float *out);
    void BatchNorm(float *X_data, float *Y_data, int *X_num, float *mean, float *var, float *gamma, float *beta);
    void ReLU(float *X_data, float *Y_data, int *X_num, int zp);
    void SiLU(float* X_data, float* Y_data, int* X_num);
    void Pointwise_conv(float *buffer_DataIn_1, float *out, float *buffer_kernel, float *buffer_bias,
                        int batch_size, int channel_in, int channel_out, int height_in, int width_in,
                        bool is_conv_bias);
    void Compute_mean(float* X_data, int* X_num, float* Y_data);
    void Convolution(float* X_data, int* X_num, float* Y_data, int* Y_num,  float* filter, int* filter_num, float* bias);
}

#endif