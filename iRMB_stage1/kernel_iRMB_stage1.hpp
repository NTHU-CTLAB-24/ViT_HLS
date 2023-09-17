// Includes
#include <ap_int.h>
#include <hls_stream.h>
#include <iostream>

const int size = 4096;

extern "C"
{
    void kernel_irmb_stage1(float* in1, float* out);
}