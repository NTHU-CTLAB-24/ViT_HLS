#include "kernel_EMO.hpp"
#include <opencv2/opencv.hpp>
#include <cmath>
#include <math.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace cv;
using namespace std;

// TODO: modify parameters
const int BATCH_SIZE = 1;
const int CHANNEL_IN = 3;
const int HEIGHT_IN = 224;
const int WIDTH_IN = 224;
const int CHANNEL_OUT = 48;
const int HEIGHT_OUT = 28;
const int WIDTH_OUT = 28;

// below size please check count_depth output to modify corresponding

// use count_depth to define size
// stage 0
float msp_conv_weight[648], msp_conv_bias[24];
float msp_norm_weight[24], msp_norm_bias[24], msp_norm_running_mean[24], msp_norm_running_var[24];
float dw_conv_weight[216], dw_norm_gamma[24], dw_norm_beta[24], dw_norm_mean[24], dw_norm_var[24];
float se_conv_reduce_weight[576], se_conv_reduce_bias[24];
float se_conv_expand_weight[576], se_conv_expand_bias[24];
float proj_conv_weight[576];

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

float X_data[150528];

float Y_msp_conv[301056] = {0};
float Y_msp_norm[301056] = {0};
float Y_dw_conv[301056] = {0};
float Y_dw_norm[301056] = {0};
float Y_dw_act[301056] = {0};
float Y_se_mean[24] = {0};
float Y_se_reduce[24] = {0};
float Y_se_act[24] = {0};
float Y_se_expand[24] = {0};
float Y_se_sigmoid[24] = {0};
float Y_se[301056] = {0};
float Y_proj[301056] = {0};

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
    // load image
    Mat image;
	image=imread("ILSVRC2012_val_00047654.JPEG");
    cout << "Origin image: " << image.rows << ' ' << image.cols << ' ' << image.channels() << endl;
    
    // Reshape Channel BGR -> RGB
    Mat image_rechannel;
    cvtColor(image, image_rechannel, COLOR_BGR2RGB);

    // Resize image to 256
    // Size dsize = Size(256, 256);
    // Mat image_resize = Mat(dsize, CV_32S);
    // resize(image_rechannel, image_resize, dsize);
    // image_resize.convertTo(image_resize, CV_32FC3, 1.0 / 255.0);
    // cout << image_resize.rows << ' ' << image_resize.cols << ' ' << image_resize.channels() << endl;
    // imwrite("resize.jpg", image_resize); // check resize image

    // Center crop image
    Mat image_crop;
    int rowStart = image_rechannel.rows % 2 == 0 ? image_rechannel.rows / 2 - 112 : image_rechannel.rows / 2 - 112 + 1;
    int colStart = image_rechannel.cols % 2 == 0 ? image_rechannel.cols / 2 - 112 : image_rechannel.cols / 2 - 112 + 1;
    image_crop = image_rechannel(Range(rowStart, rowStart + 224), Range(colStart, colStart + 224));
    cout << "Croped image: " << image_crop.rows << ' ' << image_crop.cols << ' ' << image_crop.channels() << endl;

    // Convert value range 0~255 to 0~1
    image_crop.convertTo(image_crop, CV_32FC3, 1.0 / 255.0);

    // Reshape array HWC -> CHW
    vector<Mat> input_channels(3);
    split(image_crop, input_channels); // get channel respectively

    vector<float> result(224 * 224 * 3);
    auto data = result.data(); // vector.data() return the memory address
    int channelLength = 224 * 224;
    for (int i = 0; i < 3; ++i) 
    {
        memcpy(data, input_channels[i].data, channelLength * sizeof(float));
        data += channelLength;
    }

    // Normalize array
    float mean[3] = {0.485, 0.456, 0.406};
    float std[3] = {0.229, 0.224, 0.225};
    for (int c = 0; c < 3; c++)
    {
        for (int h = 0; h < 224; h++)
        {
            for (int w = 0; w < 224; w++)
            {
                X_data[c * 224 * 224 + h * 224 + w] = (result[c * 224 * 224 + h * 224 + w] - mean[c]) / std[c];
            }
        }
    }

    // Validate image preprocess result
    cout << "Image Preprocess result: " << endl;
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if(j == 7) cout << X_data[2 * 224 * 224 + i * 224 + j] << endl;
            else cout << X_data[2 * 224 * 224 + i * 224 + j] << ' ';
        }
    }
    cout << endl;

    // // init in
    // for (int n = 0; n < BATCH_SIZE; n++)
    // {
    //     for (int c = 0; c < CHANNEL_IN; c++)
    //     {
    //         for (int h = 0; h < HEIGHT_IN; h++)
    //         {
    //             for (int w = 0; w < WIDTH_IN; w++)
    //             {
    //                 X_data[n * CHANNEL_IN * HEIGHT_IN * WIDTH_IN + c * HEIGHT_IN * WIDTH_IN + h * WIDTH_IN + w] = h + c;
    //             }
    //         }
    //     }
    // }

    // init parameters value
    ifstream file_0("./stage0_parameters.txt");
    if (!file_0.is_open())
        cerr << "Failed to open the parameter file_0." << std::endl;
    
    unordered_map<string, vector<float>> parameterData;
    string line;
    string current_key;
    while (std::getline(file_0, line))
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
    for (int i = 0; i < 24; i++) dw_norm_gamma[i] = parameterData["stage0.1.conv_local.norm.weight"][i];
    for (int i = 0; i < 24; i++) dw_norm_beta[i] = parameterData["stage0.1.conv_local.norm.bias"][i];
    for (int i = 0; i < 24; i++) dw_norm_mean[i] = parameterData["stage0.1.conv_local.norm.running_mean"][i];
    for (int i = 0; i < 24; i++) dw_norm_var[i] = parameterData["stage0.1.conv_local.norm.running_var"][i];  
    for (int i = 0; i < 576; i++) se_conv_reduce_weight[i] = parameterData["stage0.1.se.conv_reduce.weight"][i];
    for (int i = 0; i < 24; i++) se_conv_reduce_bias[i] = parameterData["stage0.1.se.conv_reduce.bias"][i];
    for (int i = 0; i < 576; i++) se_conv_expand_weight[i] = parameterData["stage0.1.se.conv_expand.weight"][i];
    for (int i = 0; i < 24; i++) se_conv_expand_bias[i] = parameterData["stage0.1.se.conv_expand.bias"][i];
    for (int i = 0; i < 576; i++) proj_conv_weight[i] = parameterData["stage0.1.proj.conv.weight"][i];

    // init parameters value
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
    kernel_EMO( X_data,
                msp_conv_weight, msp_conv_bias, msp_norm_weight, msp_norm_bias, msp_norm_running_mean, msp_norm_running_var,
                dw_conv_weight, dw_norm_gamma, dw_norm_beta, dw_norm_mean, dw_norm_var,
                se_conv_reduce_weight, se_conv_reduce_bias, se_conv_expand_weight, se_conv_expand_bias,
                proj_conv_weight,
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
                Y_msp_conv, Y_msp_norm, Y_dw_conv, Y_dw_norm, Y_dw_act,
                Y_se_mean, Y_se_reduce, Y_se_act, Y_se_expand, Y_se_sigmoid, Y_se, Y_proj,
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
