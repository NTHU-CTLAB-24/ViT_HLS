# Create a project
open_project -reset proj_kernel_stage3

# Add design files
# Remember to include all the kernel file you need
add_files kernel_stage3.cpp

add_files BatchNorm.cpp
add_files ComputeSkip.cpp
add_files DW_conv.cpp
add_files Pointwise_conv.cpp
add_files ReLU.cpp
add_files kernel_attention.cpp

# Add test bench & files
add_files -tb kernel_stage3_test.cpp

# Set the top-level function
set_top kernel_stage3

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
# -disable_depchk can ignore warning message
cosim_design 
# RTL implementation
export_design 


exit

