/**********
Copyright (c) 2018, Xilinx, Inc.
All rights reserved.
Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:
1. Redistributions of source code must retain the above copyright notice,
this list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright notice,
this list of conditions and the following disclaimer in the documentation
and/or other materials provided with the distribution.
3. Neither the name of the copyright holder nor the names of its contributors
may be used to endorse or promote products derived from this software
without specific prior written permission.
THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**********/

/*******************************************************************************
** HOST Code
*******************************************************************************/

#include "host_stage1.hpp"
#include <cstring>
#include <fcntl.h>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <vector>
#include <cmath>
#include <math.h>

#define OCL_CHECK(error, call)                                                                   \
    call;                                                                                        \
    if (error != CL_SUCCESS)                                                                     \
    {                                                                                            \
        printf("%s:%d Error calling " #call ", error code is: %d\n", __FILE__, __LINE__, error); \
        exit(EXIT_FAILURE);                                                                      \
    }

using namespace std;

// TODO: modify parameters value
// 可以在這裡塞一點需要用到的常數
const int BATCH_SIZE = 1;
const int CHANNEL_IN = 6;
const int HEIGHT_IN = 112;
const int WIDTH_IN = 112;
const int CHANNEL_OUT = 8;
const int HEIGHT_OUT = 56;
const int WIDTH_OUT = 56;
// 使用count_depth.py的註解部份
static const int X_data_size = 75264; // data in
// depth 1
static const int norm_1_weight_size = 6;
static const int norm_1_bias_size = 6;
static const int norm_1_running_mean_size = 6;
static const int norm_1_running_var_size = 6;
static const int v_conv_1_weight_size = 144;
static const int v_conv_1_bias_size = 24;
static const int dw_conv_1_filter_size = 216;
static const int dw_norm_1_gamma_size = 24;
static const int dw_norm_1_beta_size = 24;
static const int dw_norm_1_mean_size = 24;
static const int dw_norm_1_var_size = 24;
static const int proj_1_weight_size = 192;
// depth 2
static const int norm_2_weight_size = 8;
static const int norm_2_bias_size = 8;
static const int norm_2_running_mean_size = 8;
static const int norm_2_running_var_size = 8;
static const int v_conv_2_weight_size = 128;
static const int v_conv_2_bias_size = 16;
static const int dw_conv_2_filter_size = 144;
static const int dw_norm_2_gamma_size = 16;
static const int dw_norm_2_beta_size = 16;
static const int dw_norm_2_mean_size = 16;
static const int dw_norm_2_var_size = 16;
static const int proj_2_weight_size = 128;

// out
static const int Y_norm_1_size = 75264;
static const int Y_v_conv_1_size = 301056;
static const int Y_dw_conv_1_size = 75264;
static const int Y_dw_norm_1_size = 75264;
static const int Y_dw_act_1_size = 75264;
static const int Y_proj_1_size = 25088;
static const int Y_norm_2_size = 25088;
static const int Y_v_conv_2_size = 50176;
static const int Y_dw_conv_2_size = 50176;
static const int Y_dw_norm_2_size = 50176;
static const int Y_dw_act_2_size = 50176;
static const int Y_dw_skip_2_size = 50176;
static const int Y_proj_2_size = 25088;
static const int Y_skip_2_size = 25088; // final out

// Compute the size of array in bytes
size_t X_data_bytes = X_data_size * sizeof(float);
// depth 1
size_t norm_1_weight_bytes = norm_1_weight_size * sizeof(float);
size_t norm_1_bias_bytes = norm_1_bias_size * sizeof(float);
size_t norm_1_running_mean_bytes = norm_1_running_mean_size * sizeof(float);
size_t norm_1_running_var_bytes = norm_1_running_var_size * sizeof(float);
size_t v_conv_1_weight_bytes = v_conv_1_weight_size * sizeof(float);
size_t v_conv_1_bias_bytes = v_conv_1_bias_size * sizeof(float);
size_t dw_conv_1_filter_bytes = dw_conv_1_filter_size * sizeof(float);
size_t dw_norm_1_gamma_bytes = dw_norm_1_gamma_size * sizeof(float);
size_t dw_norm_1_beta_bytes = dw_norm_1_beta_size * sizeof(float);
size_t dw_norm_1_mean_bytes = dw_norm_1_mean_size * sizeof(float);
size_t dw_norm_1_var_bytes = dw_norm_1_var_size * sizeof(float);
size_t proj_1_weight_bytes = proj_1_weight_size * sizeof(float);
// depth 2
size_t norm_2_weight_bytes = norm_2_weight_size * sizeof(float);
size_t norm_2_bias_bytes = norm_2_bias_size * sizeof(float);
size_t norm_2_running_mean_bytes = norm_2_running_mean_size * sizeof(float);
size_t norm_2_running_var_bytes = norm_2_running_var_size * sizeof(float);
size_t v_conv_2_weight_bytes = v_conv_2_weight_size * sizeof(float);
size_t v_conv_2_bias_bytes = v_conv_2_bias_size * sizeof(float);
size_t dw_conv_2_filter_bytes = dw_conv_2_filter_size * sizeof(float);
size_t dw_norm_2_gamma_bytes = dw_norm_2_gamma_size * sizeof(float);
size_t dw_norm_2_beta_bytes = dw_norm_2_beta_size * sizeof(float);
size_t dw_norm_2_mean_bytes = dw_norm_2_mean_size * sizeof(float);
size_t dw_norm_2_var_bytes = dw_norm_2_var_size * sizeof(float);
size_t proj_2_weight_bytes = proj_2_weight_size * sizeof(float);
// out
size_t Y_norm_1_bytes = Y_norm_1_size * sizeof(float);
size_t Y_v_conv_1_bytes = Y_v_conv_1_size * sizeof(float);
size_t Y_dw_conv_1_bytes = Y_dw_conv_1_size * sizeof(float);
size_t Y_dw_norm_1_bytes = Y_dw_norm_1_size * sizeof(float);
size_t Y_dw_act_1_bytes = Y_dw_act_1_size * sizeof(float);
size_t Y_proj_1_bytes = Y_proj_1_size * sizeof(float);
size_t Y_norm_2_bytes = Y_norm_2_size * sizeof(float);
size_t Y_v_conv_2_bytes = Y_v_conv_2_size * sizeof(float);
size_t Y_dw_conv_2_bytes = Y_dw_conv_2_size * sizeof(float);
size_t Y_dw_norm_2_bytes = Y_dw_norm_2_size * sizeof(float);
size_t Y_dw_act_2_bytes = Y_dw_act_2_size * sizeof(float);
size_t Y_dw_skip_2_bytes = Y_dw_skip_2_size * sizeof(float);
size_t Y_proj_2_bytes = Y_proj_2_size * sizeof(float);
size_t Y_skip_2_bytes = Y_skip_2_size * sizeof(float);

static const string error_message =
    "Error: Result mismatch:\n"
    "i = %d CPU result = %d Device result = %d\n";

#define ALL_MESSAGES

// ********************************************************************************** //
// ---------------------------------------------------------------------------------- //
//                          M A I N    F U N C T I O N                                //
// ---------------------------------------------------------------------------------- //
// ********************************************************************************** //

int main(int argc, char *argv[])
{

#ifdef ALL_MESSAGES
    cout << "HOST-Info: ============================================================= " << endl;
    cout << "HOST-Info: (Step 0) Set & Print Arguments                      " << endl;
    cout << "HOST-Info: ============================================================= " << endl;
    for (int i = 0; i < argc; i++)
    {
        cout << "HOST-Info: CMD Aruguments " << i << " :" << argv[i] << endl;
    }
#endif

// TARGET_DEVICE macro needs to be passed from gcc command line
// ============================================================================
// Step 1: Check Command Line Arguments
// ============================================================================
//    o) argv[1] Platfrom Vendor
//    o) argv[2] Device Name
//    o) argv[3] XCLBIN file
// ============================================================================
#ifdef ALL_MESSAGES
    cout << "HOST-Info: ============================================================= " << endl;
    cout << "HOST-Info: (Step 1) Check Command Line Arguments                      " << endl;
    cout << "HOST-Info: ============================================================= " << endl;
#endif

    if (argc != 4)
    {
        cout << "HOST-Error: Incorrect command line syntax " << endl;
        cout << "HOST-Info:  Usage: " << argv[0] << " <Platform_Vendor> <Device_Name> <XCLBIN_File>  <Test Vectors Size>" << endl
             << endl;
        return EXIT_FAILURE;
    }

    string Target_Platform_Vendor = argv[1];
    string Target_Device_Name = argv[2];
    string xclbinFilename = argv[3];

#ifdef ALL_MESSAGES
    cout << "HOST-Info: Platform_Vendor   : " << Target_Platform_Vendor << endl;
    cout << "HOST-Info: Device_Name       : " << Target_Device_Name << endl;
    cout << "HOST-Info: XCLBIN_file       : " << xclbinFilename << endl;
#endif

// ============================================================================
// Step 2: Detect Target Platform and Target Device in a system.
//         Create Context and Command Queue.
// ============================================================================
// Variables:
//   o) Target_Platform_Vendor[] - defined as main() input argument
//   o) Target_Device_Name[]     - defined as main() input argument
//
// After that
//   o) Create a Context
//   o) Create a Command Queue
// ============================================================================
#ifdef ALL_MESSAGES
    cout << "HOST-Info: ============================================================= " << endl;
    cout << "HOST-Info: (Step 2) Detect Target Platform and Target Device in a system " << endl;
    cout << "HOST-Info:          Create Context and Command Queue                     " << endl;
    cout << "HOST-Info: ============================================================= " << endl;
#endif

    vector<cl::Platform> platforms;
    vector<cl::Device> devices;
    cl::Device device;
    cl::Context context;
    cl::CommandQueue q;
    cl_int err;
    bool found_target_device = false;

    // ------------------------------------------------------------------------------------
    // Step 2.1: Get All PLATFORMS, then search for Target_Platform_Vendor (CL_PLATFORM_VENDOR)
    // ------------------------------------------------------------------------------------
    // Get and store all PLATFORMS
    // ..................................................
    cl::Platform::get(&platforms);
#ifdef ALL_MESSAGES
    cout << "HOST-Info: Number of detected platforms : " << platforms.size() << endl;
#endif

    // Search for Platform (ex: Xilinx) using: CL_PLATFORM_VENDOR = Target_Platform_Vendor
    // Traversing all Platforms To find Xilinx Platform and targeted Device in Xilinx Platform
    // Check if the current platform matches Target_Platform_Vendor
    // .............................................................
    for (size_t i = 0; i < platforms.size(); i++)
    {
        cl::Platform platform = platforms[i];
        string platformName = platform.getInfo<CL_PLATFORM_NAME>();
        if (platformName == Target_Platform_Vendor)
        {
            devices.clear();
            platform.getDevices(CL_DEVICE_TYPE_ACCELERATOR, &devices);
#ifdef ALL_MESSAGES
            cout << "HOST-Info: Selected PlatformName[" << i << "] : " << platformName << endl;
#endif
            break;
        }
    }

// ------------------------------------------------------------------------------------
// Step 2.2:  Get All Devices for selected platform Target_Platform_ID
//            then search for Xilinx platform (CL_DEVICE_NAME = Target_Device_Name)
// ------------------------------------------------------------------------------------
// Get the Number of Devices
// ............................................................................
#ifdef ALL_MESSAGES
    cout << "HOST-Info: Number of detected devices : " << devices.size() << endl;
#endif

    // Search for CL_DEVICE_NAME = Target_Device_Name
    // Check if the current device matches Target_Device_Name
    // ............................................................................
    for (size_t i = 0; i < devices.size(); i++)
    {
        device = devices[i];
        string deviceName = device.getInfo<CL_DEVICE_NAME>();
        if (deviceName == Target_Device_Name)
        {
            found_target_device = true;
#ifdef ALL_MESSAGES
            cout << "HOST-Info: Selected Device[" << i << "] : " << deviceName << endl;
#endif
            break;
        }
    }

    if (found_target_device == false)
    {
        cout << "HOST-Error: Unable to find Device : " << Target_Device_Name << endl;
        return EXIT_FAILURE;
    }

// ------------------------------------------------------------------------------------
// Step 2.3: Create Context and Command Queue for selected Device
// ------------------------------------------------------------------------------------
#ifdef ALL_MESSAGES
    cout << "HOST-Info: Creating Context ... " << endl;
#endif
    OCL_CHECK(err, context = cl::Context(device, nullptr, nullptr, nullptr, &err));
#ifdef ALL_MESSAGES
    cout << "HOST-Info: Creating Command Queue ... " << endl;
#endif
    OCL_CHECK(err, q = cl::CommandQueue(context, device, CL_QUEUE_PROFILING_ENABLE, &err));

// ============================================================================
// Step 3: Create Program and Kernel
// ============================================================================
//   o) Create a Program from a Binary File and Build it
//   o) Create a Kernel
// ============================================================================
#ifdef ALL_MESSAGES
    cout << "HOST-Info: ============================================================= " << endl;
    cout << "HOST-Info: (Step 3) Create Program and Kernels                           " << endl;
    cout << "HOST-Info: ============================================================= " << endl;
#endif

    // ------------------------------------------------------------------
    // Step 3.1: Load Binary File from a disk to Memory
    // ------------------------------------------------------------------
    FILE *fp;
    if ((fp = fopen(xclbinFilename.c_str(), "r")) == nullptr)
    {
        printf("HOST-ERROR: %s xclbin not available please build\n", xclbinFilename.c_str());
        exit(EXIT_FAILURE);
    }
#ifdef ALL_MESSAGES
    cout << "HOST-Info: Loading " << xclbinFilename << " binary file to memory ..." << endl;
#endif
    std::ifstream bin_file(xclbinFilename, std::ifstream::binary);
    bin_file.seekg(0, bin_file.end);
    unsigned bin_file_size = bin_file.tellg();
    bin_file.seekg(0, bin_file.beg);
    char *buf = new char[bin_file_size];
    bin_file.read(buf, bin_file_size);

// ------------------------------------------------------------
// Step 3.2: Create a program using a Binary File
//           Build (compiles and links) a program executable from binary
// ------------------------------------------------------------
#ifdef ALL_MESSAGES
    cout << "HOST-Info: Creating Program with Binary ..." << endl;
#endif
    // typedef vector<std::pair<const void*, size_type> > Binaries;
    cl::Program::Binaries bins = {{buf, bin_file_size}};
    cl::Program program(context, {device}, bins, nullptr, &err);
    if (err != CL_SUCCESS)
    {
        cout << "HOST-Error: Failed to create a Program from a Binary" << endl;
        return EXIT_FAILURE;
    }

    // -------------------------------------------------------------
    // Step 3.3: Create a Kernels
    // -------------------------------------------------------------
    // TODO: use array to store same kernel
    cl::Kernel kernel_stage1;
#ifdef ALL_MESSAGES
    cout << "HOST-Info: Creating a Kernel: kernel_stage1 ..." << endl;
#endif
    OCL_CHECK(err, kernel_stage1 = cl::Kernel(program, "kernel_stage1", &err));

// ================================================================
// Step 4: Prepare Data to Run Kernel
// ================================================================
//   o) Create Buffers in Memory & map our OpenCL buffers to get the pointers
//   o) Use pointer to Generate data for DataIn_1 array
//   o) Use pointer to Generate data for DataIn_2 array
//   o) Allocate Memory to store the results: RES array
//   o) Copy Input Data from Host to Global Memory
// ================================================================
#ifdef ALL_MESSAGES
    cout << "HOST-Info: ============================================================= " << endl;
    cout << "HOST-Info: (Step 4) Prepare Data to Run Kernels                           " << endl;
    cout << "HOST-Info: ============================================================= " << endl;
#endif
    // ------------------------------------------------------------------
    // Step 4.1: Create Buffers buffer_DataIn_1 in Memory & map to In
    //           Generate data for DataIn_1 array by using In
    //           Create Buffers buffer_DataIn_2 in Memory & map to Kernel
    //           Generate data for DataIn_2 array by using Kernel
    //           Allocate Memory to store the results: RES array
    // ------------------------------------------------------------------
    /* TODO:
     * use array to store pointer
     * remember to call cl::buffer's constructor in following way
     */
    /*定義Input和output型別*/
    //input data and parameters
    // \[[0-9]+\] use this RE to replace array declarator
    float* norm_1_weight, norm_1_bias, norm_1_running_mean, norm_1_running_var;
    float* v_conv_1_weight, v_conv_1_bias;
    float* dw_conv_1_filter, dw_norm_1_gamma, dw_norm_1_beta, dw_norm_1_mean, dw_norm_1_var;
    float* proj_1_weight;
    // depth 2
    float* norm_2_weight, norm_2_bias, norm_2_running_mean, norm_2_running_var;
    float* v_conv_2_weight, v_conv_2_bias;
    float* dw_conv_2_filter, dw_norm_2_gamma, dw_norm_2_beta, dw_norm_2_mean, dw_norm_2_var;
    float* proj_2_weight;

    float* X_data;
    float* Y_norm_1;
    float* Y_v_conv_1;
    float* Y_dw_conv_1, Y_dw_norm_1, Y_dw_act_1;
    float* Y_proj_1;

    float* Y_norm_2;
    float* Y_v_conv_2;
    float* Y_dw_conv_2, Y_dw_norm_2, Y_dw_act_2, Y_dw_skip_2;
    float* Y_proj_2;
    float* Y_skip_2;
    
// These commands will allocate memory on the .Device
// The cl::Buffer objects can be used to reference the memory locations on the device.
/* 以下區域為input data傳入host的code，只需要複製並且更改參數和型別即可(size_in_bytes(考慮input大小(byte)), In, DATA_SIZE(考慮input大小))*/
// TODO:Init input data buffer
    OCL_CHECK(err, cl::Buffer buffer_DataIn_1(context, CL_MEM_READ_ONLY, X_data_bytes, NULL, &err));
    OCL_CHECK(err, X_data = (float *)q.enqueueMapBuffer(buffer_DataIn_1, CL_TRUE, CL_MAP_WRITE, 0, X_data_bytes, NULL, NULL, &err));
    dataPrepare(X_data, 1, 6, 112, 112);

    OCL_CHECK(err, cl::Buffer buffer_DataIn_2(context, CL_MEM_READ_ONLY, norm_1_weight_bytes, NULL, &err));
    OCL_CHECK(err, norm_1_weight = (float *)q.enqueueMapBuffer(buffer_DataIn_2, CL_TRUE, CL_MAP_WRITE, 0, norm_1_weight_bytes, NULL, NULL, &err));

    OCL_CHECK(err, cl::Buffer buffer_DataIn_3(context, CL_MEM_READ_ONLY, norm_1_bias_bytes, NULL, &err));
    OCL_CHECK(err, norm_1_bias = (float *)q.enqueueMapBuffer(buffer_DataIn_3, CL_TRUE, CL_MAP_WRITE, 0, norm_1_bias_bytes, NULL, NULL, &err));

    OCL_CHECK(err, cl::Buffer buffer_DataIn_4(context, CL_MEM_READ_ONLY, norm_1_running_mean_bytes, NULL, &err));
    OCL_CHECK(err, norm_1_running_mean = (float *)q.enqueueMapBuffer(buffer_DataIn_4, CL_TRUE, CL_MAP_WRITE, 0, norm_1_running_mean_bytes, NULL, NULL, &err));

    OCL_CHECK(err, cl::Buffer buffer_DataIn_5(context, CL_MEM_READ_ONLY, norm_1_running_var_bytes, NULL, &err));
    OCL_CHECK(err, norm_1_running_var = (float *)q.enqueueMapBuffer(buffer_DataIn_5, CL_TRUE, CL_MAP_WRITE, 0, norm_1_running_var_bytes, NULL, NULL, &err));

    OCL_CHECK(err, cl::Buffer buffer_DataIn_6(context, CL_MEM_READ_ONLY, v_conv_1_weight_bytes, NULL, &err));
    OCL_CHECK(err, v_conv_1_weight = (float *)q.enqueueMapBuffer(buffer_DataIn_6, CL_TRUE, CL_MAP_WRITE, 0, v_conv_1_weight_bytes, NULL, NULL, &err));

    OCL_CHECK(err, cl::Buffer buffer_DataIn_7(context, CL_MEM_READ_ONLY, v_conv_1_bias_bytes, NULL, &err));
    OCL_CHECK(err, v_conv_1_bias = (float *)q.enqueueMapBuffer(buffer_DataIn_7, CL_TRUE, CL_MAP_WRITE, 0, v_conv_1_bias_bytes, NULL, NULL, &err));

    OCL_CHECK(err, cl::Buffer buffer_DataIn_8(context, CL_MEM_READ_ONLY, dw_conv_1_filter_bytes, NULL, &err));
    OCL_CHECK(err, dw_conv_1_filter = (float *)q.enqueueMapBuffer(buffer_DataIn_8, CL_TRUE, CL_MAP_WRITE, 0, dw_conv_1_filter_bytes, NULL, NULL, &err));

    OCL_CHECK(err, cl::Buffer buffer_DataIn_9(context, CL_MEM_READ_ONLY, dw_norm_1_gamma_bytes, NULL, &err));
    OCL_CHECK(err, dw_norm_1_gamma = (float *)q.enqueueMapBuffer(buffer_DataIn_9, CL_TRUE, CL_MAP_WRITE, 0, dw_norm_1_gamma_bytes, NULL, NULL, &err));

    OCL_CHECK(err, cl::Buffer buffer_DataIn_10(context, CL_MEM_READ_ONLY, dw_norm_1_beta_bytes, NULL, &err));
    OCL_CHECK(err, dw_norm_1_beta = (float *)q.enqueueMapBuffer(buffer_DataIn_10, CL_TRUE, CL_MAP_WRITE, 0, dw_norm_1_beta_bytes, NULL, NULL, &err));

    OCL_CHECK(err, cl::Buffer buffer_DataIn_11(context, CL_MEM_READ_ONLY, dw_norm_1_mean_bytes, NULL, &err));
    OCL_CHECK(err, dw_norm_1_mean = (float *)q.enqueueMapBuffer(buffer_DataIn_11, CL_TRUE, CL_MAP_WRITE, 0, dw_norm_1_mean_bytes, NULL, NULL, &err));

    OCL_CHECK(err, cl::Buffer buffer_DataIn_12(context, CL_MEM_READ_ONLY, dw_norm_1_var_bytes, NULL, &err));
    OCL_CHECK(err, dw_norm_1_var = (float *)q.enqueueMapBuffer(buffer_DataIn_12, CL_TRUE, CL_MAP_WRITE, 0, dw_norm_1_var_bytes, NULL, NULL, &err));

    OCL_CHECK(err, cl::Buffer buffer_DataIn_13(context, CL_MEM_READ_ONLY, proj_1_weight_bytes, NULL, &err));
    OCL_CHECK(err, proj_1_weight = (float *)q.enqueueMapBuffer(buffer_DataIn_13, CL_TRUE, CL_MAP_WRITE, 0, proj_1_weight_bytes, NULL, NULL, &err));

    OCL_CHECK(err, cl::Buffer buffer_DataIn_14(context, CL_MEM_READ_ONLY, norm_2_weight_bytes, NULL, &err));
    OCL_CHECK(err, norm_2_weight = (float *)q.enqueueMapBuffer(buffer_DataIn_14, CL_TRUE, CL_MAP_WRITE, 0, norm_2_weight_bytes, NULL, NULL, &err));

    OCL_CHECK(err, cl::Buffer buffer_DataIn_15(context, CL_MEM_READ_ONLY, norm_2_bias_bytes, NULL, &err));
    OCL_CHECK(err, norm_2_bias = (float *)q.enqueueMapBuffer(buffer_DataIn_15, CL_TRUE, CL_MAP_WRITE, 0, norm_2_bias_bytes, NULL, NULL, &err));

    OCL_CHECK(err, cl::Buffer buffer_DataIn_16(context, CL_MEM_READ_ONLY, norm_2_running_mean_bytes, NULL, &err));
    OCL_CHECK(err, norm_2_running_mean = (float *)q.enqueueMapBuffer(buffer_DataIn_16, CL_TRUE, CL_MAP_WRITE, 0, norm_2_running_mean_bytes, NULL, NULL, &err));

    OCL_CHECK(err, cl::Buffer buffer_DataIn_17(context, CL_MEM_READ_ONLY, norm_2_running_var_bytes, NULL, &err));
    OCL_CHECK(err, norm_2_running_var = (float *)q.enqueueMapBuffer(buffer_DataIn_17, CL_TRUE, CL_MAP_WRITE, 0, norm_2_running_var_bytes, NULL, NULL, &err));

    OCL_CHECK(err, cl::Buffer buffer_DataIn_18(context, CL_MEM_READ_ONLY, v_conv_2_weight_bytes, NULL, &err));
    OCL_CHECK(err, v_conv_2_weight = (float *)q.enqueueMapBuffer(buffer_DataIn_18, CL_TRUE, CL_MAP_WRITE, 0, v_conv_2_weight_bytes, NULL, NULL, &err));

    OCL_CHECK(err, cl::Buffer buffer_DataIn_19(context, CL_MEM_READ_ONLY, v_conv_2_bias_bytes, NULL, &err));
    OCL_CHECK(err, v_conv_2_bias = (float *)q.enqueueMapBuffer(buffer_DataIn_19, CL_TRUE, CL_MAP_WRITE, 0, v_conv_2_bias_bytes, NULL, NULL, &err));

    OCL_CHECK(err, cl::Buffer buffer_DataIn_20(context, CL_MEM_READ_ONLY, dw_conv_2_filter_bytes, NULL, &err));
    OCL_CHECK(err, dw_conv_2_filter = (float *)q.enqueueMapBuffer(buffer_DataIn_20, CL_TRUE, CL_MAP_WRITE, 0, dw_conv_2_filter_bytes, NULL, NULL, &err));

    OCL_CHECK(err, cl::Buffer buffer_DataIn_21(context, CL_MEM_READ_ONLY, dw_norm_2_gamma_bytes, NULL, &err));
    OCL_CHECK(err, dw_norm_2_gamma = (float *)q.enqueueMapBuffer(buffer_DataIn_21, CL_TRUE, CL_MAP_WRITE, 0, dw_norm_2_gamma_bytes, NULL, NULL, &err));

    OCL_CHECK(err, cl::Buffer buffer_DataIn_22(context, CL_MEM_READ_ONLY, dw_norm_2_beta_bytes, NULL, &err));
    OCL_CHECK(err, dw_norm_2_beta = (float *)q.enqueueMapBuffer(buffer_DataIn_22, CL_TRUE, CL_MAP_WRITE, 0, dw_norm_2_beta_bytes, NULL, NULL, &err));

    OCL_CHECK(err, cl::Buffer buffer_DataIn_23(context, CL_MEM_READ_ONLY, dw_norm_2_mean_bytes, NULL, &err));
    OCL_CHECK(err, dw_norm_2_mean = (float *)q.enqueueMapBuffer(buffer_DataIn_23, CL_TRUE, CL_MAP_WRITE, 0, dw_norm_2_mean_bytes, NULL, NULL, &err));

    OCL_CHECK(err, cl::Buffer buffer_DataIn_24(context, CL_MEM_READ_ONLY, dw_norm_2_var_bytes, NULL, &err));
    OCL_CHECK(err, dw_norm_2_var = (float *)q.enqueueMapBuffer(buffer_DataIn_24, CL_TRUE, CL_MAP_WRITE, 0, dw_norm_2_var_bytes, NULL, NULL, &err));

    OCL_CHECK(err, cl::Buffer buffer_DataIn_25(context, CL_MEM_READ_ONLY, proj_2_weight_bytes, NULL, &err));
    OCL_CHECK(err, proj_2_weight = (float *)q.enqueueMapBuffer(buffer_DataIn_25, CL_TRUE, CL_MAP_WRITE, 0, proj_2_weight_bytes, NULL, NULL, &err));

    OCL_CHECK(err, cl::Buffer buffer_DataIn_26(context, CL_MEM_READ_ONLY, Y_norm_1_bytes, NULL, &err));
    OCL_CHECK(err, Y_norm_1 = (float *)q.enqueueMapBuffer(buffer_DataIn_26, CL_TRUE, CL_MAP_WRITE, 0, Y_norm_1_bytes, NULL, NULL, &err));

    OCL_CHECK(err, cl::Buffer buffer_DataIn_27(context, CL_MEM_READ_ONLY, Y_v_conv_1_bytes, NULL, &err));
    OCL_CHECK(err, Y_v_conv_1 = (float *)q.enqueueMapBuffer(buffer_DataIn_27, CL_TRUE, CL_MAP_WRITE, 0, Y_v_conv_1_bytes, NULL, NULL, &err));

    OCL_CHECK(err, cl::Buffer buffer_DataIn_28(context, CL_MEM_READ_ONLY, Y_dw_conv_1_bytes, NULL, &err));
    OCL_CHECK(err, Y_dw_conv_1 = (float *)q.enqueueMapBuffer(buffer_DataIn_28, CL_TRUE, CL_MAP_WRITE, 0, Y_dw_conv_1_bytes, NULL, NULL, &err));

    OCL_CHECK(err, cl::Buffer buffer_DataIn_29(context, CL_MEM_READ_ONLY, Y_dw_norm_1_bytes, NULL, &err));
    OCL_CHECK(err, Y_dw_norm_1 = (float *)q.enqueueMapBuffer(buffer_DataIn_29, CL_TRUE, CL_MAP_WRITE, 0, Y_dw_norm_1_bytes, NULL, NULL, &err));

    OCL_CHECK(err, cl::Buffer buffer_DataIn_30(context, CL_MEM_READ_ONLY, Y_dw_act_1_bytes, NULL, &err));
    OCL_CHECK(err, Y_dw_act_1 = (float *)q.enqueueMapBuffer(buffer_DataIn_30, CL_TRUE, CL_MAP_WRITE, 0, Y_dw_act_1_bytes, NULL, NULL, &err));

    OCL_CHECK(err, cl::Buffer buffer_DataIn_31(context, CL_MEM_READ_ONLY, Y_proj_1_bytes, NULL, &err));
    OCL_CHECK(err, Y_proj_1 = (float *)q.enqueueMapBuffer(buffer_DataIn_31, CL_TRUE, CL_MAP_WRITE, 0, Y_proj_1_bytes, NULL, NULL, &err));

    OCL_CHECK(err, cl::Buffer buffer_DataIn_32(context, CL_MEM_READ_ONLY, Y_norm_2_bytes, NULL, &err));
    OCL_CHECK(err, Y_norm_2 = (float *)q.enqueueMapBuffer(buffer_DataIn_32, CL_TRUE, CL_MAP_WRITE, 0, Y_norm_2_bytes, NULL, NULL, &err));

    OCL_CHECK(err, cl::Buffer buffer_DataIn_33(context, CL_MEM_READ_ONLY, Y_v_conv_2_bytes, NULL, &err));
    OCL_CHECK(err, Y_v_conv_2 = (float *)q.enqueueMapBuffer(buffer_DataIn_33, CL_TRUE, CL_MAP_WRITE, 0, Y_v_conv_2_bytes, NULL, NULL, &err));

    OCL_CHECK(err, cl::Buffer buffer_DataIn_34(context, CL_MEM_READ_ONLY, Y_dw_conv_2_bytes, NULL, &err));
    OCL_CHECK(err, Y_dw_conv_2 = (float *)q.enqueueMapBuffer(buffer_DataIn_34, CL_TRUE, CL_MAP_WRITE, 0, Y_dw_conv_2_bytes, NULL, NULL, &err));

    OCL_CHECK(err, cl::Buffer buffer_DataIn_35(context, CL_MEM_READ_ONLY, Y_dw_norm_2_bytes, NULL, &err));
    OCL_CHECK(err, Y_dw_norm_2 = (float *)q.enqueueMapBuffer(buffer_DataIn_35, CL_TRUE, CL_MAP_WRITE, 0, Y_dw_norm_2_bytes, NULL, NULL, &err));

    OCL_CHECK(err, cl::Buffer buffer_DataIn_36(context, CL_MEM_READ_ONLY, Y_dw_act_2_bytes, NULL, &err));
    OCL_CHECK(err, Y_dw_act_2 = (float *)q.enqueueMapBuffer(buffer_DataIn_36, CL_TRUE, CL_MAP_WRITE, 0, Y_dw_act_2_bytes, NULL, NULL, &err));

    OCL_CHECK(err, cl::Buffer buffer_DataIn_37(context, CL_MEM_READ_ONLY, Y_proj_2_bytes, NULL, &err));
    OCL_CHECK(err, Y_proj_2 = (float *)q.enqueueMapBuffer(buffer_DataIn_37, CL_TRUE, CL_MAP_WRITE, 0, Y_proj_2_bytes, NULL, NULL, &err));

    OCL_CHECK(err, cl::Buffer buffer_DataIn_38(context, CL_MEM_READ_ONLY, Y_dw_skip_2_bytes, NULL, &err));
    OCL_CHECK(err, Y_dw_skip_2 = (float *)q.enqueueMapBuffer(buffer_DataIn_38, CL_TRUE, CL_MAP_WRITE, 0, Y_dw_skip_2_bytes, NULL, NULL, &err));

    // this is final output
    OCL_CHECK(err, cl::Buffer buffer_DataIn_39(context, CL_MEM_READ_ONLY, Y_skip_2_bytes, NULL, &err));
    OCL_CHECK(err, Y_skip_2 = (float *)q.enqueueMapBuffer(buffer_DataIn_39, CL_TRUE, CL_MAP_WRITE, 0, Y_skip_2_bytes, NULL, NULL, &err));

    // init out
    for (int i = 0; i < 75264; i++)
    {
        Y_norm_1[i] = 0;
        Y_dw_conv_1[i] = 0;
        Y_dw_norm_1[i] = 0;
        Y_dw_act_1[i] = 0;
    }

    for (int i = 0; i < 301056; i++)
        Y_v_conv_1[i] = 0;

    for (int i = 0; i < 25088; i++)
    {
        Y_proj_1[i] = 0;
        Y_norm_2[i] = 0;
        Y_proj_2[i] = 0;
        Y_skip_2[i] = 0;
    }

    for (int i = 0; i < 50176; i++)
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

// TODO: Init output data buffer

    // TODO: enqueue migrate memory objects
    // Data will be migrated to kernel space
    cout << "HOST-Info: Migrating memory objects ..." << endl;
    // 考慮input量，若有多份則要改成{buffer_DataIn1, buffer_DataIn2...}
    OCL_CHECK(err, err = q.enqueueMigrateMemObjects({buffer_DataIn_1, buffer_DataIn_2, buffer_DataIn_3, buffer_DataIn_4, buffer_DataIn_5,
                                                     buffer_DataIn_6, buffer_DataIn_7, buffer_DataIn_8, buffer_DataIn_9, buffer_DataIn_10
                                                     buffer_DataIn_11, buffer_DataIn_12, buffer_DataIn_13, buffer_DataIn_14, buffer_DataIn_15
                                                     buffer_DataIn_16, buffer_DataIn_17, buffer_DataIn_18, buffer_DataIn_19, buffer_DataIn_20,
                                                     buffer_DataIn_21, buffer_DataIn_22, buffer_DataIn_23, buffer_DataIn_24, buffer_DataIn_25,
                                                     buffer_DataIn_26, buffer_DataIn_27, buffer_DataIn_28, buffer_DataIn_29, buffer_DataIn_30
                                                     buffer_DataIn_31, buffer_DataIn_32, buffer_DataIn_33, buffer_DataIn_34, buffer_DataIn_35
                                                     buffer_DataIn_36, buffer_DataIn_37, buffer_DataIn_38
                                                    }, 0 /* 0 means from host*/));

// ============================================================================
// Step 5: Set Kernel Arguments and Run the Application
//         o) Set Kernel Arguments
//         o) Submit Kernels for Execution
//         o) Copy Results from Global Memory to Host
// ============================================================================
#ifdef ALL_MESSAGES
    cout << "HOST-Info: ============================================================= " << endl;
    cout << "HOST-Info: (Step 5) Run Application                                      " << endl;
    cout << "HOST-Info: ============================================================= " << endl;
#endif
// ----------------------------------------
// Step 5.1: Set Kernel Arguments
// ----------------------------------------
#ifdef ALL_MESSAGES
    cout << "HOST-Info: Setting Kernel arguments ..." << endl;
#endif
    // TODO: set the array of pointer
    // set the kernel Arguments
    int narg = 0;
    OCL_CHECK(err, err = kernel_stage1.setArg(narg++, buffer_DataIn_1));
    OCL_CHECK(err, err = kernel_stage1.setArg(narg++, buffer_DataIn_2));
    OCL_CHECK(err, err = kernel_stage1.setArg(narg++, buffer_DataIn_3));
    OCL_CHECK(err, err = kernel_stage1.setArg(narg++, buffer_DataIn_4));
    OCL_CHECK(err, err = kernel_stage1.setArg(narg++, buffer_DataIn_5));
    OCL_CHECK(err, err = kernel_stage1.setArg(narg++, buffer_DataIn_6));
    OCL_CHECK(err, err = kernel_stage1.setArg(narg++, buffer_DataIn_7));
    OCL_CHECK(err, err = kernel_stage1.setArg(narg++, buffer_DataIn_8));
    OCL_CHECK(err, err = kernel_stage1.setArg(narg++, buffer_DataIn_9));
    OCL_CHECK(err, err = kernel_stage1.setArg(narg++, buffer_DataIn_10));
    OCL_CHECK(err, err = kernel_stage1.setArg(narg++, buffer_DataIn_11));
    OCL_CHECK(err, err = kernel_stage1.setArg(narg++, buffer_DataIn_12));
    OCL_CHECK(err, err = kernel_stage1.setArg(narg++, buffer_DataIn_13));
    OCL_CHECK(err, err = kernel_stage1.setArg(narg++, buffer_DataIn_14));
    OCL_CHECK(err, err = kernel_stage1.setArg(narg++, buffer_DataIn_15));
    OCL_CHECK(err, err = kernel_stage1.setArg(narg++, buffer_DataIn_16));
    OCL_CHECK(err, err = kernel_stage1.setArg(narg++, buffer_DataIn_17));
    OCL_CHECK(err, err = kernel_stage1.setArg(narg++, buffer_DataIn_18));
    OCL_CHECK(err, err = kernel_stage1.setArg(narg++, buffer_DataIn_19));
    OCL_CHECK(err, err = kernel_stage1.setArg(narg++, buffer_DataIn_20));
    OCL_CHECK(err, err = kernel_stage1.setArg(narg++, buffer_DataIn_21));
    OCL_CHECK(err, err = kernel_stage1.setArg(narg++, buffer_DataIn_22));
    OCL_CHECK(err, err = kernel_stage1.setArg(narg++, buffer_DataIn_23));
    OCL_CHECK(err, err = kernel_stage1.setArg(narg++, buffer_DataIn_24));
    OCL_CHECK(err, err = kernel_stage1.setArg(narg++, buffer_DataIn_25));
    OCL_CHECK(err, err = kernel_stage1.setArg(narg++, buffer_DataIn_26));
    OCL_CHECK(err, err = kernel_stage1.setArg(narg++, buffer_DataIn_27));
    OCL_CHECK(err, err = kernel_stage1.setArg(narg++, buffer_DataIn_28));
    OCL_CHECK(err, err = kernel_stage1.setArg(narg++, buffer_DataIn_29));
    OCL_CHECK(err, err = kernel_stage1.setArg(narg++, buffer_DataIn_30));
    OCL_CHECK(err, err = kernel_stage1.setArg(narg++, buffer_DataIn_31));
    OCL_CHECK(err, err = kernel_stage1.setArg(narg++, buffer_DataIn_32));
    OCL_CHECK(err, err = kernel_stage1.setArg(narg++, buffer_DataIn_33));
    OCL_CHECK(err, err = kernel_stage1.setArg(narg++, buffer_DataIn_34));
    OCL_CHECK(err, err = kernel_stage1.setArg(narg++, buffer_DataIn_35));
    OCL_CHECK(err, err = kernel_stage1.setArg(narg++, buffer_DataIn_36));
    OCL_CHECK(err, err = kernel_stage1.setArg(narg++, buffer_DataIn_37));
    OCL_CHECK(err, err = kernel_stage1.setArg(narg++, buffer_DataIn_38));
    OCL_CHECK(err, err = kernel_stage1.setArg(narg++, buffer_DataIn_39));
// ----------------------------------------
// Step 5.2: Submit Kernels for Execution
// ----------------------------------------
#ifdef ALL_MESSAGES
    cout << "HOST-Info: Submitting Kernel kernel_stage1 ..." << endl;
#endif
    // TODO: launch the kernel
    // Launch the Kernel
    OCL_CHECK(err, err = q.enqueueTask(kernel_stage1));

    // The result of the previous kernel execution will need to be retrieved in
    // order to view the results. This call will transfer the data from FPGA to
    // source_results vector
    // TODO: launch the kernel
    OCL_CHECK(err, q.enqueueMigrateMemObjects({buffer_DataIn_39}, CL_MIGRATE_MEM_OBJECT_HOST));
    OCL_CHECK(err, q.finish());

// ============================================================================
// Step 6: Processing Output Results
//         o) Check correctness of the output results
// ============================================================================
#ifdef ALL_MESSAGES
    cout << "HOST-Info: ============================================================= " << endl;
    cout << "HOST-Info: (Step 6) Check the Output Results                             " << endl;
    cout << "HOST-Info: ============================================================= " << endl;
#endif

    // TODO: remember your data shape
    // ------------------------------------------------------
    // Step 6.1: Check correctness of the output results
    // ------------------------------------------------------
    bool error_detected = false;
    // for (int i = 0; i < DATA_SIZE; i++)
    // {
    //     int host_result = In[i] + Kernel[i];
    //     if (Out[i] != host_result)
    //     {
    //         printf(error_message.c_str(), i, host_result, Out[i]);
    //         error_detected = true;
    //         break;
    //     }
    // }
    cout << "Check output result: " << endl;
    int outsize = 8;
    cout << "After DW conv: " << endl;
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

    // ============================================================================
    // Step 7: Custom Profiling
    // ============================================================================
    // cout << "HOST-Info: ============================================================= " << endl;
    // cout << "HOST-Info: (Step 7) Custom Profiling                                     " << endl;
    // cout << "HOST-Info: ============================================================= " << endl;

    // int Nb_Of_Kernels = 1;
    // int Nb_Of_Memory_Tranfers = Nb_Of_Mem_Events;

    // string list_of_kernel_names[Nb_Of_Kernels];
    // list_of_kernel_names[0]="kernel_conv_norm_act";
    // run_custom_profiling (Nb_Of_Kernels,Nb_Of_Memory_Tranfers,K_exe_event,Mem_op_event,list_of_kernel_names);

    // ============================================================================
    // Step 8: Release Allocated Resources
    // ============================================================================
    // TODO: free all the resources
    OCL_CHECK(err, err = q.enqueueUnmapMemObject(buffer_DataIn_1, X_data));
    OCL_CHECK(err, err = q.enqueueUnmapMemObject(buffer_DataIn_2, norm_1_weight));
    OCL_CHECK(err, err = q.enqueueUnmapMemObject(buffer_DataIn_3, norm_1_bias));
    OCL_CHECK(err, err = q.enqueueUnmapMemObject(buffer_DataIn_4, norm_1_running_mean));
    OCL_CHECK(err, err = q.enqueueUnmapMemObject(buffer_DataIn_5, norm_1_running_var));
    OCL_CHECK(err, err = q.enqueueUnmapMemObject(buffer_DataIn_6, v_conv_1_weight));
    OCL_CHECK(err, err = q.enqueueUnmapMemObject(buffer_DataIn_7, v_conv_1_bias));
    OCL_CHECK(err, err = q.enqueueUnmapMemObject(buffer_DataIn_8, dw_conv_1_filter));
    OCL_CHECK(err, err = q.enqueueUnmapMemObject(buffer_DataIn_9, dw_norm_1_gamma));
    OCL_CHECK(err, err = q.enqueueUnmapMemObject(buffer_DataIn_10, dw_norm_1_beta));
    OCL_CHECK(err, err = q.enqueueUnmapMemObject(buffer_DataIn_11, dw_norm_1_mean));
    OCL_CHECK(err, err = q.enqueueUnmapMemObject(buffer_DataIn_12, dw_norm_1_var));
    OCL_CHECK(err, err = q.enqueueUnmapMemObject(buffer_DataIn_13, proj_1_weight));
    OCL_CHECK(err, err = q.enqueueUnmapMemObject(buffer_DataIn_14, norm_2_weight));
    OCL_CHECK(err, err = q.enqueueUnmapMemObject(buffer_DataIn_15, norm_2_bias));
    OCL_CHECK(err, err = q.enqueueUnmapMemObject(buffer_DataIn_16, norm_2_running_mean));
    OCL_CHECK(err, err = q.enqueueUnmapMemObject(buffer_DataIn_17, norm_2_running_var));
    OCL_CHECK(err, err = q.enqueueUnmapMemObject(buffer_DataIn_18, v_conv_2_weight));
    OCL_CHECK(err, err = q.enqueueUnmapMemObject(buffer_DataIn_19, v_conv_2_bias));
    OCL_CHECK(err, err = q.enqueueUnmapMemObject(buffer_DataIn_20, dw_conv_2_filter));
    OCL_CHECK(err, err = q.enqueueUnmapMemObject(buffer_DataIn_21, dw_norm_2_gamma));
    OCL_CHECK(err, err = q.enqueueUnmapMemObject(buffer_DataIn_22, dw_norm_2_beta));
    OCL_CHECK(err, err = q.enqueueUnmapMemObject(buffer_DataIn_23, dw_norm_2_mean));
    OCL_CHECK(err, err = q.enqueueUnmapMemObject(buffer_DataIn_24, dw_norm_2_var));
    OCL_CHECK(err, err = q.enqueueUnmapMemObject(buffer_DataIn_25, proj_2_weight));
    OCL_CHECK(err, err = q.enqueueUnmapMemObject(buffer_DataIn_26, Y_norm_1));
    OCL_CHECK(err, err = q.enqueueUnmapMemObject(buffer_DataIn_27, Y_v_conv_1));
    OCL_CHECK(err, err = q.enqueueUnmapMemObject(buffer_DataIn_28, Y_dw_conv_1));
    OCL_CHECK(err, err = q.enqueueUnmapMemObject(buffer_DataIn_29, Y_dw_norm_1));
    OCL_CHECK(err, err = q.enqueueUnmapMemObject(buffer_DataIn_30, Y_dw_act_1));
    OCL_CHECK(err, err = q.enqueueUnmapMemObject(buffer_DataIn_31, Y_proj_1));
    OCL_CHECK(err, err = q.enqueueUnmapMemObject(buffer_DataIn_32, Y_norm_2));
    OCL_CHECK(err, err = q.enqueueUnmapMemObject(buffer_DataIn_33, Y_v_conv_2));
    OCL_CHECK(err, err = q.enqueueUnmapMemObject(buffer_DataIn_34, Y_dw_conv_2));
    OCL_CHECK(err, err = q.enqueueUnmapMemObject(buffer_DataIn_35, Y_dw_norm_2));
    OCL_CHECK(err, err = q.enqueueUnmapMemObject(buffer_DataIn_36, Y_dw_act_2));
    OCL_CHECK(err, err = q.enqueueUnmapMemObject(buffer_DataIn_37, Y_proj_2));
    OCL_CHECK(err, err = q.enqueueUnmapMemObject(buffer_DataIn_38, Y_dw_skip_2));
    OCL_CHECK(err, err = q.enqueueUnmapMemObject(buffer_DataIn_39, Y_skip_2));

    OCL_CHECK(err, err = q.finish());

    cout << "HOST-Info: TEST " << (error_detected ? "FAILED" : "PASSED") << endl;
    cout << "HOST-Info: DONE" << endl
         << endl;

    return (error_detected ? EXIT_FAILURE : EXIT_SUCCESS);
}

/*
Result:


*/
