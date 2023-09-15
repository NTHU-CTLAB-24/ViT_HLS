#include <hls_stream.h>
#include <hls_math.h>
#include <stdint.h>

const int IMAGE_H = 64;
const int IMAGE_W = 64;
const int CHANNEL_IN = 3;
const int CHANNEL_OUT = 24;
const int KERNEL_SIZE = 3;
const int PADDING = 1;
const int STRIDE = 2;
const int HEIGHT_IN = IMAGE_H/2;
const int WIDTH_IN = IMAGE_W/2;
const int HEIGHT_PAD = HEIGHT_IN + 2 * PADDING;
const int WIDTH_PAD = WIDTH_IN + 2 * PADDING;
const int HEIGHT_OUT = (HEIGHT_IN - KERNEL_SIZE + 2 * PADDING) / STRIDE + 1;
const int WIDTH_OUT = (WIDTH_IN - KERNEL_SIZE + 2 * PADDING) / STRIDE + 1;

const int GROUP = 1;
const bool isConvBias = true;
const int KERNEL_CHANNEL = CHANNEL_IN / GROUP;
const int inGroupNums = CHANNEL_IN / GROUP;
const int outGroupNums = CHANNEL_OUT / GROUP;

static void tiling_image(float* image, float* tile1, float* tile2, float* tile3, float* tile4) {
    for (int i = 0; i < HEIGHT_IN; i++) {
        for (int j = 0; j < WIDTH_IN; j++) {
            for (int c = 0; c < CHANNEL_IN; c++) {
#pragma HLS UNROLL
                tile1[c * HEIGHT_IN * WIDTH_IN + i * WIDTH_IN + j] = image[c * IMAGE_H * IMAGE_W + i * IMAGE_W + j];
                tile2[c * HEIGHT_IN * WIDTH_IN + i * WIDTH_IN + j] = image[c * IMAGE_H * IMAGE_W + i * IMAGE_W + j + WIDTH_IN];
                tile3[c * HEIGHT_IN * WIDTH_IN + i * WIDTH_IN + j] = image[c * IMAGE_H * IMAGE_W + (i + HEIGHT_IN) * IMAGE_W + j];
                tile4[c * HEIGHT_IN * WIDTH_IN + i * WIDTH_IN + j] = image[c * IMAGE_H * IMAGE_W + (i + HEIGHT_IN) * IMAGE_W + j + WIDTH_IN];
            }

        }
    }
}
static void load_input(float* buffer_DataIn_1,
    float in[CHANNEL_IN][HEIGHT_IN][WIDTH_IN]
)
{
    for (int h = 0; h < HEIGHT_IN; h++) {
#pragma HLS LOOP_TRIPCOUNT min = HEIGHT_IN max = HEIGHT_IN
        for (int w = 0; w < WIDTH_IN; w++) {
#pragma HLS LOOP_TRIPCOUNT min = WIDTH_IN max = WIDTH_IN
            for (int c = 0; c < CHANNEL_IN; c++) {
#pragma HLS UNROLL
                in[c][h][w] = buffer_DataIn_1[c * HEIGHT_IN * WIDTH_IN + h * WIDTH_IN + w];
            }
        }
    }
}
static void init_norm(float mean[CHANNEL_OUT], float var[CHANNEL_OUT],
    float gamma[CHANNEL_OUT], float beta[CHANNEL_OUT])
{
    for (int c = 0; c < CHANNEL_OUT; c++) {
#pragma HLS UNROLL
        mean[c] = 8;
        var[c] = 21.5;
        gamma[c] = 0.5;
        beta[c] = 0.2;
    }
}
static void init_kernel(float kernel[CHANNEL_OUT][CHANNEL_IN][KERNEL_SIZE][KERNEL_SIZE],
    float bias[CHANNEL_OUT]) {
    for (int k = 0; k < CHANNEL_OUT; k++) {
#pragma HLS UNROLL
        bias[k] = k + 0.01;
    }

    for (int k = 0; k < CHANNEL_OUT; k++) {
#pragma HLS LOOP_TRIPCOUNT min = CHANNEL_OUT max = CHANNEL_OUT
        for (int l = 0; l < KERNEL_CHANNEL; l++) {
#pragma HLS LOOP_TRIPCOUNT min = KERNEL_CHANNEL max = KERNEL_CHANNEL
            for (int i = 0; i < KERNEL_SIZE; i++) {
#pragma HLS UNROLL
                for (int j = 0; j < KERNEL_SIZE; j++) {
#pragma HLS UNROLL            
                    kernel[k][l][i][j] = 0.1;
                }
            }
        }
    }
}
static void image_padding(float image[CHANNEL_IN][HEIGHT_IN][WIDTH_IN],
    float pad[CHANNEL_IN][HEIGHT_PAD][WIDTH_PAD])
{

    for (int i = 0; i < HEIGHT_PAD; i++) {
#pragma HLS LOOP_TRIPCOUNT min = HEIGHT_PAD max = HEIGHT_PAD
        for (int j = 0; j < WIDTH_PAD; j++) {
#pragma HLS LOOP_TRIPCOUNT min = WIDTH_PAD max = WIDTH_PAD
            for (int c = 0; c < CHANNEL_IN; c++) {
#pragma HLS UNROLL
                if (i < PADDING || i >= (HEIGHT_IN + PADDING) || j < PADDING || j >= (WIDTH_IN + PADDING)) {
                    pad[c][i][j] = 0;
                }
                else {
                    pad[c][i][j] = image[c][i - PADDING][j - PADDING];
                }
            }
        }
    }
}
static void compute_conv(float in[CHANNEL_IN][HEIGHT_PAD][WIDTH_PAD],
    float kernel[CHANNEL_OUT][CHANNEL_IN][KERNEL_SIZE][KERNEL_SIZE],
    float bias[CHANNEL_OUT],
    float out[CHANNEL_OUT][HEIGHT_OUT][WIDTH_OUT])
{
    for (int i = 0; i < HEIGHT_OUT; i++) {
#pragma HLS LOOP_TRIPCOUNT min = HEIGHT_OUT max = HEIGHT_OUT
        for (int j = 0; j < WIDTH_OUT; j++) {
#pragma HLS LOOP_TRIPCOUNT min = WIDTH_OUT max = WIDTH_OUT
            for (int c = 0; c < CHANNEL_OUT; c++) {
#pragma HLS UNROLL
                if (isConvBias) out[c][i][j] = bias[c];
                else out[c][i][j] = 0;
            }
        }
    }

    for (int h = 0; h < HEIGHT_OUT; h++) {
#pragma HLS LOOP_TRIPCOUNT min = HEIGHT_OUT max = HEIGHT_OUT
        for (int w = 0; w < WIDTH_OUT; w++) {
#pragma HLS LOOP_TRIPCOUNT min = WIDTH_OUT max = WIDTH_OUT         
            for (int kr = 0; kr < KERNEL_SIZE; kr++) {
#pragma HLS PIPELINE
#pragma HLS LOOP_TRIPCOUNT min = KERNEL_SIZE max = KERNEL_SIZE
                for (int kc = 0; kc < KERNEL_SIZE; kc++) {
#pragma HLS LOOP_TRIPCOUNT min = KERNEL_SIZE max = KERNEL_SIZE
                    for (int cho = 0; cho < CHANNEL_OUT; cho++) {
#pragma HLS UNROLL  
                        for (int chi = 0; chi < CHANNEL_IN; chi++) {
#pragma HLS UNROLL
                            out[cho][h][w] += in[chi][h * STRIDE + kr][w * STRIDE + kc] * kernel[cho][chi][kr][kc];
                        }
                    }
                }
            }
        }
    }
}
static void compute_batchnorm(float in[CHANNEL_OUT][HEIGHT_OUT][WIDTH_OUT],
    float* out,
    float* mean, float* var, float* gamma, float* beta) {

    for (int i = 0; i < HEIGHT_OUT; i++) {
#pragma HLS LOOP_TRIPCOUNT min = HEIGHT_OUT max = HEIGHT_OUT
        for (int j = 0; j < WIDTH_OUT; j++) {
#pragma HLS LOOP_TRIPCOUNT min = WIDTH_OUT max = WIDTH_OUT
            for (int c = 0; c < CHANNEL_OUT; c++) {
#pragma HLS UNROLL
                out[c * HEIGHT_OUT * WIDTH_OUT + i * WIDTH_OUT + j] = ((in[c][i][j] - mean[c]) / (sqrt(var[c]) + 1e-5)) * gamma[c] + beta[c];
            }

        }
    }
}
static void kernel_mspatch(float* in1, float* buffer_result) {
    float image[CHANNEL_IN][HEIGHT_IN][WIDTH_IN];
    float kernel[CHANNEL_OUT][KERNEL_CHANNEL][KERNEL_SIZE][KERNEL_SIZE];
    float bias[CHANNEL_OUT];

    float mean[CHANNEL_OUT];
    float var[CHANNEL_OUT];
    float gamma[CHANNEL_OUT];
    float beta[CHANNEL_OUT];

    float image_pad[CHANNEL_IN][HEIGHT_PAD][WIDTH_PAD];
    float conv_result[CHANNEL_OUT][HEIGHT_OUT][WIDTH_OUT];
#pragma HLS dataflow
    load_input(in1, image);
    init_norm(mean, var, gamma, beta);
    init_kernel(kernel, bias);
    image_padding(image, image_pad);
    compute_conv(image_pad, kernel, bias, conv_result);
    compute_batchnorm(conv_result, buffer_result, mean, var, gamma, beta);
}
static void combine(float* out1, float* out2, float* out3, float* out4, float* result) {

    for (int i = 0; i < HEIGHT_OUT; i++) {
        for (int j = 0; j < WIDTH_OUT; j++) {
            for (int c = 0; c < CHANNEL_OUT; c++) {
#pragma HLS UNROLL
                result[c * HEIGHT_OUT * WIDTH_OUT * 4 + i * WIDTH_OUT * 2 + j] = out1[c * HEIGHT_OUT * WIDTH_OUT + i * WIDTH_OUT + j];
                result[c * HEIGHT_OUT * WIDTH_OUT * 4 + i * WIDTH_OUT * 2 + j + WIDTH_OUT] = out2[c * HEIGHT_OUT * WIDTH_OUT + i * WIDTH_OUT + j];
                result[c * HEIGHT_OUT * WIDTH_OUT * 4 + (i + HEIGHT_OUT) * WIDTH_OUT * 2 + j] = out3[c * HEIGHT_OUT * WIDTH_OUT + i * WIDTH_OUT + j];
                result[c * HEIGHT_OUT * WIDTH_OUT * 4 + (i + HEIGHT_OUT) * WIDTH_OUT * 2 + j + WIDTH_OUT] = out4[c * HEIGHT_OUT * WIDTH_OUT + i * WIDTH_OUT + j];
            }

        }
    }
}

extern "C" {
    void k_msp(float* in1, float* result) {
#pragma HLS INTERFACE m_axi port = in1 bundle = gmem0 depth = 12288
#pragma HLS INTERFACE m_axi port = result bundle = gmem0 depth = 24576

        
        float tile1[CHANNEL_IN * HEIGHT_IN * WIDTH_IN];
        float tile2[CHANNEL_IN * HEIGHT_IN * WIDTH_IN];
        float tile3[CHANNEL_IN * HEIGHT_IN * WIDTH_IN];
        float tile4[CHANNEL_IN * HEIGHT_IN * WIDTH_IN];

        float out1[CHANNEL_OUT * HEIGHT_OUT * WIDTH_OUT];
        float out2[CHANNEL_OUT * HEIGHT_OUT * WIDTH_OUT];
        float out3[CHANNEL_OUT * HEIGHT_OUT * WIDTH_OUT];
        float out4[CHANNEL_OUT * HEIGHT_OUT * WIDTH_OUT];
        

#pragma HLS dataflow
        tiling_image(in1, tile1, tile2, tile3, tile4);
        kernel_mspatch(tile1, out1);
        kernel_mspatch(tile2, out2);
        kernel_mspatch(tile3, out3);
        kernel_mspatch(tile4, out4);
        combine(out1, out2, out3, out4, result);
    }
}