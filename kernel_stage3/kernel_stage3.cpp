// Includes
#include <hls_math.h>
#include <hls_stream.h>
#include <stdint.h>
#include "kernel_stage3.hpp"

extern "C"
{
    void kernel_stage3(float* X_data, float* norm_0_weight_3, float* norm_0_bias_3, float* v_conv_0_weight_3, float* v_conv_0_bias_3,
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
                        float* Y_dw_skip_1_3, float* Y_skip_1_3)
{

    #pragma HLS INTERFACE m_axi port = X_data bundle = gmem0 depth = 37632

    // depth 0
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
    #pragma HLS INTERFACE m_axi port = Y_dw_conv_0_3 bundle = gmem0 depth = 37632
    #pragma HLS INTERFACE m_axi port = Y_dw_norm_0_3 bundle = gmem1 depth = 37632
    #pragma HLS INTERFACE m_axi port = Y_dw_act_0_3 bundle = gmem3 depth = 37632
    #pragma HLS INTERFACE m_axi port = result_30 bundle = gmem0 depth = 15680

    //depth1-7
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

    // depth 0
    int norm_0_X_num[4] = {1, 48, 28, 28};
    int v_conv_0_X_num[4] = {1, 288, 28, 28};
    int dw_conv_0_shape_para[7] = {1, 288, 28, 28, 288, 14, 14};
    int dw_conv_0_conv_para[6] = {5, 0, 2, 2, 288, 1};
    int dw_0_X_num[4] = {1, 288, 14, 14};

    float mean_buf_0[784];
    #pragma HLS array_partition variable = mean_buf_0 complete dim = 1 
    float var_buf_0[784];
    #pragma HLS array_partition variable = var_buf_0 complete dim = 1 

    LayerNorm(X_data, Y_norm_0_3, norm_0_X_num, mean_buf_0, var_buf_0, norm_0_weight_3, norm_0_bias_3);
    Pointwise_conv(Y_norm_0_3, Y_v_conv_0_3, v_conv_0_weight_3, v_conv_0_bias_3, 1, 48, 288, 28, 28, 1);
    GeLU(Y_v_conv_0_3, Y_v_act_0_3, v_conv_0_X_num);
    DW_conv(Y_v_act_0_3, dw_conv_0_filter_3, nullptr, dw_conv_0_shape_para, dw_conv_0_conv_para, Y_dw_conv_0_3);
    BatchNorm(Y_dw_conv_0_3, Y_dw_norm_0_3, dw_0_X_num, dw_norm_0_mean_3, dw_norm_0_var_3, dw_norm_0_weight_3, dw_norm_0_bias_3);
    SiLU(Y_dw_norm_0_3, Y_dw_act_0_3, dw_0_X_num);
    // self.proj
    Pointwise_conv(Y_dw_act_0_3, result_30, proj_0_weight_3, nullptr, 1, 288, 80, 14, 14, 0);

    
    // depth 1-7
    int norm_1_X_num[4] = {1, 80, 14, 14};
    int dw_conv_1_shape_para[7] = {1, 240, 14, 14, 240, 14, 14};
    int dw_conv_1_conv_para[6] = {5, 0, 1, 2, 240, 1};
    int dw_1_X_num[4] = {1, 240, 14, 14};
    
    //float norm1_mean_l1[196], norm1_mean_l2[196], norm1_mean_l3[196], norm1_mean_l4[196], norm1_mean_l5[196], norm1_mean_l6[196], norm1_mean_l7[196];
    //float norm1_var_l1[196], norm1_var_l2[196], norm1_var_l3[196], norm1_var_l4[196], norm1_var_l5[196], norm1_var_l6[196], norm1_var_l7[196];
    float norm1_weight_l1[80], norm1_weight_l2[80], norm1_weight_l3[80], norm1_weight_l4[80], norm1_weight_l5[80], norm1_weight_l6[80], norm1_weight_l7[80];
    float norm1_bias_l1[80], norm1_bias_l2[80], norm1_bias_l3[80], norm1_bias_l4[80], norm1_bias_l5[80], norm1_bias_l6[80], norm1_bias_l7[80];
    
    float kernel1_l1[12800], kernel1_l2[12800], kernel1_l3[12800], kernel1_l4[12800], kernel1_l5[12800], kernel1_l6[12800], kernel1_l7[12800];
    float bias1_l1[160], bias1_l2[160], bias1_l3[160], bias1_l4[160], bias1_l5[160], bias1_l6[160], bias1_l7[160];
    float kernel2_l1[19200], kernel2_l2[19200], kernel2_l3[19200], kernel2_l4[19200], kernel2_l5[19200], kernel2_l6[19200], kernel2_l7[19200];
    float bias2_l1[240], bias2_l2[240], bias2_l3[240], bias2_l4[240], bias2_l5[240], bias2_l6[240], bias2_l7[240];

    float dw_conv_1_filter_l1[6000], dw_conv_1_filter_l2[6000], dw_conv_1_filter_l3[6000], dw_conv_1_filter_l4[6000], dw_conv_1_filter_l5[6000], dw_conv_1_filter_l6[6000], dw_conv_1_filter_l7[6000];
    float dw_norm_1_weight_l1[240], dw_norm_1_weight_l2[240], dw_norm_1_weight_l3[240], dw_norm_1_weight_l4[240], dw_norm_1_weight_l5[240], dw_norm_1_weight_l6[240], dw_norm_1_weight_l7[240];
    float dw_norm_1_bias_l1[240], dw_norm_1_bias_l2[240], dw_norm_1_bias_l3[240], dw_norm_1_bias_l4[240], dw_norm_1_bias_l5[240], dw_norm_1_bias_l6[240], dw_norm_1_bias_l7[240];
    float dw_norm_1_mean_l1[240], dw_norm_1_mean_l2[240], dw_norm_1_mean_l3[240], dw_norm_1_mean_l4[240], dw_norm_1_mean_l5[240], dw_norm_1_mean_l6[240], dw_norm_1_mean_l7[240];
    float dw_norm_1_var_l1[240], dw_norm_1_var_l2[240], dw_norm_1_var_l3[240], dw_norm_1_var_l4[240], dw_norm_1_var_l5[240], dw_norm_1_var_l6[240], dw_norm_1_var_l7[240];
    
    float proj_1_weight_l1[19200], proj_1_weight_l2[19200], proj_1_weight_l3[19200], proj_1_weight_l4[19200], proj_1_weight_l5[19200], proj_1_weight_l6[19200], proj_1_weight_l7[19200];
    
    float iRMB_out1[15680], iRMB_out2[15680], iRMB_out3[15680], iRMB_out4[15680], iRMB_out5[15680], iRMB_out6[15680];
    //split_data_to7(norm1_mean_3, norm1_mean_l1, norm1_mean_l2, norm1_mean_l3, norm1_mean_l4, norm1_mean_l5, norm1_mean_l6, norm1_mean_l7, 196);
    //split_data_to7(norm1_var_3, norm1_var_l1, norm1_var_l2, norm1_var_l3, norm1_var_l4, norm1_var_l5, norm1_var_l6, norm1_var_l7, 196);
    split_data_to7(norm1_weight_3, norm1_weight_l1, norm1_weight_l2, norm1_weight_l3, norm1_weight_l4, norm1_weight_l5, norm1_weight_l6, norm1_weight_l7, 80);
    split_data_to7(norm1_bias_3, norm1_bias_l1, norm1_bias_l2, norm1_bias_l3, norm1_bias_l4, norm1_bias_l5, norm1_bias_l6, norm1_bias_l7, 80);
    
    split_data_to7(kernel1_3, kernel1_l1, kernel1_l2, kernel1_l3, kernel1_l4, kernel1_l5, kernel1_l6, kernel1_l7, 12800);
    split_data_to7(bias1_3, bias1_l1, bias1_l2, bias1_l3, bias1_l4, bias1_l5, bias1_l6, bias1_l7, 160);
    split_data_to7(kernel2_3, kernel2_l1, kernel2_l2, kernel2_l3, kernel2_l4, kernel2_l5, kernel2_l6, kernel2_l7, 19200);
    split_data_to7(bias2_3, bias2_l1, bias2_l2, bias2_l3, bias2_l4, bias2_l5, bias2_l6, bias2_l7, 240);

    split_data_to7(dw_conv_1_filter_3, dw_conv_1_filter_l1, dw_conv_1_filter_l2, dw_conv_1_filter_l3, dw_conv_1_filter_l4, dw_conv_1_filter_l5, dw_conv_1_filter_l6, dw_conv_1_filter_l7, 6000);
    split_data_to7(dw_norm_1_weight_3, dw_norm_1_weight_l1, dw_norm_1_weight_l2, dw_norm_1_weight_l3, dw_norm_1_weight_l4, dw_norm_1_weight_l5, dw_norm_1_weight_l6, dw_norm_1_weight_l7, 240);
    split_data_to7(dw_norm_1_bias_3, dw_norm_1_bias_l1, dw_norm_1_bias_l2, dw_norm_1_bias_l3, dw_norm_1_bias_l4, dw_norm_1_bias_l5, dw_norm_1_bias_l6, dw_norm_1_bias_l7, 240);
    split_data_to7(dw_norm_1_mean_3, dw_norm_1_mean_l1, dw_norm_1_mean_l2, dw_norm_1_mean_l3, dw_norm_1_mean_l4, dw_norm_1_mean_l5, dw_norm_1_mean_l6, dw_norm_1_mean_l7, 240);
    split_data_to7(dw_norm_1_var_3, dw_norm_1_var_l1, dw_norm_1_var_l2, dw_norm_1_var_l3, dw_norm_1_var_l4, dw_norm_1_var_l5, dw_norm_1_var_l6, dw_norm_1_var_l7, 240);

    split_data_to7(proj_1_weight_3, proj_1_weight_l1, proj_1_weight_l2, proj_1_weight_l3, proj_1_weight_l4, proj_1_weight_l5, proj_1_weight_l6, proj_1_weight_l7, 19200);
    float afterNorm_l2[15680];
    float afterPad_l2[15680];

    // depth 1
    kernel_attention(result_30,
                    afterNorm_3,
                    norm1_mean_3, norm1_var_3, norm1_weight_l1, norm1_bias_l1,
                    afterRearrangeX_3,
                    afterConv1_3,
                    kernel1_l1, bias1_l1,
                    in_q_3, in_k_3,
                    afterQKMultiplication_3,
                    afterSoftmax_3,
                    afterRearrangeX2_3,
                    afterQKXMultiplication_3,
                    afterRearrangeQKX_3,
                    afterConv2_3,
                    kernel2_l1, bias2_l1,
                    afterAct2_3,
                    buffer_out_3,
                    buffer_result_3
                    );
    DW_conv(buffer_result_3, dw_conv_1_filter_l1, nullptr, dw_conv_1_shape_para, dw_conv_1_conv_para, Y_dw_conv_1_3);
    BatchNorm(Y_dw_conv_1_3, Y_dw_norm_1_3, dw_1_X_num, dw_norm_1_mean_l1, dw_norm_1_var_l1, dw_norm_1_weight_l1, dw_norm_1_bias_l1);
    SiLU(Y_dw_norm_1_3, Y_dw_act_1_3, dw_1_X_num);
    Compute_skip(buffer_result_3, Y_dw_act_1_3, Y_dw_skip_1_3, dw_1_X_num);
    Pointwise_conv(Y_dw_skip_1_3, Y_proj_1_3, proj_1_weight_l1, nullptr, 1, 240, 80, 14, 14, 0);
    Compute_skip(result_30, Y_proj_1_3, iRMB_out1, norm_1_X_num);
    clear_data(
        afterNorm_3,afterRearrangeX_3, afterConv1_3,
        in_q_3, in_k_3,
        afterQKMultiplication_3, afterSoftmax_3, afterRearrangeX2_3, afterQKXMultiplication_3,
        afterRearrangeQKX_3, afterConv2_3, afterAct2_3,
        buffer_out_3, buffer_result_3,
         Y_dw_conv_1_3,  Y_dw_norm_1_3,  Y_dw_act_1_3,  Y_proj_1_3,  Y_dw_skip_1_3
    );

    // depth 2
    kernel_attention(iRMB_out1,
                    afterNorm_3,
                    norm1_mean_3, norm1_var_3, norm1_weight_l2, norm1_bias_l2,
                    afterRearrangeX_3,
                    afterConv1_3,
                    kernel1_l2, bias1_l2,
                    in_q_3, in_k_3,
                    afterQKMultiplication_3,
                    afterSoftmax_3,
                    afterRearrangeX2_3,
                    afterQKXMultiplication_3,
                    afterRearrangeQKX_3,
                    afterConv2_3,
                    kernel2_l2, bias2_l2,
                    afterAct2_3,
                    buffer_out_3,
                    buffer_result_3
                    );
    DW_conv(buffer_result_3, dw_conv_1_filter_l2, nullptr, dw_conv_1_shape_para, dw_conv_1_conv_para, Y_dw_conv_1_3);
    BatchNorm(Y_dw_conv_1_3, Y_dw_norm_1_3, dw_1_X_num, dw_norm_1_mean_l2, dw_norm_1_var_l2, dw_norm_1_weight_l2, dw_norm_1_bias_l2);
    SiLU(Y_dw_norm_1_3, Y_dw_act_1_3, dw_1_X_num);
    Compute_skip(buffer_result_3, Y_dw_act_1_3, Y_dw_skip_1_3, dw_1_X_num);
    Pointwise_conv(Y_dw_skip_1_3, Y_proj_1_3, proj_1_weight_l2, nullptr, 1, 240, 80, 14, 14, 0);
    Compute_skip(iRMB_out1, Y_proj_1_3, iRMB_out2, norm_1_X_num);
    clear_data(
        afterNorm_3,afterRearrangeX_3, afterConv1_3,
        in_q_3, in_k_3,
        afterQKMultiplication_3, afterSoftmax_3, afterRearrangeX2_3, afterQKXMultiplication_3,
        afterRearrangeQKX_3, afterConv2_3, afterAct2_3,
        buffer_out_3, buffer_result_3,
         Y_dw_conv_1_3,  Y_dw_norm_1_3,  Y_dw_act_1_3,  Y_proj_1_3,  Y_dw_skip_1_3
    );

    // depth 3
    kernel_attention(iRMB_out2,
                    afterNorm_3,
                    norm1_mean_3, norm1_var_3, norm1_weight_l3, norm1_bias_l3,
                    afterRearrangeX_3,
                    afterConv1_3,
                    kernel1_l3, bias1_l3,
                    in_q_3, in_k_3,
                    afterQKMultiplication_3,
                    afterSoftmax_3,
                    afterRearrangeX2_3,
                    afterQKXMultiplication_3,
                    afterRearrangeQKX_3,
                    afterConv2_3,
                    kernel2_l3, bias2_l3,
                    afterAct2_3,
                    buffer_out_3,
                    buffer_result_3
                    );
    DW_conv(buffer_result_3, dw_conv_1_filter_l3, nullptr, dw_conv_1_shape_para, dw_conv_1_conv_para, Y_dw_conv_1_3);
    BatchNorm(Y_dw_conv_1_3, Y_dw_norm_1_3, dw_1_X_num, dw_norm_1_mean_l3, dw_norm_1_var_l3, dw_norm_1_weight_l3, dw_norm_1_bias_l3);
    SiLU(Y_dw_norm_1_3, Y_dw_act_1_3, dw_1_X_num);
    Compute_skip(buffer_result_3, Y_dw_act_1_3, Y_dw_skip_1_3, dw_1_X_num);
    Pointwise_conv(Y_dw_skip_1_3, Y_proj_1_3, proj_1_weight_l3, nullptr, 1, 240, 80, 14, 14, 0);
    Compute_skip(iRMB_out2, Y_proj_1_3, iRMB_out3, norm_1_X_num);
    clear_data(
        afterNorm_3,afterRearrangeX_3, afterConv1_3,
        in_q_3, in_k_3,
        afterQKMultiplication_3, afterSoftmax_3, afterRearrangeX2_3, afterQKXMultiplication_3,
        afterRearrangeQKX_3, afterConv2_3, afterAct2_3,
        buffer_out_3, buffer_result_3,
         Y_dw_conv_1_3,  Y_dw_norm_1_3,  Y_dw_act_1_3,  Y_proj_1_3,  Y_dw_skip_1_3
    );

    // depth 4
    kernel_attention(iRMB_out3,
                    afterNorm_3,
                    norm1_mean_3, norm1_var_3, norm1_weight_l4, norm1_bias_l4,
                    afterRearrangeX_3,
                    afterConv1_3,
                    kernel1_l4, bias1_l4,
                    in_q_3, in_k_3,
                    afterQKMultiplication_3,
                    afterSoftmax_3,
                    afterRearrangeX2_3,
                    afterQKXMultiplication_3,
                    afterRearrangeQKX_3,
                    afterConv2_3,
                    kernel2_l4, bias2_l4,
                    afterAct2_3,
                    buffer_out_3,
                    buffer_result_3
                    );
    DW_conv(buffer_result_3, dw_conv_1_filter_l4, nullptr, dw_conv_1_shape_para, dw_conv_1_conv_para, Y_dw_conv_1_3);
    BatchNorm(Y_dw_conv_1_3, Y_dw_norm_1_3, dw_1_X_num, dw_norm_1_mean_l4, dw_norm_1_var_l4, dw_norm_1_weight_l4, dw_norm_1_bias_l4);
    SiLU(Y_dw_norm_1_3, Y_dw_act_1_3, dw_1_X_num);
    Compute_skip(buffer_result_3, Y_dw_act_1_3, Y_dw_skip_1_3, dw_1_X_num);
    Pointwise_conv(Y_dw_skip_1_3, Y_proj_1_3, proj_1_weight_l4, nullptr, 1, 240, 80, 14, 14, 0);
    Compute_skip(iRMB_out3, Y_proj_1_3, iRMB_out4, norm_1_X_num);
    clear_data(
        afterNorm_3,afterRearrangeX_3, afterConv1_3,
        in_q_3, in_k_3,
        afterQKMultiplication_3, afterSoftmax_3, afterRearrangeX2_3, afterQKXMultiplication_3,
        afterRearrangeQKX_3, afterConv2_3, afterAct2_3,
        buffer_out_3, buffer_result_3,
         Y_dw_conv_1_3,  Y_dw_norm_1_3,  Y_dw_act_1_3,  Y_proj_1_3,  Y_dw_skip_1_3
    );

    // depth 5
    kernel_attention(iRMB_out4,
                    afterNorm_3,
                    norm1_mean_3, norm1_var_3, norm1_weight_l5, norm1_bias_l5,
                    afterRearrangeX_3,
                    afterConv1_3,
                    kernel1_l5, bias1_l5,
                    in_q_3, in_k_3,
                    afterQKMultiplication_3,
                    afterSoftmax_3,
                    afterRearrangeX2_3,
                    afterQKXMultiplication_3,
                    afterRearrangeQKX_3,
                    afterConv2_3,
                    kernel2_l5, bias2_l5,
                    afterAct2_3,
                    buffer_out_3,
                    buffer_result_3
                    );
    DW_conv(buffer_result_3, dw_conv_1_filter_l5, nullptr, dw_conv_1_shape_para, dw_conv_1_conv_para, Y_dw_conv_1_3);
    BatchNorm(Y_dw_conv_1_3, Y_dw_norm_1_3, dw_1_X_num, dw_norm_1_mean_l5, dw_norm_1_var_l5, dw_norm_1_weight_l5, dw_norm_1_bias_l5);
    SiLU(Y_dw_norm_1_3, Y_dw_act_1_3, dw_1_X_num);
    Compute_skip(buffer_result_3, Y_dw_act_1_3, Y_dw_skip_1_3, dw_1_X_num);
    Pointwise_conv(Y_dw_skip_1_3, Y_proj_1_3, proj_1_weight_l5, nullptr, 1, 240, 80, 14, 14, 0);
    Compute_skip(iRMB_out4, Y_proj_1_3, iRMB_out5, norm_1_X_num);
    clear_data(
        afterNorm_3,afterRearrangeX_3, afterConv1_3,
        in_q_3, in_k_3,
        afterQKMultiplication_3, afterSoftmax_3, afterRearrangeX2_3, afterQKXMultiplication_3,
        afterRearrangeQKX_3, afterConv2_3, afterAct2_3,
        buffer_out_3, buffer_result_3,
         Y_dw_conv_1_3,  Y_dw_norm_1_3,  Y_dw_act_1_3,  Y_proj_1_3,  Y_dw_skip_1_3
    );

    // depth 6
    kernel_attention(iRMB_out5,
                    afterNorm_3,
                    norm1_mean_3, norm1_var_3, norm1_weight_l6, norm1_bias_l6,
                    afterRearrangeX_3,
                    afterConv1_3,
                    kernel1_l6, bias1_l6,
                    in_q_3, in_k_3,
                    afterQKMultiplication_3,
                    afterSoftmax_3,
                    afterRearrangeX2_3,
                    afterQKXMultiplication_3,
                    afterRearrangeQKX_3,
                    afterConv2_3,
                    kernel2_l6, bias2_l6,
                    afterAct2_3,
                    buffer_out_3,
                    buffer_result_3
                    );
    DW_conv(buffer_result_3, dw_conv_1_filter_l6, nullptr, dw_conv_1_shape_para, dw_conv_1_conv_para, Y_dw_conv_1_3);
    BatchNorm(Y_dw_conv_1_3, Y_dw_norm_1_3, dw_1_X_num, dw_norm_1_mean_l6, dw_norm_1_var_l6, dw_norm_1_weight_l6, dw_norm_1_bias_l6);
    SiLU(Y_dw_norm_1_3, Y_dw_act_1_3, dw_1_X_num);
    Compute_skip(buffer_result_3, Y_dw_act_1_3, Y_dw_skip_1_3, dw_1_X_num);
    Pointwise_conv(Y_dw_skip_1_3, Y_proj_1_3, proj_1_weight_l6, nullptr, 1, 240, 80, 14, 14, 0);
    Compute_skip(iRMB_out5, Y_proj_1_3, iRMB_out6, norm_1_X_num);
    clear_data(
        afterNorm_3,afterRearrangeX_3, afterConv1_3,
        in_q_3, in_k_3,
        afterQKMultiplication_3, afterSoftmax_3, afterRearrangeX2_3, afterQKXMultiplication_3,
        afterRearrangeQKX_3, afterConv2_3, afterAct2_3,
        buffer_out_3, buffer_result_3,
         Y_dw_conv_1_3,  Y_dw_norm_1_3,  Y_dw_act_1_3,  Y_proj_1_3,  Y_dw_skip_1_3
    );

    // depth 7
    kernel_attention(iRMB_out6,
                    afterNorm_3,
                    norm1_mean_3, norm1_var_3, norm1_weight_l7, norm1_bias_l7,
                    afterRearrangeX_3,
                    afterConv1_3,
                    kernel1_l7, bias1_l7,
                    in_q_3, in_k_3,
                    afterQKMultiplication_3,
                    afterSoftmax_3,
                    afterRearrangeX2_3,
                    afterQKXMultiplication_3,
                    afterRearrangeQKX_3,
                    afterConv2_3,
                    kernel2_l7, bias2_l7,
                    afterAct2_3,
                    buffer_out_3,
                    buffer_result_3
                    );
    DW_conv(buffer_result_3, dw_conv_1_filter_l7, nullptr, dw_conv_1_shape_para, dw_conv_1_conv_para, Y_dw_conv_1_3);
    BatchNorm(Y_dw_conv_1_3, Y_dw_norm_1_3, dw_1_X_num, dw_norm_1_mean_l7, dw_norm_1_var_l7, dw_norm_1_weight_l7, dw_norm_1_bias_l7);
    SiLU(Y_dw_norm_1_3, Y_dw_act_1_3, dw_1_X_num);
    Compute_skip(buffer_result_3, Y_dw_act_1_3, Y_dw_skip_1_3, dw_1_X_num);
    Pointwise_conv(Y_dw_skip_1_3, Y_proj_1_3, proj_1_weight_l7, nullptr, 1, 240, 80, 14, 14, 0);
    Compute_skip(iRMB_out6, Y_proj_1_3, Y_skip_1_3, norm_1_X_num);
    }
}