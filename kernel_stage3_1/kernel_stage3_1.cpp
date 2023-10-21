// Includes
#include <hls_math.h>
#include <hls_stream.h>
#include <stdint.h>
#include "kernel_stage3_1.hpp"


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
    void kernel_stage3_1(float *buffer_DataIn_1,
                              float *afterNorm,
                              float *norm1_mean, float *norm1_var, float *norm1_weight, float *norm1_bias, 
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
                              float *buffer_result,
                       float* dw_conv_1_filter, float* dw_norm_1_weight, float* dw_norm_1_bias, float* dw_norm_1_mean, float* dw_norm_1_var,
                       float* proj_1_weight,
                        float* Y_dw_conv_1, float* Y_dw_norm_1, float* Y_dw_act_1, float* Y_proj_1,
                       float* Y_dw_skip_1, float* Y_skip_1
                       )
    {
        #pragma HLS INTERFACE m_axi port = buffer_DataIn_1 bundle = gmem0 depth = 15680

        // dataflow pragma instruct compiler to run following three APIs in parallel
#pragma HLS INTERFACE m_axi port = afterNorm bundle = gmem1 depth = 15680
//        float afterNorm[BATCH_SIZE*CHANNEL_IN*HEIGHT_IN*WIDTH_IN];
#pragma HLS INTERFACE m_axi port = norm1_mean depth = 80
#pragma HLS INTERFACE m_axi port = norm1_var depth = 80
#pragma HLS INTERFACE m_axi port = norm1_weight depth = 80
#pragma HLS INTERFACE m_axi port = norm1_bias depth = 80
        // dataflow pragma instruct compiler to run following three APIs in parallel
//#pragma HLS INTERFACE m_axi port = x bundle = gmem2 depth = 3136
//        float x[BATCH_SIZE][CHANNEL_IN][HEIGHT_IN][WIDTH_IN];
#pragma HLS INTERFACE m_axi port = afterPad depth = 15680
//        float afterPad[BATCH_SIZE][CHANNEL_IN][NEW_HEIGHT_IN][NEW_WIDTH_IN];

#pragma HLS INTERFACE m_axi port = afterRearrangeX depth = 15680

#pragma HLS INTERFACE m_axi port = afterPad1 depth = 15680
#pragma HLS INTERFACE m_axi port = afterConv1 depth = 31360
#pragma HLS INTERFACE m_axi port = kernel1 depth = 12800
#pragma HLS INTERFACE m_axi port = bias1 depth = 160
//        float afterRearrangeX[BATCH_SIZE*n1*n2*CHANNEL_IN*h1*w1];
#pragma HLS INTERFACE m_axi port = in_qk depth = 31360
//        float in_qk[BATCH_SIZE*n1*n2*CHANNEL_OUT*HEIGHT_OUT*WIDTH_OUT];
#pragma HLS INTERFACE m_axi port = in_q depth = 15680
//        float in_q[BATCH_SIZE*n1*n2][HEAD_SIZE][HEIGHT_OUT*WIDTH_OUT][DIM_HEAD_SIZE];
#pragma HLS INTERFACE m_axi port = in_k depth = 15680
//        float in_k[BATCH_SIZE*n1*n2][HEAD_SIZE][HEIGHT_OUT*WIDTH_OUT][DIM_HEAD_SIZE];
#pragma HLS INTERFACE m_axi port = afterQKMultiplication depth = 38416
//        float afterQKMultiplication[BATCH_SIZE*n1*n2][HEAD_SIZE][HEIGHT_OUT*WIDTH_OUT][HEIGHT_OUT*WIDTH_OUT];
#pragma HLS INTERFACE m_axi port = afterSoftmax depth = 38416
//        float afterSoftmax[BATCH_SIZE*n1*n2][HEAD_SIZE][HEIGHT_OUT*WIDTH_OUT][HEIGHT_OUT*WIDTH_OUT];
#pragma HLS INTERFACE m_axi port = afterRearrangeX2 depth = 15680
//        float afterRearrangeX2[BATCH_SIZE*n1*n2][HEAD_SIZE][HEIGHT_OUT*WIDTH_OUT][X_DIM_HEAD_SIZE];
#pragma HLS INTERFACE m_axi port = afterQKXMultiplication depth = 15680
 //       float afterQKXMultiplication[BATCH_SIZE*n1*n2][HEAD_SIZE][HEIGHT_OUT*WIDTH_OUT][X_DIM_HEAD_SIZE];
#pragma HLS INTERFACE m_axi port = afterRearrangeQKX depth = 15680

#pragma HLS INTERFACE m_axi port = afterPad2 depth = 15680
#pragma HLS INTERFACE m_axi port = afterConv2 depth = 47040
#pragma HLS INTERFACE m_axi port = kernel2 depth = 19200
#pragma HLS INTERFACE m_axi port = bias2 depth = 240
#pragma HLS INTERFACE m_axi port = afterAct2 depth = 47040
//        float afterRearrangeQKX[BATCH_SIZE*n1*n2*HEAD_SIZE*HEIGHT_OUT*WIDTH_OUT*X_DIM_HEAD_SIZE];
#pragma HLS INTERFACE m_axi port = QKV depth = 47040
//        float QKV[BATCH_SIZE*n1*n2 * NEW_CHANNEL_OUT * HEIGHT_OUT * WIDTH_OUT];
#pragma HLS INTERFACE m_axi port = buffer_out depth = 47040
//        float buffer_out[BATCH_SIZE][NEW_CHANNEL_OUT][h1*n1][w1*n2];
#pragma HLS INTERFACE m_axi port = buffer_result bundle  = gmem0 depth = 47040

    

    #pragma HLS INTERFACE m_axi port = dw_conv_1_filter depth = 6000 //25*240
    #pragma HLS INTERFACE m_axi port = dw_norm_1_weight depth = 240
    #pragma HLS INTERFACE m_axi port = dw_norm_1_bias depth = 240
    #pragma HLS INTERFACE m_axi port = dw_norm_1_mean depth = 240
    #pragma HLS INTERFACE m_axi port = dw_norm_1_var depth = 240
    
    #pragma HLS INTERFACE m_axi port = proj_1_weight depth = 19200

    #pragma HLS INTERFACE m_axi port = Y_dw_conv_1 bundle = gmem3 depth = 47040
    #pragma HLS INTERFACE m_axi port = Y_dw_norm_1 bundle = gmem0 depth = 47040
    #pragma HLS INTERFACE m_axi port = Y_dw_act_1 bundle = gmem2 depth = 47040
    #pragma HLS INTERFACE m_axi port = Y_proj_1 bundle = gmem1 depth = 15680
    #pragma HLS INTERFACE m_axi port = Y_dw_skip_1 bundle = gmem3 depth = 47040
    #pragma HLS INTERFACE m_axi port = Y_skip_1 bundle = gmem2 depth = 15680


    // depth 2
    int norm_1_X_num[4] = {1, 80, 14, 14};
    int dw_conv_1_shape_para[7] = {1, 240, 14, 14, 240, 14, 14};
    int dw_conv_1_conv_para[6] = {5, 0, 1, 2, 240, 1};
    int dw_1_X_num[4] = {1, 240, 14, 14};


    // depth 2
    //BatchNorm(Y_proj_1, Y_norm_1, norm_1_X_num, norm_1_running_mean, norm_1_running_var, norm_1_weight, norm_1_bias);
    //Pointwise_conv(Y_norm_1, Y_v_conv_1, v_conv_1_weight, v_conv_1_bias, 1, 8, 16, 28, 28, 1);
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
                              norm1_mean, norm1_var, norm1_weight, norm1_bias,
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
                              buffer_result
                       );

    ConvNormAct(buffer_result, dw_conv_1_filter, nullptr, dw_conv_1_shape_para, dw_conv_1_conv_para,
                Y_dw_conv_1, Y_dw_norm_1, dw_norm_1_mean, dw_norm_1_var, dw_norm_1_weight, dw_norm_1_bias,
               Y_dw_act_1, 0, dw_1_X_num);
    Compute_skip(buffer_result, Y_dw_act_1, Y_dw_skip_1, dw_1_X_num);
    Pointwise_conv(Y_dw_skip_1, Y_proj_1, proj_1_weight, nullptr, 1, 240, 80, 14, 14, 0);
    Compute_skip(buffer_DataIn_1, Y_proj_1, Y_skip_1, norm_1_X_num);
    }
}