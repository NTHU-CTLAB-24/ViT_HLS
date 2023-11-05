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
                    float* Y_dw_skip_2_2, float* Y_skip_2_2,
                    float* norm_0_weight_3, float* norm_0_bias_3, float* v_conv_0_weight_3, float* v_conv_0_bias_3,
                    float* dw_conv_0_filter_3, float* dw_norm_0_weight_3, float* dw_norm_0_bias_3, float* dw_norm_0_mean_3, float* dw_norm_0_var_3,
                    float* proj_0_weight_3, float* Y_norm_0_3, float* Y_v_conv_0_3, float* Y_v_act_0_3, float* Y_dw_conv_0_3, float* Y_dw_norm_0_3, float* Y_dw_act_0_3,
                    float* result_30, float *afterNorm_3,
                    float *norm1_mean_3, float *norm1_var_3, float *norm1_weight_3, float *norm1_bias_3, 
                    float *afterRearrangeX_3,
                    float *afterConv1_3,
                    float *kernel1_3,
                    float *bias1_3,
                    float *in_q_3,
                    float *in_k_3,
                    float *afterQKMultiplication_3,
                    float *afterSoftmax_3,
                    float *afterRearrangeX2_3,
                    float *afterQKXMultiplication_3,
                    float *afterRearrangeQKX_3,
                    float *afterConv2_3,
                    float *kernel2_3,
                    float *bias2_3,
                    float *afterAct2_3,
                    float *buffer_out_3,
                    float *buffer_result_3,
                    float* dw_conv_1_filter_3, float* dw_norm_1_weight_3, float* dw_norm_1_bias_3, float* dw_norm_1_mean_3, float* dw_norm_1_var_3,
                    float* proj_1_weight_3,
                    float* Y_dw_conv_1_3, float* Y_dw_norm_1_3, float* Y_dw_act_1_3, float* Y_proj_1_3,
                    float* Y_dw_skip_1_3, float* Y_skip_1_3,
                    float* norm_0_weight_4, float* norm_0_bias_4, float* v_conv_0_weight_4, float* v_conv_0_bias_4,
                    float* dw_conv_0_filter_4, float* dw_norm_0_weight_4, float* dw_norm_0_bias_4, float* dw_norm_0_mean_4, float* dw_norm_0_var_4,
                    float* proj_0_weight_4, float* Y_norm_0_4, float* Y_v_conv_0_4, float* Y_v_act_0_4, float* Y_dw_conv_0_4, float* Y_dw_norm_0_4, float* Y_dw_act_0_4,
                    float* result_40, float *afterNorm_4,
                    float *norm1_mean_4, float *norm1_var_4, float *norm1_weight_4, float *norm1_bias_4, 
                    float *afterRearrangeX_4,
                    float *afterConv1_4,
                    float *kernel1_4,
                    float *bias1_4,
                    float *in_q_4,
                    float *in_k_4,
                    float *afterQKMultiplication_4,
                    float *afterSoftmax_4,
                    float *afterRearrangeX2_4,
                    float *afterQKXMultiplication_4,
                    float *afterRearrangeQKX_4,
                    float *afterConv2_4,
                    float *kernel2_4,
                    float *bias2_4,
                    float *afterAct2_4,
                    float *buffer_out_4,
                    float *buffer_result_4,
                    float* dw_conv_1_filter_4, float* dw_norm_1_weight_4, float* dw_norm_1_bias_4, float* dw_norm_1_mean_4, float* dw_norm_1_var_4,
                    float* proj_1_weight_4,
                    float* Y_dw_conv_1_4, float* Y_dw_norm_1_4, float* Y_dw_act_1_4, float* Y_proj_1_4,
                    float* Y_dw_skip_1_4, float* Y_skip_1_4,
                    float* Y_linear_norm, float* linear_norm_mean, float* linear_norm_var, float* linear_norm_weight, float* linear_norm_bias,
                    float* Y_linear_reduce, float* linear_weight, float* linear_bias, float* Y_out
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

    // stage 3 depth 0
    #pragma HLS INTERFACE m_axi port = norm_0_weight_3 depth = 48
    #pragma HLS INTERFACE m_axi port = norm_0_bias_3 depth = 48

    #pragma HLS INTERFACE m_axi port = v_conv_0_weight_3 depth = 13824
    #pragma HLS INTERFACE m_axi port = v_conv_0_bias_3 depth = 288

    #pragma HLS INTERFACE m_axi port = dw_conv_0_filter_3 depth = 7200
    #pragma HLS INTERFACE m_axi port = dw_norm_0_weight_3 depth = 288
    #pragma HLS INTERFACE m_axi port = dw_norm_0_bias_3 depth = 288
    #pragma HLS INTERFACE m_axi port = dw_norm_0_mean_3 depth = 288
    #pragma HLS INTERFACE m_axi port = dw_norm_0_var_3 depth = 288
    
    #pragma HLS INTERFACE m_axi port = proj_0_weight_3 depth = 23040//288*80
    

    #pragma HLS INTERFACE m_axi port = Y_norm_0_3 bundle = gmem1 depth = 37632
    #pragma HLS INTERFACE m_axi port = Y_v_conv_0_3 bundle = gmem2 depth = 225792
    #pragma HLS INTERFACE m_axi port = Y_v_act_0_3 bundle = gmem3 depth = 225792
    #pragma HLS INTERFACE m_axi port = Y_dw_conv_0_3 bundle = gmem0 depth = 56448
    #pragma HLS INTERFACE m_axi port = Y_dw_norm_0_3 bundle = gmem1 depth = 56448
    #pragma HLS INTERFACE m_axi port = Y_dw_act_0_3 bundle = gmem3 depth = 56448
    #pragma HLS INTERFACE m_axi port = result_30 bundle = gmem0 depth = 15680

    //stage 3 depth1-7
    #pragma HLS INTERFACE m_axi port = afterNorm_3 bundle = gmem1 depth = 15680
    #pragma HLS INTERFACE m_axi port = norm1_mean_3 depth = 196 //*7
    #pragma HLS INTERFACE m_axi port = norm1_var_3 depth = 196 //*7
    #pragma HLS INTERFACE m_axi port = norm1_weight_3 depth = 80*7
    #pragma HLS INTERFACE m_axi port = norm1_bias_3 depth = 80*7

    #pragma HLS INTERFACE m_axi port = afterRearrangeX_3 depth = 15680
    #pragma HLS INTERFACE m_axi port = afterConv1_3 depth = 31360

    #pragma HLS INTERFACE m_axi port = kernel1_3 depth = 12800*7
    #pragma HLS INTERFACE m_axi port = bias1_3 depth = 160*7
    #pragma HLS INTERFACE m_axi port = in_q_3 depth = 15680
    #pragma HLS INTERFACE m_axi port = in_k_3 depth = 15680
    #pragma HLS INTERFACE m_axi port = afterQKMultiplication_3 depth = 38416
    #pragma HLS INTERFACE m_axi port = afterSoftmax_3 depth = 38416
    #pragma HLS INTERFACE m_axi port = afterRearrangeX2_3 depth = 15680
    #pragma HLS INTERFACE m_axi port = afterQKXMultiplication_3 depth = 15680
    #pragma HLS INTERFACE m_axi port = afterRearrangeQKX_3 depth = 15680
    #pragma HLS INTERFACE m_axi port = afterConv2_3 depth = 47040

    #pragma HLS INTERFACE m_axi port = kernel2_3 depth = 19200*7
    #pragma HLS INTERFACE m_axi port = bias2_3 depth = 240*7

    #pragma HLS INTERFACE m_axi port = afterAct2_3 depth = 47040
    #pragma HLS INTERFACE m_axi port = buffer_out_3 depth = 47040
    #pragma HLS INTERFACE m_axi port = buffer_result_3 bundle  = gmem0 depth = 47040

    #pragma HLS INTERFACE m_axi port = dw_conv_1_filter_3 depth = 6000*7 //25*240
    #pragma HLS INTERFACE m_axi port = dw_norm_1_weight_3 depth = 240*7
    #pragma HLS INTERFACE m_axi port = dw_norm_1_bias_3 depth = 240*7
    #pragma HLS INTERFACE m_axi port = dw_norm_1_mean_3 depth = 240*7
    #pragma HLS INTERFACE m_axi port = dw_norm_1_var_3 depth = 240*7
    #pragma HLS INTERFACE m_axi port = proj_1_weight_3 depth = 19200*7

    #pragma HLS INTERFACE m_axi port = Y_dw_conv_1_3 bundle = gmem3 depth = 47040
    #pragma HLS INTERFACE m_axi port = Y_dw_norm_1_3 bundle = gmem0 depth = 47040
    #pragma HLS INTERFACE m_axi port = Y_dw_act_1_3 bundle = gmem2 depth = 47040
    #pragma HLS INTERFACE m_axi port = Y_proj_1_3 bundle = gmem1 depth = 15680
    #pragma HLS INTERFACE m_axi port = Y_dw_skip_1_3 bundle = gmem3 depth = 47040
    #pragma HLS INTERFACE m_axi port = Y_skip_1_3 bundle = gmem2 depth = 15680

    // stage 4 depth 0
    #pragma HLS INTERFACE m_axi port = norm_0_weight_4 depth = 80
    #pragma HLS INTERFACE m_axi port = norm_0_bias_4 depth = 80

    #pragma HLS INTERFACE m_axi port = v_conv_0_weight_4 depth = 44800
    #pragma HLS INTERFACE m_axi port = v_conv_0_bias_4 depth = 560

    #pragma HLS INTERFACE m_axi port = dw_conv_0_filter_4 depth = 14000
    #pragma HLS INTERFACE m_axi port = dw_norm_0_weight_4 depth = 560
    #pragma HLS INTERFACE m_axi port = dw_norm_0_bias_4 depth = 560
    #pragma HLS INTERFACE m_axi port = dw_norm_0_mean_4 depth = 560
    #pragma HLS INTERFACE m_axi port = dw_norm_0_var_4 depth = 560
    
    #pragma HLS INTERFACE m_axi port = proj_0_weight_4 depth = 94080//560*168

    #pragma HLS INTERFACE m_axi port = Y_norm_0_4 bundle = gmem1 depth = 15680
    #pragma HLS INTERFACE m_axi port = Y_v_conv_0_4 bundle = gmem2 depth = 109760
    #pragma HLS INTERFACE m_axi port = Y_v_act_0_4 bundle = gmem3 depth = 109760
    #pragma HLS INTERFACE m_axi port = Y_dw_conv_0_4 bundle = gmem0 depth = 27440
    #pragma HLS INTERFACE m_axi port = Y_dw_norm_0_4 bundle = gmem1 depth = 27440
    #pragma HLS INTERFACE m_axi port = Y_dw_act_0_4 bundle = gmem3 depth = 27440
    #pragma HLS INTERFACE m_axi port = result_40 bundle = gmem0 depth = 8232

    //stage 4 depth1-2
    #pragma HLS INTERFACE m_axi port = afterNorm_4 bundle = gmem1 depth = 8232
    #pragma HLS INTERFACE m_axi port = norm1_mean_4 depth = 49 //*2 //*7
    #pragma HLS INTERFACE m_axi port = norm1_var_4 depth = 49 //*2 //*7
    #pragma HLS INTERFACE m_axi port = norm1_weight_4 depth = 168*2
    #pragma HLS INTERFACE m_axi port = norm1_bias_4 depth = 168*2

    #pragma HLS INTERFACE m_axi port = afterRearrangeX_4 depth = 8232
    #pragma HLS INTERFACE m_axi port = afterConv1_4 depth = 16464

    #pragma HLS INTERFACE m_axi port = kernel1_4 depth = 56448*2
    #pragma HLS INTERFACE m_axi port = bias1_4 depth = 336*2
    #pragma HLS INTERFACE m_axi port = in_q_4 depth = 8232
    #pragma HLS INTERFACE m_axi port = in_k_4 depth = 8232
    #pragma HLS INTERFACE m_axi port = afterQKMultiplication_4 depth = 19208 //2401
    #pragma HLS INTERFACE m_axi port = afterSoftmax_4 depth = 19208 //2401
    #pragma HLS INTERFACE m_axi port = afterRearrangeX2_4 depth = 8232
    #pragma HLS INTERFACE m_axi port = afterQKXMultiplication_4 depth = 8232
    #pragma HLS INTERFACE m_axi port = afterRearrangeQKX_4 depth = 8232
    #pragma HLS INTERFACE m_axi port = afterConv2_4 depth = 28812

    #pragma HLS INTERFACE m_axi port = kernel2_4 depth = 98784*2
    #pragma HLS INTERFACE m_axi port = bias2_4 depth = 588*2

    #pragma HLS INTERFACE m_axi port = afterAct2_4 depth = 28812
    #pragma HLS INTERFACE m_axi port = buffer_out_4 depth = 28812
    #pragma HLS INTERFACE m_axi port = buffer_result_4 bundle  = gmem0 depth = 28812

    #pragma HLS INTERFACE m_axi port = dw_conv_1_filter_4 depth = 14700*2 //25*588
    #pragma HLS INTERFACE m_axi port = dw_norm_1_weight_4 depth = 588*2
    #pragma HLS INTERFACE m_axi port = dw_norm_1_bias_4 depth = 588*2
    #pragma HLS INTERFACE m_axi port = dw_norm_1_mean_4 depth = 588*2
    #pragma HLS INTERFACE m_axi port = dw_norm_1_var_4 depth = 588*2
    #pragma HLS INTERFACE m_axi port = proj_1_weight_4 depth = 98784*2

    #pragma HLS INTERFACE m_axi port = Y_dw_conv_1_4 bundle = gmem3 depth = 28812
    #pragma HLS INTERFACE m_axi port = Y_dw_norm_1_4 bundle = gmem0 depth = 28812
    #pragma HLS INTERFACE m_axi port = Y_dw_act_1_4 bundle = gmem2 depth = 28812
    #pragma HLS INTERFACE m_axi port = Y_proj_1_4 bundle = gmem1 depth = 8232
    #pragma HLS INTERFACE m_axi port = Y_dw_skip_1_4 bundle = gmem3 depth = 28812
    #pragma HLS INTERFACE m_axi port = Y_skip_1_4 bundle = gmem2 depth = 8232

    #pragma HLS INTERFACE m_axi port = linear_norm_mean depth = 49
    #pragma HLS INTERFACE m_axi port = linear_norm_var depth = 49
    #pragma HLS INTERFACE m_axi port = linear_norm_weight depth = 168
    #pragma HLS INTERFACE m_axi port = linear_norm_bias depth = 168
    #pragma HLS INTERFACE m_axi port = Y_linear_norm bundle = gmem0 depth = 8232
    
    #pragma HLS INTERFACE m_axi port = Y_linear_reduce bundle = gmem1 depth = 168
    #pragma HLS INTERFACE m_axi port = linear_weight depth = 168000
    #pragma HLS INTERFACE m_axi port = linear_bias depth = 1000
    #pragma HLS INTERFACE m_axi port = Y_out bundle = gmem2 depth = 1000

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

    kernel_stage3(Y_skip_2_2, norm_0_weight_3, norm_0_bias_3, v_conv_0_weight_3, v_conv_0_bias_3,
                 dw_conv_0_filter_3, dw_norm_0_weight_3, dw_norm_0_bias_3, dw_norm_0_mean_3, dw_norm_0_var_3,
                 proj_0_weight_3, Y_norm_0_3, Y_v_conv_0_3, Y_v_act_0_3, Y_dw_conv_0_3, Y_dw_norm_0_3, Y_dw_act_0_3,
                 result_30, afterNorm_3,
                 norm1_mean_3, norm1_var_3, norm1_weight_3, norm1_bias_3,
                 afterRearrangeX_3,
                 afterConv1_3,
                 kernel1_3,
                 bias1_3,
                 in_q_3,
                 in_k_3,
                 afterQKMultiplication_3,
                 afterSoftmax_3,
                 afterRearrangeX2_3,
                 afterQKXMultiplication_3,
                 afterRearrangeQKX_3,
                 afterConv2_3,
                 kernel2_3,
                 bias2_3,
                 afterAct2_3,
                 buffer_out_3,
                 buffer_result_3,
                 dw_conv_1_filter_3, dw_norm_1_weight_3, dw_norm_1_bias_3, dw_norm_1_mean_3, dw_norm_1_var_3,
                 proj_1_weight_3, Y_dw_conv_1_3, Y_dw_norm_1_3, Y_dw_act_1_3, Y_proj_1_3,
                 Y_dw_skip_1_3, Y_skip_1_3
                 );
    kernel_stage4(Y_skip_1_3, norm_0_weight_4, norm_0_bias_4, v_conv_0_weight_4, v_conv_0_bias_4,
                 dw_conv_0_filter_4, dw_norm_0_weight_4, dw_norm_0_bias_4, dw_norm_0_mean_4, dw_norm_0_var_4,
                 proj_0_weight_4, Y_norm_0_4, Y_v_conv_0_4, Y_v_act_0_4, Y_dw_conv_0_4, Y_dw_norm_0_4, Y_dw_act_0_4,
                 result_40, afterNorm_4,
                 norm1_mean_4, norm1_var_4, norm1_weight_4, norm1_bias_4,
                 afterRearrangeX_4,
                 afterConv1_4,
                 kernel1_4,
                 bias1_4,
                 in_q_4,
                 in_k_4,
                 afterQKMultiplication_4,
                 afterSoftmax_4,
                 afterRearrangeX2_4,
                 afterQKXMultiplication_4,
                 afterRearrangeQKX_4,
                 afterConv2_4,
                 kernel2_4,
                 bias2_4,
                 afterAct2_4,
                 buffer_out_4,
                 buffer_result_4,
                 dw_conv_1_filter_4, dw_norm_1_weight_4, dw_norm_1_bias_4, dw_norm_1_mean_4, dw_norm_1_var_4,
                 proj_1_weight_4, Y_dw_conv_1_4, Y_dw_norm_1_4, Y_dw_act_1_4, Y_proj_1_4,
                 Y_dw_skip_1_4, Y_skip_1_4
                 );
    kernel_linear(Y_skip_1_4, Y_linear_norm, linear_norm_mean, linear_norm_var, linear_norm_weight, linear_norm_bias,
                  Y_linear_reduce, linear_weight, linear_bias, Y_out);
    }
}