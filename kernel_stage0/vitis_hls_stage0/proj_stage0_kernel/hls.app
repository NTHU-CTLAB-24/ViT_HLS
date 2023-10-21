<AutoPilot:project xmlns:AutoPilot="com.autoesl.autopilot.project" projectType="C/C++" top="kernel_stage0" name="proj_stage0_kernel">
    <includePaths/>
    <libraryFlag/>
    <files>
        <file name="stage0_parameters.txt" sc="0" tb="false" cflags="" csimflags="" blackbox="false"/>
        <file name="../../kernel_stage0_test.cpp" sc="0" tb="1" cflags=" -Wno-unknown-pragmas" csimflags=" -Wno-unknown-pragmas" blackbox="false"/>
        <file name="ReLU.cpp" sc="0" tb="false" cflags="" csimflags="" blackbox="false"/>
        <file name="Pointwise_conv.cpp" sc="0" tb="false" cflags="" csimflags="" blackbox="false"/>
        <file name="DW_conv.cpp" sc="0" tb="false" cflags="" csimflags="" blackbox="false"/>
        <file name="BatchNorm.cpp" sc="0" tb="false" cflags="" csimflags="" blackbox="false"/>
        <file name="kernel_stage0.cpp" sc="0" tb="false" cflags="" csimflags="" blackbox="false"/>
    </files>
    <solutions>
        <solution name="solution1" status=""/>
    </solutions>
    <Simulation argv="">
        <SimFlow name="csim" setup="false" optimizeCompile="false" clean="false" ldflags="" mflags=""/>
    </Simulation>
</AutoPilot:project>

