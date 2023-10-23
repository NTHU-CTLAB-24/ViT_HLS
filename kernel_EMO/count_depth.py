# 创建一个字典来记录参数
data = {
    'X_data': [1, 24, 112, 112],
    # stage 1 depth 1
    'Y_norm_1_1': [1, 24, 112, 112],
    'Y_v_conv_1_1': [1, 96, 112, 112],
    'Y_v_act_1_1' : [1, 96, 112, 112],
    'Y_dw_conv_1_1': [1, 96, 56, 56],
    'Y_dw_norm_1_1': [1, 96, 56, 56],
    'Y_dw_act_1_1': [1, 96, 56, 56],
    'Y_proj_1_1': [1, 32, 56, 56],
    # stage 1 depth 2
    'Y_norm_1_2': [1, 32, 56, 56],
    'Y_v_conv_1_2': [1, 64, 56, 56],
    'Y_v_act_1_2' : [1, 64, 56, 56],
    'Y_dw_conv_1_2': [1, 64, 56, 56],
    'Y_dw_norm_1_2': [1, 64, 56, 56],
    'Y_dw_act_1_2': [1, 64, 56, 56],
    'Y_proj_1_2': [1, 32, 56, 56],
    'Y_dw_skip_1_2': [1, 64, 56, 56],
    'Y_skip_1_2': [1, 32, 56, 56],
    
    # stage 2 depth 1
    'Y_norm_2_1': [1, 32, 56, 56],
    'Y_v_conv_2_1': [1, 160, 56, 56],
    'Y_v_act_2_1' : [1, 160, 56, 56],
    'Y_dw_conv_2_1': [1, 160, 28, 28],
    'Y_dw_norm_2_1': [1, 160, 28, 28],
    'Y_dw_act_2_1': [1, 160, 28, 28],
    'Y_proj_2_1': [1, 48, 28, 28],
    # stage 2 depth 2
    'Y_norm_2_2': [1, 48, 28, 28],
    'Y_v_conv_2_2': [1, 120, 28, 28],
    'Y_v_act_2_2' : [1, 120, 28, 28],
    'Y_dw_conv_2_2': [1, 120, 28, 28],
    'Y_dw_norm_2_2': [1, 120, 28, 28],
    'Y_dw_act_2_2': [1, 120, 28, 28],
    'Y_proj_2_2': [1, 48, 28, 28],
    'Y_dw_skip_2_2': [1, 120, 28, 28],
    'Y_skip_2_2': [1, 48, 28, 28],

}

parameters = {
    # stage 1 depth 1
    'norm_1_1_weight': [24],
    'norm_1_1_bias': [24],
    'norm_1_1_running_mean': [24],
    'norm_1_1_running_var': [24],
    'v_conv_1_1_weight': [96, 24, 1, 1],
    'v_conv_1_1_bias': [96],
    'dw_conv_1_1_filter': [96, 1, 3, 3],
    'dw_norm_1_1_gamma': [96],
    'dw_norm_1_1_beta': [96],
    'dw_norm_1_1_mean': [96],
    'dw_norm_1_1_var': [96],
    'proj_1_1_weight': [32, 96, 1, 1],
    # stage 1 depth 2
    'norm_1_2_weight': [32],
    'norm_1_2_bias': [32],
    'norm_1_2_running_mean': [32],
    'norm_1_2_running_var': [32],
    'v_conv_1_2_weight': [64, 32, 1, 1],
    'v_conv_1_2_bias': [64],
    'dw_conv_1_2_filter': [64, 1, 3, 3],
    'dw_norm_1_2_gamma': [64],
    'dw_norm_1_2_beta': [64],
    'dw_norm_1_2_mean': [64],
    'dw_norm_1_2_var': [64],
    'proj_1_2_weight': [32, 64, 1, 1],

    # stage 2 depth 1
    'norm_2_1_weight': [32],
    'norm_2_1_bias': [32],
    'norm_2_1_running_mean': [32],
    'norm_2_1_running_var': [32],
    'v_conv_2_1_weight': [160, 32, 1, 1],
    'v_conv_2_1_bias': [160],
    'dw_conv_2_1_filter': [160, 1, 3, 3],
    'dw_norm_2_1_gamma': [160],
    'dw_norm_2_1_beta': [160],
    'dw_norm_2_1_mean': [160],
    'dw_norm_2_1_var': [160],
    'proj_2_1_weight': [48, 160, 1, 1],
    # stage 2 depth 2
    'norm_2_2_weight': [48],
    'norm_2_2_bias': [48],
    'norm_2_2_running_mean': [48],
    'norm_2_2_running_var': [48],
    'v_conv_2_2_weight': [120, 48, 1, 1],
    'v_conv_2_2_bias': [120],
    'dw_conv_2_2_filter': [120, 1, 3, 3],
    'dw_norm_2_2_gamma': [120],
    'dw_norm_2_2_beta': [120],
    'dw_norm_2_2_mean': [120],
    'dw_norm_2_2_var': [120],
    'proj_2_2_weight': [48, 120, 1, 1],
}

# In printParameters.py, copy the output into array
parametersName = [
    "stage1.0.norm.weight", 
    "stage1.0.norm.bias", 
    "stage1.0.norm.running_mean", 
    "stage1.0.norm.running_var", 
    "stage1.0.v.conv.weight", 
    "stage1.0.v.conv.bias", 
    "stage1.0.conv_local.conv.weight", 
    "stage1.0.conv_local.norm.weight", 
    "stage1.0.conv_local.norm.bias", 
    "stage1.0.conv_local.norm.running_mean", 
    "stage1.0.conv_local.norm.running_var", 
    "stage1.0.proj.conv.weight", 
    "stage1.1.norm.weight", 
    "stage1.1.norm.bias", 
    "stage1.1.norm.running_mean", 
    "stage1.1.norm.running_var", 
    "stage1.1.v.conv.weight", 
    "stage1.1.v.conv.bias", 
    "stage1.1.conv_local.conv.weight", 
    "stage1.1.conv_local.norm.weight", 
    "stage1.1.conv_local.norm.bias", 
    "stage1.1.conv_local.norm.running_mean", 
    "stage1.1.conv_local.norm.running_var", 
    "stage1.1.proj.conv.weight", 

    "stage2.0.norm.weight", 
    "stage2.0.norm.bias", 
    "stage2.0.norm.running_mean", 
    "stage2.0.norm.running_var", 
    "stage2.0.v.conv.weight", 
    "stage2.0.v.conv.bias", 
    "stage2.0.conv_local.conv.weight", 
    "stage2.0.conv_local.norm.weight", 
    "stage2.0.conv_local.norm.bias", 
    "stage2.0.conv_local.norm.running_mean", 
    "stage2.0.conv_local.norm.running_var", 
    "stage2.0.proj.conv.weight", 
    "stage2.1.norm.weight", 
    "stage2.1.norm.bias", 
    "stage2.1.norm.running_mean", 
    "stage2.1.norm.running_var", 
    "stage2.1.v.conv.weight", 
    "stage2.1.v.conv.bias", 
    "stage2.1.conv_local.conv.weight", 
    "stage2.1.conv_local.norm.weight", 
    "stage2.1.conv_local.norm.bias", 
    "stage2.1.conv_local.norm.running_mean", 
    "stage2.1.conv_local.norm.running_var", 
    "stage2.1.proj.conv.weight", 
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
#     print(f"{param_name}: {param_value}, {count}")
    
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
    print(f"for (int i = 0; i < {count}; i++) {param_name}[i] = parameterData[\"{parametersName[idx]}\"][i];")
    idx+=1
