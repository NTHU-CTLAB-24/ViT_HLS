// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2022.1 (64-bit)
// Tool Version Limit: 2022.04
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// ==============================================================
#ifndef XKERNEL_ATTENTION_H
#define XKERNEL_ATTENTION_H

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
#include "xkernel_attention_hw.h"

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
} XKernel_attention_Config;
#endif

typedef struct {
    u64 Control_BaseAddress;
    u32 IsReady;
} XKernel_attention;

typedef u32 word_type;

/***************** Macros (Inline Functions) Definitions *********************/
#ifndef __linux__
#define XKernel_attention_WriteReg(BaseAddress, RegOffset, Data) \
    Xil_Out32((BaseAddress) + (RegOffset), (u32)(Data))
#define XKernel_attention_ReadReg(BaseAddress, RegOffset) \
    Xil_In32((BaseAddress) + (RegOffset))
#else
#define XKernel_attention_WriteReg(BaseAddress, RegOffset, Data) \
    *(volatile u32*)((BaseAddress) + (RegOffset)) = (u32)(Data)
#define XKernel_attention_ReadReg(BaseAddress, RegOffset) \
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
int XKernel_attention_Initialize(XKernel_attention *InstancePtr, u16 DeviceId);
XKernel_attention_Config* XKernel_attention_LookupConfig(u16 DeviceId);
int XKernel_attention_CfgInitialize(XKernel_attention *InstancePtr, XKernel_attention_Config *ConfigPtr);
#else
int XKernel_attention_Initialize(XKernel_attention *InstancePtr, const char* InstanceName);
int XKernel_attention_Release(XKernel_attention *InstancePtr);
#endif


void XKernel_attention_Set_buffer_DataIn_1(XKernel_attention *InstancePtr, u64 Data);
u64 XKernel_attention_Get_buffer_DataIn_1(XKernel_attention *InstancePtr);
void XKernel_attention_Set_afterNorm(XKernel_attention *InstancePtr, u64 Data);
u64 XKernel_attention_Get_afterNorm(XKernel_attention *InstancePtr);
void XKernel_attention_Set_norm1_mean(XKernel_attention *InstancePtr, u64 Data);
u64 XKernel_attention_Get_norm1_mean(XKernel_attention *InstancePtr);
void XKernel_attention_Set_norm1_var(XKernel_attention *InstancePtr, u64 Data);
u64 XKernel_attention_Get_norm1_var(XKernel_attention *InstancePtr);
void XKernel_attention_Set_norm1_weight(XKernel_attention *InstancePtr, u64 Data);
u64 XKernel_attention_Get_norm1_weight(XKernel_attention *InstancePtr);
void XKernel_attention_Set_norm1_bias(XKernel_attention *InstancePtr, u64 Data);
u64 XKernel_attention_Get_norm1_bias(XKernel_attention *InstancePtr);
void XKernel_attention_Set_afterPad(XKernel_attention *InstancePtr, u64 Data);
u64 XKernel_attention_Get_afterPad(XKernel_attention *InstancePtr);
void XKernel_attention_Set_afterRearrangeX(XKernel_attention *InstancePtr, u64 Data);
u64 XKernel_attention_Get_afterRearrangeX(XKernel_attention *InstancePtr);
void XKernel_attention_Set_afterPad1(XKernel_attention *InstancePtr, u64 Data);
u64 XKernel_attention_Get_afterPad1(XKernel_attention *InstancePtr);
void XKernel_attention_Set_afterConv1(XKernel_attention *InstancePtr, u64 Data);
u64 XKernel_attention_Get_afterConv1(XKernel_attention *InstancePtr);
void XKernel_attention_Set_kernel1(XKernel_attention *InstancePtr, u64 Data);
u64 XKernel_attention_Get_kernel1(XKernel_attention *InstancePtr);
void XKernel_attention_Set_bias1(XKernel_attention *InstancePtr, u64 Data);
u64 XKernel_attention_Get_bias1(XKernel_attention *InstancePtr);
void XKernel_attention_Set_in_qk(XKernel_attention *InstancePtr, u64 Data);
u64 XKernel_attention_Get_in_qk(XKernel_attention *InstancePtr);
void XKernel_attention_Set_in_q(XKernel_attention *InstancePtr, u64 Data);
u64 XKernel_attention_Get_in_q(XKernel_attention *InstancePtr);
void XKernel_attention_Set_in_k(XKernel_attention *InstancePtr, u64 Data);
u64 XKernel_attention_Get_in_k(XKernel_attention *InstancePtr);
void XKernel_attention_Set_afterQKMultiplication(XKernel_attention *InstancePtr, u64 Data);
u64 XKernel_attention_Get_afterQKMultiplication(XKernel_attention *InstancePtr);
void XKernel_attention_Set_afterSoftmax(XKernel_attention *InstancePtr, u64 Data);
u64 XKernel_attention_Get_afterSoftmax(XKernel_attention *InstancePtr);
void XKernel_attention_Set_afterRearrangeX2(XKernel_attention *InstancePtr, u64 Data);
u64 XKernel_attention_Get_afterRearrangeX2(XKernel_attention *InstancePtr);
void XKernel_attention_Set_afterQKXMultiplication(XKernel_attention *InstancePtr, u64 Data);
u64 XKernel_attention_Get_afterQKXMultiplication(XKernel_attention *InstancePtr);
void XKernel_attention_Set_afterRearrangeQKX(XKernel_attention *InstancePtr, u64 Data);
u64 XKernel_attention_Get_afterRearrangeQKX(XKernel_attention *InstancePtr);
void XKernel_attention_Set_afterPad2(XKernel_attention *InstancePtr, u64 Data);
u64 XKernel_attention_Get_afterPad2(XKernel_attention *InstancePtr);
void XKernel_attention_Set_afterConv2(XKernel_attention *InstancePtr, u64 Data);
u64 XKernel_attention_Get_afterConv2(XKernel_attention *InstancePtr);
void XKernel_attention_Set_kernel2(XKernel_attention *InstancePtr, u64 Data);
u64 XKernel_attention_Get_kernel2(XKernel_attention *InstancePtr);
void XKernel_attention_Set_bias2(XKernel_attention *InstancePtr, u64 Data);
u64 XKernel_attention_Get_bias2(XKernel_attention *InstancePtr);
void XKernel_attention_Set_afterAct2(XKernel_attention *InstancePtr, u64 Data);
u64 XKernel_attention_Get_afterAct2(XKernel_attention *InstancePtr);
void XKernel_attention_Set_QKV(XKernel_attention *InstancePtr, u64 Data);
u64 XKernel_attention_Get_QKV(XKernel_attention *InstancePtr);
void XKernel_attention_Set_buffer_out(XKernel_attention *InstancePtr, u64 Data);
u64 XKernel_attention_Get_buffer_out(XKernel_attention *InstancePtr);
void XKernel_attention_Set_buffer_result(XKernel_attention *InstancePtr, u64 Data);
u64 XKernel_attention_Get_buffer_result(XKernel_attention *InstancePtr);

#ifdef __cplusplus
}
#endif

#endif
