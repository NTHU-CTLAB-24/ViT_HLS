// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2022.1 (64-bit)
// Tool Version Limit: 2022.04
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// ==============================================================
#ifndef __linux__

#include "xstatus.h"
#include "xparameters.h"
#include "xkernel_stage0.h"

extern XKernel_stage0_Config XKernel_stage0_ConfigTable[];

XKernel_stage0_Config *XKernel_stage0_LookupConfig(u16 DeviceId) {
	XKernel_stage0_Config *ConfigPtr = NULL;

	int Index;

	for (Index = 0; Index < XPAR_XKERNEL_STAGE0_NUM_INSTANCES; Index++) {
		if (XKernel_stage0_ConfigTable[Index].DeviceId == DeviceId) {
			ConfigPtr = &XKernel_stage0_ConfigTable[Index];
			break;
		}
	}

	return ConfigPtr;
}

int XKernel_stage0_Initialize(XKernel_stage0 *InstancePtr, u16 DeviceId) {
	XKernel_stage0_Config *ConfigPtr;

	Xil_AssertNonvoid(InstancePtr != NULL);

	ConfigPtr = XKernel_stage0_LookupConfig(DeviceId);
	if (ConfigPtr == NULL) {
		InstancePtr->IsReady = 0;
		return (XST_DEVICE_NOT_FOUND);
	}

	return XKernel_stage0_CfgInitialize(InstancePtr, ConfigPtr);
}

#endif

