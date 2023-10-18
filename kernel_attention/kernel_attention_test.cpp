#include "kernel_attention.hpp"
#include <cmath>
#include <math.h>

// TODO: modify parameters
const int BATCH_SIZE = 1;
const int CHANNEL_IN = 80;
const int HEIGHT_IN = 14;
const int WIDTH_IN = 14;



int main()
{
    float buffer_DataIn_1[15680];
    float afterNorm[15680];
    float norm1_mean[196]; 
    float norm1_var[196]; 
    float norm1_weight[15680]; 
    float norm1_bias[15680]; 
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
    float buffer_result[47040];

    // init in
    for(int i=0;i<BATCH_SIZE*CHANNEL_IN*HEIGHT_IN*WIDTH_IN;i++){
    	buffer_DataIn_1[i]=float(i%256);
        afterNorm[i]=0;
    }
    float tmp_sum=0;
    float tmp_square_sum=0;
    for(int i=0;i<80;i++){
        norm1_mean[i]=125.;
        norm1_var[i]=5638.;
    }
	for (int c = 0; c < 80; c++)
	{
		norm1_weight[c] = 0.5;
		norm1_bias[c]  = 1;
	}

    for(int i=0;i<15680;i++){
        afterPad[i]=0;
        afterRearrangeX[i]=0;
        afterPad1[i]=0;
    }
    for(int i=0;i<31360;i++){
        afterConv1[i]=0;
    }
    for (int k = 0; k < 160; k++)
    {
        bias1[k] = 0.01;
        for (int l = 0; l < 80; l++)
        {
            for (int i = 0; i < 1; i++)
            {
                for (int j = 0; j < 1; j++)
                {
                    kernel1[k*80*1*1+l*1*1+i*1+j] = (0.02);
                }
            }
        }
    }
    for(int i=0;i<31360;i++){
        in_qk[i]=0;
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
        afterPad2[i]=0;
    }
    for(int i=0;i<47040;i++){
        afterConv2[i]=0;
    }

    for (int k = 0; k < 240; k++)
    {
        bias2[k] = 2;
        for (int l = 0; l < 80; l++)
        {
            for (int i = 0; i < 1; i++)
            {
                for (int j = 0; j < 1; j++)
                {
                    kernel2[k*80*1*1+l*1*1+i*1+j] = 1.2;
                }
            }
        }
    }
    for(int i=0;i<47040;i++){
        afterAct2[i]=0;
        QKV[i]=0;
        buffer_out[i]=0;
    }
    for(int i=0;i<47040;i++){
        buffer_result[i]=0;
    }

    // execution
    kernel_attention(buffer_DataIn_1,
                              afterNorm,
                              norm1_mean, norm1_var, norm1_weight, norm1_bias,
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
                              buffer_result
                       );

    // print output
    
    //std::cout << std::setprecision(12) << buffer_DataIn_1[0] << std::endl;
    //std::cout << std::setprecision(12) << afterNorm[0] << std::endl;
    /*for(int k=0;k<1;k++){
        for(int i=0;i<28;i++){
            for(int j=0;j<28;j++){
                std::cout << std::setprecision(4) << std::fixed << afterNorm[k*28*28+i*28+j] << "\n";
            }
        }
    }*/
    //std::cout <<"\n";std::cout <<"\n";std::cout <<"\n";
    //std::cout << std::setprecision(12) << afterPad[0] << std::endl;
    /*for(int k=0;k<1;k++){
        for(int i=0;i<7;i++){
            for(int j=0;j<7;j++){
                std::cout << std::setprecision(12) << afterRearrangeX[k*7*7+i*7+j] << " ";
            }
            std::cout <<"\n";
        }
    }*/
    //std::cout <<"\n";std::cout <<"\n";std::cout <<"\n";
    //std::cout << std::setprecision(12) << afterRearrangeX[0] << std::endl;
    //std::cout << std::setprecision(12) << afterConv1[0] << std::endl;
    /*or(int k=0;k<1;k++){
            for(int i=0;i<7;i++){
                for(int j=0;j<7;j++){
                    std::cout << std::setprecision(4)<< std::fixed << afterConv1[k*7*7+i*7+j] << " ";
                }
                std::cout <<"\n";
            }
        }*/
    //std::cout <<"\n";std::cout <<"\n";std::cout <<"\n";
    /*for(int k=0;k<40;k++){
                    std::cout << std::setprecision(12) << afterRearrangeX[k*7*7] << " ";
            std::cout <<"\n";
        }*/
    /*std::cout << std::setprecision(12) << in_qk[0] << std::endl;
    std::cout << std::setprecision(12) << afterQKMultiplication[0] << std::endl;

    std::cout << std::setprecision(12) << afterSoftmax[0] << std::endl;
    std::cout << std::setprecision(12) << afterRearrangeX2[0] << std::endl;
    std::cout << std::setprecision(12) << afterQKXMultiplication[0] << std::endl;

    for(int k=0;k<1;k++){
    		for(int i=0;i<2;i++){
    			for(int j=0;j<7;j++){
    				std::cout << std::setprecision(4)<< std::fixed  <<buffer_result[50*28*28+i*28+j] << " ";
    			}
    			std::cout << "\n";
    		}
    	}
    std::cout << std::setprecision(12) << afterConv2[0] << std::endl;
    std::cout << std::setprecision(12) << afterAct2[0] << std::endl;
    std::cout << std::setprecision(12) << QKV[0] << std::endl;
    std::cout << std::setprecision(12) << buffer_out[0] << std::endl;
    std::cout << std::setprecision(12) << buffer_result[0] << std::endl;*/



    for (int n = 0; n < 1; n++)
    {
        for (int c = 0; c < 1; c++)
        {
            for (int h = 0; h < 14; h++)
            {
                for (int w = 0; w < 14; w++)
                {
                    if (w == 13){
                        std::cout << std::setprecision(6) << buffer_result[n * 240 * 14 * 14 + c * 14 * 14 + h * 14 + w] << std::endl;
                        break;
                    }

                    else
                        std::cout << std::setprecision(6) << buffer_result[n * 240 * 14 * 14 + c * 14 * 14 + h * 14 + w] << " ";
                }
                if(h == 13){
                    break;
                }
            }
            break;
        }
        break;
    }

    return EXIT_SUCCESS;
}
