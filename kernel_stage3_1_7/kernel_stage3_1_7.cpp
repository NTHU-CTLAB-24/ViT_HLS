// Includes
#include <hls_math.h>
#include <hls_stream.h>
#include <stdint.h>
#include "kernel_stage3_1_7.hpp"


void ConvNormAct(float* dw_in, float* dw_kernel, float* dw_bias, int* dw_shape_para, int* dw_conv_para,
                 float* dw_out, float* norm_out, float* norm_mean, float* norm_var, float* norm_gamma, float* norm_beta,
                 float* act_out, int zp, int* dw_X_num)
{
    DW_conv(dw_in, dw_kernel, dw_bias, dw_shape_para, dw_conv_para, dw_out);
    BatchNorm(dw_out, norm_out, dw_X_num, norm_mean, norm_var, norm_gamma, norm_beta);
    ReLU(norm_out, act_out, dw_X_num, zp);
}

void split_data_to7(float* origin, float* l1, float* l2, float* l3, float* l4, float* l5, float* l6, float* l7, int n){
    for(int i=0;i<n*7;i++){
        if(i<n) l1[i]=origin[i];
        else if(i<n*2) l2[i-n]=origin[i];
        else if(i<n*3) l3[i-n*2]=origin[i];
        else if(i<n*4) l4[i-n*3]=origin[i];
        else if(i<n*5) l5[i-n*4]=origin[i];
        else if(i<n*6) l6[i-n*5]=origin[i];
        else l7[i-n*6]=origin[i];
    }
}

void iRMB(float *buffer_DataIn_1,
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
            float* Y_dw_skip_1, float* Y_skip_1)
{
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

extern "C"
{
    void kernel_stage3_1_7(float *buffer_DataIn_1,
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
#pragma HLS INTERFACE m_axi port = norm1_mean depth = 80*7
#pragma HLS INTERFACE m_axi port = norm1_var depth = 80*7
#pragma HLS INTERFACE m_axi port = norm1_weight depth = 80*7
#pragma HLS INTERFACE m_axi port = norm1_bias depth = 80*7
        // dataflow pragma instruct compiler to run following three APIs in parallel
//#pragma HLS INTERFACE m_axi port = x bundle = gmem2 depth = 3136
//        float x[BATCH_SIZE][CHANNEL_IN][HEIGHT_IN][WIDTH_IN];
#pragma HLS INTERFACE m_axi port = afterPad depth = 15680
//        float afterPad[BATCH_SIZE][CHANNEL_IN][NEW_HEIGHT_IN][NEW_WIDTH_IN];

#pragma HLS INTERFACE m_axi port = afterRearrangeX depth = 15680

#pragma HLS INTERFACE m_axi port = afterPad1 depth = 15680
#pragma HLS INTERFACE m_axi port = afterConv1 depth = 31360

#pragma HLS INTERFACE m_axi port = kernel1 depth = 12800*7
#pragma HLS INTERFACE m_axi port = bias1 depth = 160*7
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

#pragma HLS INTERFACE m_axi port = kernel2 depth = 19200*7
#pragma HLS INTERFACE m_axi port = bias2 depth = 240*7

#pragma HLS INTERFACE m_axi port = afterAct2 depth = 47040
//        float afterRearrangeQKX[BATCH_SIZE*n1*n2*HEAD_SIZE*HEIGHT_OUT*WIDTH_OUT*X_DIM_HEAD_SIZE];
#pragma HLS INTERFACE m_axi port = QKV depth = 47040
//        float QKV[BATCH_SIZE*n1*n2 * NEW_CHANNEL_OUT * HEIGHT_OUT * WIDTH_OUT];
#pragma HLS INTERFACE m_axi port = buffer_out depth = 47040
//        float buffer_out[BATCH_SIZE][NEW_CHANNEL_OUT][h1*n1][w1*n2];
#pragma HLS INTERFACE m_axi port = buffer_result bundle  = gmem0 depth = 47040

    

    #pragma HLS INTERFACE m_axi port = dw_conv_1_filter depth = 6000*7 //25*240
    #pragma HLS INTERFACE m_axi port = dw_norm_1_weight depth = 240*7
    #pragma HLS INTERFACE m_axi port = dw_norm_1_bias depth = 240*7
    #pragma HLS INTERFACE m_axi port = dw_norm_1_mean depth = 240*7
    #pragma HLS INTERFACE m_axi port = dw_norm_1_var depth = 240*7
    
    #pragma HLS INTERFACE m_axi port = proj_1_weight depth = 19200*7

    #pragma HLS INTERFACE m_axi port = Y_dw_conv_1 bundle = gmem3 depth = 47040
    #pragma HLS INTERFACE m_axi port = Y_dw_norm_1 bundle = gmem0 depth = 47040
    #pragma HLS INTERFACE m_axi port = Y_dw_act_1 bundle = gmem2 depth = 47040
    #pragma HLS INTERFACE m_axi port = Y_proj_1 bundle = gmem1 depth = 15680
    #pragma HLS INTERFACE m_axi port = Y_dw_skip_1 bundle = gmem3 depth = 47040
    #pragma HLS INTERFACE m_axi port = Y_skip_1 bundle = gmem2 depth = 15680

    float norm1_mean_l1[80], norm1_mean_l2[80], norm1_mean_l3[80], norm1_mean_l4[80], norm1_mean_l5[80], norm1_mean_l6[80], norm1_mean_l7[80];
    float norm1_var_l1[80], norm1_var_l2[80], norm1_var_l3[80], norm1_var_l4[80], norm1_var_l5[80], norm1_var_l6[80], norm1_var_l7[80];
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
    split_data_to7(norm1_mean, norm1_mean_l1, norm1_mean_l2, norm1_mean_l3, norm1_mean_l4, norm1_mean_l5, norm1_mean_l6, norm1_mean_l7, 80);
    split_data_to7(norm1_var, norm1_var_l1, norm1_var_l2, norm1_var_l3, norm1_var_l4, norm1_var_l5, norm1_var_l6, norm1_var_l7, 80);
    split_data_to7(norm1_weight, norm1_weight_l1, norm1_weight_l2, norm1_weight_l3, norm1_weight_l4, norm1_weight_l5, norm1_weight_l6, norm1_weight_l7, 80);
    split_data_to7(norm1_bias, norm1_bias_l1, norm1_bias_l2, norm1_bias_l3, norm1_bias_l4, norm1_bias_l5, norm1_bias_l6, norm1_bias_l7, 80);
    
    split_data_to7(kernel1, kernel1_l1, kernel1_l2, kernel1_l3, kernel1_l4, kernel1_l5, kernel1_l6, kernel1_l7, 12800);
    split_data_to7(bias1, bias1_l1, bias1_l2, bias1_l3, bias1_l4, bias1_l5, bias1_l6, bias1_l7, 160);
    split_data_to7(kernel2, kernel2_l1, kernel2_l2, kernel2_l3, kernel2_l4, kernel2_l5, kernel2_l6, kernel2_l7, 19200);
    split_data_to7(bias2, bias2_l1, bias2_l2, bias2_l3, bias2_l4, bias2_l5, bias2_l6, bias2_l7, 240);

    split_data_to7(dw_conv_1_filter, dw_conv_1_filter_l1, dw_conv_1_filter_l2, dw_conv_1_filter_l3, dw_conv_1_filter_l4, dw_conv_1_filter_l5, dw_conv_1_filter_l6, dw_conv_1_filter_l7, 6000);
    split_data_to7(dw_norm_1_weight, dw_norm_1_weight_l1, dw_norm_1_weight_l2, dw_norm_1_weight_l3, dw_norm_1_weight_l4, dw_norm_1_weight_l5, dw_norm_1_weight_l6, dw_norm_1_weight_l7, 240);
    split_data_to7(dw_norm_1_bias, dw_norm_1_bias_l1, dw_norm_1_bias_l2, dw_norm_1_bias_l3, dw_norm_1_bias_l4, dw_norm_1_bias_l5, dw_norm_1_bias_l6, dw_norm_1_bias_l7, 240);
    split_data_to7(dw_norm_1_mean, dw_norm_1_mean_l1, dw_norm_1_mean_l2, dw_norm_1_mean_l3, dw_norm_1_mean_l4, dw_norm_1_mean_l5, dw_norm_1_mean_l6, dw_norm_1_mean_l7, 240);
    split_data_to7(dw_norm_1_var, dw_norm_1_var_l1, dw_norm_1_var_l2, dw_norm_1_var_l3, dw_norm_1_var_l4, dw_norm_1_var_l5, dw_norm_1_var_l6, dw_norm_1_var_l7, 240);

    float afterNorm_l2[15680];
    float afterPad_l2[15680];
    iRMB(buffer_DataIn_1,
            afterNorm,
            norm1_mean_l1, norm1_var_l1, norm1_weight_l1, norm1_bias_l1,
            afterPad,
            afterRearrangeX,
            afterPad1,
            afterConv1,
            kernel1_l1,
            bias1_l1,
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
            kernel2_l1,
            bias2_l1,
            afterAct2,
            QKV,
            buffer_out,
            buffer_result,
            dw_conv_1_filter_l1, dw_norm_1_weight_l1, dw_norm_1_bias_l1, dw_norm_1_mean_l1, dw_norm_1_var_l1,
            proj_1_weight, Y_dw_conv_1, Y_dw_norm_1, Y_dw_act_1, Y_proj_1,
            Y_dw_skip_1, iRMB_out1
            );
    iRMB(iRMB_out1,
            afterNorm,
            norm1_mean_l2, norm1_var_l2, norm1_weight_l2, norm1_bias_l2,
            afterPad,
            afterRearrangeX,
            afterPad1,
            afterConv1,
            kernel1_l2,
            bias1_l2,
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
            kernel2_l2,
            bias2_l2,
            afterAct2,
            QKV,
            buffer_out,
            buffer_result,
            dw_conv_1_filter_l2, dw_norm_1_weight_l2, dw_norm_1_bias_l2, dw_norm_1_mean_l2, dw_norm_1_var_l2,
            proj_1_weight, Y_dw_conv_1, Y_dw_norm_1, Y_dw_act_1, Y_proj_1,
            Y_dw_skip_1, iRMB_out2
            );
    iRMB(iRMB_out2,
            afterNorm,
            norm1_mean_l3, norm1_var_l3, norm1_weight_l3, norm1_bias_l3,
            afterPad,
            afterRearrangeX,
            afterPad1,
            afterConv1,
            kernel1_l3,
            bias1_l3,
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
            kernel2_l3,
            bias2_l3,
            afterAct2,
            QKV,
            buffer_out,
            buffer_result,
            dw_conv_1_filter_l3, dw_norm_1_weight_l3, dw_norm_1_bias_l3, dw_norm_1_mean_l3, dw_norm_1_var_l3,
            proj_1_weight, Y_dw_conv_1, Y_dw_norm_1, Y_dw_act_1, Y_proj_1,
            Y_dw_skip_1,iRMB_out3
            );
    iRMB(iRMB_out3,
            afterNorm,
            norm1_mean_l4, norm1_var_l4, norm1_weight_l4, norm1_bias_l4,
            afterPad,
            afterRearrangeX,
            afterPad1,
            afterConv1,
            kernel1_l4,
            bias1_l4,
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
            kernel2_l4,
            bias2_l4,
            afterAct2,
            QKV,
            buffer_out,
            buffer_result,
            dw_conv_1_filter_l4, dw_norm_1_weight_l4, dw_norm_1_bias_l4, dw_norm_1_mean_l4, dw_norm_1_var_l4,
            proj_1_weight, Y_dw_conv_1, Y_dw_norm_1, Y_dw_act_1, Y_proj_1,
            Y_dw_skip_1, iRMB_out4
            );
    iRMB(iRMB_out4,
            afterNorm,
            norm1_mean_l5, norm1_var_l5, norm1_weight_l5, norm1_bias_l5,
            afterPad,
            afterRearrangeX,
            afterPad1,
            afterConv1,
            kernel1_l5,
            bias1_l5,
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
            kernel2_l5,
            bias2_l5,
            afterAct2,
            QKV,
            buffer_out,
            buffer_result,
            dw_conv_1_filter_l5, dw_norm_1_weight_l5, dw_norm_1_bias_l5, dw_norm_1_mean_l5, dw_norm_1_var_l5,
            proj_1_weight, Y_dw_conv_1, Y_dw_norm_1, Y_dw_act_1, Y_proj_1,
            Y_dw_skip_1, iRMB_out5
            );
    iRMB(iRMB_out5,
            afterNorm,
            norm1_mean_l6, norm1_var_l6, norm1_weight_l6, norm1_bias_l6,
            afterPad,
            afterRearrangeX,
            afterPad1,
            afterConv1,
            kernel1_l6,
            bias1_l6,
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
            kernel2_l6,
            bias2_l6,
            afterAct2,
            QKV,
            buffer_out,
            buffer_result,
            dw_conv_1_filter_l6, dw_norm_1_weight_l6, dw_norm_1_bias_l6, dw_norm_1_mean_l6, dw_norm_1_var_l6,
            proj_1_weight, Y_dw_conv_1, Y_dw_norm_1, Y_dw_act_1, Y_proj_1,
            Y_dw_skip_1, iRMB_out6
            );
    iRMB(iRMB_out6,
            afterNorm,
            norm1_mean_l7, norm1_var_l7, norm1_weight_l7, norm1_bias_l7,
            afterPad,
            afterRearrangeX,
            afterPad1,
            afterConv1,
            kernel1_l7,
            bias1_l7,
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
            kernel2_l7,
            bias2_l7,
            afterAct2,
            QKV,
            buffer_out,
            buffer_result,
            dw_conv_1_filter_l7, dw_norm_1_weight_l7, dw_norm_1_bias_l7, dw_norm_1_mean_l7, dw_norm_1_var_l7,
            proj_1_weight, Y_dw_conv_1, Y_dw_norm_1, Y_dw_act_1, Y_proj_1,
            Y_dw_skip_1, Y_skip_1
            );
    
    }
}