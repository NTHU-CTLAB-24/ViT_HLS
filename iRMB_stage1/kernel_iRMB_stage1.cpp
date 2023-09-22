// Includes
#include <hls_math.h>
#include <hls_stream.h>
#include <stdint.h>
#include "kernel_norm_in_0.hpp"
#include "kernel_v_conv_0.hpp"
#include "kernel_DW_conv_0.hpp"
#include "kernel_proj_0.hpp"
#include "kernel_norm_in_1.hpp"
#include "kernel_v_conv_1.hpp"
#include "kernel_DW_conv_1.hpp"
#include "kernel_proj_1.hpp"

// TRIPCOUNT identifier
const int BATCH_SIZE = 1;
const int HEIGHT_IN = 8;
const int WIDTH_IN = 8;
const int CHANNEL_IN = 24;
const int CHANNEL_MID_0 = 96;
const int CHANNEL_MID_1 = 64;
const int CHANNEL_OUT = 32;
const int KERNEL_SIZE = 3;

const int PADDING = 1;
const int STRIDE = 2;
const int GROUP = 1;

const int HEIGHT_OUT = (HEIGHT_IN - KERNEL_SIZE + 2 * PADDING) / STRIDE + 1;
const int WIDTH_OUT = (WIDTH_IN - KERNEL_SIZE + 2 * PADDING) / STRIDE + 1;

static void init_out(float* norm_out_0, float* v_out_0, float* dw_conv_out_0, float* proj_out_0,
                     float* norm_out_1, float* v_out_1, float* dw_conv_out_1, float* dw_skip_out, float* proj_out_1){
#pragma dataflow

init_output:
    for (int n = 0; n < BATCH_SIZE; n++)
    {
#pragma HLS LOOP_TRIPCOUNT min = BATCH_SIZE max = BATCH_SIZE
        for (int c = 0; c < CHANNEL_MID_0; c++)
        {
#pragma HLS LOOP_TRIPCOUNT min = CHANNEL_MID_0 max = CHANNEL_MID_0
            for (int h = 0; h < HEIGHT_IN; h++)
            {
#pragma HLS LOOP_TRIPCOUNT min = HEIGHT_IN max = HEIGHT_IN
                for (int w = 0; w < WIDTH_IN; w++)
                {
#pragma HLS UNROLL
                    if(c < CHANNEL_IN)
                        norm_out_0[n * CHANNEL_IN * HEIGHT_IN * WIDTH_IN + c * HEIGHT_IN * WIDTH_IN + h * WIDTH_IN + w] = 0;
                    v_out_0[n * CHANNEL_MID_0 * HEIGHT_IN * WIDTH_IN + c * HEIGHT_IN * WIDTH_IN + h * WIDTH_IN + w] = 0;
                }
            }
        }
    }

    for (int n = 0; n < BATCH_SIZE; n++)
    {
#pragma HLS LOOP_TRIPCOUNT min = BATCH_SIZE max = BATCH_SIZE
        for (int c = 0; c < CHANNEL_MID_0; c++)
        {
#pragma HLS LOOP_TRIPCOUNT min = CHANNEL_MID_0 max = CHANNEL_MID_0
            for (int h = 0; h < HEIGHT_OUT; h++)
            {
#pragma HLS LOOP_TRIPCOUNT min = HEIGHT_OUT max = HEIGHT_OUT
                for (int w = 0; w < WIDTH_OUT; w++)
                {
#pragma HLS UNROLL
                    dw_conv_out_0[n * CHANNEL_MID_0 * HEIGHT_OUT * WIDTH_OUT + c * HEIGHT_OUT * WIDTH_OUT + h * WIDTH_OUT + w] = 0;
                    if(c < CHANNEL_OUT){
                        proj_out_0[n * CHANNEL_OUT * HEIGHT_OUT * WIDTH_OUT + c * HEIGHT_OUT * WIDTH_OUT + h * WIDTH_OUT + w] = 0;
                        norm_out_1[n * CHANNEL_OUT * HEIGHT_OUT * WIDTH_OUT + c * HEIGHT_OUT * WIDTH_OUT + h * WIDTH_OUT + w] = 0;
                        proj_out_1[n * CHANNEL_OUT * HEIGHT_OUT * WIDTH_OUT + c * HEIGHT_OUT * WIDTH_OUT + h * WIDTH_OUT + w] = 0;
                    }
                }
            }
        }
    }

    for (int n = 0; n < BATCH_SIZE; n++)
    {
#pragma HLS LOOP_TRIPCOUNT min = BATCH_SIZE max = BATCH_SIZE
        for (int c = 0; c < CHANNEL_MID_1; c++)
        {
#pragma HLS LOOP_TRIPCOUNT min = CHANNEL_MID_1 max = CHANNEL_MID_1
            for (int h = 0; h < HEIGHT_OUT; h++)
            {
#pragma HLS LOOP_TRIPCOUNT min = HEIGHT_OUT max = HEIGHT_OUT
                for (int w = 0; w < WIDTH_OUT; w++)
                {
#pragma HLS UNROLL
                    v_out_1[n * CHANNEL_MID_1 * HEIGHT_OUT * WIDTH_OUT + c * HEIGHT_OUT * WIDTH_OUT + h * WIDTH_OUT + w] = 0;
                    dw_conv_out_1[n * CHANNEL_MID_1 * HEIGHT_OUT * WIDTH_OUT + c * HEIGHT_OUT * WIDTH_OUT + h * WIDTH_OUT + w] = 0;
                    dw_skip_out[n * CHANNEL_MID_1 * HEIGHT_OUT * WIDTH_OUT + c * HEIGHT_OUT * WIDTH_OUT + h * WIDTH_OUT + w] = 0;
                }
            }
        }
    }
}

static void compute_dw_skip(float* v_out, float* dw_conv_out, float* dw_skip_out)
{
DW_Skip:
    for (int n = 0; n < BATCH_SIZE; n++)
    {
#pragma HLS LOOP_TRIPCOUNT min = BATCH_SIZE max = BATCH_SIZE
        for (int c = 0; c < CHANNEL_MID_1; c++)
        {
#pragma HLS LOOP_TRIPCOUNT min = CHANNEL_MID_1 max = CHANNEL_MID_1
            for (int h = 0; h < HEIGHT_OUT; h++)
            {
#pragma HLS LOOP_TRIPCOUNT min = HEIGHT_OUT max = HEIGHT_OUT
                for (int w = 0; w < WIDTH_OUT; w++)
                {
#pragma HLS UNROLL
                    dw_skip_out[n * CHANNEL_MID_1 * HEIGHT_OUT * WIDTH_OUT + c * HEIGHT_OUT * WIDTH_OUT + h * WIDTH_OUT + w] = v_out[n * CHANNEL_MID_1 * HEIGHT_OUT * WIDTH_OUT + c * HEIGHT_OUT * WIDTH_OUT + h * WIDTH_OUT + w] + dw_conv_out[n * CHANNEL_MID_1 * HEIGHT_OUT * WIDTH_OUT + c * HEIGHT_OUT * WIDTH_OUT + h * WIDTH_OUT + w];
                }
            }
        }
    }
}

static void compute_iRMB_skip(float* in, float* proj_out, float* buffer_result)
{
iRMB_Skip:
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
                    buffer_result[n * CHANNEL_OUT * HEIGHT_OUT * WIDTH_OUT + c * HEIGHT_OUT * WIDTH_OUT + h * WIDTH_OUT + w] = in[n * CHANNEL_OUT * HEIGHT_OUT * WIDTH_OUT + c * HEIGHT_OUT * WIDTH_OUT + h * WIDTH_OUT + w] + proj_out[n * CHANNEL_OUT * HEIGHT_OUT * WIDTH_OUT + c * HEIGHT_OUT * WIDTH_OUT + h * WIDTH_OUT + w];
                }
            }
        }
    }
}

extern "C"
{
    void kernel_irmb_stage1(float *in1, float *out)
    {
#pragma HLS INTERFACE m_axi port = in1 bundle = gmem0 depth = 1536
#pragma HLS INTERFACE m_axi port = out bundle = gmem0 depth = 512

// #pragma HLS dataflow
        float norm_out_0[BATCH_SIZE * CHANNEL_IN * HEIGHT_IN * WIDTH_IN];
#pragma HLS array_partition variable = norm_out_0 complete dim = 1
        float v_out_0[BATCH_SIZE * CHANNEL_MID_0 * HEIGHT_IN * WIDTH_IN];
#pragma HLS array_partition variable = v_out_0 complete dim = 1 
        float dw_conv_out_0[BATCH_SIZE * CHANNEL_MID_0 * HEIGHT_OUT * WIDTH_OUT];
#pragma HLS array_partition variable = dw_conv_out_0 complete dim = 1 
        float proj_out_0[BATCH_SIZE * CHANNEL_OUT * HEIGHT_OUT * WIDTH_OUT];
#pragma HLS array_partition variable = proj_out_0 complete dim = 1 

        float norm_out_1[BATCH_SIZE * CHANNEL_OUT * HEIGHT_OUT * WIDTH_OUT];
#pragma HLS array_partition variable = norm_out_1 complete dim = 1
        float v_out_1[BATCH_SIZE * CHANNEL_MID_1 * HEIGHT_OUT * WIDTH_OUT];
#pragma HLS array_partition variable = v_out_1 complete dim = 1 
        float dw_conv_out_1[BATCH_SIZE * CHANNEL_MID_1 * HEIGHT_OUT * WIDTH_OUT];
#pragma HLS array_partition variable = dw_conv_out_1 complete dim = 1
        float dw_skip_out[BATCH_SIZE * CHANNEL_MID_1 * HEIGHT_OUT * WIDTH_OUT];
#pragma HLS array_partition variable = dw_conv_out_1 complete dim = 1
        float proj_out_1[BATCH_SIZE * CHANNEL_OUT * HEIGHT_OUT * WIDTH_OUT];
#pragma HLS array_partition variable = proj_out_1 complete dim = 1

        
        init_out(norm_out_0, v_out_0, dw_conv_out_0, proj_out_0, norm_out_1, v_out_1, dw_conv_out_1, dw_skip_out, proj_out_1);
        // depth 0
        kernel_norm_in_0(in1, norm_out_0);
        kernel_v_conv_0(norm_out_0, v_out_0);
        kernel_DW_conv_0(v_out_0, dw_conv_out_0);
        kernel_proj_0(dw_conv_out_0, proj_out_0);

        // depth 1
        kernel_norm_in_1(proj_out_0, norm_out_1);
        kernel_v_conv_1(norm_out_1, v_out_1);
        kernel_DW_conv_1(v_out_1, dw_conv_out_1);
        compute_dw_skip(v_out_1, dw_conv_out_1, dw_skip_out);
        kernel_proj_1(dw_skip_out, proj_out_1);
        compute_iRMB_skip(proj_out_0, proj_out_1, out);
    }
}