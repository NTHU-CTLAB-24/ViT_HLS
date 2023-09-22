// Includes
#include <hls_math.h>
#include <hls_stream.h>
#include <stdint.h>

/* Remember to modify test file */

// TODO: modify size
// TRIPCOUNT identifie
const int BATCH_SIZE = 1;
const int CHANNEL_IN = 32;
const int CHANNEL_OUT = 32;
const int HEIGHT_IN = 4;
const int WIDTH_IN = 4;

const int HEIGHT_OUT = HEIGHT_IN;
const int WIDTH_OUT = WIDTH_IN;

// Normalization parameters
const float EPS = 1e-6;

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
#pragma HLS UNROLL
                    in[n][c][h][w] = buffer_DataIn_1[n * CHANNEL_IN * HEIGHT_IN * WIDTH_IN + c * HEIGHT_IN * WIDTH_IN + h * WIDTH_IN + w];
                }
            }
        }
    }
}

static void compute_norm(float in[BATCH_SIZE][CHANNEL_OUT][HEIGHT_OUT][WIDTH_OUT],
                         float* buffer_result)
{
        float RUNNING_MEAN[CHANNEL_OUT];
#pragma HLS array_partition variable = RUNNING_MEAN complete dim = 1
        float RUNNING_VAR[CHANNEL_OUT];
#pragma HLS array_partition variable = RUNNING_VAR complete dim = 1
        float weight[CHANNEL_OUT];
#pragma HLS array_partition variable = weight complete dim = 1
        float bias[CHANNEL_OUT];
#pragma HLS array_partition variable = bias complete dim = 1

    init_parameters:
        for (int c = 0; c < CHANNEL_OUT; c++)
        {
#pragma HLS UNROLL
            RUNNING_MEAN[c] = 8;
            RUNNING_VAR[c] = 21.5;
            weight[c] = 0.5;
            bias[c] = 0.2;
        }

    Batch_norm:
        for (int n = 0; n < BATCH_SIZE; n++)
        {
#pragma HLS LOOP_TRIPCOUNT min = BATCH_SIZE max = BATCH_SIZE
            for (int c = 0; c < CHANNEL_OUT; c++)
            {
#pragma HLS LOOP_TRIPCOUNT min = CHANNEL_OUT max = CHANNEL_OUT
                for (int h = 0; h < HEIGHT_OUT; h++)
                {
#pragma HLS LOOP_TRIPCOUNT min = HEIGHT_OUT max = HEIGHT_OUT
                    for (int w = 0; w < WIDTH_OUT; w++)
                    {
#pragma HLS UNROLL
                         buffer_result[n * CHANNEL_OUT * HEIGHT_OUT * WIDTH_OUT + c * HEIGHT_OUT * WIDTH_OUT + h * WIDTH_OUT + w] = ((in[n][c][h][w] - RUNNING_MEAN[c]) / sqrt(RUNNING_VAR[c] + EPS)) * weight[c] + bias[c];
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

    void kernel_norm_in_1(float *buffer_DataIn_1,
                        float *buffer_result)
    {
// TODO: modify depth
#pragma HLS INTERFACE m_axi port = buffer_DataIn_1 bundle = gmem0 depth = 512
#pragma HLS INTERFACE m_axi port = buffer_result bundle = gmem0 depth = 512

        #pragma HLS dataflow
        // dataflow僅可以接受single reader and single writer
        // dataflow pragma instruct compiler to run following three APIs in parallel
        float in[BATCH_SIZE][CHANNEL_IN][HEIGHT_IN][WIDTH_IN];
#pragma HLS array_partition variable = in complete dim = 1
        load_input(buffer_DataIn_1, in);
        compute_norm(in, buffer_result);
    }
}
