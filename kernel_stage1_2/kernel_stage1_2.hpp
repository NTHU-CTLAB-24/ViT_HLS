#ifndef _KRNL_STAGE1_2_H_
#define _KRNL_STAGE1_2_H_

// Includes
#include <ap_int.h>
#include <hls_stream.h>
#include <hls_math.h>
#include <iostream>

extern "C"
{
    void kernel_stage1_2(float* X_data, 
                        float* norm_1_1_weight, float* norm_1_1_bias, float* norm_1_1_running_mean, float* norm_1_1_running_var,
                        float* v_conv_1_1_weight, float* v_conv_1_1_bias,
                        float* dw_conv_1_1_filter, float* dw_norm_1_1_gamma, float* dw_norm_1_1_beta, float* dw_norm_1_1_mean, float* dw_norm_1_1_var,
                        float* proj_1_1_weight,
                        float* norm_1_2_weight, float* norm_1_2_bias, float* norm_1_2_running_mean, float* norm_1_2_running_var,
                        float* v_conv_1_2_weight, float* v_conv_1_2_bias,
                        float* dw_conv_1_2_filter, float* dw_norm_1_2_gamma, float* dw_norm_1_2_beta, float* dw_norm_1_2_mean, float* dw_norm_1_2_var,
                        float* proj_1_2_weight,
                        float* norm_2_1_weight, float* norm_2_1_bias, float* norm_2_1_running_mean, float* norm_2_1_running_var,
                        float* v_conv_2_1_weight, float* v_conv_2_1_bias,
                        float* dw_conv_2_1_filter, float* dw_norm_2_1_gamma, float* dw_norm_2_1_beta, float* dw_norm_2_1_mean, float* dw_norm_2_1_var,
                        float* proj_2_1_weight,
                        float* norm_2_2_weight, float* norm_2_2_bias, float* norm_2_2_running_mean, float* norm_2_2_running_var,
                        float* v_conv_2_2_weight, float* v_conv_2_2_bias,
                        float* dw_conv_2_2_filter, float* dw_norm_2_2_gamma, float* dw_norm_2_2_beta, float* dw_norm_2_2_mean, float* dw_norm_2_2_var,
                        float* proj_2_2_weight,
                        float* Y_norm_1_1, float* Y_v_conv_1_1, float* Y_v_act_1_1, float* Y_dw_conv_1_1, float* Y_dw_norm_1_1, float* Y_dw_act_1_1, float* Y_proj_1_1,
                        float* Y_norm_1_2, float* Y_v_conv_1_2, float* Y_v_act_1_2, float* Y_dw_conv_1_2, float* Y_dw_norm_1_2, float* Y_dw_act_1_2, float* Y_proj_1_2,
                        float* Y_dw_skip_1_2, float* Y_skip_1_2,
                        float* Y_norm_2_1, float* Y_v_conv_2_1, float* Y_v_act_2_1, float* Y_dw_conv_2_1, float* Y_dw_norm_2_1, float* Y_dw_act_2_1, float* Y_proj_2_1,
                        float* Y_norm_2_2, float* Y_v_conv_2_2, float* Y_v_act_2_2, float* Y_dw_conv_2_2, float* Y_dw_norm_2_2, float* Y_dw_act_2_2, float* Y_proj_2_2,
                        float* Y_dw_skip_2_2, float* Y_skip_2_2
                       );
    void kernel_stage1(float *X_data,
                       float* norm_1_1_weight, float* norm_1_1_bias, float* norm_1_1_running_mean, float* norm_1_1_running_var,
                       float* v_conv_1_1_weight, float* v_conv_1_1_bias,
                       float* dw_conv_1_1_filter, float* dw_norm_1_1_gamma, float* dw_norm_1_1_beta, float* dw_norm_1_1_mean, float* dw_norm_1_1_var,
                       float* proj_1_1_weight,
                       float* norm_1_2_weight, float* norm_1_2_bias, float* norm_1_2_running_mean, float* norm_1_2_running_var,
                       float* v_conv_1_2_weight, float* v_conv_1_2_bias,
                       float* dw_conv_1_2_filter, float* dw_norm_1_2_gamma, float* dw_norm_1_2_beta, float* dw_norm_1_2_mean, float* dw_norm_1_2_var,
                       float* proj_1_2_weight,
                       float* Y_norm_1_1, float* Y_v_conv_1_1, float* Y_v_act_1_1, float* Y_dw_conv_1_1, float* Y_dw_norm_1_1, float* Y_dw_act_1_1, float* Y_proj_1_1,
                       float* Y_norm_1_2, float* Y_v_conv_1_2, float* Y_v_act_1_2, float* Y_dw_conv_1_2, float* Y_dw_norm_1_2, float* Y_dw_act_1_2, float* Y_proj_1_2,
                       float* Y_dw_skip_1_2, float* Y_skip_1_2
                       );
    void kernel_stage2(float* X_data, 
                       float* norm_2_1_weight, float* norm_2_1_bias, float* norm_2_1_running_mean, float* norm_2_1_running_var,
                       float* v_conv_2_1_weight, float* v_conv_2_1_bias,
                       float* dw_conv_2_1_filter, float* dw_norm_2_1_gamma, float* dw_norm_2_1_beta, float* dw_norm_2_1_mean, float* dw_norm_2_1_var,
                       float* proj_2_1_weight,
                       float* norm_2_2_weight, float* norm_2_2_bias, float* norm_2_2_running_mean, float* norm_2_2_running_var,
                       float* v_conv_2_2_weight, float* v_conv_2_2_bias,
                       float* dw_conv_2_2_filter, float* dw_norm_2_2_gamma, float* dw_norm_2_2_beta, float* dw_norm_2_2_mean, float* dw_norm_2_2_var,
                       float* proj_2_2_weight,
                       float* Y_norm_2_1, float* Y_v_conv_2_1, float* Y_v_act_2_1, float* Y_dw_conv_2_1, float* Y_dw_norm_2_1, float* Y_dw_act_2_1, float* Y_proj_2_1,
                       float* Y_norm_2_2, float* Y_v_conv_2_2, float* Y_v_act_2_2, float* Y_dw_conv_2_2, float* Y_dw_norm_2_2, float* Y_dw_act_2_2, float* Y_proj_2_2,
                       float* Y_dw_skip_2_2, float* Y_skip_2_2
                       );
    void DW_conv(float *in, float *kernel, float *bias, int *shape_para, int *conv_para, float *out);
    void BatchNorm(float *X_data, float *Y_data, int *X_num, float *mean, float *var, float *gamma, float *beta);
    void ReLU(float *X_data, float *Y_data, int *X_num, int zp);
    void SiLU(float *X_data, float *Y_data, int *X_num);
    void Pointwise_conv(float *buffer_DataIn_1, float *out, float *buffer_kernel, float *buffer_bias,
                        int batch_size, int channel_in, int channel_out, int height_in, int width_in,
                        bool is_conv_bias);
    void Compute_skip(float *in1, float *in2, float *out, int *X_num);
    }

#endif
