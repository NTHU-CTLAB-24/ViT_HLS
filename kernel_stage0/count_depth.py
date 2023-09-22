# 创建一个字典来记录参数
parameters = {
    'X_data': [1, 3, 112, 112],
    'msp_filter': [24, 3, 3, 3],
    'msp_bias': [24],
    'reduce_filter': [24, 24, 1, 1],
    'reduce_bias': [24],
    'expand_filter': [24, 24, 1, 1],
    'expand_bias': [24],
    'mean': [24],
    'var': [24],
    'gamma': [24],
    'beta': [24],
    'X_pad': [1, 3, 114, 114],
    'X_conv': [1, 24, 56, 56],
    'X_mean': [1, 24, 1, 1],
    'X_reduce': [1, 24, 1, 1],
    'X_relu': [1, 24, 1, 1],
    'X_expand': [1, 24, 1, 1],
    'X_sigmoid': [1, 24, 1, 1],
    'Y_msp': [1, 24, 56, 56],
    'Y_se': [1, 24, 56, 56]
}


# 遍历所有参数的名称和值
for param_name, param_value in parameters.items():
    count = 1
    for i in param_value:
        count = count * i
    print(f"{param_name}: {param_value}, {count}")
