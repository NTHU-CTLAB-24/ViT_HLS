# 创建一个字典来记录参数
data = {
    'X_data': [1, 168, 7, 7],
    'X_reduce': [1, 168],
    'Y_linear': [1, 1000],
}

parameters = {
    "norm_weight": [168], 
    "norm_bias": [168], 
    "head_weight": [1000, 168], 
    "head_bias": [1000], 
}

# In printParameters.py, copy the output into array
parametersName = [
    "norm.norm.weight", 
    "norm.norm.bias", 
    "head.weight", 
    "head.bias", 
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
    print(f"for (int i = 0; i < {count}; i++) {param_name}[i] = parameterData[\"{parametersName[idx]}\"][i];")
    idx+=1
