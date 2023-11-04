# Create a project
open_project -reset proj_kernel_EMO

# Add design files
# Remember to include all the kernel file you need
add_files kernel_EMO.cpp
add_files kernel_stage0.cpp
add_files kernel_stage1.cpp
add_files kernel_stage2.cpp
add_files kernel_stage3.cpp
add_files kernel_stage4.cpp
add_files kernel_attention_3.cpp
add_files kernel_attention_4.cpp
add_files BatchNorm.cpp
add_files LayerNorm.cpp
add_files ComputeSkip.cpp
add_files DW_conv.cpp
add_files Pointwise_conv.cpp
add_files ReLU.cpp
add_files SiLU.cpp
add_files GeLU.cpp
add_files Clear_data_3.cpp
add_files Clear_data_4.cpp
add_files Split_data_to_7.cpp

# Add test bench & files
# add_files -tb kernel_EMO_test.cpp -cflags "-I/users/student/mr111/jhchen22/Vitis_Libraries/vision/L1/include/ -std=c++0x -I/users/student/mr111/jhchen22/OpenCV/source/opencv/install/include/opencv4/"
add_files -tb kernel_EMO_test.cpp
add_files ILSVRC2012_val_00047654.JPEG
add_files stage0_parameters.txt
add_files stage1_parameters.txt
add_files stage2_parameters.txt
add_files stage3_parameters.txt
add_files stage4_parameters.txt

# Set the top-level function
set_top kernel_EMO

# ########################################################
# Create a solution
open_solution -reset solution1
# Define technology and clock rate
set_part {xcu250-figd2104-2L-e}
# 4ns = 250 MHz為正常值
create_clock -period 50

# increase stack size
csim_design -ldflags {-z stack-size=10485760} 
# csim_design -ldflags "-L/users/student/mr111/jhchen22/OpenCV/source/opencv/install/lib64/ -lopencv_core -lopencv_imgcodecs -lopencv_imgproc -lopencv_dnn" -argv " ILSVRC2012_val_00047654.JPEG"

# Run Synthesis
# csynth_design
# RTL Simulation
# -disable_depchk can ignore warning message
# cosim_design -tool xsim -trace_level all -wave_debug
# cosim_design 
# # RTL implementation
# export_design 


exit

