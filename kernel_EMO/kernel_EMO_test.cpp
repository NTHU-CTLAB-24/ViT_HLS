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
const int CHANNEL_OUT = 168;
const int HEIGHT_OUT = 7;
const int WIDTH_OUT = 7;

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

// stage 3 depth 0
float norm_0_weight_3[48] = {0}, norm_0_bias_3[48] = {0};
float v_conv_0_weight_3[13824] = {0}, v_conv_0_bias_3[288] = {0};
float dw_conv_0_filter_3[7200] = {0}, dw_norm_0_weight_3[288] = {0}, dw_norm_0_bias_3[288] = {0}, dw_norm_0_mean_3[288] = {0}, dw_norm_0_var_3[288] = {0};
float proj_0_weight_3[23040] = {0};

float Y_norm_0_3[37632] = {0};
float Y_v_conv_0_3[225792] = {0}, Y_v_act_0_3[225792] = {0};
float Y_dw_conv_0_3[56448] = {0}, Y_dw_norm_0_3[56448] = {0}, Y_dw_act_0_3[56448] = {0};

// stage 3 depth 1-7
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

// stage 4 depth 0
float norm_0_weight_4[80] = {0}, norm_0_bias_4[80] = {0};
float v_conv_0_weight_4[44800] = {0}, v_conv_0_bias_4[560] = {0};
float dw_conv_0_filter_4[14000] = {0}, dw_norm_0_weight_4[560] = {0}, dw_norm_0_bias_4[560] = {0}, dw_norm_0_mean_4[560] = {0}, dw_norm_0_var_4[560] = {0};
float proj_0_weight_4[94080] = {0};

float Y_norm_0_4[15680] = {0};
float Y_v_conv_0_4[109760] = {0}, Y_v_act_0_4[109760] = {0};
float Y_dw_conv_0_4[27440] = {0}, Y_dw_norm_0_4[27440] = {0}, Y_dw_act_0_4[27440] = {0};

// stage 4 depth 1-2
float dw_conv_1_filter_4[14700*2] = {0}, dw_norm_1_weight_4[588*2] = {0}, dw_norm_1_bias_4[588*2] = {0}, dw_norm_1_mean_4[588*2] = {0}, dw_norm_1_var_4[588*2] = {0};
float proj_1_weight_4[98784*2] = {0};

float Y_dw_conv_1_4[28812] = {0}, Y_dw_norm_1_4[28812] = {0}, Y_dw_act_1_4[28812] = {0}, Y_dw_skip_1_4[28812] = {0};
float Y_proj_1_4[8232] = {0};
float Y_skip_1_4[8232] = {0};

float result_40[8232] = {0};
float afterNorm_4[8232] = {0};

float norm1_mean_4[49*2] = {0}; 
float norm1_var_4[49*2] = {0}; 
float norm1_weight_4[168*2] = {0}; 
float norm1_bias_4[168*2] = {0};

float afterRearrangeX_4[8232] = {0};
float afterConv1_4[16464] = {0};

float kernel1_4[56448*2] = {0};
float bias1_4[336*2] = {0};

float in_q_4[8232] = {0};
float in_k_4[8232] = {0};
float afterQKMultiplication_4[19208] = {0};
float afterSoftmax_4[19208] = {0};
float afterRearrangeX2_4[8232] = {0};
float afterQKXMultiplication_4[8232] = {0};
float afterRearrangeQKX_4[8232] = {0};
float afterConv2_4[28812] = {0};

float kernel2_4[98784*2] = {0};
float bias2_4[588*2] = {0};

float afterAct2_4[28812] = {0};
float buffer_out_4[28812] = {0};
float buffer_result_4[28812] = {0};

// Linear
float linear_norm_mean[49] = {0}, linear_norm_var[49] = {0}, linear_norm_weight[168] = {0}, linear_norm_bias[168] = {0};
float linear_weight[168000] = {0}, linear_bias[1000] = {0};
float Y_linear_norm[8232] = {0};
float Y_linear_reduce[168] = {0};
float Y_out[1000] = {0};

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

    ifstream file_3("./stage3_parameters.txt");
    if (!file_3.is_open())
        cerr << "Failed to open the parameter file_3." << std::endl;
    
    while (std::getline(file_3, line))
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

    ifstream file_4("./stage4_parameters.txt");
    if (!file_4.is_open())
        cerr << "Failed to open the parameter file_4." << std::endl;
    
    while (std::getline(file_4, line))
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

    for (int i = 0; i < 80; i++) norm_0_weight_4[i] = parameterData["stage4.0.norm.norm.weight"][i];
    for (int i = 0; i < 80; i++) norm_0_bias_4[i] = parameterData["stage4.0.norm.norm.bias"][i];
    for (int i = 0; i < 44800; i++) v_conv_0_weight_4[i] = parameterData["stage4.0.v.conv.weight"][i];
    for (int i = 0; i < 560; i++) v_conv_0_bias_4[i] = parameterData["stage4.0.v.conv.bias"][i];
    for (int i = 0; i < 14000; i++) dw_conv_0_filter_4[i] = parameterData["stage4.0.conv_local.conv.weight"][i];   
    for (int i = 0; i < 560; i++) dw_norm_0_weight_4[i] = parameterData["stage4.0.conv_local.norm.weight"][i];    
    for (int i = 0; i < 560; i++) dw_norm_0_bias_4[i] = parameterData["stage4.0.conv_local.norm.bias"][i];        
    for (int i = 0; i < 560; i++) dw_norm_0_mean_4[i] = parameterData["stage4.0.conv_local.norm.running_mean"][i];
    for (int i = 0; i < 560; i++) dw_norm_0_var_4[i] = parameterData["stage4.0.conv_local.norm.running_var"][i];  
    for (int i = 0; i < 94080; i++) proj_0_weight_4[i] = parameterData["stage4.0.proj.conv.weight"][i];

    for (int c = 0; c < 168; c++)
	{
		norm1_weight_4[c] = parameterData["stage4.1.norm.norm.weight"][c];
		norm1_bias_4[c]  = parameterData["stage4.1.norm.norm.bias"][c];
        norm1_weight_4[c+168*1] = parameterData["stage4.2.norm.norm.weight"][c];
		norm1_bias_4[c+168*1]  = parameterData["stage4.2.norm.norm.bias"][c];
	}

    for (int k = 0; k < 336; k++)
    {
        bias1_4[k] = parameterData["stage4.1.qk.conv.bias"][k];
        bias1_4[k+336*1] = parameterData["stage4.2.qk.conv.bias"][k];
        for (int l = 0; l < 168; l++)
        {
            for (int i = 0; i < 1; i++)
            {
                for (int j = 0; j < 1; j++)
                {
                    kernel1_4[k*168*1*1+l*1*1+i*1+j] = parameterData["stage4.1.qk.conv.weight"][k*168+l];
                    kernel1_4[(k+336*1)*168*1*1+l*1*1+i*1+j] = parameterData["stage4.2.qk.conv.weight"][k*168+l];
                }
            }
        }
    }
    for (int k = 0; k < 588; k++)
    {
        bias2_4[k] = parameterData["stage4.1.v.conv.bias"][k];
        bias2_4[k+588*1] = parameterData["stage4.2.v.conv.bias"][k];
        for (int l = 0; l < 168; l++)
        {
            for (int i = 0; i < 1; i++)
            {
                for (int j = 0; j < 1; j++)
                {
                    kernel2_4[k*168*1*1+l*1*1+i*1+j] = parameterData["stage4.1.v.conv.weight"][k*168+l];
                    kernel2_4[(k+588*1)*168*1*1+l*1*1+i*1+j] = parameterData["stage4.2.v.conv.weight"][k*168+l];
                }
            }
        }
    }

    for (int i = 0; i < 588; i++)
    {
        dw_norm_1_weight_4[i] = parameterData["stage4.1.conv_local.norm.weight"][i];
        dw_norm_1_bias_4[i] = parameterData["stage4.1.conv_local.norm.bias"][i];
        dw_norm_1_mean_4[i] = parameterData["stage4.1.conv_local.norm.running_mean"][i];
        dw_norm_1_var_4[i] = parameterData["stage4.1.conv_local.norm.running_var"][i];
        dw_norm_1_weight_4[i+588*1] = parameterData["stage4.2.conv_local.norm.weight"][i];
        dw_norm_1_bias_4[i+588*1] = parameterData["stage4.2.conv_local.norm.bias"][i];
        dw_norm_1_mean_4[i+588*1] = parameterData["stage4.2.conv_local.norm.running_mean"][i];
        dw_norm_1_var_4[i+588*1] = parameterData["stage4.2.conv_local.norm.running_var"][i];
    }
    for (int i = 0; i < 14700; i++){
        dw_conv_1_filter_4[i] = parameterData["stage4.1.conv_local.conv.weight"][i];
        dw_conv_1_filter_4[i+14700*1] = parameterData["stage4.2.conv_local.conv.weight"][i];
    }
    
    for (int i = 0; i < 98784; i++){
        proj_1_weight_4[i] = parameterData["stage4.1.proj.conv.weight"][i];
        proj_1_weight_4[i+98784*1] = parameterData["stage4.2.proj.conv.weight"][i];
    }

    ifstream file_linear("./linear_parameters.txt");
    if (!file_linear.is_open())
        cerr << "Failed to open the parameter file_linear." << std::endl;

    while (std::getline(file_linear, line))
    {
        if (!line.empty())
        {
            if (line[0] == 'n' || line[0] == 'h'){ // key
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
    for (int i = 0; i < 168; i++) linear_norm_weight[i] = parameterData["norm.norm.weight"][i];
    for (int i = 0; i < 168; i++) linear_norm_bias[i] = parameterData["norm.norm.bias"][i];
    for (int i = 0; i < 168000; i++) linear_weight[i] = parameterData["head.weight"][i];
    for (int i = 0; i < 1000; i++) linear_bias[i] = parameterData["head.bias"][i];

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
                Y_dw_skip_2_2, Y_skip_2_2,
                norm_0_weight_3, norm_0_bias_3, v_conv_0_weight_3, v_conv_0_bias_3,
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
                Y_dw_skip_1_3, Y_skip_1_3,
                norm_0_weight_4, norm_0_bias_4, v_conv_0_weight_4, v_conv_0_bias_4,
                dw_conv_0_filter_4, dw_norm_0_weight_4, dw_norm_0_bias_4, dw_norm_0_mean_4, dw_norm_0_var_4,
                proj_0_weight_4, Y_norm_0_4, Y_v_conv_0_4, Y_v_act_0_4, Y_dw_conv_0_4, Y_dw_norm_0_4, Y_dw_act_0_4,
                result_40, afterNorm_4,
                norm1_mean_4, norm1_var_4, norm1_weight_4, norm1_bias_4,
                afterRearrangeX_4,
                afterConv1_4,
                kernel1_4,
                bias1_4,
                in_q_4,
                in_k_4,
                afterQKMultiplication_4,
                afterSoftmax_4,
                afterRearrangeX2_4,
                afterQKXMultiplication_4,
                afterRearrangeQKX_4,
                afterConv2_4,
                kernel2_4,
                bias2_4,
                afterAct2_4,
                buffer_out_4,
                buffer_result_4,
                dw_conv_1_filter_4, dw_norm_1_weight_4, dw_norm_1_bias_4, dw_norm_1_mean_4, dw_norm_1_var_4,
                proj_1_weight_4, Y_dw_conv_1_4, Y_dw_norm_1_4, Y_dw_act_1_4, Y_proj_1_4,
                Y_dw_skip_1_4, Y_skip_1_4,
                Y_linear_norm, linear_norm_mean, linear_norm_var, linear_norm_weight, linear_norm_bias,
                Y_linear_reduce, linear_weight, linear_bias, Y_out
                );

    // print output
    for (int i = 100; i < 116; i++){
        if(i % 4 == 3) std::cout << Y_out[i] << std::endl;
        else std::cout << Y_out[i] << ' ';
    }
    return EXIT_SUCCESS;
}
