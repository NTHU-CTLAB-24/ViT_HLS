// Includes
#include <hls_math.h>
#include <hls_stream.h>
#include <stdint.h>
// TRIPCOUNT identifier
const int BATCH_SIZE = 2;
const int IMAGE_H = 4;
const int IMAGE_W = 4;
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

static void load_input_mean(float *data,
                            float in[BATCH_SIZE][CHANNEL_IN][IMAGE_H][IMAGE_W], float mean[BATCH_SIZE][CHANNEL_IN])
{

    float total = IMAGE_H * IMAGE_W;
    float sum[BATCH_SIZE * CHANNEL_IN];

init_sum:
    for (int b = 0; b < BATCH_SIZE; b++)
    {
#pragma HLS UNROLL
        for (int c = 0; c < CHANNEL_IN; c++)
        {
#pragma HLS UNROLL
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
            for (int c = 0; c < CHANNEL_IN; c++)
            {
#pragma HLS UNROLL
                for (int n = 0; n < BATCH_SIZE; n++)
                {
#pragma HLS UNROLL
                    in[n][c][h][w] = data[n * CHANNEL_IN * IMAGE_H * IMAGE_W + c * IMAGE_H * IMAGE_W + h * IMAGE_W + w];
                }
            }
        }
    }

compute_mean:

    for (int i = 0; i < IMAGE_H; i++)
    {
#pragma HLS LOOP_TRIPCOUNT min = IMAGE_H max = IMAGE_H
        for (int j = 0; j < IMAGE_W; j++)
        {
#pragma HLS UNROLL
            for (int c = 0; c < CHANNEL_IN; c++)
            {
#pragma HLS UNROLL
                for (int b = 0; b < BATCH_SIZE; b++)
                {
#pragma HLS UNROLL
                    sum[b * CHANNEL_IN + c] += in[b][c][i][j];
                }
            }
        }
    }

    for (int b = 0; b < BATCH_SIZE; b++)
    {
#pragma HLS UNROLL
        for (int c = 0; c < CHANNEL_IN; c++)
        {
#pragma HLS UNROLL
            mean[b][c] = sum[b * BATCH_SIZE + c] / total;
        }
    }
}

static void compute_conv_reduce(float in[BATCH_SIZE][CHANNEL_IN],
                                float out[BATCH_SIZE][CHANNEL_OUT])
{
    // The kernel is operating with vector of NUM_WORDS integers. The + operator performs
    // an element-wise add, resulting in NUM_WORDS parallel additions.
    float kernel[CHANNEL_OUT][CHANNEL_IN];
#pragma HLS array_partition variable = kernel complete dim = 1
    float bias[CHANNEL_OUT];
#pragma HLS array_partition variable = bias complete dim = 1

init_out:
    for (int c = 0; c < CHANNEL_OUT; c++)
    {
#pragma HLS UNROLL
        for (int b = 0; b < BATCH_SIZE; b++)
        {
#pragma HLS UNROLL
            out[b][c] = 0;
        }
    }
init_bias:
    for (int k = 0; k < CHANNEL_OUT; k++)
    {
#pragma HLS UNROLL
        bias[k] = k + 0.01;
    }

init_kernel:
    for (int k = 0; k < CHANNEL_OUT; k++)
    {
#pragma HLS LOOP_TRIPCOUNT min = CHANNEL_OUT max = CHANNEL_OUT
        for (int l = 0; l < CHANNEL_IN; l++)
        {
#pragma HLS UNROLL
            kernel[k][l] = 0.1;
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
            for (int in_ch = 0; in_ch < CHANNEL_IN; in_ch++)
            {
#pragma HLS UNROLL
                out[batch][out_ch] += in[batch][in_ch] * kernel[out_ch][in_ch];
            }
            if (isConvBias)
                out[batch][out_ch] += bias[out_ch];
        }
    }
}
static void compute_silu(float in[BATCH_SIZE][CHANNEL_OUT], float out[BATCH_SIZE][CHANNEL_OUT])
{
    for (int n = 0; n < BATCH_SIZE; n++)
    {
#pragma HLS LOOP_TRIPCOUNT min = BATCH_SIZE max = BATCH_SIZE
        for (int c = 0; c < CHANNEL_OUT; c++)
        {
#pragma HLS UNROLL
            // modify silu to relu
            // out[n][c] = in[n][c] * (1 / (1 + exp(-in[n][c])));
            if (in[n][c] > 0)
                out[n][c] = in[n][c];
            else
                out[n][c] = 0;
        }
    }
}
static void compute_conv_expand(float in[BATCH_SIZE][CHANNEL_OUT], float out[BATCH_SIZE][CHANNEL_IN])
{
    // The kernel is operating with vector of NUM_WORDS integers. The + operator performs
    // an element-wise add, resulting in NUM_WORDS parallel additions.

    float kernel[CHANNEL_IN][CHANNEL_OUT];
#pragma HLS array_partition variable = kernel complete dim = 1
    float bias[CHANNEL_IN];
#pragma HLS array_partition variable = bias complete dim = 1

init_out:
    for (int c = 0; c < CHANNEL_IN; c++)
    {
#pragma HLS UNROLL
        for (int b = 0; b < BATCH_SIZE; b++)
        {
#pragma HLS UNROLL
            out[b][c] = 0;
        }
    }
init_bias:
    for (int k = 0; k < CHANNEL_OUT; k++)
    {
#pragma HLS UNROLL
        bias[k] = k + 0.01;
    }

init_kernel:
    for (int k = 0; k < CHANNEL_OUT; k++)
    {
#pragma HLS LOOP_TRIPCOUNT min = CHANNEL_OUT max = CHANNEL_OUT
        for (int l = 0; l < CHANNEL_IN; l++)
        {
#pragma HLS UNROLL
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
                out[batch][out_ch] += in[batch][in_ch] * kernel[out_ch][in_ch];
            }
            if (isConvBias)
                out[batch][out_ch] += bias[out_ch];
        }
    }
}

static void compute_sigmoid(float input[BATCH_SIZE][CHANNEL_IN], float *sigmoid)
{
    for (int b = 0; b < BATCH_SIZE; b++)
    {
#pragma HLS LOOP_TRIPCOUNT min = BATCH_SIZE max = BATCH_SIZE
        for (int c = 0; c < CHANNEL_IN; c++)
        {
#pragma HLS UNROLL
            float tmp = input[b][c];
            sigmoid[b * CHANNEL_IN + c] = 1 / (1 + exp(-tmp));
        }
    }
}

static void compute_mul(float in1[BATCH_SIZE][CHANNEL_IN][IMAGE_H][IMAGE_W], float *in2,
                        float *result)
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
                for (int c = 0; c < CHANNEL_IN; c++)
                {
#pragma HLS UNROLL
                    float val = in2[b * BATCH_SIZE + c];
                    result[b * CHANNEL_IN * IMAGE_H * IMAGE_W + c * IMAGE_H * IMAGE_W + i * IMAGE_W + j] = in1[b][c][i][j] * val;
                }
            }
        }
    }
}

extern "C"
{
    void kernel_se(float *image, float *buffer_result)
    {
#pragma HLS INTERFACE m_axi port = image bundle = gmem0 depth = 768
#pragma HLS INTERFACE m_axi port = buffer_result bundle = gmem1 depth = 768

        float in[BATCH_SIZE][CHANNEL_IN][IMAGE_H][IMAGE_W];
#pragma HLS array_partition variable = in complete dim = 1
        float mean[BATCH_SIZE][CHANNEL_IN];
#pragma HLS array_partition variable = mean complete dim = 1
        float reduce_conv[BATCH_SIZE][CHANNEL_OUT];
#pragma HLS array_partition variable = reduce_conv complete dim = 1
        float silu[BATCH_SIZE][CHANNEL_OUT];
#pragma HLS array_partition variable = silu complete dim = 1
        float expand_conv[BATCH_SIZE][CHANNEL_IN];
#pragma HLS array_partition variable = expand_conv complete dim = 1
        float sigmoid[BATCH_SIZE * CHANNEL_IN];
#pragma HLS array_partition variable = sigmoid complete dim = 1

        load_input_mean(image, in, mean);
        compute_conv_reduce(mean, reduce_conv);
        compute_silu(reduce_conv, silu);
        compute_conv_expand(silu, expand_conv);
        compute_sigmoid(expand_conv, sigmoid);
        compute_mul(in, sigmoid, buffer_result);
    }
}
