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

#include "host_iRMB_stage0.hpp"
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
static const int BATCH_SIZE = 1;
static const int CHANNEL_IN = 3;
static const int CHANNEL_OUT = 24;
static const int HEIGHT_IN = 112;
static const int WIDTH_IN = 112;

// Convolution parameters
static const int KERNEL_SIZE = 3;
static const int STRIDE = 2;
static const int GROUP = 1;

static const int PADDING = ceil((float)(KERNEL_SIZE - STRIDE) / 2);
static const int HEIGHT_OUT = (HEIGHT_IN - KERNEL_SIZE + 2 * PADDING) / STRIDE + 1;
static const int WIDTH_OUT = (WIDTH_IN - KERNEL_SIZE + 2 * PADDING) / STRIDE + 1;


// In and out size
static const int IN_SIZE = BATCH_SIZE * HEIGHT_IN * WIDTH_IN * CHANNEL_IN;
static const int MSP_NORM_SIZE = CHANNEL_OUT * 4;
static const int OUT_SIZE = BATCH_SIZE * HEIGHT_OUT * WIDTH_OUT * CHANNEL_OUT;

// Compute the size of array in bytes
size_t size_in_bytes = IN_SIZE * sizeof(ftype);
size_t size_msp_norm_bytes = MSP_NORM_SIZE * sizeof(ftype);
size_t size_out_bytes = OUT_SIZE * sizeof(ftype);

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
    cl::Kernel kernel_mspatch;
    cl::Kernel kernel_DW_conv;
    cl::Kernel kernel_se;
    cl::Kernel kernel_proj;
#ifdef ALL_MESSAGESF
    cout << "HOST-Info: Creating a Kernel: kernel_mspatch ..." << endl;
    cout << "HOST-Info: Creating a Kernel: kernel_DW_conv ..." << endl;
    cout << "HOST-Info: Creating a Kernel: kernel_se ..." << endl;
    cout << "HOST-Info: Creating a Kernel: kernel_proj ..." << endl;
#endif
    OCL_CHECK(err, kernel_mspatch = cl::Kernel(program, "kernel_mspatch", &err));
    OCL_CHECK(err, kernel_DW_conv = cl::Kernel(program, "kernel_DW_conv", &err));
    OCL_CHECK(err, kernel_se = cl::Kernel(program, "kernel_se", &err));
    OCL_CHECK(err, kernel_proj = cl::Kernel(program, "kernel_proj", &err));

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
    // int *In;
    // int *Kernel;
    // int *Out;
    ftype *In;
    ftype *msp_norm;
    ftype *msp_out;
    ftype *dw_conv_out;
    ftype *se_out;
    float *Out;
// These commands will allocate memory on the .Device
// The cl::Buffer objects can be used to reference the memory locations on the device.
/* 以下區域為input data傳入host的code，只需要複製並且更改參數和型別即可(size_in_bytes(考慮input大小(byte)), In, DATA_SIZE(考慮input大小))*/
// TODO:Init input data buffer
#ifdef ALL_MESSAGES
    cout << "HOST-Info: Allocating Memory buffer_DataIn_1 for DataIn_1 ... " << endl;
#endif
    OCL_CHECK(err, cl::Buffer buffer_DataIn_1(context, CL_MEM_READ_ONLY, size_in_bytes, NULL, &err));
#ifdef ALL_MESSAGES
    cout << "HOST-Info: Mapping buffer_DataIn_1 to In ... " << endl;
#endif
    OCL_CHECK(err,
              In = (ftype *)q.enqueueMapBuffer(buffer_DataIn_1, CL_TRUE, CL_MAP_WRITE, 0, size_in_bytes, NULL, NULL, &err));
#ifdef ALL_MESSAGES
    cout << "HOST-Info: Generating buffer_DataIn_1 ..." << endl;
#endif
    // Call dataPrepare to init data
    // dataPrepare(In, DATA_SIZE);
    for (int n = 0; n < BATCH_SIZE; n++)
    {
        for (int c = 0; c < CHANNEL_IN; c++)
        {
            for (int h = 0; h < HEIGHT_IN; h++)
            {
                for (int w = 0; w < WIDTH_IN; w++)
                {
                    In[n * CHANNEL_IN * HEIGHT_IN * WIDTH_IN + c * HEIGHT_IN * WIDTH_IN + h * WIDTH_IN + w] = (ftype)(h + c);
                }
            }
        }
    }

#ifdef ALL_MESSAGES
    cout << "           Generated " << IN_SIZE << " values" << endl;
#endif

#ifdef ALL_MESSAGES
    cout << "HOST-Info: Allocating Memory buffer_DataIn_2 for DataIn_2 ... " << endl;
#endif
    OCL_CHECK(err, cl::Buffer buffer_DataIn_2(context, CL_MEM_READ_ONLY, size_msp_norm_bytes, NULL, &err));
#ifdef ALL_MESSAGES
    cout << "HOST-Info: Mapping buffer_DataIn_2 to msp_norm ... " << endl;
#endif
    OCL_CHECK(err,
              msp_norm = (ftype *)q.enqueueMapBuffer(buffer_DataIn_2, CL_TRUE, CL_MAP_WRITE, 0, size_msp_norm_bytes, NULL, NULL, &err));
#ifdef ALL_MESSAGES
    cout << "HOST-Info: Generating buffer_DataIn_2 ..." << endl;
#endif
    // Call dataPrepare to init data
    // dataPrepare(In, DATA_SIZE);
    for (int i = 0; i < CHANNEL_OUT; i++)
    {
        msp_norm[i] = (ftype)8;
    }
    for (int i = CHANNEL_OUT; i < CHANNEL_OUT * 2; i++)
    {
        msp_norm[i] = (ftype)20;
    }
    for (int i = CHANNEL_OUT * 2; i < CHANNEL_OUT * 3; i++)
    {
        msp_norm[i] = (ftype)0.1;
    }
    for (int i = CHANNEL_OUT * 3; i < CHANNEL_OUT * 4; i++)
    {
        msp_norm[i] = (ftype)0.2;
    }

#ifdef ALL_MESSAGES
    cout << "           Generated " << MSP_NORM_SIZE << " values" << endl;
#endif

// TODO: Init output data buffer
#ifdef ALL_MESSAGES
    cout << "HOST-Info: Allocating Memory buffer_msp_out for RES Array ... " << endl;
    cout << "HOST-Info: Allocating Memory buffer_dw_conv_out for RES Array ... " << endl;
    cout << "HOST-Info: Allocating Memory buffer_se_out for RES Array ... " << endl;
    cout << "HOST-Info: Allocating Memory buffer_result for RES Array ... " << endl;
#endif
    OCL_CHECK(err, cl::Buffer buffer_msp_out(context, CL_MEM_WRITE_ONLY, size_out_bytes, NULL, &err));
    OCL_CHECK(err, cl::Buffer buffer_dw_conv_out(context, CL_MEM_WRITE_ONLY, size_out_bytes, NULL, &err));
    OCL_CHECK(err, cl::Buffer buffer_se_out(context, CL_MEM_WRITE_ONLY, size_out_bytes, NULL, &err));
    OCL_CHECK(err, cl::Buffer buffer_result(context, CL_MEM_WRITE_ONLY, size_out_bytes, NULL, &err));
#ifdef ALL_MESSAGES
    cout << "HOST-Info: Mapping buffer_msp_out to Out ... " << endl;
    cout << "HOST-Info: Mapping buffer_dw_conv_out to Out ... " << endl;
    cout << "HOST-Info: Mapping buffer_se_out to Out ... " << endl;
    cout << "HOST-Info: Mapping buffer_result to Out ... " << endl;
#endif
    OCL_CHECK(err,
              msp_out = (ftype *)q.enqueueMapBuffer(buffer_msp_out, CL_TRUE, CL_MAP_READ, 0, size_out_bytes, NULL, NULL, &err));
    OCL_CHECK(err,
              dw_conv_out = (ftype *)q.enqueueMapBuffer(buffer_dw_conv_out, CL_TRUE, CL_MAP_READ, 0, size_out_bytes, NULL, NULL, &err));
    OCL_CHECK(err,
              se_out = (ftype *)q.enqueueMapBuffer(buffer_se_out, CL_TRUE, CL_MAP_READ, 0, size_out_bytes, NULL, NULL, &err));
    OCL_CHECK(err,
              Out = (float *)q.enqueueMapBuffer(buffer_result, CL_TRUE, CL_MAP_READ, 0, size_out_bytes, NULL, NULL, &err));

    cout << "HOST-Info: Generating buffer_result ..." << endl;

    for (int n = 0; n < BATCH_SIZE; n++)
    {
        for (int c = 0; c < CHANNEL_OUT; c++)
        {
            for (int h = 0; h < HEIGHT_OUT; h++)
            {
                for (int w = 0; w < WIDTH_OUT; w++)
                {
                    msp_out[n * CHANNEL_OUT * HEIGHT_OUT * WIDTH_OUT + c * HEIGHT_OUT * WIDTH_OUT + h * WIDTH_OUT + w] = 0;
                    dw_conv_out[n * CHANNEL_OUT * HEIGHT_OUT * WIDTH_OUT + c * HEIGHT_OUT * WIDTH_OUT + h * WIDTH_OUT + w] = 0;
                    se_out[n * CHANNEL_OUT * HEIGHT_OUT * WIDTH_OUT + c * HEIGHT_OUT * WIDTH_OUT + h * WIDTH_OUT + w] = 0;
                    Out[n * CHANNEL_OUT * HEIGHT_OUT * WIDTH_OUT + c * HEIGHT_OUT * WIDTH_OUT + h * WIDTH_OUT + w] = 0;
                }
            }
        }
    }

    // TODO: enqueue migrate memory objects
    // Data will be migrated to kernel space
    cout << "HOST-Info: Migrating memory objects ..." << endl;
    // 考慮input量，若有多份則要改成{buffer_DataIn1, buffer_DataIn2...}
    OCL_CHECK(err, err = q.enqueueMigrateMemObjects({buffer_DataIn_1, buffer_DataIn_2}, 0 /* 0 means from host*/));
    OCL_CHECK(err, err = q.enqueueMigrateMemObjects({buffer_msp_out, buffer_dw_conv_out, buffer_se_out}, 0 /* 0 means from host*/));

// ============================================================================
// Step 5: Set Kernel Arguments and Run the Application
//         o) Set Kernel Arguments
// 				----------------------------------------------------
// 				 Kernel	  		Argument Nb		Description
// 				----------------------------------------------------
//  			 kernel_conv_norm_act	    0				GlobMem_BUF_DataIn_1
//  			 kernel_conv_norm_act	    1				GlobMem_BUF_DataIn_2
//  			 kernel_conv_norm_act	    2				GlobMem_BUF_RES
//  			 kernel_conv_norm_act	    3	K-A4u3StpzbW			CONST_arg
// 				----------------------------------------------------
//
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
    OCL_CHECK(err, err = kernel_mspatch.setArg(narg++, buffer_DataIn_1));
    OCL_CHECK(err, err = kernel_mspatch.setArg(narg++, buffer_DataIn_2));
    OCL_CHECK(err, err = kernel_mspatch.setArg(narg++, buffer_msp_out));

    narg = 0;
    OCL_CHECK(err, err = kernel_DW_conv.setArg(narg++, buffer_msp_out));
    OCL_CHECK(err, err = kernel_DW_conv.setArg(narg++, buffer_dw_conv_out));

    narg = 0;
    OCL_CHECK(err, err = kernel_se.setArg(narg++, buffer_dw_conv_out));
    OCL_CHECK(err, err = kernel_se.setArg(narg++, buffer_se_out));

    narg = 0;
    OCL_CHECK(err, err = kernel_proj.setArg(narg++, buffer_se_out));
    OCL_CHECK(err, err = kernel_proj.setArg(narg++, buffer_result));
    
// ----------------------------------------
// Step 5.2: Submit Kernels for Execution
// ----------------------------------------
#ifdef ALL_MESSAGES
    cout << "HOST-Info: Submitting Kernel kernel_conv_norm_act ..." << endl;
#endif
    // TODO: launch the kernel
    // Launch the Kernel
    OCL_CHECK(err, err = q.enqueueTask(kernel_mspatch));
    OCL_CHECK(err, err = q.enqueueTask(kernel_DW_conv));
    OCL_CHECK(err, err = q.enqueueTask(kernel_se));
    OCL_CHECK(err, err = q.enqueueTask(kernel_proj));


    // The result of the previous kernel execution will need to be retrieved in
    // order to view the results. This call will transfer the data from FPGA to
    // source_results vector
    // TODO: launch the kernel
    OCL_CHECK(err, q.enqueueMigrateMemObjects({buffer_msp_out}, CL_MIGRATE_MEM_OBJECT_HOST));
    OCL_CHECK(err, q.finish());
    
    OCL_CHECK(err, q.enqueueMigrateMemObjects({buffer_dw_conv_out}, CL_MIGRATE_MEM_OBJECT_HOST));
    OCL_CHECK(err, q.finish());
    
    OCL_CHECK(err, q.enqueueMigrateMemObjects({buffer_se_out}, CL_MIGRATE_MEM_OBJECT_HOST));
    OCL_CHECK(err, q.finish());

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
    for (int n = 0; n < BATCH_SIZE; n++)
    {
        for (int c = 0; c < CHANNEL_OUT; c++)
        {
            for (int h = 0; h < HEIGHT_OUT; h++)
            {
                for (int w = 0; w < WIDTH_OUT; w++)
                {
                    if (w == WIDTH_OUT - 1)
                        cout << Out[n * CHANNEL_OUT * HEIGHT_OUT * WIDTH_OUT + c * HEIGHT_OUT * WIDTH_OUT + h * WIDTH_OUT + w] << endl;
                    else
                        cout << Out[n * CHANNEL_OUT * HEIGHT_OUT * WIDTH_OUT + c * HEIGHT_OUT * WIDTH_OUT + h * WIDTH_OUT + w] << " ";
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
    OCL_CHECK(err, err = q.enqueueUnmapMemObject(buffer_DataIn_1, In));
    OCL_CHECK(err, err = q.enqueueUnmapMemObject(buffer_DataIn_2, msp_norm));
    OCL_CHECK(err, err = q.enqueueUnmapMemObject(buffer_msp_out, msp_out));
    OCL_CHECK(err, err = q.enqueueUnmapMemObject(buffer_dw_conv_out, dw_conv_out));
    OCL_CHECK(err, err = q.enqueueUnmapMemObject(buffer_se_out, se_out));
    OCL_CHECK(err, err = q.enqueueUnmapMemObject(buffer_result, Out));
    OCL_CHECK(err, err = q.finish());

    cout << "HOST-Info: TEST " << (error_detected ? "FAILED" : "PASSED") << endl;
    cout << "HOST-Info: DONE" << endl
         << endl;

    return (error_detected ? EXIT_FAILURE : EXIT_SUCCESS);
}

/*
Result:


*/
