#include <stdint.h>
#include "kernel_stage0.hpp"

static bool init_blocks(){
    for (int i = 0; i < compute_space; i++) img[i] = 0.0;
    for (int i = 0; i < compute_space; i++) compute_tmp[i] = 0.0;
    for (int i = 0; i < max_param_size; i++) params[i] = 0.0;
    return true;
}

static const bool init = init_blocks();

float img[compute_space] = {};
float compute_tmp[compute_space] = {};
float params[max_param_size] = {};