// Includes
#include <hls_math.h>
#include <hls_stream.h>
#include <stdint.h>
#include "kernel_stage1.hpp"

void ConvNormAct(float* dw_in, float* dw_kernel, float* dw_bias, int* dw_shape_para, int* dw_conv_para,
                 float* dw_out, float* norm_out, float* norm_mean, float* norm_var, float* norm_gamma, float* norm_beta,
                 float* act_out, int zp, int* dw_X_num)
{
    DW_conv(dw_in, dw_kernel, dw_bias, dw_shape_para, dw_conv_para, dw_out);
    BatchNorm(dw_out, norm_out, dw_X_num, norm_mean, norm_var, norm_gamma, norm_beta);
    ReLU(norm_out, act_out, dw_X_num, zp);
}

extern "C"
{
    void kernel_stage1(float* X_data, 
                       float* norm_1_weight, float* norm_1_bias, float* norm_1_running_mean, float* norm_1_running_var,
                       float* v_conv_1_weight, float* v_conv_1_bias,
                       float* dw_conv_1_filter, float* dw_norm_1_gamma, float* dw_norm_1_beta, float* dw_norm_1_mean, float* dw_norm_1_var,
                       float* proj_1_weight,
                       float* norm_2_weight, float* norm_2_bias, float* norm_2_running_mean, float* norm_2_running_var,
                       float* v_conv_2_weight, float* v_conv_2_bias,
                       float* dw_conv_2_filter, float* dw_norm_2_gamma, float* dw_norm_2_beta, float* dw_norm_2_mean, float* dw_norm_2_var,
                       float* proj_2_weight,
                       float* Y_norm_1, float* Y_v_conv_1, float* Y_dw_conv_1, float* Y_dw_norm_1, float* Y_dw_act_1, float* Y_proj_1,
                       float* Y_norm_2, float* Y_v_conv_2, float* Y_dw_conv_2, float* Y_dw_norm_2, float* Y_dw_act_2, float* Y_proj_2,
                       float* Y_dw_skip_2, float* Y_skip_2
                       )
    {
    #pragma HLS INTERFACE m_axi port = X_data bundle = gmem0 depth = 75264
    // depth 1
    #pragma HLS INTERFACE m_axi port = norm_1_weight depth = 6
    #pragma HLS INTERFACE m_axi port = norm_1_bias depth = 6
    #pragma HLS INTERFACE m_axi port = norm_1_running_mean depth = 6
    #pragma HLS INTERFACE m_axi port = norm_1_running_var depth = 6

    #pragma HLS INTERFACE m_axi port = v_conv_1_weight depth = 144
    #pragma HLS INTERFACE m_axi port = v_conv_1_bias depth = 24

    #pragma HLS INTERFACE m_axi port = dw_conv_1_filter depth = 216
    #pragma HLS INTERFACE m_axi port = dw_norm_1_gamma depth = 24
    #pragma HLS INTERFACE m_axi port = dw_norm_1_beta depth = 24
    #pragma HLS INTERFACE m_axi port = dw_norm_1_mean depth = 24
    #pragma HLS INTERFACE m_axi port = dw_norm_1_var depth = 24
    
    #pragma HLS INTERFACE m_axi port = proj_1_weight depth = 192
    
    // depth 2
    #pragma HLS INTERFACE m_axi port = norm_2_weight depth = 8
    #pragma HLS INTERFACE m_axi port = norm_2_bias depth = 8
    #pragma HLS INTERFACE m_axi port = norm_2_running_mean depth = 8
    #pragma HLS INTERFACE m_axi port = norm_2_running_var depth = 8

    #pragma HLS INTERFACE m_axi port = v_conv_2_weight depth = 128
    #pragma HLS INTERFACE m_axi port = v_conv_2_bias depth = 16

    #pragma HLS INTERFACE m_axi port = dw_conv_2_filter depth = 144
    #pragma HLS INTERFACE m_axi port = dw_norm_2_gamma depth = 16
    #pragma HLS INTERFACE m_axi port = dw_norm_2_beta depth = 16
    #pragma HLS INTERFACE m_axi port = dw_norm_2_mean depth = 16
    #pragma HLS INTERFACE m_axi port = dw_norm_2_var depth = 16
    
    #pragma HLS INTERFACE m_axi port = proj_2_weight depth = 128

    // in and out depth 1
    #pragma HLS INTERFACE m_axi port = Y_norm_1 bundle = gmem1 depth = 75264
    #pragma HLS INTERFACE m_axi port = Y_v_conv_1 bundle = gmem2 depth = 301056
    #pragma HLS INTERFACE m_axi port = Y_dw_conv_1 bundle = gmem0 depth = 75264
    #pragma HLS INTERFACE m_axi port = Y_dw_norm_1 bundle = gmem1 depth = 75264
    #pragma HLS INTERFACE m_axi port = Y_dw_act_1 bundle = gmem3 depth = 75264
    #pragma HLS INTERFACE m_axi port = Y_proj_1 bundle = gmem0 depth = 25088

    // in and out depth 2
    #pragma HLS INTERFACE m_axi port = Y_norm_2 bundle = gmem1 depth = 25088
    #pragma HLS INTERFACE m_axi port = Y_v_conv_2 bundle = gmem2 depth = 50176
    #pragma HLS INTERFACE m_axi port = Y_dw_conv_2 bundle = gmem0 depth = 50176
    #pragma HLS INTERFACE m_axi port = Y_dw_norm_2 bundle = gmem1 depth = 50176
    #pragma HLS INTERFACE m_axi port = Y_dw_act_2 bundle = gmem3 depth = 50176
    #pragma HLS INTERFACE m_axi port = Y_dw_skip_2 bundle = gmem1 depth = 50176
    #pragma HLS INTERFACE m_axi port = Y_proj_2 bundle = gmem0 depth = 25088

    #pragma HLS INTERFACE m_axi port = Y_skip_2 bundle = gmem1 depth = 25088

    // depth 1
    int norm_1_X_num[4] = {1, 6, 112, 112};
    int dw_conv_1_shape_para[7] = {1, 24, 112, 112, 24, 56, 56};
    int dw_conv_1_conv_para[6] = {3, 0, 2, 1, 24, 1};
    int dw_1_X_num[4] = {1, 24, 56, 56};

    // depth 2
    int norm_2_X_num[4] = {1, 8, 56, 56};
    int dw_conv_2_shape_para[7] = {1, 16, 56, 56, 16, 56, 56};
    int dw_conv_2_conv_para[6] = {3, 0, 1, 1, 16, 1};
    int dw_2_X_num[4] = {1, 16, 56, 56};

    // depth 1
    BatchNorm(X_data, Y_norm_1, norm_1_X_num, norm_1_running_mean, norm_1_running_var, norm_1_weight, norm_1_bias);
    Pointwise_conv(Y_norm_1, Y_v_conv_1, v_conv_1_weight, v_conv_1_bias, 1, 6, 24, 112, 112, 1);
    ConvNormAct(Y_v_conv_1, dw_conv_1_filter, nullptr, dw_conv_1_shape_para, dw_conv_1_conv_para,
                Y_dw_conv_1, Y_dw_norm_1, dw_norm_1_mean, dw_norm_1_var, dw_norm_1_gamma, dw_norm_1_beta,
                Y_dw_act_1, 0, dw_1_X_num);
    Pointwise_conv(Y_dw_act_1, Y_proj_1, proj_1_weight, nullptr, 1, 24, 8, 56, 56, 0);

    // depth 2
    BatchNorm(Y_proj_1, Y_norm_2, norm_2_X_num, norm_2_running_mean, norm_2_running_var, norm_2_weight, norm_2_bias);
    Pointwise_conv(Y_norm_2, Y_v_conv_2, v_conv_2_weight, v_conv_2_bias, 1, 8, 16, 56, 56, 1);
    ConvNormAct(Y_v_conv_2, dw_conv_2_filter, nullptr, dw_conv_2_shape_para, dw_conv_2_conv_para,
                Y_dw_conv_2, Y_dw_norm_2, dw_norm_2_mean, dw_norm_2_var, dw_norm_2_gamma, dw_norm_2_beta,
                Y_dw_act_2, 0, dw_2_X_num);
    Compute_skip(Y_v_conv_2, Y_dw_act_2, Y_dw_skip_2, dw_2_X_num);
    Pointwise_conv(Y_dw_skip_2, Y_proj_2, proj_2_weight, nullptr, 1, 16, 8, 56, 56, 0);
    Compute_skip(Y_proj_1, Y_proj_2, Y_skip_2, norm_2_X_num);
    }
}