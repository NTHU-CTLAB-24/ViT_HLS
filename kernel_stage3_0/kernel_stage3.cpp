// Includes
#include <hls_math.h>
#include <hls_stream.h>
#include <stdint.h>
#include "kernel_stage3.hpp"

void ConvNormAct(float* dw_in, float* dw_kernel, float* dw_bias, int* dw_shape_para, int* dw_conv_para,
                 float* dw_out, float* norm_out, float* norm_mean, float* norm_var, float* norm_gamma, float* norm_beta,
                 float* act_out, int zp, int* dw_X_num)
{
    DW_conv(dw_in, dw_kernel, dw_bias, dw_shape_para, dw_conv_para, dw_out);
    BatchNorm(dw_out, norm_out, dw_X_num, norm_mean, norm_var, norm_gamma, norm_beta);
    SiLU(norm_out, act_out, dw_X_num);
}

extern "C"
{
    void kernel_stage3(float* X_data, float* norm_0_weight, float* norm_0_bias, float* v_conv_0_weight, float* v_conv_0_bias,
                       float* dw_conv_0_filter, float* dw_norm_0_weight, float* dw_norm_0_bias, float* dw_norm_0_mean, float* dw_norm_0_var,
                       float* proj_0_weight, float* Y_norm_0, float* Y_v_conv_0, float* Y_v_act_0, float* Y_dw_conv_0, float* Y_dw_norm_0, float* Y_dw_act_0,
                       float* result_30, float *atten_norm,
                        float *norm1_mean, float *norm1_var, float *norm1_weight, float *norm1_bias, float *norm1_ln_in,
                        float *afterPad, float *afterRearrangeX, float *afterPad1, float *afterConv1,
                        float *kernel1, float *bias1, float *in_qk, float *in_q, float *in_k,
                        float *afterQKMultiplication, float *afterSoftmax, float *afterRearrangeX2, float *afterQKXMultiplication, float *afterRearrangeQKX,
                        float *afterPad2, float *afterConv2,
                        float *kernel2, float *bias2, float *afterAct2, float *QKV,
                        float *buffer_out, float *in1_stream, float *sumQK, float *sumQKX,
                        float *buffer_result,
                        float* dw_conv_2_filter, float* dw_norm_2_gamma, float* dw_norm_2_beta, float* dw_norm_2_mean, float* dw_norm_2_var,
                        float* proj_2_weight,
                        float* Y_dw_conv_2, float* Y_dw_norm_2, float* Y_dw_act_2, float* Y_proj_2,
                        float* Y_dw_skip_2, float* Y_skip_2)
{

#pragma HLS INTERFACE m_axi port = X_data bundle = gmem0 depth = 37632

    // depth 0
    #pragma HLS INTERFACE m_axi port = norm_0_weight depth = 48
    #pragma HLS INTERFACE m_axi port = norm_0_bias depth = 48

    #pragma HLS INTERFACE m_axi port = v_conv_0_weight depth = 13824
    #pragma HLS INTERFACE m_axi port = v_conv_0_bias depth = 288

    #pragma HLS INTERFACE m_axi port = dw_conv_0_filter depth = 2592//288*9
    #pragma HLS INTERFACE m_axi port = dw_norm_0_weight depth = 288
    #pragma HLS INTERFACE m_axi port = dw_norm_0_bias depth = 288
    #pragma HLS INTERFACE m_axi port = dw_norm_0_mean depth = 288
    #pragma HLS INTERFACE m_axi port = dw_norm_0_var depth = 288
    
    #pragma HLS INTERFACE m_axi port = proj_0_weight depth = 23040//288*80
    

    #pragma HLS INTERFACE m_axi port = Y_norm_0 bundle = gmem1 depth = 37632
    #pragma HLS INTERFACE m_axi port = Y_v_conv_0 bundle = gmem2 depth = 225792
    #pragma HLS INTERFACE m_axi port = Y_v_act_0 bundle = gmem3 depth = 225792
    #pragma HLS INTERFACE m_axi port = Y_dw_conv_0 bundle = gmem0 depth = 37632
    #pragma HLS INTERFACE m_axi port = Y_dw_norm_0 bundle = gmem1 depth = 37632
    #pragma HLS INTERFACE m_axi port = Y_dw_act_0 bundle = gmem3 depth = 37632
    #pragma HLS INTERFACE m_axi port = result_30 bundle = gmem0 depth = 15680

    //others
    
#pragma HLS INTERFACE m_axi port = atten_norm bundle = gmem1 depth = 15680
#pragma HLS INTERFACE m_axi port = norm1_mean depth = 196
#pragma HLS INTERFACE m_axi port = norm1_var depth = 196
#pragma HLS INTERFACE m_axi port = norm1_weight depth = 15680
#pragma HLS INTERFACE m_axi port = norm1_bias depth = 15680
#pragma HLS INTERFACE m_axi port = norm1_ln_in depth = 15680

#pragma HLS INTERFACE m_axi port = afterPad depth = 15680
#pragma HLS INTERFACE m_axi port = afterRearrangeX depth = 15680

#pragma HLS INTERFACE m_axi port = afterPad1 depth = 15680
#pragma HLS INTERFACE m_axi port = afterConv1 depth = 31360
#pragma HLS INTERFACE m_axi port = kernel1 depth = 12800
#pragma HLS INTERFACE m_axi port = bias1 depth = 160
#pragma HLS INTERFACE m_axi port = in_qk depth = 31360
#pragma HLS INTERFACE m_axi port = in_q depth = 15680
#pragma HLS INTERFACE m_axi port = in_k depth = 15680
#pragma HLS INTERFACE m_axi port = afterQKMultiplication depth = 38416
#pragma HLS INTERFACE m_axi port = afterSoftmax depth = 38416
#pragma HLS INTERFACE m_axi port = afterRearrangeX2 depth = 15680
#pragma HLS INTERFACE m_axi port = afterQKXMultiplication depth = 15680
#pragma HLS INTERFACE m_axi port = afterRearrangeQKX depth = 15680

#pragma HLS INTERFACE m_axi port = afterPad2 depth = 15680
#pragma HLS INTERFACE m_axi port = afterConv2 depth = 47040
#pragma HLS INTERFACE m_axi port = kernel2 depth = 19200
#pragma HLS INTERFACE m_axi port = bias2 depth = 240
#pragma HLS INTERFACE m_axi port = afterAct2 depth = 47040

#pragma HLS INTERFACE m_axi port = QKV depth = 47040
#pragma HLS INTERFACE m_axi port = buffer_out depth = 47040
#pragma HLS INTERFACE m_axi port = in1_stream depth = 38416
#pragma HLS INTERFACE m_axi port = sumQK depth = 2401
#pragma HLS INTERFACE m_axi port = sumQKX depth = 980
#pragma HLS INTERFACE m_axi port = buffer_result bundle  = gmem0 depth = 47040

    #pragma HLS INTERFACE m_axi port = dw_conv_2_filter depth = 2160//9*240
    #pragma HLS INTERFACE m_axi port = dw_norm_2_gamma depth = 240
    #pragma HLS INTERFACE m_axi port = dw_norm_2_beta depth = 240
    #pragma HLS INTERFACE m_axi port = dw_norm_2_mean depth = 240
    #pragma HLS INTERFACE m_axi port = dw_norm_2_var depth = 240
    
    #pragma HLS INTERFACE m_axi port = proj_2_weight depth = 9600

    
    #pragma HLS INTERFACE m_axi port = Y_dw_conv_2 bundle = gmem3 depth = 47040
    #pragma HLS INTERFACE m_axi port = Y_dw_norm_2 bundle = gmem0 depth = 47040
    #pragma HLS INTERFACE m_axi port = Y_dw_act_2 bundle = gmem2 depth = 47040
    #pragma HLS INTERFACE m_axi port = Y_proj_2 bundle = gmem1 depth = 15680
    #pragma HLS INTERFACE m_axi port = Y_dw_skip_2 bundle = gmem3 depth = 47040
    #pragma HLS INTERFACE m_axi port = Y_skip_2 bundle = gmem2 depth = 15680

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

    // get_norm = ln_2d, not batchnorm!
    LayerNorm(X_data, Y_norm_0, norm_0_X_num, mean_buf_0, var_buf_0, norm_0_weight, norm_0_bias);
    // self.v = ConvNormAct (後面的depth是做atten)
    Pointwise_conv(Y_norm_0, Y_v_conv_0, v_conv_0_weight, v_conv_0_bias, 1, 48, 288, 28, 28, 1);
    // 用relu會全部變成0，實際上應該要用gelu，先用silu代替
    SiLU(Y_v_conv_0, Y_v_act_0, v_conv_0_X_num);
    
    // self.local_conv = ConvNormAct
    ConvNormAct(Y_v_act_0, dw_conv_0_filter, nullptr, dw_conv_0_shape_para, dw_conv_0_conv_para,
                Y_dw_conv_0, Y_dw_norm_0, dw_norm_0_mean, dw_norm_0_var, dw_norm_0_weight, dw_norm_0_bias,
                Y_dw_act_0, 0, dw_0_X_num);
    // self.proj
    Pointwise_conv(Y_dw_act_0, result_30, proj_0_weight, nullptr, 1, 288, 80, 14, 14, 0);
    
    /**
     * shortcut1 = attention input
     * after attention:
     *  shortcut2 = attention output
     *  out1 = shortcut2 + ConvNormAct(attention output)=>in/out shape the same
     * 
     *  out2 = shortcut1 + Pointwise_conv(out1)=>shape decrease three times
     */
    
    // depth 1
      // depth 1
    int norm_2_X_num[4] = {1, 80, 14, 14};
    int dw_conv_2_shape_para[7] = {1, 80, 14, 14, 80, 14, 14};
    int dw_conv_2_conv_para[6] = {3, 0, 1, 1, 240, 1};
    int dw_2_X_num[4] = {1, 240, 14, 14};

    //應該先做一次norm才進去attention
    
    /*
    kernel_attention(result_30, atten_norm,
                    norm1_mean, norm1_var, norm1_weight, norm1_bias, norm1_ln_in,
                    afterPad, afterRearrangeX, afterPad1, afterConv1,
                    kernel1, bias1, in_qk, in_q, in_k, afterQKMultiplication, afterSoftmax, afterRearrangeX2,
                    afterQKXMultiplication, afterRearrangeQKX, afterPad2, afterConv2,
                    kernel2, bias2, afterAct2, QKV,
                    buffer_out, in1_stream, sumQK, sumQKX, buffer_result);
    
    ConvNormAct(buffer_result, dw_conv_2_filter, nullptr, dw_conv_2_shape_para, dw_conv_2_conv_para,
                Y_dw_conv_2, Y_dw_norm_2, dw_norm_2_mean, dw_norm_2_var, dw_norm_2_gamma, dw_norm_2_beta,
                Y_dw_act_2, 0, dw_2_X_num);
    
    Compute_skip(buffer_result, Y_dw_act_2, Y_dw_skip_2, dw_2_X_num);
    Pointwise_conv(Y_dw_skip_2, Y_proj_2, proj_2_weight, nullptr, 1, 120, 40, 28, 28, 0);
    Compute_skip(buffer_DataIn_1, Y_proj_2, Y_skip_2, norm_2_X_num);
    */
    }
}