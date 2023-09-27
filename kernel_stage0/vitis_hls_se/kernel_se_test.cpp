#include "kernel_se.hpp"
using namespace std;

int main() {
int msp_size = 8;
 
float X_data[1536];
float Y_se[1536];
int X_num[4] = {1, 24, 8, 8};
float X_mean[24];
float X_reduce[24];
float X_relu[24];
float X_expand[24];
float X_sigmoid[24];

float reduce_filter[576];
float reduce_bias[24];
float expand_filter[576];
float expand_bias[24];

for (int b = 0; b < 1; b++) {
    for (int c = 0; c < 24; c++) {
        for (int h = 0; h < msp_size; h++) {
            for (int w = 0; w < msp_size; w++) {
                X_data[b*1*msp_size*msp_size + c*msp_size*msp_size + h*msp_size + w] = c + h;
            }
        }
    }
}
for (int i = 0; i < 24; i++) {
    for (int j = 0; j < 24; j++) {
        for (int k = 0; k < 1; k++) {
            for (int l = 0; l < 1; l++) {
                reduce_filter[i*24 + j + k + l] = 0.1;
                expand_filter[i*24 + j + k + l] = 0.005;
            }
        }
    }
}
for (int c = 0; c < 24; c++) {
    reduce_bias[c] = c + 0.01;
    expand_bias[c] = c + 0.01;
}


SE(X_data, Y_se, X_num, X_mean, X_reduce, X_relu, X_expand, X_sigmoid, reduce_filter, reduce_bias, expand_filter, expand_bias); 

for (int b = 0; b < 1; b++) {
    for (int c = 0; c < 24; c++) {
        for (int h = 0; h < 1; h++) {
            for (int w = 0; w < 1; w++) {
                cout << X_reduce[b*24 + c] << " ";
            }
            cout << endl;
        }
    }
}
  
  return EXIT_SUCCESS;
}
