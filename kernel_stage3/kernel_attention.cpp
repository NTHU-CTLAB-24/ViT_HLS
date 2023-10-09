
// Includes

#include <stdint.h>
#include "kernel_stage1.hpp"

//#include "kernel_conv_norm_act.cpp"
//#include "kernel_conv_norm_act2.cpp"
//#include "kernel_conv_norm_act0.cpp"
// TRIPCOUNT identifier
// TRIPCOUNT identifier
/*const int BATCH_SIZE = 1;

const int CHANNEL_IN = 4;
const int CHANNEL_OUT = 8;
const int WIDTH_IN = 16;
const int HEIGHT_IN = 16;
//const int CHANNEL_OUT = 3;
const int WINDOW_SIZE = 7;
const int WINDOW_SIZE_W = WINDOW_SIZE <= 0 ? WIDTH_IN: WINDOW_SIZE;
const int WINDOW_SIZE_H = WINDOW_SIZE <= 0 ? HEIGHT_IN: WINDOW_SIZE;
const int pad_l = 0;
const int pad_t = 0;
const int pad_r = (WINDOW_SIZE_W - WIDTH_IN % WINDOW_SIZE_W) % WINDOW_SIZE_W;
const int pad_b = (WINDOW_SIZE_H - HEIGHT_IN % WINDOW_SIZE_H) % WINDOW_SIZE_H;
const int n1 = 3 ;// window_size_H
const int n2 = 3 ;// window_size_W

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
*/
// Convolution parameters
//const int KERNEL_SIZE = 3;
//const int PADDING = 0;
//const int STRIDE = 1;
//const bool isBias = true;
//const bool isSkip = false;
//const int HEIGHT_OUT = (HEIGHT_IN - KERNEL_SIZE + 2 * PADDING) / STRIDE + 1;
//const int WIDTH_OUT = (WIDTH_IN - KERNEL_SIZE + 2 * PADDING) / STRIDE + 1;

void pad_f(float* x, float* afterPad, int* X_num, int* padding){
    int B = X_num[0];//BATCH_SIZE
    int C = X_num[1];//CHANNEL_IN
    int H = X_num[2];//HEIGHT_IN
    int W = X_num[3];//WIDTH_IN
    int NH = X_num[2] + padding[1] + padding[3];//NEW_HEIGHT_IN                       pad l t r b
    int NW = X_num[3] + padding[0] + padding[2];//NEW_WIDTH_IN
    /*for(int i = 0; i < B; i++){
        for(int j = 0; j < C; j++){
            for(int k = 0; k < NH; k++){
                for(int l = 0; l < NW; l++){
                    afterPad[i * C * NH * NW + j * NH * NW + k * NW + l] = 0;
                }
            }
        }
    }*/
    for(int i = 0; i < B; i++){
        for(int j = 0; j < C; j++){
            for(int k = 0; k < H; k++){
                for(int l = 0; l < W; l++){
                    afterPad[i * C * NH * NW + j * NH * NW + (k + padding[1]) * NW + (l + padding[0])] = x[i * C * H * W + j * H * W + k * W + l];
                }
            }
        }
    }
}
// 'b (qk heads dim_head) h w -> qk b heads (h w) dim_head'
void get_qk(float* in_qk,float* in_q,float* in_k,int* X_num)
{
    int QK = X_num[0];//QK_SIZE
    int B = X_num[1];//BATCH_SIZE*n1*n2
    int C = X_num[2];//HEAD_SIZE
    int DH = X_num[3];//DIM_HEAD_SIZE
    int H = X_num[4];//HEIGHT_OUT
    int W = X_num[5];//WIDTH_OUT

init_in:
	for (int qk = 0; qk < QK; qk++)
    {
	    for (int b = 0; b < B; b++)
        {
            for (int c = 0; c < C; c++)
            {
                for (int dh = 0; dh < DH; dh++)
                {
                    for (int h = 0; h < H; h++)
                    {
                        for (int w = 0; w < W; w++)
                        {
                            if(qk==0)
                                in_q[b * DH * W * H * C + c * DH * W * H + (h * W + w) * DH + dh]
                                                                             = in_qk[b * QK * C * DH * H * W+
																			   qk * C * DH * H * W+
																			   c * DH * H * W + dh * H * W +
																			   h * W +
																			   w];
                            else
                                in_k[b * DH * W * H * C + c * DH * W * H + (h * W + w) * DH + dh]
                                                                             = in_qk[b * QK * C * DH * H * W+
																			   qk * C * DH * H * W+
																			   c * DH * H * W + dh * H * W +
																			   h * W +
																			   w];
                        }
                    }
                }
            }
        }
    }
}
// 'b c (h1 n1) (w1 n2) -> (b n1 n2) c h1 w1'
void rearrangeX(float* afterPad, float* afterRearrangeX, int* X_num){
    int B = X_num[0];//BATCH_SIZE
    int C = X_num[1];//CHANNEL_IN
    int H1 = X_num[2];//h1
    int W1 = X_num[3];//w1
    int N1 = X_num[4];//n1
    int N2 = X_num[5];//n2
    for (int i = 0; i < B; i++)
    {
        for (int j = 0; j < C; j++)
        {
            for (int k = 0; k < H1; k++)
            {
                for (int l = 0; l < N1; l++)
                {
                    for (int m = 0; m < W1; m++)
                    {
                        for (int n = 0; n < N2; n++)
                        {
                           afterRearrangeX[(i * N1 * N2 + l * N2 + n) * C * H1 * W1 + j * H1 * W1 + k * W1 + m] = 
                           afterPad[i * H1 * N1 * W1 * N2 * C + j * H1 * N1 * W1 * N2 + (k * N1 + l) * W1 * N2 + m * N2 + n];
                        }
                    }
                }
            }
        }

    }
}
//'b (heads dim_head) h w -> b heads (h w) dim_head'
void rearrangeX2(float* afterRearrangeX, float* afterRearrangeX2, int* X_num){
    int B = X_num[0];//BATCH_SIZE*n1*n2
    int C = X_num[1];//HEAD_SIZE
    int XDH = X_num[2];//X_DIM_HEAD_SIZE
    int H = X_num[3];//HEIGHT_OUT
    int W = X_num[4];//WIDTH_OUT
    for (int i = 0; i < B; i++)
    {
        for (int j = 0; j < C; j++)
        {
            for (int k = 0; k < XDH; k++)
            {
                for (int l = 0; l < H; l++)
                {
                    for (int m = 0; m < W; m++)
                    {
                        afterRearrangeX2[i * XDH * W * H * C+
                                        j * XDH * W * H + (l * W + m) * XDH + k] 
                                = afterRearrangeX[i * C * XDH * H * W + (j * XDH + k) * H * W + l * W + m];
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
void rearrangeX3(float* QKV, float* buffer_out, int* X_num){
    int B = X_num[0];//BATCH_SIZE
    int C = X_num[1];//NEW_CHANNEL_OUT
    int N1 = X_num[2];//n1
    int N2 = X_num[3];//n2
    int H = X_num[4];//HEIGHT_OUT
    int W = X_num[5];//WIDTH_OUT
    for (int i = 0; i < B; i++)
    {
        for (int j = 0; j < N1; j++)
        {
            for (int k = 0; k < N2; k++)
            {
                for (int l = 0; l < C; l++)
                {
                    for (int m = 0; m < H; m++)
                    {
                        for (int n = 0; n < W; n++)
                        {

                            buffer_out[i * N2 * W * N1 * H * C + l * N2 * W * N1 * H + (m * N1 + j) * N2 * W + n * N2 + k] = 
                              QKV[(i * N1 * N2 + j * N2 + k) * C * H * W + l *H * W + m * W + n];

                        }
                    }
                }
            }
        }

    }
}

//'b heads (h w) dim_head -> b (heads dim_head) h w'
//b (heads dim_head) h w
void rearrangeQKX(float* afterQKXMultiplication, float* afterRearrangeQKX, int* X_num){
    int B = X_num[0];//BATCH_SIZE*n1*n2
    int C = X_num[1];//HEAD_SIZE
    int H = X_num[2];//HEIGHT_OUT
    int W = X_num[3];//WIDTH_OUT
    int XC = X_num[4];//X_DIM_HEAD_SIZE
    for (int b = 0; b < B; b++)
    {
        for (int c = 0; c < C; c++)
        {
            for (int h = 0; h < H; h++)
            {
                for (int w = 0; w < W; w++){
                    for (int x = 0; x < XC; x++){
                            afterRearrangeQKX[b * XC * W * H * C + (c * XC + x) * H * W + h * W + w] = 
                              afterQKXMultiplication[b * XC * W * H * C + c * XC * W * H + (h * W + w) * XC + x];
                        }
                }
            }
        }

    }
}
void compute_multiplication(float* in_q, float* in_k, float* afterQKMultiplication,float* sum, int* X_num, float scale, int times)
{
    int B = X_num[0];//BATCH_SIZE*n1*n2
    int C = X_num[1];//HEAD_SIZE
    int H = X_num[2];//HEIGHT_OUT*WIDTH_OUT
    int W = X_num[3];//DIM_HEAD_SIZE
    int NW = X_num[4];//HEIGHT_OUT*WIDTH_OUT
execute:
    for(int b = 0; b < B; b++){
        for(int c = 0;c < C; c++){
            //float sum[H*NW]={};
            for(int i = 0; i < H; i++){
                for(int j = 0; j < W; j++){
                    for(int k = 0; k < NW; k++){
                    	if(times==1){
                    		sum[i*NW+k]+=in_q[b * C * H * W + c * H * W + i * W + j]
                                   *in_k[b * C * W * NW + c * W * NW + k * W + j]*scale;
                    	}
                    	else{
                    		sum[i*NW+k]+=in_q[b * C * H * W + c * H * W + i * W + j]
                    		                                   *in_k[b * C * W * NW + c * W * NW + j * NW + k]*scale;
                    	}
					}
                }
            }
            for(int i = 0; i < H; i++){
                for(int k = 0; k < NW; k++){
                    afterQKMultiplication[b * H * NW * C + c * H * NW + i * NW+ k] = sum[i*NW+k];
                    sum[i*NW+k]=0;
                }
            }
        }
    }
}
void load_softmax(float* in, float* out, int* X_num) {
    int B = X_num[0];//BATCH_SIZE*n1*n2
    int C = X_num[1];//HEAD_SIZE
    int H = X_num[2];//HEIGHT_OUT*WIDTH_OUT
    int W = X_num[3];//HEIGHT_OUT*WIDTH_OUT
mem_rd:
    for (int b = 0; b < B; b++) {
        for (int h = 0; h < C; h++) {
            for (int hw = 0; hw < H; hw++) {
                for (int i = 0; i < W; i++) {
                    float tmp = in[b * H * W * C + h * H * W + hw * W + i];
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
                    out[b * H * W * C + h * H * W + hw * W + i] = exp(tmp);
                    //std::cout<<out[b][h][hw][i]<<"\n";
                }
            }
        }
    }
}
void compute_softmax(float* inStream,float* out_stream, int* X_num)
{
    int B = X_num[0];//BATCH_SIZE*n1*n2
    int C = X_num[1];//HEAD_SIZE
    int H = X_num[2];//HEIGHT_OUT*WIDTH_OUT
    int W = X_num[3];//HEIGHT_OUT*WIDTH_OUT
gen_output2:
    //float tmp_in[W];
    float sum = 0;
    for(int b = 0; b < B; ++b){
        for(int h = 0; h < C; ++h){
            for (int i = 0; i < H; ++i) {
            count_sum:
                for (int j = 0; j < W; ++j) {
                    //tmp_in[j] = inStream[b * H * W * C + h * H * W + i * W + j];
                    sum += inStream[b * H * W * C + h * H * W + i * W + j];
                }
            divide:
                for (int j = 0; j < W; ++j) {
                    if(sum==0){
                        out_stream[b * W * H * C + h * H * W + i * W + j] = 0;
                    }
                    else{
                        out_stream[b * H * W * C + h * H * W + i * W + j] = inStream[b * H * W * C + h * H * W + i * W + j] / sum;
                    }

                }
                sum = 0;
            }
        }
    }
}
void krnl_softmax(float* afterQKMultiplication, float* in1_stream, float* afterSoftmax, int* X_num){
    //float in1_stream[BATCH_SIZE*n1*n2*HEAD_SIZE*HEIGHT_OUT*WIDTH_OUT*HEIGHT_OUT*WIDTH_OUT];

    // dataflow pragma instruct compiler to run following three APIs in parallel
    load_softmax(afterQKMultiplication, in1_stream, X_num);
    compute_softmax(in1_stream, afterSoftmax, X_num);
}

void store_result(float* buffer_out,float* buffer_result, int* X_num){
    //std::cout<<BATCH_SIZE<<" "<<NEW_CHANNEL_OUT<<" "<<HEIGHT_OUT*n1<<" "<<WIDTH_OUT*n2<<"\n";
   // std::cout<<BATCH_SIZE * NEW_CHANNEL_OUT * HEIGHT_OUT * WIDTH_OUT<<"\n";
    int B = X_num[0];//BATCH_SIZE
    int C = X_num[1];//NEW_CHANNEL_OUT
    int H = X_num[2];//HEIGHT_IN
    int W = X_num[3];//WIDTH_IN
    int NH = X_num[4];//HEIGHT_OUT*n1
    int NW = X_num[5];//WIDTH_OUT*n2
    for(int i = 0; i < B; i++){
        for(int j = 0; j < C; j++){
            for(int k = 0; k < NH; k++){
                for(int l = 0; l < NW; l++){
                    if(k < H && l < W){
                        //std::cout<<i<<" "<<j<<" "<<k<<" "<<l<<" "<<i*C*H*W+j*H*W+k*W+l<<"\n";
                        buffer_result[i * C * H * W + j * H * W + k * W + l] = 
                        buffer_out[i * NW * NH * C + j * NW * NH + k * NW + l];
                    }
                }
            }
        }
    }
}
void compute_PADDING(float* in, float* in_pad, int* X_num)
{
    //float in[BATCH_SIZE1][CHANNEL_IN1][HEIGHT_IN1][WIDTH_IN1]
    //float in_pad[BATCH_SIZE1][CHANNEL_IN1][new_HEIGHT_IN1][new_WIDTH_IN1]
    //int PADDING = X_num[0];
    int B = X_num[0];//BATCH_SIZE
    int C = X_num[1];//NEW_CHANNEL_OUT
    int H = X_num[2];//HEIGHT_IN
    int W = X_num[3];//WIDTH_IN
    
    int KERNEL_SIZE = X_num[4];
    int STRIDE = X_num[5];
    
    int PADDING = (KERNEL_SIZE - STRIDE) % 2 == 0 ? (KERNEL_SIZE - STRIDE) / 2 : (KERNEL_SIZE - STRIDE) / 2 + 1;
    int NH = H + 2 * PADDING;
    int NW = W + 2 * PADDING;
    //int HO = (H - KERNEL_SIZE + 2 * PADDING) / STRIDE + 1;
    //int WO = (W - KERNEL_SIZE + 2 * PADDING) / STRIDE + 1;
    /*
    const int PADDING1 = (KERNEL_SIZE1 - STRIDE1) % 2 == 0 ? (KERNEL_SIZE1 - STRIDE1) / 2 : (KERNEL_SIZE1 - STRIDE1) / 2 + 1;
    const int new_HEIGHT_IN1 = HEIGHT_IN1 + 2 * PADDING1;
    const int new_WIDTH_IN1 = WIDTH_IN1 + 2 * PADDING1;
    const int HEIGHT_OUT1 = (HEIGHT_IN1 - KERNEL_SIZE1 + 2 * PADDING1) / STRIDE1 + 1;
    const int WIDTH_OUT1 = (WIDTH_IN1 - KERNEL_SIZE1 + 2 * PADDING1) / STRIDE1 + 1;
    */
PADDING1:
    for (int n = 0; n < B; n++)
    {
        for (int c = 0; c < C; c++)
        {
            for (int h = 0; h < NH; h++)
            {
                for (int w = 0; w < NW; w++)
                {
                    if (h < PADDING || h >= H + PADDING || W < PADDING || w >= W + PADDING)
                        in_pad[n*C*NH*NW+c*NH*NW+h*NW+w] = 0;
                    else
                        in_pad[n*C*NH*NW+c*NH*NW+h*NW+w] = in[n*C*H*W+c*H*W+(h - PADDING)*W+w - PADDING];
                }
            }
        }
    }
}
/*
    float in_pad[BATCH_SIZE1][CHANNEL_IN1][new_HEIGHT_IN1][new_WIDTH_IN1],
                         float afterConv[BATCH_SIZE1][CHANNEL_OUT1][HEIGHT_OUT1][WIDTH_OUT1],
                         float kernel[CHANNEL_OUT1][KERNEL_CHANNEL1][KERNEL_SIZE1][KERNEL_SIZE1],
                         float bias[CHANNEL_OUT1]
    */
    //float kernel[CHANNEL_OUT1][KERNEL_CHANNEL1][KERNEL_SIZE1][KERNEL_SIZE1];
    //float bias[CHANNEL_OUT1];

/*init_kernel_bias:
    for (int k = 0; k < CHANNEL_OUT1; k++)
    {
        bias[k] = k + 0.5;
        for (int l = 0; l < KERNEL_CHANNEL1; l++)
        {
            for (int i = 0; i < KERNEL_SIZE1; i++)
            {
                for (int j = 0; j < KERNEL_SIZE1; j++)
                {
                    kernel[k][l][i][j] = (k+j+i+l)*0.1;
                }
            }
        }
    }*/
void compute_conv(float* in_pad, float* afterConv, float* kernel, float* bias, int* X_num, int isBias1)
{
    int B = X_num[0];//BATCH*n1*n2
    int C = X_num[1];//CHANNEL_OUT
    int H = X_num[2];//HEIGHT_OUT
    int W = X_num[3];//
    int K = X_num[4];//KERNEL_SIZE1
    int CI = X_num[5];//CHANNEL_IN
    int HI = X_num[6];//CHANNEL_IN
    int WI = X_num[7];//CHANNEL_IN
    int IGN = X_num[8];//inGROUP1Nums1
    int OGN = X_num[9];//outGROUP1Nums1
    int S = X_num[10];//STRIDE1
    int KC = X_num[11];//KERNEL_CHANNEL
init_output:
    for (int n = 0; n < B; n++)
    {
        for (int c = 0; c < C; c++)
        {
            for (int h = 0; h < H; h++)
            {
                for (int w = 0; w < W; w++)
                {
                    if (isBias1)
                        afterConv[n*C*H*W+c*H*W+h*W+w] = bias[c];
                    else
                        afterConv[n*C*H*W+c*H*W+h*W+w] = 0;
                }
            }
        }
    }

execute:
Batch:
    for (int batch = 0; batch < B; batch++)
    {
    Out_Row:
        for (int row = 0; row < H; row++)
        {
        Out_Column:
            for (int col = 0; col < W; col++)
            {
            Kernel_Row:
                for (int kernel_row = 0; kernel_row < K; kernel_row++)
                {
                Kernel_Col:
                    for (int kernel_col = 0; kernel_col < K; kernel_col++)
                    {
                        int GROUP1Index = 0;
                    Output_Channel:
                        for (int out_ch = 0; out_ch < C; out_ch++)
                        {
                            int kernelChannelIdx = 0;
                        In_Channel:
                            for (int in_ch = GROUP1Index * IGN; in_ch < CI; in_ch++)
                            {
                                afterConv[batch * C * W * H + out_ch * W * H + row * W + col] += 
                                    in_pad[batch * CI * HI * WI + in_ch * HI * WI + (row * S + kernel_row) * WI + col * S + kernel_col] * 
                                    kernel[out_ch*KC*K*K+kernelChannelIdx*K+kernel_row*K+kernel_col];
                                kernelChannelIdx++;
                                if ((in_ch + 1) % IGN == 0)
                                    break;
                            }
                            if ((out_ch + 1) % OGN == 0)
                                GROUP1Index++;
                        }
                    }
                }
            }
        }
    }
}
static void compute_norm(float* afterConv, float* afterNorm, float* RUNNING_MEAN, float* RUNNING_VAR, float* weight, float* bias, float* ln_in, int* X_num, int NORM_LAYER)
{
    /*
    float* afterConv[BATCH_SIZE2][CHANNEL_OUT2][HEIGHT_OUT2][WIDTH_OUT2],
    float* afterNorm[BATCH_SIZE2][CHANNEL_OUT2][HEIGHT_OUT2][WIDTH_OUT2]
    float ln_in[BATCH_SIZE0][HEIGHT_IN0][WIDTH_IN0][CHANNEL_IN0];
    float weight[HEIGHT_IN0][WIDTH_IN0][CHANNEL_IN0];
    float bias[HEIGHT_IN0][WIDTH_IN0][CHANNEL_IN0];
    float mean[BATCH_SIZE0*HEIGHT_IN0*WIDTH_IN0];
    float var[BATCH_SIZE0*HEIGHT_IN0*WIDTH_IN0];
*/
    int B = X_num[0];//
    int C = X_num[1];//
    int H = X_num[2];//
    int W = X_num[3];//
init_output:

    switch (NORM_LAYER)
    {
    case 0: {
        //float RUNNING_MEAN[C];
        //float RUNNING_VAR[C];
        //float weight[C];
        //float bias[C];

    init_parameters:
        /*for (int c = 0; c < CHANNEL_OUT2; c++)
        {
            RUNNING_MEAN[c] = 8;
            RUNNING_VAR[c] = 21.5;
            weight[c] = 0.5;
            bias[c] = 0.2;
        }*/

    Batch_norm:
        for (int n = 0; n < B; n++)
        {
            for (int c = 0; c < C; c++)
            {
                for (int h = 0; h < H; h++)
                {
                    for (int w = 0; w < W; w++)
                    {
                        afterNorm[n*C*H*W + c*H*W + h*W+w] = ((afterConv[n*C*H*W+c*H*W+h*W+w] - RUNNING_MEAN[c]) / sqrt(RUNNING_VAR[c] + 1e-6)) * weight[c] + bias[c];
                    }
                }
            }
        }
        break;
    }

    case 1: {
        /*float ln_in[BATCH_SIZE0][HEIGHT_IN0][WIDTH_IN0][CHANNEL_IN0];
        float weight[HEIGHT_IN0][WIDTH_IN0][CHANNEL_IN0];
        float bias[HEIGHT_IN0][WIDTH_IN0][CHANNEL_IN0];
        float mean[BATCH_SIZE0*HEIGHT_IN0*WIDTH_IN0];
        float var[BATCH_SIZE0*HEIGHT_IN0*WIDTH_IN0];*/

    Reshape:
        for (int n = 0; n < B; n++)
        {
            for (int c = 0; c < C; c++)
            {
                for (int h = 0; h < H; h++)
                {
                    for (int w = 0; w < W; w++)
                    {
                        ln_in[n*C*H*W + h*W*C + w*C + c] = afterConv[n*C*H*W + c*H*W + h*W+w];
                    }
                }
            }
        }

        int total =  C;
    Layer_Norm_Init:
        for (int n = 0; n < B; n++)
        {

            for (int h = 0; h < H; h++)
            {
                for (int w = 0; w < W; w++)
                {
                    float sum = 0;
                    float squareSum = 0;
                    for (int c = 0; c < C; c++)
                    {
                        sum += afterConv[n*C*H*W + c*H*W + h*W + w];
                        squareSum += afterConv[n*C*H*W + c*H*W + h*W+w] * afterConv[n*C*H*W + c*H*W + h*W+w];
                        //weight[h][w][c] = 0.5;
                        //bias[h][w][c] = 0.2;
                    }
                    RUNNING_MEAN[n*H*W + h*W + w] = sum / total;
                    RUNNING_VAR[n*H*W + h*W + w] = (squareSum / total) - (RUNNING_MEAN[n*H*W + h*W + w] * RUNNING_MEAN[n*H*W + h*W + w]);
                }
            }

        }

    Layer_Norm:
        for (int n = 0; n < B; n++)
        {
            for (int h = 0; h < H; h++)
            {
                for (int w = 0; w < W; w++)
                {
                    for (int c = 0; c < C; c++)
                    {
                        afterNorm[n*C*H*W + c*H*W + h*W + w] = (ln_in[n*C*H*W + h*W*C + w*C + c] - RUNNING_MEAN[n*H*W + h*W + w]) / sqrt(RUNNING_VAR[n*H*W + h*W + w] + 1e-6)
                        * weight[h*W*C+w*C+c] + bias[h*W*C+w*C+c];
                    }
                }
            }
        }
        break;
    }

    default:
        break;
    }
}
void compute_act(float* afterNorm, float* afterAct, int* X_num, int ACT_LAYER)
{
    int B = X_num[0];//
    int C = X_num[1];//
    int H = X_num[2];//
    int W = X_num[3];//
    switch (ACT_LAYER)
    {
    case 0: {
        for (int n = 0; n < B; n++)
        {
            for (int c = 0; c < C; c++)
            {
                for (int h = 0; h < H; h++)
                {
                    for (int w = 0; w < W; w++)
                    {
                        if (afterNorm[n*C*H*W+c*H*W+h*W+w] < 0)
                            afterAct[n*C*H*W+c*H*W+h*W+w] = 0;
                        else
                            afterAct[n*C*H*W+c*H*W+h*W+w] = afterNorm[n*C*H*W+c*H*W+h*W+w];
                    }
                }
            }
        }
        break;
    }
    case 1: {
        for (int n = 0; n < B; n++)
        {
            for (int c = 0; c < C; c++)
            {
                for (int h = 0; h < H; h++)
                {
                    for (int w = 0; w < W; w++)
                    {
                        afterAct[n*C*H*W+c*H*W+h*W+w] = afterNorm[n*C*H*W+c*H*W+h*W+w] * (1 / (1 + exp(-afterNorm[n*C*H*W+c*H*W+h*W+w])));
                    }
                }
            }
        }
        break;
    }
    case 2: {
        for (int n = 0; n < B; n++)
        {
            for (int c = 0; c < C; c++)
            {
                for (int h = 0; h < H; h++)
                {
                    for (int w = 0; w < W; w++)
                    {
                        float x = afterNorm[n*C*H*W+c*H*W+h*W+w];
                        afterAct[n*C*H*W+c*H*W+h*W+w] = 0.5 * x * (1.0 + tanh(sqrt(2.0 / 3.14159265358979323846) * (x + 0.044715 * pow(x, 3))));
                    }
                }
            }
        }
        break;
    }
    default:
        break;
    }
}


void compute_skip(float* afterAct, float* in, float *buffer_result, int* X_num, int isSkip)
{
    int B = X_num[0];//
    int C = X_num[1];//
    int H = X_num[2];//HEIGHT_OUT1
    int W = X_num[3];//
    int CI = X_num[5];//
    int HI = X_num[5];//HEIGHT_IN1
    int WI = X_num[6];//
Skip:
    for (int n = 0; n < B; n++)
    {
        for (int c = 0; c < C; c++)
        {
            for (int h = 0; h < H; h++)
            {
                for (int w = 0; w < W; w++)
                {
                    if (isSkip && (CI == C) && (HI == H) && (WI == W))
                        buffer_result[n * C * H * W + c * H * W + h * W + w] = afterAct[n*C*H*W + c*H*W + h*W + w] + in[n*C*H*W + c*H*W + h*W + w];
                    else
                        buffer_result[n * C * H * W + c * H * W + h * W + w] = afterAct[n*C*H*W + c*H*W + h*W + w];
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

void kernel_attention(float *buffer_DataIn_1,
                              float *afterNorm,
                              float *norm1_mean, float *norm1_var, float *norm1_weight, float *norm1_bias, float *norm1_ln_in,
                              float *afterPad,
                              float *afterRearrangeX,
                              float *afterPad1,
                              float *afterConv1,
                              float *kernel1,
                              float *bias1,
                              float *in_qk,
                              float *in_q,
                              float *in_k,
                              float *afterQKMultiplication,
                              float *afterSoftmax,
                              float *afterRearrangeX2,
                              float *afterQKXMultiplication,
                              float *afterRearrangeQKX,
                              float *afterPad2,
                              float *afterConv2,
                              float *kernel2,
                              float *bias2,
                              float *afterAct2,
                              float *QKV,
                              float *buffer_out,
                              float *in1_stream,
                              float *sumQK,
                              float *sumQKX,
                              float *buffer_result)
    {

//        float in1_stream[BATCH_SIZE*n1*n2*HEAD_SIZE*HEIGHT_OUT*WIDTH_OUT*HEIGHT_OUT*WIDTH_OUT];
        int norm_layer = 1;
        int act_layer = 0;
        int isBias1 = 1;
        int isSkip = 0;
        float scale = 1./sqrt(4.);//scale = 1/sqrt(dim_head);
        int norm_num[4]={1,4,16,16};//BATCH CHANNEL_IN HEIGHT_IN WIDTH_IN
        int pad_num[4]={1,4,16,16};//BATCH CHANNEL_IN HEIGHT_IN WIDTH_IN
        int pad_ltrb[4]={0,0,5,5};// l t r b
        int rearrangex_num[6]={1,4,7,7,3,3};//BATCH CHANNEL_IN h1 w1 n1 n2
        
        int pad1_num[6]={9,4,7,7,1,1};//BATCH*n1*n2
        int conv1_num[12]={9,8,7,7,
                             1,4,7,7,
                             4,8,1,4};
        //BATCH*n1*n2 CHANNEL_OUT HEIGHT_OUT WIDTH_OUT KERNEL_SIZE CHANNEL_IN HEIGHT_IN WIDTH_IN inGROUPNums outGROUPNums STRIDE KERNEL_CHANNEL
        int skip1_num[7]={9,8,7,7,4,7,7};//BATCH*n1*n2 CHANNEL_OUT HO WO CI HI WI
        int qk_num[6]={2,9,1,4,7,7};//2 BATCH_SIZE*n1*n2 HEAD_SIZE DIM_HEAD_SIZE HEIGHT_OUT WIDTH_OUT
        int mul1_num[5]={9,1,49,4,49};//B*n1*n2 HEAD_SIZE HO*WO DIM_HEAD_SIZE HO*WO
        int softmax_num[4]={9,1,49,49};//B*n1*n2  HEAD_SIZE HO*WO HO*WO
        int rearrangex2_num[5]={9,1,4,7,7};//B*n1*n2  HEAD_SIZE X_DIM_HEAD_SIZE HO WO
        int mul2_num[5]={9,1,49,49,4};//BATCH_SIZE*n1*n2 HEAD_SIZE HEIGHT_OUT*WIDTH_OUT HEIGHT_OUT*WIDTH_OUT X_DIM_HEAD_SIZE
        int rearrangeQKX_num[5]={9,1,7,7,4};//BATCH_SIZE*n1*n2 HEAD_SIZE  HO WO X_DIM_HEAD_SIZE

        int pad2_num[6]={9,4,7,7,1,1};//BATCH*n1*n2 NEW_CHANNEL_OUT H W KERNEL_SIZE STRIDE
        int conv2_num[12]={9,12,7,7,
                             1,4,7,7,
                             4,12,1,4};
        int act2_num[4]={9,12,7,7};
        int skip2_num[7]={9,12,7,7,4,7,7};
        int rearrangex3_num[6]={1,12,3,3,7,7};//BATCH_SIZE NEW_CHANNEL_OUT n1 n2 H W
        int out_num[6]={1,12,16,16,21,21};
        compute_norm(buffer_DataIn_1, afterNorm, norm1_mean, norm1_var, norm1_weight, norm1_bias, norm1_ln_in, norm_num, norm_layer);
        //load_input(afterNorm, x);
        pad_f(afterNorm, afterPad, pad_num, pad_ltrb);
        rearrangeX(afterPad, afterRearrangeX, rearrangex_num);
        //kernel_conv_norm_act(afterRearrangeX, in_qk);
        compute_PADDING(afterRearrangeX, afterPad1, pad1_num);
        compute_conv(afterPad1, afterConv1, kernel1, bias1, conv1_num, isBias1);
        compute_skip(afterConv1, afterRearrangeX, in_qk, skip1_num, isSkip);

        get_qk(in_qk, in_q, in_k, qk_num);
        compute_multiplication(in_q, in_k, afterQKMultiplication, sumQK, mul1_num, scale, 1);
        krnl_softmax(afterQKMultiplication, in1_stream, afterSoftmax, softmax_num);
        rearrangeX2(afterRearrangeX, afterRearrangeX2, rearrangex2_num);

        compute_multiplication(afterSoftmax, afterRearrangeX2, afterQKXMultiplication, sumQKX, mul2_num, 1, 2);
        rearrangeQKX(afterQKXMultiplication, afterRearrangeQKX, rearrangeQKX_num);
        //kernel_conv_norm_act2(afterRearrangeQKX, QKV);
        compute_PADDING(afterRearrangeQKX, afterPad2, pad2_num);
        compute_conv(afterPad2, afterConv2, kernel2, bias2, conv2_num, isBias1);
        compute_act(afterConv2, afterAct2, act2_num, act_layer);
        compute_skip(afterAct2, afterRearrangeQKX, QKV, skip2_num, isSkip);

        rearrangeX3(QKV, buffer_out, rearrangex3_num);
        store_result(buffer_out, buffer_result, out_num);
    }

