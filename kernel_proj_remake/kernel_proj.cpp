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
//

static void compute_conv(float *buffer_DataIn_1, float *out, float *buffer_kernel, float *buffer_bias)
{

execute:
Batch:
	for(int k = 0; k < CHANNEL_OUT; k++){
		for(int l = 0; l < CHANNEL_IN; l++){
			out[k*CHANNEL_IN+l] = buffer_kernel[k*CHANNEL_IN + l];
		}
	}
//    for (int batch = 0; batch < BATCH_SIZE; batch++){
//    Out_Row:
//        for (int row = 0; row < HEIGHT_OUT; row++){
//        Out_Column:
//            for (int col = 0; col < WIDTH_OUT; col++){
//                Output_Channel:
//                for (int out_ch = 0; out_ch < CHANNEL_OUT; out_ch++){
//                	out[batch * CHANNEL_OUT * HEIGHT_OUT * WIDTH_OUT + out_ch * HEIGHT_OUT * WIDTH_OUT + row * WIDTH_OUT + col] = 0;
//                    In_Channel:
//                    for (int in_ch = 0; in_ch < CHANNEL_IN; in_ch++){
//                    	// TODO: kernel returns 0
//                        out[batch * CHANNEL_OUT * HEIGHT_OUT * WIDTH_OUT + out_ch * HEIGHT_OUT * WIDTH_OUT + row * WIDTH_OUT + col] += buffer_DataIn_1[batch * CHANNEL_IN * HEIGHT_IN * WIDTH_IN + in_ch * HEIGHT_IN * WIDTH_IN + row * WIDTH_IN + col] * buffer_kernel[out_ch * CHANNEL_IN + in_ch];
//                    }
//                    if (isConvBias)
//                        out[batch * CHANNEL_OUT * HEIGHT_OUT * WIDTH_OUT + out_ch * HEIGHT_OUT * WIDTH_OUT + row * WIDTH_OUT + col] += buffer_bias[out_ch];
//                }
//            }
//        }
//    }
}

extern "C"
{
    void kernel_proj(float *buffer_DataIn_1,
                     float *buffer_result,
                     float *buffer_kernel,
                     float *buffer_bias)
    {
// TODO: modify depth
#pragma HLS INTERFACE m_axi port = buffer_DataIn_1 bundle = gmem0 //depth = 18816
#pragma HLS INTERFACE m_axi port = buffer_result bundle = gmem0 //depth = 18816
#pragma HLS INTERFACE m_axi port = buffer_kernel bundle = gmem0 //depth = 576
#pragma HLS INTERFACE m_axi port = buffer_bias bundle = gmem0 //depth = 24

        compute_conv(buffer_DataIn_1, buffer_result, buffer_kernel, buffer_bias);
    }
}
