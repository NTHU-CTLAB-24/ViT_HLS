# 创建一个字典来记录参数
data = {
    'X_data': [1, 3, 224, 224],
    'Y_msp_conv': [1, 24, 112, 112],
    'Y_msp_norm': [1, 24, 112, 112],

    'Y_dw_conv': [1, 24, 112, 112],
    'Y_dw_norm': [1, 24, 112, 112],
    'Y_dw_act': [1, 24, 112, 112],

    'Y_mean': [1, 24, 1, 1],
    'Y_reduce': [1, 24, 1, 1],
    'Y_relu': [1, 24, 1, 1],
    'Y_expand': [1, 24, 1, 1],
    'Y_sigmoid': [1, 24, 1, 1],
    'Y_se': [1, 24, 112, 112],

    'Y_proj': [1, 24, 112, 112]
}

parameters = {
    # msp
    'msp_conv_weight': [24, 3, 3, 3],
    'msp_conv_bias': [24],
    'msp_norm_weight': [24],
    'msp_norm_bias': [24],
    'msp_norm_running_mean': [24],
    'msp_norm_running_var': [24],
    # conv_local
    'dw_conv_weight': [24, 1, 3, 3],
    'norm_1_weight': [24],
    'norm_1_bias': [24],
    'norm_1_running_mean': [24],
    'norm_1_running_var': [24],
    # se
    'se_conv_reduce_weight': [24, 24, 1, 1],
    'se_conv_reduce_bias': [24],
    'se_conv_expand_weight': [24, 24, 1, 1],
    'se_conv_expand_bias': [24],
    # projection
    'proj_conv_weight': [24, 24, 1, 1]
}

# In printParameters.py, copy the output into array
parametersName = [
    "stage0.0.convs.0.0.weight",
    "stage0.0.convs.0.0.bias",
    "stage0.0.convs.0.1.weight",
    "stage0.0.convs.0.1.bias",
    "stage0.0.convs.0.1.running_mean",
    "stage0.0.convs.0.1.running_var",
    "stage0.1.conv_local.conv.weight",
    "stage0.1.conv_local.norm.weight",
    "stage0.1.conv_local.norm.bias",
    "stage0.1.conv_local.norm.running_mean",
    "stage0.1.conv_local.norm.running_var",
    "stage0.1.se.conv_reduce.weight",
    "stage0.1.se.conv_reduce.bias",
    "stage0.1.se.conv_expand.weight",
    "stage0.1.se.conv_expand.bias",
    "stage0.1.proj.conv.weight",
]

# print data depth
# for param_name, param_value in data.items():
#     count = 1
#     for i in param_value:
#         count = count * i
#     print(f"{param_name}: {param_value}, {count}")

# 遍历所有参数的名称和值
idx = 0
for param_name, param_value in parameters.items():
    count = 1
    for i in param_value:
        count = count * i
    # print(f"{param_name}: {param_value}, {count}")

    # below code is used to generate host.cpp code #

    # print(f"static const int {param_name}_size = {count};")

    # print(f"size_t {param_name}_bytes = {param_name}_size * sizeof(float);")

    # print(f"OCL_CHECK(err, cl::Buffer buffer_DataIn_{idx}(context, CL_MEM_READ_ONLY, {param_name}_bytes, NULL, &err));")
    # print(f"OCL_CHECK(err, {param_name} = (float *)q.enqueueMapBuffer(buffer_DataIn_{idx}, CL_TRUE, CL_MAP_WRITE, 0, {param_name}_bytes, NULL, NULL, &err));")
    # print()
    # idx += 1

    # print(f"OCL_CHECK(err, err = kernel_stage1.setArg(narg++, buffer_DataIn_{idx}));")
    # idx += 1

    # print(f"OCL_CHECK(err, err = q.enqueueUnmapMemObject(buffer_DataIn_{idx}, {param_name}));")
    # idx += 1

    # generate code for testbench init parameters value
    print(
        f"for (int i = 0; i < {count}; i++) {param_name}[i] = parameterData[\"{parametersName[idx]}\"][i];")
    idx += 1
