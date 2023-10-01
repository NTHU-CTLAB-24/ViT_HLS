// Includes
#include <hls_math.h>
#include <hls_stream.h>
#include <stdint.h>
#include "kernel_stage0.hpp"

void load_data(float* in, float* out, int* data_shape) {
    int batch = data_shape[0];
    int channel = data_shape[1];
    int height = data_shape[2];
    int width = data_shape[3];

    for (int b = 0; b < batch; b++) {
        for (int c = 0; c < channel; c++) {
            for (int h = 0; h < height; h++) {
                for (int w = 0; w < width; w++) {
                    int pos = b*channel*height*width + c*height*width + h*width + w;
                    out[pos] = in[pos];
                }
            }
        }
    }
}

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
    void kernel_stage0(float* X_data, float* msp_filter, float* msp_bias, float* dw_filter, float* dw_bias,
                        float* reduce_filter, float* reduce_bias, float* expand_filter, float* expand_bias, float* proj_filter,
                        float* mean1, float* var1, float* gamma1, float* beta1,
                        float* mean2, float* var2, float* gamma2, float* beta2,
                        float* X_conv, float* X_dwconv, 
                        float* X_mean, float* X_reduce, float* X_relu, float* X_expand, float* X_sigmoid,
                        float* Y_msp, float* Y_dw, float* Y_se, float* Y_proj)
    {
    #pragma HLS INTERFACE m_axi port = X_data bundle = gmem0 depth = 9408
    #pragma HLS INTERFACE m_axi port = msp_filter bundle = gmem1 depth = 648
    #pragma HLS INTERFACE m_axi port = msp_bias bundle = gmem2 depth = 24
    #pragma HLS INTERFACE m_axi port = dw_filter depth = 216
    #pragma HLS INTERFACE m_axi port = dw_bias depth = 24
    #pragma HLS INTERFACE m_axi port = reduce_filter depth = 576
    #pragma HLS INTERFACE m_axi port = reduce_bias  depth = 24
    #pragma HLS INTERFACE m_axi port = expand_filter  depth = 576
    #pragma HLS INTERFACE m_axi port = expand_bias depth = 24
    #pragma HLS INTERFACE m_axi port = proj_filter depth = 576
    #pragma HLS INTERFACE m_axi port = mean1  depth = 24
    #pragma HLS INTERFACE m_axi port = var1  depth = 24
    #pragma HLS INTERFACE m_axi port = gamma1  depth = 24
    #pragma HLS INTERFACE m_axi port = beta1  depth = 24
    #pragma HLS INTERFACE m_axi port = mean2  depth = 24
    #pragma HLS INTERFACE m_axi port = var2  depth = 24
    #pragma HLS INTERFACE m_axi port = gamma2  depth = 24
    #pragma HLS INTERFACE m_axi port = beta2  depth = 24

#pragma HLS INTERFACE m_axi port = X_conv bundle = gmem1 depth = 18816
#pragma HLS INTERFACE m_axi port = X_dwconv bundle = gmem3 depth = 18816
#pragma HLS INTERFACE m_axi port = X_mean bundle = gmem1 depth = 24
#pragma HLS INTERFACE m_axi port = X_reduce bundle = gmem2 depth = 24
#pragma HLS INTERFACE m_axi port = X_relu bundle = gmem3 depth = 24
#pragma HLS INTERFACE m_axi port = X_expand bundle = gmem1 depth = 24
#pragma HLS INTERFACE m_axi port = X_sigmoid bundle = gmem1 depth = 24

#pragma HLS INTERFACE m_axi port = Y_msp bundle = gmem1 depth = 18816
#pragma HLS INTERFACE m_axi port = Y_dw bundle = gmem2 depth = 18816
#pragma HLS INTERFACE m_axi port = Y_se bundle = gmem3 depth = 18816
#pragma HLS INTERFACE m_axi port = Y_proj bundle = gmem0 depth = 18816


    int X_num[4] = {1, 3, 56, 56};
    int shape_para[7] = {1, 3, 56, 56, 24, 28, 28};
    int conv_para[6] = {3, 1, 2, 1, 1, 3};
    int msp_num[4] = {1, 24, 28, 28};
    int msp_filter_num[7] = {24, 3, 3, 3, 1, 2, 1};

    int dw_shape_num[7] = {1, 24, 28, 28, 24, 28, 28};
    int dw_conv_num[6] = {3, 0, 1, 1, 24, 1};
    int dw_norm_num[4] = {1, 24, 28, 28};

    int se_data_num[4] = {1, 24, 28, 28};
    int X_reduce_num[4] = {1, 24, 1, 1};
    int X_expand_num[4] = {1, 24, 1, 1};


    //float X_data_copy[9408];
    //#pragma HLS bind_storage variable=X_data_copy type=RAM_1P impl=uram
    //int data_shape[4] = {1, 3, 56, 56};
    //Mspatch
    //group=1 as normal convolution
    DW_conv(X_data, msp_filter, msp_bias, shape_para, conv_para, X_conv);
    //load_data(X_data, X_data_copy, data_shape);
    //Convolution(X_data, X_num, X_conv, msp_num, msp_filter, msp_filter_num, msp_bias);
    BatchNorm(X_conv, Y_msp, msp_num, mean1, var1, gamma1, beta1);

    //Depth-Wise Conv
    DW_conv(Y_msp, dw_filter, nullptr, dw_shape_num, dw_conv_num, X_dwconv);
    BatchNorm(X_dwconv, Y_dw, dw_norm_num, mean2, var2, gamma2, beta2);
    //ReLU(X_dwnorm, Y_dwact, dw_norm_num, 0);

    
    //SE
    Compute_mean(Y_dw, se_data_num, X_mean);
    Pointwise_conv(X_mean, X_reduce, reduce_filter, reduce_bias, 1, 24, 24, 1, 1, 1);
    ReLU(X_reduce, X_relu, X_reduce_num, 0);
    Pointwise_conv(X_relu, X_expand, expand_filter, expand_bias, 1, 24, 24, 1, 1, 1);
    Sigmoid(X_expand, X_sigmoid, X_expand_num);
    Compute_mul(Y_dw, X_sigmoid, Y_se, se_data_num);

    //Projection
    Pointwise_conv(Y_se, Y_proj, proj_filter, nullptr, 1, 24, 24, 28, 28, 0);
    
    }
}