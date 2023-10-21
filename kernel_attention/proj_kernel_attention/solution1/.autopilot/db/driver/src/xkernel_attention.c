// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2022.1 (64-bit)
// Tool Version Limit: 2022.04
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// ==============================================================
/***************************** Include Files *********************************/
#include "xkernel_attention.h"

/************************** Function Implementation *************************/
#ifndef __linux__
int XKernel_attention_CfgInitialize(XKernel_attention *InstancePtr, XKernel_attention_Config *ConfigPtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(ConfigPtr != NULL);

    InstancePtr->Control_BaseAddress = ConfigPtr->Control_BaseAddress;
    InstancePtr->IsReady = XIL_COMPONENT_IS_READY;

    return XST_SUCCESS;
}
#endif

void XKernel_attention_Set_buffer_DataIn_1(XKernel_attention *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XKernel_attention_WriteReg(InstancePtr->Control_BaseAddress, XKERNEL_ATTENTION_CONTROL_ADDR_BUFFER_DATAIN_1_DATA, (u32)(Data));
    XKernel_attention_WriteReg(InstancePtr->Control_BaseAddress, XKERNEL_ATTENTION_CONTROL_ADDR_BUFFER_DATAIN_1_DATA + 4, (u32)(Data >> 32));
}

u64 XKernel_attention_Get_buffer_DataIn_1(XKernel_attention *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XKernel_attention_ReadReg(InstancePtr->Control_BaseAddress, XKERNEL_ATTENTION_CONTROL_ADDR_BUFFER_DATAIN_1_DATA);
    Data += (u64)XKernel_attention_ReadReg(InstancePtr->Control_BaseAddress, XKERNEL_ATTENTION_CONTROL_ADDR_BUFFER_DATAIN_1_DATA + 4) << 32;
    return Data;
}

void XKernel_attention_Set_afterNorm(XKernel_attention *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XKernel_attention_WriteReg(InstancePtr->Control_BaseAddress, XKERNEL_ATTENTION_CONTROL_ADDR_AFTERNORM_DATA, (u32)(Data));
    XKernel_attention_WriteReg(InstancePtr->Control_BaseAddress, XKERNEL_ATTENTION_CONTROL_ADDR_AFTERNORM_DATA + 4, (u32)(Data >> 32));
}

u64 XKernel_attention_Get_afterNorm(XKernel_attention *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XKernel_attention_ReadReg(InstancePtr->Control_BaseAddress, XKERNEL_ATTENTION_CONTROL_ADDR_AFTERNORM_DATA);
    Data += (u64)XKernel_attention_ReadReg(InstancePtr->Control_BaseAddress, XKERNEL_ATTENTION_CONTROL_ADDR_AFTERNORM_DATA + 4) << 32;
    return Data;
}

void XKernel_attention_Set_norm1_mean(XKernel_attention *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XKernel_attention_WriteReg(InstancePtr->Control_BaseAddress, XKERNEL_ATTENTION_CONTROL_ADDR_NORM1_MEAN_DATA, (u32)(Data));
    XKernel_attention_WriteReg(InstancePtr->Control_BaseAddress, XKERNEL_ATTENTION_CONTROL_ADDR_NORM1_MEAN_DATA + 4, (u32)(Data >> 32));
}

u64 XKernel_attention_Get_norm1_mean(XKernel_attention *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XKernel_attention_ReadReg(InstancePtr->Control_BaseAddress, XKERNEL_ATTENTION_CONTROL_ADDR_NORM1_MEAN_DATA);
    Data += (u64)XKernel_attention_ReadReg(InstancePtr->Control_BaseAddress, XKERNEL_ATTENTION_CONTROL_ADDR_NORM1_MEAN_DATA + 4) << 32;
    return Data;
}

void XKernel_attention_Set_norm1_var(XKernel_attention *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XKernel_attention_WriteReg(InstancePtr->Control_BaseAddress, XKERNEL_ATTENTION_CONTROL_ADDR_NORM1_VAR_DATA, (u32)(Data));
    XKernel_attention_WriteReg(InstancePtr->Control_BaseAddress, XKERNEL_ATTENTION_CONTROL_ADDR_NORM1_VAR_DATA + 4, (u32)(Data >> 32));
}

u64 XKernel_attention_Get_norm1_var(XKernel_attention *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XKernel_attention_ReadReg(InstancePtr->Control_BaseAddress, XKERNEL_ATTENTION_CONTROL_ADDR_NORM1_VAR_DATA);
    Data += (u64)XKernel_attention_ReadReg(InstancePtr->Control_BaseAddress, XKERNEL_ATTENTION_CONTROL_ADDR_NORM1_VAR_DATA + 4) << 32;
    return Data;
}

void XKernel_attention_Set_norm1_weight(XKernel_attention *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XKernel_attention_WriteReg(InstancePtr->Control_BaseAddress, XKERNEL_ATTENTION_CONTROL_ADDR_NORM1_WEIGHT_DATA, (u32)(Data));
    XKernel_attention_WriteReg(InstancePtr->Control_BaseAddress, XKERNEL_ATTENTION_CONTROL_ADDR_NORM1_WEIGHT_DATA + 4, (u32)(Data >> 32));
}

u64 XKernel_attention_Get_norm1_weight(XKernel_attention *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XKernel_attention_ReadReg(InstancePtr->Control_BaseAddress, XKERNEL_ATTENTION_CONTROL_ADDR_NORM1_WEIGHT_DATA);
    Data += (u64)XKernel_attention_ReadReg(InstancePtr->Control_BaseAddress, XKERNEL_ATTENTION_CONTROL_ADDR_NORM1_WEIGHT_DATA + 4) << 32;
    return Data;
}

void XKernel_attention_Set_norm1_bias(XKernel_attention *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XKernel_attention_WriteReg(InstancePtr->Control_BaseAddress, XKERNEL_ATTENTION_CONTROL_ADDR_NORM1_BIAS_DATA, (u32)(Data));
    XKernel_attention_WriteReg(InstancePtr->Control_BaseAddress, XKERNEL_ATTENTION_CONTROL_ADDR_NORM1_BIAS_DATA + 4, (u32)(Data >> 32));
}

u64 XKernel_attention_Get_norm1_bias(XKernel_attention *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XKernel_attention_ReadReg(InstancePtr->Control_BaseAddress, XKERNEL_ATTENTION_CONTROL_ADDR_NORM1_BIAS_DATA);
    Data += (u64)XKernel_attention_ReadReg(InstancePtr->Control_BaseAddress, XKERNEL_ATTENTION_CONTROL_ADDR_NORM1_BIAS_DATA + 4) << 32;
    return Data;
}

void XKernel_attention_Set_afterPad(XKernel_attention *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XKernel_attention_WriteReg(InstancePtr->Control_BaseAddress, XKERNEL_ATTENTION_CONTROL_ADDR_AFTERPAD_DATA, (u32)(Data));
    XKernel_attention_WriteReg(InstancePtr->Control_BaseAddress, XKERNEL_ATTENTION_CONTROL_ADDR_AFTERPAD_DATA + 4, (u32)(Data >> 32));
}

u64 XKernel_attention_Get_afterPad(XKernel_attention *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XKernel_attention_ReadReg(InstancePtr->Control_BaseAddress, XKERNEL_ATTENTION_CONTROL_ADDR_AFTERPAD_DATA);
    Data += (u64)XKernel_attention_ReadReg(InstancePtr->Control_BaseAddress, XKERNEL_ATTENTION_CONTROL_ADDR_AFTERPAD_DATA + 4) << 32;
    return Data;
}

void XKernel_attention_Set_afterRearrangeX(XKernel_attention *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XKernel_attention_WriteReg(InstancePtr->Control_BaseAddress, XKERNEL_ATTENTION_CONTROL_ADDR_AFTERREARRANGEX_DATA, (u32)(Data));
    XKernel_attention_WriteReg(InstancePtr->Control_BaseAddress, XKERNEL_ATTENTION_CONTROL_ADDR_AFTERREARRANGEX_DATA + 4, (u32)(Data >> 32));
}

u64 XKernel_attention_Get_afterRearrangeX(XKernel_attention *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XKernel_attention_ReadReg(InstancePtr->Control_BaseAddress, XKERNEL_ATTENTION_CONTROL_ADDR_AFTERREARRANGEX_DATA);
    Data += (u64)XKernel_attention_ReadReg(InstancePtr->Control_BaseAddress, XKERNEL_ATTENTION_CONTROL_ADDR_AFTERREARRANGEX_DATA + 4) << 32;
    return Data;
}

void XKernel_attention_Set_afterPad1(XKernel_attention *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XKernel_attention_WriteReg(InstancePtr->Control_BaseAddress, XKERNEL_ATTENTION_CONTROL_ADDR_AFTERPAD1_DATA, (u32)(Data));
    XKernel_attention_WriteReg(InstancePtr->Control_BaseAddress, XKERNEL_ATTENTION_CONTROL_ADDR_AFTERPAD1_DATA + 4, (u32)(Data >> 32));
}

u64 XKernel_attention_Get_afterPad1(XKernel_attention *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XKernel_attention_ReadReg(InstancePtr->Control_BaseAddress, XKERNEL_ATTENTION_CONTROL_ADDR_AFTERPAD1_DATA);
    Data += (u64)XKernel_attention_ReadReg(InstancePtr->Control_BaseAddress, XKERNEL_ATTENTION_CONTROL_ADDR_AFTERPAD1_DATA + 4) << 32;
    return Data;
}

void XKernel_attention_Set_afterConv1(XKernel_attention *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XKernel_attention_WriteReg(InstancePtr->Control_BaseAddress, XKERNEL_ATTENTION_CONTROL_ADDR_AFTERCONV1_DATA, (u32)(Data));
    XKernel_attention_WriteReg(InstancePtr->Control_BaseAddress, XKERNEL_ATTENTION_CONTROL_ADDR_AFTERCONV1_DATA + 4, (u32)(Data >> 32));
}

u64 XKernel_attention_Get_afterConv1(XKernel_attention *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XKernel_attention_ReadReg(InstancePtr->Control_BaseAddress, XKERNEL_ATTENTION_CONTROL_ADDR_AFTERCONV1_DATA);
    Data += (u64)XKernel_attention_ReadReg(InstancePtr->Control_BaseAddress, XKERNEL_ATTENTION_CONTROL_ADDR_AFTERCONV1_DATA + 4) << 32;
    return Data;
}

void XKernel_attention_Set_kernel1(XKernel_attention *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XKernel_attention_WriteReg(InstancePtr->Control_BaseAddress, XKERNEL_ATTENTION_CONTROL_ADDR_KERNEL1_DATA, (u32)(Data));
    XKernel_attention_WriteReg(InstancePtr->Control_BaseAddress, XKERNEL_ATTENTION_CONTROL_ADDR_KERNEL1_DATA + 4, (u32)(Data >> 32));
}

u64 XKernel_attention_Get_kernel1(XKernel_attention *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XKernel_attention_ReadReg(InstancePtr->Control_BaseAddress, XKERNEL_ATTENTION_CONTROL_ADDR_KERNEL1_DATA);
    Data += (u64)XKernel_attention_ReadReg(InstancePtr->Control_BaseAddress, XKERNEL_ATTENTION_CONTROL_ADDR_KERNEL1_DATA + 4) << 32;
    return Data;
}

void XKernel_attention_Set_bias1(XKernel_attention *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XKernel_attention_WriteReg(InstancePtr->Control_BaseAddress, XKERNEL_ATTENTION_CONTROL_ADDR_BIAS1_DATA, (u32)(Data));
    XKernel_attention_WriteReg(InstancePtr->Control_BaseAddress, XKERNEL_ATTENTION_CONTROL_ADDR_BIAS1_DATA + 4, (u32)(Data >> 32));
}

u64 XKernel_attention_Get_bias1(XKernel_attention *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XKernel_attention_ReadReg(InstancePtr->Control_BaseAddress, XKERNEL_ATTENTION_CONTROL_ADDR_BIAS1_DATA);
    Data += (u64)XKernel_attention_ReadReg(InstancePtr->Control_BaseAddress, XKERNEL_ATTENTION_CONTROL_ADDR_BIAS1_DATA + 4) << 32;
    return Data;
}

void XKernel_attention_Set_in_qk(XKernel_attention *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XKernel_attention_WriteReg(InstancePtr->Control_BaseAddress, XKERNEL_ATTENTION_CONTROL_ADDR_IN_QK_DATA, (u32)(Data));
    XKernel_attention_WriteReg(InstancePtr->Control_BaseAddress, XKERNEL_ATTENTION_CONTROL_ADDR_IN_QK_DATA + 4, (u32)(Data >> 32));
}

u64 XKernel_attention_Get_in_qk(XKernel_attention *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XKernel_attention_ReadReg(InstancePtr->Control_BaseAddress, XKERNEL_ATTENTION_CONTROL_ADDR_IN_QK_DATA);
    Data += (u64)XKernel_attention_ReadReg(InstancePtr->Control_BaseAddress, XKERNEL_ATTENTION_CONTROL_ADDR_IN_QK_DATA + 4) << 32;
    return Data;
}

void XKernel_attention_Set_in_q(XKernel_attention *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XKernel_attention_WriteReg(InstancePtr->Control_BaseAddress, XKERNEL_ATTENTION_CONTROL_ADDR_IN_Q_DATA, (u32)(Data));
    XKernel_attention_WriteReg(InstancePtr->Control_BaseAddress, XKERNEL_ATTENTION_CONTROL_ADDR_IN_Q_DATA + 4, (u32)(Data >> 32));
}

u64 XKernel_attention_Get_in_q(XKernel_attention *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XKernel_attention_ReadReg(InstancePtr->Control_BaseAddress, XKERNEL_ATTENTION_CONTROL_ADDR_IN_Q_DATA);
    Data += (u64)XKernel_attention_ReadReg(InstancePtr->Control_BaseAddress, XKERNEL_ATTENTION_CONTROL_ADDR_IN_Q_DATA + 4) << 32;
    return Data;
}

void XKernel_attention_Set_in_k(XKernel_attention *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XKernel_attention_WriteReg(InstancePtr->Control_BaseAddress, XKERNEL_ATTENTION_CONTROL_ADDR_IN_K_DATA, (u32)(Data));
    XKernel_attention_WriteReg(InstancePtr->Control_BaseAddress, XKERNEL_ATTENTION_CONTROL_ADDR_IN_K_DATA + 4, (u32)(Data >> 32));
}

u64 XKernel_attention_Get_in_k(XKernel_attention *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XKernel_attention_ReadReg(InstancePtr->Control_BaseAddress, XKERNEL_ATTENTION_CONTROL_ADDR_IN_K_DATA);
    Data += (u64)XKernel_attention_ReadReg(InstancePtr->Control_BaseAddress, XKERNEL_ATTENTION_CONTROL_ADDR_IN_K_DATA + 4) << 32;
    return Data;
}

void XKernel_attention_Set_afterQKMultiplication(XKernel_attention *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XKernel_attention_WriteReg(InstancePtr->Control_BaseAddress, XKERNEL_ATTENTION_CONTROL_ADDR_AFTERQKMULTIPLICATION_DATA, (u32)(Data));
    XKernel_attention_WriteReg(InstancePtr->Control_BaseAddress, XKERNEL_ATTENTION_CONTROL_ADDR_AFTERQKMULTIPLICATION_DATA + 4, (u32)(Data >> 32));
}

u64 XKernel_attention_Get_afterQKMultiplication(XKernel_attention *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XKernel_attention_ReadReg(InstancePtr->Control_BaseAddress, XKERNEL_ATTENTION_CONTROL_ADDR_AFTERQKMULTIPLICATION_DATA);
    Data += (u64)XKernel_attention_ReadReg(InstancePtr->Control_BaseAddress, XKERNEL_ATTENTION_CONTROL_ADDR_AFTERQKMULTIPLICATION_DATA + 4) << 32;
    return Data;
}

void XKernel_attention_Set_afterSoftmax(XKernel_attention *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XKernel_attention_WriteReg(InstancePtr->Control_BaseAddress, XKERNEL_ATTENTION_CONTROL_ADDR_AFTERSOFTMAX_DATA, (u32)(Data));
    XKernel_attention_WriteReg(InstancePtr->Control_BaseAddress, XKERNEL_ATTENTION_CONTROL_ADDR_AFTERSOFTMAX_DATA + 4, (u32)(Data >> 32));
}

u64 XKernel_attention_Get_afterSoftmax(XKernel_attention *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XKernel_attention_ReadReg(InstancePtr->Control_BaseAddress, XKERNEL_ATTENTION_CONTROL_ADDR_AFTERSOFTMAX_DATA);
    Data += (u64)XKernel_attention_ReadReg(InstancePtr->Control_BaseAddress, XKERNEL_ATTENTION_CONTROL_ADDR_AFTERSOFTMAX_DATA + 4) << 32;
    return Data;
}

void XKernel_attention_Set_afterRearrangeX2(XKernel_attention *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XKernel_attention_WriteReg(InstancePtr->Control_BaseAddress, XKERNEL_ATTENTION_CONTROL_ADDR_AFTERREARRANGEX2_DATA, (u32)(Data));
    XKernel_attention_WriteReg(InstancePtr->Control_BaseAddress, XKERNEL_ATTENTION_CONTROL_ADDR_AFTERREARRANGEX2_DATA + 4, (u32)(Data >> 32));
}

u64 XKernel_attention_Get_afterRearrangeX2(XKernel_attention *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XKernel_attention_ReadReg(InstancePtr->Control_BaseAddress, XKERNEL_ATTENTION_CONTROL_ADDR_AFTERREARRANGEX2_DATA);
    Data += (u64)XKernel_attention_ReadReg(InstancePtr->Control_BaseAddress, XKERNEL_ATTENTION_CONTROL_ADDR_AFTERREARRANGEX2_DATA + 4) << 32;
    return Data;
}

void XKernel_attention_Set_afterQKXMultiplication(XKernel_attention *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XKernel_attention_WriteReg(InstancePtr->Control_BaseAddress, XKERNEL_ATTENTION_CONTROL_ADDR_AFTERQKXMULTIPLICATION_DATA, (u32)(Data));
    XKernel_attention_WriteReg(InstancePtr->Control_BaseAddress, XKERNEL_ATTENTION_CONTROL_ADDR_AFTERQKXMULTIPLICATION_DATA + 4, (u32)(Data >> 32));
}

u64 XKernel_attention_Get_afterQKXMultiplication(XKernel_attention *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XKernel_attention_ReadReg(InstancePtr->Control_BaseAddress, XKERNEL_ATTENTION_CONTROL_ADDR_AFTERQKXMULTIPLICATION_DATA);
    Data += (u64)XKernel_attention_ReadReg(InstancePtr->Control_BaseAddress, XKERNEL_ATTENTION_CONTROL_ADDR_AFTERQKXMULTIPLICATION_DATA + 4) << 32;
    return Data;
}

void XKernel_attention_Set_afterRearrangeQKX(XKernel_attention *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XKernel_attention_WriteReg(InstancePtr->Control_BaseAddress, XKERNEL_ATTENTION_CONTROL_ADDR_AFTERREARRANGEQKX_DATA, (u32)(Data));
    XKernel_attention_WriteReg(InstancePtr->Control_BaseAddress, XKERNEL_ATTENTION_CONTROL_ADDR_AFTERREARRANGEQKX_DATA + 4, (u32)(Data >> 32));
}

u64 XKernel_attention_Get_afterRearrangeQKX(XKernel_attention *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XKernel_attention_ReadReg(InstancePtr->Control_BaseAddress, XKERNEL_ATTENTION_CONTROL_ADDR_AFTERREARRANGEQKX_DATA);
    Data += (u64)XKernel_attention_ReadReg(InstancePtr->Control_BaseAddress, XKERNEL_ATTENTION_CONTROL_ADDR_AFTERREARRANGEQKX_DATA + 4) << 32;
    return Data;
}

void XKernel_attention_Set_afterPad2(XKernel_attention *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XKernel_attention_WriteReg(InstancePtr->Control_BaseAddress, XKERNEL_ATTENTION_CONTROL_ADDR_AFTERPAD2_DATA, (u32)(Data));
    XKernel_attention_WriteReg(InstancePtr->Control_BaseAddress, XKERNEL_ATTENTION_CONTROL_ADDR_AFTERPAD2_DATA + 4, (u32)(Data >> 32));
}

u64 XKernel_attention_Get_afterPad2(XKernel_attention *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XKernel_attention_ReadReg(InstancePtr->Control_BaseAddress, XKERNEL_ATTENTION_CONTROL_ADDR_AFTERPAD2_DATA);
    Data += (u64)XKernel_attention_ReadReg(InstancePtr->Control_BaseAddress, XKERNEL_ATTENTION_CONTROL_ADDR_AFTERPAD2_DATA + 4) << 32;
    return Data;
}

void XKernel_attention_Set_afterConv2(XKernel_attention *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XKernel_attention_WriteReg(InstancePtr->Control_BaseAddress, XKERNEL_ATTENTION_CONTROL_ADDR_AFTERCONV2_DATA, (u32)(Data));
    XKernel_attention_WriteReg(InstancePtr->Control_BaseAddress, XKERNEL_ATTENTION_CONTROL_ADDR_AFTERCONV2_DATA + 4, (u32)(Data >> 32));
}

u64 XKernel_attention_Get_afterConv2(XKernel_attention *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XKernel_attention_ReadReg(InstancePtr->Control_BaseAddress, XKERNEL_ATTENTION_CONTROL_ADDR_AFTERCONV2_DATA);
    Data += (u64)XKernel_attention_ReadReg(InstancePtr->Control_BaseAddress, XKERNEL_ATTENTION_CONTROL_ADDR_AFTERCONV2_DATA + 4) << 32;
    return Data;
}

void XKernel_attention_Set_kernel2(XKernel_attention *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XKernel_attention_WriteReg(InstancePtr->Control_BaseAddress, XKERNEL_ATTENTION_CONTROL_ADDR_KERNEL2_DATA, (u32)(Data));
    XKernel_attention_WriteReg(InstancePtr->Control_BaseAddress, XKERNEL_ATTENTION_CONTROL_ADDR_KERNEL2_DATA + 4, (u32)(Data >> 32));
}

u64 XKernel_attention_Get_kernel2(XKernel_attention *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XKernel_attention_ReadReg(InstancePtr->Control_BaseAddress, XKERNEL_ATTENTION_CONTROL_ADDR_KERNEL2_DATA);
    Data += (u64)XKernel_attention_ReadReg(InstancePtr->Control_BaseAddress, XKERNEL_ATTENTION_CONTROL_ADDR_KERNEL2_DATA + 4) << 32;
    return Data;
}

void XKernel_attention_Set_bias2(XKernel_attention *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XKernel_attention_WriteReg(InstancePtr->Control_BaseAddress, XKERNEL_ATTENTION_CONTROL_ADDR_BIAS2_DATA, (u32)(Data));
    XKernel_attention_WriteReg(InstancePtr->Control_BaseAddress, XKERNEL_ATTENTION_CONTROL_ADDR_BIAS2_DATA + 4, (u32)(Data >> 32));
}

u64 XKernel_attention_Get_bias2(XKernel_attention *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XKernel_attention_ReadReg(InstancePtr->Control_BaseAddress, XKERNEL_ATTENTION_CONTROL_ADDR_BIAS2_DATA);
    Data += (u64)XKernel_attention_ReadReg(InstancePtr->Control_BaseAddress, XKERNEL_ATTENTION_CONTROL_ADDR_BIAS2_DATA + 4) << 32;
    return Data;
}

void XKernel_attention_Set_afterAct2(XKernel_attention *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XKernel_attention_WriteReg(InstancePtr->Control_BaseAddress, XKERNEL_ATTENTION_CONTROL_ADDR_AFTERACT2_DATA, (u32)(Data));
    XKernel_attention_WriteReg(InstancePtr->Control_BaseAddress, XKERNEL_ATTENTION_CONTROL_ADDR_AFTERACT2_DATA + 4, (u32)(Data >> 32));
}

u64 XKernel_attention_Get_afterAct2(XKernel_attention *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XKernel_attention_ReadReg(InstancePtr->Control_BaseAddress, XKERNEL_ATTENTION_CONTROL_ADDR_AFTERACT2_DATA);
    Data += (u64)XKernel_attention_ReadReg(InstancePtr->Control_BaseAddress, XKERNEL_ATTENTION_CONTROL_ADDR_AFTERACT2_DATA + 4) << 32;
    return Data;
}

void XKernel_attention_Set_QKV(XKernel_attention *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XKernel_attention_WriteReg(InstancePtr->Control_BaseAddress, XKERNEL_ATTENTION_CONTROL_ADDR_QKV_DATA, (u32)(Data));
    XKernel_attention_WriteReg(InstancePtr->Control_BaseAddress, XKERNEL_ATTENTION_CONTROL_ADDR_QKV_DATA + 4, (u32)(Data >> 32));
}

u64 XKernel_attention_Get_QKV(XKernel_attention *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XKernel_attention_ReadReg(InstancePtr->Control_BaseAddress, XKERNEL_ATTENTION_CONTROL_ADDR_QKV_DATA);
    Data += (u64)XKernel_attention_ReadReg(InstancePtr->Control_BaseAddress, XKERNEL_ATTENTION_CONTROL_ADDR_QKV_DATA + 4) << 32;
    return Data;
}

void XKernel_attention_Set_buffer_out(XKernel_attention *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XKernel_attention_WriteReg(InstancePtr->Control_BaseAddress, XKERNEL_ATTENTION_CONTROL_ADDR_BUFFER_OUT_DATA, (u32)(Data));
    XKernel_attention_WriteReg(InstancePtr->Control_BaseAddress, XKERNEL_ATTENTION_CONTROL_ADDR_BUFFER_OUT_DATA + 4, (u32)(Data >> 32));
}

u64 XKernel_attention_Get_buffer_out(XKernel_attention *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XKernel_attention_ReadReg(InstancePtr->Control_BaseAddress, XKERNEL_ATTENTION_CONTROL_ADDR_BUFFER_OUT_DATA);
    Data += (u64)XKernel_attention_ReadReg(InstancePtr->Control_BaseAddress, XKERNEL_ATTENTION_CONTROL_ADDR_BUFFER_OUT_DATA + 4) << 32;
    return Data;
}

void XKernel_attention_Set_buffer_result(XKernel_attention *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XKernel_attention_WriteReg(InstancePtr->Control_BaseAddress, XKERNEL_ATTENTION_CONTROL_ADDR_BUFFER_RESULT_DATA, (u32)(Data));
    XKernel_attention_WriteReg(InstancePtr->Control_BaseAddress, XKERNEL_ATTENTION_CONTROL_ADDR_BUFFER_RESULT_DATA + 4, (u32)(Data >> 32));
}

u64 XKernel_attention_Get_buffer_result(XKernel_attention *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XKernel_attention_ReadReg(InstancePtr->Control_BaseAddress, XKERNEL_ATTENTION_CONTROL_ADDR_BUFFER_RESULT_DATA);
    Data += (u64)XKernel_attention_ReadReg(InstancePtr->Control_BaseAddress, XKERNEL_ATTENTION_CONTROL_ADDR_BUFFER_RESULT_DATA + 4) << 32;
    return Data;
}

