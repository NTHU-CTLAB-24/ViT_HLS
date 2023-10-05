#include "kernel_stage1.hpp"
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
const int CHANNEL_OUT = 32;
const int HEIGHT_OUT = 56;
const int WIDTH_OUT = 56;

// below size please check count_depth output to modify corresponding
const int X_DATA_SIZE = 301056;
const int Y_V_CONV_1_SIZE = 1204224;
const int Y_PROJ_1_SIZE = 100352;
const int Y_V_CONV_2_SIZE = 200704;

// use count_depth to define size
// depth 1
float norm_1_weight[24], norm_1_bias[24], norm_1_running_mean[24], norm_1_running_var[24];
float v_conv_1_weight[2304], v_conv_1_bias[96];
float dw_conv_1_filter[864], dw_norm_1_gamma[96], dw_norm_1_beta[96], dw_norm_1_mean[96], dw_norm_1_var[96];
float proj_1_weight[3072];
// depth 2
float norm_2_weight[32], norm_2_bias[32], norm_2_running_mean[32], norm_2_running_var[32];
float v_conv_2_weight[2048], v_conv_2_bias[64];
float dw_conv_2_filter[576], dw_norm_2_gamma[64], dw_norm_2_beta[64], dw_norm_2_mean[64], dw_norm_2_var[64];
float proj_2_weight[2048];

float X_data[X_DATA_SIZE];
float Y_norm_1[X_DATA_SIZE];
float Y_v_conv_1[Y_V_CONV_1_SIZE], Y_v_act_1[Y_V_CONV_1_SIZE];
float Y_dw_conv_1[X_DATA_SIZE], Y_dw_norm_1[X_DATA_SIZE], Y_dw_act_1[X_DATA_SIZE];
float Y_proj_1[Y_PROJ_1_SIZE];

float Y_norm_2[Y_PROJ_1_SIZE];
float Y_v_conv_2[Y_V_CONV_2_SIZE], Y_v_act_2[Y_V_CONV_2_SIZE];
float Y_dw_conv_2[Y_V_CONV_2_SIZE], Y_dw_norm_2[Y_V_CONV_2_SIZE], Y_dw_act_2[Y_V_CONV_2_SIZE], Y_dw_skip_2[Y_V_CONV_2_SIZE];
float Y_proj_2[Y_PROJ_1_SIZE];
float Y_skip_2[Y_PROJ_1_SIZE];

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

    // init out
    for (int i = 0; i < X_DATA_SIZE; i++)
    {
        Y_norm_1[i] = 0;
        Y_dw_conv_1[i] = 0;
        Y_dw_norm_1[i] = 0;
        Y_dw_act_1[i] = 0;
    }

    for (int i = 0; i < Y_V_CONV_1_SIZE; i++)
    {
        Y_v_conv_1[i] = 0;
        Y_v_act_1[i] = 0;
    }

    for (int i = 0; i < Y_PROJ_1_SIZE; i++)
    {
        Y_proj_1[i] = 0;
        Y_norm_2[i] = 0;
        Y_proj_2[i] = 0;
        Y_skip_2[i] = 0;
    }

    for (int i = 0; i < Y_V_CONV_2_SIZE; i++)
    {
        Y_v_conv_2[i] = 0;
        Y_v_act_2[i] = 0;
        Y_dw_conv_2[i] = 0;
        Y_dw_norm_2[i] = 0;
        Y_dw_act_2[i] = 0;
        Y_dw_skip_2[i] = 0;
    }

    // // init value
    // // depth 1
    // for (int i = 0; i < 24; i++)
    // {
    //     norm_1_weight[i] = 0.5;
    //     norm_1_bias[i] = 0.2;
    //     norm_1_running_mean[i] = 8;
    //     norm_1_running_var[i] = 21.5;
    // }

    // for (int i = 0; i < 2304; i++)
    //     v_conv_1_weight[i] = 0.3;

    // for (int i = 0; i < 96; i++)
    // {
    //     v_conv_1_bias[i] = i + 0.01;
    //     dw_norm_1_gamma[i] = 0.5;
    //     dw_norm_1_beta[i] = 0.2;
    //     dw_norm_1_mean[i] = 8;
    //     dw_norm_1_var[i] = 21.5;
    // }

    // for (int i = 0; i < 864; i++)
    //     dw_conv_1_filter[i] = 0.3;

    // for (int i = 0; i < 3072; i++)
    //     proj_1_weight[i] = 0.3;

    // // depth 2
    // for (int i = 0; i < 32; i++)
    // {
    //     norm_2_weight[i] = 0.5;
    //     norm_2_bias[i] = 0.2;
    //     norm_2_running_mean[i] = 8;
    //     norm_2_running_var[i] = 21.5;
    // }

    // for (int i = 0; i < 2048; i++)
    //     v_conv_2_weight[i] = 0.3;

    // for (int i = 0; i < 64; i++)
    // {
    //     v_conv_2_bias[i] = i + 0.01;
    //     dw_norm_2_gamma[i] = 0.5;
    //     dw_norm_2_beta[i] = 0.2;
    //     dw_norm_2_mean[i] = 8;
    //     dw_norm_2_var[i] = 21.5;
    // }

    // for (int i = 0; i < 576; i++)
    //     dw_conv_2_filter[i] = 0.3;

    // for (int i = 0; i < 2048; i++)
    //     proj_2_weight[i] = 0.3;

    // init parameters value
    ifstream file("./stage1_parameters.txt");
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

    for (int i = 0; i < 24; i++) norm_1_weight[i] = parameterData["stage1.0.norm.weight"][i];
    for (int i = 0; i < 24; i++) norm_1_bias[i] = parameterData["stage1.0.norm.bias"][i];
    for (int i = 0; i < 24; i++) norm_1_running_mean[i] = parameterData["stage1.0.norm.running_mean"][i];
    for (int i = 0; i < 24; i++) norm_1_running_var[i] = parameterData["stage1.0.norm.running_var"][i];
    for (int i = 0; i < 2304; i++) v_conv_1_weight[i] = parameterData["stage1.0.v.conv.weight"][i];
    for (int i = 0; i < 96; i++) v_conv_1_bias[i] = parameterData["stage1.0.v.conv.bias"][i];
    for (int i = 0; i < 864; i++) dw_conv_1_filter[i] = parameterData["stage1.0.conv_local.conv.weight"][i];
    for (int i = 0; i < 96; i++) dw_norm_1_gamma[i] = parameterData["stage1.0.conv_local.norm.weight"][i];
    for (int i = 0; i < 96; i++) dw_norm_1_beta[i] = parameterData["stage1.0.conv_local.norm.bias"][i];
    for (int i = 0; i < 96; i++) dw_norm_1_mean[i] = parameterData["stage1.0.conv_local.norm.running_mean"][i];
    for (int i = 0; i < 96; i++) dw_norm_1_var[i] = parameterData["stage1.0.conv_local.norm.running_var"][i];
    for (int i = 0; i < 3072; i++) proj_1_weight[i] = parameterData["stage1.0.proj.conv.weight"][i];
    for (int i = 0; i < 32; i++) norm_2_weight[i] = parameterData["stage1.1.norm.weight"][i];
    for (int i = 0; i < 32; i++) norm_2_bias[i] = parameterData["stage1.1.norm.bias"][i];
    for (int i = 0; i < 32; i++) norm_2_running_mean[i] = parameterData["stage1.1.norm.running_mean"][i];
    for (int i = 0; i < 32; i++) norm_2_running_var[i] = parameterData["stage1.1.norm.running_var"][i];
    for (int i = 0; i < 2048; i++) v_conv_2_weight[i] = parameterData["stage1.1.v.conv.weight"][i];
    for (int i = 0; i < 64; i++) v_conv_2_bias[i] = parameterData["stage1.1.v.conv.bias"][i];
    for (int i = 0; i < 576; i++) dw_conv_2_filter[i] = parameterData["stage1.1.conv_local.conv.weight"][i];
    for (int i = 0; i < 64; i++) dw_norm_2_gamma[i] = parameterData["stage1.1.conv_local.norm.weight"][i];
    for (int i = 0; i < 64; i++) dw_norm_2_beta[i] = parameterData["stage1.1.conv_local.norm.bias"][i];
    for (int i = 0; i < 64; i++) dw_norm_2_mean[i] = parameterData["stage1.1.conv_local.norm.running_mean"][i];
    for (int i = 0; i < 64; i++) dw_norm_2_var[i] = parameterData["stage1.1.conv_local.norm.running_var"][i];
    for (int i = 0; i < 2048; i++) proj_2_weight[i] = parameterData["stage1.1.proj.conv.weight"][i];

    // execution
    kernel_stage1(X_data,
                  norm_1_weight, norm_1_bias, norm_1_running_mean, norm_1_running_var,
                  v_conv_1_weight, v_conv_1_bias,
                  dw_conv_1_filter, dw_norm_1_gamma, dw_norm_1_beta, dw_norm_1_mean, dw_norm_1_var,
                  proj_1_weight,
                  norm_2_weight, norm_2_bias, norm_2_running_mean, norm_2_running_var,
                  v_conv_2_weight, v_conv_2_bias,
                  dw_conv_2_filter, dw_norm_2_gamma, dw_norm_2_beta, dw_norm_2_mean, dw_norm_2_var,
                  proj_2_weight,
                  Y_norm_1, Y_v_conv_1, Y_v_act_1, Y_dw_conv_1, Y_dw_norm_1, Y_dw_act_1, Y_proj_1,
                  Y_norm_2, Y_v_conv_2, Y_v_act_2, Y_dw_conv_2, Y_dw_norm_2, Y_dw_act_2, Y_proj_2,
                  Y_dw_skip_2, Y_skip_2);

    // print output
    for (int n = 0; n < BATCH_SIZE; n++)
    {
        for (int c = 0; c < CHANNEL_OUT; c++)
        {
            for (int h = 0; h < HEIGHT_OUT; h++)
            {
                for (int w = 0; w < WIDTH_OUT; w++)
                {
                    if (w == 7)
                    {
                        std::cout << Y_skip_2[n * CHANNEL_OUT * HEIGHT_OUT * WIDTH_OUT + c * HEIGHT_OUT * WIDTH_OUT + h * WIDTH_OUT + w] << std::endl;
                        break;
                    }

                    else
                        std::cout << Y_skip_2[n * CHANNEL_OUT * HEIGHT_OUT * WIDTH_OUT + c * HEIGHT_OUT * WIDTH_OUT + h * WIDTH_OUT + w] << " ";
                }
                if (h == 7)
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
