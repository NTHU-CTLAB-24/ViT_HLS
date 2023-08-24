// Includes
#include <hls_stream.h>
#include <hls_math.h>
#include <stdint.h>
// TRIPCOUNT identifier
const int BATCH_SIZE = 1;
const int HEIGHT_IN = 14;
const int WIDTH_IN = 14;
const int CHANNEL_IN = 3;
const int CHANNEL_OUT = 16;
const int KERNEL_SIZE = 3;
const int PADDING = 1;
const int STRIDE = 2;
const int HEIGHT_PAD = HEIGHT_IN + 2 * PADDING;
const int WIDTH_PAD = WIDTH_IN + 2 * PADDING;
const int HEIGHT_OUT = (HEIGHT_IN - KERNEL_SIZE + 2 * PADDING) / STRIDE + 1;
const int WIDTH_OUT = (WIDTH_IN - KERNEL_SIZE + 2 * PADDING) / STRIDE + 1;

static void load_input(float* in1, float* in2, float* in3, 
    float* buffer1, float* buffer2, float* mean, float* var, float* norm) {
input_data:
    for (int n = 0; n < BATCH_SIZE; n++) {
#pragma HLS LOOP_TRIPCOUNT min = BATCH_SIZE max = BATCH_SIZE
        for (int c = 0; c < CHANNEL_IN; c++) {
#pragma HLS LOOP_TRIPCOUNT min = CHANNEL_IN max = CHANNEL_IN
            for (int h = 0; h < HEIGHT_IN; h++) {
#pragma HLS LOOP_TRIPCOUNT min = HEIGHT_IN max = HEIGHT_IN
                for (int w = 0; w < WIDTH_IN; w++) {
#pragma HLS LOOP_TRIPCOUNT min = WIDTH_IN max = WIDTH_IN
                    buffer1[n * CHANNEL_IN * HEIGHT_IN * WIDTH_IN + c * HEIGHT_IN * WIDTH_IN + h * WIDTH_IN + w] = in1[n * CHANNEL_IN * HEIGHT_IN * WIDTH_IN + c * HEIGHT_IN * WIDTH_IN + h * WIDTH_IN + w];
                }
            }
        }
    }

init_kernel:
    for (int k = 0; k < CHANNEL_OUT; k++) {
#pragma HLS LOOP_TRIPCOUNT min = CHANNEL_OUT max = CHANNEL_OUT
        for (int i = 0; i < KERNEL_SIZE; i++) {
#pragma HLS LOOP_TRIPCOUNT min = KERNEL_SIZE max = KERNEL_SIZE
            for (int j = 0; j < KERNEL_SIZE; j++) {
#pragma HLS LOOP_TRIPCOUNT min = KERNEL_SIZE max = KERNEL_SIZE
                buffer2[k * KERNEL_SIZE * KERNEL_SIZE + i * KERNEL_SIZE + j] = in2[k * KERNEL_SIZE * KERNEL_SIZE + i * KERNEL_SIZE + j];
            }
        }
    }
init_norm_parameter:
    for (int i=0; i<CHANNEL_OUT; i++) {
#pragma HLS LOOP_TRIPCOUNT min = CHANNEL_OUT max = CHANNEL_OUT
        mean[i] = in3[i];
        var[i] = in3[i+CHANNEL_OUT];
    }
    norm[0] = in3[CHANNEL_OUT*2];
    norm[1] = in3[CHANNEL_OUT*2 + 1];
}

static void compute_conv(float* in, float* kernel, float* in_pad, float* result) {

        for (int b = 0; b < BATCH_SIZE; b++) {
#pragma HLS LOOP_TRIPCOUNT min = BATCH_SIZE max = BATCH_SIZE
            for (int c = 0; c < CHANNEL_IN; c++) {
#pragma HLS LOOP_TRIPCOUNT min = CHANNEL_IN max = CHANNEL_IN
                for (int i = 0; i < HEIGHT_PAD; i++) {
#pragma HLS LOOP_TRIPCOUNT min = HEIGHT_PAD max = HEIGHT_PAD
                    for (int j = 0; j < WIDTH_PAD; j++) {
#pragma HLS LOOP_TRIPCOUNT min = WIDTH_PAD max = WIDTH_PAD
                        int pos = b * CHANNEL_IN * HEIGHT_PAD * WIDTH_PAD + c * HEIGHT_PAD * WIDTH_PAD + i * WIDTH_PAD + j;
                        if (i < PADDING || i >= (HEIGHT_IN + PADDING) || j < PADDING || j >= (WIDTH_IN + PADDING))
                            in_pad[pos] = 0;
                        else
                            in_pad[pos] = in[b * CHANNEL_IN * HEIGHT_IN * WIDTH_IN + c * HEIGHT_IN * WIDTH_IN + (i - PADDING) * WIDTH_IN + j - PADDING];
                    }
                }
            }
        }
    
execute:
Batch:
    for (int batch = 0; batch < BATCH_SIZE; batch++){
#pragma HLS LOOP_TRIPCOUNT min = BATCH_SIZE max = BATCH_SIZE
    Out_Row:
        for (int row = 0; row < HEIGHT_OUT; row++){
#pragma HLS LOOP_TRIPCOUNT min = HEIGHT_OUT max = HEIGHT_OUT
        Out_Column:
            for (int col = 0; col < WIDTH_OUT; col++){
// #pragma HLS PIPELINE
#pragma HLS LOOP_TRIPCOUNT min = WIDTH_OUT max = WIDTH_OUT
            Output_Channel:
                for (int out_ch = 0; out_ch < CHANNEL_OUT; out_ch++){
#pragma HLS LOOP_TRIPCOUNT min = CHANNEL_OUT max = CHANNEL_OUT
                	float sum = 0.0;
                In_Channel:
                    for (int in_ch = 0; in_ch < CHANNEL_IN; in_ch++){
#pragma HLS LOOP_TRIPCOUNT min = CHANNEL_IN max = CHANNEL_IN
                    Kernel_Row:
                        for (int kernel_row = 0; kernel_row < KERNEL_SIZE; kernel_row++){
#pragma HLS LOOP_TRIPCOUNT min = KERNEL_SIZE max = KERNEL_SIZE
                        Kernel_Col:
                            for (int kernel_col = 0; kernel_col < KERNEL_SIZE; kernel_col++){
#pragma HLS LOOP_TRIPCOUNT min = KERNEL_SIZE max = KERNEL_SIZE
                                int pos_row = row * STRIDE + kernel_row;
                                int pos_col = col * STRIDE + kernel_col;
                                int pos = batch*CHANNEL_IN*HEIGHT_PAD*WIDTH_PAD + in_ch*HEIGHT_PAD*WIDTH_PAD + pos_row*WIDTH_PAD + pos_col;
                                int kernel_pos = out_ch*KERNEL_SIZE*KERNEL_SIZE + kernel_row*KERNEL_SIZE + kernel_col;
                                sum += in_pad[pos] * kernel[kernel_pos];
                            }
                        }
                    }
                    result[batch * CHANNEL_OUT * HEIGHT_OUT * WIDTH_OUT + out_ch * HEIGHT_OUT * WIDTH_OUT + row * WIDTH_OUT + col] = sum;
                }
            }
        }
    }
}

static void compute_batchnorm(float* in, float* out, float* mean, float* var, float* norm) {
    int pos;
    float gamma = norm[0];
    float beta = norm[1];

    for (int b = 0; b < BATCH_SIZE; b++) {
#pragma HLS LOOP_TRIPCOUNT min = BATCH_SIZE max = BATCH_SIZE
        for (int c = 0; c < CHANNEL_OUT; c++) {
#pragma HLS LOOP_TRIPCOUNT min = CHANNEL_OUT max = CHANNEL_OUT
            for (int i = 0; i < HEIGHT_OUT; i++) {
#pragma HLS LOOP_TRIPCOUNT min = HEIGHT_OUT max = HEIGHT_OUT
                for (int j = 0; j < WIDTH_OUT; j++) {
#pragma HLS LOOP_TRIPCOUNT min = WIDTH_OUT max = WIDTH_OUT
                    pos = b * CHANNEL_OUT * HEIGHT_OUT * WIDTH_OUT + c * HEIGHT_OUT * WIDTH_OUT + i * WIDTH_OUT + j;
                    out[pos] = (in[pos] - mean[c]) / sqrt(var[c] + 1e-5) * gamma + beta;
                }
            }
        }
    }


}

extern "C" {
    void kernel_mspatch(float* in1, float* in2, float* in3, float* buffer_result) {
#pragma HLS INTERFACE m_axi port = in1 bundle = gmem0
#pragma HLS INTERFACE m_axi port = in2 bundle = gmem1
#pragma HLS INTERFACE m_axi port = in3 bundle = gmem2
#pragma HLS INTERFACE m_axi port = buffer_result bundle = gmem0


        float image[BATCH_SIZE * CHANNEL_IN * HEIGHT_IN * WIDTH_IN];
#pragma HLS array_partition variable = image complete dim = 1
        float kernel[CHANNEL_OUT * KERNEL_SIZE * KERNEL_SIZE];
#pragma HLS array_partition variable = kernel complete dim = 1
        float in_pad[BATCH_SIZE * CHANNEL_IN * HEIGHT_PAD * WIDTH_PAD];
#pragma HLS array_partition variable = in_pad complete dim = 1
        float conv_result[BATCH_SIZE * CHANNEL_OUT * HEIGHT_OUT * WIDTH_OUT];
#pragma HLS array_partition variable = conv_result complete dim = 1


        float mean[CHANNEL_OUT];
        float var[CHANNEL_OUT];
        float norm[2];

        load_input(in1, in2, in3, image, kernel, mean, var, norm);
        compute_conv(image, kernel, in_pad, conv_result);
        compute_batchnorm(conv_result, buffer_result, mean, var, norm);
    }
}