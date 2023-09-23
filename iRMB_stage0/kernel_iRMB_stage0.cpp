// Includes
#include <hls_math.h>
#include <hls_stream.h>
#include <stdint.h>
#include "kernel_mspatch.hpp"
#include "kernel_DW_conv.hpp"
#include "kernel_se.hpp"
#include "kernel_proj.hpp"

// TRIPCOUNT identifier
const int BATCH_SIZE = 2;
const int HEIGHT_IN = 8;
const int WIDTH_IN = 8;
const int CHANNEL_IN = 3;
const int CHANNEL_OUT = 24;
const int KERNEL_SIZE = 3;

const int PADDING = 1;
const int STRIDE = 2;
const int GROUP = 1;

const int HEIGHT_OUT = (HEIGHT_IN - KERNEL_SIZE + 2 * PADDING) / STRIDE + 1;
const int WIDTH_OUT = (WIDTH_IN - KERNEL_SIZE + 2 * PADDING) / STRIDE + 1;

static void init_out(float* msp_out, float* dw_conv_out, float* se_out){
init_output:
    for (int n = 0; n < BATCH_SIZE; n++)
    {
#pragma HLS LOOP_TRIPCOUNT min = BATCH_SIZE max = BATCH_SIZE
        for (int c = 0; c < CHANNEL_OUT; c++)
        {
#pragma HLS LOOP_TRIPCOUNT min = CHANNEL_OUT max = CHANNEL_OUT
            for (int h = 0; h < HEIGHT_OUT; h++)
            {
#pragma HLS LOOP_TRIPCOUNT min = HEIGHT_OUT max = HEIGHT_OUT
                for (int w = 0; w < WIDTH_OUT; w++)
                {
#pragma HLS UNROLL
                    msp_out[n * CHANNEL_OUT * HEIGHT_OUT * WIDTH_OUT + c * HEIGHT_OUT * WIDTH_OUT + h * WIDTH_OUT + w] = 0;
                    dw_conv_out[n * CHANNEL_OUT * HEIGHT_OUT * WIDTH_OUT + c * HEIGHT_OUT * WIDTH_OUT + h * WIDTH_OUT + w] = 0;
                    se_out[n * CHANNEL_OUT * HEIGHT_OUT * WIDTH_OUT + c * HEIGHT_OUT * WIDTH_OUT + h * WIDTH_OUT + w] = 0;
                }
            }
        }
    }
}

extern "C"
{
    void kernel_irmb_stage0(float *in1, float *in2, float *out)
    {
#pragma HLS INTERFACE m_axi port = in1 bundle = gmem0 depth = 384
#pragma HLS INTERFACE m_axi port = in2 bundle = gmem1 depth = 96
#pragma HLS INTERFACE m_axi port = out bundle = gmem0 depth = 768

// #pragma HLS dataflow
        float msp_out[BATCH_SIZE * CHANNEL_OUT * HEIGHT_OUT * WIDTH_OUT];
#pragma HLS array_partition variable = msp_out complete dim = 1
        float dw_conv_out[BATCH_SIZE * CHANNEL_OUT * HEIGHT_OUT * WIDTH_OUT];
#pragma HLS array_partition variable = dw_conv_out complete dim = 1 
        float se_out[BATCH_SIZE * CHANNEL_OUT * HEIGHT_OUT * WIDTH_OUT];
#pragma HLS array_partition variable = se_out complete dim = 1 
        
        init_out(msp_out, dw_conv_out, se_out);
        kernel_mspatch(in1, in2, msp_out);
        kernel_DW_conv(msp_out, dw_conv_out);
        kernel_se(dw_conv_out, se_out);
        kernel_proj(se_out, out);
    }
}