#include "kernel_stage0.hpp"
#include <cmath>
#include <math.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

float X_data[150528];
float msp_conv_weight[648], msp_conv_bias[24];
float msp_norm_weight[24], msp_norm_bias[24], msp_norm_running_mean[24], msp_norm_running_var[24];
float dw_conv_weight[216];
float norm_1_weight[24], norm_1_bias[24], norm_1_running_mean[24], norm_1_running_var[24];
float se_conv_reduce_weight[576], se_conv_reduce_bias[24];
float se_conv_expand_weight[576], se_conv_expand_bias[24];
float proj_conv_weight[576];

float Y_msp_conv[301056];
float Y_msp_norm[301056];
float Y_dw_conv[301056];
float Y_dw_norm[301056];
float Y_dw_act[301056];
float Y_se_mean[24];
float Y_se_reduce[24];
float Y_se_act[24];
float Y_se_expand[24];
float Y_sigmoid[24];
float Y_se[301056];
float Y_proj[301056];

void dataPrepare(float* Array, int batch, int channel, int height, int width){
     for (int b = 0; b < batch; b++){
        for (int c = 0; c < channel; c++){
            for (int h = 0; h < height; h++){
                for (int w = 0; w < width; w++){
                    Array[b*channel*height*width + c*height*width + h*width + w] = h + c;
                }
            }
        }
    }
}

int main() {
    // init input (image) data
    dataPrepare(X_data, 1, 3, 224, 224);
    //for (int i=0; i<648; i++) msp_conv_weight[i] = 0.1;
    //for (int i=0; i<24; i++) msp_conv_bias[i] = i+0.1;
    for (int i=0; i<24; i++) {
        msp_norm_weight[i] = 0.5;
        msp_norm_bias[i] = 0.2;
        msp_norm_running_mean[i] = 8;
        msp_norm_running_var[i] = 21.5;
    }

    //init output
    for (int i = 0; i < 301056; i++) Y_msp_conv[i] = 0;
    for (int i = 0; i < 301056; i++) Y_msp_norm[i] = 0; 
    for (int i = 0; i < 301056; i++) Y_proj[i] = 0;
     // init parameters value
    ifstream file("./stage0_parameters.txt");
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

    for (int i = 0; i < 648; i++) msp_conv_weight[i] = parameterData["stage0.0.convs.0.0.weight"][i];
    for (int i = 0; i < 24; i++) msp_conv_bias[i] = parameterData["stage0.0.convs.0.0.bias"][i];
    for (int i = 0; i < 24; i++) msp_norm_weight[i] = parameterData["stage0.0.convs.0.1.weight"][i];
    for (int i = 0; i < 24; i++) msp_norm_bias[i] = parameterData["stage0.0.convs.0.1.bias"][i];
    for (int i = 0; i < 24; i++) msp_norm_running_mean[i] = parameterData["stage0.0.convs.0.1.running_mean"][i];    
    for (int i = 0; i < 24; i++) msp_norm_running_var[i] = parameterData["stage0.0.convs.0.1.running_var"][i];      
    for (int i = 0; i < 216; i++) dw_conv_weight[i] = parameterData["stage0.1.conv_local.conv.weight"][i];
    for (int i = 0; i < 24; i++) norm_1_weight[i] = parameterData["stage0.1.conv_local.norm.weight"][i];
    for (int i = 0; i < 24; i++) norm_1_bias[i] = parameterData["stage0.1.conv_local.norm.bias"][i];
    for (int i = 0; i < 24; i++) norm_1_running_mean[i] = parameterData["stage0.1.conv_local.norm.running_mean"][i];
    for (int i = 0; i < 24; i++) norm_1_running_var[i] = parameterData["stage0.1.conv_local.norm.running_var"][i];  
    for (int i = 0; i < 576; i++) se_conv_reduce_weight[i] = parameterData["stage0.1.se.conv_reduce.weight"][i];
    for (int i = 0; i < 24; i++) se_conv_reduce_bias[i] = parameterData["stage0.1.se.conv_reduce.bias"][i];
    for (int i = 0; i < 576; i++) se_conv_expand_weight[i] = parameterData["stage0.1.se.conv_expand.weight"][i];
    for (int i = 0; i < 24; i++) se_conv_expand_bias[i] = parameterData["stage0.1.se.conv_expand.bias"][i];
    for (int i = 0; i < 576; i++) proj_conv_weight[i] = parameterData["stage0.1.proj.conv.weight"][i];
    

    kernel_stage0(X_data, msp_conv_weight, msp_conv_bias, msp_norm_weight, msp_norm_bias, msp_norm_running_mean, msp_norm_running_var,
                    dw_conv_weight, norm_1_weight, norm_1_bias, norm_1_running_mean, norm_1_running_var,
                    se_conv_reduce_weight, se_conv_reduce_bias, se_conv_expand_weight, se_conv_expand_bias,
                    proj_conv_weight, Y_msp_conv, Y_msp_norm, Y_dw_conv, Y_dw_norm, Y_dw_act, Y_se_mean, Y_se_reduce, 
                    Y_se_act, Y_se_expand, Y_sigmoid, Y_se, Y_proj);
    int out_size;

    out_size = 112;

    cout << " after msp norm  - [0, 1, 10:20, 10:20]" << endl;
    for (int b = 0; b < 1; b++) {
        for (int c = 1; c < 2; c++) {
            for (int h = 10; h < 20; h++) {
                for (int w = 10; w < 20; w++) {
                    cout << Y_msp_norm[b*24*out_size*out_size + c*out_size*out_size + h*out_size + w] << " ";
                }
                cout << endl;
            }
        }
    }

    cout << " after proj- [0, 1, 10:15, 10:15]" << endl;
    for (int b = 0; b < 1; b++) {
        for (int c = 1; c < 2; c++) {
            for (int h = 10; h < 15; h++) {
                for (int w = 10; w < 15; w++) {
                    cout << Y_proj[b*24*out_size*out_size + c*out_size*out_size + h*out_size + w] << " ";
                }
                cout << endl;
            }
        }
    }

  return EXIT_SUCCESS;
}