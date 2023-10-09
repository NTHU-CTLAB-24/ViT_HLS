// Includes
#include <hls_math.h>
#include <hls_stream.h>
#include <stdint.h>
#include "kernel_stage3.hpp"

//1*12*16*16

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
    void kernel_stage3(float *buffer_DataIn_1,
                              float *afterNorm,
                              float *norm1_mean, float *norm1_var, float *norm1_weight, float *norm1_bias, float *norm1_ln_in,
                              float *afterPad,
                              float *afterRearrangeX,
                              float *afterPad1,
                              float *afterConv1,
                              float *kernel1,
                              float *bias1,
                              float *in_qk,
                              float *in_q,
                              float *in_k,
                              float *afterQKMultiplication,
                              float *afterSoftmax,
                              float *afterRearrangeX2,
                              float *afterQKXMultiplication,
                              float *afterRearrangeQKX,
                              float *afterPad2,
                              float *afterConv2,
                              float *kernel2,
                              float *bias2,
                              float *afterAct2,
                              float *QKV,
                              float *buffer_out,
                              float *in1_stream,
                              float *sumQK,
                              float *sumQKX,
                              float *buffer_result,
                       float* dw_conv_2_filter, float* dw_norm_2_gamma, float* dw_norm_2_beta, float* dw_norm_2_mean, float* dw_norm_2_var,
                       float* proj_2_weight,
                        float* Y_dw_conv_2, float* Y_dw_norm_2, float* Y_dw_act_2, float* Y_proj_2,
                       float* Y_dw_skip_2, float* Y_skip_2
                       )
    {
        #pragma HLS INTERFACE m_axi port = buffer_DataIn_1 bundle = gmem0 depth = 1024

        // dataflow pragma instruct compiler to run following three APIs in parallel
#pragma HLS INTERFACE m_axi port = afterNorm bundle = gmem1 depth = 1024
//        float afterNorm[BATCH_SIZE*CHANNEL_IN*HEIGHT_IN*WIDTH_IN];
#pragma HLS INTERFACE m_axi port = norm1_mean depth = 256
#pragma HLS INTERFACE m_axi port = norm1_var depth = 256
#pragma HLS INTERFACE m_axi port = norm1_weight depth = 1024
#pragma HLS INTERFACE m_axi port = norm1_bias depth = 1024
#pragma HLS INTERFACE m_axi port = norm1_ln_in depth = 1024
        // dataflow pragma instruct compiler to run following three APIs in parallel
//#pragma HLS INTERFACE m_axi port = x bundle = gmem2 depth = 3136
//        float x[BATCH_SIZE][CHANNEL_IN][HEIGHT_IN][WIDTH_IN];
#pragma HLS INTERFACE m_axi port = afterPad depth = 1764
//        float afterPad[BATCH_SIZE][CHANNEL_IN][NEW_HEIGHT_IN][NEW_WIDTH_IN];

#pragma HLS INTERFACE m_axi port = afterRearrangeX depth = 1764

#pragma HLS INTERFACE m_axi port = afterPad1 depth = 1764
#pragma HLS INTERFACE m_axi port = afterConv1 depth = 3528
#pragma HLS INTERFACE m_axi port = kernel1 depth = 32
#pragma HLS INTERFACE m_axi port = bias1 depth = 8
//        float afterRearrangeX[BATCH_SIZE*n1*n2*CHANNEL_IN*h1*w1];
#pragma HLS INTERFACE m_axi port = in_qk depth = 3528
//        float in_qk[BATCH_SIZE*n1*n2*CHANNEL_OUT*HEIGHT_OUT*WIDTH_OUT];
#pragma HLS INTERFACE m_axi port = in_q depth = 1764
//        float in_q[BATCH_SIZE*n1*n2][HEAD_SIZE][HEIGHT_OUT*WIDTH_OUT][DIM_HEAD_SIZE];
#pragma HLS INTERFACE m_axi port = in_k depth = 1764
//        float in_k[BATCH_SIZE*n1*n2][HEAD_SIZE][HEIGHT_OUT*WIDTH_OUT][DIM_HEAD_SIZE];
#pragma HLS INTERFACE m_axi port = afterQKMultiplication depth = 21609
//        float afterQKMultiplication[BATCH_SIZE*n1*n2][HEAD_SIZE][HEIGHT_OUT*WIDTH_OUT][HEIGHT_OUT*WIDTH_OUT];
#pragma HLS INTERFACE m_axi port = afterSoftmax depth = 21609
//        float afterSoftmax[BATCH_SIZE*n1*n2][HEAD_SIZE][HEIGHT_OUT*WIDTH_OUT][HEIGHT_OUT*WIDTH_OUT];
#pragma HLS INTERFACE m_axi port = afterRearrangeX2 depth = 1764
//        float afterRearrangeX2[BATCH_SIZE*n1*n2][HEAD_SIZE][HEIGHT_OUT*WIDTH_OUT][X_DIM_HEAD_SIZE];
#pragma HLS INTERFACE m_axi port = afterQKXMultiplication depth = 1764
 //       float afterQKXMultiplication[BATCH_SIZE*n1*n2][HEAD_SIZE][HEIGHT_OUT*WIDTH_OUT][X_DIM_HEAD_SIZE];
#pragma HLS INTERFACE m_axi port = afterRearrangeQKX depth = 1764

#pragma HLS INTERFACE m_axi port = afterPad2 depth = 1764
#pragma HLS INTERFACE m_axi port = afterConv2 depth = 5292
#pragma HLS INTERFACE m_axi port = kernel2 depth = 48
#pragma HLS INTERFACE m_axi port = bias2 depth = 12
#pragma HLS INTERFACE m_axi port = afterAct2 depth = 5292
//        float afterRearrangeQKX[BATCH_SIZE*n1*n2*HEAD_SIZE*HEIGHT_OUT*WIDTH_OUT*X_DIM_HEAD_SIZE];
#pragma HLS INTERFACE m_axi port = QKV depth = 5292
//        float QKV[BATCH_SIZE*n1*n2 * NEW_CHANNEL_OUT * HEIGHT_OUT * WIDTH_OUT];
#pragma HLS INTERFACE m_axi port = buffer_out depth = 5292
//        float buffer_out[BATCH_SIZE][NEW_CHANNEL_OUT][h1*n1][w1*n2];
#pragma HLS INTERFACE m_axi port = in1_stream depth = 21609
#pragma HLS INTERFACE m_axi port = sumQK depth = 2401
#pragma HLS INTERFACE m_axi port = sumQKX depth = 196
#pragma HLS INTERFACE m_axi port = buffer_result bundle  = gmem0 depth = 3072

    

    #pragma HLS INTERFACE m_axi port = dw_conv_2_filter depth = 108
    #pragma HLS INTERFACE m_axi port = dw_norm_2_gamma depth = 12
    #pragma HLS INTERFACE m_axi port = dw_norm_2_beta depth = 12
    #pragma HLS INTERFACE m_axi port = dw_norm_2_mean depth = 12
    #pragma HLS INTERFACE m_axi port = dw_norm_2_var depth = 12
    
    #pragma HLS INTERFACE m_axi port = proj_2_weight depth = 48

    
    #pragma HLS INTERFACE m_axi port = Y_dw_conv_2 bundle = gmem3 depth = 3072
    #pragma HLS INTERFACE m_axi port = Y_dw_norm_2 bundle = gmem0 depth = 3072
    #pragma HLS INTERFACE m_axi port = Y_dw_act_2 bundle = gmem2 depth = 3072
    #pragma HLS INTERFACE m_axi port = Y_proj_2 bundle = gmem1 depth = 1024
    #pragma HLS INTERFACE m_axi port = Y_dw_skip_2 bundle = gmem3 depth = 3072
    #pragma HLS INTERFACE m_axi port = Y_skip_2 bundle = gmem2 depth = 1024

    
    int norm_2_X_num[4] = {1, 4, 16, 16};
    int dw_conv_2_shape_para[7] = {1, 12, 16, 16, 12, 16, 16};
    int dw_conv_2_conv_para[6] = {3, 0, 1, 1, 12, 1};
    int dw_2_X_num[4] = {1, 12, 16, 16};

    
    /**
     * shortcut1 = attention input
     * after attention:
     *  shortcut2 = attention output
     *  out1 = shortcut2 + ConvNormAct(attention output)=>in/out shape the same
     * 
     *  out2 = shortcut1 + Pointwise_conv(out1)=>shape decrease three times
     */
    kernel_attention(buffer_DataIn_1,
                              afterNorm,
                              norm1_mean, norm1_var, norm1_weight, norm1_bias, norm1_ln_in,
                              afterPad,
                              afterRearrangeX,
                              afterPad1,
                              afterConv1,
                              kernel1,
                              bias1,
                              in_qk,
                              in_q,
                              in_k,
                              afterQKMultiplication,
                              afterSoftmax,
                              afterRearrangeX2,
                              afterQKXMultiplication,
                              afterRearrangeQKX,
                              afterPad2,
                              afterConv2,
                              kernel2,
                              bias2,
                              afterAct2,
                              QKV,
                              buffer_out,
                              in1_stream,
                              sumQK,
                              sumQKX,
                              buffer_result);
    ConvNormAct(buffer_result, dw_conv_2_filter, nullptr, dw_conv_2_shape_para, dw_conv_2_conv_para,
                Y_dw_conv_2, Y_dw_norm_2, dw_norm_2_mean, dw_norm_2_var, dw_norm_2_gamma, dw_norm_2_beta,
                Y_dw_act_2, 0, dw_2_X_num);
    Compute_skip(buffer_result, Y_dw_act_2, Y_dw_skip_2, dw_2_X_num);
    Pointwise_conv(Y_dw_skip_2, Y_proj_2, proj_2_weight, nullptr, 1, 12, 4, 16, 16, 0);
    Compute_skip(buffer_DataIn_1, Y_proj_2, Y_skip_2, norm_2_X_num);
    }
}