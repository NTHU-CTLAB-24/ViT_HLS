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

static void load_input(float* data, float* kernel,
    float* store_in, float* store_kernel) {
input_data:
    for (int n = 0; n < BATCH_SIZE; n++) {
#pragma HLS LOOP_TRIPCOUNT min = BATCH_SIZE max = BATCH_SIZE
        for (int c = 0; c < CHANNEL_IN; c++) {
#pragma HLS LOOP_TRIPCOUNT min = CHANNEL_IN max = CHANNEL_IN
            for (int h = 0; h < HEIGHT_IN; h++) {
#pragma HLS LOOP_TRIPCOUNT min = HEIGHT_IN max = HEIGHT_IN
                for (int w = 0; w < WIDTH_IN; w++) {
#pragma HLS LOOP_TRIPCOUNT min = WIDTH_IN max = WIDTH_IN
                    int pos = n * CHANNEL_IN * HEIGHT_IN * WIDTH_IN + c * HEIGHT_IN * WIDTH_IN + h * WIDTH_IN + w;
                    store_in[pos] = data[pos];
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
                store_kernel[k * KERNEL_SIZE * KERNEL_SIZE + i * KERNEL_SIZE + j] = kernel[k * KERNEL_SIZE * KERNEL_SIZE + i * KERNEL_SIZE + j];
            }
        }
    }
}

static void compute_conv(float* in, float* kernel, float* in_pad, float* buffer_result, int cin, int cout, int height, int width, int kernel_size = 1, int stride = 1, int padding = 0) {
    int height_pad, width_pad;
    if (padding > 0) {
        height_pad = height + 2*padding;
        width_pad = width + 2*padding;
        for (int b = 0; b < BATCH_SIZE; b++) {
#pragma HLS LOOP_TRIPCOUNT min = BATCH_SIZE max = BATCH_SIZE
            for (int c = 0; c < cin; c++) {
#pragma HLS LOOP_TRIPCOUNT min = cin max = cin
                for (int i = 0; i < height_pad; i++) {
#pragma HLS LOOP_TRIPCOUNT min = height_pad max = height_pad
                    for (int j = 0; j < width_pad; j++) {
#pragma HLS LOOP_TRIPCOUNT min = width_pad max = width_pad
                        int pos = b * cin * height_pad * width_pad + c * height_pad * width_pad + i * width_pad + j;
                        if (i < padding || i >= height + padding || j < padding ||
                            j >= width + padding)
                            in_pad[pos] = 0;
                        else
                            in_pad[pos] = in[b * cin * height * width + c * height * width + (i - padding) * width + j - padding];
                    }
                }
            }
        }
    }

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
                                int pos_pad = batch * cin * height_pad *width_pad + in_ch * height_pad * width_pad + (row * stride + kernel_row) * width_pad + (col * stride + kernel_col);
                                int pos_kernel = out_ch * kernel_size * kernel_size + kernel_row * kernel_size + kernel_col;
                                if (padding == 0) sum += in[pos] * kernel[pos_kernel];
                                else sum += in_pad[pos_pad] + kernel[pos_kernel];
                            }
                        }
                    }
                    buffer_result[batch * cout * height_out * width_out + out_ch * height_out * width_out + row * width_out + col] = sum;
                }
            }
        }
    }
}

static void compute_batchnorm(float* in, float* out, float* mean, float* var) {
    float sum, sum2;
    float val;
    int pos;
    for (int c = 0; c < CHANNEL_OUT; c++) {
#pragma HLS LOOP_TRIPCOUNT min = CHANNEL_OUT max = CHANNEL_OUT
        sum = 0;
        sum2 = 0;
        for (int b = 0; b < BATCH_SIZE; b++) {
#pragma HLS LOOP_TRIPCOUNT min = BATCH_SIZE max = BATCH_SIZE
            for (int i = 0; i < HEIGHT_OUT; i++) {
#pragma HLS LOOP_TRIPCOUNT min = HEIGHT_OUT max = HEIGHT_OUT
                for (int j = 0; j < WIDTH_OUT; j++) {
#pragma HLS LOOP_TRIPCOUNT min = WIDTH_OUT max = WIDTH_OUT
                    val = in[b * HEIGHT_OUT * CHANNEL_OUT * HEIGHT_OUT * WIDTH_OUT + c * HEIGHT_OUT * WIDTH_OUT + i * WIDTH_OUT + j];
                    sum += val;
                    sum2 += val * val;
                }
            }
        }
        float avg = sum / (BATCH_SIZE * HEIGHT_OUT * WIDTH_OUT);
        float avg2 = sum2 / (BATCH_SIZE * HEIGHT_OUT * WIDTH_OUT);
        mean[c] = avg;
        var[c] = avg2 - avg * avg; //var(x) = E[x^2] - E[x]^2 
    }

    for (int b = 0; b < BATCH_SIZE; b++) {
#pragma HLS LOOP_TRIPCOUNT min = BATCH_SIZE max = BATCH_SIZE
        for (int c = 0; c < CHANNEL_OUT; c++) {
#pragma HLS LOOP_TRIPCOUNT min = CHANNEL_OUT max = CHANNEL_OUT
            for (int i = 0; i < HEIGHT_OUT; i++) {
#pragma HLS LOOP_TRIPCOUNT min = HEIGHT_OUT max = HEIGHT_OUT
                for (int j = 0; j < WIDTH_OUT; j++) {
#pragma HLS LOOP_TRIPCOUNT min = WIDTH_OUT max = WIDTH_OUT
                    pos = b * CHANNEL_OUT * HEIGHT_OUT * WIDTH_OUT + c * HEIGHT_OUT * WIDTH_OUT + i * WIDTH_OUT + j;
                    out[pos] = (in[pos] - mean[c]) / sqrt(var[c] + 1e-5);
                }
            }
        }
    }


}

extern "C" {
    void kernel_mspatch(float* in1, float* in2, float* buffer_result) {
#pragma HLS INTERFACE m_axi port = in1 bundle = gmem0
#pragma HLS INTERFACE m_axi port = in2 bundle = gmem1
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

        load_input(in1, in2, image, kernel);
        compute_conv(image, kernel, in_pad, conv_result, CHANNEL_IN, CHANNEL_OUT, HEIGHT_IN, WIDTH_IN, 3, 2, 1);
        compute_batchnorm(conv_result, buffer_result, mean, var);
    }
}
