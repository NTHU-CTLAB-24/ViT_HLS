
// Includes
#include <stdint.h>
#include <hls_stream.h>

static void compute_image(int* in, int* out, int height, int width, int channel) {
// The kernel is operating with vector of NUM_WORDS integers. The + operator performs
// an element-wise add, resulting in NUM_WORDS parallel additions.
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            for(int k = 0; k < channel; k++){
                out[k*height*width + i*width + j] = in[k*height*width + i*width + j];
            }
        }
    }
}

extern "C" {

/*
    Vector Addition Kernel

    Arguments:
        in1  (input)  --> Input vector 1
        in2  (input)  --> Input vector 2
        out  (output) --> Output vector
        size (input)  --> Number of elements in vector
*/

	void kernel_read(int* inp, int* out, int height, int width, int channel) {
		#pragma HLS INTERFACE m_axi port = inp bundle = gmem0
		#pragma HLS INTERFACE m_axi port = out bundle = gmem0

		compute_image(inp, out, height, width, channel);
	}
}
