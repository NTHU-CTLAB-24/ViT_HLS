/*******************************************************************************
Vendor: Xilinx
Associated Filename: vadd.h
Purpose: VITIS vector addition

*******************************************************************************
Copyright (C) 2019 XILINX, Inc.

This file contains confidential and proprietary information of Xilinx, Inc. and
is protected under U.S. and international copyright and other intellectual
property laws.

DISCLAIMER
This disclaimer is not a license and does not grant any rights to the materials
distributed herewith. Except as otherwise provided in a valid license issued to
you by Xilinx, and to the maximum extent permitted by applicable law:
(1) THESE MATERIALS ARE MADE AVAILABLE "AS IS" AND WITH ALL FAULTS, AND XILINX
HEREBY DISCLAIMS ALL WARRANTIES AND CONDITIONS, EXPRESS, IMPLIED, OR STATUTORY,
INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, NON-INFRINGEMENT, OR
FITNESS FOR ANY PARTICULAR PURPOSE; and (2) Xilinx shall not be liable (whether
in contract or tort, including negligence, or under any other theory of
liability) for any loss or damage of any kind or nature related to, arising
under or in connection with these materials, including for any direct, or any
indirect, special, incidental, or consequential loss or damage (including loss
of data, profits, goodwill, or any type of loss or damage suffered as a result
of any action brought by a third party) even if such damage or loss was
reasonably foreseeable or Xilinx had been advised of the possibility of the
same.

CRITICAL APPLICATIONS
Xilinx products are not designed or intended to be fail-safe, or for use in any
application requiring fail-safe performance, such as life-support or safety
devices or systems, Class III medical devices, nuclear facilities, applications
related to the deployment of airbags, or any other applications that could lead
to death, personal injury, or severe property or environmental damage
(individually and collectively, "Critical Applications"). Customer assumes the
sole risk and liability of any use of Xilinx products in Critical Applications,
subject only to applicable laws and regulations governing limitations on product
liability.

THIS COPYRIGHT NOTICE AND DISCLAIMER MUST BE RETAINED AS PART OF THIS FILE AT
ALL TIMES.

*******************************************************************************/

/*******************************************************************************
Description:

    This example uses the load/compute/store coding style which is generally
    the most efficient for implementing kernels using HLS. The load and store
    functions are responsible for moving data in and out of the kernel as
    efficiently as possible. The core functionality is decomposed across one
    of more compute functions. Whenever possible, the compute function should
    pass data through HLS streams and should contain a single set of nested
loops.

    HLS stream objects are used to pass data between producer and consumer
    functions. Stream read and write operations have a blocking behavior which
    allows consumers and producers to synchronize with each other automatically.

    The dataflow pragma instructs the compiler to enable task-level pipelining.
    This is required for to load/compute/store functions to execute in a
parallel and pipelined manner. Here the kernel loads, computes and stores
NUM_WORDS integer values per clock cycle and is implemented as below:
                                       _____________
                                      |             |<----- Input Vector 1 from
Global Memory |  load_input |       __
                                      |_____________|----->|  |
                                       _____________       |  | in1_stream
Input Vector 2 from Global Memory --->|             |      |__|
                               __     |  load_input |        |
                              |  |<---|_____________|        |
                   in2_stream |  |     _____________         |
                              |__|--->|             |<--------
                                      | compute_add |      __
                                      |_____________|---->|  |
                                       ______________     |  | out_stream
                                      |              |<---|__|
                                      | store_result |
                                      |______________|-----> Output result to
Global Memory

*******************************************************************************/

// Includes
#include <hls_stream.h>
#include <hls_math.h>
#include <stdint.h>

#define DIM 5
#define DATA_SIZE DIM

// TRIPCOUNT identifier
const int c_size = DATA_SIZE;

static void load_input(float* in, hls::stream<float>& inStream,
                       int size) {
mem_rd:
  for (int i = 0; i < size; i++) {
#pragma HLS LOOP_TRIPCOUNT min = c_size max = c_size
    inStream << in[i];
  }
}

static void compute_add(hls::stream<float>& in1_stream, 
                        hls::stream<float>& in2_stream,
						hls::stream<float>& in3_stream,
                        hls::stream<float>& out_stream, 
                        int size) {
    for (int i = 0; i < size; i++) {
        out_stream << (in1_stream.read()+in2_stream.read() + in3_stream.read());
    }
}

static void compute_norm(hls::stream<float>& in1_stream,
                        hls::stream<float>& in2_stream,
                        hls::stream<float>& in3_stream,
                        hls::stream<float>& out_stream, int size) {
    float data[DIM];
sum:
    float sum = 0;
    float sum2 = 0;
    for (int i = 0; i < size ; i++) {
    data[i] = in1_stream.read();
    sum += data[i];
    sum2 += data[i] * data[i];
  }

std:
  float avg = sum / size;  // mean of the input array
  float var = sum2 / size;
  var -= avg * avg;     // Var(x) = E[X^2] - E[X]^2
  var += 1e-5;
  float std = sqrtf(var);  // square root of the variance of the input

gen_output:
    float err;
	float mul;
	float val;
  for (int i = 0; i < size; i++) {
    err = data[i] - avg;
    err = err / std;
    val = err * in2_stream.read();
    out_stream << (val + in3_stream.read());
  }
}

static void store_result(float* out, hls::stream<float>& out_stream, int size) {
mem_wr:
    for (int i = 0; i < size; i++) {
#pragma HLS LOOP_TRIPCOUNT min = c_size max = c_size
        out[i] = out_stream.read();
    }
}

extern "C" {
/*
    Normalization Kernel

    Arguments:
        in1  (input)  --> Input 
        in2 (input) --> Weight
        in3 (input) --> Bias
        output  (output) --> Output 
        size (input)  --> Number of elements in vector
*/
void krnl_norm(float* in1, float* in2, float* in3, float* output, int size) {
#pragma HLS INTERFACE m_axi port = in1 bundle = gmem0
#pragma HLS INTERFACE m_axi port = in2 bundle = gmem1
#pragma HLS INTERFACE m_axi port = in3 bundle = gmem2
#pragma HLS INTERFACE m_axi port = output bundle = gmem0

  static hls::stream<float> in1_stream("in1_stream");
  static hls::stream<float> in2_stream("in2_stream");
  static hls::stream<float> in3_stream("in3_stream");
  static hls::stream<float> output_stream("output_stream");

#pragma HLS dataflow
  // dataflow pragma instruct compiler to run following three APIs in parallel
  load_input(in1, in1_stream, size);
  load_input(in2, in2_stream, size);
  load_input(in3, in3_stream, size);
  compute_norm(in1_stream, in2_stream, in3_stream, output_stream, size);
  store_result(output, output_stream, size);
}
}

