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
    //ReLU(norm_out, act_out, dw_X_num, zp);
    SiLU(norm_out, act_out, dw_X_num);
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
            float *afterRearrangeX,
            float *afterConv1,
            float *kernel1,
            float *bias1,
            float *in_q,
            float *in_k,
            float *afterQKMultiplication,
            float *afterSoftmax,
            float *afterRearrangeX2,
            float *afterQKXMultiplication,
            float *afterRearrangeQKX,
            float *afterConv2,
            float *kernel2,
            float *bias2,
            float *afterAct2,
            float *buffer_out,
            float *buffer_result,
            float* dw_conv_1_filter, float* dw_norm_1_weight, float* dw_norm_1_bias, float* dw_norm_1_mean, float* dw_norm_1_var,
            float* proj_1_weight,
            float* Y_dw_conv_1, float* Y_dw_norm_1, float* Y_dw_act_1, float* Y_proj_1,
            float* Y_dw_skip_1, float* Y_skip_1)
{
    // depth 1-7
    int norm_1_X_num[4] = {1, 80, 14, 14};
    int dw_conv_1_shape_para[7] = {1, 240, 14, 14, 240, 14, 14};
    int dw_conv_1_conv_para[6] = {5, 0, 1, 2, 240, 1};
    int dw_1_X_num[4] = {1, 240, 14, 14};


    // depth 1-7
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
                              afterRearrangeX,
                              afterConv1,
                              kernel1,
                              bias1,
                              in_q,
                              in_k,
                              afterQKMultiplication,
                              afterSoftmax,
                              afterRearrangeX2,
                              afterQKXMultiplication,
                              afterRearrangeQKX,
                              afterConv2,
                              kernel2,
                              bias2,
                              afterAct2,
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

void clear_data(
    float* afterNorm, float *afterRearrangeX, float *afterConv1,
    float *in_q, float *in_k,
    float *afterQKMultiplication, float *afterSoftmax, float *afterRearrangeX2, float *afterQKXMultiplication,
    float *afterRearrangeQKX, float *afterConv2, float *afterAct2,
    float *buffer_out, float *buffer_result,
    float* Y_dw_conv_1, float* Y_dw_norm_1, float* Y_dw_act_1, float* Y_proj_1, float* Y_dw_skip_1
){
    for(int i=0;i<15680;i++){
        afterNorm[i]=0;
        afterRearrangeX[i]=0;
    }
    for(int i=0;i<31360;i++){
        afterConv1[i]=0;
    }
    for(int i=0;i<15680;i++){
        in_q[i]=0;
        in_k[i]=0;
    }
    for(int i=0;i<38416;i++){
        afterQKMultiplication[i]=0;
        afterSoftmax[i]=0;
    }
    for(int i=0;i<15680;i++){
        afterRearrangeX2[i]=0;
        afterQKXMultiplication[i]=0;
        afterRearrangeQKX[i]=0;
    }
    for(int i=0;i<47040;i++){
        afterConv2[i]=0;
        afterAct2[i]=0;
        buffer_out[i]=0;
        buffer_result[i]=0;
        Y_dw_conv_1[i] = 0;
        Y_dw_norm_1[i] = 0;
        Y_dw_act_1[i] = 0;
        Y_dw_skip_1[i] = 0;
    }
    for (int i = 0; i < 15680; i++)
    {
        Y_proj_1[i] = 0;
    }

}
extern "C"
{
    void kernel_stage3(float* X_data, float* norm_0_weight, float* norm_0_bias, float* v_conv_0_weight, float* v_conv_0_bias,
                        float* dw_conv_0_filter, float* dw_norm_0_weight, float* dw_norm_0_bias, float* dw_norm_0_mean, float* dw_norm_0_var,
                        float* proj_0_weight, float* Y_norm_0, float* Y_v_conv_0, float* Y_v_act_0, float* Y_dw_conv_0, float* Y_dw_norm_0, float* Y_dw_act_0,
                        float* result_30, float *afterNorm,
                        float *norm1_mean, float *norm1_var, float *norm1_weight, float *norm1_bias, 
                        float *afterRearrangeX,
                        float *afterConv1,
                        float *kernel1,
                        float *bias1,
                        float *in_q,
                        float *in_k,
                        float *afterQKMultiplication,
                        float *afterSoftmax,
                        float *afterRearrangeX2,
                        float *afterQKXMultiplication,
                        float *afterRearrangeQKX,
                        float *afterConv2,
                        float *kernel2,
                        float *bias2,
                        float *afterAct2,
                        float *buffer_out,
                        float *buffer_result,
                        float* dw_conv_1_filter, float* dw_norm_1_weight, float* dw_norm_1_bias, float* dw_norm_1_mean, float* dw_norm_1_var,
                        float* proj_1_weight,
                        float* Y_dw_conv_1, float* Y_dw_norm_1, float* Y_dw_act_1, float* Y_proj_1,
                        float* Y_dw_skip_1, float* Y_skip_1)
{

#pragma HLS INTERFACE m_axi port = X_data bundle = gmem0 depth = 37632

    // depth 0
    #pragma HLS INTERFACE m_axi port = norm_0_weight depth = 48
    #pragma HLS INTERFACE m_axi port = norm_0_bias depth = 48

    #pragma HLS INTERFACE m_axi port = v_conv_0_weight depth = 13824
    #pragma HLS INTERFACE m_axi port = v_conv_0_bias depth = 288

    #pragma HLS INTERFACE m_axi port = dw_conv_0_filter depth = 7200
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

    //depth1-7
    #pragma HLS INTERFACE m_axi port = afterNorm bundle = gmem1 depth = 15680
    #pragma HLS INTERFACE m_axi port = norm1_mean depth = 196 //*7
    #pragma HLS INTERFACE m_axi port = norm1_var depth = 196 //*7
    #pragma HLS INTERFACE m_axi port = norm1_weight depth = 80*7
    #pragma HLS INTERFACE m_axi port = norm1_bias depth = 80*7

    #pragma HLS INTERFACE m_axi port = afterRearrangeX depth = 15680
    #pragma HLS INTERFACE m_axi port = afterConv1 depth = 31360

    #pragma HLS INTERFACE m_axi port = kernel1 depth = 12800*7
    #pragma HLS INTERFACE m_axi port = bias1 depth = 160*7
    #pragma HLS INTERFACE m_axi port = in_q depth = 15680
    #pragma HLS INTERFACE m_axi port = in_k depth = 15680
    #pragma HLS INTERFACE m_axi port = afterQKMultiplication depth = 38416
    #pragma HLS INTERFACE m_axi port = afterSoftmax depth = 38416
    #pragma HLS INTERFACE m_axi port = afterRearrangeX2 depth = 15680
    #pragma HLS INTERFACE m_axi port = afterQKXMultiplication depth = 15680
    #pragma HLS INTERFACE m_axi port = afterRearrangeQKX depth = 15680
    #pragma HLS INTERFACE m_axi port = afterConv2 depth = 47040

    #pragma HLS INTERFACE m_axi port = kernel2 depth = 19200*7
    #pragma HLS INTERFACE m_axi port = bias2 depth = 240*7

    #pragma HLS INTERFACE m_axi port = afterAct2 depth = 47040
    #pragma HLS INTERFACE m_axi port = buffer_out depth = 47040
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

    
    // depth 1-7
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
    //split_data_to7(norm1_mean, norm1_mean_l1, norm1_mean_l2, norm1_mean_l3, norm1_mean_l4, norm1_mean_l5, norm1_mean_l6, norm1_mean_l7, 196);
    //split_data_to7(norm1_var, norm1_var_l1, norm1_var_l2, norm1_var_l3, norm1_var_l4, norm1_var_l5, norm1_var_l6, norm1_var_l7, 196);
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

    split_data_to7(proj_1_weight, proj_1_weight_l1, proj_1_weight_l2, proj_1_weight_l3, proj_1_weight_l4, proj_1_weight_l5, proj_1_weight_l6, proj_1_weight_l7, 19200);
    float afterNorm_l2[15680];
    float afterPad_l2[15680];
    iRMB(result_30,
            afterNorm,
            norm1_mean, norm1_var, norm1_weight_l1, norm1_bias_l1,
            afterRearrangeX,
            afterConv1,
            kernel1_l1,
            bias1_l1,
            in_q,
            in_k,
            afterQKMultiplication,
            afterSoftmax,
            afterRearrangeX2,
            afterQKXMultiplication,
            afterRearrangeQKX,
            afterConv2,
            kernel2_l1,
            bias2_l1,
            afterAct2,
            buffer_out,
            buffer_result,
            dw_conv_1_filter_l1, dw_norm_1_weight_l1, dw_norm_1_bias_l1, dw_norm_1_mean_l1, dw_norm_1_var_l1,
            proj_1_weight_l1, Y_dw_conv_1, Y_dw_norm_1, Y_dw_act_1, Y_proj_1,
            Y_dw_skip_1, iRMB_out1
            );
    clear_data(
        afterNorm,afterRearrangeX, afterConv1,
        in_q, in_k,
        afterQKMultiplication, afterSoftmax, afterRearrangeX2, afterQKXMultiplication,
        afterRearrangeQKX, afterConv2, afterAct2,
        buffer_out, buffer_result,
         Y_dw_conv_1,  Y_dw_norm_1,  Y_dw_act_1,  Y_proj_1,  Y_dw_skip_1
    );
    iRMB(iRMB_out1,
            afterNorm,
            norm1_mean, norm1_var, norm1_weight_l2, norm1_bias_l2,
            afterRearrangeX,
            afterConv1,
            kernel1_l2,
            bias1_l2,
            in_q,
            in_k,
            afterQKMultiplication,
            afterSoftmax,
            afterRearrangeX2,
            afterQKXMultiplication,
            afterRearrangeQKX,
            afterConv2,
            kernel2_l2,
            bias2_l2,
            afterAct2,
            buffer_out,
            buffer_result,
            dw_conv_1_filter_l2, dw_norm_1_weight_l2, dw_norm_1_bias_l2, dw_norm_1_mean_l2, dw_norm_1_var_l2,
            proj_1_weight_l2, Y_dw_conv_1, Y_dw_norm_1, Y_dw_act_1, Y_proj_1,
            Y_dw_skip_1, iRMB_out2
            );
    clear_data(
        afterNorm,afterRearrangeX, afterConv1,
        in_q, in_k,
        afterQKMultiplication, afterSoftmax, afterRearrangeX2, afterQKXMultiplication,
        afterRearrangeQKX, afterConv2, afterAct2,
        buffer_out, buffer_result,
         Y_dw_conv_1,  Y_dw_norm_1,  Y_dw_act_1,  Y_proj_1,  Y_dw_skip_1
    );
    iRMB(iRMB_out2,
            afterNorm,
            norm1_mean, norm1_var, norm1_weight_l3, norm1_bias_l3,
            afterRearrangeX,
            afterConv1,
            kernel1_l3,
            bias1_l3,
            in_q,
            in_k,
            afterQKMultiplication,
            afterSoftmax,
            afterRearrangeX2,
            afterQKXMultiplication,
            afterRearrangeQKX,
            afterConv2,
            kernel2_l3,
            bias2_l3,
            afterAct2,
            buffer_out,
            buffer_result,
            dw_conv_1_filter_l3, dw_norm_1_weight_l3, dw_norm_1_bias_l3, dw_norm_1_mean_l3, dw_norm_1_var_l3,
            proj_1_weight_l3, Y_dw_conv_1, Y_dw_norm_1, Y_dw_act_1, Y_proj_1,
            Y_dw_skip_1,iRMB_out3
            );
    clear_data(
        afterNorm,afterRearrangeX, afterConv1,
        in_q, in_k,
        afterQKMultiplication, afterSoftmax, afterRearrangeX2, afterQKXMultiplication,
        afterRearrangeQKX, afterConv2, afterAct2,
        buffer_out, buffer_result,
         Y_dw_conv_1,  Y_dw_norm_1,  Y_dw_act_1,  Y_proj_1,  Y_dw_skip_1
    );
    iRMB(iRMB_out3,
            afterNorm,
            norm1_mean, norm1_var, norm1_weight_l4, norm1_bias_l4,
            afterRearrangeX,
            afterConv1,
            kernel1_l4,
            bias1_l4,
            in_q,
            in_k,
            afterQKMultiplication,
            afterSoftmax,
            afterRearrangeX2,
            afterQKXMultiplication,
            afterRearrangeQKX,
            afterConv2,
            kernel2_l4,
            bias2_l4,
            afterAct2,
            buffer_out,
            buffer_result,
            dw_conv_1_filter_l4, dw_norm_1_weight_l4, dw_norm_1_bias_l4, dw_norm_1_mean_l4, dw_norm_1_var_l4,
            proj_1_weight_l4, Y_dw_conv_1, Y_dw_norm_1, Y_dw_act_1, Y_proj_1,
            Y_dw_skip_1, iRMB_out4
            );
    clear_data(
        afterNorm,afterRearrangeX, afterConv1,
        in_q, in_k,
        afterQKMultiplication, afterSoftmax, afterRearrangeX2, afterQKXMultiplication,
        afterRearrangeQKX, afterConv2, afterAct2,
        buffer_out, buffer_result,
         Y_dw_conv_1,  Y_dw_norm_1,  Y_dw_act_1,  Y_proj_1,  Y_dw_skip_1
    );
    iRMB(iRMB_out4,
            afterNorm,
            norm1_mean, norm1_var, norm1_weight_l5, norm1_bias_l5,
            afterRearrangeX,
            afterConv1,
            kernel1_l5,
            bias1_l5,
            in_q,
            in_k,
            afterQKMultiplication,
            afterSoftmax,
            afterRearrangeX2,
            afterQKXMultiplication,
            afterRearrangeQKX,
            afterConv2,
            kernel2_l5,
            bias2_l5,
            afterAct2,
            buffer_out,
            buffer_result,
            dw_conv_1_filter_l5, dw_norm_1_weight_l5, dw_norm_1_bias_l5, dw_norm_1_mean_l5, dw_norm_1_var_l5,
            proj_1_weight_l5, Y_dw_conv_1, Y_dw_norm_1, Y_dw_act_1, Y_proj_1,
            Y_dw_skip_1, iRMB_out5
            );
    clear_data(
        afterNorm,afterRearrangeX, afterConv1,
        in_q, in_k,
        afterQKMultiplication, afterSoftmax, afterRearrangeX2, afterQKXMultiplication,
        afterRearrangeQKX, afterConv2, afterAct2,
        buffer_out, buffer_result,
         Y_dw_conv_1,  Y_dw_norm_1,  Y_dw_act_1,  Y_proj_1,  Y_dw_skip_1
    );
    iRMB(iRMB_out5,
            afterNorm,
            norm1_mean, norm1_var, norm1_weight_l6, norm1_bias_l6,
            afterRearrangeX,
            afterConv1,
            kernel1_l6,
            bias1_l6,
            in_q,
            in_k,
            afterQKMultiplication,
            afterSoftmax,
            afterRearrangeX2,
            afterQKXMultiplication,
            afterRearrangeQKX,
            afterConv2,
            kernel2_l6,
            bias2_l6,
            afterAct2,
            buffer_out,
            buffer_result,
            dw_conv_1_filter_l6, dw_norm_1_weight_l6, dw_norm_1_bias_l6, dw_norm_1_mean_l6, dw_norm_1_var_l6,
            proj_1_weight_l6, Y_dw_conv_1, Y_dw_norm_1, Y_dw_act_1, Y_proj_1,
            Y_dw_skip_1, iRMB_out6
            );
    clear_data(
        afterNorm,afterRearrangeX, afterConv1,
        in_q, in_k,
        afterQKMultiplication, afterSoftmax, afterRearrangeX2, afterQKXMultiplication,
        afterRearrangeQKX, afterConv2, afterAct2,
        buffer_out, buffer_result,
         Y_dw_conv_1,  Y_dw_norm_1,  Y_dw_act_1,  Y_proj_1,  Y_dw_skip_1
    );
    iRMB(iRMB_out6,
            afterNorm,
            norm1_mean, norm1_var, norm1_weight_l7, norm1_bias_l7,
            afterRearrangeX,
            afterConv1,
            kernel1_l7,
            bias1_l7,
            in_q,
            in_k,
            afterQKMultiplication,
            afterSoftmax,
            afterRearrangeX2,
            afterQKXMultiplication,
            afterRearrangeQKX,
            afterConv2,
            kernel2_l7,
            bias2_l7,
            afterAct2,
            buffer_out,
            buffer_result,
            dw_conv_1_filter_l7, dw_norm_1_weight_l7, dw_norm_1_bias_l7, dw_norm_1_mean_l7, dw_norm_1_var_l7,
            proj_1_weight_l7, Y_dw_conv_1, Y_dw_norm_1, Y_dw_act_1, Y_proj_1,
            Y_dw_skip_1, Y_skip_1
            );
    }
}