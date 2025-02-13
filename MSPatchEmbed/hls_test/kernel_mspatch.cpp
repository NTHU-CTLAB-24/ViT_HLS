// Includes
#include <hls_stream.h>
#include <hls_math.h>
#include <stdint.h>
// TRIPCOUNT identifier
// const int BATCH_SIZE = 1; 
const int HEIGHT_IN = 24;
const int WIDTH_IN = 24;
const int CHANNEL_IN = 3;
const int CHANNEL_OUT = 24;
const int KERNEL_SIZE = 3;
const int PADDING = 1;
const int STRIDE = 2;
const int GROUP = 1;
const bool isConvBias = true;
const int HEIGHT_OUT = (HEIGHT_IN - KERNEL_SIZE + 2 * PADDING) / STRIDE + 1;
const int WIDTH_OUT = (WIDTH_IN - KERNEL_SIZE + 2 * PADDING) / STRIDE + 1;
const int KERNEL_CHANNEL = CHANNEL_IN / GROUP;
const int inGroupNums = CHANNEL_IN / GROUP;
const int outGroupNums = CHANNEL_OUT / GROUP;
const int HEIGHT_PAD = HEIGHT_IN + 2*PADDING;
const int WIDTH_PAD = WIDTH_IN + 2*PADDING;

static void load_input(float *buffer_DataIn_1, 
                       float in[CHANNEL_IN][HEIGHT_IN][WIDTH_IN]
                        )
{
init_in:
    for (int h=0; h<HEIGHT_IN; h++) {
#pragma HLS LOOP_TRIPCOUNT min = HEIGHT_IN max = HEIGHT_IN
        for (int w=0; w<WIDTH_IN; w++) {
    #pragma HLS LOOP_TRIPCOUNT min = WIDTH_IN max = WIDTH_IN
            for (int c=0; c<CHANNEL_IN; c++) {
                #pragma HLS UNROLL
                 in[c][h][w] = buffer_DataIn_1[c * HEIGHT_IN * WIDTH_IN + h * WIDTH_IN + w];
            }
        }
    }
    
}

static void load_norm(float* buffer, float mean[CHANNEL_OUT], float var[CHANNEL_OUT],
                        float gamma[CHANNEL_OUT], float beta[CHANNEL_OUT]) 
{
    for (int c=0; c<CHANNEL_OUT; c++) {
#pragma HLS UNROLL
        mean[c] = buffer[c];
        var[c] = buffer[c+CHANNEL_OUT];
        gamma[c] = buffer[c+2*CHANNEL_OUT];
        beta[c] = buffer[c+3*CHANNEL_OUT];
    }               
                    
}

static void padding_input(float in[CHANNEL_IN][HEIGHT_IN][WIDTH_IN], 
                        float image_pad[CHANNEL_IN][HEIGHT_PAD][WIDTH_PAD]) 
{   
    for (int i=0; i<HEIGHT_PAD; i++) {
#pragma HLS LOOP_TRIPCOUNT min = HEIGHT_PAD max = HEIGHT_PAD
        for (int j=0; j<WIDTH_PAD; j++) {
    #pragma HLS LOOP_TRIPCOUNT min = WIDTH_PAD max = WIDTH_PAD
            for (int c=0; c<CHANNEL_IN; c++) {
                #pragma HLS UNROLL
                if (i < PADDING || i >= (HEIGHT_IN + PADDING) || j < PADDING || j >= (WIDTH_IN + PADDING))
                    image_pad[c][i][j] = 0;
                else
                    image_pad[c][i][j] = in[c][i - PADDING][j - PADDING];
            }
        }
    }
}
                        


static void compute_conv(float in[CHANNEL_IN][HEIGHT_PAD][WIDTH_PAD],
                         float out[CHANNEL_OUT][HEIGHT_OUT][WIDTH_OUT])
{
    // The kernel is operating with vector of NUM_WORDS integers. The + operator performs
    // an element-wise add, resulting in NUM_WORDS parallel additions.

    float kernel[CHANNEL_OUT][KERNEL_CHANNEL][KERNEL_SIZE][KERNEL_SIZE];
#pragma HLS array_partition variable = kernel complete dim = 1
    float bias[CHANNEL_OUT];
#pragma HLS array_partition variable = bias complete dim = 1


init_kernel:
    for (int k = 0; k < CHANNEL_OUT; k++){
#pragma HLS LOOP_TRIPCOUNT min = CHANNEL_OUT max = CHANNEL_OUT
        bias[k] = k + 0.01;
        for (int l = 0; l < KERNEL_CHANNEL; l++){
#pragma HLS LOOP_TRIPCOUNT min = KERNEL_CHANNEL max = KERNEL_CHANNEL
            for (int i = 0; i < KERNEL_SIZE; i++){
#pragma HLS UNROLL
                for (int j = 0; j < KERNEL_SIZE; j++){
#pragma HLS UNROLL
                    kernel[k][l][i][j] = 0.1;
                }
            }
        }
    }
init_out: 
    for (int i=0; i<HEIGHT_OUT; i++) {
#pragma HLS LOOP_TRIPCOUNT min = HEIGHT_OUT max = HEIGHT_OUT
        for (int j=0; j<WIDTH_OUT; j++) {
#pragma HLS LOOP_TRIPCOUNT min = WIDTH_OUT max = WIDTH_OUT
            for (int c=0; c<CHANNEL_OUT; c++) {
#pragma HLS UNROLL
                out[c][i][j] = 0;
                if (isConvBias) out[c][i][j] = bias[c];
            } 
        }
    }

conv:
    row:
    for (int h=0; h<HEIGHT_OUT; h++) {
        column:
        for (int w=0; w<WIDTH_OUT; w++) {
            kernel_row:
            for (int kr=0; kr<KERNEL_SIZE; kr++) {
                kernel_column:
                for (int kc=0; kc<KERNEL_SIZE; kc++) {
                    output_channel:
                    for (int cho=0; cho<CHANNEL_OUT; cho++) {
                        #pragma HLS UNROLL  
                        input_channel:
                        for (int chi=0; chi<CHANNEL_IN; chi++) {
                            #pragma HLS UNROLL
                            out[cho][h][w] += in[chi][h*STRIDE+kr][w*STRIDE+kc] * kernel[cho][chi][kr][kc];
                        }
                    }
                }
            }
        }
    }
}


static void compute_batchnorm(float in[CHANNEL_OUT][HEIGHT_OUT][WIDTH_OUT], 
                                float* out, float* mean, float* var, float* gamma, float* beta) {

    for (int i = 0; i < HEIGHT_OUT; i++) {
#pragma HLS LOOP_TRIPCOUNT min = HEIGHT_OUT max = HEIGHT_OUT
        for (int j = 0; j < WIDTH_OUT; j++) {
#pragma HLS LOOP_TRIPCOUNT min = WIDTH_OUT max = WIDTH_OUT
            for (int c=0; c<CHANNEL_OUT; c++) {
                #pragma HLS UNROLL
                out[c * HEIGHT_OUT * WIDTH_OUT + i * WIDTH_OUT + j] = (in[c][i][j] - mean[c]) / sqrt(var[c] + 1e-5) * gamma[c] + beta[c];
            }
                    
        }
    }
}

extern "C" {
    void kernel_mspatch(float* in1, float* in2, float* buffer_result) {
#pragma HLS INTERFACE m_axi port = in1 bundle = gmem0 depth = 1728
#pragma HLS INTERFACE m_axi port = in2 bundle = gmem1 depth = 96
#pragma HLS INTERFACE m_axi port = buffer_result bundle = gmem0 depth = 3456

#pragma HLS dataflow
        float image[CHANNEL_IN][HEIGHT_IN][WIDTH_IN];
#pragma HLS array_partition variable = image complete dim = 1
        float in_pad[CHANNEL_IN][HEIGHT_PAD][WIDTH_PAD];
#pragma HLS array_partition variable = in_pad complete dim = 1
        float conv_result[CHANNEL_OUT][HEIGHT_OUT][WIDTH_OUT];
#pragma HLS array_partition variable = conv_result complete dim = 1

        float mean[CHANNEL_OUT];
        float var[CHANNEL_OUT];
        float gamma[CHANNEL_OUT];
        float beta[CHANNEL_OUT];

        load_input(in1, image);
        load_norm(in2, mean, var, gamma, beta);
        padding_input(image, in_pad);
        compute_conv(in_pad, conv_result);
        compute_batchnorm(conv_result, buffer_result, mean, var, gamma, beta);
    }
}