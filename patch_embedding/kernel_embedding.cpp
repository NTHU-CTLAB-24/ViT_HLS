// Includes
#include <hls_stream.h>
#include <stdint.h>

// TRIPCOUNT identifier
const int BATCH_SIZE = 1;
const int HEIGHT_IN = 16;
const int WIDTH_IN = 16;
const int CHANNEL_IN = 3;
const int KERNEL_SIZE = 4;
const int PADDING = 0;
const int STRIDE = 4;
const int HEIGHT_OUT = (HEIGHT_IN - KERNEL_SIZE + 2 * PADDING) / STRIDE + 1;
const int WIDTH_OUT = (WIDTH_IN - KERNEL_SIZE + 2 * PADDING) / STRIDE + 1;
const int NUM_PATCH = (WIDTH_OUT * HEIGHT_OUT) + 1; //including class token
const int CHANNEL_OUT = 10;
const int IN_SIZE = HEIGHT_IN * WIDTH_IN * CHANNEL_IN;
const int OUT_SIZE = HEIGHT_OUT * WIDTH_OUT * CHANNEL_OUT;

static void load_input(float* buffer_DataIn_1, float* buffer_DataIn_2,
    float in[HEIGHT_IN][WIDTH_IN][CHANNEL_IN],
    float kernel[KERNEL_SIZE][KERNEL_SIZE][CHANNEL_OUT]) {
init_in:
    for (int i = 0; i < HEIGHT_IN; i++) {
#pragma HLS LOOP_TRIPCOUNT min = HEIGHT_IN max = HEIGHT_IN
        for (int j = 0; j < WIDTH_IN; j++) {
#pragma HLS LOOP_TRIPCOUNT min = WIDTH_IN max = WIDTH_IN
            for (int k = 0; k < CHANNEL_IN; k++) {
#pragma HLS LOOP_TRIPCOUNT min = CHANNEL_IN max = CHANNEL_IN
                in[i][j][k] = buffer_DataIn_1[i * WIDTH_IN * CHANNEL_IN + j * CHANNEL_IN + k];
            }
        }
    }

init_kernel:
    for (int i = 0; i < KERNEL_SIZE; i++) {
#pragma HLS LOOP_TRIPCOUNT min = KERNEL_SIZE max = KERNEL_SIZE
        for (int j = 0; j < KERNEL_SIZE; j++) {
#pragma HLS LOOP_TRIPCOUNT min = KERNEL_SIZE max = KERNEL_SIZE
            for (int k = 0; k < CHANNEL_OUT; k++) {
#pragma HLS LOOP_TRIPCOUNT min = CHANNEL_OUT max = CHANNEL_OUT
                kernel[i][j][k] = buffer_DataIn_2[i * KERNEL_SIZE * CHANNEL_OUT + j * CHANNEL_OUT + k];
            }
        }
    }
}
static void embedding(float in[HEIGHT_IN][WIDTH_IN][CHANNEL_IN],
                         float kernel[KERNEL_SIZE][KERNEL_SIZE][CHANNEL_OUT],
                         float* in3, float* in4, float* result) {
float tmp[NUM_PATCH * CHANNEL_OUT];

patch_conv:
    int index = 1;
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
                    float sum = 0.0;
                Kernel_Row:
                    for (int kernel_row = 0; kernel_row < KERNEL_SIZE; kernel_row++)
                    {
#pragma HLS LOOP_TRIPCOUNT min = KERNEL_SIZE max = KERNEL_SIZE
                    Kernel_Col:
                        for (int kernel_col = 0; kernel_col < KERNEL_SIZE; kernel_col++)
                        {
#pragma HLS LOOP_TRIPCOUNT min = KERNEL_SIZE max = KERNEL_SIZE
                        In_Channel:
                            for (int in_ch = 0; in_ch < CHANNEL_IN; in_ch++)
                            {
#pragma HLS LOOP_TRIPCOUNT min = CHANNEL_IN max = CHANNEL_IN
                                sum += in[row * STRIDE + kernel_row][col * STRIDE + kernel_col][in_ch] * kernel[kernel_row][kernel_col][out_ch];
                            }
                        }
                    }
                    index = (row * WIDTH_OUT  + col) * CHANNEL_OUT + out_ch;
                    //output[index][out_ch] = sum;
                    tmp[index] = sum;
                }
            }
        }

concate_class_position:
    for (int c=0; c<CHANNEL_OUT; c++) {
#pragma HLS LOOP_TRIPCOUNT min = CHANNEL_OUT max = CHANNEL_OUT
        result[c] = in3[c] + in4[c];
    }

    for (int i = 1; i < NUM_PATCH; i++) {
#pragma HLS LOOP_TRIPCOUNT min = NUM_PATCH max = NUM_PATCH
        for (int j = 0; j < CHANNEL_OUT; j++) {
#pragma HLS LOOP_TRIPCOUNT min = CHANNEL_OUT max = CHANNEL_OUT
            int pos = (i-1) * CHANNEL_OUT + j;
            result[i * CHANNEL_OUT + j] = tmp[pos] + in4[i * CHANNEL_OUT + j];
        }
    }
}
extern "C"
{
    /*
        Arguments:
            in1  (input)  --> image data
            in2  (input)  --> kernel (filter)
            in3  (input)  --> class token
            in4  (input)  --> position
            result (output) --> patch embedding result

    */

    void kernel_embedding(float* in1, float* in2, float* in3, float* in4, float* result) {
#pragma HLS INTERFACE m_axi port = in1 bundle = gmem0
#pragma HLS INTERFACE m_axi port = in2 bundle = gmem1
#pragma HLS INTERFACE m_axi port = in3 bundle = gmem2
#pragma HLS INTERFACE m_axi port = in4 bundle = gmem3
#pragma HLS INTERFACE m_axi port = result bundle = gmem0

#pragma HLS dataflow
// dataflow pragma instruct compiler to run following three APIs in parallel
        float in[HEIGHT_IN][WIDTH_IN][CHANNEL_IN];
#pragma HLS array_partition variable = in complete dim = 1

        float kernel[KERNEL_SIZE][KERNEL_SIZE][CHANNEL_OUT];
#pragma HLS array_partition variable = kernel complete dim = 1

        load_input(in1, in2, in, kernel);
        embedding(in, kernel, in3, in4, result);
    }
}
