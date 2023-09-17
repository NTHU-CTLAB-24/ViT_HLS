// Includes
#include <iostream>
#include <ap_int.h>
#include <hls_stream.h>

extern "C" {
void kernel_DW_conv_1(float* in1, float* out);
}

