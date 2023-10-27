#include <stdint.h>
#include "kernel_stage0.hpp"
using namespace std;

void load_params(float* params, float* src, int size){
    int i = 0;
    for(i = 0; i < size; i++) params[i] = src[i];
    for(; i < max_param_size; i++) params[i] = 0;
}