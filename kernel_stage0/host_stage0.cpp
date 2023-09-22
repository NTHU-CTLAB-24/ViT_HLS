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

#include "host_stage0.hpp"
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
// 參考count_depth.py的計算
static const int X_data_size = 37632; //1x3x112x112
static const int msp_filter_size = 648;
static const int msp_bias_size = 24;
static const int reduce_filter_size = 576;
static const int reduce_bias_size = 24;
static const int expand_filter_size = 576;
static const int expand_bias_size = 24;

static const int mean_size = 24;
static const int var_size = 24;
static const int gamma_size = 24;
static const int beta_size = 24;

static const int X_pad_size = 38988;
static const int X_conv_size = 75264;
static const int X_mean_size = 24;
static const int X_reduce_size = 24;
static const int X_relu_size = 24;
static const int X_expand_size = 24;
static const int X_sigmoid_size = 24;
static const int Y_msp_size = 75264;

static const int Y_se_size = 75264; //final output

// Compute the size of array in bytes
size_t X_data_bytes = X_data_size * sizeof(float);
size_t msp_filter_bytes = msp_filter_size * sizeof(float);
size_t msp_bias_bytes = msp_bias_size * sizeof(float);
size_t reduce_filter_bytes = reduce_filter_size * sizeof(float);
size_t reduce_bias_bytes = reduce_bias_size * sizeof(float);
size_t expand_filter_bytes = expand_filter_size * sizeof(float);
size_t expand_bias_bytes = expand_bias_size * sizeof(float);

size_t mean_bytes = mean_size * sizeof(float);
size_t var_bytes = var_size * sizeof(float);
size_t gamma_bytes = gamma_size * sizeof(float);
size_t beta_bytes = beta_size * sizeof(float);

size_t X_pad_bytes = X_pad_size * sizeof(float);
size_t X_conv_bytes = X_conv_size * sizeof(float);
size_t X_mean_bytes = X_mean_size * sizeof(float);
size_t X_reduce_bytes = X_reduce_size * sizeof(float);
size_t X_relu_bytes = X_reduce_size * sizeof(float);
size_t X_expand_bytes = X_expand_size * sizeof(float);
size_t X_sigmoid_bytes = X_sigmoid_size * sizeof(float);
size_t Y_msp_bytes = Y_msp_size * sizeof(float);

size_t Y_se_bytes = Y_se_size * sizeof(float);
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
    cl::Kernel kernel_stage0;
#ifdef ALL_MESSAGESF
    cout << "HOST-Info: Creating a Kernel: kernel_mspatch ..." << endl;
    cout << "HOST-Info: Creating a Kernel: kernel_DW_conv ..." << endl;
    cout << "HOST-Info: Creating a Kernel: kernel_se ..." << endl;
    cout << "HOST-Info: Creating a Kernel: kernel_proj ..." << endl;
#endif
    OCL_CHECK(err, kernel_stage0 = cl::Kernel(program, "kernel_stage0", &err));

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
    float* X_data; //input image
    float* msp_filter;
    float* msp_bias;
    float* reduce_filter;
    float* reduce_bias;
    float* expand_filter;
    float* expand_bias;
    float* mean;
    float* var;
    float* gamma;
    float* beta;

    //temporary storage
    float* X_pad;
    float* X_conv;
    float* X_mean;
    float* X_reduce;
    float* X_relu;
    float* X_expand;
    float* X_sigmoid;
    float* Y_msp; //result of MSP module

    //output
    float* Y_se; //result of SE module
    
// These commands will allocate memory on the .Device
// The cl::Buffer objects can be used to reference the memory locations on the device.
/* 以下區域為input data傳入host的code，只需要複製並且更改參數和型別即可(size_in_bytes(考慮input大小(byte)), In, DATA_SIZE(考慮input大小))*/
// TODO:Init input data buffer
    OCL_CHECK(err, cl::Buffer buffer_DataIn_1(context, CL_MEM_READ_ONLY, X_data_bytes, NULL, &err));
    OCL_CHECK(err,
              X_data = (float *)q.enqueueMapBuffer(buffer_DataIn_1, CL_TRUE, CL_MAP_WRITE, 0, X_data_bytes, NULL, NULL, &err));
    dataPrepare(X_data, 1, 3, 112, 112);

    OCL_CHECK(err, cl::Buffer buffer_DataIn_2(context, CL_MEM_READ_ONLY, msp_filter_bytes, NULL, &err));
    OCL_CHECK(err,
              msp_filter = (float *)q.enqueueMapBuffer(buffer_DataIn_2, CL_TRUE, CL_MAP_WRITE, 0, msp_filter_bytes, NULL, NULL, &err));
    mspfilterPrepare(msp_filter, 24, 3, 3, 3);

    OCL_CHECK(err, cl::Buffer buffer_DataIn_3(context, CL_MEM_READ_ONLY, msp_bias_bytes, NULL, &err));
    OCL_CHECK(err,
            msp_bias = (float *)q.enqueueMapBuffer(buffer_DataIn_3, CL_TRUE, CL_MAP_WRITE, 0, msp_bias_bytes, NULL, NULL, &err));
    mspbiasPrepare(msp_bias, 24);

    OCL_CHECK(err, cl::Buffer buffer_DataIn_4(context, CL_MEM_READ_ONLY, reduce_filter_bytes, NULL, &err));
    OCL_CHECK(err,
            reduce_filter = (float *)q.enqueueMapBuffer(buffer_DataIn_4, CL_TRUE, CL_MAP_WRITE, 0, reduce_filter_bytes, NULL, NULL, &err));
    reducefilterPrepare(reduce_filter, 24, 24);

    OCL_CHECK(err, cl::Buffer buffer_DataIn_5(context, CL_MEM_READ_ONLY, reduce_bias_bytes, NULL, &err));
    OCL_CHECK(err,
            reduce_bias = (float *)q.enqueueMapBuffer(buffer_DataIn_5, CL_TRUE, CL_MAP_WRITE, 0, reduce_bias_bytes, NULL, NULL, &err));
    reducebiasPrepare(reduce_bias, 24);

    OCL_CHECK(err, cl::Buffer buffer_DataIn_6(context, CL_MEM_READ_ONLY, expand_filter_bytes, NULL, &err));
    OCL_CHECK(err,
            expand_filter = (float *)q.enqueueMapBuffer(buffer_DataIn_6, CL_TRUE, CL_MAP_WRITE, 0, expand_filter_bytes, NULL, NULL, &err));
    expandfilterPrepare(expand_filter, 24, 24);

    OCL_CHECK(err, cl::Buffer buffer_DataIn_7(context, CL_MEM_READ_ONLY, expand_bias_bytes, NULL, &err));
    OCL_CHECK(err,
            expand_bias = (float *)q.enqueueMapBuffer(buffer_DataIn_7, CL_TRUE, CL_MAP_WRITE, 0, expand_bias_bytes, NULL, NULL, &err));
    expandbiasPrepare(expand_bias, 24);

    OCL_CHECK(err, cl::Buffer buffer_DataIn_8(context, CL_MEM_READ_ONLY, mean_bytes, NULL, &err));
    OCL_CHECK(err,
            mean = (float *)q.enqueueMapBuffer(buffer_DataIn_8, CL_TRUE, CL_MAP_WRITE, 0, mean_bytes, NULL, NULL, &err));
    meanPrepare(mean, 24);

    OCL_CHECK(err, cl::Buffer buffer_DataIn_9(context, CL_MEM_READ_ONLY, var_bytes, NULL, &err));
    OCL_CHECK(err,
            var = (float *)q.enqueueMapBuffer(buffer_DataIn_9, CL_TRUE, CL_MAP_WRITE, 0, var_bytes, NULL, NULL, &err));
    varPrepare(var, 24);

    OCL_CHECK(err, cl::Buffer buffer_DataIn_10(context, CL_MEM_READ_ONLY, gamma_bytes, NULL, &err));
    OCL_CHECK(err,
            gamma = (float *)q.enqueueMapBuffer(buffer_DataIn_10, CL_TRUE, CL_MAP_WRITE, 0, gamma_bytes, NULL, NULL, &err));
    gammaPrepare(gamma, 24);

    OCL_CHECK(err, cl::Buffer buffer_DataIn_11(context, CL_MEM_READ_ONLY, beta_bytes, NULL, &err));
    OCL_CHECK(err,
            beta = (float *)q.enqueueMapBuffer(buffer_DataIn_11, CL_TRUE, CL_MAP_WRITE, 0, beta_bytes, NULL, NULL, &err));
    betaPrepare(beta, 24);

// TODO: Init output data buffer
#ifdef ALL_MESSAGES
    cout << "HOST-Info: Allocating Memory for RES Array ... " << endl;
#endif
    OCL_CHECK(err, cl::Buffer buffer_tmp1(context, CL_MEM_READ_ONLY, X_pad_bytes, NULL, &err));
    OCL_CHECK(err,
            X_pad = (float *)q.enqueueMapBuffer(buffer_tmp1, CL_TRUE, CL_MAP_WRITE, 0, X_pad_bytes, NULL, NULL, &err));

    OCL_CHECK(err, cl::Buffer buffer_tmp2(context, CL_MEM_READ_ONLY, X_conv_bytes, NULL, &err));
    OCL_CHECK(err,
            X_conv = (float *)q.enqueueMapBuffer(buffer_tmp2, CL_TRUE, CL_MAP_WRITE, 0, X_conv_bytes, NULL, NULL, &err));
    
    OCL_CHECK(err, cl::Buffer buffer_tmp3(context, CL_MEM_READ_ONLY, X_mean_bytes, NULL, &err));
    OCL_CHECK(err,
            X_mean = (float *)q.enqueueMapBuffer(buffer_tmp3, CL_TRUE, CL_MAP_WRITE, 0, X_mean_bytes, NULL, NULL, &err));

    OCL_CHECK(err, cl::Buffer buffer_tmp4(context, CL_MEM_READ_ONLY, X_reduce_bytes, NULL, &err));
    OCL_CHECK(err,
            X_reduce = (float *)q.enqueueMapBuffer(buffer_tmp4, CL_TRUE, CL_MAP_WRITE, 0, X_reduce_bytes, NULL, NULL, &err));

    OCL_CHECK(err, cl::Buffer buffer_tmp5(context, CL_MEM_READ_ONLY, X_relu_bytes, NULL, &err));
    OCL_CHECK(err,
            X_relu = (float *)q.enqueueMapBuffer(buffer_tmp5, CL_TRUE, CL_MAP_WRITE, 0, X_relu_bytes, NULL, NULL, &err));

    OCL_CHECK(err, cl::Buffer buffer_tmp6(context, CL_MEM_READ_ONLY, X_expand_bytes, NULL, &err));
    OCL_CHECK(err,
            X_expand = (float *)q.enqueueMapBuffer(buffer_tmp6, CL_TRUE, CL_MAP_WRITE, 0, X_expand_bytes, NULL, NULL, &err));

    OCL_CHECK(err, cl::Buffer buffer_tmp7(context, CL_MEM_READ_ONLY, X_sigmoid_bytes, NULL, &err));
    OCL_CHECK(err,
            X_sigmoid = (float *)q.enqueueMapBuffer(buffer_tmp7, CL_TRUE, CL_MAP_WRITE, 0, X_sigmoid_bytes, NULL, NULL, &err));

    OCL_CHECK(err, cl::Buffer buffer_tmp8(context, CL_MEM_READ_ONLY, Y_msp_bytes, NULL, &err));
    OCL_CHECK(err,
            Y_msp = (float *)q.enqueueMapBuffer(buffer_tmp8, CL_TRUE, CL_MAP_WRITE, 0, Y_msp_bytes, NULL, NULL, &err));

    OCL_CHECK(err, cl::Buffer buffer_result(context, CL_MEM_READ_ONLY, Y_se_bytes, NULL, &err));
    OCL_CHECK(err,
            Y_se = (float *)q.enqueueMapBuffer(buffer_result, CL_TRUE, CL_MAP_WRITE, 0, Y_se_bytes, NULL, NULL, &err));
    // TODO: enqueue migrate memory objects
    // Data will be migrated to kernel space
    cout << "HOST-Info: Migrating memory objects ..." << endl;
    // 考慮input量，若有多份則要改成{buffer_DataIn1, buffer_DataIn2...}
    OCL_CHECK(err, err = q.enqueueMigrateMemObjects({buffer_DataIn_1, buffer_DataIn_2, buffer_DataIn_3, buffer_DataIn_4,
                                                    buffer_DataIn_5, buffer_DataIn_6, buffer_DataIn_7, buffer_DataIn_8,
                                                    buffer_DataIn_9, buffer_DataIn_10, buffer_DataIn_11, 
                                                    buffer_tmp1, buffer_tmp2, buffer_tmp3, buffer_tmp4, 
                                                    buffer_tmp5, buffer_tmp6, buffer_tmp7, buffer_tmp8}, 0 /* 0 means from host*/));

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
    OCL_CHECK(err, err = kernel_stage0.setArg(narg++, buffer_DataIn_1));
    OCL_CHECK(err, err = kernel_stage0.setArg(narg++, buffer_DataIn_2));
    OCL_CHECK(err, err = kernel_stage0.setArg(narg++, buffer_DataIn_3));
    OCL_CHECK(err, err = kernel_stage0.setArg(narg++, buffer_DataIn_4));
    OCL_CHECK(err, err = kernel_stage0.setArg(narg++, buffer_DataIn_5));
    OCL_CHECK(err, err = kernel_stage0.setArg(narg++, buffer_DataIn_6));
    OCL_CHECK(err, err = kernel_stage0.setArg(narg++, buffer_DataIn_7));
    OCL_CHECK(err, err = kernel_stage0.setArg(narg++, buffer_DataIn_8));
    OCL_CHECK(err, err = kernel_stage0.setArg(narg++, buffer_DataIn_9));
    OCL_CHECK(err, err = kernel_stage0.setArg(narg++, buffer_DataIn_10));
    OCL_CHECK(err, err = kernel_stage0.setArg(narg++, buffer_DataIn_11));

    OCL_CHECK(err, err = kernel_stage0.setArg(narg++, buffer_tmp1));
    OCL_CHECK(err, err = kernel_stage0.setArg(narg++, buffer_tmp2));
    OCL_CHECK(err, err = kernel_stage0.setArg(narg++, buffer_tmp3));
    OCL_CHECK(err, err = kernel_stage0.setArg(narg++, buffer_tmp4));
    OCL_CHECK(err, err = kernel_stage0.setArg(narg++, buffer_tmp5));
    OCL_CHECK(err, err = kernel_stage0.setArg(narg++, buffer_tmp6));
    OCL_CHECK(err, err = kernel_stage0.setArg(narg++, buffer_tmp7));
    OCL_CHECK(err, err = kernel_stage0.setArg(narg++, buffer_tmp8));

    OCL_CHECK(err, err = kernel_stage0.setArg(narg++, buffer_result));
// ----------------------------------------
// Step 5.2: Submit Kernels for Execution
// ----------------------------------------
#ifdef ALL_MESSAGES
    cout << "HOST-Info: Submitting Kernel kernel_stage0 ..." << endl;
#endif
    // TODO: launch the kernel
    // Launch the Kernel
    OCL_CHECK(err, err = q.enqueueTask(kernel_stage0));

    // The result of the previous kernel execution will need to be retrieved in
    // order to view the results. This call will transfer the data from FPGA to
    // source_results vector
    // TODO: launch the kernel
    OCL_CHECK(err, q.enqueueMigrateMemObjects({buffer_result}, CL_MIGRATE_MEM_OBJECT_HOST));
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
    for (int n = 0; n < 1; n++){
        for (int c = 0; c < 24; c++){
            for (int h = 0; h < 56; h++){
                for (int w = 0; w < 56; w++){
                    if (w == 56 - 1)
                        cout << Y_se[n*24*56*56 + c*56*56 + h*56 + w] << endl;
                    else
                        cout <<  Y_se[n*24*56*56 + c*56*56 + h*56 + w] << " ";
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
    OCL_CHECK(err, err = q.enqueueUnmapMemObject(buffer_DataIn_2, msp_filter));
    OCL_CHECK(err, err = q.enqueueUnmapMemObject(buffer_DataIn_3, msp_bias));
    OCL_CHECK(err, err = q.enqueueUnmapMemObject(buffer_DataIn_4, reduce_filter));
    OCL_CHECK(err, err = q.enqueueUnmapMemObject(buffer_DataIn_5, reduce_bias));
    OCL_CHECK(err, err = q.enqueueUnmapMemObject(buffer_DataIn_6, expand_filter));
    OCL_CHECK(err, err = q.enqueueUnmapMemObject(buffer_DataIn_7, expand_bias));
    OCL_CHECK(err, err = q.enqueueUnmapMemObject(buffer_DataIn_8, mean));
    OCL_CHECK(err, err = q.enqueueUnmapMemObject(buffer_DataIn_9, var));
    OCL_CHECK(err, err = q.enqueueUnmapMemObject(buffer_DataIn_10, gamma));
    OCL_CHECK(err, err = q.enqueueUnmapMemObject(buffer_DataIn_11, beta));

    OCL_CHECK(err, err = q.enqueueUnmapMemObject(buffer_tmp1, X_pad));
    OCL_CHECK(err, err = q.enqueueUnmapMemObject(buffer_tmp2, X_conv));
    OCL_CHECK(err, err = q.enqueueUnmapMemObject(buffer_tmp3, X_mean));
    OCL_CHECK(err, err = q.enqueueUnmapMemObject(buffer_tmp4, X_reduce));
    OCL_CHECK(err, err = q.enqueueUnmapMemObject(buffer_tmp5, X_relu));
    OCL_CHECK(err, err = q.enqueueUnmapMemObject(buffer_tmp6, X_expand));
    OCL_CHECK(err, err = q.enqueueUnmapMemObject(buffer_tmp7, X_sigmoid));
    OCL_CHECK(err, err = q.enqueueUnmapMemObject(buffer_tmp8, Y_msp));

    OCL_CHECK(err, err = q.enqueueUnmapMemObject(buffer_result, Y_se));
    OCL_CHECK(err, err = q.finish());

    cout << "HOST-Info: TEST " << (error_detected ? "FAILED" : "PASSED") << endl;
    cout << "HOST-Info: DONE" << endl
         << endl;

    return (error_detected ? EXIT_FAILURE : EXIT_SUCCESS);
}

/*
Result:


*/
