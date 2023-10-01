#include "kernel_stage1.hpp"
#include <cmath>
#include <math.h>

// TODO: modify parameters
const int BATCH_SIZE = 1;
const int CHANNEL_IN = 6;
const int HEIGHT_IN = 28;
const int WIDTH_IN = 28;
const int CHANNEL_OUT = 8;
const int HEIGHT_OUT = 14;
const int WIDTH_OUT = 14;

// below size please check count_depth output to modify corresponding
const int X_DATA_SIZE = 4704;
const int Y_V_CONV_1_SIZE = 18816;
const int Y_PROJ_1_SIZE = 1568;
const int Y_V_CONV_2_SIZE = 3136;

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
        Y_v_conv_1[i] = 0;

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
    kernel_stage1(X_data,
                  norm_1_weight, norm_1_bias, norm_1_running_mean, norm_1_running_var,
                  v_conv_1_weight, v_conv_1_bias,
                  dw_conv_1_filter, dw_norm_1_gamma, dw_norm_1_beta, dw_norm_1_mean, dw_norm_1_var,
                  proj_1_weight,
                  norm_2_weight, norm_2_bias, norm_2_running_mean, norm_2_running_var,
                  v_conv_2_weight, v_conv_2_bias,
                  dw_conv_2_filter, dw_norm_2_gamma, dw_norm_2_beta, dw_norm_2_mean, dw_norm_2_var,
                  proj_2_weight,
                  Y_norm_1, Y_v_conv_1, Y_dw_conv_1, Y_dw_norm_1, Y_dw_act_1, Y_proj_1,
                  Y_norm_2, Y_v_conv_2, Y_dw_conv_2, Y_dw_norm_2, Y_dw_act_2, Y_proj_2,
                  Y_dw_skip_2, Y_skip_2
                  );

    // print output
    for (int n = 0; n < BATCH_SIZE; n++)
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
    }

    return EXIT_SUCCESS;
}
