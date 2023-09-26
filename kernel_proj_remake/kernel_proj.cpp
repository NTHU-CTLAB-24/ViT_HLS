// Includes
#include <hls_math.h>
#include <hls_stream.h>
#include <stdint.h>

/* Remember to modify test file */

// TODO: modify size
// TRIPCOUNT identifie
// const int BATCH_SIZE = 1;
// const int CHANNEL_IN = 24;
// const int CHANNEL_OUT = 24;
// const int HEIGHT_IN = 28;
// const int WIDTH_IN = 28;

// // TODO: modify conv parameters
// // Convolution parameters
// const int KERNEL_SIZE = 1;
// const int STRIDE = 1;
// const int GROUP = 1;

// // Padding and size
// const int PADDING = 0;
// const int HEIGHT_OUT = (HEIGHT_IN - KERNEL_SIZE + 2 * PADDING) / STRIDE + 1;
// const int WIDTH_OUT = (WIDTH_IN - KERNEL_SIZE + 2 * PADDING) / STRIDE + 1;

// For Convolution
// const int KERNEL_CHANNEL = CHANNEL_IN / GROUP;
// const int inGroupNums = CHANNEL_IN / GROUP;
// const int outGroupNums = CHANNEL_OUT / GROUP;
// const bool isConvBias = false;

// Coding Style: function宣告要為static，遇到for迴圈前可以取error_type的名稱(ex: mem_rd)
//

static void compute_conv(float *buffer_DataIn_1, float *out, float *buffer_kernel, float *buffer_bias,
                        int batch_size, int channel_in, int channel_out, int height_in, int width_in,
                        int kernel_size, int stride, int group, int padding, bool is_conv_bias){
execute:
    int height_out = (height_in - kernel_size + 2 * padding) / stride + 1;
    int width_out = (width_in - kernel_size + 2 * padding) / stride + 1;
    int kernel_channel = channel_in / group;
    int in_group_num = channel_in / group;
    int out_group_num = channel_out / group;
Batch:
//	for(int k = 0; k < CHANNEL_OUT; k++){
//		for(int l = 0; l < CHANNEL_IN; l++){
//			out[k*CHANNEL_IN+l] = buffer_kernel[k*CHANNEL_IN + l];
//		}
//	}
    for (int batch = 0; batch < batch_size; batch++){
    Out_Row:
        for (int row = 0; row < height_out; row++){
        Out_Column:
            for (int col = 0; col < width_out; col++){
                Output_Channel:
                for (int out_ch = 0; out_ch < channel_out; out_ch++){
                    In_Channel:
                    for (int in_ch = 0; in_ch < channel_in; in_ch++){
                    	// TODO: kernel returns 0
                        out[batch * channel_out * height_out * width_out + out_ch * height_out * width_out + row * width_out + col]
                            += buffer_DataIn_1[batch * channel_in * height_in * width_in + in_ch * height_in * width_in + row * width_in + col] * buffer_kernel[out_ch * kernel_channel + in_ch];
                    }
                    if (isConvBias)
                        out[batch * channel_out * height_out * width_out + out_ch * height_out * width_out + row * width_out + col] += buffer_bias[out_ch];
                }
            }
        }
    }
}

extern "C"
{
    void kernel_proj(float* buffer_DataIn_1, float* buffer_result, float* buffer_kernel, float* buffer_bias,
                    int batch_size, int channel_in, int channel_out, int height_in, int width_in,
                    int kernel_size, int stride, int group, int padding, bool is_conv_bias)
    {
// TODO: modify depth
#pragma HLS INTERFACE m_axi port = buffer_DataIn_1 bundle = gmem0 //depth = 18816
#pragma HLS INTERFACE m_axi port = buffer_result bundle = gmem0 //depth = 18816
#pragma HLS INTERFACE m_axi port = buffer_kernel bundle = gmem0 //depth = 576
#pragma HLS INTERFACE m_axi port = buffer_bias bundle = gmem0 //depth = 24

        compute_conv(buffer_DataIn_1, buffer_result, buffer_kernel, buffer_bias,
                    batch_size, channel_in, channel_out, height_in, width_in,
                    kernel_size, stride, group, padding, is_conv_bias);
    }
}
