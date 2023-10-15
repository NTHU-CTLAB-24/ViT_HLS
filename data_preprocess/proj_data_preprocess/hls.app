<AutoPilot:project xmlns:AutoPilot="com.autoesl.autopilot.project" top="linear" name="proj_data_preprocess">
    <includePaths/>
    <libraryFlag/>
    <files>
        <file name="ILSVRC2012_val_00047654.JPEG" sc="0" tb="false" cflags="" csimflags="" blackbox="false"/>
        <file name="linear_parameters.txt" sc="0" tb="false" cflags="" csimflags="" blackbox="false"/>
        <file name="../../data_preprocess.cpp" sc="0" tb="1" cflags=" -I/users/student/mr111/jhchen22/Vitis_Libraries/vision/L1/include/.  -I/users/student/mr111/jhchen22/OpenCV/source/opencv/install/include/opencv4/. -std=c++0x  -Wno-unknown-pragmas" csimflags=" -Wno-unknown-pragmas" blackbox="false"/>
        <file name="linear.cpp" sc="0" tb="false" cflags="-I/users/student/mr111/jhchen22/Vitis_Libraries/vision/L1/include/. -std=c++0x -I/users/student/mr111/jhchen22/OpenCV/source/opencv/install/include/opencv4/." csimflags="" blackbox="false"/>
    </files>
    <solutions>
        <solution name="solution1" status=""/>
    </solutions>
    <Simulation argv=" ILSVRC2012_val_00047654.JPEG">
        <SimFlow name="csim" setup="false" optimizeCompile="false" clean="false" ldflags="-L/users/student/mr111/jhchen22/OpenCV/source/opencv/install/lib64/ -lopencv_core -lopencv_imgcodecs -lopencv_imgproc -lopencv_dnn" mflags=""/>
    </Simulation>
</AutoPilot:project>

