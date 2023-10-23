# 创建一个字典来记录参数
data = {
    'X_data': [1, 48, 28, 28],
   
    # depth 0
    'Y_norm_0': [1, 48, 28, 28],
    'Y_v_conv_0': [1, 288, 28, 28],
    'Y_v_act_0': [1, 288, 28, 28],
    'Y_dw_conv_0': [1, 288, 14, 14],
    'Y_dw_act_0': [1, 288, 14, 14],
    'result_30': [1, 80, 14, 14],
}

parameters = {
     # depth 0
    'norm_0_weight': [48],
    'norm_0_bias': [48],
    'v_conv_0_weight': [288, 48, 1, 1],
    'v_conv_0_bias': [288],
    'dw_conv_0_filter': [288, 1, 5, 5],
    'dw_norm_0_weight': [288],
    'dw_norm_0_bias': [288],
    'dw_norm_0_mean': [288],
    'dw_norm_0_var': [288],
    'proj_0_weight': [80, 288, 1, 1],
}
'''
# depth 1
    'norm_1_weight': [80],
    'norm_1_bias': [80],
    'norm_1_running_mean': [80],
    'norm_1_running_var': [80],
    'v_conv_1_weight': [240, 80, 1, 1],
    'v_conv_1_bias': [240],
    'dw_conv_1_filter': [240, 1, 3, 3],
    'dw_norm_1_weight': [240],
    'dw_norm_1_bias': [240],
    'dw_norm_1_mean': [240],
    'dw_norm_1_var': [240],
    'proj_1_weight': [80, 240, 1, 1],
'''
# In printParameters.py, copy the output into array
parametersName = [
    "stage3.0.norm.norm.weight",
    "stage3.0.norm.norm.bias",
    "stage3.0.v.conv.weight",
    "stage3.0.v.conv.bias",
    "stage3.0.conv_local.conv.weight",
    "stage3.0.conv_local.norm.weight",
    "stage3.0.conv_local.norm.bias",
    "stage3.0.conv_local.norm.running_mean",
    "stage3.0.conv_local.norm.running_var",
    "stage3.0.proj.conv.weight",
]
'''
    "stage3.1.norm.norm.weight",
    "stage3.1.norm.norm.bias",
    "stage3.1.qk.conv.weight",
    "stage3.1.qk.conv.bias",
    "stage3.1.v.conv.weight",
    "stage3.1.v.conv.bias",
    "stage3.1.conv_local.conv.weight",
    "stage3.1.conv_local.norm.weight",
    "stage3.1.conv_local.norm.bias",
    "stage3.1.conv_local.norm.running_mean",
    "stage3.1.conv_local.norm.running_var",
    "stage3.1.proj.conv.weight",
    "stage3.2.norm.norm.weight",
    "stage3.2.norm.norm.bias",
    "stage3.2.qk.conv.weight",
    "stage3.2.qk.conv.bias",
    "stage3.2.v.conv.weight",
    "stage3.2.v.conv.bias",
    "stage3.2.conv_local.conv.weight",
    "stage3.2.conv_local.norm.weight",
    "stage3.2.conv_local.norm.bias",
    "stage3.2.conv_local.norm.running_mean",
    "stage3.2.conv_local.norm.running_var",
    "stage3.2.proj.conv.weight",
    "stage3.3.norm.norm.weight",
    "stage3.3.norm.norm.bias",
    "stage3.3.qk.conv.weight",
    "stage3.3.qk.conv.bias",
    "stage3.3.v.conv.weight",
    "stage3.3.v.conv.bias",
    "stage3.3.conv_local.conv.weight",
    "stage3.3.conv_local.norm.weight",
    "stage3.3.conv_local.norm.bias",
    "stage3.3.conv_local.norm.running_mean",
    "stage3.3.conv_local.norm.running_var",
    "stage3.3.proj.conv.weight",
    "stage3.4.norm.norm.weight",
    "stage3.4.norm.norm.bias",
    "stage3.4.qk.conv.weight",
    "stage3.4.qk.conv.bias",
    "stage3.4.v.conv.weight",
    "stage3.4.v.conv.bias",
    "stage3.4.conv_local.conv.weight",
    "stage3.4.conv_local.norm.weight",
    "stage3.4.conv_local.norm.bias",
    "stage3.4.conv_local.norm.running_mean",
    "stage3.4.conv_local.norm.running_var",
    "stage3.4.proj.conv.weight",
    "stage3.5.norm.norm.weight",
    "stage3.5.norm.norm.bias",
    "stage3.5.qk.conv.weight",
    "stage3.5.qk.conv.bias",
    "stage3.5.v.conv.weight",
    "stage3.5.v.conv.bias",
    "stage3.5.conv_local.conv.weight",
    "stage3.5.conv_local.norm.weight",
    "stage3.5.conv_local.norm.bias",
    "stage3.5.conv_local.norm.running_mean",
    "stage3.5.conv_local.norm.running_var",
    "stage3.5.proj.conv.weight",
    "stage3.6.norm.norm.weight",
    "stage3.6.norm.norm.bias",
    "stage3.6.qk.conv.weight",
    "stage3.6.qk.conv.bias",
    "stage3.6.v.conv.weight",
    "stage3.6.v.conv.bias",
    "stage3.6.conv_local.conv.weight",
    "stage3.6.conv_local.norm.weight",
    "stage3.6.conv_local.norm.bias",
    "stage3.6.conv_local.norm.running_mean",
    "stage3.6.conv_local.norm.running_var",
    "stage3.6.proj.conv.weight",
    "stage3.7.norm.norm.weight",
    "stage3.7.norm.norm.bias",
    "stage3.7.qk.conv.weight",
    "stage3.7.qk.conv.bias",
    "stage3.7.v.conv.weight",
    "stage3.7.v.conv.bias",
    "stage3.7.conv_local.conv.weight",
    "stage3.7.conv_local.norm.weight",
    "stage3.7.conv_local.norm.bias",
    "stage3.7.conv_local.norm.running_mean",
    "stage3.7.conv_local.norm.running_var",
    "stage3.7.proj.conv.weight",
    '''

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
