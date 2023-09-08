// Includes
#include <iostream>
#include <ap_int.h>
#include <hls_stream.h>

const int size = 4096;

extern "C" {
void kernel_mspatch(float* in1, float* in2, float* out);
}

