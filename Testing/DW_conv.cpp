#include <stdint.h>
#include "kernel_stage0.hpp"
using namespace std;

void DW_conv(float *in, float *kernel, float *bias, int *shape_para, int *conv_para, float *out)
{
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
    int in_row;
    int in_col;
    int in_pos;
    int kernel_pos;

execute:
Batch:
    for (int batch = 0; batch < BATCH_SIZE; batch++)
    {
    Out_Row:
        for (int row = 0; row < HEIGHT_OUT; row++)
        {
        Out_Column:
            for (int col = 0; col < WIDTH_OUT; col++)
            {
                int biasFlag = 1; // 這種迴圈架構的bias會被重複計算，需要此flag限制只加一次
            Kernel_Row:
                for (int kernel_row = 0; kernel_row < KERNEL_SIZE; kernel_row++)
                {
                Kernel_Col:
                    for (int kernel_col = 0; kernel_col < KERNEL_SIZE; kernel_col++)
                    {
                        int groupIndex = 0;
                        in_row = row * STRIDE + kernel_row - PADDING;
                        in_col = col * STRIDE + kernel_col - PADDING;
                        if (in_row < 0 || in_row >= HEIGHT_IN || in_col < 0 || in_col >= WIDTH_IN )
                            continue;
                    Output_Channel:
                        for (int out_ch = 0; out_ch < CHANNEL_OUT; out_ch++)
                        {
                            out_pos = batch * CHANNEL_OUT * HEIGHT_OUT * WIDTH_OUT + out_ch * HEIGHT_OUT * WIDTH_OUT + row * WIDTH_OUT + col;
                            kernelChannelIdx = 0;
                        In_Channel:
                            for (int in_ch = groupIndex * inGroupNums; in_ch < CHANNEL_IN; in_ch++)
                            {
                                in_pos = batch * CHANNEL_IN * HEIGHT_IN * WIDTH_IN + in_ch * HEIGHT_IN * WIDTH_IN + in_row * WIDTH_IN + in_col;
                                kernel_pos = out_ch * KERNEL_CHANNEL * KERNEL_SIZE * KERNEL_SIZE + kernelChannelIdx * KERNEL_SIZE * KERNEL_SIZE + kernel_row * KERNEL_SIZE + kernel_col;
                                out[out_pos] += in[in_pos] * kernel[kernel_pos];
                                kernelChannelIdx++;
                                if ((in_ch + 1) % inGroupNums == 0)
                                    break;
                            }
                            if (isConvBias && biasFlag){
                                out[out_pos] += bias[out_ch];
                                biasFlag = 0;
                            }
                            if ((out_ch + 1) % outGroupNums == 0)
                                groupIndex++;
                        }
                    }
                }
            }
        }
    }

    return;
}
