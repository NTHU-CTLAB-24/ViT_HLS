# Create a project
open_project -reset proj_irmb_stage1_kernel

# Add design files
# Remember to include all the kernel file you need
add_files kernel_iRMB_stage1.cpp

add_files kernel_norm_in_0.cpp
add_files kernel_v_conv_0.cpp
add_files kernel_DW_conv_0.cpp
add_files kernel_proj_0.cpp

add_files kernel_norm_in_1.cpp
add_files kernel_v_conv_1.cpp
add_files kernel_DW_conv_1.cpp
add_files kernel_proj_1.cpp

# Add test bench & files
add_files -tb kernel_iRMB_stage1_test.cpp

# Set the top-level function
set_top kernel_irmb_stage1

# ########################################################
# Create a solution
open_solution -reset solution1
# Define technology and clock rate
set_part  {xcu250-figd2104-2L-e}
create_clock -period 50


csim_design
# Run Synthesis
csynth_design
# RTL Simulation
cosim_design 
# RTL implementation
export_design 


exit

