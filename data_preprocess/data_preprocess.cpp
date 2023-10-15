#include "linear.hpp"
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

float X_data[8232];
float X_reduce[168] = {0};
float Y_linear[1000] = {0};

float norm_weight[168];
float norm_bias[168];
float head_weight[168000];
float head_bias[1000];

int main(){
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
    float input_x[1 * 3 * 224 * 224];
    float mean[3] = {0.485, 0.456, 0.406};
    float std[3] = {0.229, 0.224, 0.225};
    for (int c = 0; c < 3; c++)
    {
        for (int h = 0; h < 224; h++)
        {
            for (int w = 0; w < 224; w++)
            {
                input_x[c * 224 * 224 + h * 224 + w] = (result[c * 224 * 224 + h * 224 + w] - mean[c]) / std[c];
            }
        }
    }

    // Validate image preprocess result
    cout << "Image Preprocess result: " << endl;
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if(j == 7) cout << input_x[2 * 224 * 224 + i * 224 + j] << endl;
            else cout << input_x[2 * 224 * 224 + i * 224 + j] << ' ';
        }
    }
    cout << endl;

    // Mat reconstruct = Mat(dsize, CV_32FC3);
    // cvtColor(image_resize, reconstruct, COLOR_RGB2BGR);
    // imwrite("reconstruct.jpg", reconstruct);

    // Reshape: blobFromImage(輸入圖片, 各通道縮放比例, 圖片尺寸, 各通道減去常數, 是否交換R和B通道(BGR <-> RGB), 圖像裁減, 輸出圖像深度)
    // 使用該函數可以將通道BGR轉換成RGB，並且從形狀HWC轉成CHW，目前該函式有報錯
    // Mat image_reshape = cv::dnn::blobFromImage(image_resize, 1.0 / 255.0, dsize, Scalar(0, 0, 0), true, false, CV_32F);
    // cout << image_reshape.channels() << ' ' << image_reshape.rows << ' ' << image_reshape.cols << endl;
    // cout << image_reshape << endl;

    // convert mat to float array
    // int image_channels = image_resize.channels();
    // int image_rows = image_resize.rows;
    // int image_cols = image_resize.cols;
    // int image_size = image_rows * image_cols * image_channels;
    // float* array_data = new float[image_size]();
    // cout << image_size << endl; // 224 * 224 * 3 should be 150528
    // std::memcpy(array_data, image_resize.ptr<float>(0), image_size * sizeof(float));

    // float array_data[1 * 3 * 224 * 224];
	// for (size_t i = 0; i < image_resize.rows; i++)
	// {
	// 	for (size_t j = 0; j < image_resize.cols; j++)
	// 	{
	// 		array_data[0 * 224 * 224 + i * 224 + j] = image_resize.at<Vec3b>(i, j)[2];
	// 		array_data[1 * 224 * 224 + i * 224 + j] = image_resize.at<Vec3b>(i, j)[1];
	// 		array_data[2 * 224 * 224 + i * 224 + j] = image_resize.at<Vec3b>(i, j)[0];
	// 	}
	// }

    // Mat image_reconstruct = Mat(dsize, CV_32F);
    // for (size_t i = 0; i < image_resize.rows; i++)
	// {
	// 	for (size_t j = 0; j < image_resize.cols; j++)
	// 	{
	// 		image_reconstruct.at<Vec3b>(i, j)[2] = array_data[0 * 224 * 224 + i * 224 + j];
	// 		image_reconstruct.at<Vec3b>(i, j)[1] = array_data[1 * 224 * 224 + i * 224 + j];
	// 		image_reconstruct.at<Vec3b>(i, j)[0] = array_data[2 * 224 * 224 + i * 224 + j];
	// 	}
	// }
    // imwrite("reconstruct.JPEG", image_reconstruct);

    // linear part
    for (int i = 0; i < 168; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            for (int k = 0; k < 7; k++)
            {
                X_data[i * 7 * 7 + j * 7 + k] = (j + k) * 0.1;
            }
        }
    }

    // init parameters value
    ifstream file("./linear_parameters.txt"); // TODO: modify stageX
    if (!file.is_open())
        cerr << "Failed to open the parameter file." << std::endl;
    
    unordered_map<string, vector<float>> parameterData;
    string line;
    string current_key;
    while (std::getline(file, line))
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
    for (int i = 0; i < 168; i++) norm_weight[i] = parameterData["norm.norm.weight"][i];
    for (int i = 0; i < 168; i++) norm_bias[i] = parameterData["norm.norm.bias"][i];
    for (int i = 0; i < 168000; i++) head_weight[i] = parameterData["head.weight"][i];
    for (int i = 0; i < 1000; i++) head_bias[i] = parameterData["head.bias"][i];

    linear(X_data, X_reduce, head_weight, head_bias, Y_linear);

    cout << endl;
    cout << "Linear result: " << endl;
    for (int i = 111; i < 121; i++)
    {
        if(i == 120) cout << Y_linear[i] << endl;
        else cout << Y_linear[i] << ' ';
    }
    cout << endl;

    return 0;
}