// Includes
#include <hls_math.h>
#include <hls_stream.h>
#include <stdint.h>
#include "kernel_EMO.hpp"

extern "C"
{
    void kernel_stage4(float* X_data, float* norm_0_weight_4, float* norm_0_bias_4, float* v_conv_0_weight_4, float* v_conv_0_bias_4,
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
                        float* Y_dw_skip_1_4, float* Y_skip_1_4)
{

    // #pragma HLS INTERFACE m_axi port = X_data bundle = gmem0 depth = 37632

    // // depth 0
    // #pragma HLS INTERFACE m_axi port = norm_0_weight_4 depth = 80
    // #pragma HLS INTERFACE m_axi port = norm_0_bias_4 depth = 80

    // #pragma HLS INTERFACE m_axi port = v_conv_0_weight_4 depth = 13824
    // #pragma HLS INTERFACE m_axi port = v_conv_0_bias_4 depth = 560

    // #pragma HLS INTERFACE m_axi port = dw_conv_0_filter_4 depth = 7200
    // #pragma HLS INTERFACE m_axi port = dw_norm_0_weight_4 depth = 560
    // #pragma HLS INTERFACE m_axi port = dw_norm_0_bias_4 depth = 560
    // #pragma HLS INTERFACE m_axi port = dw_norm_0_mean_4 depth = 560
    // #pragma HLS INTERFACE m_axi port = dw_norm_0_var_4 depth = 560
    
    // #pragma HLS INTERFACE m_axi port = proj_0_weight_4 depth = 23040//560*80
    

    // #pragma HLS INTERFACE m_axi port = Y_norm_0_4 bundle = gmem1 depth = 37632
    // #pragma HLS INTERFACE m_axi port = Y_v_conv_0_4 bundle = gmem2 depth = 225792
    // #pragma HLS INTERFACE m_axi port = Y_v_act_0_4 bundle = gmem3 depth = 225792
    // #pragma HLS INTERFACE m_axi port = Y_dw_conv_0_4 bundle = gmem0 depth = 37632
    // #pragma HLS INTERFACE m_axi port = Y_dw_norm_0_4 bundle = gmem1 depth = 37632
    // #pragma HLS INTERFACE m_axi port = Y_dw_act_0_4 bundle = gmem3 depth = 37632
    // #pragma HLS INTERFACE m_axi port = result_40 bundle = gmem0 depth = 15680

    // //depth1-7
    // #pragma HLS INTERFACE m_axi port = afterNorm_4 bundle = gmem1 depth = 15680
    // #pragma HLS INTERFACE m_axi port = norm1_mean_4 depth = 196 //*7
    // #pragma HLS INTERFACE m_axi port = norm1_var_4 depth = 196 //*7
    // #pragma HLS INTERFACE m_axi port = norm1_weight_4 depth = 80*7
    // #pragma HLS INTERFACE m_axi port = norm1_bias_4 depth = 80*7

    // #pragma HLS INTERFACE m_axi port = afterRearrangeX_4 depth = 15680
    // #pragma HLS INTERFACE m_axi port = afterConv1_4 depth = 31360

    // #pragma HLS INTERFACE m_axi port = kernel1_4 depth = 12800*7
    // #pragma HLS INTERFACE m_axi port = bias1_4 depth = 160*7
    // #pragma HLS INTERFACE m_axi port = in_q_4 depth = 15680
    // #pragma HLS INTERFACE m_axi port = in_k_4 depth = 15680
    // #pragma HLS INTERFACE m_axi port = afterQKMultiplication_4 depth = 38416
    // #pragma HLS INTERFACE m_axi port = afterSoftmax_4 depth = 38416
    // #pragma HLS INTERFACE m_axi port = afterRearrangeX2_4 depth = 15680
    // #pragma HLS INTERFACE m_axi port = afterQKXMultiplication_4 depth = 15680
    // #pragma HLS INTERFACE m_axi port = afterRearrangeQKX_4 depth = 15680
    // #pragma HLS INTERFACE m_axi port = afterConv2_4 depth = 47040

    // #pragma HLS INTERFACE m_axi port = kernel2_4 depth = 19200*7
    // #pragma HLS INTERFACE m_axi port = bias2_4 depth = 240*7

    // #pragma HLS INTERFACE m_axi port = afterAct2_4 depth = 47040
    // #pragma HLS INTERFACE m_axi port = buffer_out_4 depth = 47040
    // #pragma HLS INTERFACE m_axi port = buffer_result_4 bundle  = gmem0 depth = 47040

    // #pragma HLS INTERFACE m_axi port = dw_conv_1_filter_4 depth = 6000*7 //25*240
    // #pragma HLS INTERFACE m_axi port = dw_norm_1_weight_4 depth = 240*7
    // #pragma HLS INTERFACE m_axi port = dw_norm_1_bias_4 depth = 240*7
    // #pragma HLS INTERFACE m_axi port = dw_norm_1_mean_4 depth = 240*7
    // #pragma HLS INTERFACE m_axi port = dw_norm_1_var_4 depth = 240*7
    // #pragma HLS INTERFACE m_axi port = proj_1_weight_4 depth = 19200*7

    // #pragma HLS INTERFACE m_axi port = Y_dw_conv_1_4 bundle = gmem3 depth = 47040
    // #pragma HLS INTERFACE m_axi port = Y_dw_norm_1_4 bundle = gmem0 depth = 47040
    // #pragma HLS INTERFACE m_axi port = Y_dw_act_1_4 bundle = gmem2 depth = 47040
    // #pragma HLS INTERFACE m_axi port = Y_proj_1_4 bundle = gmem1 depth = 15680
    // #pragma HLS INTERFACE m_axi port = Y_dw_skip_1_4 bundle = gmem3 depth = 47040
    // #pragma HLS INTERFACE m_axi port = Y_skip_1_4 bundle = gmem2 depth = 15680

    // depth 0
    int norm_0_X_num[4] = {1, 80, 14, 14};
    int v_conv_0_X_num[4] = {1, 560, 14, 14};
    int dw_conv_0_shape_para[7] = {1, 560, 14, 14, 560, 7, 7};
    int dw_conv_0_conv_para[6] = {5, 0, 2, 2, 560, 1};
    int dw_0_X_num[4] = {1, 560, 7, 7};

    float mean_buf_0[196];
    #pragma HLS array_partition variable = mean_buf_0 complete dim = 1 
    float var_buf_0[196];
    #pragma HLS array_partition variable = var_buf_0 complete dim = 1 

    LayerNorm(X_data, Y_norm_0_4, norm_0_X_num, mean_buf_0, var_buf_0, norm_0_weight_4, norm_0_bias_4);
    Pointwise_conv(Y_norm_0_4, Y_v_conv_0_4, v_conv_0_weight_4, v_conv_0_bias_4, 1, 80, 560, 14, 14, 1);
    GeLU(Y_v_conv_0_4, Y_v_act_0_4, v_conv_0_X_num);
    DW_conv(Y_v_act_0_4, dw_conv_0_filter_4, nullptr, dw_conv_0_shape_para, dw_conv_0_conv_para, Y_dw_conv_0_4);
    BatchNorm(Y_dw_conv_0_4, Y_dw_norm_0_4, dw_0_X_num, dw_norm_0_mean_4, dw_norm_0_var_4, dw_norm_0_weight_4, dw_norm_0_bias_4);
    SiLU(Y_dw_norm_0_4, Y_dw_act_0_4, dw_0_X_num);
    // self.proj
    Pointwise_conv(Y_dw_act_0_4, result_40, proj_0_weight_4, nullptr, 1, 560, 168, 7, 7, 0);

    
    // depth 1-2
    int norm_1_X_num[4] = {1, 168, 7, 7};
    int dw_conv_1_shape_para[7] = {1, 588, 7, 7, 588, 7, 7};
    int dw_conv_1_conv_para[6] = {5, 0, 1, 2, 588, 1};
    int dw_1_X_num[4] = {1, 588, 7, 7};
    
    //float norm1_mean_l1[196], norm1_mean_l2[196], norm1_mean_l4[196], norm1_mean_l4[196], norm1_mean_l5[196], norm1_mean_l6[196], norm1_mean_l7[196];
    //float norm1_var_l1[196], norm1_var_l2[196], norm1_var_l4[196], norm1_var_l4[196], norm1_var_l5[196], norm1_var_l6[196], norm1_var_l7[196];
    float norm1_weight_l1[168], norm1_weight_l2[168];
    float norm1_bias_l1[168], norm1_bias_l2[168];

    float kernel1_l1[56448], kernel1_l2[56448];
    float bias1_l1[336], bias1_l2[336];
    float kernel2_l1[98784], kernel2_l2[98784];
    float bias2_l1[588], bias2_l2[588];

    float dw_conv_1_filter_l1[14700], dw_conv_1_filter_l2[14700];
    float dw_norm_1_weight_l1[588], dw_norm_1_weight_l2[588];
    float dw_norm_1_bias_l1[588], dw_norm_1_bias_l2[588];
    float dw_norm_1_mean_l1[588], dw_norm_1_mean_l2[588];
    float dw_norm_1_var_l1[588], dw_norm_1_var_l2[588];

    float proj_1_weight_l1[98784], proj_1_weight_l2[98784];

    float iRMB_out1[8232] = {0};
    
    for (int i = 0; i < 168 * 2; i++)
    {
        if (i < 168) norm1_weight_l1[i] = norm1_weight_4[i];
        else if (i < 168 * 2) norm1_weight_l2[i - 168] = norm1_weight_4[i];
    }
    for (int i = 0; i < 168 * 2; i++)
    {
        if (i < 168) norm1_bias_l1[i] = norm1_bias_4[i];
        else if (i < 168 * 2) norm1_bias_l2[i - 168] = norm1_bias_4[i];
    }
    for (int i = 0; i < 56448 * 2; i++)
    {
        if (i < 56448) kernel1_l1[i] = kernel1_4[i];
        else if (i < 56448 * 2) kernel1_l2[i - 56448] = kernel1_4[i];
    }
    for (int i = 0; i < 336 * 2; i++)
    {
        if (i < 336) bias1_l1[i] = bias1_4[i];
        else if (i < 336 * 2) bias1_l2[i - 336] = bias1_4[i];
    }
    for (int i = 0; i < 98784 * 2; i++)
    {
        if (i < 98784) kernel2_l1[i] = kernel2_4[i];
        else if (i < 98784 * 2) kernel2_l2[i - 98784] = kernel2_4[i];
    }
    for (int i = 0; i < 588 * 2; i++)
    {
        if (i < 588) bias2_l1[i] = bias2_4[i];
        else if (i < 588 * 2) bias2_l2[i - 588] = bias2_4[i];
    }
    for (int i = 0; i < 14700 * 2; i++)
    {
        if (i < 14700) dw_conv_1_filter_l1[i] = dw_conv_1_filter_4[i];
        else if (i < 14700 * 2) dw_conv_1_filter_l2[i - 14700] = dw_conv_1_filter_4[i];
    }
    for (int i = 0; i < 588 * 2; i++)
    {
        if (i < 588) dw_norm_1_weight_l1[i] = dw_norm_1_weight_4[i];
        else if (i < 588 * 2) dw_norm_1_weight_l2[i - 588] = dw_norm_1_weight_4[i];
    }
    for (int i = 0; i < 588 * 2; i++)
    {
        if (i < 588) dw_norm_1_bias_l1[i] = dw_norm_1_bias_4[i];
        else if (i < 588 * 2) dw_norm_1_bias_l2[i - 588] = dw_norm_1_bias_4[i];
    }
    for (int i = 0; i < 588 * 2; i++)
    {
        if (i < 588) dw_norm_1_mean_l1[i] = dw_norm_1_mean_4[i];
        else if (i < 588 * 2) dw_norm_1_mean_l2[i - 588] = dw_norm_1_mean_4[i];
    }
    for (int i = 0; i < 588 * 2; i++)
    {
        if (i < 588) dw_norm_1_var_l1[i] = dw_norm_1_var_4[i];
        else if (i < 588 * 2) dw_norm_1_var_l2[i - 588] = dw_norm_1_var_4[i];
    }
    for (int i = 0; i < 98784 * 2; i++)
    {
        if (i < 98784) proj_1_weight_l1[i] = proj_1_weight_4[i];
        else if (i < 98784 * 2) proj_1_weight_l2[i - 98784] = proj_1_weight_4[i];
    }
    float afterNorm_l2[8232];
    float afterPad_l2[8232];

    // depth 1
    kernel_attention_4(result_40,
                    afterNorm_4,
                    norm1_mean_4, norm1_var_4, norm1_weight_l1, norm1_bias_l1,
                    afterRearrangeX_4,
                    afterConv1_4,
                    kernel1_l1, bias1_l1,
                    in_q_4, in_k_4,
                    afterQKMultiplication_4,
                    afterSoftmax_4,
                    afterRearrangeX2_4,
                    afterQKXMultiplication_4,
                    afterRearrangeQKX_4,
                    afterConv2_4,
                    kernel2_l1, bias2_l1,
                    afterAct2_4,
                    buffer_out_4,
                    buffer_result_4
                    );
    DW_conv(buffer_result_4, dw_conv_1_filter_l1, nullptr, dw_conv_1_shape_para, dw_conv_1_conv_para, Y_dw_conv_1_4);
    BatchNorm(Y_dw_conv_1_4, Y_dw_norm_1_4, dw_1_X_num, dw_norm_1_mean_l1, dw_norm_1_var_l1, dw_norm_1_weight_l1, dw_norm_1_bias_l1);
    SiLU(Y_dw_norm_1_4, Y_dw_act_1_4, dw_1_X_num);
    Compute_skip(buffer_result_4, Y_dw_act_1_4, Y_dw_skip_1_4, dw_1_X_num);
    Pointwise_conv(Y_dw_skip_1_4, Y_proj_1_4, proj_1_weight_l1, nullptr, 1, 588, 168, 7, 7, 0);
    Compute_skip(result_40, Y_proj_1_4, iRMB_out1, norm_1_X_num);
    clear_data_4(
        afterNorm_4, afterRearrangeX_4, afterConv1_4,
        in_q_4, in_k_4,
        afterQKMultiplication_4, afterSoftmax_4, afterRearrangeX2_4, afterQKXMultiplication_4,
        afterRearrangeQKX_4, afterConv2_4, afterAct2_4,
        buffer_out_4, buffer_result_4,
        Y_dw_conv_1_4,  Y_dw_norm_1_4,  Y_dw_act_1_4,  Y_proj_1_4,  Y_dw_skip_1_4
    );

    // depth 2
    kernel_attention_4(iRMB_out1,
                    afterNorm_4,
                    norm1_mean_4, norm1_var_4, norm1_weight_l2, norm1_bias_l2,
                    afterRearrangeX_4,
                    afterConv1_4,
                    kernel1_l2, bias1_l2,
                    in_q_4, in_k_4,
                    afterQKMultiplication_4,
                    afterSoftmax_4,
                    afterRearrangeX2_4,
                    afterQKXMultiplication_4,
                    afterRearrangeQKX_4,
                    afterConv2_4,
                    kernel2_l2, bias2_l2,
                    afterAct2_4,
                    buffer_out_4,
                    buffer_result_4
                    );
    DW_conv(buffer_result_4, dw_conv_1_filter_l2, nullptr, dw_conv_1_shape_para, dw_conv_1_conv_para, Y_dw_conv_1_4);
    BatchNorm(Y_dw_conv_1_4, Y_dw_norm_1_4, dw_1_X_num, dw_norm_1_mean_l2, dw_norm_1_var_l2, dw_norm_1_weight_l2, dw_norm_1_bias_l2);
    SiLU(Y_dw_norm_1_4, Y_dw_act_1_4, dw_1_X_num);
    Compute_skip(buffer_result_4, Y_dw_act_1_4, Y_dw_skip_1_4, dw_1_X_num);
    Pointwise_conv(Y_dw_skip_1_4, Y_proj_1_4, proj_1_weight_l2, nullptr, 1, 588, 168, 7, 7, 0);
    Compute_skip(iRMB_out1, Y_proj_1_4, Y_skip_1_4, norm_1_X_num);
    }
}