// Includes
#include <stdint.h>
#include "kernel_stage0.hpp"
using namespace std;

void Pointwise_conv(float* img, float* out, float *buffer_kernel, float *buffer_bias,
                    int batch_size, int channel_in, int channel_out, int height_in, int width_in,
                    bool is_conv_bias)
{
execute:
    int height_out = height_in;
    int width_out = width_in;
    int kernel_channel = channel_in;

Batch:
    for (int batch = 0; batch < batch_size; batch++)
    {
    Out_Row:
        for (int row = 0; row < height_out; row++)
        {
        Out_Column:
            for (int col = 0; col < width_out; col++)
            {
            Output_Channel:
                for (int out_ch = 0; out_ch < channel_out; out_ch++)
                {
                In_Channel:
                    for (int in_ch = 0; in_ch < channel_in; in_ch++)
                    {
                        out[batch * channel_out * height_out * width_out + out_ch * height_out * width_out + row * width_out + col] += img[batch * channel_in * height_in * width_in + in_ch * height_in * width_in + row * width_in + col] * buffer_kernel[out_ch * kernel_channel + in_ch];
                    }
                    if (is_conv_bias)
                        out[batch * channel_out * height_out * width_out + out_ch * height_out * width_out + row * width_out + col] += buffer_bias[out_ch];
                }
            }
        }
    }

    return;
}