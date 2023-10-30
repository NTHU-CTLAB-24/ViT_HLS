# Create a project
open_project -reset proj_stage0_kernel

# Add design files
add_files kernel_stage0.cpp
add_files kernel_stage0.hpp

add_files BatchNorm.cpp
add_files DW_conv.cpp
add_files Pointwise_conv.cpp
add_files ReLU.cpp
add_files SiLU.cpp
add_files reset_arr.cpp
add_files stage0_resources.cpp

# Add test bench & files
add_files -tb kernel_stage0_test.cpp
add_files stage0_parameters.txt

# Set the top-level function
set_top kernel_stage0

# ########################################################
# Create a solution
open_solution -reset solution1
# Define technology and clock rate
set_part  {xcu250-figd2104-2L-e}
# set_part  {xczu49dr-fsvf1760-1-i}
# 4ns = 250 MHz為正常值
create_clock -period 15
#set_part {xcvu11p-flga2577-1-e}
#create_clock -period 4 -name default
#config_export -format ip_catalog
#set_clock_uncertainty 0.5

csim_design
# Run Synthesis
csynth_design
# RTL Simulation
# cosim_design 
# RTL implementation
# export_design 


exit

