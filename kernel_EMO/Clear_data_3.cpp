#include "kernel_EMO.hpp"
#include <stdint.h>
using namespace std;

void clear_data_3(
    float *afterNorm, float *afterRearrangeX, float *afterConv1,
    float *in_q, float *in_k,
    float *afterQKMultiplication, float *afterSoftmax, float *afterRearrangeX2, float *afterQKXMultiplication,
    float *afterRearrangeQKX, float *afterConv2, float *afterAct2,
    float *buffer_out, float *buffer_result,
    float *Y_dw_conv_1, float *Y_dw_norm_1, float *Y_dw_act_1, float *Y_proj_1, float *Y_dw_skip_1)
{
    for (int i = 0; i < 15680; i++)
    {
    #pragma HLS LOOP_TRIPCOUNT min = 15680 max = 15680
        afterNorm[i] = 0;
        afterRearrangeX[i] = 0;
    }
    for (int i = 0; i < 31360; i++)
    {
    #pragma HLS LOOP_TRIPCOUNT min = 31360 max = 31360
        afterConv1[i] = 0;
    }
    for (int i = 0; i < 15680; i++)
    {
    #pragma HLS LOOP_TRIPCOUNT min = 15680 max = 15680
        in_q[i] = 0;
        in_k[i] = 0;
    }
    for (int i = 0; i < 38416; i++)
    {
    #pragma HLS LOOP_TRIPCOUNT min = 38416 max = 38416
        afterQKMultiplication[i] = 0;
        afterSoftmax[i] = 0;
    }
    for (int i = 0; i < 15680; i++)
    {
    #pragma HLS LOOP_TRIPCOUNT min = 15680 max = 15680
        afterRearrangeX2[i] = 0;
        afterQKXMultiplication[i] = 0;
        afterRearrangeQKX[i] = 0;
    }
    for (int i = 0; i < 47040; i++)
    {
    #pragma HLS LOOP_TRIPCOUNT min = 47040 max = 47040
        afterConv2[i] = 0;
        afterAct2[i] = 0;
        buffer_out[i] = 0;
        buffer_result[i] = 0;
        Y_dw_conv_1[i] = 0;
        Y_dw_norm_1[i] = 0;
        Y_dw_act_1[i] = 0;
        Y_dw_skip_1[i] = 0;
    }
    for (int i = 0; i < 15680; i++)
    {
    #pragma HLS LOOP_TRIPCOUNT min = 15680 max = 15680
        Y_proj_1[i] = 0;
    }
}