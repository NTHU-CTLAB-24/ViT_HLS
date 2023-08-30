// Includes
#include <hls_math.h>
#include <hls_stream.h>
#include <stdint.h>

// TRIPCOUNT identifier
const int BATCH_SIZE = 2;
const int CHANNEL_IN = 3;
const int HEIGHT_IN = 16;
const int WIDTH_IN = 16;

// BatchNorm parameters
const float EPS = 1e-5;

// Coding Style: function宣告要為static，遇到for迴圈前可以取error_type的名稱(ex: mem_rd)

static void load_input(float *buffer_DataIn_1,
                       float in[BATCH_SIZE][CHANNEL_IN][HEIGHT_IN][WIDTH_IN])
{
init_in:
    for (int n = 0; n < BATCH_SIZE; n++)
    {
#pragma HLS LOOP_TRIPCOUNT min = BATCH_SIZE max = BATCH_SIZE
        for (int c = 0; c < CHANNEL_IN; c++)
        {
#pragma HLS LOOP_TRIPCOUNT min = CHANNEL_IN max = CHANNEL_IN
            for (int h = 0; h < HEIGHT_IN; h++)
            {
#pragma HLS LOOP_TRIPCOUNT min = HEIGHT_IN max = HEIGHT_IN
                for (int w = 0; w < WIDTH_IN; w++)
                {
#pragma HLS LOOP_TRIPCOUNT min = WIDTH_IN max = WIDTH_IN
                    in[n][c][h][w] = buffer_DataIn_1[n * CHANNEL_IN * HEIGHT_IN * WIDTH_IN + c * HEIGHT_IN * WIDTH_IN + h * WIDTH_IN + w];
                }
            }
        }
    }
}

static void compute_norm(float in[BATCH_SIZE][CHANNEL_IN][HEIGHT_IN][WIDTH_IN],
                         float *buffer_result)
{
    const float RUNNING_MEAN[CHANNEL_IN] = {8, 8, 8};
#pragma HLS array_partition variable = RUNNING_MEAN complete dim = 1
    const float RUNNING_VAR[CHANNEL_IN] = {21.5, 21.5, 21.5};
#pragma HLS array_partition variable = RUNNING_VAR complete dim = 1
    const float weight[CHANNEL_IN] = {0.5, 0.5, 0.5};
#pragma HLS array_partition variable = weight complete dim = 1
    const float bias[CHANNEL_IN] = {0.2, 0.2, 0.2};
#pragma HLS array_partition variable = bias complete dim = 1

Batch_norm:
    for (int n = 0; n < BATCH_SIZE; n++)
    {
#pragma HLS LOOP_TRIPCOUNT min = BATCH_SIZE max = BATCH_SIZE
        for (int c = 0; c < CHANNEL_IN; c++)
        {
#pragma HLS LOOP_TRIPCOUNT min = CHANNEL_IN max = CHANNEL_IN
            for (int h = 0; h < HEIGHT_IN; h++)
            {
#pragma HLS LOOP_TRIPCOUNT min = HEIGHT_IN max = HEIGHT_IN
                for (int w = 0; w < WIDTH_IN; w++)
                {
#pragma HLS LOOP_TRIPCOUNT min = WIDTH_IN max = WIDTH_IN
                    buffer_result[n * CHANNEL_IN * HEIGHT_IN * WIDTH_IN + c * HEIGHT_IN * WIDTH_IN + h * WIDTH_IN + w] = ((in[n][c][h][w] - RUNNING_MEAN[c]) / sqrt(RUNNING_VAR[c] + EPS)) * weight[c] + bias[c];
                }
            }
        }
    }
}

extern "C"
{

    /*
        Vector Addition Kernel

        Arguments:
            in1  (input)  --> Input vector 1
            in2  (input)  --> Input vector 2
            out  (output) --> Output vector
            size (input)  --> Number of elements in vector
    */

    void krnl_batchnorm(float *buffer_DataIn_1,
                              float *buffer_result)
    {
#pragma HLS INTERFACE m_axi port = buffer_DataIn_1 bundle = gmem0
#pragma HLS INTERFACE m_axi port = buffer_result bundle = gmem0

#pragma HLS dataflow
        float in[BATCH_SIZE][CHANNEL_IN][HEIGHT_IN][WIDTH_IN];
#pragma HLS array_partition variable = in complete dim = 1

        load_input(buffer_DataIn_1, in);
        compute_norm(in, buffer_result);

    }
}
