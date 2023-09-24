
// Includes

#include <stdint.h>
#include <hls_math.h>
#include <hls_stream.h>

#include "kernel_conv_norm_act.cpp"
#include "kernel_conv_norm_act2.cpp"
namespace{
// TRIPCOUNT identifier
const int BATCH_SIZE = 1;

const int CHANNEL_IN = 4;
const int CHANNEL_OUT = 8;
const int WIDTH_IN = 2;
const int HEIGHT_IN = 2;
//const int CHANNEL_OUT = 3;
const int WINDOW_SIZE = 7;
const int WINDOW_SIZE_W = WINDOW_SIZE <= 0 ? WIDTH_IN: WINDOW_SIZE;
const int WINDOW_SIZE_H = WINDOW_SIZE <= 0 ? HEIGHT_IN: WINDOW_SIZE;
const int pad_l = 0;
const int pad_t = 0;
const int pad_r = (WINDOW_SIZE_W - WIDTH_IN % WINDOW_SIZE_W) % WINDOW_SIZE_W;
const int pad_b = (WINDOW_SIZE_H - HEIGHT_IN % WINDOW_SIZE_H) % WINDOW_SIZE_H;
const int n1 = 1 ;// window_size_H
const int n2 = 1 ;// window_size_W

const int NEW_HEIGHT_IN = HEIGHT_IN+pad_t+pad_b;
const int NEW_WIDTH_IN = WIDTH_IN+pad_l+pad_r;
const int NEW_BATCH_SIZE = BATCH_SIZE * n1 * n2;
const int h1 =  7;// window_size_W
const int w1 =  7;// window_size_W
const int dim_head = 4;
const int HEIGHT_OUT = 7;
const int WIDTH_OUT = 7;
const int HEAD_SIZE = 1;
const int DIM_HEAD_SIZE = 4;
const int X_DIM_HEAD_SIZE = 4;
const int QK_SIZE = 2;
const int NEW_CHANNEL_OUT = 12;
const float scale = 1/sqrt(dim_head);

// Convolution parameters
//const int KERNEL_SIZE = 3;
//const int PADDING = 0;
//const int STRIDE = 1;
//const bool isBias = true;
//const bool isSkip = false;
//const int HEIGHT_OUT = (HEIGHT_IN - KERNEL_SIZE + 2 * PADDING) / STRIDE + 1;
//const int WIDTH_OUT = (WIDTH_IN - KERNEL_SIZE + 2 * PADDING) / STRIDE + 1;


// Coding Style: function宣告要為static，遇到for迴圈前可以取error_type的名稱(ex: mem_rd)
static void load_input(float* buffer_DataIn_1, float x[BATCH_SIZE][CHANNEL_IN][HEIGHT_IN][WIDTH_IN]){
    for(int i = 0; i < BATCH_SIZE; i++){
        for(int j = 0; j < CHANNEL_IN; j++){
            for(int k = 0; k < HEIGHT_IN; k++){
                for(int l = 0; l < WIDTH_IN; l++){
                    x[i][j][k][l] = buffer_DataIn_1[i * CHANNEL_IN * HEIGHT_IN * WIDTH_IN + j * HEIGHT_IN * WIDTH_IN + k * WIDTH_IN + l];
                }
            }
        }
    }
}
static void pad_f(float x[BATCH_SIZE][CHANNEL_IN][HEIGHT_IN][WIDTH_IN], float afterPad[BATCH_SIZE][CHANNEL_IN][NEW_HEIGHT_IN][NEW_WIDTH_IN]){
    for(int i = 0; i < BATCH_SIZE; i++){
        for(int j = 0; j < CHANNEL_IN; j++){
            for(int k = 0; k < NEW_HEIGHT_IN; k++){
                for(int l = 0; l < NEW_WIDTH_IN; l++){
                    afterPad[i][j][k][l] = 0;
                }
            }
        }
    }
    for(int i = 0; i < BATCH_SIZE; i++){
        for(int j = 0; j < CHANNEL_IN; j++){
            for(int k = 0; k < HEIGHT_IN; k++){
                for(int l = 0; l < WIDTH_IN; l++){
                    afterPad[i][j][k+pad_t][l+pad_l] = x[i][j][k][l];
                }
            }
        }
    }
}
// 'b (qk heads dim_head) h w -> qk b heads (h w) dim_head'
static void get_qk(float in_qk[BATCH_SIZE*n1*n2*CHANNEL_OUT*HEIGHT_OUT*WIDTH_OUT],
                       float in_q[BATCH_SIZE*n1*n2][HEAD_SIZE][HEIGHT_OUT*WIDTH_OUT][DIM_HEAD_SIZE],
                       float in_k[BATCH_SIZE*n1*n2][HEAD_SIZE][HEIGHT_OUT*WIDTH_OUT][DIM_HEAD_SIZE]
                       )
{
init_in:
	for (int qk = 0; qk < QK_SIZE; qk++)
    {
	    for (int b = 0; b < BATCH_SIZE*n1*n2; b++)
        {
            for (int c = 0; c < HEAD_SIZE; c++)
            {
                for (int dh = 0; dh < DIM_HEAD_SIZE; dh++)
                {
                    for (int h = 0; h < HEIGHT_OUT; h++){
                        for (int w = 0; w < WIDTH_OUT; w++){
                            if(qk==0)
                                in_q[b][c][h*WIDTH_OUT+w][dh] = in_qk[b * QK_SIZE * HEAD_SIZE * DIM_HEAD_SIZE * HEIGHT_OUT * WIDTH_OUT+
																			   qk * HEAD_SIZE * DIM_HEAD_SIZE * HEIGHT_OUT * WIDTH_OUT+
																			   c * DIM_HEAD_SIZE * HEIGHT_OUT * WIDTH_OUT + dh * HEIGHT_OUT * WIDTH_OUT +
																			   h * WIDTH_OUT +
																			   w];
                            else
                                in_k[b][c][h*WIDTH_OUT+w][dh] = in_qk[b * QK_SIZE * HEAD_SIZE * DIM_HEAD_SIZE * HEIGHT_OUT * WIDTH_OUT+
																			   qk * HEAD_SIZE * DIM_HEAD_SIZE * HEIGHT_OUT * WIDTH_OUT+
																			   c * DIM_HEAD_SIZE * HEIGHT_OUT * WIDTH_OUT + dh * HEIGHT_OUT * WIDTH_OUT +
																			   h * WIDTH_OUT +
																			   w];
                        }
                    }
                }
            }
        }
    }
}
// 'b c (h1 n1) (w1 n2) -> (b n1 n2) c h1 w1'
static void rearrangeX(float afterPad[BATCH_SIZE][CHANNEL_IN][NEW_HEIGHT_IN][NEW_WIDTH_IN], float afterRearrangeX[BATCH_SIZE*n1*n2*CHANNEL_IN*h1*w1]){
    for (int i = 0; i < BATCH_SIZE; i++)
    {
        for (int j = 0; j < CHANNEL_IN; j++)
        {
            for (int k = 0; k < h1; k++)
            {
                for (int l = 0; l < n1; l++){
                    for (int m = 0; m < w1; m++){
                        for (int n = 0; n < n2; n++){
                           afterRearrangeX[(i*n1*n2+l*n2+n)*CHANNEL_IN*h1*w1+j*h1*w1+k*w1+m] = afterPad[i][j][k*n1+l][m*n2+n];
                        }
                    }
                }
            }
        }

    }
}
//'b (heads dim_head) h w -> b heads (h w) dim_head'
static void rearrangeX2(float afterRearrangeX[BATCH_SIZE*n1*n2*CHANNEL_IN*h1*w1], float afterRearrangeX2[BATCH_SIZE*n1*n2][HEAD_SIZE][HEIGHT_OUT*WIDTH_OUT][X_DIM_HEAD_SIZE]){
    for (int i = 0; i < BATCH_SIZE*n1*n2; i++)
    {
        for (int j = 0; j < HEAD_SIZE; j++)
        {
            for (int k = 0; k < X_DIM_HEAD_SIZE; k++)
            {
                for (int l = 0; l < HEIGHT_OUT; l++)
                {
                    for (int m = 0; m < WIDTH_OUT; m++)
                    {
                        afterRearrangeX2[i][j][l*WIDTH_OUT+m][k] = afterRearrangeX[i*HEAD_SIZE*X_DIM_HEAD_SIZE*HEIGHT_OUT*WIDTH_OUT+(j*DIM_HEAD_SIZE+k)*HEIGHT_OUT*WIDTH_OUT+l*WIDTH_OUT+m];
                    }
                }
            }
        }

    }
}
/*
x = rearrange(
                x_spa, '(b n1 n2) c h1 w1 -> b c (h1 n1) (w1 n2)', n1=n1, n2=n2).contiguous()
            if pad_r > 0 or pad_b > 0:
                # :H, :W代表只有取到原本維度，後面多出來的(padding)就丟掉
                x = x[:, :, :H, :W].contiguous()
*/
static void rearrangeX3(float QKV[BATCH_SIZE*n1*n2 * NEW_CHANNEL_OUT * HEIGHT_OUT * WIDTH_OUT], float buffer_out[BATCH_SIZE][NEW_CHANNEL_OUT][h1*n1][w1*n2]){
    for (int i = 0; i < BATCH_SIZE; i++)
    {
        for (int j = 0; j < n1; j++)
        {
            for (int k = 0; k < n2; k++)
            {
                for (int l = 0; l < NEW_CHANNEL_OUT; l++)
                {
                    for (int m = 0; m < HEIGHT_OUT; m++)
                    {
                        for (int n = 0; n < WIDTH_OUT; n++)
                        {

                            buffer_out[i*n1*n2+j*n2+k][l][m][n] = QKV[(i*n1*n2+j*n2+k)*NEW_CHANNEL_OUT*HEIGHT_OUT * WIDTH_OUT + l *HEIGHT_OUT * WIDTH_OUT+m*WIDTH_OUT+n];

                        }
                    }
                }
            }
        }

    }
}

//'b heads (h w) dim_head -> b (heads dim_head) h w'
//b (heads dim_head) h w
static void rearrangeQKX(float afterQKXMultiplication[BATCH_SIZE*n1*n2][HEAD_SIZE][HEIGHT_OUT*WIDTH_OUT][X_DIM_HEAD_SIZE], float afterRearrangeQKX[BATCH_SIZE*n1*n2*HEAD_SIZE*HEIGHT_OUT*WIDTH_OUT*X_DIM_HEAD_SIZE]){
    for (int b = 0; b < BATCH_SIZE*n1*n2; b++)
    {
        for (int c = 0; c < HEAD_SIZE; c++)
        {
            for (int h = 0; h < HEIGHT_OUT; h++)
            {
                for (int w = 0; w < WIDTH_OUT; w++){
                    for (int x = 0; x < X_DIM_HEAD_SIZE; x++){
                            afterRearrangeQKX[b*X_DIM_HEAD_SIZE*WIDTH_OUT*HEIGHT_OUT*HEAD_SIZE+(c*X_DIM_HEAD_SIZE+x)*HEIGHT_OUT*WIDTH_OUT+h*WIDTH_OUT+w] = afterQKXMultiplication[b][c][h*WIDTH_OUT+w][x];
                        }
                }
            }
        }

    }
}
static void compute_multiplicationQK(float in_q[BATCH_SIZE*n1*n2][HEAD_SIZE][HEIGHT_OUT*WIDTH_OUT][DIM_HEAD_SIZE],
                        float in_k[BATCH_SIZE*n1*n2][HEAD_SIZE][HEIGHT_OUT*WIDTH_OUT][DIM_HEAD_SIZE],
                        float afterQKMultiplication[BATCH_SIZE*n1*n2][HEAD_SIZE][HEIGHT_OUT*WIDTH_OUT][HEIGHT_OUT*WIDTH_OUT])
{
execute:
    for(int b = 0; b < BATCH_SIZE*n1*n2; b++){
        for(int c = 0;c < HEAD_SIZE; c++){
            float sum[HEIGHT_OUT*WIDTH_OUT][HEIGHT_OUT*WIDTH_OUT]={};
            for(int i = 0; i < HEIGHT_OUT*WIDTH_OUT; i++){
                for(int j = 0; j < DIM_HEAD_SIZE; j++){
                    for(int k = 0; k < HEIGHT_OUT*WIDTH_OUT; k++){
                        sum[i][k]+=in_q[b][c][i][j]*in_k[b][c][k][j]*scale;
                    }
                }
            }
            for(int i = 0; i < HEIGHT_OUT*WIDTH_OUT; i++){
                for(int k = 0; k < HEIGHT_OUT*WIDTH_OUT; k++){
                    afterQKMultiplication[b][c][i][k] = sum[i][k];
                    sum[i][k]=0;
                }
            }
        }
    }
}
static void compute_multiplicationQKX(float afterSoftmax[BATCH_SIZE*n1*n2][HEAD_SIZE][HEIGHT_OUT*WIDTH_OUT][HEIGHT_OUT*WIDTH_OUT],
                                      float afterRearrange[BATCH_SIZE*n1*n2][HEAD_SIZE][HEIGHT_OUT*WIDTH_OUT][X_DIM_HEAD_SIZE],
                                      float afterQKXMultiplication[BATCH_SIZE*n1*n2][HEAD_SIZE][HEIGHT_OUT*WIDTH_OUT][X_DIM_HEAD_SIZE])
{
execute:

    for(int b = 0; b < BATCH_SIZE*n1*n2; b++){
        for(int c = 0;c < HEAD_SIZE; c++){
        	float sum[HEIGHT_OUT*WIDTH_OUT][X_DIM_HEAD_SIZE]={};
            for(int i = 0; i < HEIGHT_OUT*WIDTH_OUT; i++){
                for(int j = 0; j < HEIGHT_OUT*WIDTH_OUT; j++){
                    for(int k = 0; k < X_DIM_HEAD_SIZE; k++){
                    	sum[i][k]+=afterSoftmax[b][c][i][j]*afterRearrange[b][c][j][k];
                    }
                }
            }
            for(int i = 0; i < HEIGHT_OUT*WIDTH_OUT; i++){
				for(int k = 0; k < X_DIM_HEAD_SIZE; k++){
					afterQKXMultiplication[b][c][i][k] = sum[i][k];
					sum[i][k]=0;
				}
			}

        }
    }
}
static void load_softmax(float in[BATCH_SIZE*n1*n2][HEAD_SIZE][HEIGHT_OUT*WIDTH_OUT][HEIGHT_OUT*WIDTH_OUT], float out[BATCH_SIZE*n1*n2][HEAD_SIZE][HEIGHT_OUT*WIDTH_OUT][HEIGHT_OUT*WIDTH_OUT]) {
mem_rd:
    for (int b = 0; b < BATCH_SIZE*n1*n2; b++) {
        for (int h = 0; h < HEAD_SIZE; h++) {
            for (int hw = 0; hw < HEIGHT_OUT*WIDTH_OUT; hw++) {
                for (int i = 0; i < HEIGHT_OUT*WIDTH_OUT; i++) {
                    float tmp = in[b][h][hw][i];
                    /*float expo = 1;
                    int neg = tmp>=0?0:1;
                    if(neg)tmp = -tmp;
                    if(tmp>=9) expo*=8103.083928,tmp-=9;//e^9
                    else if(tmp>=8) expo*=2980.957987,tmp-=8;//e^8
                    else if(tmp>=7) expo*=1096.633158,tmp-=7;//e^7
                    else if(tmp>=6) expo*=403.428793,tmp-=6;//e^6
                    else if(tmp>=5) expo*=148.413159,tmp-=5;//e^5
                    else if(tmp>=4) expo*=54.598150,tmp-=4;//e^4
                    else if(tmp>=3) expo*=20.085537,tmp-=3;//e^3
                    else if(tmp>=2) expo*=7.389056,tmp-=2;//e^2
                    else if(tmp>=1) expo*=2.718282,tmp-=1;//e^1
                    //if tmp>=0 expo =expo,tmp-=0

                    if(tmp>=0.9) expo*=2.459603,tmp-=0.9;//e^0.9
                    else if(tmp>=0.8) expo*=2.225541,tmp-=0.8;//e^0.8
                    else if(tmp>=0.7) expo*=2.013753,tmp-=0.7;//e^0.7
                    else if(tmp>=0.6) expo*=1.822119,tmp-=0.6;//e^0.6
                    else if(tmp>=0.5) expo*=1.648721,tmp-=0.5;//e^0.5
                    else if(tmp>=0.4) expo*=1.491825,tmp-=0.4;//e^0.4
                    else if(tmp>=0.3) expo*=1.349859,tmp-=0.3;//e^0.3
                    else if(tmp>=0.2) expo*=1.221403,tmp-=0.2;//e^0.2
                    else if(tmp>=0.1) expo*=1.105171,tmp-=0.1;//e^0.1

                    //do the rounding
                    if(tmp>=0.085) expo*=1.094174;//e^0.09
                    else if(tmp>=0.075) expo*=1.083287;//e^0.08
                    else if(tmp>=0.065) expo*=1.072508;//e^0.07
                    else if(tmp>=0.055) expo*=1.061837;//e^0.06
                    else if(tmp>=0.045) expo*=1.051271;//e^0.05
                    else if(tmp>=0.035) expo*=1.040811;//e^0.04
                    else if(tmp>=0.025) expo*=1.030455;//e^0.03
                    else if(tmp>=0.015) expo*=1.020201;//e^0.02
                    else if(tmp>=0.005) expo*=1.010050;//e^0.01

                    if(neg)out[b][h][hw][i] = 1/expo;
                    else out[b][h][hw][i] = expo;*/
                    out[b][h][hw][i] = exp(tmp);
                    //std::cout<<out[b][h][hw][i]<<"\n";
                }
            }
        }
    }
}
static void compute_softmax(float inStream[BATCH_SIZE*n1*n2][HEAD_SIZE][HEIGHT_OUT*WIDTH_OUT][HEIGHT_OUT*WIDTH_OUT],
                        float out_stream[BATCH_SIZE*n1*n2][HEAD_SIZE][HEIGHT_OUT*WIDTH_OUT][HEIGHT_OUT*WIDTH_OUT]) {

gen_output2:
    float tmp_in[HEIGHT_OUT*WIDTH_OUT];
    float sum = 0;
    for(int b = 0; b < BATCH_SIZE; ++b){
        for(int h = 0; h < HEAD_SIZE; ++h){
            for (int i = 0; i < HEIGHT_OUT*WIDTH_OUT; ++i) {
            count_sum:
                for (int j = 0; j < HEIGHT_OUT*WIDTH_OUT; ++j) {
                    tmp_in[j] = inStream[b][h][i][j];
                    sum += tmp_in[j];
                }
            divide:
                for (int j = 0; j < HEIGHT_OUT*WIDTH_OUT; ++j) {
                    if(sum==0){
                        out_stream[b][h][i][j] = 0;
                    }
                    else{
                        out_stream[b][h][i][j] = tmp_in[j]/sum;
                    }

                }
                sum = 0;
            }
        }
    }
}
static void krnl_softmax(float afterQKMultiplication[BATCH_SIZE*n1*n2][HEAD_SIZE][HEIGHT_OUT*WIDTH_OUT][HEIGHT_OUT*WIDTH_OUT],float afterSoftmax[BATCH_SIZE][HEAD_SIZE][HEIGHT_OUT*WIDTH_OUT][HEIGHT_OUT*WIDTH_OUT]){
    float in1_stream[BATCH_SIZE*n1*n2][HEAD_SIZE][HEIGHT_OUT*WIDTH_OUT][HEIGHT_OUT*WIDTH_OUT];

    // dataflow pragma instruct compiler to run following three APIs in parallel
    load_softmax(afterQKMultiplication, in1_stream);
    compute_softmax(in1_stream, afterSoftmax);
}

static void store_result(float buffer_out[BATCH_SIZE][NEW_CHANNEL_OUT][HEIGHT_OUT][WIDTH_OUT],float* buffer_result){
    for(int i=0;i<BATCH_SIZE;i++){
        for(int j=0;j<NEW_CHANNEL_OUT;j++){
            for(int k=0;k<HEIGHT_OUT;k++){
                for(int l=0;l<WIDTH_OUT;l++){
                    if(k<HEIGHT_IN&&l<WIDTH_IN)
                        buffer_result[i*NEW_CHANNEL_OUT*HEIGHT_IN*WIDTH_IN+j*HEIGHT_IN*WIDTH_IN+k*WIDTH_IN+l] = buffer_out[i][j][k][l];
                }
            }
        }
    }
}
    /*
        Vector Addition Kernel

        Arguments:
            in1  (input)  --> Input vector 1
            in2  (input)  --> Input vector 2
            out  (output) --> Output vector
            size (input)  --> Number of elements in vector
    */
extern "C"
{

void kernel_attention(float *buffer_DataIn_1,
                              float *buffer_result)
    {
#pragma HLS INTERFACE m_axi port = buffer_DataIn_1 bundle = gmem0 depth = 64;
#pragma HLS INTERFACE m_axi port = buffer_result bundle = gmem0 depth = 192;
        // dataflow pragma instruct compiler to run following three APIs in parallel
        float x[BATCH_SIZE][CHANNEL_IN][HEIGHT_IN][WIDTH_IN];
        float afterPad[BATCH_SIZE][CHANNEL_IN][NEW_HEIGHT_IN][NEW_WIDTH_IN];
        float afterRearrangeX[BATCH_SIZE*n1*n2*CHANNEL_IN*h1*w1];
        float in_qk[BATCH_SIZE*n1*n2*CHANNEL_OUT*HEIGHT_OUT*WIDTH_OUT];
        float in_q[BATCH_SIZE*n1*n2][HEAD_SIZE][HEIGHT_OUT*WIDTH_OUT][DIM_HEAD_SIZE];
        float in_k[BATCH_SIZE*n1*n2][HEAD_SIZE][HEIGHT_OUT*WIDTH_OUT][DIM_HEAD_SIZE];
        float afterQKMultiplication[BATCH_SIZE*n1*n2][HEAD_SIZE][HEIGHT_OUT*WIDTH_OUT][HEIGHT_OUT*WIDTH_OUT];
        float afterSoftmax[BATCH_SIZE*n1*n2][HEAD_SIZE][HEIGHT_OUT*WIDTH_OUT][HEIGHT_OUT*WIDTH_OUT];
        float afterRearrangeX2[BATCH_SIZE*n1*n2][HEAD_SIZE][HEIGHT_OUT*WIDTH_OUT][X_DIM_HEAD_SIZE];
        float afterQKXMultiplication[BATCH_SIZE*n1*n2][HEAD_SIZE][HEIGHT_OUT*WIDTH_OUT][X_DIM_HEAD_SIZE];
        float afterRearrangeQKX[BATCH_SIZE*n1*n2*HEAD_SIZE*HEIGHT_OUT*WIDTH_OUT*X_DIM_HEAD_SIZE];
        float QKV[BATCH_SIZE*n1*n2 * NEW_CHANNEL_OUT * HEIGHT_OUT * WIDTH_OUT];
        float buffer_out[BATCH_SIZE][NEW_CHANNEL_OUT][h1*n1][w1*n2];


        load_input(buffer_DataIn_1, x);
        pad_f(x, afterPad);
        rearrangeX(afterPad, afterRearrangeX);
        kernel_conv_norm_act(afterRearrangeX, in_qk);
        get_qk(in_qk, in_q, in_k);
        compute_multiplicationQK(in_q, in_k, afterQKMultiplication);
        krnl_softmax(afterQKMultiplication, afterSoftmax);
        rearrangeX2(afterRearrangeX, afterRearrangeX2);
        compute_multiplicationQKX(afterSoftmax, afterRearrangeX2, afterQKXMultiplication);
        rearrangeQKX(afterQKXMultiplication, afterRearrangeQKX);
        kernel_conv_norm_act2(afterRearrangeQKX, QKV);
        rearrangeX3(QKV, buffer_out);
        store_result(buffer_out,buffer_result);
    }

}
}
