# Create a project
open_project -reset proj_data_preprocess

# Add design files
# Remember to include all the kernel file you need
add_files linear.cpp -cflags "-I/users/student/mr111/jhchen22/Vitis_Libraries/vision/L1/include/ -std=c++0x -I/users/student/mr111/jhchen22/OpenCV/source/opencv/install/include/opencv4/"

# Add test bench & files
add_files -tb data_preprocess.cpp -cflags "-I/users/student/mr111/jhchen22/Vitis_Libraries/vision/L1/include/ -std=c++0x -I/users/student/mr111/jhchen22/OpenCV/source/opencv/install/include/opencv4/"
add_files linear_parameters.txt
add_files ILSVRC2012_val_00047654.JPEG

# Set the top-level function
set_top linear

# ########################################################
# Create a solution
open_solution -reset solution1
# Define technology and clock rate
set_part {xcu250-figd2104-2L-e}
# 4ns = 250 MHz為正常值
create_clock -period 50

# increase stack size
# csim_design -ldflags {-z stack-size=10485760}
csim_design -ldflags "-L/users/student/mr111/jhchen22/OpenCV/source/opencv/install/lib64/ -lopencv_core -lopencv_imgcodecs -lopencv_imgproc -lopencv_dnn" -argv " ILSVRC2012_val_00047654.JPEG"

# Run Synthesis
# csynth_design
# RTL Simulation
# -disable_depchk can ignore warning message
# cosim_design -tool xsim -trace_level all -wave_debug
# cosim_design 
# # RTL implementation
# export_design 

# if {$CSIM == 1} {
#   csim_design -ldflags "-L ${OPENCV_LIB} -lopencv_imgcodecs -lopencv_imgproc -lopencv_core -lopencv_highgui -lopencv_flann -lopencv_features2d" -argv " ${XF_PROJ_ROOT}/data/128x128.png "
# }

# if {$CSYNTH == 1} {
#   csynth_design
# }

# if {$COSIM == 1} {
#   cosim_design -ldflags "-L ${OPENCV_LIB} -lopencv_imgcodecs -lopencv_imgproc -lopencv_core -lopencv_highgui -lopencv_flann -lopencv_features2d" -argv " ${XF_PROJ_ROOT}/data/128x128.png "
# }

# if {$VIVADO_SYN == 1} {
#   export_design -flow syn -rtl verilog
# }

# if {$VIVADO_IMPL == 1} {
#   export_design -flow impl -rtl verilog
# }


exit

