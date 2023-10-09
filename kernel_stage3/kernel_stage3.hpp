#ifndef _KRNL_STAGE1_H_
#define _KRNL_STAGE1_H_

// Includes
#include <ap_int.h>
#include <hls_stream.h>
#include <hls_math.h>
#include <iostream>

extern "C"
{
    void kernel_stage3(float *buffer_DataIn_1,
                              float *afterNorm,
                              float *norm1_mean, float *norm1_var, float *norm1_weight, float *norm1_bias, float *norm1_ln_in,
                              float *afterPad,
                              float *afterRearrangeX,
                              float *afterPad1,
                              float *afterConv1,
                              float *kernel1,
                              float *bias1,
                              float *in_qk,
                              float *in_q,
                              float *in_k,
                              float *afterQKMultiplication,
                              float *afterSoftmax,
                              float *afterRearrangeX2,
                              float *afterQKXMultiplication,
                              float *afterRearrangeQKX,
                              float *afterPad2,
                              float *afterConv2,
                              float *kernel2,
                              float *bias2,
                              float *afterAct2,
                              float *QKV,
                              float *buffer_out,
                              float *in1_stream,
                              float *sumQK,
                              float *sumQKX,
                              float *buffer_result,
                       float* dw_conv_2_filter, float* dw_norm_2_gamma, float* dw_norm_2_beta, float* dw_norm_2_mean, float* dw_norm_2_var,
                       float* proj_2_weight,
                       float* Y_dw_conv_2, float* Y_dw_norm_2, float* Y_dw_act_2, float* Y_proj_2,
                       float* Y_dw_skip_2, float* Y_skip_2
                       );
    void DW_conv(float *in, float *kernel, float *bias, int *shape_para, int *conv_para, float *out);
    void BatchNorm(float *X_data, float *Y_data, int *X_num, float *mean, float *var, float *gamma, float *beta);
    void ReLU(float *X_data, float *Y_data, int *X_num, int zp);
    void Pointwise_conv(float *buffer_DataIn_1, float *out, float *buffer_kernel, float *buffer_bias,
                        int batch_size, int channel_in, int channel_out, int height_in, int width_in,
                        bool is_conv_bias);
    void Compute_skip(float *in1, float *in2, float *out, int *X_num);
    void kernel_attention(float *buffer_DataIn_1,
                              float *afterNorm,
                              float *norm1_mean, float *norm1_var, float *norm1_weight, float *norm1_bias, float *norm1_ln_in,
                              float *afterPad,
                              float *afterRearrangeX,
                              float *afterPad1,
                              float *afterConv1,
                              float *kernel1,
                              float *bias1,
                              float *in_qk,
                              float *in_q,
                              float *in_k,
                              float *afterQKMultiplication,
                              float *afterSoftmax,
                              float *afterRearrangeX2,
                              float *afterQKXMultiplication,
                              float *afterRearrangeQKX,
                              float *afterPad2,
                              float *afterConv2,
                              float *kernel2,
                              float *bias2,
                              float *afterAct2,
                              float *QKV,
                              float *buffer_out,
                              float *in1_stream,
                              float *sumQK,
                              float *sumQKX,
                              float *buffer_result
                       );
}

#endif
