// Includes
#include <hls_math.h>
#include <hls_stream.h>
#include <stdint.h>
#include "kernel_EMO.hpp"

extern "C"
{
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
                       )
    {
    // #pragma HLS INTERFACE m_axi port = X_data bundle = gmem0 depth = 100352
    
    // // stage 2 depth 1
    // #pragma HLS INTERFACE m_axi port = norm_2_1_weight depth = 32
    // #pragma HLS INTERFACE m_axi port = norm_2_1_bias depth = 32
    // #pragma HLS INTERFACE m_axi port = norm_2_1_running_mean depth = 32
    // #pragma HLS INTERFACE m_axi port = norm_2_1_running_var depth = 32
    // #pragma HLS INTERFACE m_axi port = v_conv_2_1_weight depth = 5120
    // #pragma HLS INTERFACE m_axi port = v_conv_2_1_bias depth = 160
    // #pragma HLS INTERFACE m_axi port = dw_conv_2_1_filter depth = 1440
    // #pragma HLS INTERFACE m_axi port = dw_norm_2_1_gamma depth = 160
    // #pragma HLS INTERFACE m_axi port = dw_norm_2_1_beta depth = 160
    // #pragma HLS INTERFACE m_axi port = dw_norm_2_1_mean depth = 160
    // #pragma HLS INTERFACE m_axi port = dw_norm_2_1_var depth = 160
    // #pragma HLS INTERFACE m_axi port = proj_2_1_weight depth = 7680
    
    // // stage 2 depth 2
    // #pragma HLS INTERFACE m_axi port = norm_2_2_weight depth = 48
    // #pragma HLS INTERFACE m_axi port = norm_2_2_bias depth = 48
    // #pragma HLS INTERFACE m_axi port = norm_2_2_running_mean depth = 48
    // #pragma HLS INTERFACE m_axi port = norm_2_2_running_var depth = 48
    // #pragma HLS INTERFACE m_axi port = v_conv_2_2_weight depth = 5760
    // #pragma HLS INTERFACE m_axi port = v_conv_2_2_bias depth = 120
    // #pragma HLS INTERFACE m_axi port = dw_conv_2_2_filter depth = 1080
    // #pragma HLS INTERFACE m_axi port = dw_norm_2_2_gamma depth = 120
    // #pragma HLS INTERFACE m_axi port = dw_norm_2_2_beta depth = 120
    // #pragma HLS INTERFACE m_axi port = dw_norm_2_2_mean depth = 120
    // #pragma HLS INTERFACE m_axi port = dw_norm_2_2_var depth = 120
    // #pragma HLS INTERFACE m_axi port = proj_2_2_weight depth = 5760

    // // in and out stage 2 depth 1
    // #pragma HLS INTERFACE m_axi port = Y_norm_2_1 bundle = gmem1 depth = 100352
    // #pragma HLS INTERFACE m_axi port = Y_v_conv_2_1 bundle = gmem2 depth = 501760
    // #pragma HLS INTERFACE m_axi port = Y_v_act_2_1 bundle = gmem3 depth = 501760
    // #pragma HLS INTERFACE m_axi port = Y_dw_conv_2_1 bundle = gmem0 depth = 125440
    // #pragma HLS INTERFACE m_axi port = Y_dw_norm_2_1 bundle = gmem1 depth = 125440
    // #pragma HLS INTERFACE m_axi port = Y_dw_act_2_1 bundle = gmem3 depth = 125440
    // #pragma HLS INTERFACE m_axi port = Y_proj_2_1 bundle = gmem0 depth = 37632

    // // in and out stage 2 depth 2
    // #pragma HLS INTERFACE m_axi port = Y_norm_2_2 bundle = gmem2 depth = 37632
    // #pragma HLS INTERFACE m_axi port = Y_v_conv_2_2 bundle = gmem1 depth = 94080
    // #pragma HLS INTERFACE m_axi port = Y_v_act_2_2 bundle = gmem0 depth = 94080
    // #pragma HLS INTERFACE m_axi port = Y_dw_conv_2_2 bundle = gmem3 depth = 94080
    // #pragma HLS INTERFACE m_axi port = Y_dw_norm_2_2 bundle = gmem0 depth = 94080
    // #pragma HLS INTERFACE m_axi port = Y_dw_act_2_2 bundle = gmem2 depth = 94080
    // #pragma HLS INTERFACE m_axi port = Y_proj_2_2 bundle = gmem1 depth = 37632
    // #pragma HLS INTERFACE m_axi port = Y_dw_skip_2_2 bundle = gmem3 depth = 94080
    // #pragma HLS INTERFACE m_axi port = Y_skip_2_2 bundle = gmem2 depth = 37632

    // stage 2 depth 1
    int norm_2_1_X_num[4] = {1, 32, 56, 56};
    int v_conv_2_1_X_num[4] = {1, 160, 56, 56};
    int dw_conv_2_1_shape_para[7] = {1, 160, 56, 56, 160, 28, 28};
    int dw_conv_2_1_conv_para[6] = {3, 0, 2, 1, 160, 1};
    int dw_2_1_X_num[4] = {1, 160, 28, 28};

    // stage 2 depth 2
    int norm_2_2_X_num[4] = {1, 48, 28, 28};
    int v_conv_2_2_X_num[4] = {1, 120, 28, 28};
    int dw_conv_2_2_shape_para[7] = {1, 120, 28, 28, 120, 28, 28};
    int dw_conv_2_2_conv_para[6] = {3, 0, 1, 1, 120, 1};
    int dw_2_2_X_num[4] = {1, 120, 28, 28};


    // stage 2 depth 1
    BatchNorm(X_data, Y_norm_2_1, norm_2_1_X_num, norm_2_1_running_mean, norm_2_1_running_var, norm_2_1_weight, norm_2_1_bias);
    Pointwise_conv(Y_norm_2_1, Y_v_conv_2_1, v_conv_2_1_weight, v_conv_2_1_bias, 1, 32, 160, 56, 56, 1);
    SiLU(Y_v_conv_2_1, Y_v_act_2_1, v_conv_2_1_X_num);
    DW_conv(Y_v_act_2_1, dw_conv_2_1_filter, nullptr, dw_conv_2_1_shape_para, dw_conv_2_1_conv_para, Y_dw_conv_2_1);
    BatchNorm(Y_dw_conv_2_1, Y_dw_norm_2_1, dw_2_1_X_num, dw_norm_2_1_mean, dw_norm_2_1_var, dw_norm_2_1_gamma, dw_norm_2_1_beta);
    SiLU(Y_dw_norm_2_1, Y_dw_act_2_1, dw_2_1_X_num);
    Pointwise_conv(Y_dw_act_2_1, Y_proj_2_1, proj_2_1_weight, nullptr, 1, 160, 48, 28, 28, 0);

    // stage 2 depth 2
    BatchNorm(Y_proj_2_1, Y_norm_2_2, norm_2_2_X_num, norm_2_2_running_mean, norm_2_2_running_var, norm_2_2_weight, norm_2_2_bias);
    Pointwise_conv(Y_norm_2_2, Y_v_conv_2_2, v_conv_2_2_weight, v_conv_2_2_bias, 1, 48, 120, 28, 28, 1);
    SiLU(Y_v_conv_2_2, Y_v_act_2_2, v_conv_2_2_X_num);
    DW_conv(Y_v_act_2_2, dw_conv_2_2_filter, nullptr, dw_conv_2_2_shape_para, dw_conv_2_2_conv_para, Y_dw_conv_2_2);
    BatchNorm(Y_dw_conv_2_2, Y_dw_norm_2_2, dw_2_2_X_num, dw_norm_2_2_mean, dw_norm_2_2_var, dw_norm_2_2_gamma, dw_norm_2_2_beta);
    SiLU(Y_dw_norm_2_2, Y_dw_act_2_2, dw_2_2_X_num);
    Compute_skip(Y_v_act_2_2, Y_dw_act_2_2, Y_dw_skip_2_2, dw_2_2_X_num);
    Pointwise_conv(Y_dw_skip_2_2, Y_proj_2_2, proj_2_2_weight, nullptr, 1, 120, 48, 28, 28, 0);
    Compute_skip(Y_proj_2_1, Y_proj_2_2, Y_skip_2_2, norm_2_2_X_num);
    }
}