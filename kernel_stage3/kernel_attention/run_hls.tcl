# Create a project
open_project -reset proj_kernel_attention

# Add design files
# Remember to include all the kernel file you need
add_files kernel_attention.cpp

# Add test bench & files
add_files -tb kernel_attention_test.cpp

# Set the top-level function
set_top kernel_attention

# ########################################################
# Create a solution
open_solution -reset solution1
# Define technology and clock rate
set_part  {xcu250-figd2104-2L-e}
create_clock -period 50


csim_design
# Run Synthesis
csynth_design


exit

