#ifndef _KRNL_ATTENTION_H_
#define _KRNL_ATTENTION_H_

// Includes
#include <ap_int.h>
#include <hls_stream.h>
#include <hls_math.h>
#include <iostream>

extern "C"
{
    void kernel_attention(float *buffer_DataIn_1,
                              float *afterNorm,
                              float *norm1_mean, float *norm1_var, float *norm1_weight, float *norm1_bias, float *norm1_ln_in,
                              float *afterPad,
                              float *afterRearrangeX,
                              float *afterPad1,
                              float *afterConv1,
                              float *kernel1,
                              float *bias1,
                              float *in_qk,
                              float *in_q,
                              float *in_k,
                              float *afterQKMultiplication,
                              float *afterSoftmax,
                              float *afterRearrangeX2,
                              float *afterQKXMultiplication,
                              float *afterRearrangeQKX,
                              float *afterPad2,
                              float *afterConv2,
                              float *kernel2,
                              float *bias2,
                              float *afterAct2,
                              float *QKV,
                              float *buffer_out,
                              float *in1_stream,
                              float *sumQK,
                              float *sumQKX,
                              float *buffer_result
                       );
}

#endif