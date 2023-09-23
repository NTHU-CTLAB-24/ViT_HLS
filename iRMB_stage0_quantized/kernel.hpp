#include <stdint.h>
#include "ap_fixed.h"
//#include “hls_half.h”

typedef uint8_t dtype;//for picture
typedef int int_t;// just int?
typedef ap_fixed<17, 9, AP_RND, AP_SAT> ftype;// 17 bits for all, 9 bits for sign int, 8bits for bits after fixed point
//typedef float ftype;
