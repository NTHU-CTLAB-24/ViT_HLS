// Includes
#include <hls_math.h>
#include <hls_stream.h>
#include <stdint.h>
#include "kernel_stage1_2.hpp"

extern "C"
{
    void kernel_stage1(float* X_data, 
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
                       )
    {
    // #pragma HLS INTERFACE m_axi port = X_data bundle = gmem0 depth = 301056
    // // depth 1
    // #pragma HLS INTERFACE m_axi port = norm_1_1_weight depth = 24
    // #pragma HLS INTERFACE m_axi port = norm_1_1_bias depth = 24
    // #pragma HLS INTERFACE m_axi port = norm_1_1_running_mean depth = 24
    // #pragma HLS INTERFACE m_axi port = norm_1_1_running_var depth = 24

    // #pragma HLS INTERFACE m_axi port = v_conv_1_1_weight depth = 2304
    // #pragma HLS INTERFACE m_axi port = v_conv_1_1_bias depth = 96

    // #pragma HLS INTERFACE m_axi port = dw_conv_1_1_filter depth = 864
    // #pragma HLS INTERFACE m_axi port = dw_norm_1_1_gamma depth = 96
    // #pragma HLS INTERFACE m_axi port = dw_norm_1_1_beta depth = 96
    // #pragma HLS INTERFACE m_axi port = dw_norm_1_1_mean depth = 96
    // #pragma HLS INTERFACE m_axi port = dw_norm_1_1_var depth = 96
    
    // #pragma HLS INTERFACE m_axi port = proj_1_1_weight depth = 3072
    
    // // depth 2
    // #pragma HLS INTERFACE m_axi port = norm_1_2_weight depth = 32
    // #pragma HLS INTERFACE m_axi port = norm_1_2_bias depth = 32
    // #pragma HLS INTERFACE m_axi port = norm_1_2_running_mean depth = 32
    // #pragma HLS INTERFACE m_axi port = norm_1_2_running_var depth = 32

    // #pragma HLS INTERFACE m_axi port = v_conv_1_2_weight depth = 2048
    // #pragma HLS INTERFACE m_axi port = v_conv_1_2_bias depth = 64

    // #pragma HLS INTERFACE m_axi port = dw_conv_1_2_filter depth = 576
    // #pragma HLS INTERFACE m_axi port = dw_norm_1_2_gamma depth = 64
    // #pragma HLS INTERFACE m_axi port = dw_norm_1_2_beta depth = 64
    // #pragma HLS INTERFACE m_axi port = dw_norm_1_2_mean depth = 64
    // #pragma HLS INTERFACE m_axi port = dw_norm_1_2_var depth = 64
    
    // #pragma HLS INTERFACE m_axi port = proj_1_2_weight depth = 2048

    // // in and out depth 1
    // #pragma HLS INTERFACE m_axi port = Y_norm_1_1 bundle = gmem1 depth = 301056
    // #pragma HLS INTERFACE m_axi port = Y_v_conv_1_1 bundle = gmem2 depth = 1204224
    // #pragma HLS INTERFACE m_axi port = Y_v_act_1_1 bundle = gmem3 depth = 1204224
    // #pragma HLS INTERFACE m_axi port = Y_dw_conv_1_1 bundle = gmem0 depth = 301056
    // #pragma HLS INTERFACE m_axi port = Y_dw_norm_1_1 bundle = gmem1 depth = 301056
    // #pragma HLS INTERFACE m_axi port = Y_dw_act_1_1 bundle = gmem3 depth = 301056
    // #pragma HLS INTERFACE m_axi port = Y_proj_1_1 bundle = gmem0 depth = 100352

    // // in and out depth 2
    // #pragma HLS INTERFACE m_axi port = Y_norm_1_2 bundle = gmem2 depth = 100352
    // #pragma HLS INTERFACE m_axi port = Y_v_conv_1_2 bundle = gmem1 depth = 200704
    // #pragma HLS INTERFACE m_axi port = Y_v_act_1_2 bundle = gmem0 depth = 200704
    // #pragma HLS INTERFACE m_axi port = Y_dw_conv_1_2 bundle = gmem3 depth = 200704
    // #pragma HLS INTERFACE m_axi port = Y_dw_norm_1_2 bundle = gmem0 depth = 200704
    // #pragma HLS INTERFACE m_axi port = Y_dw_act_1_2 bundle = gmem2 depth = 200704
    // #pragma HLS INTERFACE m_axi port = Y_proj_1_2 bundle = gmem1 depth = 100352
    // #pragma HLS INTERFACE m_axi port = Y_dw_skip_1_2 bundle = gmem3 depth = 200704
    // #pragma HLS INTERFACE m_axi port = Y_skip_1_2 bundle = gmem2 depth = 100352

    // depth 1
    int norm_1_1_X_num[4] = {1, 24, 112, 112};
    int v_conv_1_1_X_num[4] = {1, 96, 112, 112};
    int dw_conv_1_1_shape_para[7] = {1, 96, 112, 112, 96, 56, 56};
    int dw_conv_1_1_conv_para[6] = {3, 0, 2, 1, 96, 1};
    int dw_1_1_X_num[4] = {1, 96, 56, 56};

    // depth 2
    int norm_1_2_X_num[4] = {1, 32, 56, 56};
    int v_conv_1_2_X_num[4] = {1, 64, 56, 56};
    int dw_conv_1_2_shape_para[7] = {1, 64, 56, 56, 64, 56, 56};
    int dw_conv_1_2_conv_para[6] = {3, 0, 1, 1, 64, 1};
    int dw_1_2_X_num[4] = {1, 64, 56, 56};

    // depth 1
    BatchNorm(X_data, Y_norm_1_1, norm_1_1_X_num, norm_1_1_running_mean, norm_1_1_running_var, norm_1_1_weight, norm_1_1_bias);
    Pointwise_conv(Y_norm_1_1, Y_v_conv_1_1, v_conv_1_1_weight, v_conv_1_1_bias, 1, 24, 96, 112, 112, 1);
    SiLU(Y_v_conv_1_1, Y_v_act_1_1, v_conv_1_1_X_num);
    DW_conv(Y_v_act_1_1, dw_conv_1_1_filter, nullptr, dw_conv_1_1_shape_para, dw_conv_1_1_conv_para, Y_dw_conv_1_1);
    BatchNorm(Y_dw_conv_1_1, Y_dw_norm_1_1, dw_1_1_X_num, dw_norm_1_1_mean, dw_norm_1_1_var, dw_norm_1_1_gamma, dw_norm_1_1_beta);
    SiLU(Y_dw_norm_1_1, Y_dw_act_1_1, dw_1_1_X_num);
    Pointwise_conv(Y_dw_act_1_1, Y_proj_1_1, proj_1_1_weight, nullptr, 1, 96, 32, 56, 56, 0);

    // depth 2
    BatchNorm(Y_proj_1_1, Y_norm_1_2, norm_1_2_X_num, norm_1_2_running_mean, norm_1_2_running_var, norm_1_2_weight, norm_1_2_bias);
    Pointwise_conv(Y_norm_1_2, Y_v_conv_1_2, v_conv_1_2_weight, v_conv_1_2_bias, 1, 32, 64, 56, 56, 1);
    SiLU(Y_v_conv_1_2, Y_v_act_1_2, v_conv_1_2_X_num);
    DW_conv(Y_v_act_1_2, dw_conv_1_2_filter, nullptr, dw_conv_1_2_shape_para, dw_conv_1_2_conv_para, Y_dw_conv_1_2);
    BatchNorm(Y_dw_conv_1_2, Y_dw_norm_1_2, dw_1_2_X_num, dw_norm_1_2_mean, dw_norm_1_2_var, dw_norm_1_2_gamma, dw_norm_1_2_beta);
    SiLU(Y_dw_norm_1_2, Y_dw_act_1_2, dw_1_2_X_num);
    Compute_skip(Y_v_act_1_2, Y_dw_act_1_2, Y_dw_skip_1_2, dw_1_2_X_num);
    Pointwise_conv(Y_dw_skip_1_2, Y_proj_1_2, proj_1_2_weight, nullptr, 1, 64, 32, 56, 56, 0);
    Compute_skip(Y_proj_1_1, Y_proj_1_2, Y_skip_1_2, norm_1_2_X_num);
    }
}