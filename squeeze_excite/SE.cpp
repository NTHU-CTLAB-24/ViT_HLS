#include <array>
#include <iostream>
#include <cmath>

#define BATCH_SIZE 2
#define CHANNEL_IN 16
#define HEIGHT_IN 16
#define WIDTH_IN 16
#define KERNEL_SIZE 1
#define STRIDE 1
#define SE_RATIO 0.25 //0.25為測試用, EMO實際為1

#define REDUCED_CHS int(CHANNEL_IN*SE_RATIO) //reduced_chs = make_divisible(dim_in*se_ratio)

using namespace std;

float In[BATCH_SIZE][CHANNEL_IN][HEIGHT_IN][WIDTH_IN];
float Kernel_1[REDUCED_CHS][KERNEL_SIZE][KERNEL_SIZE];
float Kernel_2[CHANNEL_IN][KERNEL_SIZE][KERNEL_SIZE];

float conv_reduce[BATCH_SIZE][REDUCED_CHS][1][1];
float conv_expand[BATCH_SIZE][CHANNEL_IN][1][1];

float result[BATCH_SIZE][CHANNEL_IN][HEIGHT_IN][WIDTH_IN];

void LoadData() {
    //input data (image)
    for (int b = 0; b < BATCH_SIZE; b++) {
        for (int c = 0; c < CHANNEL_IN; c++) {
            for (int i = 0; i < HEIGHT_IN; i++) {
                for (int j = 0; j < WIDTH_IN; j++) {
                    In[b][c][i][j] = float((b+c+i+j) % 256);
                }
            }
        }
    }
    //kernel_1
    for (int c = 0; c < REDUCED_CHS; c++) {
        for (int ki = 0; ki < KERNEL_SIZE; ki++) {
            for (int kj = 0; kj < KERNEL_SIZE; kj++) {
                Kernel_1[c][ki][kj] = 0.1;
            }
        }
    }
    //kernel_2
    for (int c = 0; c < CHANNEL_IN; c++) {
        for (int ki = 0; ki < KERNEL_SIZE; ki++) {
            for (int kj = 0; kj < KERNEL_SIZE; kj++) {
                Kernel_2[c][ki][kj] = 0.005;
            }
        }
    }
}


int main() {
    //initialize the required data
    LoadData();

    //mean(2, 3), keepdim=True
    //(b, dim_in, h_in, w_in) => (b, dim_in, 1, 1)
    float mean_x[BATCH_SIZE][CHANNEL_IN][1][1];
    for (int b = 0; b < BATCH_SIZE; b++) {
        for (int c = 0; c < CHANNEL_IN; c++) {
            float sum = 0;
            for (int i = 0; i < HEIGHT_IN; i++) {
                for (int j = 0; j < WIDTH_IN; j++) {
                    sum += In[b][i][j][c];
                }
            }
            mean_x[b][c][0][0] = sum / (HEIGHT_IN * WIDTH_IN);
        }
    }

    //reduce = nn.Conv2d(dim_in, reduced_chs, 1, bias = False)
    //(b, c_in, h_in, w_in) => (b, reduced_chs, h_in, w_in)

    for (int batch = 0; batch < BATCH_SIZE; batch++) {
        for (int kernel_row = 0; kernel_row < KERNEL_SIZE; kernel_row++) {
            for (int kernel_col = 0; kernel_col < KERNEL_SIZE; kernel_col++) {
                for (int row = 0; row < 1; row++) {
                    for (int col = 0; col < 1; col++) {
                        for (int ch_out = 0; ch_out < REDUCED_CHS; ch_out++) {
                            for (int ch_in = 0; ch_in < CHANNEL_IN; ch_in++) {
                                conv_reduce[batch][ch_out][row][col] += mean_x[batch][ch_in][row * STRIDE + kernel_row][col * STRIDE + kernel_col] * Kernel_1[ch_out][kernel_row][kernel_col];
                            }
                        }
                    }
                }
            }
        }
    }
    cout << "x_se after one conv_reduce" << endl;
    for (int b=0; b<BATCH_SIZE; b++) {
        for (int c=0; c<REDUCED_CHS; c++) {
            for (int i=0; i<1; i++) {
                for (int j=0; j<1; j++) {
                    cout << conv_reduce[b][c][i][j] << " ";
                }
            }
        }
        cout << endl;
    }

    //relu
    for (int b = 0; b < BATCH_SIZE; b++) {
        for (int c = 0; c < REDUCED_CHS; c++) {
            if (conv_reduce[b][c][0][0] < 0) {
                conv_reduce[b][c][0][0] = 0;
            }
        }
    }

    //expand: nn.Conv2d(reduced_chs, dim_in, 1, bias = False)
    //(b, reduced_chs, h_in, w_in) => (b, c_in, h_w)
    for (int batch = 0; batch < BATCH_SIZE; batch++) {
        for (int kernel_row = 0; kernel_row < KERNEL_SIZE; kernel_row++) {
            for (int kernel_col = 0; kernel_col < KERNEL_SIZE; kernel_col++) {
                for (int row = 0; row < 1; row++) {
                    for (int col = 0; col < 1; col++) {
                        for (int ch_out = 0; ch_out < CHANNEL_IN; ch_out++) {
                            for (int ch_in = 0; ch_in < REDUCED_CHS; ch_in++) {
                                conv_expand[batch][ch_out][row][col] += conv_reduce[batch][ch_in][row * STRIDE + kernel_row][col * STRIDE + kernel_col] * Kernel_2[ch_out][kernel_row][kernel_col];
                            }
                        }
                    }
                }
            }
        }
    }
    cout << "expand" << endl;
     for (int b=0; b<BATCH_SIZE; b++) {
        for (int c=0; c<CHANNEL_IN; c++) {
            cout << conv_expand[b][c][0][0] << " ";
        }
        cout << endl;
    }

    
    //sigmoid
    float tmp = 0;
    for (int b = 0; b < BATCH_SIZE; b++) {
        for (int c = 0; c < CHANNEL_IN; c++) {
            tmp = conv_expand[b][c][0][0];
            conv_expand[b][c][0][0] = 1 / (1 + exp(-tmp));
        }
    }
    cout << endl;
    cout << "sigmoid" << endl;
    for (int b=0; b<BATCH_SIZE; b++) {
        for (int c=0; c<CHANNEL_IN; c++) {
            cout << conv_expand[b][c][0][0] << " ";
        }
        cout << endl;
    }
    cout << endl;

    //x*sigmoid(x_se)
    //(2, 3, 4, 4) * (2, 3, 1, 1)
    float val = 0;
    for (int b = 0; b < BATCH_SIZE; b++) {
        for (int c = 0; c < CHANNEL_IN; c++) {
            val = conv_expand[b][c][0][0];
            for (int i = 0; i < HEIGHT_IN; i++) {
                for (int j = 0; j < WIDTH_IN; j++) {
                    result[b][c][i][j] = In[b][c][i][j] * val;
                }
            }
        }
    }
    //print the image
    for (int i=0; i<HEIGHT_IN; i++) {
        for (int j=0; j<WIDTH_IN; j++) {
            cout << In[0][0][i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
    //print the result
    for (int b=0; b<1; b++) {
        for (int c=0; c<1; c++) {
            for (int i=0; i<HEIGHT_IN; i++) {
                for (int j=0; j<WIDTH_IN; j++) {
                    cout << result[b][c][i][j] << ", ";
                }
                cout << endl;
            }
            cout << endl;
        }
    }
}