# 创建一个字典来记录参数
parameters = {
    'X_data': [1, 6, 112, 112],
    # depth 1
    'norm_1_weight': [6],
    'norm_1_bias': [6],
    'norm_1_running_mean': [6],
    'norm_1_running_var': [6],
    'v_conv_1_weight': [24, 6, 1, 1],
    'v_conv_1_bias': [24],
    'dw_conv_1_filter': [24, 1, 3, 3],
    'dw_norm_1_gamma': [24],
    'dw_norm_1_beta': [24],
    'dw_norm_1_mean': [24],
    'dw_norm_1_var': [24],
    'proj_1_weight': [8, 24, 1, 1],
    # depth 2
    'norm_2_weight': [8],
    'norm_2_bias': [8],
    'norm_2_running_mean': [8],
    'norm_2_running_var': [8],
    'v_conv_2_weight': [16, 8, 1, 1],
    'v_conv_2_bias': [16],
    'dw_conv_2_filter': [16, 1, 3, 3],
    'dw_norm_2_gamma': [16],
    'dw_norm_2_beta': [16],
    'dw_norm_2_mean': [16],
    'dw_norm_2_var': [16],
    'proj_2_weight': [8, 16, 1, 1],

    # depth 1
    'Y_norm_1': [1, 6, 112, 112],
    'Y_v_conv_1': [1, 24, 112, 112],
    'Y_dw_conv_1': [1, 24, 56, 56],
    'Y_dw_norm_1': [1, 24, 56, 56],
    'Y_dw_act_1': [1, 24, 56, 56],
    'Y_proj_1': [1, 8, 56, 56],
    # depth 2
    'Y_norm_2': [1, 8, 56, 56],
    'Y_v_conv_2': [1, 16, 56, 56],
    'Y_dw_conv_2': [1, 16, 56, 56],
    'Y_dw_norm_2': [1, 16, 56, 56],
    'Y_dw_act_2': [1, 16, 56, 56],
    'Y_proj_2': [1, 8, 56, 56],
    'Y_dw_skip_2': [1, 16, 56, 56],
    'Y_skip_2': [1, 8, 56, 56]
}


# 遍历所有参数的名称和值
idx = 1
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
    
    print(f"OCL_CHECK(err, err = q.enqueueUnmapMemObject(buffer_DataIn_{idx}, {param_name}));")
    idx += 1
