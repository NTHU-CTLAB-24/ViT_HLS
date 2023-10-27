#include "kernel_stage3.hpp"
#include <cmath>
#include <math.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

// TODO: modify parameters
const int BATCH_SIZE = 1;
const int CHANNEL_IN = 48;
const int HEIGHT_IN = 28;
const int WIDTH_IN = 28;
const int CHANNEL_OUT = 80;
const int HEIGHT_OUT = 14;
const int WIDTH_OUT = 14;

// below size please check count_depth output to modify corresponding
const int X_DATA_SIZE = 37632;
const int Y_V_CONV_0_SIZE = 225792;
const int Y_PROJ_1_SIZE = 15680;
const int Y_V_CONV_1_SIZE = 47040;
// depth 0
float norm_0_weight[48], norm_0_bias[48], norm_0_running_mean[48], norm_0_running_var[48];
float v_conv_0_weight[13824], v_conv_0_bias[288];
float dw_conv_0_filter[7200], dw_norm_0_weight[288], dw_norm_0_bias[288], dw_norm_0_mean[288], dw_norm_0_var[288];
float proj_0_weight[23040];

float X_data[X_DATA_SIZE];
float Y_norm_0[X_DATA_SIZE];
float Y_v_conv_0[225792], Y_v_act_0[225792];
float Y_dw_conv_0[56448], Y_dw_norm_0[56448], Y_dw_act_0[56448];
// use count_depth to define size
// depth 1-7
static float norm_1_weight[80*7], norm_1_bias[80*7], norm_1_running_mean[80*7], norm_1_running_var[80*7];
static float v_conv_1_weight[19200*7], v_conv_1_bias[240*7];
static float dw_conv_1_filter[6000*7], dw_norm_1_weight[240*7], dw_norm_1_bias[240*7], dw_norm_1_mean[240*7], dw_norm_1_var[240*7];
static float proj_1_weight[19200*7];


static float Y_dw_conv_1[Y_V_CONV_1_SIZE], Y_dw_norm_1[Y_V_CONV_1_SIZE], Y_dw_act_1[Y_V_CONV_1_SIZE], Y_dw_skip_1[Y_V_CONV_1_SIZE];
static float Y_proj_1[Y_PROJ_1_SIZE];
static float Y_skip_1[Y_PROJ_1_SIZE];

float result_30[15680];
float afterNorm[15680];

float norm1_mean[196*7]; 
float norm1_var[196*7]; 
float norm1_weight[80*7]; 
float norm1_bias[80*7];

float afterRearrangeX[15680];
float afterConv1[31360];

float kernel1[12800*7];
float bias1[160*7];

float in_q[15680];
float in_k[15680];
float afterQKMultiplication[38416];
float afterSoftmax[38416];
float afterRearrangeX2[15680];
float afterQKXMultiplication[15680];
float afterRearrangeQKX[15680];
float afterConv2[47040];

float kernel2[19200*7];
float bias2[240*7];

float afterAct2[47040];
float buffer_out[47040];
float buffer_result[47040];

int main()
{
    // use count_depth to define size
    
    // init in
    for (int n = 0; n < 1; n++) {
        for (int c = 0; c < 48; c++) {
            for (int h = 0; h < 28; h++) {
                for (int w = 0; w < 28; w++) {
                    X_data[n * CHANNEL_IN * HEIGHT_IN * WIDTH_IN + c * HEIGHT_IN * WIDTH_IN + h * WIDTH_IN + w] = (n+c+h+w) % 25;
                }
            }
        }
    }


     // init parameters value
    ifstream file("./stage3_parameters.txt");
    if (!file.is_open())
        cerr << "Failed to open the parameter file." << std::endl;
    
    unordered_map<string, vector<float>> parameterData;
    string line;
    string current_key;

    while (std::getline(file, line))
    {
        if (!line.empty())
        {
            if (line[0] == 's'){ // key
                current_key = line;
                cout << "HOST-INFO: loading " << current_key << " value..." << endl;
            } 
            else
            {
                istringstream iss(line);
                float value;
                while (iss >> value)
                {
                    parameterData[current_key].push_back(value);
                }
            }
        }
    }
    for (int i = 0; i < 48; i++) norm_0_weight[i] = parameterData["stage3.0.norm.norm.weight"][i];
    for (int i = 0; i < 48; i++) norm_0_bias[i] = parameterData["stage3.0.norm.norm.bias"][i];
    for (int i = 0; i < 13824; i++) v_conv_0_weight[i] = parameterData["stage3.0.v.conv.weight"][i];
    for (int i = 0; i < 288; i++) v_conv_0_bias[i] = parameterData["stage3.0.v.conv.bias"][i];
    for (int i = 0; i < 7200; i++) dw_conv_0_filter[i] = parameterData["stage3.0.conv_local.conv.weight"][i];   
    for (int i = 0; i < 288; i++) dw_norm_0_weight[i] = parameterData["stage3.0.conv_local.norm.weight"][i];    
    for (int i = 0; i < 288; i++) dw_norm_0_bias[i] = parameterData["stage3.0.conv_local.norm.bias"][i];        
    for (int i = 0; i < 288; i++) dw_norm_0_mean[i] = parameterData["stage3.0.conv_local.norm.running_mean"][i];
    for (int i = 0; i < 288; i++) dw_norm_0_var[i] = parameterData["stage3.0.conv_local.norm.running_var"][i];  
    for (int i = 0; i < 23040; i++) proj_0_weight[i] = parameterData["stage3.0.proj.conv.weight"][i];

    // init out
    for (int i = 0; i < 15680; i++) result_30[i] = 0;
    for(int i=0;i<15680;i++){
        afterNorm[i]=0;
    }
    float tmp_sum=0;
    float tmp_square_sum=0;
    for(int i=0;i<196*7;i++){
        norm1_mean[i]=0.;
        norm1_var[i]=0.;
    }
	for (int c = 0; c < 80; c++)
	{
		norm1_weight[c] = parameterData["stage3.1.norm.norm.weight"][c];
		norm1_bias[c]  = parameterData["stage3.1.norm.norm.bias"][c];
        norm1_weight[c+80*1] = parameterData["stage3.2.norm.norm.weight"][c];
		norm1_bias[c+80*1]  = parameterData["stage3.2.norm.norm.bias"][c];
        norm1_weight[c+80*2] = parameterData["stage3.3.norm.norm.weight"][c];
		norm1_bias[c+80*2]  = parameterData["stage3.3.norm.norm.bias"][c];
		norm1_weight[c+80*3] = parameterData["stage3.4.norm.norm.weight"][c];
		norm1_bias[c+80*3]  = parameterData["stage3.4.norm.norm.bias"][c];
		norm1_weight[c+80*4] = parameterData["stage3.5.norm.norm.weight"][c];
		norm1_bias[c+80*4]  = parameterData["stage3.5.norm.norm.bias"][c];
		norm1_weight[c+80*5] = parameterData["stage3.6.norm.norm.weight"][c];
		norm1_bias[c+80*5]  = parameterData["stage3.6.norm.norm.bias"][c];
		norm1_weight[c+80*6] = parameterData["stage3.7.norm.norm.weight"][c];
		norm1_bias[c+80*6]  = parameterData["stage3.7.norm.norm.bias"][c];
	}
    for(int i=0;i<15680;i++){
        afterRearrangeX[i]=0;
    }
    for(int i=0;i<31360;i++){
        afterConv1[i]=0;
    }
    for (int k = 0; k < 160; k++)
    {
        bias1[k] = parameterData["stage3.1.qk.conv.bias"][k];
        bias1[k+160*1] = parameterData["stage3.2.qk.conv.bias"][k];
        bias1[k+160*2] = parameterData["stage3.3.qk.conv.bias"][k];
        bias1[k+160*3] = parameterData["stage3.4.qk.conv.bias"][k];
        bias1[k+160*4] = parameterData["stage3.5.qk.conv.bias"][k];
        bias1[k+160*5] = parameterData["stage3.6.qk.conv.bias"][k];
        bias1[k+160*6] = parameterData["stage3.7.qk.conv.bias"][k];
        for (int l = 0; l < 80; l++)
        {
            for (int i = 0; i < 1; i++)
            {
                for (int j = 0; j < 1; j++)
                {
                    kernel1[k*80*1*1+l*1*1+i*1+j] = parameterData["stage3.1.qk.conv.weight"][k*80+l];
                    kernel1[(k+160*1)*80*1*1+l*1*1+i*1+j] = parameterData["stage3.2.qk.conv.weight"][k*80+l];
                    kernel1[(k+160*2)*80*1*1+l*1*1+i*1+j] = parameterData["stage3.3.qk.conv.weight"][k*80+l];
                    kernel1[(k+160*3)*80*1*1+l*1*1+i*1+j] = parameterData["stage3.4.qk.conv.weight"][k*80+l];
                    kernel1[(k+160*4)*80*1*1+l*1*1+i*1+j] = parameterData["stage3.5.qk.conv.weight"][k*80+l];
                    kernel1[(k+160*5)*80*1*1+l*1*1+i*1+j] = parameterData["stage3.6.qk.conv.weight"][k*80+l];
                    kernel1[(k+160*6)*80*1*1+l*1*1+i*1+j] = parameterData["stage3.7.qk.conv.weight"][k*80+l];
                }
            }
        }
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
    }
    for(int i=0;i<47040;i++){
        afterConv2[i]=0;
    }

    for (int k = 0; k < 240; k++)
    {
        bias2[k] = parameterData["stage3.1.v.conv.bias"][k];
        bias2[k+240*1] = parameterData["stage3.2.v.conv.bias"][k];
        bias2[k+240*2] = parameterData["stage3.3.v.conv.bias"][k];
        bias2[k+240*3] = parameterData["stage3.4.v.conv.bias"][k];
        bias2[k+240*4] = parameterData["stage3.5.v.conv.bias"][k];
        bias2[k+240*5] = parameterData["stage3.6.v.conv.bias"][k];
        bias2[k+240*6] = parameterData["stage3.7.v.conv.bias"][k];
        for (int l = 0; l < 80; l++)
        {
            for (int i = 0; i < 1; i++)
            {
                for (int j = 0; j < 1; j++)
                {
                    kernel2[k*80*1*1+l*1*1+i*1+j] = parameterData["stage3.1.v.conv.weight"][k*80+l];
                    kernel2[(k+240*1)*80*1*1+l*1*1+i*1+j] = parameterData["stage3.2.v.conv.weight"][k*80+l];
                    kernel2[(k+240*2)*80*1*1+l*1*1+i*1+j] = parameterData["stage3.3.v.conv.weight"][k*80+l];
                    kernel2[(k+240*3)*80*1*1+l*1*1+i*1+j] = parameterData["stage3.4.v.conv.weight"][k*80+l];
                    kernel2[(k+240*4)*80*1*1+l*1*1+i*1+j] = parameterData["stage3.5.v.conv.weight"][k*80+l];
                    kernel2[(k+240*5)*80*1*1+l*1*1+i*1+j] = parameterData["stage3.6.v.conv.weight"][k*80+l];
                    kernel2[(k+240*6)*80*1*1+l*1*1+i*1+j] = parameterData["stage3.7.v.conv.weight"][k*80+l];
                }
            }
        }
    }
    for(int i=0;i<47040;i++){
        afterAct2[i]=0;
        buffer_out[i]=0;
    }
    for(int i=0;i<47040;i++){
        buffer_result[i]=0;
    }

    for (int i = 0; i < Y_PROJ_1_SIZE; i++)
    {
        Y_proj_1[i] = 0;
        Y_skip_1[i] = 0;
    }
    
    for (int i = 0; i < Y_V_CONV_1_SIZE; i++)
    {
        Y_dw_conv_1[i] = 0;
        Y_dw_norm_1[i] = 0;
        Y_dw_act_1[i] = 0;
        Y_dw_skip_1[i] = 0;
    }


    for (int i = 0; i < 240*1; i++)
    {
        dw_norm_1_weight[i] = parameterData["stage3.1.conv_local.norm.weight"][i];
        dw_norm_1_bias[i] = parameterData["stage3.1.conv_local.norm.bias"][i];
        dw_norm_1_mean[i] = parameterData["stage3.1.conv_local.norm.running_mean"][i];
        dw_norm_1_var[i] = parameterData["stage3.1.conv_local.norm.running_var"][i];
        dw_norm_1_weight[i+240*1] = parameterData["stage3.2.conv_local.norm.weight"][i];
        dw_norm_1_bias[i+240*1] = parameterData["stage3.2.conv_local.norm.bias"][i];
        dw_norm_1_mean[i+240*1] = parameterData["stage3.2.conv_local.norm.running_mean"][i];
        dw_norm_1_var[i+240*1] = parameterData["stage3.2.conv_local.norm.running_var"][i];
        dw_norm_1_weight[i+240*2] = parameterData["stage3.3.conv_local.norm.weight"][i];
        dw_norm_1_bias[i+240*2] = parameterData["stage3.3.conv_local.norm.bias"][i];
        dw_norm_1_mean[i+240*2] = parameterData["stage3.3.conv_local.norm.running_mean"][i];
        dw_norm_1_var[i+240*2] = parameterData["stage3.3.conv_local.norm.running_var"][i];
        dw_norm_1_weight[i+240*3] = parameterData["stage3.4.conv_local.norm.weight"][i];
        dw_norm_1_bias[i+240*3] = parameterData["stage3.4.conv_local.norm.bias"][i];
        dw_norm_1_mean[i+240*3] = parameterData["stage3.4.conv_local.norm.running_mean"][i];
        dw_norm_1_var[i+240*3] = parameterData["stage3.4.conv_local.norm.running_var"][i];
        dw_norm_1_weight[i+240*4] = parameterData["stage3.5.conv_local.norm.weight"][i];
        dw_norm_1_bias[i+240*4] = parameterData["stage3.5.conv_local.norm.bias"][i];
        dw_norm_1_mean[i+240*4] = parameterData["stage3.5.conv_local.norm.running_mean"][i];
        dw_norm_1_var[i+240*4] = parameterData["stage3.5.conv_local.norm.running_var"][i];
        dw_norm_1_weight[i+240*5] = parameterData["stage3.6.conv_local.norm.weight"][i];
        dw_norm_1_bias[i+240*5] = parameterData["stage3.6.conv_local.norm.bias"][i];
        dw_norm_1_mean[i+240*5] = parameterData["stage3.6.conv_local.norm.running_mean"][i];
        dw_norm_1_var[i+240*5] = parameterData["stage3.6.conv_local.norm.running_var"][i];
        dw_norm_1_weight[i+240*6] = parameterData["stage3.7.conv_local.norm.weight"][i];
        dw_norm_1_bias[i+240*6] = parameterData["stage3.7.conv_local.norm.bias"][i];
        dw_norm_1_mean[i+240*6] = parameterData["stage3.7.conv_local.norm.running_mean"][i];
        dw_norm_1_var[i+240*6] = parameterData["stage3.7.conv_local.norm.running_var"][i];
    }
    for (int i = 0; i < 6000; i++){
        dw_conv_1_filter[i] = parameterData["stage3.1.conv_local.conv.weight"][i];
        dw_conv_1_filter[i+6000*1] = parameterData["stage3.2.conv_local.conv.weight"][i];
        dw_conv_1_filter[i+6000*2] = parameterData["stage3.3.conv_local.conv.weight"][i];
        dw_conv_1_filter[i+6000*3] = parameterData["stage3.4.conv_local.conv.weight"][i];
        dw_conv_1_filter[i+6000*4] = parameterData["stage3.5.conv_local.conv.weight"][i];
        dw_conv_1_filter[i+6000*5] = parameterData["stage3.6.conv_local.conv.weight"][i];
        dw_conv_1_filter[i+6000*6] = parameterData["stage3.7.conv_local.conv.weight"][i];

    }
    
    for (int i = 0; i < 19200*1; i++){
        proj_1_weight[i] = parameterData["stage3.1.proj.conv.weight"][i];
        proj_1_weight[i+19200*1] = parameterData["stage3.2.proj.conv.weight"][i];
        proj_1_weight[i+19200*2] = parameterData["stage3.3.proj.conv.weight"][i];
        proj_1_weight[i+19200*3] = parameterData["stage3.4.proj.conv.weight"][i];
        proj_1_weight[i+19200*4] = parameterData["stage3.5.proj.conv.weight"][i];
        proj_1_weight[i+19200*5] = parameterData["stage3.6.proj.conv.weight"][i];
        proj_1_weight[i+19200*6] = parameterData["stage3.7.proj.conv.weight"][i];

    }
    // execution
    kernel_stage3(X_data, norm_0_weight, norm_0_bias, v_conv_0_weight, v_conv_0_bias,
                dw_conv_0_filter, dw_norm_0_weight, dw_norm_0_bias, dw_norm_0_mean, dw_norm_0_var,
                proj_0_weight, Y_norm_0, Y_v_conv_0, Y_v_act_0, Y_dw_conv_0, Y_dw_norm_0, Y_dw_act_0,
                result_30, afterNorm,
                norm1_mean, norm1_var, norm1_weight, norm1_bias,
                afterRearrangeX,
                afterConv1,
                kernel1,
                bias1,
                in_q,
                in_k,
                afterQKMultiplication,
                afterSoftmax,
                afterRearrangeX2,
                afterQKXMultiplication,
                afterRearrangeQKX,
                afterConv2,
                kernel2,
                bias2,
                afterAct2,
                buffer_out,
                buffer_result,
                dw_conv_1_filter, dw_norm_1_weight, dw_norm_1_bias, dw_norm_1_mean, dw_norm_1_var,
                proj_1_weight, Y_dw_conv_1, Y_dw_norm_1, Y_dw_act_1, Y_proj_1,
                Y_dw_skip_1, Y_skip_1
                );

    
    cout << "stage 3.0 result" << endl;
    cout << "[0, 0, :7, :7]" << endl;
    for (int b = 0; b < 1; b++) {
        for (int c = 0; c < 1; c++) {
            for (int h = 0; h < 7; h++) {
                for (int w = 0; w < 7; w++) {
                    cout << result_30[b*80*14*14 + c*14*14 + h*14 + w] << " ";
                }
                cout << endl;
            }
        }
    }
    cout << "[0, 79, 7:14, 7:14]" << endl;
    for (int b = 0; b < 1; b++) {
        for (int c = 79; c < 80; c++) {
            for (int h = 7; h < 14; h++) {
                for (int w = 7; w < 14; w++) {
                    cout << result_30[b*80*14*14 + c*14*14 + h*14 + w] << " ";
                }
                cout << endl;
            }
        }
    }

    for(int i=0;i<Y_PROJ_1_SIZE;i++){
        //std::cout<<Y_proj_1[i]<<" ";
      std::cout<<std::setprecision(10)<<Y_skip_1[i]<<" ";
    }
    std::cout<<"\n";
    return EXIT_SUCCESS;
}
