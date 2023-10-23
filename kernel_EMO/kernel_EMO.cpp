// Includes
#include <hls_math.h>
#include <hls_stream.h>
#include <stdint.h>
#include "kernel_EMO.hpp"

extern "C"
{
    void kernel_EMO(float* X_data,
                    float* msp_conv_weight, float* msp_conv_bias, float* msp_norm_weight, float* msp_norm_bias, float* msp_norm_running_mean, float* msp_norm_running_var,
                    float* dw_conv_weight, float* dw_norm_gamma, float* dw_norm_beta, float* dw_norm_mean, float* dw_norm_var,
                    float* se_conv_reduce_weight, float* se_conv_reduce_bias, float* se_conv_expand_weight, float* se_conv_expand_bias,
                    float* proj_conv_weight,
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
                    float* Y_msp_conv, float* Y_msp_norm, float* Y_dw_conv, float* Y_dw_norm, float* Y_dw_act,
                    float* Y_se_mean, float* Y_se_reduce, float* Y_se_act, float* Y_se_expand, float* Y_se_sigmoid, float* Y_se, float* Y_proj,
                    float* Y_norm_1_1, float* Y_v_conv_1_1, float* Y_v_act_1_1, float* Y_dw_conv_1_1, float* Y_dw_norm_1_1, float* Y_dw_act_1_1, float* Y_proj_1_1,
                    float* Y_norm_1_2, float* Y_v_conv_1_2, float* Y_v_act_1_2, float* Y_dw_conv_1_2, float* Y_dw_norm_1_2, float* Y_dw_act_1_2, float* Y_proj_1_2,
                    float* Y_dw_skip_1_2, float* Y_skip_1_2,
                    float* Y_norm_2_1, float* Y_v_conv_2_1, float* Y_v_act_2_1, float* Y_dw_conv_2_1, float* Y_dw_norm_2_1, float* Y_dw_act_2_1, float* Y_proj_2_1,
                    float* Y_norm_2_2, float* Y_v_conv_2_2, float* Y_v_act_2_2, float* Y_dw_conv_2_2, float* Y_dw_norm_2_2, float* Y_dw_act_2_2, float* Y_proj_2_2,
                    float* Y_dw_skip_2_2, float* Y_skip_2_2
                    )
    {
    // #pragma HLS INTERFACE m_axi port = X_data bundle = gmem0 depth = 301056
    #pragma HLS INTERFACE m_axi port = X_data bundle = gmem0 depth = 150528

    // stage 0
    #pragma HLS INTERFACE m_axi port = msp_conv_weight depth = 648
    #pragma HLS INTERFACE m_axi port = msp_conv_bias depth = 24
    #pragma HLS INTERFACE m_axi port = msp_norm_weight depth = 24
    #pragma HLS INTERFACE m_axi port = msp_norm_bias depth = 24
    #pragma HLS INTERFACE m_axi port = msp_norm_running_mean depth = 24
    #pragma HLS INTERFACE m_axi port = msp_norm_running_var depth = 24
    #pragma HLS INTERFACE m_axi port = dw_conv_weight depth = 216
    #pragma HLS INTERFACE m_axi port = dw_norm_gamma depth = 24
    #pragma HLS INTERFACE m_axi port = dw_norm_beta depth = 24
    #pragma HLS INTERFACE m_axi port = dw_norm_mean depth = 24
    #pragma HLS INTERFACE m_axi port = dw_norm_var depth = 24
    #pragma HLS INTERFACE m_axi port = se_conv_reduce_weight depth = 576
    #pragma HLS INTERFACE m_axi port = se_conv_reduce_bias depth = 24
    #pragma HLS INTERFACE m_axi port = se_conv_expand_weight depth = 576
    #pragma HLS INTERFACE m_axi port = se_conv_expand_bias depth = 24
    #pragma HLS INTERFACE m_axi port = proj_conv_weight depth = 576

    // stage 1 depth 1
    #pragma HLS INTERFACE m_axi port = norm_1_1_weight depth = 24
    #pragma HLS INTERFACE m_axi port = norm_1_1_bias depth = 24
    #pragma HLS INTERFACE m_axi port = norm_1_1_running_mean depth = 24
    #pragma HLS INTERFACE m_axi port = norm_1_1_running_var depth = 24
    #pragma HLS INTERFACE m_axi port = v_conv_1_1_weight depth = 2304
    #pragma HLS INTERFACE m_axi port = v_conv_1_1_bias depth = 96
    #pragma HLS INTERFACE m_axi port = dw_conv_1_1_filter depth = 864
    #pragma HLS INTERFACE m_axi port = dw_norm_1_1_gamma depth = 96
    #pragma HLS INTERFACE m_axi port = dw_norm_1_1_beta depth = 96
    #pragma HLS INTERFACE m_axi port = dw_norm_1_1_mean depth = 96
    #pragma HLS INTERFACE m_axi port = dw_norm_1_1_var depth = 96
    #pragma HLS INTERFACE m_axi port = proj_1_1_weight depth = 3072
    
    // stage 1 depth 2
    #pragma HLS INTERFACE m_axi port = norm_1_2_weight depth = 32
    #pragma HLS INTERFACE m_axi port = norm_1_2_bias depth = 32
    #pragma HLS INTERFACE m_axi port = norm_1_2_running_mean depth = 32
    #pragma HLS INTERFACE m_axi port = norm_1_2_running_var depth = 32
    #pragma HLS INTERFACE m_axi port = v_conv_1_2_weight depth = 2048
    #pragma HLS INTERFACE m_axi port = v_conv_1_2_bias depth = 64
    #pragma HLS INTERFACE m_axi port = dw_conv_1_2_filter depth = 576
    #pragma HLS INTERFACE m_axi port = dw_norm_1_2_gamma depth = 64
    #pragma HLS INTERFACE m_axi port = dw_norm_1_2_beta depth = 64
    #pragma HLS INTERFACE m_axi port = dw_norm_1_2_mean depth = 64
    #pragma HLS INTERFACE m_axi port = dw_norm_1_2_var depth = 64
    #pragma HLS INTERFACE m_axi port = proj_1_2_weight depth = 2048

    // stage 2 depth 1
    #pragma HLS INTERFACE m_axi port = norm_2_1_weight depth = 32
    #pragma HLS INTERFACE m_axi port = norm_2_1_bias depth = 32
    #pragma HLS INTERFACE m_axi port = norm_2_1_running_mean depth = 32
    #pragma HLS INTERFACE m_axi port = norm_2_1_running_var depth = 32
    #pragma HLS INTERFACE m_axi port = v_conv_2_1_weight depth = 5120
    #pragma HLS INTERFACE m_axi port = v_conv_2_1_bias depth = 160
    #pragma HLS INTERFACE m_axi port = dw_conv_2_1_filter depth = 1440
    #pragma HLS INTERFACE m_axi port = dw_norm_2_1_gamma depth = 160
    #pragma HLS INTERFACE m_axi port = dw_norm_2_1_beta depth = 160
    #pragma HLS INTERFACE m_axi port = dw_norm_2_1_mean depth = 160
    #pragma HLS INTERFACE m_axi port = dw_norm_2_1_var depth = 160
    #pragma HLS INTERFACE m_axi port = proj_2_1_weight depth = 7680
    
    // stage 2 depth 2
    #pragma HLS INTERFACE m_axi port = norm_2_2_weight depth = 48
    #pragma HLS INTERFACE m_axi port = norm_2_2_bias depth = 48
    #pragma HLS INTERFACE m_axi port = norm_2_2_running_mean depth = 48
    #pragma HLS INTERFACE m_axi port = norm_2_2_running_var depth = 48
    #pragma HLS INTERFACE m_axi port = v_conv_2_2_weight depth = 5760
    #pragma HLS INTERFACE m_axi port = v_conv_2_2_bias depth = 120
    #pragma HLS INTERFACE m_axi port = dw_conv_2_2_filter depth = 1080
    #pragma HLS INTERFACE m_axi port = dw_norm_2_2_gamma depth = 120
    #pragma HLS INTERFACE m_axi port = dw_norm_2_2_beta depth = 120
    #pragma HLS INTERFACE m_axi port = dw_norm_2_2_mean depth = 120
    #pragma HLS INTERFACE m_axi port = dw_norm_2_2_var depth = 120
    #pragma HLS INTERFACE m_axi port = proj_2_2_weight depth = 5760

    // in and out stage 0
    #pragma HLS INTERFACE m_axi port = Y_msp_conv depth = 301056 bundle = gmem1
    #pragma HLS INTERFACE m_axi port = Y_msp_norm depth = 301056 bundle = gmem2
    #pragma HLS INTERFACE m_axi port = Y_dw_conv depth = 301056 bundle = gmem3
    #pragma HLS INTERFACE m_axi port = Y_dw_norm depth = 301056 bundle = gmem0
    #pragma HLS INTERFACE m_axi port = Y_dw_act depth = 301056 bundle = gmem1
    #pragma HLS INTERFACE m_axi port = Y_se_mean depth = 24 bundle = gmem2 
    #pragma HLS INTERFACE m_axi port = Y_se_reduce depth = 24 bundle = gmem3
    #pragma HLS INTERFACE m_axi port = Y_se_act depth = 24 bundle = gmem0
    #pragma HLS INTERFACE m_axi port = Y_se_expand depth = 24 bundle = gmem1
    #pragma HLS INTERFACE m_axi port = Y_se_sigmoid depth = 24 bundle = gmem2
    #pragma HLS INTERFACE m_axi port = Y_se depth = 301056 bundle = gmem3
    #pragma HLS INTERFACE m_axi port = Y_proj depth = 301056 bundle = gmem0

    // in and out stage 1 depth 1
    #pragma HLS INTERFACE m_axi port = Y_norm_1_1 bundle = gmem1 depth = 301056
    #pragma HLS INTERFACE m_axi port = Y_v_conv_1_1 bundle = gmem2 depth = 1204224
    #pragma HLS INTERFACE m_axi port = Y_v_act_1_1 bundle = gmem3 depth = 1204224
    #pragma HLS INTERFACE m_axi port = Y_dw_conv_1_1 bundle = gmem0 depth = 301056
    #pragma HLS INTERFACE m_axi port = Y_dw_norm_1_1 bundle = gmem1 depth = 301056
    #pragma HLS INTERFACE m_axi port = Y_dw_act_1_1 bundle = gmem3 depth = 301056
    #pragma HLS INTERFACE m_axi port = Y_proj_1_1 bundle = gmem0 depth = 100352

    // in and out stage 1 depth 2
    #pragma HLS INTERFACE m_axi port = Y_norm_1_2 bundle = gmem2 depth = 100352
    #pragma HLS INTERFACE m_axi port = Y_v_conv_1_2 bundle = gmem1 depth = 200704
    #pragma HLS INTERFACE m_axi port = Y_v_act_1_2 bundle = gmem0 depth = 200704
    #pragma HLS INTERFACE m_axi port = Y_dw_conv_1_2 bundle = gmem3 depth = 200704
    #pragma HLS INTERFACE m_axi port = Y_dw_norm_1_2 bundle = gmem0 depth = 200704
    #pragma HLS INTERFACE m_axi port = Y_dw_act_1_2 bundle = gmem2 depth = 200704
    #pragma HLS INTERFACE m_axi port = Y_proj_1_2 bundle = gmem1 depth = 100352
    #pragma HLS INTERFACE m_axi port = Y_dw_skip_1_2 bundle = gmem3 depth = 200704
    #pragma HLS INTERFACE m_axi port = Y_skip_1_2 bundle = gmem2 depth = 100352

    // in and out stage 2 depth 1
    #pragma HLS INTERFACE m_axi port = Y_norm_2_1 bundle = gmem1 depth = 100352
    #pragma HLS INTERFACE m_axi port = Y_v_conv_2_1 bundle = gmem2 depth = 501760
    #pragma HLS INTERFACE m_axi port = Y_v_act_2_1 bundle = gmem3 depth = 501760
    #pragma HLS INTERFACE m_axi port = Y_dw_conv_2_1 bundle = gmem0 depth = 125440
    #pragma HLS INTERFACE m_axi port = Y_dw_norm_2_1 bundle = gmem1 depth = 125440
    #pragma HLS INTERFACE m_axi port = Y_dw_act_2_1 bundle = gmem3 depth = 125440
    #pragma HLS INTERFACE m_axi port = Y_proj_2_1 bundle = gmem0 depth = 37632

    // in and out stage 2 depth 2
    #pragma HLS INTERFACE m_axi port = Y_norm_2_2 bundle = gmem2 depth = 37632
    #pragma HLS INTERFACE m_axi port = Y_v_conv_2_2 bundle = gmem1 depth = 94080
    #pragma HLS INTERFACE m_axi port = Y_v_act_2_2 bundle = gmem0 depth = 94080
    #pragma HLS INTERFACE m_axi port = Y_dw_conv_2_2 bundle = gmem3 depth = 94080
    #pragma HLS INTERFACE m_axi port = Y_dw_norm_2_2 bundle = gmem0 depth = 94080
    #pragma HLS INTERFACE m_axi port = Y_dw_act_2_2 bundle = gmem2 depth = 94080
    #pragma HLS INTERFACE m_axi port = Y_proj_2_2 bundle = gmem1 depth = 37632
    #pragma HLS INTERFACE m_axi port = Y_dw_skip_2_2 bundle = gmem3 depth = 94080
    #pragma HLS INTERFACE m_axi port = Y_skip_2_2 bundle = gmem2 depth = 37632


    // // stage 1 depth 1
    // int norm_1_1_X_num[4] = {1, 24, 112, 112};
    // int v_conv_1_1_X_num[4] = {1, 96, 112, 112};
    // int dw_conv_1_1_shape_para[7] = {1, 96, 112, 112, 96, 56, 56};
    // int dw_conv_1_1_conv_para[6] = {3, 0, 2, 1, 96, 1};
    // int dw_1_1_X_num[4] = {1, 96, 56, 56};

    // // stage 1 depth 2
    // int norm_1_2_X_num[4] = {1, 32, 56, 56};
    // int v_conv_1_2_X_num[4] = {1, 64, 56, 56};
    // int dw_conv_1_2_shape_para[7] = {1, 64, 56, 56, 64, 56, 56};
    // int dw_conv_1_2_conv_para[6] = {3, 0, 1, 1, 64, 1};
    // int dw_1_2_X_num[4] = {1, 64, 56, 56};

    // // stage 2 depth 1
    // int norm_2_1_X_num[4] = {1, 32, 56, 56};
    // int v_conv_2_1_X_num[4] = {1, 160, 56, 56};
    // int dw_conv_2_1_shape_para[7] = {1, 160, 56, 56, 160, 28, 28};
    // int dw_conv_2_1_conv_para[6] = {3, 0, 2, 1, 160, 1};
    // int dw_2_1_X_num[4] = {1, 160, 28, 28};

    // // stage 2 depth 2
    // int norm_2_2_X_num[4] = {1, 48, 28, 28};
    // int v_conv_2_2_X_num[4] = {1, 120, 28, 28};
    // int dw_conv_2_2_shape_para[7] = {1, 120, 28, 28, 120, 28, 28};
    // int dw_conv_2_2_conv_para[6] = {3, 0, 1, 1, 120, 1};
    // int dw_2_2_X_num[4] = {1, 120, 28, 28};

    kernel_stage0(X_data, msp_conv_weight, msp_conv_bias, msp_norm_weight, msp_norm_bias, msp_norm_running_mean, msp_norm_running_var,
                  dw_conv_weight, dw_norm_gamma, dw_norm_beta, dw_norm_mean, dw_norm_var,
                  se_conv_reduce_weight, se_conv_reduce_bias, se_conv_expand_weight, se_conv_expand_bias,
                  proj_conv_weight, Y_msp_conv, Y_msp_norm, Y_dw_conv, Y_dw_norm, Y_dw_act, Y_se_mean, Y_se_reduce, 
                  Y_se_act, Y_se_expand, Y_se_sigmoid, Y_se, Y_proj);

    kernel_stage1(Y_proj, 
                  norm_1_1_weight, norm_1_1_bias, norm_1_1_running_mean, norm_1_1_running_var,
                  v_conv_1_1_weight, v_conv_1_1_bias,
                  dw_conv_1_1_filter, dw_norm_1_1_gamma, dw_norm_1_1_beta, dw_norm_1_1_mean, dw_norm_1_1_var,
                  proj_1_1_weight,
                  norm_1_2_weight, norm_1_2_bias, norm_1_2_running_mean, norm_1_2_running_var,
                  v_conv_1_2_weight, v_conv_1_2_bias,
                  dw_conv_1_2_filter, dw_norm_1_2_gamma, dw_norm_1_2_beta, dw_norm_1_2_mean, dw_norm_1_2_var,
                  proj_1_2_weight,
                  Y_norm_1_1, Y_v_conv_1_1, Y_v_act_1_1, Y_dw_conv_1_1, Y_dw_norm_1_1, Y_dw_act_1_1, Y_proj_1_1,
                  Y_norm_1_2, Y_v_conv_1_2, Y_v_act_1_2, Y_dw_conv_1_2, Y_dw_norm_1_2, Y_dw_act_1_2, Y_proj_1_2,
                  Y_dw_skip_1_2, Y_skip_1_2
                 );

    kernel_stage2(Y_skip_1_2,
                  norm_2_1_weight, norm_2_1_bias, norm_2_1_running_mean, norm_2_1_running_var,
                  v_conv_2_1_weight, v_conv_2_1_bias,
                  dw_conv_2_1_filter, dw_norm_2_1_gamma, dw_norm_2_1_beta, dw_norm_2_1_mean, dw_norm_2_1_var,
                  proj_2_1_weight,
                  norm_2_2_weight, norm_2_2_bias, norm_2_2_running_mean, norm_2_2_running_var,
                  v_conv_2_2_weight, v_conv_2_2_bias,
                  dw_conv_2_2_filter, dw_norm_2_2_gamma, dw_norm_2_2_beta, dw_norm_2_2_mean, dw_norm_2_2_var,
                  proj_2_2_weight,
                  Y_norm_2_1, Y_v_conv_2_1, Y_v_act_2_1, Y_dw_conv_2_1, Y_dw_norm_2_1, Y_dw_act_2_1, Y_proj_2_1,
                  Y_norm_2_2, Y_v_conv_2_2, Y_v_act_2_2, Y_dw_conv_2_2, Y_dw_norm_2_2, Y_dw_act_2_2, Y_proj_2_2,
                  Y_dw_skip_2_2, Y_skip_2_2
                  );
    }
}