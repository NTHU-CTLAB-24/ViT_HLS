#include "kernel_stage0.hpp"
using namespace std;

void dataPrepare(float* Array, int batch, int channel, int height, int width){
     for (int b = 0; b < batch; b++){
        for (int c = 0; c < channel; c++){
            for (int h = 0; h < height; h++){
                for (int w = 0; w < width; w++){
                    Array[b*channel*height*width + c*height*width + h*width + w] = h + c;
                }
            }
        }
    }
}
void mspbiasPrepare(float* Array, int channel) {
    for (int c = 0; c < channel; c++) {
        Array[c] = c + 0.01;
    }
}
void mspfilterPrepare(float* Array, int channel_out, int channel_in, int kernel_size) {
    for (int i = 0; i < channel_out; i++) {
        for (int j = 0; j < channel_in; j++) {
            for (int kh = 0; kh < kernel_size; kh++) {
                for (int kw = 0; kw < kernel_size; kw++) {
                    Array[i*channel_in*kernel_size*kernel_size + j*kernel_size*kernel_size + kh*kernel_size + kw] = 0.1;
                }
            }
        }
    }
}
void meanPrepare(float* Array, int channel) {
    for (int i = 0; i < channel; i++){
        Array[i] = 8;
    }
}
void varPrepare(float* Array, int channel) {
       for (int i = 0; i < channel; i++){
        Array[i] = 21.5;
    }
}
void gammaPrepare(float* Array, int channel) {
    for (int i = 0; i < channel; i++){
        Array[i] = 0.5;
    }
}
void betaPrepare(float* Array, int channel) {
    for (int i = 0; i < channel; i++){
        Array[i] = 0.2;
    }
}

void dwfilterPrepare(float* Array, int channel_out, int channel_in, int kernel_size) {
    for (int i = 0; i < channel_out; i++) {
        for (int j = 0; j < channel_in; j++) {
            for (int kh = 0; kh < kernel_size; kh++) {
                for (int kw = 0; kw < kernel_size; kw++) {
                    Array[i*channel_in*kernel_size*kernel_size + j*kernel_size*kernel_size + kh*kernel_size + kw] = 0.002;
                }
            }
        }
    }
}
void dwbiasPrepare(float* Array, int channel) {
    for (int c = 0; c < channel; c++) {
        Array[c] = c + 0.01;
    }
}
void reducefilterPrepare(float* Array, int channel_out, int channel_in) {
    for (int i = 0; i < channel_out; i++) {
        for (int j = 0; j < channel_in; j++) {
            for (int h = 0; h < 1; h++) {
                for (int w = 0; w < 1; w++) {
                    Array[i*channel_in + j + h + w] = 0.1;
                }
            }
        }
    }
}
void reducebiasPrepare(float* Array, int channel) {
    for (int i = 0; i < channel; i++) {
        Array[i] = i + 0.01;
    }
}
void expandfilterPrepare(float* Array, int channel_out, int channel_in) {
     for (int i = 0; i < channel_out; i++) {
        for (int j = 0; j < channel_in; j++) {
            Array[i*channel_in + j] = 0.005;
        }
    }
}
void expandbiasPrepare(float* Array, int channel) {
    for (int i = 0; i < channel; i++) {
        Array[i] = i + 0.01;
    }
}

int main() {
    float X_data[768];
    float msp_filter[648];
    float msp_bias[24];
    float dw_filter[216];
    float dw_bias[24];
    float reduce_filter[576];
    float reduce_bias[24];
    float expand_filter[576];
    float expand_bias[24];

    float mean1[24];
    float var1[24];
    float gamma1[24];
    float beta1[24];

    float mean2[24];
    float var2[24];
    float gamma2[24];
    float beta2[24];
    
    float X_pad[972];
    float X_conv[1536];
    float X_dwconv[1536];
    float X_dwnorm[1536];
    float X_mean[24];
    float X_reduce[24];
    float X_relu[24];
    float X_expand[24];
    float X_sigmoid[24];
    float Y_msp[1536];
    float Y_dw[1536];
    float Y_se[1536];

    int X_num[4] = {1, 3, 16, 16};
    int msp_num[4] = {1, 24, 8, 8};
    int msp_filter_num[7] = {24, 3, 3, 3, 1, 2, 0};

    dataPrepare(X_data, 1, 3, 16, 16);
    mspfilterPrepare(msp_filter, 24, 3, 3);
    mspbiasPrepare(msp_bias, 24);
    meanPrepare(mean1, 24);
    varPrepare(var1, 24);
    gammaPrepare(gamma1, 24);
    betaPrepare(beta1, 24);
    meanPrepare(mean2, 24);
    varPrepare(var2, 24);
    gammaPrepare(gamma2, 24);
    betaPrepare(beta2, 24);
    dwfilterPrepare(dw_filter, 24, 1, 3);
    dwbiasPrepare(dw_bias, 24);
    reducefilterPrepare(reduce_filter, 24, 24);
    reducebiasPrepare(reduce_bias, 24);
    expandfilterPrepare(expand_filter, 24, 24);
    expandbiasPrepare(expand_bias, 24);

    kernel_stage0(X_data, msp_filter, msp_bias, dw_filter, dw_bias, reduce_filter, reduce_bias, 
                    expand_filter, expand_bias, mean1, var1, gamma1, beta1,
                    mean2, var2, gamma2, beta2, X_pad, X_conv, X_dwconv, X_dwnorm,
                    X_mean, X_reduce, X_relu, X_expand, X_sigmoid, Y_msp, Y_dw, Y_se);

    cout << "SE - mean" << endl;
    for (int b = 0; b < 1; b++) {
        for (int c = 0; c < 24; c++) {
            cout << X_mean[b*24 + c] << " ";
        }
        cout << endl;
    }

    cout << "SE reduce conv" << endl;
    for (int b = 0; b < 1; b++) {
        for (int c = 0;  c < 24; c++) {
            cout << X_reduce[b*24 + c] << " ";
        }
        cout << endl;
    }
 
    cout << " after Mspatch, Dw conv, and SE" << endl;
    int out_size = 8;
    for (int b = 0; b < 1; b++) {
        for (int c = 0; c < 1; c++) {
            for (int h = 0; h < out_size; h++) {
                for (int w = 0; w < out_size; w++) {
                    cout << Y_se[b*24*out_size*out_size + c*out_size*out_size + h*out_size + w] << " ";
                }
                cout << endl;
            }
        }
    }
  
  return EXIT_SUCCESS;
}
