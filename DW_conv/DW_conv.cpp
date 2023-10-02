#include <stdint.h>
#include "DW_conv.hpp"
using namespace std;

void DW_conv(float *in, float *kernel, float *bias, int *shape_para, int *conv_para, float *out)
{
#pragma HLS INTERFACE m_axi port = in bundle = gmem0 depth = 3072   
#pragma HLS INTERFACE m_axi port = out bundle = gmem0 depth = 768
#pragma HLS INTERFACE m_axi port = kernel bundle = gmem0 depth = 216
#pragma HLS INTERFACE m_axi port = bias bundle = gmem0 depth = 24
#pragma HLS INTERFACE m_axi port = shape_para bundle = gmem0 depth = 7
#pragma HLS INTERFACE m_axi port = conv_para bundle = gmem0 depth = 6

    int BATCH_SIZE = shape_para[0];
    int CHANNEL_IN = shape_para[1];
    int HEIGHT_IN = shape_para[2];
    int WIDTH_IN = shape_para[3];
    int CHANNEL_OUT = shape_para[4];
    int HEIGHT_OUT = shape_para[5];
    int WIDTH_OUT = shape_para[6];

    int KERNEL_SIZE = conv_para[0];
    int isConvBias = conv_para[1];
    int STRIDE = conv_para[2];
    int PADDING = conv_para[3];
    int GROUP = conv_para[4];
    int KERNEL_CHANNEL = conv_para[5];

    int inGroupNums = CHANNEL_IN / GROUP;
    int outGroupNums = CHANNEL_OUT / GROUP;

    int kernelChannelIdx;
    int out_pos;
    float out_val;
    int in_row;
    int in_col;
    int in_pos;
    int kernel_pos;
    float kernel_val;

execute:
Batch:
    for (int batch = 0; batch < BATCH_SIZE; batch++)
    {
	#pragma HLS LOOP_TRIPCOUNT min = 2 max = 2
    Out_Row:
        for (int row = 0; row < HEIGHT_OUT; row++)
        {
		#pragma HLS LOOP_TRIPCOUNT min = 4 max = 4
        Out_Column:
            for (int col = 0; col < WIDTH_OUT; col++)
            {
			#pragma HLS LOOP_TRIPCOUNT min = 4 max = 4
			int biasFlag = 1; // 這種迴圈架構的bias會被重複計算，需要此flag限制只加一次
            Kernel_Row:
                for (int kernel_row = 0; kernel_row < KERNEL_SIZE; kernel_row++)
                {
				#pragma HLS LOOP_TRIPCOUNT min = 3 max = 3
                Kernel_Col:
                    for (int kernel_col = 0; kernel_col < KERNEL_SIZE; kernel_col++)
                    {
					#pragma HLS LOOP_TRIPCOUNT min = 3 max = 3
						int groupIndex = 0;
						in_row = row * STRIDE + kernel_row - PADDING;
						in_col = col * STRIDE + kernel_col - PADDING;
						if (in_row < 0 || in_row >= HEIGHT_IN || in_col < 0 || in_col >= WIDTH_IN )
							continue;
					Output_Channel:
                        for (int out_ch = 0; out_ch < CHANNEL_OUT; out_ch++)
                        {
						#pragma HLS LOOP_TRIPCOUNT min = 24 max = 24
                        	out_pos = batch * CHANNEL_OUT * HEIGHT_OUT * WIDTH_OUT + out_ch * HEIGHT_OUT * WIDTH_OUT + row * WIDTH_OUT + col;
                            out_val = out[out_pos];
                        In_Channel:
                            kernel_pos = out_ch * KERNEL_CHANNEL * KERNEL_SIZE * KERNEL_SIZE + kernelChannelIdx * KERNEL_SIZE * KERNEL_SIZE + kernel_row * KERNEL_SIZE + kernel_col;
                            kernel_val = kernel[kernel_pos];
                            for (int in_ch = groupIndex * inGroupNums; in_ch < CHANNEL_IN; in_ch++)
                            {
							#pragma HLS LOOP_TRIPCOUNT min = 0 max = 24
                                kernelChannelIdx = 0;
                                in_pos = batch * CHANNEL_IN * HEIGHT_IN * WIDTH_IN + in_ch * HEIGHT_IN * WIDTH_IN + in_row * WIDTH_IN + in_col;
                                out_val += in[in_pos] * kernel_val;
                                kernelChannelIdx++;
                                if ((in_ch + 1) % inGroupNums == 0)
                                    break;
                            }
                            if (isConvBias && biasFlag){
                                out_val += bias[out_ch];
                            }
                            out[out_pos] = out_val;
                            if ((out_ch + 1) % outGroupNums == 0)
                                groupIndex++;
                        }
                        biasFlag = 0;
                    }
                }
            }
        }
    }

    return;
}