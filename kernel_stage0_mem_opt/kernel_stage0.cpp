// Includes
#include <hls_math.h>
#include <hls_stream.h>
#include <stdint.h>
#include "kernel_stage0.hpp"

void Compute_mean(float* inp, float* out, int* X_num, float* compute_tmp) {
    int XN = X_num[0];
    int XC = X_num[1];
    int XH = X_num[2];
    int XW = X_num[3];
    
    float temp = 0;
    float total_num = XH * XW;
    for (int n = 0; n < XN; n++) {
        for (int c = 0; c < XC; c++) {
            temp = 0;
            for (int h = 0; h < XH; h++) {
                for (int w = 0; w < XW; w++) {
                    compute_tmp[n*XC*XH*XW + c*XH*XW + h*XW + w] = inp[n*XC*XH*XW + c*XH*XW + h*XW + w];
                    temp += inp[n*XC*XH*XW + c*XH*XW + h*XW + w];
                }
            }
            out[n*XC + c] = temp / total_num;
        }
    }
}

void Sigmoid(float* inp, int* X_num){
    int XN = X_num[0];
    int XC = X_num[1];
    int XH = X_num[2];
    int XW = X_num[3];

    int y_pos = 0;
    float temp = 0;
    for (int n = 0; n < XN; n++) {
        for (int c = 0; c < XC; c++) {
            for (int h = 0; h < XH; h++) {
                for (int w = 0; w < XW; w++) {
                    y_pos = n*XC*XH*XW + c*XH*XW + h*XW + w;
                    temp = inp[n*XC*XH*XW + c*XH*XW + h*XW + w];
                    inp[y_pos] = 1 / (1 + exp(-temp));
                }
            }
        }
    }
}
void Compute_mul(float* inp, float* features, int* X_num) {
    int XN = X_num[0];
    int XC = X_num[1];
    int XH = X_num[2];
    int XW = X_num[3];

    float scale;
    int pos;
    for (int b = 0; b < XN; b++) {
        for (int c = 0; c < XC; c++) {
            scale = features[b*XC + c];
            for (int h = 0; h < XH; h++) {
                for (int w = 0; w < XW; w++) {
                    pos = b*XC*XH*XW + c*XH*XW + h*XW + w;
                    inp[pos] = inp[pos] * scale;
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
    for(int i = 0; i <150528; i++) img[i] = X_data[i];
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
    
#pragma HLS bind_storage variable=img type=RAM_T2P impl=URAM
#pragma HLS bind_storage variable=compute_tmp type=RAM_T2P impl=URAM
#pragma HLS bind_storage variable=params type=RAM_1WNR

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

    float* off_img = (img+(24*112*112));

    //Mspatch
    //group=1 as normal convolution
    DW_conv(img, off_img, msp_conv_weight, msp_conv_bias, shape_para, conv_para);
    BatchNorm(off_img, msp_num, msp_norm_running_mean, msp_norm_running_var, msp_norm_weight, msp_norm_bias);

    //Depth-Wise Conv
    reset_arr(img, dw_norm_num);
    DW_conv(off_img, img, dw_conv_weight, nullptr, dw_shape_num, dw_conv_num);
    BatchNorm(img, dw_norm_num, norm_1_running_mean, norm_1_running_var, norm_1_weight, norm_1_bias);
    SiLU(img, dw_norm_num);
        //for(int i = 0; i < 24*112*112; i++) Y_msp_conv[i] = img[i];
    
    //SE
    reset_arr(off_img, dw_norm_num);
    Compute_mean(img, off_img, se_data_num, compute_tmp);
    //reset_arr(off_img, dw_norm_num);
    Pointwise_conv(off_img, img, se_conv_reduce_weight, se_conv_reduce_bias, 1, 24, 24, 1, 1, 1);
    SiLU(img, X_reduce_num);
    reset_arr(off_img, dw_norm_num);
    Pointwise_conv(img, off_img, se_conv_expand_weight, se_conv_expand_bias, 1, 24, 24, 1, 1, 1);
    Sigmoid(off_img, X_expand_num);
    Compute_mul(compute_tmp, off_img, se_data_num);

    //Projection
    reset_arr(off_img, dw_norm_num);
    Pointwise_conv(compute_tmp, off_img, proj_conv_weight, nullptr, 1, 24, 24, 112, 112, 0);
    
    for(int i = 0; i < 24*112*112; i++) Y_proj[i] = off_img[i];
    
    }
}