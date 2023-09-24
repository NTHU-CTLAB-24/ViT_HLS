// Includes
#include <hls_math.h>
#include <hls_stream.h>
#include <stdint.h>
#include "kernel.hpp"
// TRIPCOUNT identifier
const int BATCH_SIZE = 1;
const int IMAGE_H = 56;
const int IMAGE_W = 56;
const float RATIO = 1;
const int HEIGHT_IN = 1;
const int WIDTH_IN = 1;
const int CHANNEL_IN = 24;
const int CHANNEL_OUT = int(CHANNEL_IN * RATIO); // REDUCE_CHS
const int KERNEL_SIZE = 1;
const int PADDING = 0;
const int STRIDE = 1;
const bool isConvBias = true;
const int HEIGHT_OUT = (HEIGHT_IN - KERNEL_SIZE + 2 * PADDING) / STRIDE + 1;
const int WIDTH_OUT = (WIDTH_IN - KERNEL_SIZE + 2 * PADDING) / STRIDE + 1;

static void load_input_mean(ftype *data,
                            ftype in[BATCH_SIZE][CHANNEL_IN][IMAGE_H][IMAGE_W], ftype mean[BATCH_SIZE][CHANNEL_IN])
{

    float total = IMAGE_H * IMAGE_W;
    float sum[BATCH_SIZE * CHANNEL_IN];
#pragma HLS bind_storage variable=sum type=RAM_1P impl=uram

init_sum:
    for (int b = 0; b < BATCH_SIZE; b++){
#pragma HLS LOOP_TRIPCOUNT min = BATCH_SIZE  max = BATCH_SIZE
        for (int c = 0; c < CHANNEL_IN; c++){
#pragma HLS LOOP_TRIPCOUNT min = CHANNEL_IN  max = CHANNEL_IN
            sum[b * CHANNEL_IN + c] = 0;
        }
    }

load_data:
    for (int h = 0; h < IMAGE_H; h++)
    {
#pragma HLS LOOP_TRIPCOUNT min = IMAGE_H max = IMAGE_H
        for (int w = 0; w < IMAGE_W; w++)
        {
#pragma HLS LOOP_TRIPCOUNT min = IMAGE_W max = IMAGE_W
                for (int c=0; c<CHANNEL_IN; c++) {
#pragma HLS LOOP_TRIPCOUNT min = CHANNEL_IN  max = CHANNEL_IN
                    for (int n = 0; n < BATCH_SIZE; n++) {
#pragma HLS LOOP_TRIPCOUNT min = BATCH_SIZE  max = BATCH_SIZE               
                         in[n][c][h][w] = data[n * CHANNEL_IN * IMAGE_H * IMAGE_W + c * IMAGE_H * IMAGE_W + h * IMAGE_W + w];
                    }
                }
            }
        }

compute_mean:

    for (int i = 0; i < IMAGE_H; i++)
    {
#pragma HLS LOOP_TRIPCOUNT min = IMAGE_H max = IMAGE_H
        for (int j = 0; j < IMAGE_W; j++){
#pragma HLS LOOP_TRIPCOUNT min = IMAGE_W max = IMAGE_W
            for (int c = 0; c < CHANNEL_IN; c++) {
#pragma HLS LOOP_TRIPCOUNT min = CHANNEL_IN  max = CHANNEL_IN
                for (int b = 0; b < BATCH_SIZE; b++) {
#pragma HLS LOOP_TRIPCOUNT min = BATCH_SIZE  max = BATCH_SIZE
                    sum[b * CHANNEL_IN + c] += (float)in[b][c][i][j];
                }
            }
        }
    }

    for (int b = 0; b < BATCH_SIZE; b++){
#pragma HLS LOOP_TRIPCOUNT min = BATCH_SIZE max = BATCH_SIZE
        for (int c = 0; c < CHANNEL_IN; c++){
#pragma HLS LOOP_TRIPCOUNT min = CHANNEL_IN  max = CHANNEL_IN
            mean[b][c] = (ftype)(sum[b * BATCH_SIZE + c] / total);
        }
    }
}

static void compute_conv_reduce(ftype in[BATCH_SIZE][CHANNEL_IN],
                                ftype out[BATCH_SIZE][CHANNEL_OUT])
{
    // The kernel is operating with vector of NUM_WORDS integers. The + operator performs
    // an element-wise add, resulting in NUM_WORDS parallel additions.
    ftype kernel[CHANNEL_OUT][CHANNEL_IN];
#pragma HLS bind_storage variable=kernel type=RAM_1P impl=uram
    ftype bias[CHANNEL_OUT];
#pragma HLS bind_storage variable=bias type=RAM_1P impl=uram

init_out:
    for (int c = 0; c < CHANNEL_OUT; c++){
#pragma HLS LOOP_TRIPCOUNT min = CHANNEL_OUT  max = CHANNEL_OUT
        for (int b = 0; b < BATCH_SIZE; b++) {
#pragma HLS LOOP_TRIPCOUNT min = BATCH_SIZE max = BATCH_SIZE
             out[b][c] = 0;
        }
    }
init_bias:
    for (int k = 0; k < CHANNEL_OUT; k++) {
#pragma HLS LOOP_TRIPCOUNT min = CHANNEL_OUT  max = CHANNEL_OUT 
        bias[k] = (ftype)(k + 0.01);
    }

init_kernel:
    for (int k = 0; k < CHANNEL_OUT; k++)
    {
#pragma HLS LOOP_TRIPCOUNT min = CHANNEL_OUT max = CHANNEL_OUT
        for (int l = 0; l < CHANNEL_IN; l++){
#pragma HLS LOOP_TRIPCOUNT min = CHANNEL_IN  max = CHANNEL_IN
            kernel[k][l] = (ftype)0.1;
        }
    }

execute:
Batch:
    for (int batch = 0; batch < BATCH_SIZE; batch++)
    {
#pragma HLS LOOP_TRIPCOUNT min = BATCH_SIZE max = BATCH_SIZE
    Output_Channel:
        for (int out_ch = 0; out_ch < CHANNEL_OUT; out_ch++)
        {
#pragma HLS LOOP_TRIPCOUNT min = CHANNEL_OUT max = CHANNEL_OUT
                In_Channel:
                    for (int in_ch = 0; in_ch < CHANNEL_IN; in_ch++){
#pragma HLS LOOP_TRIPCOUNT min = CHANNEL_IN  max = CHANNEL_IN
                        out[batch][out_ch] += in[batch][in_ch] * kernel[out_ch][in_ch];
                    }
                    if (isConvBias)
                        out[batch][out_ch] += bias[out_ch];
            }
    }
}
static void compute_relu(ftype in[BATCH_SIZE][CHANNEL_OUT], ftype out[BATCH_SIZE][CHANNEL_OUT]) {
     for (int n = 0; n < BATCH_SIZE; n++) {
#pragma HLS LOOP_TRIPCOUNT min = BATCH_SIZE max = BATCH_SIZE
        for (int c = 0; c < CHANNEL_OUT; c++){
#pragma HLS LOOP_TRIPCOUNT min = CHANNEL_OUT  max = CHANNEL_OUT
            if (in[n][c] < 0) out[n][c] = 0;
            else out[n][c] = in[c][c];
        }
    }
}
static void compute_conv_expand(ftype in[BATCH_SIZE][CHANNEL_OUT], float out[BATCH_SIZE][CHANNEL_IN])
{
    // The kernel is operating with vector of NUM_WORDS integers. The + operator performs
    // an element-wise add, resulting in NUM_WORDS parallel additions.

    float kernel[CHANNEL_IN][CHANNEL_OUT];
#pragma HLS bind_storage variable=kernel type=RAM_1P impl=uram
    float bias[CHANNEL_IN];
#pragma HLS bind_storage variable=bias type=RAM_1P impl=uram

init_out:
    for (int c = 0; c < CHANNEL_IN; c++){
#pragma HLS LOOP_TRIPCOUNT min = CHANNEL_IN  max = CHANNEL_IN
        for (int b = 0; b < BATCH_SIZE; b++) {
#pragma HLS LOOP_TRIPCOUNT min = BATCH_SIZE max = BATCH_SIZE
             out[b][c] = 0;
        }
    }
init_bias:
    for (int k = 0; k < CHANNEL_OUT; k++) {
#pragma HLS LOOP_TRIPCOUNT min = CHANNEL_OUT max = CHANNEL_OUT
        bias[k] = (k + 0.01);
    }

init_kernel:
    for (int k = 0; k < CHANNEL_OUT; k++)
    {
#pragma HLS LOOP_TRIPCOUNT min = CHANNEL_OUT max = CHANNEL_OUT
        for (int l = 0; l < CHANNEL_IN; l++){
#pragma HLS LOOP_TRIPCOUNT min = CHANNEL_IN max = CHANNEL_IN
            kernel[k][l] = 0.005;
        }
    }

execute:
Batch:
    for (int batch = 0; batch < BATCH_SIZE; batch++)
    {
#pragma HLS LOOP_TRIPCOUNT min = BATCH_SIZE max = BATCH_SIZE
    Output_Channel:
        for (int out_ch = 0; out_ch < CHANNEL_IN; out_ch++)
        {
#pragma HLS LOOP_TRIPCOUNT min = CHANNEL_IN max = CHANNEL_IN
        In_Channel:
            for (int in_ch = 0; in_ch < CHANNEL_OUT; in_ch++)
            {
#pragma HLS LOOP_TRIPCOUNT min = CHANNEL_OUT max = CHANNEL_OUT
                out[batch][out_ch] += (float)in[batch][in_ch] * kernel[out_ch][in_ch];
            }
            if (isConvBias)
                out[batch][out_ch] += bias[out_ch];
        }
    }
}

static void compute_sigmoid(float input[BATCH_SIZE][CHANNEL_IN], ftype *sigmoid)
{
    for (int b = 0; b < BATCH_SIZE; b++)
    {
#pragma HLS LOOP_TRIPCOUNT min = BATCH_SIZE max = BATCH_SIZE
        for (int c = 0; c < CHANNEL_IN; c++){
#pragma HLS LOOP_TRIPCOUNT min = CHANNEL_IN max = CHANNEL_IN
            float tmp = input[b][c];
            sigmoid[b * CHANNEL_IN + c] = (ftype)(1 / (1 + exp(-tmp)));
        }
    }
}

static void compute_mul(ftype in1[BATCH_SIZE][CHANNEL_IN][IMAGE_H][IMAGE_W], ftype *in2,
                        ftype *result)
{

    for (int i = 0; i < IMAGE_H; i++)
    {
#pragma HLS LOOP_TRIPCOUNT min = IMAGE_H max = IMAGE_H
        for (int j = 0; j < IMAGE_W; j++)
        {
#pragma HLS LOOP_TRIPCOUNT min = IMAGE_W max = IMAGE_W
            for (int b = 0; b < BATCH_SIZE; b++)
            {
#pragma HLS LOOP_TRIPCOUNT min = BATCH_SIZE max = BATCH_SIZE
                for (int c = 0; c < CHANNEL_IN; c++) {
#pragma HLS LOOP_TRIPCOUNT min = CHANNEL_IN max = CHANNEL_IN
                    ftype val = in2[b*BATCH_SIZE + c];
                    result[b*CHANNEL_IN*IMAGE_H*IMAGE_W + c*IMAGE_H*IMAGE_W + i*IMAGE_W + j] = in1[b][c][i][j] * val;
                }
            }
        }
    }
}

extern "C"
{
    void kernel_se(ftype *image, ftype *buffer_result)
    {
#pragma HLS INTERFACE m_axi port = image bundle = gmem0 depth = 75264
#pragma HLS INTERFACE m_axi port = buffer_result bundle = gmem1 depth = 75264

        ftype in[BATCH_SIZE][CHANNEL_IN][IMAGE_H][IMAGE_W];
#pragma HLS bind_storage variable=in type=RAM_1P impl=uram
        ftype mean[BATCH_SIZE][CHANNEL_IN];
#pragma HLS bind_storage variable=mean type=RAM_1P impl=uram
        ftype reduce_conv[BATCH_SIZE][CHANNEL_OUT];
#pragma HLS bind_storage variable=reduce_conv type=RAM_1P impl=uram
        ftype silu[BATCH_SIZE][CHANNEL_OUT];
#pragma HLS bind_storage variable=silu type=RAM_1P impl=uram
        float expand_conv[BATCH_SIZE][CHANNEL_IN];
#pragma HLS bind_storage variable=expand_conv type=RAM_1P impl=uram
        ftype sigmoid[BATCH_SIZE * CHANNEL_IN];
#pragma HLS bind_storage variable=sigmoid type=RAM_1P impl=uram

#pragma HLS dataflow
        load_input_mean(image, in, mean);
        compute_conv_reduce(mean, reduce_conv);
        compute_relu(reduce_conv, silu);
        compute_conv_expand(silu, expand_conv);
        compute_sigmoid(expand_conv, sigmoid);
        compute_mul(in, sigmoid, buffer_result);
    }
}
