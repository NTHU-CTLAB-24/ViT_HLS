// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2022.1 (64-bit)
// Tool Version Limit: 2022.04
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// ==============================================================
/***************************** Include Files *********************************/
#include "xkernel_stage0.h"

/************************** Function Implementation *************************/
#ifndef __linux__
int XKernel_stage0_CfgInitialize(XKernel_stage0 *InstancePtr, XKernel_stage0_Config *ConfigPtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(ConfigPtr != NULL);

    InstancePtr->Control_BaseAddress = ConfigPtr->Control_BaseAddress;
    InstancePtr->IsReady = XIL_COMPONENT_IS_READY;

    return XST_SUCCESS;
}
#endif

void XKernel_stage0_Set_X_data(XKernel_stage0 *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XKernel_stage0_WriteReg(InstancePtr->Control_BaseAddress, XKERNEL_STAGE0_CONTROL_ADDR_X_DATA_DATA, (u32)(Data));
    XKernel_stage0_WriteReg(InstancePtr->Control_BaseAddress, XKERNEL_STAGE0_CONTROL_ADDR_X_DATA_DATA + 4, (u32)(Data >> 32));
}

u64 XKernel_stage0_Get_X_data(XKernel_stage0 *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XKernel_stage0_ReadReg(InstancePtr->Control_BaseAddress, XKERNEL_STAGE0_CONTROL_ADDR_X_DATA_DATA);
    Data += (u64)XKernel_stage0_ReadReg(InstancePtr->Control_BaseAddress, XKERNEL_STAGE0_CONTROL_ADDR_X_DATA_DATA + 4) << 32;
    return Data;
}

void XKernel_stage0_Set_msp_conv_weight(XKernel_stage0 *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XKernel_stage0_WriteReg(InstancePtr->Control_BaseAddress, XKERNEL_STAGE0_CONTROL_ADDR_MSP_CONV_WEIGHT_DATA, (u32)(Data));
    XKernel_stage0_WriteReg(InstancePtr->Control_BaseAddress, XKERNEL_STAGE0_CONTROL_ADDR_MSP_CONV_WEIGHT_DATA + 4, (u32)(Data >> 32));
}

u64 XKernel_stage0_Get_msp_conv_weight(XKernel_stage0 *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XKernel_stage0_ReadReg(InstancePtr->Control_BaseAddress, XKERNEL_STAGE0_CONTROL_ADDR_MSP_CONV_WEIGHT_DATA);
    Data += (u64)XKernel_stage0_ReadReg(InstancePtr->Control_BaseAddress, XKERNEL_STAGE0_CONTROL_ADDR_MSP_CONV_WEIGHT_DATA + 4) << 32;
    return Data;
}

void XKernel_stage0_Set_msp_conv_bias(XKernel_stage0 *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XKernel_stage0_WriteReg(InstancePtr->Control_BaseAddress, XKERNEL_STAGE0_CONTROL_ADDR_MSP_CONV_BIAS_DATA, (u32)(Data));
    XKernel_stage0_WriteReg(InstancePtr->Control_BaseAddress, XKERNEL_STAGE0_CONTROL_ADDR_MSP_CONV_BIAS_DATA + 4, (u32)(Data >> 32));
}

u64 XKernel_stage0_Get_msp_conv_bias(XKernel_stage0 *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XKernel_stage0_ReadReg(InstancePtr->Control_BaseAddress, XKERNEL_STAGE0_CONTROL_ADDR_MSP_CONV_BIAS_DATA);
    Data += (u64)XKernel_stage0_ReadReg(InstancePtr->Control_BaseAddress, XKERNEL_STAGE0_CONTROL_ADDR_MSP_CONV_BIAS_DATA + 4) << 32;
    return Data;
}

void XKernel_stage0_Set_msp_norm_weight(XKernel_stage0 *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XKernel_stage0_WriteReg(InstancePtr->Control_BaseAddress, XKERNEL_STAGE0_CONTROL_ADDR_MSP_NORM_WEIGHT_DATA, (u32)(Data));
    XKernel_stage0_WriteReg(InstancePtr->Control_BaseAddress, XKERNEL_STAGE0_CONTROL_ADDR_MSP_NORM_WEIGHT_DATA + 4, (u32)(Data >> 32));
}

u64 XKernel_stage0_Get_msp_norm_weight(XKernel_stage0 *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XKernel_stage0_ReadReg(InstancePtr->Control_BaseAddress, XKERNEL_STAGE0_CONTROL_ADDR_MSP_NORM_WEIGHT_DATA);
    Data += (u64)XKernel_stage0_ReadReg(InstancePtr->Control_BaseAddress, XKERNEL_STAGE0_CONTROL_ADDR_MSP_NORM_WEIGHT_DATA + 4) << 32;
    return Data;
}

void XKernel_stage0_Set_msp_norm_bias(XKernel_stage0 *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XKernel_stage0_WriteReg(InstancePtr->Control_BaseAddress, XKERNEL_STAGE0_CONTROL_ADDR_MSP_NORM_BIAS_DATA, (u32)(Data));
    XKernel_stage0_WriteReg(InstancePtr->Control_BaseAddress, XKERNEL_STAGE0_CONTROL_ADDR_MSP_NORM_BIAS_DATA + 4, (u32)(Data >> 32));
}

u64 XKernel_stage0_Get_msp_norm_bias(XKernel_stage0 *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XKernel_stage0_ReadReg(InstancePtr->Control_BaseAddress, XKERNEL_STAGE0_CONTROL_ADDR_MSP_NORM_BIAS_DATA);
    Data += (u64)XKernel_stage0_ReadReg(InstancePtr->Control_BaseAddress, XKERNEL_STAGE0_CONTROL_ADDR_MSP_NORM_BIAS_DATA + 4) << 32;
    return Data;
}

void XKernel_stage0_Set_msp_norm_running_mean(XKernel_stage0 *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XKernel_stage0_WriteReg(InstancePtr->Control_BaseAddress, XKERNEL_STAGE0_CONTROL_ADDR_MSP_NORM_RUNNING_MEAN_DATA, (u32)(Data));
    XKernel_stage0_WriteReg(InstancePtr->Control_BaseAddress, XKERNEL_STAGE0_CONTROL_ADDR_MSP_NORM_RUNNING_MEAN_DATA + 4, (u32)(Data >> 32));
}

u64 XKernel_stage0_Get_msp_norm_running_mean(XKernel_stage0 *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XKernel_stage0_ReadReg(InstancePtr->Control_BaseAddress, XKERNEL_STAGE0_CONTROL_ADDR_MSP_NORM_RUNNING_MEAN_DATA);
    Data += (u64)XKernel_stage0_ReadReg(InstancePtr->Control_BaseAddress, XKERNEL_STAGE0_CONTROL_ADDR_MSP_NORM_RUNNING_MEAN_DATA + 4) << 32;
    return Data;
}

void XKernel_stage0_Set_msp_norm_running_var(XKernel_stage0 *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XKernel_stage0_WriteReg(InstancePtr->Control_BaseAddress, XKERNEL_STAGE0_CONTROL_ADDR_MSP_NORM_RUNNING_VAR_DATA, (u32)(Data));
    XKernel_stage0_WriteReg(InstancePtr->Control_BaseAddress, XKERNEL_STAGE0_CONTROL_ADDR_MSP_NORM_RUNNING_VAR_DATA + 4, (u32)(Data >> 32));
}

u64 XKernel_stage0_Get_msp_norm_running_var(XKernel_stage0 *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XKernel_stage0_ReadReg(InstancePtr->Control_BaseAddress, XKERNEL_STAGE0_CONTROL_ADDR_MSP_NORM_RUNNING_VAR_DATA);
    Data += (u64)XKernel_stage0_ReadReg(InstancePtr->Control_BaseAddress, XKERNEL_STAGE0_CONTROL_ADDR_MSP_NORM_RUNNING_VAR_DATA + 4) << 32;
    return Data;
}

void XKernel_stage0_Set_dw_conv_weight(XKernel_stage0 *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XKernel_stage0_WriteReg(InstancePtr->Control_BaseAddress, XKERNEL_STAGE0_CONTROL_ADDR_DW_CONV_WEIGHT_DATA, (u32)(Data));
    XKernel_stage0_WriteReg(InstancePtr->Control_BaseAddress, XKERNEL_STAGE0_CONTROL_ADDR_DW_CONV_WEIGHT_DATA + 4, (u32)(Data >> 32));
}

u64 XKernel_stage0_Get_dw_conv_weight(XKernel_stage0 *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XKernel_stage0_ReadReg(InstancePtr->Control_BaseAddress, XKERNEL_STAGE0_CONTROL_ADDR_DW_CONV_WEIGHT_DATA);
    Data += (u64)XKernel_stage0_ReadReg(InstancePtr->Control_BaseAddress, XKERNEL_STAGE0_CONTROL_ADDR_DW_CONV_WEIGHT_DATA + 4) << 32;
    return Data;
}

void XKernel_stage0_Set_norm_1_weight(XKernel_stage0 *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XKernel_stage0_WriteReg(InstancePtr->Control_BaseAddress, XKERNEL_STAGE0_CONTROL_ADDR_NORM_1_WEIGHT_DATA, (u32)(Data));
    XKernel_stage0_WriteReg(InstancePtr->Control_BaseAddress, XKERNEL_STAGE0_CONTROL_ADDR_NORM_1_WEIGHT_DATA + 4, (u32)(Data >> 32));
}

u64 XKernel_stage0_Get_norm_1_weight(XKernel_stage0 *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XKernel_stage0_ReadReg(InstancePtr->Control_BaseAddress, XKERNEL_STAGE0_CONTROL_ADDR_NORM_1_WEIGHT_DATA);
    Data += (u64)XKernel_stage0_ReadReg(InstancePtr->Control_BaseAddress, XKERNEL_STAGE0_CONTROL_ADDR_NORM_1_WEIGHT_DATA + 4) << 32;
    return Data;
}

void XKernel_stage0_Set_norm_1_bias(XKernel_stage0 *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XKernel_stage0_WriteReg(InstancePtr->Control_BaseAddress, XKERNEL_STAGE0_CONTROL_ADDR_NORM_1_BIAS_DATA, (u32)(Data));
    XKernel_stage0_WriteReg(InstancePtr->Control_BaseAddress, XKERNEL_STAGE0_CONTROL_ADDR_NORM_1_BIAS_DATA + 4, (u32)(Data >> 32));
}

u64 XKernel_stage0_Get_norm_1_bias(XKernel_stage0 *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XKernel_stage0_ReadReg(InstancePtr->Control_BaseAddress, XKERNEL_STAGE0_CONTROL_ADDR_NORM_1_BIAS_DATA);
    Data += (u64)XKernel_stage0_ReadReg(InstancePtr->Control_BaseAddress, XKERNEL_STAGE0_CONTROL_ADDR_NORM_1_BIAS_DATA + 4) << 32;
    return Data;
}

void XKernel_stage0_Set_norm_1_running_mean(XKernel_stage0 *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XKernel_stage0_WriteReg(InstancePtr->Control_BaseAddress, XKERNEL_STAGE0_CONTROL_ADDR_NORM_1_RUNNING_MEAN_DATA, (u32)(Data));
    XKernel_stage0_WriteReg(InstancePtr->Control_BaseAddress, XKERNEL_STAGE0_CONTROL_ADDR_NORM_1_RUNNING_MEAN_DATA + 4, (u32)(Data >> 32));
}

u64 XKernel_stage0_Get_norm_1_running_mean(XKernel_stage0 *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XKernel_stage0_ReadReg(InstancePtr->Control_BaseAddress, XKERNEL_STAGE0_CONTROL_ADDR_NORM_1_RUNNING_MEAN_DATA);
    Data += (u64)XKernel_stage0_ReadReg(InstancePtr->Control_BaseAddress, XKERNEL_STAGE0_CONTROL_ADDR_NORM_1_RUNNING_MEAN_DATA + 4) << 32;
    return Data;
}

void XKernel_stage0_Set_norm_1_running_var(XKernel_stage0 *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XKernel_stage0_WriteReg(InstancePtr->Control_BaseAddress, XKERNEL_STAGE0_CONTROL_ADDR_NORM_1_RUNNING_VAR_DATA, (u32)(Data));
    XKernel_stage0_WriteReg(InstancePtr->Control_BaseAddress, XKERNEL_STAGE0_CONTROL_ADDR_NORM_1_RUNNING_VAR_DATA + 4, (u32)(Data >> 32));
}

u64 XKernel_stage0_Get_norm_1_running_var(XKernel_stage0 *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XKernel_stage0_ReadReg(InstancePtr->Control_BaseAddress, XKERNEL_STAGE0_CONTROL_ADDR_NORM_1_RUNNING_VAR_DATA);
    Data += (u64)XKernel_stage0_ReadReg(InstancePtr->Control_BaseAddress, XKERNEL_STAGE0_CONTROL_ADDR_NORM_1_RUNNING_VAR_DATA + 4) << 32;
    return Data;
}

void XKernel_stage0_Set_se_conv_reduce_weight(XKernel_stage0 *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XKernel_stage0_WriteReg(InstancePtr->Control_BaseAddress, XKERNEL_STAGE0_CONTROL_ADDR_SE_CONV_REDUCE_WEIGHT_DATA, (u32)(Data));
    XKernel_stage0_WriteReg(InstancePtr->Control_BaseAddress, XKERNEL_STAGE0_CONTROL_ADDR_SE_CONV_REDUCE_WEIGHT_DATA + 4, (u32)(Data >> 32));
}

u64 XKernel_stage0_Get_se_conv_reduce_weight(XKernel_stage0 *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XKernel_stage0_ReadReg(InstancePtr->Control_BaseAddress, XKERNEL_STAGE0_CONTROL_ADDR_SE_CONV_REDUCE_WEIGHT_DATA);
    Data += (u64)XKernel_stage0_ReadReg(InstancePtr->Control_BaseAddress, XKERNEL_STAGE0_CONTROL_ADDR_SE_CONV_REDUCE_WEIGHT_DATA + 4) << 32;
    return Data;
}

void XKernel_stage0_Set_se_conv_reduce_bias(XKernel_stage0 *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XKernel_stage0_WriteReg(InstancePtr->Control_BaseAddress, XKERNEL_STAGE0_CONTROL_ADDR_SE_CONV_REDUCE_BIAS_DATA, (u32)(Data));
    XKernel_stage0_WriteReg(InstancePtr->Control_BaseAddress, XKERNEL_STAGE0_CONTROL_ADDR_SE_CONV_REDUCE_BIAS_DATA + 4, (u32)(Data >> 32));
}

u64 XKernel_stage0_Get_se_conv_reduce_bias(XKernel_stage0 *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XKernel_stage0_ReadReg(InstancePtr->Control_BaseAddress, XKERNEL_STAGE0_CONTROL_ADDR_SE_CONV_REDUCE_BIAS_DATA);
    Data += (u64)XKernel_stage0_ReadReg(InstancePtr->Control_BaseAddress, XKERNEL_STAGE0_CONTROL_ADDR_SE_CONV_REDUCE_BIAS_DATA + 4) << 32;
    return Data;
}

void XKernel_stage0_Set_se_conv_expand_weight(XKernel_stage0 *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XKernel_stage0_WriteReg(InstancePtr->Control_BaseAddress, XKERNEL_STAGE0_CONTROL_ADDR_SE_CONV_EXPAND_WEIGHT_DATA, (u32)(Data));
    XKernel_stage0_WriteReg(InstancePtr->Control_BaseAddress, XKERNEL_STAGE0_CONTROL_ADDR_SE_CONV_EXPAND_WEIGHT_DATA + 4, (u32)(Data >> 32));
}

u64 XKernel_stage0_Get_se_conv_expand_weight(XKernel_stage0 *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XKernel_stage0_ReadReg(InstancePtr->Control_BaseAddress, XKERNEL_STAGE0_CONTROL_ADDR_SE_CONV_EXPAND_WEIGHT_DATA);
    Data += (u64)XKernel_stage0_ReadReg(InstancePtr->Control_BaseAddress, XKERNEL_STAGE0_CONTROL_ADDR_SE_CONV_EXPAND_WEIGHT_DATA + 4) << 32;
    return Data;
}

void XKernel_stage0_Set_se_conv_expand_bias(XKernel_stage0 *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XKernel_stage0_WriteReg(InstancePtr->Control_BaseAddress, XKERNEL_STAGE0_CONTROL_ADDR_SE_CONV_EXPAND_BIAS_DATA, (u32)(Data));
    XKernel_stage0_WriteReg(InstancePtr->Control_BaseAddress, XKERNEL_STAGE0_CONTROL_ADDR_SE_CONV_EXPAND_BIAS_DATA + 4, (u32)(Data >> 32));
}

u64 XKernel_stage0_Get_se_conv_expand_bias(XKernel_stage0 *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XKernel_stage0_ReadReg(InstancePtr->Control_BaseAddress, XKERNEL_STAGE0_CONTROL_ADDR_SE_CONV_EXPAND_BIAS_DATA);
    Data += (u64)XKernel_stage0_ReadReg(InstancePtr->Control_BaseAddress, XKERNEL_STAGE0_CONTROL_ADDR_SE_CONV_EXPAND_BIAS_DATA + 4) << 32;
    return Data;
}

void XKernel_stage0_Set_proj_conv_weight(XKernel_stage0 *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XKernel_stage0_WriteReg(InstancePtr->Control_BaseAddress, XKERNEL_STAGE0_CONTROL_ADDR_PROJ_CONV_WEIGHT_DATA, (u32)(Data));
    XKernel_stage0_WriteReg(InstancePtr->Control_BaseAddress, XKERNEL_STAGE0_CONTROL_ADDR_PROJ_CONV_WEIGHT_DATA + 4, (u32)(Data >> 32));
}

u64 XKernel_stage0_Get_proj_conv_weight(XKernel_stage0 *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XKernel_stage0_ReadReg(InstancePtr->Control_BaseAddress, XKERNEL_STAGE0_CONTROL_ADDR_PROJ_CONV_WEIGHT_DATA);
    Data += (u64)XKernel_stage0_ReadReg(InstancePtr->Control_BaseAddress, XKERNEL_STAGE0_CONTROL_ADDR_PROJ_CONV_WEIGHT_DATA + 4) << 32;
    return Data;
}

void XKernel_stage0_Set_Y_msp_conv(XKernel_stage0 *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XKernel_stage0_WriteReg(InstancePtr->Control_BaseAddress, XKERNEL_STAGE0_CONTROL_ADDR_Y_MSP_CONV_DATA, (u32)(Data));
    XKernel_stage0_WriteReg(InstancePtr->Control_BaseAddress, XKERNEL_STAGE0_CONTROL_ADDR_Y_MSP_CONV_DATA + 4, (u32)(Data >> 32));
}

u64 XKernel_stage0_Get_Y_msp_conv(XKernel_stage0 *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XKernel_stage0_ReadReg(InstancePtr->Control_BaseAddress, XKERNEL_STAGE0_CONTROL_ADDR_Y_MSP_CONV_DATA);
    Data += (u64)XKernel_stage0_ReadReg(InstancePtr->Control_BaseAddress, XKERNEL_STAGE0_CONTROL_ADDR_Y_MSP_CONV_DATA + 4) << 32;
    return Data;
}

void XKernel_stage0_Set_Y_msp_norm(XKernel_stage0 *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XKernel_stage0_WriteReg(InstancePtr->Control_BaseAddress, XKERNEL_STAGE0_CONTROL_ADDR_Y_MSP_NORM_DATA, (u32)(Data));
    XKernel_stage0_WriteReg(InstancePtr->Control_BaseAddress, XKERNEL_STAGE0_CONTROL_ADDR_Y_MSP_NORM_DATA + 4, (u32)(Data >> 32));
}

u64 XKernel_stage0_Get_Y_msp_norm(XKernel_stage0 *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XKernel_stage0_ReadReg(InstancePtr->Control_BaseAddress, XKERNEL_STAGE0_CONTROL_ADDR_Y_MSP_NORM_DATA);
    Data += (u64)XKernel_stage0_ReadReg(InstancePtr->Control_BaseAddress, XKERNEL_STAGE0_CONTROL_ADDR_Y_MSP_NORM_DATA + 4) << 32;
    return Data;
}

void XKernel_stage0_Set_Y_dw_conv(XKernel_stage0 *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XKernel_stage0_WriteReg(InstancePtr->Control_BaseAddress, XKERNEL_STAGE0_CONTROL_ADDR_Y_DW_CONV_DATA, (u32)(Data));
    XKernel_stage0_WriteReg(InstancePtr->Control_BaseAddress, XKERNEL_STAGE0_CONTROL_ADDR_Y_DW_CONV_DATA + 4, (u32)(Data >> 32));
}

u64 XKernel_stage0_Get_Y_dw_conv(XKernel_stage0 *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XKernel_stage0_ReadReg(InstancePtr->Control_BaseAddress, XKERNEL_STAGE0_CONTROL_ADDR_Y_DW_CONV_DATA);
    Data += (u64)XKernel_stage0_ReadReg(InstancePtr->Control_BaseAddress, XKERNEL_STAGE0_CONTROL_ADDR_Y_DW_CONV_DATA + 4) << 32;
    return Data;
}

void XKernel_stage0_Set_Y_dw_norm(XKernel_stage0 *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XKernel_stage0_WriteReg(InstancePtr->Control_BaseAddress, XKERNEL_STAGE0_CONTROL_ADDR_Y_DW_NORM_DATA, (u32)(Data));
    XKernel_stage0_WriteReg(InstancePtr->Control_BaseAddress, XKERNEL_STAGE0_CONTROL_ADDR_Y_DW_NORM_DATA + 4, (u32)(Data >> 32));
}

u64 XKernel_stage0_Get_Y_dw_norm(XKernel_stage0 *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XKernel_stage0_ReadReg(InstancePtr->Control_BaseAddress, XKERNEL_STAGE0_CONTROL_ADDR_Y_DW_NORM_DATA);
    Data += (u64)XKernel_stage0_ReadReg(InstancePtr->Control_BaseAddress, XKERNEL_STAGE0_CONTROL_ADDR_Y_DW_NORM_DATA + 4) << 32;
    return Data;
}

void XKernel_stage0_Set_Y_dw_act(XKernel_stage0 *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XKernel_stage0_WriteReg(InstancePtr->Control_BaseAddress, XKERNEL_STAGE0_CONTROL_ADDR_Y_DW_ACT_DATA, (u32)(Data));
    XKernel_stage0_WriteReg(InstancePtr->Control_BaseAddress, XKERNEL_STAGE0_CONTROL_ADDR_Y_DW_ACT_DATA + 4, (u32)(Data >> 32));
}

u64 XKernel_stage0_Get_Y_dw_act(XKernel_stage0 *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XKernel_stage0_ReadReg(InstancePtr->Control_BaseAddress, XKERNEL_STAGE0_CONTROL_ADDR_Y_DW_ACT_DATA);
    Data += (u64)XKernel_stage0_ReadReg(InstancePtr->Control_BaseAddress, XKERNEL_STAGE0_CONTROL_ADDR_Y_DW_ACT_DATA + 4) << 32;
    return Data;
}

void XKernel_stage0_Set_Y_mean(XKernel_stage0 *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XKernel_stage0_WriteReg(InstancePtr->Control_BaseAddress, XKERNEL_STAGE0_CONTROL_ADDR_Y_MEAN_DATA, (u32)(Data));
    XKernel_stage0_WriteReg(InstancePtr->Control_BaseAddress, XKERNEL_STAGE0_CONTROL_ADDR_Y_MEAN_DATA + 4, (u32)(Data >> 32));
}

u64 XKernel_stage0_Get_Y_mean(XKernel_stage0 *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XKernel_stage0_ReadReg(InstancePtr->Control_BaseAddress, XKERNEL_STAGE0_CONTROL_ADDR_Y_MEAN_DATA);
    Data += (u64)XKernel_stage0_ReadReg(InstancePtr->Control_BaseAddress, XKERNEL_STAGE0_CONTROL_ADDR_Y_MEAN_DATA + 4) << 32;
    return Data;
}

void XKernel_stage0_Set_Y_reduce(XKernel_stage0 *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XKernel_stage0_WriteReg(InstancePtr->Control_BaseAddress, XKERNEL_STAGE0_CONTROL_ADDR_Y_REDUCE_DATA, (u32)(Data));
    XKernel_stage0_WriteReg(InstancePtr->Control_BaseAddress, XKERNEL_STAGE0_CONTROL_ADDR_Y_REDUCE_DATA + 4, (u32)(Data >> 32));
}

u64 XKernel_stage0_Get_Y_reduce(XKernel_stage0 *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XKernel_stage0_ReadReg(InstancePtr->Control_BaseAddress, XKERNEL_STAGE0_CONTROL_ADDR_Y_REDUCE_DATA);
    Data += (u64)XKernel_stage0_ReadReg(InstancePtr->Control_BaseAddress, XKERNEL_STAGE0_CONTROL_ADDR_Y_REDUCE_DATA + 4) << 32;
    return Data;
}

void XKernel_stage0_Set_Y_relu(XKernel_stage0 *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XKernel_stage0_WriteReg(InstancePtr->Control_BaseAddress, XKERNEL_STAGE0_CONTROL_ADDR_Y_RELU_DATA, (u32)(Data));
    XKernel_stage0_WriteReg(InstancePtr->Control_BaseAddress, XKERNEL_STAGE0_CONTROL_ADDR_Y_RELU_DATA + 4, (u32)(Data >> 32));
}

u64 XKernel_stage0_Get_Y_relu(XKernel_stage0 *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XKernel_stage0_ReadReg(InstancePtr->Control_BaseAddress, XKERNEL_STAGE0_CONTROL_ADDR_Y_RELU_DATA);
    Data += (u64)XKernel_stage0_ReadReg(InstancePtr->Control_BaseAddress, XKERNEL_STAGE0_CONTROL_ADDR_Y_RELU_DATA + 4) << 32;
    return Data;
}

void XKernel_stage0_Set_Y_expand(XKernel_stage0 *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XKernel_stage0_WriteReg(InstancePtr->Control_BaseAddress, XKERNEL_STAGE0_CONTROL_ADDR_Y_EXPAND_DATA, (u32)(Data));
    XKernel_stage0_WriteReg(InstancePtr->Control_BaseAddress, XKERNEL_STAGE0_CONTROL_ADDR_Y_EXPAND_DATA + 4, (u32)(Data >> 32));
}

u64 XKernel_stage0_Get_Y_expand(XKernel_stage0 *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XKernel_stage0_ReadReg(InstancePtr->Control_BaseAddress, XKERNEL_STAGE0_CONTROL_ADDR_Y_EXPAND_DATA);
    Data += (u64)XKernel_stage0_ReadReg(InstancePtr->Control_BaseAddress, XKERNEL_STAGE0_CONTROL_ADDR_Y_EXPAND_DATA + 4) << 32;
    return Data;
}

void XKernel_stage0_Set_Y_sigmoid(XKernel_stage0 *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XKernel_stage0_WriteReg(InstancePtr->Control_BaseAddress, XKERNEL_STAGE0_CONTROL_ADDR_Y_SIGMOID_DATA, (u32)(Data));
    XKernel_stage0_WriteReg(InstancePtr->Control_BaseAddress, XKERNEL_STAGE0_CONTROL_ADDR_Y_SIGMOID_DATA + 4, (u32)(Data >> 32));
}

u64 XKernel_stage0_Get_Y_sigmoid(XKernel_stage0 *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XKernel_stage0_ReadReg(InstancePtr->Control_BaseAddress, XKERNEL_STAGE0_CONTROL_ADDR_Y_SIGMOID_DATA);
    Data += (u64)XKernel_stage0_ReadReg(InstancePtr->Control_BaseAddress, XKERNEL_STAGE0_CONTROL_ADDR_Y_SIGMOID_DATA + 4) << 32;
    return Data;
}

void XKernel_stage0_Set_Y_se(XKernel_stage0 *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XKernel_stage0_WriteReg(InstancePtr->Control_BaseAddress, XKERNEL_STAGE0_CONTROL_ADDR_Y_SE_DATA, (u32)(Data));
    XKernel_stage0_WriteReg(InstancePtr->Control_BaseAddress, XKERNEL_STAGE0_CONTROL_ADDR_Y_SE_DATA + 4, (u32)(Data >> 32));
}

u64 XKernel_stage0_Get_Y_se(XKernel_stage0 *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XKernel_stage0_ReadReg(InstancePtr->Control_BaseAddress, XKERNEL_STAGE0_CONTROL_ADDR_Y_SE_DATA);
    Data += (u64)XKernel_stage0_ReadReg(InstancePtr->Control_BaseAddress, XKERNEL_STAGE0_CONTROL_ADDR_Y_SE_DATA + 4) << 32;
    return Data;
}

void XKernel_stage0_Set_Y_proj(XKernel_stage0 *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XKernel_stage0_WriteReg(InstancePtr->Control_BaseAddress, XKERNEL_STAGE0_CONTROL_ADDR_Y_PROJ_DATA, (u32)(Data));
    XKernel_stage0_WriteReg(InstancePtr->Control_BaseAddress, XKERNEL_STAGE0_CONTROL_ADDR_Y_PROJ_DATA + 4, (u32)(Data >> 32));
}

u64 XKernel_stage0_Get_Y_proj(XKernel_stage0 *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XKernel_stage0_ReadReg(InstancePtr->Control_BaseAddress, XKERNEL_STAGE0_CONTROL_ADDR_Y_PROJ_DATA);
    Data += (u64)XKernel_stage0_ReadReg(InstancePtr->Control_BaseAddress, XKERNEL_STAGE0_CONTROL_ADDR_Y_PROJ_DATA + 4) << 32;
    return Data;
}

