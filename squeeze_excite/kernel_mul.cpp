// Includes
#include <hls_stream.h>
#include <stdint.h>

// TRIPCOUNT identifier
const int BATCH_SIZE = 1;
const int HEIGHT_IN = 16;
const int WIDTH_IN = 16;
const int CHANNEL_IN = 16;

static void load_input(float* data_1, float* data_2,
    float buffer_1[BATCH_SIZE][CHANNEL_IN][HEIGHT_IN][WIDTH_IN],
    float buffer_2[BATCH_SIZE][CHANNEL_IN]) {
    for (int b = 0; b < BATCH_SIZE; b++) {
#pragma HLS LOOP_TRIPCOUNT min = BATCH_SIZE max = BATCH_SIZE
        for (int c = 0; c < CHANNEL_IN; c++) {
#pragma HLS LOOP_TRIPCOUNT min = CHANNEL_IN max = CHANNEL_IN
            for (int i = 0; i < HEIGHT_IN; i++) {
#pragma HLS LOOP_TRIPCOUNT min = HEIGHT_IN max = HEIGHT_IN
                for (int j = 0; j < WIDTH_IN; j++) {
#pragma HLS LOOP_TRIPCOUNT min = WIDTH_IN max = WIDTH_IN
                    buffer_1[b][c][i][j] = data_1[b * CHANNEL_IN * HEIGHT_IN * WIDTH_IN + c * HEIGHT_IN * WIDTH_IN + i * WIDTH_IN + j];
                }
            }
        }
    }
    for (int b = 0; b < BATCH_SIZE; b++) {
#pragma HLS LOOP_TRIPCOUNT min = BATCH_SIZE max = BATCH_SIZE
        for (int c = 0; c < CHANNEL_IN; c++) {
#pragma HLS LOOP_TRIPCOUNT min = CHANNEL_IN max = CHANNEL_IN
            buffer_2[b][c] = data_2[b * CHANNEL_IN + c];
        }
    }
}
static void compute_mul(float in1[BATCH_SIZE][CHANNEL_IN][HEIGHT_IN][WIDTH_IN],
    float in2[BATCH_SIZE][CHANNEL_IN],
    float* result) {
    float val = 0;
    for (int b = 0; b < BATCH_SIZE; b++) {
#pragma HLS LOOP_TRIPCOUNT min = BATCH_SIZE max = BATCH_SIZE
        for (int c = 0; c < CHANNEL_IN; c++) {
#pragma HLS LOOP_TRIPCOUNT min = CHANNEL_IN max = CHANNEL_IN
            val = in2[b][c];
            for (int i = 0; i < HEIGHT_IN; i++) {
                for (int j = 0; j < WIDTH_IN; j++) {
                    result[b * CHANNEL_IN * HEIGHT_IN * WIDTH_IN + c * HEIGHT_IN * WIDTH_IN + i * WIDTH_IN + j] = in1[b][c][i][j] * val;
                }
            }
        }
    }
}
extern "C"
{
    void kernel_mul(float* in1, float* in2, float* result) {
#pragma HLS INTERFACE m_axi port = in1 bundle = gmem0
#pragma HLS INTERFACE m_axi port = in2 bundle = gmem1
#pragma HLS INTERFACE m_axi port = result bundle = gmem0

#pragma HLS dataflow
        // dataflow pragma instruct compiler to run following three APIs in parallel
        float x[BATCH_SIZE][CHANNEL_IN][HEIGHT_IN][WIDTH_IN];
#pragma HLS array_partition variable = x complete dim = 1
        float x_se[BATCH_SIZE][CHANNEL_IN];
#pragma HLS array_partition variable = x_se complete dim = 1

        load_input(in1, in2, x, x_se);
        compute_mul(x, x_se, result);
    }
}
