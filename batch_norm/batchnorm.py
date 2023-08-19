import math
import numpy as np
import torch


def my_batch_norm_2d_detail(features, eps=1e-5):

    n, c, h, w = features.shape
    running_var = np.zeros((c))
    running_mean = np.zeros((c))
    gamma = 0.5
    beta = 0.2
    for ci in range(c):  # 分别 处理每一个通道
        mean = 0  # 均值
        var = 0  # 方差

        _sum = 0
        # 对一个 batch 中，特征图相同位置 channel 的每一个元素求和
        for ni in range(n):
            for hi in range(h):
                for wi in range(w):
                    _sum += features[ni, ci, hi, wi]
        mean = _sum / (n * h * w)
        running_mean[ci] = mean

        _sum = 0
        # 对一个 batch 中，特征图相同位置 channel 的每一个元素求平方和，用于计算方差
        for ni in range(n):
            for hi in range(h):
                for wi in range(w):
                    _sum += (features[ni, ci, hi, wi] - mean) ** 2  # 均差平方和
        var = _sum / (n * h * w)
        running_var[ci] = var

        # 更新元素
        for ni in range(n):
            for hi in range(h):
                for wi in range(w):
                    features[ni, ci, hi, wi] = (
                        (features[ni, ci, hi, wi] - mean) / math.sqrt(var + eps)) * gamma + beta

    return features, running_mean, running_var


if __name__ == "__main__":
    featrue = np.zeros((2, 3, 16, 16))

    for n in range(2):
        for c in range(3):
            for h in range(16):
                for w in range(16):
                    featrue[n, c, h, w] = h + n

    my_bn_output, running_mean, running_var = my_batch_norm_2d_detail(featrue)

    # my_bn_output = torch.tensor(my_bn_output)
    # my_bn_output = my_bn_output.permute(0, 3, 1, 2)
    # print(my_bn_output.shape)
    print(my_bn_output)
    # print(running_mean)
    # print(running_var)