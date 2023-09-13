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
const bool isConvBias = false;
const int HEIGHT_OUT = (HEIGHT_IN - KERNEL_SIZE + 2 * PADDING) / STRIDE + 1;
const int WIDTH_OUT = (WIDTH_IN - KERNEL_SIZE + 2 * PADDING) / STRIDE + 1;

static void load_input_mean(float *data,
                            float in[BATCH_SIZE][CHANNEL_IN][IMAGE_H][IMAGE_W], float *mean)
{

    float total = IMAGE_H * IMAGE_W;
    float sum[BATCH_SIZE * CHANNEL_IN];

init_sum:
    for (int b = 0; b < BATCH_SIZE; b++)
    {
#pragma HLS LOOP_TRIPCOUNT min = BATCH_SIZE max = BATCH_SIZE
        for (int c = 0; c < CHANNEL_IN; c++)
        {
#pragma HLS UNROLL
            sum[b * CHANNEL_IN + c] = 0;
        }
    }

load_data:
    for (int n = 0; n < BATCH_SIZE; n++)
    {
#pragma HLS LOOP_TRIPCOUNT min = BATCH_SIZE max = BATCH_SIZE
        for (int c = 0; c < CHANNEL_IN; c++)
        {
#pragma HLS LOOP_TRIPCOUNT min = CHANNEL_IN max = CHANNEL_IN
            for (int h = 0; h < IMAGE_H; h++)
            {
#pragma HLS LOOP_TRIPCOUNT min = IMAGE_H max = IMAGE_H
                for (int w = 0; w < IMAGE_W; w++)
                {
#pragma HLS UNROLL
                    in[n][c][h][w] = data[n * CHANNEL_IN * IMAGE_H * IMAGE_W + c * IMAGE_H * IMAGE_W + h * IMAGE_W + w];
                }
            }
        }
    }

compute_mean:
    for (int b = 0; b < BATCH_SIZE; b++)
    {
#pragma HLS LOOP_TRIPCOUNT min = BATCH_SIZE max = BATCH_SIZE
        for (int c = 0; c < CHANNEL_IN; c++)
        {
#pragma HLS LOOP_TRIPCOUNT min = CHANNEL_IN max = CHANNEL_IN
            for (int i = 0; i < IMAGE_H; i++)
            {
#pragma HLS LOOP_TRIPCOUNT min = IMAGE_H max = IMAGE_H
                for (int j = 0; j < IMAGE_W; j++)
                {
#pragma HLS UNROLL
                    sum[b * CHANNEL_IN + c] += in[b][c][i][j];
                }
            }
        }
    }

    for (int b = 0; b < BATCH_SIZE; b++)
    {
#pragma HLS LOOP_TRIPCOUNT min = BATCH_SIZE max = BATCH_SIZE
        for (int c = 0; c < CHANNEL_IN; c++)
        {
#pragma HLS UNROLL
            mean[b * BATCH_SIZE + c] = sum[b * BATCH_SIZE + c] / total;
        }
    }
}

static void compute_conv_reduce(float *in, float *reduce_conv, float *out)
{
    // The kernel is operating with vector of NUM_WORDS integers. The + operator performs
    // an element-wise add, resulting in NUM_WORDS parallel additions.

    float kernel[CHANNEL_OUT][CHANNEL_IN][KERNEL_SIZE][KERNEL_SIZE];
#pragma HLS array_partition variable = kernel complete dim = 1
    float bias[CHANNEL_OUT];
#pragma HLS array_partition variable = bias complete dim = 1

init_out:
    for (int b = 0; b < BATCH_SIZE; b++)
    {
#pragma HLS LOOP_TRIPCOUNT min = BATCH_SIZE max = BATCH_SIZE
        for (int c = 0; c < CHANNEL_OUT; c++)
        {
#pragma HLS UNROLL
            out[b * BATCH_SIZE + c] = 0;
        }
    }

init_kernel_bias:
    for (int k = 0; k < CHANNEL_OUT; k++)
    {
#pragma HLS LOOP_TRIPCOUNT min = CHANNEL_OUT max = CHANNEL_OUT
        bias[k] = k + 0.01;
        for (int l = 0; l < CHANNEL_IN; l++)
        {
#pragma HLS LOOP_TRIPCOUNT min = CHANNEL_IN max = CHANNEL_IN
            for (int i = 0; i < KERNEL_SIZE; i++)
            {
#pragma HLS UNROLL
                for (int j = 0; j < KERNEL_SIZE; j++)
                {
#pragma HLS UNROLL
                    kernel[k][l][i][j] = 0.1;
                }
            }
        }
    }

execute:
Batch:
    for (int batch = 0; batch < BATCH_SIZE; batch++)
    {
#pragma HLS LOOP_TRIPCOUNT min = BATCH_SIZE max = BATCH_SIZE
    Out_Row:
        for (int row = 0; row < HEIGHT_OUT; row++)
        {
#pragma HLS LOOP_TRIPCOUNT min = HEIGHT_OUT max = HEIGHT_OUT
        Out_Column:
            for (int col = 0; col < WIDTH_OUT; col++)
            {
// #pragma HLS PIPELINE
#pragma HLS LOOP_TRIPCOUNT min = WIDTH_OUT max = WIDTH_OUT
            Output_Channel:
                for (int out_ch = 0; out_ch < CHANNEL_OUT; out_ch++)
                {
#pragma HLS LOOP_TRIPCOUNT min = CHANNEL_OUT max = CHANNEL_OUT
                In_Channel:
                    for (int in_ch = 0; in_ch < CHANNEL_IN; in_ch++)
                    {
#pragma HLS LOOP_TRIPCOUNT min = CHANNEL_IN max = CHANNEL_IN
                    Kernel_Row:
                        for (int kernel_row = 0; kernel_row < KERNEL_SIZE; kernel_row++)
                        {
#pragma HLS LOOP_TRIPCOUNT min = KERNEL_SIZE max = KERNEL_SIZE
                        Kernel_Col:
                            for (int kernel_col = 0; kernel_col < KERNEL_SIZE; kernel_col++)
                            {
#pragma HLS LOOP_TRIPCOUNT min = KERNEL_SIZE max = KERNEL_SIZE
                                int pos = batch * CHANNEL_IN * HEIGHT_IN * WIDTH_IN;
                                int row_index = row * STRIDE + kernel_row;
                                int col_index = col * STRIDE + kernel_col;
                                pos += in_ch * HEIGHT_IN * WIDTH_IN;
                                pos += row_index * WIDTH_IN;
                                pos += col_index;
                                reduce_conv[batch * BATCH_SIZE + out_ch] += in[pos] * kernel[out_ch][in_ch][kernel_row][kernel_col];
                            }
                        }
                    }
                    int out_index = batch * BATCH_SIZE + out_ch;
                    if (isConvBias)
                        reduce_conv[out_index] += bias[out_ch];
                }
            }
        }
    }

silu:
    for (int n = 0; n < BATCH_SIZE; n++)
    {
#pragma HLS LOOP_TRIPCOUNT min = BATCH_SIZE max = BATCH_SIZE
        for (int c = 0; c < CHANNEL_OUT; c++)
        {
#pragma HLS UNROLL
            out[n * BATCH_SIZE + c] = reduce_conv[n * BATCH_SIZE + c] * (1 / (1 + exp(-reduce_conv[n * BATCH_SIZE + c])));
        }
    }
}

static void compute_conv_expand(float *in, float *out)
{
    // The kernel is operating with vector of NUM_WORDS integers. The + operator performs
    // an element-wise add, resulting in NUM_WORDS parallel additions.

    float kernel[CHANNEL_IN][CHANNEL_OUT][KERNEL_SIZE][KERNEL_SIZE];
#pragma HLS array_partition variable = kernel complete dim = 1
    float bias[CHANNEL_IN];
#pragma HLS array_partition variable = bias complete dim = 1

init_out:
    for (int b = 0; b < BATCH_SIZE; b++)
    {
#pragma HLS LOOP_TRIPCOUNT min = BATCH_SIZE max = BATCH_SIZE
        for (int c = 0; c < CHANNEL_IN; c++)
        {
#pragma HLS UNROLL
            out[b * BATCH_SIZE + c] = 0;
        }
    }

init_kernel_bias:
    for (int k = 0; k < CHANNEL_IN; k++)
    {
#pragma HLS LOOP_TRIPCOUNT min = CHANNEL_IN max = CHANNEL_IN
        bias[k] = k + 0.01;
        for (int l = 0; l < CHANNEL_OUT; l++)
        {
#pragma HLS LOOP_TRIPCOUNT min = CHANNEL_OUT max = CHANNEL_OUT
            for (int i = 0; i < KERNEL_SIZE; i++)
            {
#pragma HLS UNROLL
                for (int j = 0; j < KERNEL_SIZE; j++)
                {
#pragma HLS UNROLL
                    kernel[k][l][i][j] = 0.005;
                }
            }
        }
    }

execute:
Batch:
    for (int batch = 0; batch < BATCH_SIZE; batch++)
    {
#pragma HLS LOOP_TRIPCOUNT min = BATCH_SIZE max = BATCH_SIZE
    Out_Row:
        for (int row = 0; row < HEIGHT_OUT; row++)
        {
#pragma HLS LOOP_TRIPCOUNT min = HEIGHT_OUT max = HEIGHT_OUT
        Out_Column:
            for (int col = 0; col < WIDTH_OUT; col++)
            {
// #pragma HLS PIPELINE
#pragma HLS LOOP_TRIPCOUNT min = WIDTH_OUT max = WIDTH_OUT
            Output_Channel:
                for (int out_ch = 0; out_ch < CHANNEL_IN; out_ch++)
                {
#pragma HLS LOOP_TRIPCOUNT min = CHANNEL_IN max = CHANNEL_IN
                In_Channel:
                    for (int in_ch = 0; in_ch < CHANNEL_OUT; in_ch++)
                    {
#pragma HLS LOOP_TRIPCOUNT min = CHANNEL_OUT max = CHANNEL_OUT
                    Kernel_Row:
                        for (int kernel_row = 0; kernel_row < KERNEL_SIZE; kernel_row++)
                        {
#pragma HLS LOOP_TRIPCOUNT min = KERNEL_SIZE max = KERNEL_SIZE
                        Kernel_Col:
                            for (int kernel_col = 0; kernel_col < KERNEL_SIZE; kernel_col++)
                            {
#pragma HLS LOOP_TRIPCOUNT min = KERNEL_SIZE max = KERNEL_SIZE
                                int pos = batch * CHANNEL_IN * HEIGHT_IN * WIDTH_IN;
                                int row_index = row * STRIDE + kernel_row;
                                int col_index = col * STRIDE + kernel_col;
                                pos += in_ch * HEIGHT_IN * WIDTH_IN;
                                pos += row_index * WIDTH_IN;
                                pos += col_index;
                                out[batch * BATCH_SIZE + out_ch] += in[pos] * kernel[out_ch][in_ch][kernel_row][kernel_col];
                            }
                        }
                    }
                    if (isConvBias)
                        out[batch * BATCH_SIZE + out_ch] += bias[out_ch];
                }
            }
        }
    }
}

static void compute_sigmoid(float *input, float *sigmoid)
{
    for (int b = 0; b < BATCH_SIZE; b++)
    {
#pragma HLS LOOP_TRIPCOUNT min = BATCH_SIZE max = BATCH_SIZE
        for (int c = 0; c < CHANNEL_IN; c++)
        {
#pragma HLS UNROLL
            float tmp = input[b * CHANNEL_IN + c];
            sigmoid[b * CHANNEL_IN + c] = 1 / (1 + exp(-tmp));
        }
    }
}

static void compute_mul(float in1[BATCH_SIZE][CHANNEL_IN][IMAGE_H][IMAGE_W], float *in2,
                        float *result)
{
    float val = 0;
    for (int b = 0; b < BATCH_SIZE; b++)
    {
#pragma HLS LOOP_TRIPCOUNT min = BATCH_SIZE max = BATCH_SIZE
        for (int c = 0; c < CHANNEL_IN; c++)
        {
#pragma HLS LOOP_TRIPCOUNT min = CHANNEL_IN max = CHANNEL_IN
            val = in2[b * CHANNEL_IN + c];
            for (int i = 0; i < IMAGE_H; i++)
            {
#pragma HLS LOOP_TRIPCOUNT min = IMAGE_H max = IMAGE_H
                for (int j = 0; j < IMAGE_W; j++)
                {
#pragma HLS UNROLL
                    int b_idx = b * CHANNEL_IN * IMAGE_H * IMAGE_W;
                    int c_idx = c * IMAGE_H * IMAGE_W;
                    int i_idx = i * IMAGE_W;
                    result[b_idx + c_idx + i_idx + j] = in1[b][c][i][j] * val;
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
        float mean[BATCH_SIZE * CHANNEL_IN];
#pragma HLS array_partition variable = mean complete dim = 1
        float reduce_conv[BATCH_SIZE * CHANNEL_OUT];
#pragma HLS array_partition variable = reduce_conv complete dim = 1
        float reduce_conv_silu[BATCH_SIZE * CHANNEL_OUT];
#pragma HLS array_partition variable = reduce_conv_silu complete dim = 1
        float expand_conv[BATCH_SIZE * CHANNEL_IN];
#pragma HLS array_partition variable = expand_conv complete dim = 1
        float sigmoid[BATCH_SIZE * CHANNEL_IN];
#pragma HLS array_partition variable = sigmoid complete dim = 1

        load_input_mean(image, in, mean);
        compute_conv_reduce(mean, reduce_conv, reduce_conv_silu);
        compute_conv_expand(reduce_conv_silu, expand_conv);
        compute_sigmoid(expand_conv, sigmoid);
        compute_mul(in, sigmoid, buffer_result);
    }
}
