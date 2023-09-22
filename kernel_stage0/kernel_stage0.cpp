// Includes
#include <hls_math.h>
#include <hls_stream.h>
#include <stdint.h>
#include "kernel_stage0.hpp"


extern "C"
{
    void kernel_stage0(float* X_data, float* msp_filter, float* msp_bias, float* reduce_filter, float* reduce_bias,
                        float* expand_filter, float* expand_bias, float* mean, float* var, float* gamma, float* beta,
                        float* X_pad, float* X_conv,  float* X_mean, float* X_reduce, float* X_relu, 
                        float* X_expand, float* X_sigmoid, float* Y_msp, float* Y_se)
    {
    #pragma HLS INTERFACE m_axi port = X_data bundle = gmem0 depth = 37632
    #pragma HLS INTERFACE m_axi port = msp_filter depth = 648
    #pragma HLS INTERFACE m_axi port = msp_bias depth = 24
    #pragma HLS INTERFACE m_axi port = reduce_filter depth = 576
    #pragma HLS INTERFACE m_axi port = reduce_bias depth = 24
    #pragma HLS INTERFACE m_axi port = expand_filter depth = 576
    #pragma HLS INTERFACE m_axi port = expand_bias depth = 24
    #pragma HLS INTERFACE m_axi port = mean depth = 24
    #pragma HLS INTERFACE m_axi port = var depth = 24
    #pragma HLS INTERFACE m_axi port = gamma depth = 24
    #pragma HLS INTERFACE m_axi port = beta depth = 24

#pragma HLS INTERFACE m_axi port = X_pad bundle = gmem1 depth = 38988
#pragma HLS INTERFACE m_axi port = X_conv bundle = gmem0 depth = 75264
#pragma HLS INTERFACE m_axi port = X_mean bundle = gmem1 depth = 24
#pragma HLS INTERFACE m_axi port = X_reduce bundle = gmem0 depth = 24
#pragma HLS INTERFACE m_axi port = X_relu bundle = gmem1 depth = 24
#pragma HLS INTERFACE m_axi port = X_expand bundle = gmem0 depth = 24
#pragma HLS INTERFACE m_axi port = X_sigmoid bundle = gmem1 depth = 24

#pragma HLS INTERFACE m_axi port = Y_msp bundle = gmem2 depth = 75264
#pragma HLS INTERFACE m_axi port = Y_se bundle = gmem0 depth = 75264



    int X_num[4] = {1, 3, 112, 112};
    int msp_num[4] = {1, 24, 56, 56};
    int msp_filter_num[7] = {24, 3, 3, 3, 1, 2, 0};

    Mspatch(float* X_data, int* X_num, float* X_pad, float* X_conv, float* Y_msp, int* msp_num, float* msp_filter, int* msp_filter_num, float* msp_bias, float* mean, float* var, float* gamma, float* beta);
        //DW_conv();
    SE(float* Y_msp, float* Y_se, int* msp_num, float* X_mean, float* X_reduce, float* X_relu, float* X_expand, float* X_sigmoid, float* reduce_filter, float* reduce_bias, float* expand_filter, float* expand_bias);
        //Projection();
    }
}