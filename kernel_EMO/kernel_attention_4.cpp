//memory 579952
// Includes

#include <stdint.h>
#include "kernel_EMO.hpp"
#include <hls_math.h>
#include <hls_stream.h>

void pad_f_4(float* x, float* afterPad, int* X_num, int* padding){
    int B = X_num[0];//BATCH_SIZE
    int C = X_num[1];//CHANNEL_IN
    int H = X_num[2];//HEIGHT_IN
    int W = X_num[3];//WIDTH_IN
    int NH = X_num[2] + padding[1] + padding[3];//NEW_HEIGHT_IN                       pad l t r b
    int NW = X_num[3] + padding[0] + padding[2];//NEW_WIDTH_IN
    
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
void get_qk_4(float* in_qk,float* in_q,float* in_k,int* X_num)
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
                                in_k[b * DH * W * H * C + c * DH * W * H + dh * H * W + h * W + w]
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
void rearrangeX_4(float* afterPad, float* afterRearrangeX, int* X_num){
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
                           afterPad[i * H1 * N1 * W1 * N2 * C + 
                                    j * H1 * N1 * W1 * N2 + 
                                    (k * N1 + l) * W1 * N2 + 
                                    m * N2 + n];
                        }
                    }
                }
            }
        }

    }
}
//'b (heads dim_head) h w -> b heads (h w) dim_head'
void rearrangeX2_4(float* afterRearrangeX, float* afterRearrangeX2, int* X_num){
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
void rearrangeX3_4(float* QKV, float* buffer_out, int* X_num){
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
void rearrangeQKX_4(float* afterQKXMultiplication, float* afterRearrangeQKX, int* X_num){
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
void compute_multiplication_4(float* in_q, float* in_k, float* afterQKMultiplication, int* X_num, float scale)
{
    int B = X_num[0];//BATCH_SIZE*n1*n2
    int C = X_num[1];//HEAD_SIZE
    int H = X_num[2];//HEIGHT_OUT*WIDTH_OUT
    int W = X_num[3];//DIM_HEAD_SIZE
    int NW = X_num[4];//HEIGHT_OUT*WIDTH_OUT
    float sum = 0;
execute:
    for(int b = 0; b < B; b++){
        for(int c = 0;c < C; c++){
            for(int i = 0; i < H; i++){
                for(int k = 0; k < NW; k++){
                    for(int j = 0; j < W; j++){
                        sum += in_q[b * C * H * W + c * H * W + i * W + j]
                        *in_k[b * C * W * NW + c * W * NW + j * NW + k]*scale;
					}
                    afterQKMultiplication[b * H * NW * C + c * H * NW + i * NW+ k] = sum;
                    sum = 0;
                }
            }
        }
    }
}

void compute_softmax_4(float* inStream,float* out_stream, int* X_num)
{
    int B = X_num[0];//BATCH_SIZE*n1*n2
    int C = X_num[1];//HEAD_SIZE
    int H = X_num[2];//HEIGHT_OUT*WIDTH_OUT
    int W = X_num[3];//HEIGHT_OUT*WIDTH_OUT
gen_output2:
    //float tmp_in[W];
    float sum = 0;
    float tmp_in = 0;
    float tmp_in2 = 0;
    for(int b = 0; b < B; ++b){
        for(int h = 0; h < C; ++h){
            for (int i = 0; i < H; ++i) {
            count_sum:
                for (int j = 0; j < W; ++j) {
                    tmp_in = inStream[b * H * W * C + h * H * W + i * W + j];
                    for(int k = 0; k < W;k++){
                        tmp_in2 = inStream[b * H * W * C + h * H * W + i * W + k];
                        sum = sum + pow(2.718281828459,tmp_in2-tmp_in);//expf(tmp_in-tmp_in2);
                    }
                    out_stream[b * H * W * C + h * H * W + i * W + j] = 1 / sum;
                    //sum += inStream[b * H * W * C + h * H * W + i * W + j];
                    sum = 0;
                }
            /*divide:
                for (int j = 0; j < W; ++j) {
                    if(sum==0){
                        out_stream[b * W * H * C + h * H * W + i * W + j] = 0;
                    }
                    else{
                        out_stream[b * H * W * C + h * H * W + i * W + j] = inStream[b * H * W * C + h * H * W + i * W + j] / sum;
                    }

                }
                sum = 0;*/
            }
        }
    }
}

void store_result_4(float* buffer_out,float* buffer_result, int* X_num){
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
                        buffer_result[i * C * H * W + j * H * W + k * W + l] = 
                        buffer_out[i * NW * NH * C + j * NW * NH + k * NW + l];
                    }
                }
            }
        }
    }
}
void DW_conv_4(float *in, float *kernel, float *bias, int *shape_para, int *conv_para, float *out)
{
    int BATCH_SIZE = shape_para[0];
    int CHANNEL_IN = shape_para[1];
    int HEIGHT_IN = shape_para[2];
    int WIDTH_IN = shape_para[3];
    int CHANNEL_OUT = shape_para[4];
    int HEIGHT_OUT = shape_para[5];
    int WIDTH_OUT = shape_para[6];

    int KERNEL_SIZE = conv_para[0];
    int isConvBias = conv_para[1];
    int STRIDE = conv_para[2];
    int PADDING = conv_para[3];
    int GROUP = conv_para[4];
    int KERNEL_CHANNEL = conv_para[5];

    int inGroupNums = CHANNEL_IN / GROUP;
    int outGroupNums = CHANNEL_OUT / GROUP;

    int kernelChannelIdx;
    int out_pos;
    int in_row;
    int in_col;
    int in_pos;
    int kernel_pos;

execute:
Batch:
    for (int batch = 0; batch < BATCH_SIZE; batch++){
//#pragma HLS LOOP_TRIPCOUNT min = 1 max = 1
    Out_Row:
        for (int row = 0; row < HEIGHT_OUT; row++){
//#pragma HLS LOOP_TRIPCOUNT min = 112 max = 112
        Out_Column:
            for (int col = 0; col < WIDTH_OUT; col++){
//#pragma HLS LOOP_TRIPCOUNT min = 112 max = 112
                int biasFlag = 1; // 這種迴圈架構的bias會被重複計算，需要此flag限制只加一次
            Kernel_Row:
                for (int kernel_row = 0; kernel_row < KERNEL_SIZE; kernel_row++){
//#pragma HLS LOOP_TRIPCOUNT min = 3 max = 3
                Kernel_Col:
                    for (int kernel_col = 0; kernel_col < KERNEL_SIZE; kernel_col++){
//#pragma HLS LOOP_TRIPCOUNT min = 3 max = 3
                        int groupIndex = 0;
                        in_row = row * STRIDE + kernel_row - PADDING;
                        in_col = col * STRIDE + kernel_col - PADDING;
                        if (in_row < 0 || in_row >= HEIGHT_IN || in_col < 0 || in_col >= WIDTH_IN )
                            continue;
                    Output_Channel:
                        for (int out_ch = 0; out_ch < CHANNEL_OUT; out_ch++){
//#pragma HLS LOOP_TRIPCOUNT min = 24 max = 24
                            out_pos = batch * CHANNEL_OUT * HEIGHT_OUT * WIDTH_OUT + out_ch * HEIGHT_OUT * WIDTH_OUT + row * WIDTH_OUT + col;
                            kernelChannelIdx = 0;
                        In_Channel:
                            for (int in_ch = groupIndex * inGroupNums; in_ch < CHANNEL_IN; in_ch++){
//#pragma HLS LOOP_TRIPCOUNT min = 0 max = 24
                                in_pos = batch * CHANNEL_IN * HEIGHT_IN * WIDTH_IN + in_ch * HEIGHT_IN * WIDTH_IN + in_row * WIDTH_IN + in_col;
                                kernel_pos = out_ch * KERNEL_CHANNEL * KERNEL_SIZE * KERNEL_SIZE + kernelChannelIdx * KERNEL_SIZE * KERNEL_SIZE + kernel_row * KERNEL_SIZE + kernel_col;
                                out[out_pos] += in[in_pos] * kernel[kernel_pos];
                                kernelChannelIdx++;
                                if ((in_ch + 1) % inGroupNums == 0)
                                    break;
                            }
                            if (isConvBias && biasFlag)
                                out[out_pos] += bias[out_ch];
                            if ((out_ch + 1) % outGroupNums == 0)
                                groupIndex++;
                        }
                        biasFlag = 0;
                    }
                }
            }
        }
    }

    return;
}
void LayerNorm_4(float* X_data, float* Y_data, int* X_num, float* mean_buf, float* var_buf, float* weight, float* bias) {
    //get X(input) size
    int N = X_num[0]; //1
    int C = X_num[1];
    int H = X_num[2];
    int W = X_num[3];

    int pos = 0;
    float sum = 0;
    float sum2 = 0;
    float diff = 0;
    float value = 0;
    float mean = 0;
    for (int n = 0; n < N; n++) {
        for (int h = 0; h < H; h++) {
            for (int w = 0; w < W; w++) {
                pos = h * W + w;
                sum = 0;
                sum2 = 0;
                for (int c = 0; c < C; c++) {
                    value = X_data[n*C*H*W + c*H*W + pos];
                    sum += value/ C;
                    //sum2 += value/ C * value;
                }
                mean = sum ;
                for (int c = 0; c < C; c++) {
                    value = X_data[n*C*H*W + c*H*W + pos];
                    diff = value - mean;
                    sum2 += diff / C * diff ;
                }
                //if(n =0&&h=0)std:cout<<" mean = "<<mean<<std::endl;
                mean_buf[pos] = mean;
                var_buf[pos] = sum2 ;
            }
        }
    }
    
    for (int n = 0; n < N; n++) {
        for (int h = 0; h < H; h++) {
            for (int w = 0; w < W; w++) {
                pos = h * W + w;
                for (int c = 0; c < C; c++) {
                     Y_data[n*C*H*W + c*H*W + pos] = (X_data[n*C*H*W + c*H*W + pos] - mean_buf[pos]) / sqrt(var_buf[pos] + 1e-6) * weight[c] + bias[c];
                }
            }
        }
   }
    
}

void BatchNorm_4(float *X_data, float *Y_data, int *X_num, float *running_mean, float *running_var, float *gamma, float *beta)
{
    // get X(input) size
    int N = X_num[0];
    int C = X_num[1];
    int H = X_num[2];
    int W = X_num[3];
    // #pragma HLS INTERFACE mode=ap_fifo port=X_data
    // #pragma HLS INTERFACE mode=ap_fifo port=Y_data

    for (int n = 0; n < N; n++)
    {
        for (int c = 0; c < C; c++)
        {
            for (int h = 0; h < H; h++)
            {
                for (int w = 0; w < W; w++)
                {
// #pragma HLS UNROLL
// #pragma HLS PIPELINE
                    Y_data[n * C * H * W + c * H * W + h * W + w] = (X_data[n * C * H * W + c * H * W + h * W + w] - running_mean[c]) / sqrt(running_var[c] + 1e-6) * gamma[c] + beta[c];
                }
            }
        }
    }
}

void compute_act_4(float* afterNorm, float* afterAct, int* X_num, int ACT_LAYER)
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
                        //afterAct[n*C*H*W+c*H*W+h*W+w] = 0.5 * x * (1.0 + tanh(sqrt(2.0 / 3.14159265358979323846) * (x + 0.044715 * pow(x, 3))));
                        afterAct[n*C*H*W+c*H*W+h*W+w] = x/2*(1+erf(x/1.4142135623730951));
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


void compute_skip_4(float* afterAct, float* in, float *buffer_result, int* X_num, int isSkip)
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

extern "C"{


void kernel_attention_4(float *buffer_DataIn_1,
                              float *afterNorm,
                              float *norm1_mean, float *norm1_var, float *norm1_weight, float *norm1_bias,
                              float *afterRearrangeX,
                              float *afterConv1,
                              float *kernel1,
                              float *bias1,
                              float *in_q,
                              float *in_k,
                              float *afterQKMultiplication,
                              float *afterSoftmax,
                              float *afterRearrangeX2,
                              float *afterQKXMultiplication,
                              float *afterRearrangeQKX,
                              float *afterConv2,
                              float *kernel2,
                              float *bias2,
                              float *afterAct2,
                              float *buffer_out,
                              float *buffer_result)
    {
        /*****************************/
        int act_layer = 2;  //for gelu
        int isBias1 = 1;
        int isSkip = 0;
        float scale = 1./sqrt(21);//scale = 1/sqrt(dim_head);
        int norm_num[4]={1, 168, 7, 7};//BATCH CHANNEL_IN HEIGHT_IN WIDTH_IN
        int pad_num[4]={1,168,7,7};//BATCH CHANNEL_IN HEIGHT_IN WIDTH_IN
        int pad_ltrb[4]={0,0,0,0};// l t r b
        int rearrangex_num[6]={1,168,7,7,1,1};//BATCH CHANNEL_IN h1 w1 n1 n2
        
        int shape1_para[7] = {1, 168, 7, 7, 336, 7, 7};
        int conv1_para[6] = {1, 1, 1, 0, 1, 168};

        //BATCH*n1*n2 CHANNEL_OUT HEIGHT_OUT WIDTH_OUT 
        //KERNEL_SIZE CHANNEL_IN HEIGHT_IN WIDTH_IN 
        //inGROUPNums outGROUPNums STRIDE KERNEL_CHANNEL
        int skip1_num[7]={1,336,7,7,168,7,7};//BATCH*n1*n2 CHANNEL_OUT HO WO CI HI WI
        int qk_num[6]={2,1,8,21,7,7};//2 BATCH_SIZE*n1*n2 HEAD_SIZE DIM_HEAD_SIZE HEIGHT_OUT WIDTH_OUT
        int mul1_num[5]={1,8,49,21,49};//B*n1*n2 HEAD_SIZE HO*WO DIM_HEAD_SIZE HO*WO
        int softmax_num[4]={1,8,49,49};//B*n1*n2  HEAD_SIZE HO*WO HO*WO
        int rearrangex2_num[5]={1,8,21,7,7};//B*n1*n2  HEAD_SIZE X_DIM_HEAD_SIZE HO WO
        int mul2_num[5]={1,8,49,49,21};//BATCH_SIZE*n1*n2 HEAD_SIZE HEIGHT_OUT*WIDTH_OUT HEIGHT_OUT*WIDTH_OUT X_DIM_HEAD_SIZE
        int rearrangeQKX_num[5]={1,8,7,7,21};//BATCH_SIZE*n1*n2 HEAD_SIZE  HO WO X_DIM_HEAD_SIZE

        /*int pad2_num[6]={16,40,7,7,1,2};//BATCH*n1*n2 NEW_CHANNEL_OUT H W KERNEL_SIZE STRIDE
        int conv2_num[12]={16,120,7,7,
                             1,40,7,7,
                             40,120,1,40};*/
        int shape2_para[7] = {1, 168, 7, 7, 588, 7, 7};
        int conv2_para[6] = {1, 1, 1, 0, 1, 168};
        
        int act2_num[4]={1,588,7,7};
        int skip2_num[7]={1,588,7,7,168,7,7};
        int rearrangex3_num[6]={1,588,1,1,7,7};//BATCH_SIZE NEW_CHANNEL_OUT n1 n2 H W
        int out_num[6]={1,588,7,7,7,7};
        
        // LayerNorm_4(buffer_DataIn_1, afterNorm, norm_num, norm1_mean, norm1_var, norm1_weight, norm1_bias);
        LayerNorm(buffer_DataIn_1, afterNorm, norm_num, norm1_mean, norm1_var, norm1_weight, norm1_bias);
        rearrangeX_4(afterNorm, afterRearrangeX, rearrangex_num);
        DW_conv_4(afterRearrangeX, kernel1, bias1, shape1_para, conv1_para, afterConv1);


        get_qk_4(afterConv1, in_q, in_k, qk_num);
        compute_multiplication_4(in_q, in_k, afterQKMultiplication, mul1_num, scale);
        compute_softmax_4(afterQKMultiplication, afterSoftmax, softmax_num);
        rearrangeX2_4(afterRearrangeX, afterRearrangeX2, rearrangex2_num);

        compute_multiplication_4(afterSoftmax, afterRearrangeX2, afterQKXMultiplication, mul2_num, 1);
        rearrangeQKX_4(afterQKXMultiplication, afterRearrangeQKX, rearrangeQKX_num);

        DW_conv_4(afterRearrangeQKX, kernel2, bias2, shape2_para, conv2_para, afterConv2);
        compute_act_4(afterConv2, afterAct2, act2_num, act_layer);

        rearrangeX3_4(afterAct2, buffer_out, rearrangex3_num);
        store_result_4(buffer_out, buffer_result, out_num);
    }
}