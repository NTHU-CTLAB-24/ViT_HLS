# Create a project
open_project -reset proj_kernel_stage1

# Add design files
# Remember to include all the kernel file you need
add_files kernel_stage1.cpp

add_files BatchNorm.cpp
add_files ComputeSkip.cpp
add_files DW_conv.cpp
add_files Pointwise_conv.cpp
add_files ReLU.cpp
add_files SiLU.cpp

# Add test bench & files
add_files -tb kernel_stage1_test.cpp
add_files stage1_parameters.txt

# Set the top-level function
set_top kernel_stage1

# ########################################################
# Create a solution
open_solution -reset solution1
# Define technology and clock rate
set_part {xcu250-figd2104-2L-e}
# 4ns = 250 MHz為正常值
create_clock -period 50

# increase stack size
csim_design -ldflags {-z stack-size=10485760}
# Run Synthesis
csynth_design
# RTL Simulation
# -disable_depchk can ignore warning message
# cosim_design -tool xsim -trace_level all -wave_debug
# cosim_design 
# # RTL implementation
# export_design 


exit

