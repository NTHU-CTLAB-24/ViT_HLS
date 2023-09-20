// Includes
#include <hls_math.h>
#include <hls_stream.h>
#include <stdint.h>

/* Remember to modify test file */

// TODO: modify size
// TRIPCOUNT identifie
const int BATCH_SIZE = 1;
const int CHANNEL_IN = 24;
const int CHANNEL_OUT = 24;
const int HEIGHT_IN = 28;
const int WIDTH_IN = 28;

// TODO: modify conv parameters
// Convolution parameters
const int KERNEL_SIZE = 1;
const int STRIDE = 1;
const int GROUP = 1;

// Padding and size
const int PADDING = 0;
const int HEIGHT_OUT = (HEIGHT_IN - KERNEL_SIZE + 2 * PADDING) / STRIDE + 1;
const int WIDTH_OUT = (WIDTH_IN - KERNEL_SIZE + 2 * PADDING) / STRIDE + 1;

// For Convolution
const int KERNEL_CHANNEL = CHANNEL_IN / GROUP;
const int inGroupNums = CHANNEL_IN / GROUP;
const int outGroupNums = CHANNEL_OUT / GROUP;
const bool isConvBias = false;

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
#pragma HLS LOOP_TRIPCOUNT min = CHANNEL_IN max = CHANNEL_IN
                    in[n][c][h][w] = buffer_DataIn_1[n * CHANNEL_IN * HEIGHT_IN * WIDTH_IN + c * HEIGHT_IN * WIDTH_IN + h * WIDTH_IN + w];
                }
            }
        }
    }
}

static void compute_conv(float in[BATCH_SIZE][CHANNEL_IN][HEIGHT_IN][WIDTH_IN],
                         float out[BATCH_SIZE][CHANNEL_OUT][HEIGHT_OUT][WIDTH_OUT])
{
    float kernel[CHANNEL_OUT][KERNEL_CHANNEL];
#pragma HLS bind_storage variable=kernel type=RAM_1P impl=uram
    float bias[CHANNEL_OUT];
#pragma HLS bind_storage variable=bias type=RAM_1P impl=uram

init_out:
    for (int i = 0; i < HEIGHT_OUT; i++) {
#pragma HLS LOOP_TRIPCOUNT min = HEIGHT_OUT max = HEIGHT_OUT
        for (int j = 0; j < WIDTH_OUT; j++) {
#pragma HLS LOOP_TRIPCOUNT min = WIDTH_OUT max = WIDTH_OUT
            for (int b = 0; b < BATCH_SIZE; b++) {
#pragma HLS LOOP_TRIPCOUNT min = BATCH_SIZE max = BATCH_SIZE
                for (int c = 0; c < CHANNEL_OUT; c++) {
#pragma HLS LOOP_TRIPCOUNT min = CHANNEL_OUT max = CHANNEL_OUT
                    out[b][c][i][j] = 0;
                }
            }
        }
    }

init_bias:
  for (int k = 0; k < CHANNEL_OUT; k++) {
#pragma HLS LOOP_TRIPCOUNT min = CHANNEL_OUT max = CHANNEL_OUT 
        bias[k] = k + 10;
    }
init_kernel:
    for (int k = 0; k < CHANNEL_OUT; k++){
#pragma HLS LOOP_TRIPCOUNT min = CHANNEL_OUT max = CHANNEL_OUT
        for (int l = 0; l < CHANNEL_IN; l++){
#pragma HLS LOOP_TRIPCOUNT min = CHANNEL_IN max = CHANNEL_IN
            kernel[k][l] = 2;
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
#pragma HLS LOOP_TRIPCOUNT min = WIDTH_OUT max = WIDTH_OUT
                Output_Channel:
                for (int out_ch = 0; out_ch < CHANNEL_OUT; out_ch++){
#pragma HLS LOOP_TRIPCOUNT min = CHANNEL_OUT max = CHANNEL_OUT
                    In_Channel:
                    for (int in_ch = 0; in_ch < CHANNEL_IN; in_ch++){
#pragma HLS LOOP_TRIPCOUNT min = CHANNEL_IN max = CHANNEL_IN
                        out[batch][out_ch][row][col] += in[batch][in_ch][row][col] * kernel[out_ch][in_ch];
                    }
                    if (isConvBias)
                        out[batch][out_ch][row][col] += bias[out_ch];
                }
            }
        }
    }
}
static void store_result(float out[BATCH_SIZE][CHANNEL_OUT][HEIGHT_OUT][WIDTH_OUT], float* buffer_result)
{
    for (int i = 0; i < HEIGHT_OUT; i++) {
#pragma HLS LOOP_TRIPCOUNT min = HEIGHT_OUT max = HEIGHT_OUT
        for (int j = 0; j < WIDTH_OUT; j++) {
#pragma HLS LOOP_TRIPCOUNT min = WIDTH_OUT max = WIDTH_OUT
            for (int c = 0; c < CHANNEL_OUT; c++) {
#pragma HLS LOOP_TRIPCOUNT min = CHANNEL_OUT max = CHANNEL_OUT
                for (int b = 0; b < BATCH_SIZE; b++) {
#pragma HLS LOOP_TRIPCOUNT min = BATCH_SIZE max = BATCH_SIZE
                    buffer_result[b*CHANNEL_OUT*HEIGHT_OUT*WIDTH_OUT + c*HEIGHT_OUT*WIDTH_OUT + i*WIDTH_OUT + j] = out[b][c][i][j];
                }
            }
        }
    }
}
extern "C"
{
    void kernel_proj(float *buffer_DataIn_1,
                     float *buffer_result)
    {
// TODO: modify depth
#pragma HLS INTERFACE m_axi port = buffer_DataIn_1 bundle = gmem0 depth = 75264
#pragma HLS INTERFACE m_axi port = buffer_result bundle = gmem0 depth = 75264

#pragma HLS dataflow
// dataflow僅可以接受single reader and single writer
        // dataflow pragma instruct compiler to run following three APIs in parallel
        float in[BATCH_SIZE][CHANNEL_IN][HEIGHT_IN][WIDTH_IN];
#pragma HLS bind_storage variable=in type=RAM_1P impl=uram
        float out[BATCH_SIZE][CHANNEL_OUT][HEIGHT_OUT][WIDTH_OUT];
#pragma HLS bind_storage variable=out type=RAM_1P impl=uram
        load_input(buffer_DataIn_1, in);
        compute_conv(in, out);
        store_result(out, buffer_result);
    }
}
