// Includes
#include <hls_math.h>
#include <hls_stream.h>
#include <stdint.h>
#include "kernel_stage0.hpp"

void Compute_mean(float* X_data, int* X_num, float* Y_data) {
    int XN = X_num[0];
    int XC = X_num[1];
    int XH = X_num[2];
    int XW = X_num[3];

    float total_num = XH * XW;
    for (int n = 0; n < XN; n++) {
        for (int c = 0; c < XC; c++) {
            float temp = 0;
            for (int h = 0; h < XH; h++) {
                for (int w = 0; w < XW; w++) {
                    temp += X_data[n*XC*XH*XW + c*XH*XW + h*XW + w];
                }
            }
            Y_data[n*XC + c] = temp / total_num;
        }
    }
}

void Sigmoid(float* X_data, float* Y_data, int* X_num){
    int XN = X_num[0];
    int XC = X_num[1];
    int XH = X_num[2];
    int XW = X_num[3];

    for (int n = 0; n < XN; n++) {
        for (int c = 0; c < XC; c++) {
            for (int h = 0; h < XH; h++) {
                for (int w = 0; w < XW; w++) {
                    int y_pos = n*XC*XH*XW + c*XH*XW + h*XW + w;
                    float temp = X_data[n*XC*XH*XW + c*XH*XW + h*XW + w];
                    Y_data[y_pos] = 1 / (1 + exp(-temp));
                }
            }
        }
    }
}
void Compute_mul(float* X_data, float* feature, float* Y_data, int* X_num) {
    int XN = X_num[0];
    int XC = X_num[1];
    int XH = X_num[2];
    int XW = X_num[3];

    float scale;
    int pos;
    for (int b = 0; b < XN; b++) {
        for (int c = 0; c < XC; c++) {
            scale = feature[b*XC + c];
            for (int h = 0; h < XH; h++) {
                for (int w = 0; w < XW; w++) {
                    pos = b*XC*XH*XW + c*XH*XW + h*XW + w;
                    Y_data[pos] = X_data[pos] * scale;
                }
            }
        }
    }
}

extern "C"
{
    void kernel_stage0(float* X_data, float* msp_conv_weight, float* msp_conv_bias, float* msp_norm_weight, float* msp_norm_bias, float* msp_norm_running_mean, float* msp_norm_running_var,
                    float* dw_conv_weight, float* norm_1_weight, float* norm_1_bias, float* norm_1_running_mean, float* norm_1_running_var,
                    float* se_conv_reduce_weight, float* se_conv_reduce_bias, float* se_conv_expand_weight, float* se_conv_expand_bias,
                    float* proj_conv_weight, float* Y_msp_conv, float* Y_msp_norm, float* Y_dw_conv, float* Y_dw_norm, float* Y_dw_act, float* Y_se_mean, float* Y_se_reduce, 
                    float* Y_se_act, float* Y_se_expand, float* Y_se_sigmoid, float* Y_se, float* Y_proj)
    {
    #pragma HLS INTERFACE m_axi port = X_data bundle = gmem0 depth = 150528
    #pragma HLS INTERFACE m_axi port = msp_conv_weight depth = 648
    #pragma HLS INTERFACE m_axi port = msp_conv_bias depth = 24
    #pragma HLS INTERFACE m_axi port = msp_norm_weight depth = 24
    #pragma HLS INTERFACE m_axi port = msp_norm_bias depth = 24
    #pragma HLS INTERFACE m_axi port = msp_norm_running_mean depth = 24
    #pragma HLS INTERFACE m_axi port = msp_norm_running_var depth = 24
    #pragma HLS INTERFACE m_axi port = dw_conv_weight depth = 216
    #pragma HLS INTERFACE m_axi port = norm_1_weight depth = 24
    #pragma HLS INTERFACE m_axi port = norm_1_bias depth = 24
    #pragma HLS INTERFACE m_axi port = norm_1_running_mean depth = 24
    #pragma HLS INTERFACE m_axi port = norm_1_running_var depth = 24
    #pragma HLS INTERFACE m_axi port = se_conv_reduce_weight depth = 576
    #pragma HLS INTERFACE m_axi port = se_conv_reduce_bias depth = 24
    #pragma HLS INTERFACE m_axi port = se_conv_expand_weight depth = 576
    #pragma HLS INTERFACE m_axi port = se_conv_expand_bias depth = 24
    #pragma HLS INTERFACE m_axi port = proj_conv_weight depth = 576

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

    int X_num[4] = {1, 3, 224, 224};
    int shape_para[7] = {1, 3, 224, 224, 24, 112, 112};
    int conv_para[6] = {3, 1, 2, 1, 1, 3};
    int msp_num[4] = {1, 24, 112, 112};

    int dw_shape_num[7] = {1, 24, 112, 112, 24, 112, 112};
    int dw_conv_num[6] = {3, 0, 1, 1, 24, 1};
    int dw_norm_num[4] = {1, 24, 112, 112};

    int se_data_num[4] = {1, 24, 112, 112};
    int X_reduce_num[4] = {1, 24, 1, 1};
    int X_expand_num[4] = {1, 24, 1, 1};

    //Mspatch
    //group=1 as normal convolution
    DW_conv(X_data, msp_conv_weight, msp_conv_bias, shape_para, conv_para, Y_msp_conv);
    BatchNorm(Y_msp_conv, Y_msp_norm, msp_num, msp_norm_running_mean, msp_norm_running_var, msp_norm_weight, msp_norm_bias);

    //Depth-Wise Conv
    DW_conv(Y_msp_norm, dw_conv_weight, nullptr, dw_shape_num, dw_conv_num, Y_dw_conv);
    BatchNorm(Y_dw_conv, Y_dw_norm, dw_norm_num, norm_1_running_mean, norm_1_running_var, norm_1_weight, norm_1_bias);
    SiLU(Y_dw_norm, Y_dw_act, dw_norm_num);

    
    //SE
    Compute_mean(Y_dw_act, se_data_num, Y_se_mean);
    Pointwise_conv(Y_se_mean, Y_se_reduce, se_conv_reduce_weight, se_conv_reduce_bias, 1, 24, 24, 1, 1, 1);
    SiLU(Y_se_reduce, Y_se_act, X_reduce_num);
    Pointwise_conv(Y_se_act, Y_se_expand, se_conv_expand_weight, se_conv_expand_bias, 1, 24, 24, 1, 1, 1);
    Sigmoid(Y_se_expand, Y_se_sigmoid, X_expand_num);
    Compute_mul(Y_dw_act, Y_se_sigmoid, Y_se, se_data_num);

    //Projection
    Pointwise_conv(Y_se, Y_proj, proj_conv_weight, nullptr, 1, 24, 24, 112, 112, 0);
    
    }
}