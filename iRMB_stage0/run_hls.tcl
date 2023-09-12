#
# Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
# Copyright 2022-2023 Advanced Micro Devices, Inc. All Rights Reserved.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#   http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

# Create a project
open_project -reset proj_irmb_stage0_kernel

# Add design files
# Remember to include all the kernel file you need
add_files kernel_iRMB_stage0.cpp
add_files kernel_mspatch.cpp
add_files kernel_DW_conv.cpp
add_files kernel_se.cpp
add_files kernel_proj.cpp

# Add test bench & files
add_files -tb kernel_iRMB_stage0_test.cpp

# Set the top-level function
set_top kernel_irmb_stage0

# ########################################################
# Create a solution
open_solution -reset solution1
# Define technology and clock rate
set_part  {xcu250-figd2104-2L-e}
create_clock -period 25


csim_design
# Run Synthesis
csynth_design
# RTL Simulation
cosim_design 
# RTL implementation
export_design 


exit

