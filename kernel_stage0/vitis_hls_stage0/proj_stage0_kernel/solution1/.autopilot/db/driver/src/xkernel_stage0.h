// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2022.1 (64-bit)
// Tool Version Limit: 2022.04
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// ==============================================================
#ifndef XKERNEL_STAGE0_H
#define XKERNEL_STAGE0_H

#ifdef __cplusplus
extern "C" {
#endif

/***************************** Include Files *********************************/
#ifndef __linux__
#include "xil_types.h"
#include "xil_assert.h"
#include "xstatus.h"
#include "xil_io.h"
#else
#include <stdint.h>
#include <assert.h>
#include <dirent.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stddef.h>
#endif
#include "xkernel_stage0_hw.h"

/**************************** Type Definitions ******************************/
#ifdef __linux__
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
#else
typedef struct {
    u16 DeviceId;
    u64 Control_BaseAddress;
} XKernel_stage0_Config;
#endif

typedef struct {
    u64 Control_BaseAddress;
    u32 IsReady;
} XKernel_stage0;

typedef u32 word_type;

/***************** Macros (Inline Functions) Definitions *********************/
#ifndef __linux__
#define XKernel_stage0_WriteReg(BaseAddress, RegOffset, Data) \
    Xil_Out32((BaseAddress) + (RegOffset), (u32)(Data))
#define XKernel_stage0_ReadReg(BaseAddress, RegOffset) \
    Xil_In32((BaseAddress) + (RegOffset))
#else
#define XKernel_stage0_WriteReg(BaseAddress, RegOffset, Data) \
    *(volatile u32*)((BaseAddress) + (RegOffset)) = (u32)(Data)
#define XKernel_stage0_ReadReg(BaseAddress, RegOffset) \
    *(volatile u32*)((BaseAddress) + (RegOffset))

#define Xil_AssertVoid(expr)    assert(expr)
#define Xil_AssertNonvoid(expr) assert(expr)

#define XST_SUCCESS             0
#define XST_DEVICE_NOT_FOUND    2
#define XST_OPEN_DEVICE_FAILED  3
#define XIL_COMPONENT_IS_READY  1
#endif

/************************** Function Prototypes *****************************/
#ifndef __linux__
int XKernel_stage0_Initialize(XKernel_stage0 *InstancePtr, u16 DeviceId);
XKernel_stage0_Config* XKernel_stage0_LookupConfig(u16 DeviceId);
int XKernel_stage0_CfgInitialize(XKernel_stage0 *InstancePtr, XKernel_stage0_Config *ConfigPtr);
#else
int XKernel_stage0_Initialize(XKernel_stage0 *InstancePtr, const char* InstanceName);
int XKernel_stage0_Release(XKernel_stage0 *InstancePtr);
#endif


void XKernel_stage0_Set_X_data(XKernel_stage0 *InstancePtr, u64 Data);
u64 XKernel_stage0_Get_X_data(XKernel_stage0 *InstancePtr);
void XKernel_stage0_Set_msp_conv_weight(XKernel_stage0 *InstancePtr, u64 Data);
u64 XKernel_stage0_Get_msp_conv_weight(XKernel_stage0 *InstancePtr);
void XKernel_stage0_Set_msp_conv_bias(XKernel_stage0 *InstancePtr, u64 Data);
u64 XKernel_stage0_Get_msp_conv_bias(XKernel_stage0 *InstancePtr);
void XKernel_stage0_Set_msp_norm_weight(XKernel_stage0 *InstancePtr, u64 Data);
u64 XKernel_stage0_Get_msp_norm_weight(XKernel_stage0 *InstancePtr);
void XKernel_stage0_Set_msp_norm_bias(XKernel_stage0 *InstancePtr, u64 Data);
u64 XKernel_stage0_Get_msp_norm_bias(XKernel_stage0 *InstancePtr);
void XKernel_stage0_Set_msp_norm_running_mean(XKernel_stage0 *InstancePtr, u64 Data);
u64 XKernel_stage0_Get_msp_norm_running_mean(XKernel_stage0 *InstancePtr);
void XKernel_stage0_Set_msp_norm_running_var(XKernel_stage0 *InstancePtr, u64 Data);
u64 XKernel_stage0_Get_msp_norm_running_var(XKernel_stage0 *InstancePtr);
void XKernel_stage0_Set_dw_conv_weight(XKernel_stage0 *InstancePtr, u64 Data);
u64 XKernel_stage0_Get_dw_conv_weight(XKernel_stage0 *InstancePtr);
void XKernel_stage0_Set_norm_1_weight(XKernel_stage0 *InstancePtr, u64 Data);
u64 XKernel_stage0_Get_norm_1_weight(XKernel_stage0 *InstancePtr);
void XKernel_stage0_Set_norm_1_bias(XKernel_stage0 *InstancePtr, u64 Data);
u64 XKernel_stage0_Get_norm_1_bias(XKernel_stage0 *InstancePtr);
void XKernel_stage0_Set_norm_1_running_mean(XKernel_stage0 *InstancePtr, u64 Data);
u64 XKernel_stage0_Get_norm_1_running_mean(XKernel_stage0 *InstancePtr);
void XKernel_stage0_Set_norm_1_running_var(XKernel_stage0 *InstancePtr, u64 Data);
u64 XKernel_stage0_Get_norm_1_running_var(XKernel_stage0 *InstancePtr);
void XKernel_stage0_Set_se_conv_reduce_weight(XKernel_stage0 *InstancePtr, u64 Data);
u64 XKernel_stage0_Get_se_conv_reduce_weight(XKernel_stage0 *InstancePtr);
void XKernel_stage0_Set_se_conv_reduce_bias(XKernel_stage0 *InstancePtr, u64 Data);
u64 XKernel_stage0_Get_se_conv_reduce_bias(XKernel_stage0 *InstancePtr);
void XKernel_stage0_Set_se_conv_expand_weight(XKernel_stage0 *InstancePtr, u64 Data);
u64 XKernel_stage0_Get_se_conv_expand_weight(XKernel_stage0 *InstancePtr);
void XKernel_stage0_Set_se_conv_expand_bias(XKernel_stage0 *InstancePtr, u64 Data);
u64 XKernel_stage0_Get_se_conv_expand_bias(XKernel_stage0 *InstancePtr);
void XKernel_stage0_Set_proj_conv_weight(XKernel_stage0 *InstancePtr, u64 Data);
u64 XKernel_stage0_Get_proj_conv_weight(XKernel_stage0 *InstancePtr);
void XKernel_stage0_Set_Y_msp_conv(XKernel_stage0 *InstancePtr, u64 Data);
u64 XKernel_stage0_Get_Y_msp_conv(XKernel_stage0 *InstancePtr);
void XKernel_stage0_Set_Y_msp_norm(XKernel_stage0 *InstancePtr, u64 Data);
u64 XKernel_stage0_Get_Y_msp_norm(XKernel_stage0 *InstancePtr);
void XKernel_stage0_Set_Y_dw_conv(XKernel_stage0 *InstancePtr, u64 Data);
u64 XKernel_stage0_Get_Y_dw_conv(XKernel_stage0 *InstancePtr);
void XKernel_stage0_Set_Y_dw_norm(XKernel_stage0 *InstancePtr, u64 Data);
u64 XKernel_stage0_Get_Y_dw_norm(XKernel_stage0 *InstancePtr);
void XKernel_stage0_Set_Y_dw_act(XKernel_stage0 *InstancePtr, u64 Data);
u64 XKernel_stage0_Get_Y_dw_act(XKernel_stage0 *InstancePtr);
void XKernel_stage0_Set_Y_mean(XKernel_stage0 *InstancePtr, u64 Data);
u64 XKernel_stage0_Get_Y_mean(XKernel_stage0 *InstancePtr);
void XKernel_stage0_Set_Y_reduce(XKernel_stage0 *InstancePtr, u64 Data);
u64 XKernel_stage0_Get_Y_reduce(XKernel_stage0 *InstancePtr);
void XKernel_stage0_Set_Y_relu(XKernel_stage0 *InstancePtr, u64 Data);
u64 XKernel_stage0_Get_Y_relu(XKernel_stage0 *InstancePtr);
void XKernel_stage0_Set_Y_expand(XKernel_stage0 *InstancePtr, u64 Data);
u64 XKernel_stage0_Get_Y_expand(XKernel_stage0 *InstancePtr);
void XKernel_stage0_Set_Y_sigmoid(XKernel_stage0 *InstancePtr, u64 Data);
u64 XKernel_stage0_Get_Y_sigmoid(XKernel_stage0 *InstancePtr);
void XKernel_stage0_Set_Y_se(XKernel_stage0 *InstancePtr, u64 Data);
u64 XKernel_stage0_Get_Y_se(XKernel_stage0 *InstancePtr);
void XKernel_stage0_Set_Y_proj(XKernel_stage0 *InstancePtr, u64 Data);
u64 XKernel_stage0_Get_Y_proj(XKernel_stage0 *InstancePtr);

#ifdef __cplusplus
}
#endif

#endif
