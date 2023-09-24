// Includes
#include <iostream>
#include <ap_int.h>
#include <hls_stream.h>

void DW_conv(float *in, float *kernel, float *bias, int *shape_para, int *conv_para, float *out);
