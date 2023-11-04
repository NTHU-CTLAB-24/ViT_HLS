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

// depth 0
float norm_0_weight_3[48] = {0}, norm_0_bias_3[48] = {0};
float v_conv_0_weight_3[13824] = {0}, v_conv_0_bias_3[288] = {0};
float dw_conv_0_filter_3[7200] = {0}, dw_norm_0_weight_3[288] = {0}, dw_norm_0_bias_3[288] = {0}, dw_norm_0_mean_3[288] = {0}, dw_norm_0_var_3[288] = {0};
float proj_0_weight_3[23040] = {0};

float X_data[37632] = {0};
float Y_norm_0_3[37632] = {0};
float Y_v_conv_0_3[225792] = {0}, Y_v_act_0_3[225792] = {0};
float Y_dw_conv_0_3[56448] = {0}, Y_dw_norm_0_3[56448] = {0}, Y_dw_act_0_3[56448] = {0};
// use count_depth to define size
// depth 1-7
float dw_conv_1_filter_3[6000*7] = {0}, dw_norm_1_weight_3[240*7] = {0}, dw_norm_1_bias_3[240*7] = {0}, dw_norm_1_mean_3[240*7] = {0}, dw_norm_1_var_3[240*7] = {0};
float proj_1_weight_3[19200*7] = {0};


float Y_dw_conv_1_3[47040] = {0}, Y_dw_norm_1_3[47040] = {0}, Y_dw_act_1_3[47040] = {0}, Y_dw_skip_1_3[47040] = {0};
float Y_proj_1_3[15680] = {0};
float Y_skip_1_3[15680] = {0};

float result_30[15680] = {0};
float afterNorm_3[15680] = {0};

float norm1_mean_3[196*7] = {0}; 
float norm1_var_3[196*7] = {0}; 
float norm1_weight_3[80*7] = {0}; 
float norm1_bias_3[80*7] = {0};

float afterRearrangeX_3[15680] = {0};
float afterConv1_3[31360] = {0};

float kernel1_3[12800*7] = {0};
float bias1_3[160*7] = {0};

float in_q_3[15680] = {0};
float in_k_3[15680] = {0};
float afterQKMultiplication_3[38416] = {0};
float afterSoftmax_3[38416] = {0};
float afterRearrangeX2_3[15680] = {0};
float afterQKXMultiplication_3[15680] = {0};
float afterRearrangeQKX_3[15680] = {0};
float afterConv2_3[47040] = {0};

float kernel2_3[19200*7] = {0};
float bias2_3[240*7] = {0};

float afterAct2_3[47040] = {0};
float buffer_out_3[47040] = {0};
float buffer_result_3[47040] = {0};

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
    for (int i = 0; i < 48; i++) norm_0_weight_3[i] = parameterData["stage3.0.norm.norm.weight"][i];
    for (int i = 0; i < 48; i++) norm_0_bias_3[i] = parameterData["stage3.0.norm.norm.bias"][i];
    for (int i = 0; i < 13824; i++) v_conv_0_weight_3[i] = parameterData["stage3.0.v.conv.weight"][i];
    for (int i = 0; i < 288; i++) v_conv_0_bias_3[i] = parameterData["stage3.0.v.conv.bias"][i];
    for (int i = 0; i < 7200; i++) dw_conv_0_filter_3[i] = parameterData["stage3.0.conv_local.conv.weight"][i];   
    for (int i = 0; i < 288; i++) dw_norm_0_weight_3[i] = parameterData["stage3.0.conv_local.norm.weight"][i];    
    for (int i = 0; i < 288; i++) dw_norm_0_bias_3[i] = parameterData["stage3.0.conv_local.norm.bias"][i];        
    for (int i = 0; i < 288; i++) dw_norm_0_mean_3[i] = parameterData["stage3.0.conv_local.norm.running_mean"][i];
    for (int i = 0; i < 288; i++) dw_norm_0_var_3[i] = parameterData["stage3.0.conv_local.norm.running_var"][i];  
    for (int i = 0; i < 23040; i++) proj_0_weight_3[i] = parameterData["stage3.0.proj.conv.weight"][i];

    // init out
	for (int c = 0; c < 80; c++)
	{
		norm1_weight_3[c] = parameterData["stage3.1.norm.norm.weight"][c];
		norm1_bias_3[c]  = parameterData["stage3.1.norm.norm.bias"][c];
        norm1_weight_3[c+80*1] = parameterData["stage3.2.norm.norm.weight"][c];
		norm1_bias_3[c+80*1]  = parameterData["stage3.2.norm.norm.bias"][c];
        norm1_weight_3[c+80*2] = parameterData["stage3.3.norm.norm.weight"][c];
		norm1_bias_3[c+80*2]  = parameterData["stage3.3.norm.norm.bias"][c];
		norm1_weight_3[c+80*3] = parameterData["stage3.4.norm.norm.weight"][c];
		norm1_bias_3[c+80*3]  = parameterData["stage3.4.norm.norm.bias"][c];
		norm1_weight_3[c+80*4] = parameterData["stage3.5.norm.norm.weight"][c];
		norm1_bias_3[c+80*4]  = parameterData["stage3.5.norm.norm.bias"][c];
		norm1_weight_3[c+80*5] = parameterData["stage3.6.norm.norm.weight"][c];
		norm1_bias_3[c+80*5]  = parameterData["stage3.6.norm.norm.bias"][c];
		norm1_weight_3[c+80*6] = parameterData["stage3.7.norm.norm.weight"][c];
		norm1_bias_3[c+80*6]  = parameterData["stage3.7.norm.norm.bias"][c];
	}
    for (int k = 0; k < 160; k++)
    {
        bias1_3[k] = parameterData["stage3.1.qk.conv.bias"][k];
        bias1_3[k+160*1] = parameterData["stage3.2.qk.conv.bias"][k];
        bias1_3[k+160*2] = parameterData["stage3.3.qk.conv.bias"][k];
        bias1_3[k+160*3] = parameterData["stage3.4.qk.conv.bias"][k];
        bias1_3[k+160*4] = parameterData["stage3.5.qk.conv.bias"][k];
        bias1_3[k+160*5] = parameterData["stage3.6.qk.conv.bias"][k];
        bias1_3[k+160*6] = parameterData["stage3.7.qk.conv.bias"][k];
        for (int l = 0; l < 80; l++)
        {
            for (int i = 0; i < 1; i++)
            {
                for (int j = 0; j < 1; j++)
                {
                    kernel1_3[k*80*1*1+l*1*1+i*1+j] = parameterData["stage3.1.qk.conv.weight"][k*80+l];
                    kernel1_3[(k+160*1)*80*1*1+l*1*1+i*1+j] = parameterData["stage3.2.qk.conv.weight"][k*80+l];
                    kernel1_3[(k+160*2)*80*1*1+l*1*1+i*1+j] = parameterData["stage3.3.qk.conv.weight"][k*80+l];
                    kernel1_3[(k+160*3)*80*1*1+l*1*1+i*1+j] = parameterData["stage3.4.qk.conv.weight"][k*80+l];
                    kernel1_3[(k+160*4)*80*1*1+l*1*1+i*1+j] = parameterData["stage3.5.qk.conv.weight"][k*80+l];
                    kernel1_3[(k+160*5)*80*1*1+l*1*1+i*1+j] = parameterData["stage3.6.qk.conv.weight"][k*80+l];
                    kernel1_3[(k+160*6)*80*1*1+l*1*1+i*1+j] = parameterData["stage3.7.qk.conv.weight"][k*80+l];
                }
            }
        }
    }
    for (int k = 0; k < 240; k++)
    {
        bias2_3[k] = parameterData["stage3.1.v.conv.bias"][k];
        bias2_3[k+240*1] = parameterData["stage3.2.v.conv.bias"][k];
        bias2_3[k+240*2] = parameterData["stage3.3.v.conv.bias"][k];
        bias2_3[k+240*3] = parameterData["stage3.4.v.conv.bias"][k];
        bias2_3[k+240*4] = parameterData["stage3.5.v.conv.bias"][k];
        bias2_3[k+240*5] = parameterData["stage3.6.v.conv.bias"][k];
        bias2_3[k+240*6] = parameterData["stage3.7.v.conv.bias"][k];
        for (int l = 0; l < 80; l++)
        {
            for (int i = 0; i < 1; i++)
            {
                for (int j = 0; j < 1; j++)
                {
                    kernel2_3[k*80*1*1+l*1*1+i*1+j] = parameterData["stage3.1.v.conv.weight"][k*80+l];
                    kernel2_3[(k+240*1)*80*1*1+l*1*1+i*1+j] = parameterData["stage3.2.v.conv.weight"][k*80+l];
                    kernel2_3[(k+240*2)*80*1*1+l*1*1+i*1+j] = parameterData["stage3.3.v.conv.weight"][k*80+l];
                    kernel2_3[(k+240*3)*80*1*1+l*1*1+i*1+j] = parameterData["stage3.4.v.conv.weight"][k*80+l];
                    kernel2_3[(k+240*4)*80*1*1+l*1*1+i*1+j] = parameterData["stage3.5.v.conv.weight"][k*80+l];
                    kernel2_3[(k+240*5)*80*1*1+l*1*1+i*1+j] = parameterData["stage3.6.v.conv.weight"][k*80+l];
                    kernel2_3[(k+240*6)*80*1*1+l*1*1+i*1+j] = parameterData["stage3.7.v.conv.weight"][k*80+l];
                }
            }
        }
    }
    for (int i = 0; i < 240*1; i++)
    {
        dw_norm_1_weight_3[i] = parameterData["stage3.1.conv_local.norm.weight"][i];
        dw_norm_1_bias_3[i] = parameterData["stage3.1.conv_local.norm.bias"][i];
        dw_norm_1_mean_3[i] = parameterData["stage3.1.conv_local.norm.running_mean"][i];
        dw_norm_1_var_3[i] = parameterData["stage3.1.conv_local.norm.running_var"][i];
        dw_norm_1_weight_3[i+240*1] = parameterData["stage3.2.conv_local.norm.weight"][i];
        dw_norm_1_bias_3[i+240*1] = parameterData["stage3.2.conv_local.norm.bias"][i];
        dw_norm_1_mean_3[i+240*1] = parameterData["stage3.2.conv_local.norm.running_mean"][i];
        dw_norm_1_var_3[i+240*1] = parameterData["stage3.2.conv_local.norm.running_var"][i];
        dw_norm_1_weight_3[i+240*2] = parameterData["stage3.3.conv_local.norm.weight"][i];
        dw_norm_1_bias_3[i+240*2] = parameterData["stage3.3.conv_local.norm.bias"][i];
        dw_norm_1_mean_3[i+240*2] = parameterData["stage3.3.conv_local.norm.running_mean"][i];
        dw_norm_1_var_3[i+240*2] = parameterData["stage3.3.conv_local.norm.running_var"][i];
        dw_norm_1_weight_3[i+240*3] = parameterData["stage3.4.conv_local.norm.weight"][i];
        dw_norm_1_bias_3[i+240*3] = parameterData["stage3.4.conv_local.norm.bias"][i];
        dw_norm_1_mean_3[i+240*3] = parameterData["stage3.4.conv_local.norm.running_mean"][i];
        dw_norm_1_var_3[i+240*3] = parameterData["stage3.4.conv_local.norm.running_var"][i];
        dw_norm_1_weight_3[i+240*4] = parameterData["stage3.5.conv_local.norm.weight"][i];
        dw_norm_1_bias_3[i+240*4] = parameterData["stage3.5.conv_local.norm.bias"][i];
        dw_norm_1_mean_3[i+240*4] = parameterData["stage3.5.conv_local.norm.running_mean"][i];
        dw_norm_1_var_3[i+240*4] = parameterData["stage3.5.conv_local.norm.running_var"][i];
        dw_norm_1_weight_3[i+240*5] = parameterData["stage3.6.conv_local.norm.weight"][i];
        dw_norm_1_bias_3[i+240*5] = parameterData["stage3.6.conv_local.norm.bias"][i];
        dw_norm_1_mean_3[i+240*5] = parameterData["stage3.6.conv_local.norm.running_mean"][i];
        dw_norm_1_var_3[i+240*5] = parameterData["stage3.6.conv_local.norm.running_var"][i];
        dw_norm_1_weight_3[i+240*6] = parameterData["stage3.7.conv_local.norm.weight"][i];
        dw_norm_1_bias_3[i+240*6] = parameterData["stage3.7.conv_local.norm.bias"][i];
        dw_norm_1_mean_3[i+240*6] = parameterData["stage3.7.conv_local.norm.running_mean"][i];
        dw_norm_1_var_3[i+240*6] = parameterData["stage3.7.conv_local.norm.running_var"][i];
    }
    for (int i = 0; i < 6000; i++){
        dw_conv_1_filter_3[i] = parameterData["stage3.1.conv_local.conv.weight"][i];
        dw_conv_1_filter_3[i+6000*1] = parameterData["stage3.2.conv_local.conv.weight"][i];
        dw_conv_1_filter_3[i+6000*2] = parameterData["stage3.3.conv_local.conv.weight"][i];
        dw_conv_1_filter_3[i+6000*3] = parameterData["stage3.4.conv_local.conv.weight"][i];
        dw_conv_1_filter_3[i+6000*4] = parameterData["stage3.5.conv_local.conv.weight"][i];
        dw_conv_1_filter_3[i+6000*5] = parameterData["stage3.6.conv_local.conv.weight"][i];
        dw_conv_1_filter_3[i+6000*6] = parameterData["stage3.7.conv_local.conv.weight"][i];

    }
    
    for (int i = 0; i < 19200*1; i++){
        proj_1_weight_3[i] = parameterData["stage3.1.proj.conv.weight"][i];
        proj_1_weight_3[i+19200*1] = parameterData["stage3.2.proj.conv.weight"][i];
        proj_1_weight_3[i+19200*2] = parameterData["stage3.3.proj.conv.weight"][i];
        proj_1_weight_3[i+19200*3] = parameterData["stage3.4.proj.conv.weight"][i];
        proj_1_weight_3[i+19200*4] = parameterData["stage3.5.proj.conv.weight"][i];
        proj_1_weight_3[i+19200*5] = parameterData["stage3.6.proj.conv.weight"][i];
        proj_1_weight_3[i+19200*6] = parameterData["stage3.7.proj.conv.weight"][i];
    }
    // execution
    kernel_stage3(X_data, norm_0_weight_3, norm_0_bias_3, v_conv_0_weight_3, v_conv_0_bias_3,
                dw_conv_0_filter_3, dw_norm_0_weight_3, dw_norm_0_bias_3, dw_norm_0_mean_3, dw_norm_0_var_3,
                proj_0_weight_3, Y_norm_0_3, Y_v_conv_0_3, Y_v_act_0_3, Y_dw_conv_0_3, Y_dw_norm_0_3, Y_dw_act_0_3,
                result_30, afterNorm_3,
                norm1_mean_3, norm1_var_3, norm1_weight_3, norm1_bias_3,
                afterRearrangeX_3,
                afterConv1_3,
                kernel1_3,
                bias1_3,
                in_q_3,
                in_k_3,
                afterQKMultiplication_3,
                afterSoftmax_3,
                afterRearrangeX2_3,
                afterQKXMultiplication_3,
                afterRearrangeQKX_3,
                afterConv2_3,
                kernel2_3,
                bias2_3,
                afterAct2_3,
                buffer_out_3,
                buffer_result_3,
                dw_conv_1_filter_3, dw_norm_1_weight_3, dw_norm_1_bias_3, dw_norm_1_mean_3, dw_norm_1_var_3,
                proj_1_weight_3, Y_dw_conv_1_3, Y_dw_norm_1_3, Y_dw_act_1_3, Y_proj_1_3,
                Y_dw_skip_1_3, Y_skip_1_3
                );

    
    cout << "stage 3.0 result" << endl;
    cout << "[0, 0, :8, :8]" << endl;
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

    cout << "stage 3 result" << endl;
    for (int b = 0; b < 1; b++) {
        for (int c = 0; c < 1; c++) {
            for (int h = 0; h < 8; h++) {
                for (int w = 0; w < 8; w++) {
                    cout << Y_skip_1_3[b*80*14*14 + c*14*14 + h*14 + w] << " ";
                }
                cout << endl;
            }
        }
    }
    // cout << "[0, 79, 7:14, 7:14]" << endl;
    // for (int b = 0; b < 1; b++) {
    //     for (int c = 79; c < 80; c++) {
    //         for (int h = 7; h < 14; h++) {
    //             for (int w = 7; w < 14; w++) {
    //                 cout << result_30[b*80*14*14 + c*14*14 + h*14 + w] << " ";
    //             }
    //             cout << endl;
    //         }
    //     }
    // }

    // for(int i=0;i<15680;i++){
    //     //std::cout<<Y_proj_1_3[i]<<" ";
    //   std::cout<<std::setprecision(10)<<Y_skip_1_3[i]<<" ";
    // }
    std::cout<<"\n";
    return EXIT_SUCCESS;
}
