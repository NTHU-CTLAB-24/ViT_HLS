#ifndef _KRNL_STAGE0_H_
#define _KRNL_STAGE0_H_

#include <iostream>
#include <ap_int.h>
#include <hls_math.h>
#include <hls_stream.h>

const int img_space = 24*112*112;
const int compute_space = 2*img_space;
const int max_weight_size = 672;
const int max_bias_size = 24;
const int max_param_size = 2*(max_weight_size+max_bias_size);

extern float img[compute_space];
//#pragma HLS bind_storage variable=img type=RAM_T2P impl=URAM
extern float compute_tmp[compute_space];
//#pragma HLS bind_storage variable=compute_tmp type=RAM_T2P impl=URAM
extern float params[max_param_size];
//#pragma HLS bind_storage variable=params type=RAM_1WNR

extern "C" {
    void kernel_stage0(float* X_data, float* msp_conv_weight, float* msp_conv_bias, float* msp_norm_weight, float* msp_norm_bias, float* msp_norm_running_mean, float* msp_norm_running_var,
                    float* dw_conv_weight, float* norm_1_weight, float* norm_1_bias, float* norm_1_running_mean, float* norm_1_running_var,
                    float* se_conv_reduce_weight, float* se_conv_reduce_bias, float* se_conv_expand_weight, float* se_conv_expand_bias,
                    float* proj_conv_weight, float* Y_msp_conv, float* Y_msp_norm, float* Y_dw_conv, float* Y_dw_norm, float* Y_dw_act, float* Y_se_mean, float* Y_se_reduce, 
                    float* Y_se_silu, float* Y_se_expand, float* Y_se_sigmoid, float* Y_se, float* Y_proj);
    void DW_conv(float *img, float* out, float *kernel, float *bias, int *shape_para, int *conv_para);
    void BatchNorm(float *img, int *X_num, float *mean, float *var, float *gamma, float *beta);
    void ReLU(float *img, int *X_num, int zp);
    void SiLU(float *img, int* X_num);
    void Pointwise_conv(float *img, float* out, float *buffer_kernel, float *buffer_bias,
                        int batch_size, int channel_in, int channel_out, int height_in, int width_in,
                        bool is_conv_bias);
    void reset_arr(float* img, int* X_num);
    void load_params(float* params, float* src, int size);
}

#endif