#include "kernel_stage3_1.hpp"
#include <cmath>
#include <math.h>

// TODO: modify parameters
const int BATCH_SIZE = 1;
const int CHANNEL_IN = 80;
const int HEIGHT_IN = 14;
const int WIDTH_IN = 14;
const int CHANNEL_OUT = 240;
const int HEIGHT_OUT = 14;
const int WIDTH_OUT = 14;

const int Y_PROJ_1_SIZE = 15680;
const int Y_V_CONV_1_SIZE = 47040;
// use count_depth to define size
    // depth 2
    static float norm_1_weight[80], norm_1_bias[80], norm_1_running_mean[80], norm_1_running_var[80];
    static float v_conv_1_weight[19200], v_conv_1_bias[240];
    static float dw_conv_1_filter[6000], dw_norm_1_weight[240], dw_norm_1_bias[240], dw_norm_1_mean[240], dw_norm_1_var[240];
    static float proj_1_weight[19200];


    static float Y_norm_1[Y_PROJ_1_SIZE];
    static float Y_v_conv_1[Y_V_CONV_1_SIZE];
    static float Y_dw_conv_1[Y_V_CONV_1_SIZE], Y_dw_norm_1[Y_V_CONV_1_SIZE], Y_dw_act_1[Y_V_CONV_1_SIZE], Y_dw_skip_1[Y_V_CONV_1_SIZE];
    static float Y_proj_1[Y_PROJ_1_SIZE];
    static float Y_skip_1[Y_PROJ_1_SIZE];

    float buffer_DataIn_1[15680];
    float afterNorm[15680];
    float norm1_mean[80]; 
    float norm1_var[80]; 
    float norm1_weight[80]; 
    float norm1_bias[80]; 
    float afterPad[15680];
    float afterRearrangeX[15680];
    float afterPad1[15680];
    float afterConv1[31360];
    float kernel1[12800];
    float bias1[160];
    float in_qk[31360];
    float in_q[15680];
    float in_k[15680];
    float afterQKMultiplication[38416];
    float afterSoftmax[38416];
    float afterRearrangeX2[15680];
    float afterQKXMultiplication[15680];
    float afterRearrangeQKX[15680];
    float afterPad2[15680];
    float afterConv2[47040];
    float kernel2[19200];
    float bias2[240];
    float afterAct2[47040];
    float QKV[47040];
    float buffer_out[47040];
    float buffer_result[47040];

int main()
{
    

    // init in
    for(int i=0;i<BATCH_SIZE*CHANNEL_IN*HEIGHT_IN*WIDTH_IN;i++){
    	buffer_DataIn_1[i]=float(i%256);
        afterNorm[i]=0;
    }
    float tmp_sum=0;
    float tmp_square_sum=0;
    for(int i=0;i<80;i++){
        norm1_mean[i]=125.;
        norm1_var[i]=5638.;
    }
	for (int c = 0; c < 80; c++)
	{
		norm1_weight[c] = 0.5;
		norm1_bias[c]  = 1;
	}

    for(int i=0;i<15680;i++){
        afterPad[i]=0;
        afterRearrangeX[i]=0;
        afterPad1[i]=0;
    }
    for(int i=0;i<31360;i++){
        afterConv1[i]=0;
    }
    for (int k = 0; k < 160; k++)
    {
        bias1[k] = 0.01;
        for (int l = 0; l < 80; l++)
        {
            for (int i = 0; i < 1; i++)
            {
                for (int j = 0; j < 1; j++)
                {
                    kernel1[k*80*1*1+l*1*1+i*1+j] = (0.02);
                }
            }
        }
    }
    for(int i=0;i<31360;i++){
        in_qk[i]=0;
    }
    for(int i=0;i<15680;i++){
        in_q[i]=0;
        in_k[i]=0;
    }
    for(int i=0;i<38416;i++){
        afterQKMultiplication[i]=0;
        afterSoftmax[i]=0;
    }
    for(int i=0;i<15680;i++){
        afterRearrangeX2[i]=0;
        afterQKXMultiplication[i]=0;
        afterRearrangeQKX[i]=0;
        afterPad2[i]=0;
    }
    for(int i=0;i<47040;i++){
        afterConv2[i]=0;
    }

    for (int k = 0; k < 240; k++)
    {
        bias2[k] = 2;
        for (int l = 0; l < 80; l++)
        {
            for (int i = 0; i < 1; i++)
            {
                for (int j = 0; j < 1; j++)
                {
                    kernel2[k*80*1*1+l*1*1+i*1+j] = 1.2;
                }
            }
        }
    }
    for(int i=0;i<47040;i++){
        afterAct2[i]=0;
        QKV[i]=0;
        buffer_out[i]=0;
    }
    for(int i=0;i<47040;i++){
        buffer_result[i]=0;
    }

    for (int i = 0; i < Y_PROJ_1_SIZE; i++)
    {
        Y_norm_1[i] = 0;
        Y_proj_1[i] = 0;
        Y_skip_1[i] = 0;
    }

    for (int i = 0; i < Y_V_CONV_1_SIZE; i++)
    {
        Y_v_conv_1[i] = 0;
        Y_dw_conv_1[i] = 0;
        Y_dw_norm_1[i] = 0;
        Y_dw_act_1[i] = 0;
        Y_dw_skip_1[i] = 0;
    }


    for (int i = 0; i < 240; i++)
    {
        dw_norm_1_weight[i] = 0.5;
        dw_norm_1_bias[i] = 0.2;
        dw_norm_1_mean[i] = 8;
        dw_norm_1_var[i] = 21.5;
    }

    for (int i = 0; i < 6000; i++)
        dw_conv_1_filter[i] = 0.5;

    for (int i = 0; i < 19200; i++)
        proj_1_weight[i] = 0.8;

    // execution
    kernel_stage3_1(buffer_DataIn_1,
                              afterNorm,
                              norm1_mean, norm1_var, norm1_weight, norm1_bias,
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
                              buffer_result,
                  dw_conv_1_filter, dw_norm_1_weight, dw_norm_1_bias, dw_norm_1_mean, dw_norm_1_var,
                  proj_1_weight, Y_dw_conv_1, Y_dw_norm_1, Y_dw_act_1, Y_proj_1,
                  Y_dw_skip_1, Y_skip_1
                  );

    
    for(int i=0;i<Y_PROJ_1_SIZE;i++){
        //std::cout<<Y_proj_1[i]<<" ";
      std::cout<<std::setprecision(10)<<Y_skip_1[i]<<" ";
    }
    std::cout<<"\n";
    return EXIT_SUCCESS;
}
