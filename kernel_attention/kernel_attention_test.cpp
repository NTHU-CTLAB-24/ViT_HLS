#include "kernel_attention.hpp"
#include <cmath>
#include <math.h>

// TODO: modify parameters
const int BATCH_SIZE = 1;
const int CHANNEL_IN = 4;
const int HEIGHT_IN = 16;
const int WIDTH_IN = 16;



int main()
{
    float buffer_DataIn_1[1024];
    float afterNorm[1024];
    float norm1_mean[256]; 
    float norm1_var[256]; 
    float norm1_weight[1024]; 
    float norm1_bias[1024]; 
    float norm1_ln_in[1024];
    float afterPad[1764];
    float afterRearrangeX[1764];
    float afterPad1[1764];
    float afterConv1[3528];
    float kernel1[32];
    float bias1[8];
    float in_qk[3528];
    float in_q[1764];
    float in_k[1764];
    float afterQKMultiplication[21609];
    float afterSoftmax[21609];
    float afterRearrangeX2[1764];
    float afterQKXMultiplication[1764];
    float afterRearrangeQKX[1764];
    float afterPad2[1764];
    float afterConv2[5292];
    float kernel2[48];
    float bias2[12];
    float afterAct2[5292];
    float QKV[5292];
    float buffer_out[5292];
    float in1_stream[21609];
    float sumQK[2401];
    float sumQKX[196];
    float buffer_result[3072];

    // init in
    for(int i=0;i<BATCH_SIZE*CHANNEL_IN*HEIGHT_IN*WIDTH_IN;i++){
    	buffer_DataIn_1[i]=float(i)/20;
        afterNorm[i]=0;
    }
    for(int i=0;i<256;i++){
        norm1_mean[i]=0;
        norm1_var[i]=0;
    }
    for (int h = 0; h < 16; h++)
	{
		for (int w = 0; w < 16; w++)
		{
			for (int c = 0; c < 4; c++)
			{
				norm1_weight[h*4*16+w*4+c] = 0.5;
				norm1_bias[h*4*16+w*4+c]  = 0.2;
			}
		}
	}
    for(int i=0;i<1024;i++){
        norm1_ln_in[i]=0;
    }
    for(int i=0;i<1764;i++){
        afterPad[i]=0;
        afterRearrangeX[i]=0;
        afterPad1[i]=0;
    }
    for(int i=0;i<3528;i++){
        afterConv1[i]=0;
    }
    for (int k = 0; k < 8; k++)
    {
        bias1[k] = k + 0.5;
        for (int l = 0; l < 4; l++)
        {
            for (int i = 0; i < 1; i++)
            {
                for (int j = 0; j < 1; j++)
                {
                    kernel1[k*4*1*1+l*1*1+i*1+j] = (k+j+i+l)*0.1;
                }
            }
        }
    }
    for(int i=0;i<3528;i++){
        in_qk[i]=0;
    }
    for(int i=0;i<1764;i++){
        in_q[i]=0;
        in_k[i]=0;
    }
    for(int i=0;i<21609;i++){
        afterQKMultiplication[i]=0;
        afterSoftmax[i]=0;
    }
    for(int i=0;i<1764;i++){
        afterRearrangeX2[i]=0;
        afterQKXMultiplication[i]=0;
        afterRearrangeQKX[i]=0;
        afterPad2[i]=0;
    }
    for(int i=0;i<5292;i++){
        afterConv2[i]=0;
    }

    for (int k = 0; k < 12; k++)
    {
        bias2[k] = 2;
        for (int l = 0; l < 4; l++)
        {
            for (int i = 0; i < 1; i++)
            {
                for (int j = 0; j < 1; j++)
                {
                    kernel2[k*4*1*1+l*1*1+i*1+j] = 1.2;
                }
            }
        }
    }
    for(int i=0;i<5292;i++){
        afterAct2[i]=0;
        QKV[i]=0;
        buffer_out[i]=0;
    }
    for(int i=0;i<21609;i++){
        in1_stream[i]=0;
    }
    for(int i=0;i<2401;i++){
        sumQK[i]=0;
    }
    for(int i=0;i<196;i++){
        sumQKX[i]=0;
    }
    for(int i=0;i<3072;i++){
        buffer_result[i]=0;
    }

    // execution
    kernel_attention(buffer_DataIn_1,
                              afterNorm,
                              norm1_mean, norm1_var, norm1_weight, norm1_bias, norm1_ln_in,
                              afterPad,
                              afterRearrangeX,
                              afterPad1,
                              afterConv1,
                              kernel1,
                              bias1,
                              in_qk,
                              in_q,
                              in_k,
                              afterQKMultiplication,
                              afterSoftmax,
                              afterRearrangeX2,
                              afterQKXMultiplication,
                              afterRearrangeQKX,
                              afterPad2,
                              afterConv2,
                              kernel2,
                              bias2,
                              afterAct2,
                              QKV,
                              buffer_out,
                              in1_stream,
                              sumQK,
                              sumQKX,
                              buffer_result
                       );

    // print output
    
    
    
    
    for (int n = 0; n < BATCH_SIZE; n++)
    {
        for (int c = 0; c < 1; c++)
        {
            for (int h = 0; h < 16; h++)
            {
                for (int w = 0; w < 16; w++)
                {
                    if (w == 15){
                        std::cout << buffer_result[n * 12 * 16 * 16 + c * 16 * 16 + h * 16 + w] << std::endl;
                        break;
                    }

                    else
                        std::cout << buffer_result[n * 12 * 16 * 16 + c * 16 * 16 + h * 16 + w] << " ";
                }
                if(h == 15){
                    break;
                }
            }
            break;
        }
        break;
    }

    return EXIT_SUCCESS;
}
