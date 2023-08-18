// Includes
#include <hls_stream.h>
#include <hls_math.h>
#include <stdint.h>
// TRIPCOUNT identifier
const int BATCH_SIZE = 1;
const int IMAGE_H = 16;
const int IMAGE_W = 16;
const int HEIGHT_IN = 1;
const int WIDTH_IN = 1;
const int CHANNEL_IN = 16;
const int KERNEL_SIZE = 1;
const int PADDING = 0;
const int STRIDE = 1;
const int CHANNEL_OUT = 4;//REDUCE_CHS
const int HEIGHT_OUT = (HEIGHT_IN - KERNEL_SIZE + 2 * PADDING) / STRIDE + 1;
const int WIDTH_OUT = (WIDTH_IN - KERNEL_SIZE + 2 * PADDING) / STRIDE + 1;

static void load_input(float* data, float* kernel_reduce, float* kernel_expand,
    float store_in[BATCH_SIZE][CHANNEL_IN][IMAGE_H][IMAGE_W],
    float* store_kernel1, int cout_1, float* store_kernel2, int cout_2) {
input_data:
    for (int n = 0; n < BATCH_SIZE; n++) {
#pragma HLS LOOP_TRIPCOUNT min = BATCH_SIZE max = BATCH_SIZE
        for (int c = 0; c < CHANNEL_IN; c++) {
#pragma HLS LOOP_TRIPCOUNT min = CHANNEL_IN max = CHANNEL_IN
            for (int h = 0; h < IMAGE_H; h++) {
#pragma HLS LOOP_TRIPCOUNT min = IMAGE_H max = IMAGE_H
                for (int w = 0; w < IMAGE_W; w++) {
#pragma HLS LOOP_TRIPCOUNT min = IMAGE_W max = IMAGE_W
                    store_in[n][c][h][w] = data[n * CHANNEL_IN * IMAGE_H * IMAGE_W + c * IMAGE_H * IMAGE_W + h * IMAGE_W + w];
                }
            }
        }
    }

init_kernel_reduce:
    for (int k = 0; k < cout_1; k++) {
#pragma HLS LOOP_TRIPCOUNT min = cout_1 max = cout_1
        for (int i = 0; i < KERNEL_SIZE; i++) {
#pragma HLS LOOP_TRIPCOUNT min = KERNEL_SIZE max = KERNEL_SIZE
            for (int j = 0; j < KERNEL_SIZE; j++) {
#pragma HLS LOOP_TRIPCOUNT min = KERNEL_SIZE max = KERNEL_SIZE
                store_kernel1[k * KERNEL_SIZE * KERNEL_SIZE + i * KERNEL_SIZE + j] = kernel_reduce[k * KERNEL_SIZE * KERNEL_SIZE + i * KERNEL_SIZE + j];
            }
        }
    }

init_kernel_expand:
    for (int k = 0; k < cout_2; k++) {
#pragma HLS LOOP_TRIPCOUNT min = cout_2 max = cout_2
        for (int i = 0; i < KERNEL_SIZE; i++) {
#pragma HLS LOOP_TRIPCOUNT min = KERNEL_SIZE max = KERNEL_SIZE
            for (int j = 0; j < KERNEL_SIZE; j++) {
#pragma HLS LOOP_TRIPCOUNT min = KERNEL_SIZE max = KERNEL_SIZE
                store_kernel2[k * KERNEL_SIZE * KERNEL_SIZE + i * KERNEL_SIZE + j] = kernel_expand[k * KERNEL_SIZE * KERNEL_SIZE + i * KERNEL_SIZE + j];
            }
        }
    }
}
static void compute_mean(float in[BATCH_SIZE][CHANNEL_IN][IMAGE_H][IMAGE_W], float* mean) {
    int total = IMAGE_H * IMAGE_W;
    for (int b = 0; b < BATCH_SIZE; b++) {
#pragma HLS LOOP_TRIPCOUNT min = BATCH_SIZE max = BATCH_SIZE
        for (int c = 0; c < CHANNEL_IN; c++) {
#pragma HLS LOOP_TRIPCOUNT min = CHANNEL_IN max = CHANNEL_IN
            float sum = 0;
            for (int i = 0; i < IMAGE_H; i++) {
#pragma HLS LOOP_TRIPCOUNT min = IMAGE_H max = IMAGE_H
                for (int j = 0; j < IMAGE_W; j++) {
#pragma HLS LOOP_TRIPCOUNT min = IMAGE_W max = IMAGE_W
                    sum += in[b][c][i][j];
                }
            }
            mean[b * BATCH_SIZE + c] = sum / total;
        }
    }

}

static void compute_conv(float* in, float* kernel, float* buffer_result, int cin, int cout, int height, int width, int kernel_size = 1, int stride = 1, int padding = 0) {
    int height_out = (height - kernel_size + 2 * padding) / stride + 1;
    int width_out = (width - kernel_size + 2 * padding) / stride + 1;
execute:
Batch:
    for (int batch = 0; batch < BATCH_SIZE; batch++) {
#pragma HLS LOOP_TRIPCOUNT min = BATCH_SIZE max = BATCH_SIZE
        Out_Row :
        for (int row = 0; row < height_out; row++) {
#pragma HLS LOOP_TRIPCOUNT min = height_out max = height_out
            Out_Column :
            for (int col = 0; col < width_out; col++) {
#pragma HLS LOOP_TRIPCOUNT min = width_out max = width_out
                Output_Channel :
                for (int out_ch = 0; out_ch < cout; out_ch++) {
#pragma HLS LOOP_TRIPCOUNT min = cout max = cout
                    float sum = 0.0;
                In_Channel:
                    for (int in_ch = 0; in_ch < cin; in_ch++) {
#pragma HLS LOOP_TRIPCOUNT min = cin max = cin
                        Kernel_Row :
                        for (int kernel_row = 0; kernel_row < kernel_size; kernel_row++) {
#pragma HLS LOOP_TRIPCOUNT min = kernel_size max = kernel_size
                            Kernel_Col :
                            for (int kernel_col = 0; kernel_col < kernel_size; kernel_col++) {
#pragma HLS LOOP_TRIPCOUNT min = kernel_size max = kernel_size
                                int pos = batch * cin * height * width + in_ch * height * width + (row * stride + kernel_row) * width + (col * stride + kernel_col);
                                int pos_kernel = out_ch * kernel_size * kernel_size + kernel_row * kernel_size + kernel_col;
                                sum += in[pos] * kernel[pos_kernel];
                            }
                        }
                    }
                    buffer_result[batch * cout * height_out * width_out + out_ch * height_out * width_out + row * width_out + col] = sum;
                }
            }
        }
    }
}

static void compute_relu(float* input, float* output) {
    int val = 0;
    for (int b = 0; b < BATCH_SIZE; b++) {
#pragma HLS LOOP_TRIPCOUNT min = BATCH_SIZE max = BATCH_SIZE
        for (int c = 0; c < CHANNEL_OUT; c++) {
#pragma HLS LOOP_TRIPCOUNT min = CHANNEL_OUT max = CHANNEL_OUT
            val = input[b*CHANNEL_OUT + c];
            if (val < 0) {
                output[b*CHANNEL_OUT + c] = 0;
            }
            else {
                output[b*CHANNEL_OUT + c] = val;
            }
        }
    }
}

static void compute_sigmoid(float* input, float* sigmoid) {
    for (int b = 0; b < BATCH_SIZE; b++) {
#pragma HLS LOOP_TRIPCOUNT min = BATCH_SIZE max = BATCH_SIZE
        for (int c = 0; c < CHANNEL_IN; c++) {
#pragma HLS LOOP_TRIPCOUNT min = CHANNEL_IN max = CHANNEL_IN
            float tmp = input[b * CHANNEL_IN + c];
            sigmoid[b * CHANNEL_IN + c] = 1 / (1 + exp(-tmp));
        }
    }
}

static void compute_mul(float in1[BATCH_SIZE][CHANNEL_IN][IMAGE_H][IMAGE_W], float* in2,
    float* result) {
    float val = 0;
    for (int b = 0; b < BATCH_SIZE; b++) {
#pragma HLS LOOP_TRIPCOUNT min = BATCH_SIZE max = BATCH_SIZE
        for (int c = 0; c < CHANNEL_IN; c++) {
#pragma HLS LOOP_TRIPCOUNT min = CHANNEL_IN max = CHANNEL_IN
            val = in2[b * CHANNEL_IN + c];
            for (int i = 0; i < IMAGE_H; i++) {
#pragma HLS LOOP_TRIPCOUNT min = IMAGE_H max = IMAGE_H
                for (int j = 0; j < IMAGE_W; j++) {
#pragma HLS LOOP_TRIPCOUNT min = IMAGE_W max = IMAGE_W
                    result[b * CHANNEL_IN * IMAGE_H * IMAGE_W + c * IMAGE_H * IMAGE_W + i * IMAGE_W + j] = in1[b][c][i][j] * val;
                }
            }
        }
    }
}

extern "C" {
    void kernel_se(float* image, float* kernel_reduce, float* kernel_expand, float* buffer_result) {
#pragma HLS INTERFACE m_axi port = image bundle = gmem0
#pragma HLS INTERFACE m_axi port = kernel_reduce bundle = gmem1
#pragma HLS INTERFACE m_axi port = kernel_expand bundle = gmem2
#pragma HLS INTERFACE m_axi port = buffer_result bundle = gmem0


        float in[BATCH_SIZE][CHANNEL_IN][IMAGE_H][IMAGE_W];
#pragma HLS array_partition variable = in complete dim = 1
        float kernel_1[CHANNEL_OUT * KERNEL_SIZE * KERNEL_SIZE];
#pragma HLS array_partition variable = kernel_1 complete dim = 1
        float kernel_2[CHANNEL_IN * KERNEL_SIZE * KERNEL_SIZE];
#pragma HLS array_partition variable = kernel_2 complete dim = 1

        float mean[BATCH_SIZE * CHANNEL_IN];
#pragma HLS array_partition variable = mean complete dim = 1
        float tmp[BATCH_SIZE * CHANNEL_OUT];
#pragma HLS array_partition variable = tmp complete dim = 1
        float relu_x[BATCH_SIZE * CHANNEL_OUT];
#pragma HLS array_partition variable = relu_x complete dim = 1
        float sigmoid[BATCH_SIZE * CHANNEL_IN];
#pragma HLS array_partition variable = sigmoid complete dim = 1



        load_input(image, kernel_reduce, kernel_expand, in, kernel_1, CHANNEL_OUT, kernel_2, CHANNEL_IN);
        compute_mean(in, mean);
        compute_conv(mean, kernel_1, tmp, CHANNEL_IN, CHANNEL_OUT, 1, 1);
        compute_relu(tmp, relu_x);
        compute_conv(relu_x, kernel_2, tmp, CHANNEL_OUT, CHANNEL_IN, 1, 1);
        compute_sigmoid(tmp, sigmoid);
        compute_mul(in, sigmoid, buffer_result);
    }
}
