# Create a project
open_project -reset proj_se_kernel

# Add design files
add_files kernel_se.cpp
# Add test bench & files
add_files -tb kernel_se_test.cpp

# Set the top-level function
set_top kernel_se

# ########################################################
# Create a solution
open_solution -reset solution1
# Define technology and clock rate
set_part  {xcu250-figd2104-2L-e}
create_clock -period 15
#set_part {xcvu11p-flga2577-1-e}
#create_clock -period 4 -name default
#config_export -format ip_catalog
#set_clock_uncertainty 0.5

csim_design
# Run Synthesis
csynth_design
# RTL Simulation
cosim_design 
# RTL implementation
export_design 


exit

