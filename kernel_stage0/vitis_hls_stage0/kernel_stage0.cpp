// Includes
#include <hls_math.h>
#include <hls_stream.h>
#include <stdint.h>
#include "kernel_stage0.hpp"

void Padding(float* X_data, float* Y_data, int* X_num, int padding) {
    //get X(input) size
    int XN = X_num[0];
    int XC = X_num[1];
    int XH = X_num[2];
    int XW = X_num[3];

    int YH = XH + 2*padding;
    int YW = XW + 2*padding;
   
   for (int n = 0; n < XN; n++) {
        for (int c = 0; c < XC; c++) {
            for (int h = 0; h < YH; h++) {
                for (int w = 0; w < YW; w++) {
                    int y_pos = n*XC*YH*YW + c*YH*YW + h*YW + w;
                    if (h<padding || h>=XH+padding || w<padding || w>=XW+padding) Y_data[y_pos] = 0;
                    else Y_data[y_pos] = X_data[n*XC*XH*XW + c*XH*XW + (h-padding)*XW + w-padding];
                }
            }
        }
   }
}


void Convolution(float* X_data, int* X_num, float* Y_data, int* Y_num,  float* filter, int* filter_num, float* bias) {
    //get X(input) size
    int XN = X_num[0];
    int XC = X_num[1];
    int XH = X_num[2];
    int XW = X_num[3];

    //get filter size
    int KC = filter_num[0];
    int KD = filter_num[1];
    int KH = filter_num[2];
    int KW = filter_num[3];
    int padding = filter_num[4];
    int stride = filter_num[5];
    int isBias = filter_num[6];

    //get Y(output) size
    int YN = Y_num[0];
    int YC = Y_num[1];
    int YH = Y_num[2];
    int YW = Y_num[3];

    int x_pos, k_pos, y_pos;
    for (int yn = 0; yn < YN; yn++) {
        for (int yh = 0; yh < YH; yh++) {
            for (int yw = 0; yw < YW; yw++) {
                for (int yc = 0; yc < YC; yc++) {
                    for (int xc = 0; xc < XC; xc++) {
                        for (int kh = 0; kh < KH; kh++) {
                            for (int kw = 0; kw < KW; kw++) {
                                x_pos = yn*XC*XH*XW + xc*XH*XW + (yh*stride+kh)*XW + (yw*stride+kw);
                                k_pos = yc*KD*KH*KW + xc*KW*KW + kh*KW + kw;
                                y_pos = yn*YC*YH*YW + yc*YH*YW + yh*YW + yw;
                                Y_data[y_pos] += X_data[x_pos] * filter[k_pos];
                            }

                        }
                    }
                    if (isBias) Y_data[y_pos] += bias[yc];
                }
            }
        }
    }
}


void BatchNorm(float* X_data, float* Y_data, int* X_num, float* running_mean, float* running_var, float* gamma, float* beta) {
    //get X(input) size
    int N = X_num[0];
    int C = X_num[1];
    int H = X_num[2];
    int W = X_num[3];
    
   for (int n = 0; n < N; n++) {
        for (int c = 0; c < C; c++) {
            for (int h = 0; h < H; h++) {
                for (int w = 0; w < W; w++) {
                    Y_data[n*C*H*W + c*H*W + h*W + w] = (X_data[n*C*H*W + c*H*W + h*W + w] - running_mean[c]) / sqrt(running_var[c] + 1e-6) * gamma[c] + beta[c];
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

    int total_num = XH * XW;
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
void ReLU(float* X_data, float* Y_data, int* X_num, int zp){
	
	for(int i = X_num[0] * X_num[1] * X_num[2] * X_num[3] - 1; i >= 0; i--) // traverse all data
		Y_data[i] = (X_data[i] > zp) ? X_data[i] : zp;
	
	return;
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

    for (int h = 0; h < XH; h++) {
        for (int w = 0; w < XW; w++) {
            for (int n = 0; n < XN; n++) {
                for (int c = 0; c < XC; c++) {
                    int pos = n*XC*XH*XW + c*XH*XW + h*XW + w;
                    float val = feature[n*XC + c];
                    Y_data[pos] = X_data[pos] * val;
                }
            }
        }
    }
}
void Mspatch(float* X_data, int* X_num, float* X_pad, float* X_conv, int* msp_num, float* filter, int* filter_num, 
                float* bias, float* running_mean, float* running_var, float* gamma, float* beta, float* Y_data) {

    int padding = filter_num[4];
    int stride = filter_num[5];

    Padding(X_data, X_pad, X_num, padding);

    
    int x_pad_num[4];
    x_pad_num[0] = X_num[0];
    x_pad_num[1] = X_num[1];
    x_pad_num[2] = X_num[2] + 2*padding;
    x_pad_num[3] = X_num[3] + 2*padding;

    Convolution(X_pad, x_pad_num, X_conv, msp_num, filter, filter_num, bias);
    BatchNorm(X_conv, Y_data, msp_num, running_mean, running_var, gamma, beta);
}

void DW_conv(float *in, float *kernel, float *bias, int *shape_para, int *conv_para, float *out)
{

    int BATCH_SIZE = shape_para[0];
    int CHANNEL_IN = shape_para[1];
    int HEIGHT_IN = shape_para[2];
    int WIDTH_IN = shape_para[3];
    int CHANNEL_OUT = shape_para[4];
    int HEIGHT_OUT = shape_para[5];
    int WIDTH_OUT = shape_para[6];

    int KERNEL_SIZE = conv_para[0];
    int isConvBias = conv_para[1];
    int STRIDE = conv_para[2];
    int PADDING = conv_para[3];
    int GROUP = conv_para[4];
    int KERNEL_CHANNEL = conv_para[5];

    int inGroupNums = CHANNEL_IN / GROUP;
    int outGroupNums = CHANNEL_OUT / GROUP;

    int kernelChannelIdx;
    int out_pos;
    int in_row;
    int in_col;
    int in_pos;
    int kernel_pos;

execute:
Batch:
    for (int batch = 0; batch < BATCH_SIZE; batch++){
    Out_Row:
        for (int row = 0; row < HEIGHT_OUT; row++)
        {
        Out_Column:
            for (int col = 0; col < WIDTH_OUT; col++)
            {
                int biasFlag = 1; // 這種迴圈架構的bias會被重複計算，需要此flag限制只加一次
            Kernel_Row:
                for (int kernel_row = 0; kernel_row < KERNEL_SIZE; kernel_row++)
                {
                Kernel_Col:
                    for (int kernel_col = 0; kernel_col < KERNEL_SIZE; kernel_col++)
                    {
                        int groupIndex = 0;
                        in_row = row * STRIDE + kernel_row - PADDING;
                        in_col = col * STRIDE + kernel_col - PADDING;
                        if (in_row < 0 || in_row >= HEIGHT_IN || in_col < 0 || in_col >= WIDTH_IN)
                            continue;
                    Output_Channel:
                        for (int out_ch = 0; out_ch < CHANNEL_OUT; out_ch++)
                        {
                            out_pos = batch * CHANNEL_OUT * HEIGHT_OUT * WIDTH_OUT + out_ch * HEIGHT_OUT * WIDTH_OUT + row * WIDTH_OUT + col;
                        In_Channel:
                            for (int in_ch = groupIndex * inGroupNums; in_ch < CHANNEL_IN; in_ch++)
                            {
                                kernelChannelIdx = 0;
                                in_pos = batch * CHANNEL_IN * HEIGHT_IN * WIDTH_IN + in_ch * HEIGHT_IN * WIDTH_IN + in_row * WIDTH_IN + in_col;
                                kernel_pos = out_ch * KERNEL_CHANNEL * KERNEL_SIZE * KERNEL_SIZE + kernelChannelIdx * KERNEL_SIZE * KERNEL_SIZE + kernel_row * KERNEL_SIZE + kernel_col;
                                out[out_pos] += in[in_pos] * kernel[kernel_pos];
                                kernelChannelIdx++;
                                if ((in_ch + 1) % inGroupNums == 0)
                                    break;
                            }
                            if (isConvBias && biasFlag){
                                out[out_pos] += bias[out_ch];
                                biasFlag = 0;
                            }
                            if ((out_ch + 1) % outGroupNums == 0)
                                groupIndex++;
                        }
                    }
                }
            }
        }
    }

    return;
}
void SE(float* X_data, float* Y_data, int* X_num, float* X_mean, float* X_reduce, float* X_relu, float* X_expand, float* X_sigmoid, float* reduce_filter, float* reduce_bias, float* expand_filter, float* expand_bias) {

    float se_ratio = 1;
    Compute_mean(X_data, X_num, X_mean);
    int XC = X_num[1];
    int X_mean_num[4] = {X_num[0], X_num[1], 1, 1};
    int SEC = int(XC * se_ratio);
    int reduce_filter_num[7] = {XC, SEC, 1, 1, 0, 1, 1};
    int expand_filter_num[7] = {SEC, XC, 1, 1, 0, 1, 1};

    int X_reduce_num[4] = {1, SEC, 1, 1};
    int X_expand_num[4] = {1, XC, 1, 1};

    //reduce convolution
    Convolution(X_mean, X_mean_num, X_reduce, X_reduce_num, reduce_filter, reduce_filter_num, reduce_bias);
    ReLU(X_reduce, X_relu, X_reduce_num, 0);
    //expand convolution
    Convolution(X_relu, X_reduce_num, X_expand, X_expand_num, expand_filter, expand_filter_num, expand_bias);
    Sigmoid(X_expand, X_sigmoid, X_expand_num);
    Compute_mul(X_data, X_sigmoid, Y_data, X_num);
}

extern "C"
{
    void kernel_stage0(float* X_data, float* msp_filter, float* msp_bias, float* dw_filter, float* dw_bias,
                        float* reduce_filter, float* reduce_bias, float* expand_filter, float* expand_bias, float* proj_filter,
                        float* mean1, float* var1, float* gamma1, float* beta1,
                        float* mean2, float* var2, float* gamma2, float* beta2,
                        float* X_pad, float* X_conv, float* X_dwconv, float* X_dwnorm,
                        float* X_mean, float* X_reduce, float* X_relu, float* X_expand, float* X_sigmoid,
                        float* Y_msp, float* Y_dwact, float* Y_se, float* Y_proj)
    {
    #pragma HLS INTERFACE m_axi port = X_data bundle = gmem depth = 768
    #pragma HLS INTERFACE m_axi port = msp_filter bundle = gmem0 depth = 648
    #pragma HLS INTERFACE m_axi port = msp_bias bundle = gmem0 depth = 24
    #pragma HLS INTERFACE m_axi port = dw_filter bundle = gmem1 depth = 216
    #pragma HLS INTERFACE m_axi port = dw_bias bundle = gmem1 depth = 24
    #pragma HLS INTERFACE m_axi port = reduce_filter depth = 576
    #pragma HLS INTERFACE m_axi port = reduce_bias depth = 24
    #pragma HLS INTERFACE m_axi port = expand_filter depth = 576
    #pragma HLS INTERFACE m_axi port = expand_bias depth = 24
    #pragma HLS INTERFACE m_axi port = proj_filter depth = 576
    #pragma HLS INTERFACE m_axi port = mean1 bundle = gmem1 depth = 24
    #pragma HLS INTERFACE m_axi port = var1 bundle = gmem1 depth = 24
    #pragma HLS INTERFACE m_axi port = gamma1 bundle = gmem1 depth = 24
    #pragma HLS INTERFACE m_axi port = beta1 bundle = gmem1 depth = 24
    #pragma HLS INTERFACE m_axi port = mean2 bundle = gmem0 depth = 24
    #pragma HLS INTERFACE m_axi port = var2 bundle = gmem0 depth = 24
    #pragma HLS INTERFACE m_axi port = gamma2 bundle = gmem0 depth = 24
    #pragma HLS INTERFACE m_axi port = beta2 bundle = gmem0 depth = 24

#pragma HLS INTERFACE m_axi port = X_pad bundle = gmem2 depth = 972
#pragma HLS INTERFACE m_axi port = X_conv bundle = gmem2 depth = 1536
#pragma HLS INTERFACE m_axi port = X_dwconv bundle = gmem1 depth = 1536
#pragma HLS INTERFACE m_axi port = X_dwnorm bundle = gmem1 depth = 1536
#pragma HLS INTERFACE m_axi port = X_mean bundle = gmem1 depth = 24
#pragma HLS INTERFACE m_axi port = X_reduce bundle = gmem3 depth = 24
#pragma HLS INTERFACE m_axi port = X_relu bundle = gmem1 depth = 24
#pragma HLS INTERFACE m_axi port = X_expand bundle = gmem0 depth = 24
#pragma HLS INTERFACE m_axi port = X_sigmoid bundle = gmem1 depth = 24

#pragma HLS INTERFACE m_axi port = Y_msp bundle = gmem2 depth = 1536
#pragma HLS INTERFACE m_axi port = Y_dwact bundle = gmem2 depth = 1536
#pragma HLS INTERFACE m_axi port = Y_se bundle = gmem0 depth = 1536
#pragma HLS INTERFACE m_axi port = Y_proj bundle = gmem1 depth = 1536

    int X_num[4] = {1, 3, 16, 16};
    int msp_num[4] = {1, 24, 8, 8};
    int msp_filter_num[7] = {24, 3, 3, 3, 1, 2, 1};
    int dw_shape_num[7] = {1, 24, 8, 8, 24, 8, 8};
    int dw_conv_num[6] = {3, 0, 1, 1, 24, 1};
    int dw_norm_num[4] = {1, 24, 8, 8};
    int se_num[4] = {1, 24, 8, 8};
    int proj_num[4] = {1, 24, 8, 8};
    int proj_filter_num[7] = {24, 24, 1, 1, 0, 1, 0};

    Mspatch(X_data, X_num, X_pad, X_conv, msp_num, msp_filter, msp_filter_num, msp_bias, mean1, var1, gamma1, beta1, Y_msp);
    DW_conv(Y_msp, dw_filter, dw_bias, dw_shape_num, dw_conv_num, X_dwconv);
    BatchNorm(X_dwconv, Y_dwact, dw_norm_num, mean2, var2, gamma2, beta2);
    //ReLU(X_dwnorm, Y_dwact, dw_norm_num, 0);
    SE( Y_dwact, Y_se,  msp_num,  X_mean,  X_reduce,  X_relu,  X_expand,  X_sigmoid,  reduce_filter,  reduce_bias,  expand_filter,  expand_bias);
    //Projection. equal to convolution actually
    Convolution(Y_se, se_num, Y_proj, proj_num, proj_filter, proj_filter_num, expand_bias);
    }
}