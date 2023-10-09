#include "kernel_stage1.hpp"
#include <cmath>
#include <math.h>

// TODO: modify parameters
const int BATCH_SIZE = 1;
const int CHANNEL_IN = 6;
const int HEIGHT_IN = 56;
const int WIDTH_IN = 56;
const int CHANNEL_OUT = 8;
const int HEIGHT_OUT = 28;
const int WIDTH_OUT = 28;

// below size please check count_depth output to modify corresponding
const int X_DATA_SIZE = 18816;
const int Y_V_CONV_1_SIZE = 75264;
const int Y_PROJ_1_SIZE = 6272;
const int Y_V_CONV_2_SIZE = 12544;

int main()
{
    // use count_depth to define size
    // depth 1
    float norm_1_weight[6], norm_1_bias[6], norm_1_running_mean[6], norm_1_running_var[6];
    float v_conv_1_weight[144], v_conv_1_bias[24];
    float dw_conv_1_filter[216], dw_norm_1_gamma[24], dw_norm_1_beta[24], dw_norm_1_mean[24], dw_norm_1_var[24];
    float proj_1_weight[192];
    // depth 2
    float norm_2_weight[8], norm_2_bias[8], norm_2_running_mean[8], norm_2_running_var[8];
    float v_conv_2_weight[128], v_conv_2_bias[16];
    float dw_conv_2_filter[144], dw_norm_2_gamma[16], dw_norm_2_beta[16], dw_norm_2_mean[16], dw_norm_2_var[16];
    float proj_2_weight[128];

    float X_data[X_DATA_SIZE];
    float Y_norm_1[X_DATA_SIZE];
    float Y_v_conv_1[Y_V_CONV_1_SIZE];
    float Y_dw_conv_1[X_DATA_SIZE], Y_dw_norm_1[X_DATA_SIZE], Y_dw_act_1[X_DATA_SIZE];
    float Y_proj_1[Y_PROJ_1_SIZE];

    float Y_norm_2[Y_PROJ_1_SIZE];
    float Y_v_conv_2[Y_V_CONV_2_SIZE];
    float Y_dw_conv_2[Y_V_CONV_2_SIZE], Y_dw_norm_2[Y_V_CONV_2_SIZE], Y_dw_act_2[Y_V_CONV_2_SIZE], Y_dw_skip_2[Y_V_CONV_2_SIZE];
    float Y_proj_2[Y_PROJ_1_SIZE];
    float Y_skip_2[Y_PROJ_1_SIZE];

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


    // init in
    /*for (int n = 0; n < BATCH_SIZE; n++)
    {
        for (int c = 0; c < CHANNEL_IN; c++)
        {
            for (int h = 0; h < HEIGHT_IN; h++)
            {
                for (int w = 0; w < WIDTH_IN; w++)
                {
                    X_data[n * CHANNEL_IN * HEIGHT_IN * WIDTH_IN + c * HEIGHT_IN * WIDTH_IN + h * WIDTH_IN + w] = h + c;
                }
            }
        }
    }
    for (int i = 0; i < Y_V_CONV_2_SIZE; i++)
    {
        Y_v_conv_2[i] = i/(Y_V_CONV_2_SIZE/32);
    }
    for (int i = 0; i < Y_PROJ_1_SIZE; i++)
    {
        Y_proj_1[i] = i/(Y_PROJ_1_SIZE/32);
    }*/

    // init out
    for (int i = 0; i < X_DATA_SIZE; i++)
    {
        Y_norm_1[i] = 0;
        Y_dw_conv_1[i] = 0;
        Y_dw_norm_1[i] = 0;
        Y_dw_act_1[i] = 0;
    }

    /*for (int i = 0; i < Y_V_CONV_1_SIZE; i++)
        Y_v_conv_1[i] = 0;*/

    for (int i = 0; i < Y_PROJ_1_SIZE; i++)
    {
        //Y_proj_1[i] = 0;
        Y_norm_2[i] = 0;
        Y_proj_2[i] = 0;
        Y_skip_2[i] = 0;
    }

    for (int i = 0; i < Y_V_CONV_2_SIZE; i++)
    {
        Y_v_conv_2[i] = 0;
        Y_dw_conv_2[i] = 0;
        Y_dw_norm_2[i] = 0;
        Y_dw_act_2[i] = 0;
        Y_dw_skip_2[i] = 0;
    }

    // init value
    // depth 1
    for (int i = 0; i < 6; i++)
    {
        norm_1_weight[i] = 0.5;
        norm_1_bias[i] = 0.2;
        norm_1_running_mean[i] = 8;
        norm_1_running_var[i] = 21.5;
    }

    for (int i = 0; i < 144; i++)
        v_conv_1_weight[i] = 0.3;

    for (int i = 0; i < 24; i++)
    {
        v_conv_1_bias[i] = i + 0.01;
        dw_norm_1_gamma[i] = 0.5;
        dw_norm_1_beta[i] = 0.2;
        dw_norm_1_mean[i] = 8;
        dw_norm_1_var[i] = 21.5;
    }

    for (int i = 0; i < 216; i++)
        dw_conv_1_filter[i] = 0.3;

    for (int i = 0; i < 192; i++)
        proj_1_weight[i] = 0.3;

    // depth 2
    for (int i = 0; i < 8; i++)
    {
        norm_2_weight[i] = 0.5;
        norm_2_bias[i] = 0.2;
        norm_2_running_mean[i] = 8;
        norm_2_running_var[i] = 21.5;
    }

    for (int i = 0; i < 128; i++)
        v_conv_2_weight[i] = 0.3;

    for (int i = 0; i < 16; i++)
    {
        v_conv_2_bias[i] = i + 0.01;
        dw_norm_2_gamma[i] = 0.5;
        dw_norm_2_beta[i] = 0.2;
        dw_norm_2_mean[i] = 8;
        dw_norm_2_var[i] = 21.5;
    }

    for (int i = 0; i < 144; i++)
        dw_conv_2_filter[i] = 0.3;

    for (int i = 0; i < 128; i++)
        proj_2_weight[i] = 0.3;

    // execution
    kernel_stage3(buffer_DataIn_1,
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
                              buffer_result,
                  dw_conv_2_filter, dw_norm_2_gamma, dw_norm_2_beta, dw_norm_2_mean, dw_norm_2_var,
                  proj_2_weight,
                  Y_dw_conv_2, Y_dw_norm_2, Y_dw_act_2, Y_proj_2,
                  Y_dw_skip_2, Y_skip_2
                  );

    // print output
    /*for (int n = 0; n < BATCH_SIZE; n++)
    {
        for (int c = 0; c < CHANNEL_OUT; c++)
        {
            for (int h = 0; h < HEIGHT_OUT; h++)
            {
                for (int w = 0; w < WIDTH_OUT; w++)
                {
                    if (w == 7){
                        std::cout << Y_skip_2[n * CHANNEL_OUT * HEIGHT_OUT * WIDTH_OUT + c * HEIGHT_OUT * WIDTH_OUT + h * WIDTH_OUT + w] << std::endl;
                        break;
                    }

                    else
                        std::cout << Y_skip_2[n * CHANNEL_OUT * HEIGHT_OUT * WIDTH_OUT + c * HEIGHT_OUT * WIDTH_OUT + h * WIDTH_OUT + w] << " ";
                }
                if(h == 7){
                    break;
                }
            }
            break;
        }
        break;
    }*/
    for(int i=0;i<Y_PROJ_1_SIZE;i++){
      std::cout<<Y_skip_2[i]<<" ";
    }
    std::cout<<"\n";
    return EXIT_SUCCESS;
}
