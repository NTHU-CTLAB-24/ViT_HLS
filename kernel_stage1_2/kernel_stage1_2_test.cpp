#include "kernel_stage1_2.hpp"
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
const int CHANNEL_IN = 24;
const int HEIGHT_IN = 112;
const int WIDTH_IN = 112;
const int CHANNEL_OUT = 48;
const int HEIGHT_OUT = 28;
const int WIDTH_OUT = 28;

// below size please check count_depth output to modify corresponding

// use count_depth to define size
// stage 1 depth 1
float norm_1_1_weight[24], norm_1_1_bias[24], norm_1_1_running_mean[24], norm_1_1_running_var[24];
float v_conv_1_1_weight[2304], v_conv_1_1_bias[96];
float dw_conv_1_1_filter[864], dw_norm_1_1_gamma[96], dw_norm_1_1_beta[96], dw_norm_1_1_mean[96], dw_norm_1_1_var[96];
float proj_1_1_weight[3072];
// stage 1 depth 2
float norm_1_2_weight[32], norm_1_2_bias[32], norm_1_2_running_mean[32], norm_1_2_running_var[32];
float v_conv_1_2_weight[2048], v_conv_1_2_bias[64];
float dw_conv_1_2_filter[576], dw_norm_1_2_gamma[64], dw_norm_1_2_beta[64], dw_norm_1_2_mean[64], dw_norm_1_2_var[64];
float proj_1_2_weight[2048];

// stage 2 depth 1
float norm_2_1_weight[32], norm_2_1_bias[32], norm_2_1_running_mean[32], norm_2_1_running_var[32];
float v_conv_2_1_weight[5120], v_conv_2_1_bias[160];
float dw_conv_2_1_filter[1440], dw_norm_2_1_gamma[160], dw_norm_2_1_beta[160], dw_norm_2_1_mean[160], dw_norm_2_1_var[160];
float proj_2_1_weight[7680];
// stage 2 depth 2
float norm_2_2_weight[48], norm_2_2_bias[48], norm_2_2_running_mean[48], norm_2_2_running_var[48];
float v_conv_2_2_weight[5760], v_conv_2_2_bias[120];
float dw_conv_2_2_filter[1080], dw_norm_2_2_gamma[120], dw_norm_2_2_beta[120], dw_norm_2_2_mean[120], dw_norm_2_2_var[120];
float proj_2_2_weight[5760];

float X_data[301056];

float Y_norm_1_1[301056] = {0};
float Y_v_conv_1_1[1204224] = {0}, Y_v_act_1_1[1204224] = {0};
float Y_dw_conv_1_1[301056] = {0}, Y_dw_norm_1_1[301056] = {0}, Y_dw_act_1_1[301056] = {0};
float Y_proj_1_1[100352] = {0};

float Y_norm_1_2[100352] = {0};
float Y_v_conv_1_2[200704] = {0}, Y_v_act_1_2[200704] = {0};
float Y_dw_conv_1_2[200704] = {0}, Y_dw_norm_1_2[200704] = {0}, Y_dw_act_1_2[200704] = {0}, Y_dw_skip_1_2[200704] = {0};
float Y_proj_1_2[100352] = {0};
float Y_skip_1_2[100352] = {0};

float Y_norm_2_1[100352] = {0};
float Y_v_conv_2_1[501760] = {0}, Y_v_act_2_1[501760] = {0};
float Y_dw_conv_2_1[125440] = {0}, Y_dw_norm_2_1[125440] = {0}, Y_dw_act_2_1[125440] = {0};
float Y_proj_2_1[37632] = {0};

float Y_norm_2_2[37632] = {0};
float Y_v_conv_2_2[94080] = {0}, Y_v_act_2_2[94080] = {0};
float Y_dw_conv_2_2[94080] = {0}, Y_dw_norm_2_2[94080] = {0}, Y_dw_act_2_2[94080] = {0}, Y_dw_skip_2_2[94080] = {0};
float Y_proj_2_2[37632] = {0};
float Y_skip_2_2[37632] = {0};

int main()
{
    // init in
    for (int n = 0; n < BATCH_SIZE; n++)
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


    // init parameters value
    unordered_map<string, vector<float>> parameterData;
    string line;
    string current_key;

    ifstream file_1("./stage1_parameters.txt");
    if (!file_1.is_open())
        cerr << "Failed to open the parameter file_1." << std::endl;
    
    while (std::getline(file_1, line))
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

    for (int i = 0; i < 24; i++) norm_1_1_weight[i] = parameterData["stage1.0.norm.weight"][i];
    for (int i = 0; i < 24; i++) norm_1_1_bias[i] = parameterData["stage1.0.norm.bias"][i];
    for (int i = 0; i < 24; i++) norm_1_1_running_mean[i] = parameterData["stage1.0.norm.running_mean"][i];
    for (int i = 0; i < 24; i++) norm_1_1_running_var[i] = parameterData["stage1.0.norm.running_var"][i];
    for (int i = 0; i < 2304; i++) v_conv_1_1_weight[i] = parameterData["stage1.0.v.conv.weight"][i];
    for (int i = 0; i < 96; i++) v_conv_1_1_bias[i] = parameterData["stage1.0.v.conv.bias"][i];
    for (int i = 0; i < 864; i++) dw_conv_1_1_filter[i] = parameterData["stage1.0.conv_local.conv.weight"][i];
    for (int i = 0; i < 96; i++) dw_norm_1_1_gamma[i] = parameterData["stage1.0.conv_local.norm.weight"][i];
    for (int i = 0; i < 96; i++) dw_norm_1_1_beta[i] = parameterData["stage1.0.conv_local.norm.bias"][i];
    for (int i = 0; i < 96; i++) dw_norm_1_1_mean[i] = parameterData["stage1.0.conv_local.norm.running_mean"][i];
    for (int i = 0; i < 96; i++) dw_norm_1_1_var[i] = parameterData["stage1.0.conv_local.norm.running_var"][i];
    for (int i = 0; i < 3072; i++) proj_1_1_weight[i] = parameterData["stage1.0.proj.conv.weight"][i];
    for (int i = 0; i < 32; i++) norm_1_2_weight[i] = parameterData["stage1.1.norm.weight"][i];
    for (int i = 0; i < 32; i++) norm_1_2_bias[i] = parameterData["stage1.1.norm.bias"][i];
    for (int i = 0; i < 32; i++) norm_1_2_running_mean[i] = parameterData["stage1.1.norm.running_mean"][i];
    for (int i = 0; i < 32; i++) norm_1_2_running_var[i] = parameterData["stage1.1.norm.running_var"][i];
    for (int i = 0; i < 2048; i++) v_conv_1_2_weight[i] = parameterData["stage1.1.v.conv.weight"][i];
    for (int i = 0; i < 64; i++) v_conv_1_2_bias[i] = parameterData["stage1.1.v.conv.bias"][i];
    for (int i = 0; i < 576; i++) dw_conv_1_2_filter[i] = parameterData["stage1.1.conv_local.conv.weight"][i];
    for (int i = 0; i < 64; i++) dw_norm_1_2_gamma[i] = parameterData["stage1.1.conv_local.norm.weight"][i];
    for (int i = 0; i < 64; i++) dw_norm_1_2_beta[i] = parameterData["stage1.1.conv_local.norm.bias"][i];
    for (int i = 0; i < 64; i++) dw_norm_1_2_mean[i] = parameterData["stage1.1.conv_local.norm.running_mean"][i];
    for (int i = 0; i < 64; i++) dw_norm_1_2_var[i] = parameterData["stage1.1.conv_local.norm.running_var"][i];
    for (int i = 0; i < 2048; i++) proj_1_2_weight[i] = parameterData["stage1.1.proj.conv.weight"][i];

    ifstream file_2("./stage2_parameters.txt");
    if (!file_2.is_open())
        cerr << "Failed to open the parameter file_2." << std::endl;
    
    while (std::getline(file_2, line))
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

    for (int i = 0; i < 32; i++) norm_2_1_weight[i] = parameterData["stage2.0.norm.weight"][i];
    for (int i = 0; i < 32; i++) norm_2_1_bias[i] = parameterData["stage2.0.norm.bias"][i];
    for (int i = 0; i < 32; i++) norm_2_1_running_mean[i] = parameterData["stage2.0.norm.running_mean"][i];
    for (int i = 0; i < 32; i++) norm_2_1_running_var[i] = parameterData["stage2.0.norm.running_var"][i];
    for (int i = 0; i < 5120; i++) v_conv_2_1_weight[i] = parameterData["stage2.0.v.conv.weight"][i];
    for (int i = 0; i < 160; i++) v_conv_2_1_bias[i] = parameterData["stage2.0.v.conv.bias"][i];
    for (int i = 0; i < 1440; i++) dw_conv_2_1_filter[i] = parameterData["stage2.0.conv_local.conv.weight"][i];
    for (int i = 0; i < 160; i++) dw_norm_2_1_gamma[i] = parameterData["stage2.0.conv_local.norm.weight"][i];
    for (int i = 0; i < 160; i++) dw_norm_2_1_beta[i] = parameterData["stage2.0.conv_local.norm.bias"][i];
    for (int i = 0; i < 160; i++) dw_norm_2_1_mean[i] = parameterData["stage2.0.conv_local.norm.running_mean"][i];
    for (int i = 0; i < 160; i++) dw_norm_2_1_var[i] = parameterData["stage2.0.conv_local.norm.running_var"][i];
    for (int i = 0; i < 7680; i++) proj_2_1_weight[i] = parameterData["stage2.0.proj.conv.weight"][i];
    for (int i = 0; i < 48; i++) norm_2_2_weight[i] = parameterData["stage2.1.norm.weight"][i];
    for (int i = 0; i < 48; i++) norm_2_2_bias[i] = parameterData["stage2.1.norm.bias"][i];
    for (int i = 0; i < 48; i++) norm_2_2_running_mean[i] = parameterData["stage2.1.norm.running_mean"][i];
    for (int i = 0; i < 48; i++) norm_2_2_running_var[i] = parameterData["stage2.1.norm.running_var"][i];
    for (int i = 0; i < 5760; i++) v_conv_2_2_weight[i] = parameterData["stage2.1.v.conv.weight"][i];
    for (int i = 0; i < 120; i++) v_conv_2_2_bias[i] = parameterData["stage2.1.v.conv.bias"][i];
    for (int i = 0; i < 1080; i++) dw_conv_2_2_filter[i] = parameterData["stage2.1.conv_local.conv.weight"][i];
    for (int i = 0; i < 120; i++) dw_norm_2_2_gamma[i] = parameterData["stage2.1.conv_local.norm.weight"][i];
    for (int i = 0; i < 120; i++) dw_norm_2_2_beta[i] = parameterData["stage2.1.conv_local.norm.bias"][i];
    for (int i = 0; i < 120; i++) dw_norm_2_2_mean[i] = parameterData["stage2.1.conv_local.norm.running_mean"][i];
    for (int i = 0; i < 120; i++) dw_norm_2_2_var[i] = parameterData["stage2.1.conv_local.norm.running_var"][i];
    for (int i = 0; i < 5760; i++) proj_2_2_weight[i] = parameterData["stage2.1.proj.conv.weight"][i];

    // execution
    kernel_stage1_2(X_data, 
                    norm_1_1_weight, norm_1_1_bias, norm_1_1_running_mean, norm_1_1_running_var,
                    v_conv_1_1_weight, v_conv_1_1_bias,
                    dw_conv_1_1_filter, dw_norm_1_1_gamma, dw_norm_1_1_beta, dw_norm_1_1_mean, dw_norm_1_1_var,
                    proj_1_1_weight,
                    norm_1_2_weight, norm_1_2_bias, norm_1_2_running_mean, norm_1_2_running_var,
                    v_conv_1_2_weight, v_conv_1_2_bias,
                    dw_conv_1_2_filter, dw_norm_1_2_gamma, dw_norm_1_2_beta, dw_norm_1_2_mean, dw_norm_1_2_var,
                    proj_1_2_weight,
                    norm_2_1_weight, norm_2_1_bias, norm_2_1_running_mean, norm_2_1_running_var,
                    v_conv_2_1_weight, v_conv_2_1_bias,
                    dw_conv_2_1_filter, dw_norm_2_1_gamma, dw_norm_2_1_beta, dw_norm_2_1_mean, dw_norm_2_1_var,
                    proj_2_1_weight,
                    norm_2_2_weight, norm_2_2_bias, norm_2_2_running_mean, norm_2_2_running_var,
                    v_conv_2_2_weight, v_conv_2_2_bias,
                    dw_conv_2_2_filter, dw_norm_2_2_gamma, dw_norm_2_2_beta, dw_norm_2_2_mean, dw_norm_2_2_var,
                    proj_2_2_weight,
                    Y_norm_1_1, Y_v_conv_1_1, Y_v_act_1_1, Y_dw_conv_1_1, Y_dw_norm_1_1, Y_dw_act_1_1, Y_proj_1_1,
                    Y_norm_1_2, Y_v_conv_1_2, Y_v_act_1_2, Y_dw_conv_1_2, Y_dw_norm_1_2, Y_dw_act_1_2, Y_proj_1_2,
                    Y_dw_skip_1_2, Y_skip_1_2,
                    Y_norm_2_1, Y_v_conv_2_1, Y_v_act_2_1, Y_dw_conv_2_1, Y_dw_norm_2_1, Y_dw_act_2_1, Y_proj_2_1,
                    Y_norm_2_2, Y_v_conv_2_2, Y_v_act_2_2, Y_dw_conv_2_2, Y_dw_norm_2_2, Y_dw_act_2_2, Y_proj_2_2,
                    Y_dw_skip_2_2, Y_skip_2_2
                    );

    // print output
    for (int n = 0; n < BATCH_SIZE; n++)
    {
        for (int c = 3; c < CHANNEL_OUT; c++)
        {
            for (int h = 0; h < HEIGHT_OUT; h++)
            {
                for (int w = 0; w < WIDTH_OUT; w++)
                {
                    if (w == 3)
                    {
                        std::cout << Y_skip_2_2[n * CHANNEL_OUT * HEIGHT_OUT * WIDTH_OUT + c * HEIGHT_OUT * WIDTH_OUT + h * WIDTH_OUT + w] << std::endl;
                        break;
                    }

                    else
                        std::cout << Y_skip_2_2[n * CHANNEL_OUT * HEIGHT_OUT * WIDTH_OUT + c * HEIGHT_OUT * WIDTH_OUT + h * WIDTH_OUT + w] << " ";
                }
                if (h == 3)
                {
                    break;
                }
            }
            break;
        }
        break;
    }

    return EXIT_SUCCESS;
}
