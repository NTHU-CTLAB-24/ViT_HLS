#include <hls_math.h>
#include <hls_stream.h>
#include <stdint.h>
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

extern "C" {
   void SE(float* X_data, float* Y_data, int* X_num, float* X_mean, float* X_reduce, float* X_relu, float* X_expand, float* X_sigmoid, float* reduce_filter, float* reduce_bias, float* expand_filter, float* expand_bias) {
    #pragma HLS INTERFACE m_axi port = X_data bundle = gmem depth = 1536
    #pragma HLS INTERFACE m_axi port = Y_data bundle = gmem depth = 1536
    #pragma HLS INTERFACE m_axi port = X_num bundle = gmem0 depth = 4
    #pragma HLS INTERFACE m_axi port = X_mean bundle = gmem1 depth = 24
    #pragma HLS INTERFACE m_axi port = X_reduce bundle = gmem2 depth = 24
    #pragma HLS INTERFACE m_axi port = X_relu bundle = gmem1 depth = 24
    #pragma HLS INTERFACE m_axi port = X_expand bundle = gmem depth = 24
    #pragma HLS INTERFACE m_axi port = X_sigmoid bundle = gmem2 depth = 24
    #pragma HLS INTERFACE m_axi port = reduce_filter depth = 576
    #pragma HLS INTERFACE m_axi port = reduce_bias depth = 24
    #pragma HLS INTERFACE m_axi port = expand_filter depth = 576
    #pragma HLS INTERFACE m_axi port = expand_bias depth = 24


    float se_ratio = 1;
    Compute_mean(X_data, X_num, X_mean);
    int X_mean_num[4] = {X_num[0], X_num[1], 1, 1};
    int XC = X_num[1];
    int SEC = int(XC * se_ratio);
    int reduce_filter_num[7] = {XC, SEC, 1, 1, 0, 1, 1};
    int expand_filter_num[7] = {SEC, XC, 1, 1, 0, 1, 1};

    int X_reduce_num[4];
    X_reduce_num[0] = X_num[0];
    X_reduce_num[1] = reduce_filter_num[0];
    X_reduce_num[2] = (X_mean_num[2] - reduce_filter_num[2]) + 1;
    X_reduce_num[3] = (X_mean_num[3] - reduce_filter_num[3]) + 1;

    int X_expand_num[4];
    X_expand_num[0] = X_num[0];
    X_expand_num[1] = expand_filter_num[0];
    X_expand_num[2] = (X_reduce_num[2] - expand_filter_num[2]) + 1;
    X_expand_num[3] = (X_reduce_num[3] - expand_filter_num[3]) + 1;

    //reduce convolution
    Convolution(X_mean, X_mean_num, X_reduce, X_reduce_num, reduce_filter, reduce_filter_num, reduce_bias);
    //ReLU(X_reduce, X_relu, X_reduce_num, 0);
    //expand convolution
    //Convolution(X_relu, X_reduce_num, X_expand, X_expand_num, expand_filter, expand_filter_num, expand_bias);
    //Sigmoid(X_expand, X_sigmoid, X_expand_num);
    //Compute_mul(X_data, X_sigmoid, Y_data, X_num);
}
}
