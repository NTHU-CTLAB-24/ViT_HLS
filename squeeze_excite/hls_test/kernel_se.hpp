// Includes
#include <iostream>
#include <ap_int.h>
#include <hls_stream.h>


extern "C" {
void kernel_se(float* in1, float* out);
//暫時用relu取代silu (pretrain用silu)
//之後需要的話再改回silu
}

