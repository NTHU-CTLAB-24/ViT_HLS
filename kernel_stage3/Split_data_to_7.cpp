#include "kernel_stage3.hpp"
#include <stdint.h>
using namespace std;

void split_data_to7(float *origin, float *l1, float *l2, float *l3, float *l4, float *l5, float *l6, float *l7, int n)
{
    for (int i = 0; i < n * 7; i++)
    {
        if (i < n)
            l1[i] = origin[i];
        else if (i < n * 2)
            l2[i - n] = origin[i];
        else if (i < n * 3)
            l3[i - n * 2] = origin[i];
        else if (i < n * 4)
            l4[i - n * 3] = origin[i];
        else if (i < n * 5)
            l5[i - n * 4] = origin[i];
        else if (i < n * 6)
            l6[i - n * 5] = origin[i];
        else
            l7[i - n * 6] = origin[i];
    }
}