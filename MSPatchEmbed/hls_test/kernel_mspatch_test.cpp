#include "kernel_mspatch.hpp"
const int BATCH_SIZE = 1;
const int HEIGHT_IN = 30;
const int WIDTH_IN = 30;
const int CHANNEL_IN = 3;
const int CHANNEL_OUT = 24;
const int KERNEL_SIZE = 3;
const int PADDING = 1;
const int STRIDE = 2;
const int HEIGHT_PAD = HEIGHT_IN + 2 * PADDING;
const int WIDTH_PAD = WIDTH_IN + 2 * PADDING;
const int HEIGHT_OUT = (HEIGHT_IN - KERNEL_SIZE + 2 * PADDING) / STRIDE + 1;
const int WIDTH_OUT = (WIDTH_IN - KERNEL_SIZE + 2 * PADDING) / STRIDE + 1;

int main() {
    
float in1[BATCH_SIZE*CHANNEL_IN*HEIGHT_IN*WIDTH_IN];
float in2[CHANNEL_OUT*4];
float out[BATCH_SIZE*CHANNEL_OUT*HEIGHT_OUT*WIDTH_OUT];

//init image
for (int b=0; b<BATCH_SIZE; b++) {
    for (int c=0; c<CHANNEL_IN; c++) {
        for (int i=0; i<HEIGHT_IN; i++)  {
            for (int j=0; j<WIDTH_IN; j++) {
                in1[b*CHANNEL_IN*HEIGHT_IN*WIDTH_IN + c*HEIGHT_IN*WIDTH_IN + i*WIDTH_IN + j] = (c+i+j)%256;
            }
        }
    }
}

//init norm parameter
for (int i=0; i<CHANNEL_OUT; i++) {
    in2[i] = 8;
}
for (int i=CHANNEL_OUT; i<CHANNEL_OUT*2; i++) {
    in2[i] = 21.5;
}
for (int i=CHANNEL_OUT*2; i<CHANNEL_OUT*3; i++) {
    in2[i] = 0.5;
}
for (int i=CHANNEL_OUT*3; i<CHANNEL_OUT*4; i++) {
    in2[i] = 0.2;
}

kernel_mspatch(in1, in2, out);


std::cout << "result" << std::endl;
  //print out[0, 0, :, :]
  for (int i=0; i<HEIGHT_OUT; i++) {
    for (int j=0; j<WIDTH_OUT; j++) {
        std::cout << out[i*WIDTH_OUT + j] << " ";
    }
    std::cout << std::endl;
  }
  
  return EXIT_SUCCESS;
}
