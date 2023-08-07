#include <array>
#include <iostream>

#define CHANNEL_IN 3
#define CHANNEL_OUT 10
#define HEIGHT_IN 16
#define WIDTH_IN 16

#define KERNEL_SIZE 4
#define PADDING 0
#define STRIDE 4


int main() {
  const int HEIGHT_OUT = (HEIGHT_IN - KERNEL_SIZE + 2 * PADDING) / STRIDE + 1;
  const int WIDTH_OUT = (WIDTH_IN - KERNEL_SIZE + 2 * PADDING) / STRIDE + 1;
  const int num_patch = HEIGHT_OUT * WIDTH_OUT + 1;
  std::cout << "Check output size: " << HEIGHT_OUT << " * " << WIDTH_OUT
            << std::endl;

  float In[HEIGHT_IN][WIDTH_IN][CHANNEL_IN];
  float Out[HEIGHT_OUT][WIDTH_OUT][CHANNEL_OUT];
  float Flatten[num_patch][CHANNEL_OUT]; //result
  float Kernel[KERNEL_SIZE][KERNEL_SIZE][CHANNEL_OUT];
  float ClassToken[CHANNEL_OUT];
  float Position[num_patch][CHANNEL_OUT];

Initialize_In:
int num = 1;
  for (int i = 0; i < HEIGHT_IN; i++) {
    for (int j = 0; j < WIDTH_IN; j++) {
      for (int k = 0; k < CHANNEL_IN; k++) {
        In[i][j][k] = float(num%256);
        num  = num + 1;
      }
    }
  }
  std::cout << "init image done" << std::endl;

Initialize_Kernel:

  for (int i = 0; i < KERNEL_SIZE; i++) {
    for (int j = 0; j < KERNEL_SIZE; j++) {
      for (int k = 0; k < CHANNEL_OUT; k++) {
        Kernel[i][j][k] = j;
      }
    }
  }

Initialize_ClassToken:
    for (int i=0; i<CHANNEL_OUT; i++) {
        ClassToken[i] = i;
    }

Initialize_Position:
    int pos = 0;
    for (int i=0; i<num_patch; i++) {
        for (int j=0; j<CHANNEL_OUT; j++) {
            Position[i][j] = pos;
            pos++;
        }
    }

Intialize_Out:

  for (int i = 0; i < HEIGHT_OUT; i++) {
    for (int j = 0; j < WIDTH_OUT; j++) {
      for (int k = 0; k < CHANNEL_OUT; k++) {
        Out[i][j][k] = 0;
      }
    }
  }

// 該版本為unroll和pipeline的3D版本
Convolution:
Kernel_Row:
  for (int kernel_row = 0; kernel_row < KERNEL_SIZE; kernel_row++) {
  Kernel_Col:
    for (int kernel_col = 0; kernel_col < KERNEL_SIZE; kernel_col++) {
    Out_Row:
      for (int row = 0; row < HEIGHT_OUT; row++) {
      Out_Column:
        for (int col = 0; col < WIDTH_OUT; col++) {
#pragma HLS PIPELINE
        Out_channel:
          for (int ch_out = 0; ch_out < CHANNEL_OUT; ch_out++) {
          In_channel:
            for (int ch_in = 0; ch_in < CHANNEL_IN; ch_in++) {
              Out[row][col][ch_out] += In[row * STRIDE + kernel_row]
                                         [col * STRIDE + kernel_col][ch_in] *
                                       Kernel[kernel_row][kernel_col][ch_out];
            }
          }
        }
      }
    }
  }
    std::cout << "conv done" << std::endl;
    Reshape:
        for (int i=0; i<HEIGHT_OUT; i++) {
            for (int j=0; j<WIDTH_OUT; j++) {
                for (int k=0; k<CHANNEL_OUT; k++) {
                    int row = i*WIDTH_OUT+j+1;
                    Flatten[row][k] = Out[i][j][k];
                }
            }
        }
        for (int i=0; i<CHANNEL_OUT; i++) {
            Flatten[0][i] = 0;
        }
        for (int i=0; i<num_patch; i++) {
            for (int j=0; j<CHANNEL_OUT; j++) {
                std::cout << Flatten[i][j] << " ";
            }
            std::cout << std::endl;
        }

    std::cout << "reshape done" << std::endl;

    Concate_ClassToken:
        for (int i=0; i<CHANNEL_OUT; i++) {
            Flatten[0][i] = ClassToken[i];
        }
    std::cout << "class token is added" << std::endl;

    
    Add_Position:
        for (int i=0; i<num_patch; i++) {
            for (int j=0; j<CHANNEL_OUT; j++) {
                Flatten[i][j] += Position[i][j];
            }
        }
    std::cout << "position is added" << std::endl;
      std::cout << "Output array: " << std::endl;
Output:
    for (int i=0; i<num_patch; i++) {
        for (int j=0; j<CHANNEL_OUT; j++) {
            if (j == CHANNEL_OUT - 1)
                std::cout << Flatten[i][j] << std::endl;
            else
                std::cout << Flatten[i][j] << " ";
        }
    }

}