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
const int Y_V_CONV_1_SIZE = 225792;
const int Y_PROJ_1_SIZE = 15680;
const int Y_V_CONV_2_SIZE = 47040;
// depth 0
float norm_0_weight[48], norm_0_bias[48], norm_0_running_mean[48], norm_0_running_var[48];
float v_conv_0_weight[13824], v_conv_0_bias[288];
float dw_conv_0_filter[2592], dw_norm_0_weight[288], dw_norm_0_bias[288], dw_norm_0_mean[288], dw_norm_0_var[288];
float proj_0_weight[23040];
// depth 1
float norm_2_weight[80], norm_2_bias[80], norm_2_running_mean[80], norm_2_running_var[80];
float v_conv_2_weight[19200], v_conv_2_bias[240];
float dw_conv_2_filter[2160], dw_norm_2_gamma[240], dw_norm_2_beta[240], dw_norm_2_mean[240], dw_norm_2_var[240];
float proj_2_weight[19200];

float X_data[X_DATA_SIZE];
float Y_norm_0[X_DATA_SIZE];
float Y_v_conv_0[Y_V_CONV_1_SIZE], Y_v_act_0[Y_V_CONV_1_SIZE];
float Y_dw_conv_0[X_DATA_SIZE], Y_dw_norm_0[X_DATA_SIZE], Y_dw_act_0[X_DATA_SIZE];
//float Y_proj_1[Y_PROJ_1_SIZE];

float Y_norm_2[Y_PROJ_1_SIZE];
float Y_v_conv_2[Y_V_CONV_2_SIZE];
float Y_dw_conv_2[Y_V_CONV_2_SIZE], Y_dw_norm_2[Y_V_CONV_2_SIZE], Y_dw_act_2[Y_V_CONV_2_SIZE], Y_dw_skip_2[Y_V_CONV_2_SIZE];
float Y_proj_2[Y_PROJ_1_SIZE];
float Y_skip_2[Y_PROJ_1_SIZE];

float result_30[15680];
float atten_norm[15680];
float norm1_mean[196]; 
float norm1_var[196]; 
float norm1_weight[15680]; 
float norm1_bias[15680]; 
float norm1_ln_in[15680];
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
float in1_stream[38416];
float sumQK[2401];
float sumQKX[980];
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
    for (int i = 0; i < 2592; i++) dw_conv_0_filter[i] = parameterData["stage3.0.conv_local.conv.weight"][i];
    for (int i = 0; i < 288; i++) dw_norm_0_weight[i] = parameterData["stage3.0.conv_local.norm.weight"][i];
    for (int i = 0; i < 288; i++) dw_norm_0_bias[i] = parameterData["stage3.0.conv_local.norm.bias"][i];
    for (int i = 0; i < 288; i++) dw_norm_0_mean[i] = parameterData["stage3.0.conv_local.norm.running_mean"][i];
    for (int i = 0; i < 288; i++) dw_norm_0_var[i] = parameterData["stage3.0.conv_local.norm.running_var"][i];
    for (int i = 0; i < 23040; i++) proj_0_weight[i] = parameterData["stage3.0.proj.conv.weight"][i];

    // init out
    for (int i = 0; i < 15680; i++) result_30[i] = 0;
    // execution
    kernel_stage3(X_data, norm_0_weight, norm_0_bias, v_conv_0_weight, v_conv_0_bias,
                dw_conv_0_filter, dw_norm_0_weight, dw_norm_0_bias, dw_norm_0_mean, dw_norm_0_var,
                proj_0_weight, Y_norm_0, Y_v_conv_0, Y_v_act_0, Y_dw_conv_0, Y_dw_norm_0, Y_dw_act_0,
                result_30, atten_norm,
                norm1_mean, norm1_var, norm1_weight, norm1_bias, norm1_ln_in,
                afterPad, afterRearrangeX, afterPad1, afterConv1,
                kernel1, bias1, in_qk, in_q, in_k,
                afterQKMultiplication, afterSoftmax, afterRearrangeX2, afterQKXMultiplication,
                afterRearrangeQKX, afterPad2, afterConv2,
                kernel2, bias2, afterAct2, QKV,
                buffer_out, in1_stream, sumQK, sumQKX,
                buffer_result,
                dw_conv_2_filter, dw_norm_2_gamma, dw_norm_2_beta, dw_norm_2_mean, dw_norm_2_var,
                proj_2_weight,
                Y_dw_conv_2, Y_dw_norm_2, Y_dw_act_2, Y_proj_2,
                Y_dw_skip_2, Y_skip_2
                );

    cout << "after DW act [0, 0, :7, :7]" << endl;
    for (int b = 0; b < 1; b++) {
        for (int c = 0; c < 1; c++) {
            for (int h = 0; h < 7; h++) {
                for (int w = 0; w < 7; w++) {
                    cout << Y_dw_act_0[b*288*14*14 + c*14*14+ h*14 + w] << " ";
                }
                cout << endl;
            }
        }
    }    
    cout << "stage 3.0 result" << endl;
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

    std::cout<<"\n";
    return EXIT_SUCCESS;
}
