// Includes
#include <hls_math.h>
#include <hls_stream.h>
#include <stdint.h>

/* Remember to modify test file */

// TODO: modify size
// TRIPCOUNT identifie
const int BATCH_SIZE = 2;
const int CHANNEL_IN = 24;
const int CHANNEL_OUT = 24;
const int HEIGHT_IN = 4;
const int WIDTH_IN = 4;

// TODO: modify conv parameters
// Convolution parameters
const int KERNEL_SIZE = 3;
const int STRIDE = 1;
const int GROUP = 24;

// Padding and size
const int PADDING = (KERNEL_SIZE - STRIDE) % 2 == 0 ? (KERNEL_SIZE - STRIDE) / 2 : (KERNEL_SIZE - STRIDE) / 2 + 1;
const int HEIGHT_PAD = HEIGHT_IN + 2 * PADDING;
const int WIDTH_PAD = WIDTH_IN + 2 * PADDING;
const int HEIGHT_OUT = (HEIGHT_IN - KERNEL_SIZE + 2 * PADDING) / STRIDE + 1;
const int WIDTH_OUT = (WIDTH_IN - KERNEL_SIZE + 2 * PADDING) / STRIDE + 1;

// For Convolution
const int KERNEL_CHANNEL = CHANNEL_IN / GROUP;
const int inGroupNums = CHANNEL_IN / GROUP;
const int outGroupNums = CHANNEL_OUT / GROUP;
const bool isConvBias = false;

// Normalization parameters
const float EPS = 1e-5;

// TODO: modify hyperparameters
// Hyperparameters
const int NORM_LAYER = 0; // 0:batch_norm, 1: layer_norm
const int ACT_LAYER = 1;  // 0: relu, 1: silu, 2:gelu

// Coding Style: function宣告要為static，遇到for迴圈前可以取error_type的名稱(ex: mem_rd)
static void load_input(float *buffer_DataIn_1,
                       float in[BATCH_SIZE][CHANNEL_IN][HEIGHT_IN][WIDTH_IN])
{
init_in:
    for (int h = 0; h < HEIGHT_IN; h++){
#pragma HLS LOOP_TRIPCOUNT min = HEIGHT_IN max = HEIGHT_IN
        for (int w = 0; w < WIDTH_IN; w++){
#pragma HLS LOOP_TRIPCOUNT min = WIDTH_IN max = WIDTH_IN
            for (int n = 0; n < BATCH_SIZE; n++) {
#pragma HLS LOOP_TRIPCOUNT min = BATCH_SIZE max = BATCH_SIZE
                for (int c = 0; c < CHANNEL_IN; c++) {
#pragma HLS UNROLL
                    in[n][c][h][w] = buffer_DataIn_1[n * CHANNEL_IN * HEIGHT_IN * WIDTH_IN + c * HEIGHT_IN * WIDTH_IN + h * WIDTH_IN + w];
                }
            }
        }
    }
}

static void compute_padding(float in[BATCH_SIZE][CHANNEL_IN][HEIGHT_IN][WIDTH_IN],
                            float in_pad[BATCH_SIZE][CHANNEL_IN][HEIGHT_PAD][WIDTH_PAD])
{
Padding:
for (int n = 0; n < BATCH_SIZE; n++){
#pragma HLS LOOP_TRIPCOUNT min = BATCH_SIZE max = BATCH_SIZE
        for (int i = 0; i < HEIGHT_PAD; i++){
#pragma HLS LOOP_TRIPCOUNT min = HEIGHT_PAD max = HEIGHT_PAD
            for (int j = 0; j < WIDTH_PAD; j++){
#pragma HLS LOOP_TRIPCOUNT min = WIDTH_PAD max = WIDTH_PAD
                for (int c = 0; c < CHANNEL_IN; c++){
#pragma HLS UNROLL
                    if (i < PADDING || i >= (HEIGHT_IN + PADDING) || j < PADDING || j >= (WIDTH_IN + PADDING))
                        in_pad[n][c][i][j] = 0;
                    else
                        in_pad[n][c][i][j] = in[n][c][i - PADDING][j - PADDING];
                }
            }
        }
    }
}

static void compute_conv(float in_pad[BATCH_SIZE][CHANNEL_IN][HEIGHT_PAD][WIDTH_PAD],
                         float afterConv[BATCH_SIZE][CHANNEL_OUT][HEIGHT_OUT][WIDTH_OUT])
{
    float kernel[CHANNEL_OUT][KERNEL_CHANNEL][KERNEL_SIZE][KERNEL_SIZE];
#pragma HLS array_partition variable = kernel complete dim = 1
    float bias[CHANNEL_OUT];
#pragma HLS array_partition variable = bias complete dim = 1

init_bias:
    for (int k = 0; k < CHANNEL_OUT; k++) {
#pragma HLS UNROLL  
        bias[k] = k + 10;
    }
init_kernel:
    for (int k = 0; k < CHANNEL_OUT; k++) {
#pragma HLS LOOP_TRIPCOUNT min = CHANNEL_OUT max = CHANNEL_OUT
        for (int l = 0; l < KERNEL_CHANNEL; l++) {
#pragma HLS LOOP_TRIPCOUNT min = KERNEL_CHANNEL max = KERNEL_CHANNEL
            for (int i = 0; i < KERNEL_SIZE; i++) {
#pragma HLS UNROLL
                for (int j = 0; j < KERNEL_SIZE; j++) {
#pragma HLS UNROLL
                    kernel[k][l][i][j] = j + k;
                }
            }
        }
    }

init_output:
    for (int n = 0; n < BATCH_SIZE; n++){
#pragma HLS LOOP_TRIPCOUNT min = BATCH_SIZE max = BATCH_SIZE
        for (int i = 0; i < HEIGHT_OUT; i++){
#pragma HLS LOOP_TRIPCOUNT min = HEIGHT_OUT max = HEIGHT_OUT
            for (int j = 0; j < WIDTH_OUT; j++){
#pragma HLS LOOP_TRIPCOUNT min = WIDTH_OUT max = WIDTH_OUT
                for (int c = 0; c < CHANNEL_OUT; c++){
#pragma HLS UNROLL
                    afterConv[n][c][i][j] = 0;
                    if (isConvBias)
                        afterConv[n][c][i][j] = bias[c];
                }
            }
        }
    }
execute:
Batch:
    for (int batch = 0; batch < BATCH_SIZE; batch++) {
#pragma HLS LOOP_TRIPCOUNT min = BATCH_SIZE max = BATCH_SIZE
    Out_Row:
        for (int row = 0; row < HEIGHT_OUT; row++) {
#pragma HLS LOOP_TRIPCOUNT min = HEIGHT_OUT max = HEIGHT_OUT
        Out_Column:
            for (int col = 0; col < WIDTH_OUT; col++) {
#pragma HLS LOOP_TRIPCOUNT min = WIDTH_OUT max = WIDTH_OUT
            Kernel_Row:
                for (int kernel_row = 0; kernel_row < KERNEL_SIZE; kernel_row++) {
#pragma HLS LOOP_TRIPCOUNT min = KERNEL_SIZE max = KERNEL_SIZE
                Kernel_Col:
                    for (int kernel_col = 0; kernel_col < KERNEL_SIZE; kernel_col++) {
#pragma HLS LOOP_TRIPCOUNT min = KERNEL_SIZE max = KERNEL_SIZE
                        int groupIndex = 0;
                    Output_Channel:
                        for (int out_ch = 0; out_ch < CHANNEL_OUT; out_ch++) {
#pragma HLS UNROLL
                            int kernelChannelIdx = 0;
                        In_Channel:
                            for (int in_ch = groupIndex * inGroupNums; in_ch < CHANNEL_IN; in_ch++) {
#pragma HLS UNROLL
                                afterConv[batch][out_ch][row][col] += in_pad[batch][in_ch][row * STRIDE + kernel_row][col * STRIDE + kernel_col] * kernel[out_ch][kernelChannelIdx][kernel_row][kernel_col];
                                kernelChannelIdx++;
                                if ((in_ch + 1) % inGroupNums == 0)
                                    break;
                            }
                            if ((out_ch + 1) % outGroupNums == 0)
                                groupIndex++;
                        }
                    }
                }
            }
        }
    }
}

static void compute_norm(float afterConv[BATCH_SIZE][CHANNEL_OUT][HEIGHT_OUT][WIDTH_OUT],
                         float afterNorm[BATCH_SIZE][CHANNEL_OUT][HEIGHT_OUT][WIDTH_OUT])
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
        for (int c = 0; c < CHANNEL_OUT; c++){
#pragma HLS UNROLL
            RUNNING_MEAN[c] = 8;
            RUNNING_VAR[c] = 21.5;
            weight[c] = 0.5;
            bias[c] = 0.2;
        }

init_output:
    for (int n = 0; n < BATCH_SIZE; n++){
#pragma HLS LOOP_TRIPCOUNT min = BATCH_SIZE max = BATCH_SIZE
        for (int i = 0; i < HEIGHT_OUT; i++){
#pragma HLS LOOP_TRIPCOUNT min = HEIGHT_OUT max = HEIGHT_OUT
            for (int j = 0; j < WIDTH_OUT; j++){
#pragma HLS LOOP_TRIPCOUNT min = WIDTH_OUT max = WIDTH_OUT
                for (int c = 0; c < CHANNEL_OUT; c++){
#pragma HLS UNROLL
                    afterNorm[n][c][i][j] = 0;
                }
            }
        }
    }
    Batch_norm:
         for (int n = 0; n < BATCH_SIZE; n++) {
#pragma HLS LOOP_TRIPCOUNT min = BATCH_SIZE max = BATCH_SIZE
        for (int i = 0; i < HEIGHT_OUT; i++) {
#pragma HLS LOOP_TRIPCOUNT min = HEIGHT_OUT max = HEIGHT_OUT
            for (int j = 0; j < WIDTH_OUT; j++) {
#pragma HLS LOOP_TRIPCOUNT min = WIDTH_OUT max = WIDTH_OUT
                for (int c = 0; c < CHANNEL_OUT; c++) {
#pragma HLS UNROLL
                    afterNorm[n][c][i][j] = (afterConv[n][c][i][j] - RUNNING_MEAN[c]) / sqrt(RUNNING_VAR[c] + EPS) * weight[c] + bias[c];
                }
            }
        }
    }
}

static void compute_act(float afterNorm[BATCH_SIZE][CHANNEL_OUT][HEIGHT_OUT][WIDTH_OUT],
                        float* buffer_result)
{
    //to avoid use "exp", we replace "silu" with "relu" function
    relu:
    for (int n = 0; n < BATCH_SIZE; n++) {
#pragma HLS LOOP_TRIPCOUNT min = BATCH_SIZE max = BATCH_SIZE
        for (int h = 0; h < HEIGHT_OUT; h++) {
#pragma HLS LOOP_TRIPCOUNT min = HEIGHT_OUT max = HEIGHT_OUT
            for (int w = 0; w < WIDTH_OUT; w++) {
#pragma HLS LOOP_TRIPCOUNT min = WIDTH_OUT max = WIDTH_OUT
                for (int c = 0; c < CHANNEL_OUT; c++) {
#pragma HLS UNROLL
                    if (afterNorm[n][c][h][w] < 0)                      
                        buffer_result[n * CHANNEL_OUT * HEIGHT_OUT * WIDTH_OUT + c * HEIGHT_OUT * WIDTH_OUT + h * WIDTH_OUT + w] = 0;
                    else 
                        buffer_result[n * CHANNEL_OUT * HEIGHT_OUT * WIDTH_OUT + c * HEIGHT_OUT * WIDTH_OUT + h * WIDTH_OUT + w] = afterNorm[n][c][h][w];
                }
            }        
        }
    }
}

extern "C"
{
    void kernel_DW_conv(float *buffer_DataIn_1,
                        float *buffer_result)
    {
// TODO: modify depth
#pragma HLS INTERFACE m_axi port = buffer_DataIn_1 bundle = gmem0 depth = 768
#pragma HLS INTERFACE m_axi port = buffer_result bundle = gmem0 depth = 768

#pragma HLS dataflow
        // dataflow僅可以接受single reader and single writer
        // dataflow pragma instruct compiler to run following three APIs in parallel
        float in[BATCH_SIZE][CHANNEL_IN][HEIGHT_IN][WIDTH_IN];
#pragma HLS array_partition variable = in complete dim = 1
        float in_pad[BATCH_SIZE][CHANNEL_IN][HEIGHT_PAD][WIDTH_PAD];
#pragma HLS array_partition variable = in_pad complete dim = 1
        float afterConv[BATCH_SIZE][CHANNEL_OUT][HEIGHT_OUT][WIDTH_OUT];
#pragma HLS array_partition variable = afterConv complete dim = 1
        float afterNorm[BATCH_SIZE][CHANNEL_OUT][HEIGHT_OUT][WIDTH_OUT];
#pragma HLS array_partition variable = afterNorm complete dim = 1
        load_input(buffer_DataIn_1, in);
        compute_padding(in, in_pad);
        compute_conv(in_pad, afterConv);
        compute_norm(afterConv, afterNorm);
        compute_act(afterNorm, buffer_result);
    }
}
