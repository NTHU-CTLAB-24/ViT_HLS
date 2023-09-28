// Includes
#include <iostream>
#include <ap_int.h>
#include <hls_stream.h>

const int size = 4096;

extern "C" {
     void kernel_stage0(float* X_data, float* msp_filter, float* msp_bias, float* dw_filter, float* dw_bias,
                        float* reduce_filter, float* reduce_bias, float* expand_filter, float* expand_bias, float* proj_filter,
                        float* mean1, float* var1, float* gamma1, float* beta1,
                        float* mean2, float* var2, float* gamma2, float* beta2,
                        float* X_pad, float* X_conv, float* X_dwconv, float* X_dwnorm,
                        float* X_mean, float* X_reduce, float* X_relu, float* X_expand, float* X_sigmoid,
                        float* Y_msp, float* Y_dwact, float* Y_se, float* Y_proj);
}

