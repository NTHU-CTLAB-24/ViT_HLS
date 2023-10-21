// 0x000 : reserved
// 0x004 : reserved
// 0x008 : reserved
// 0x00c : reserved
// 0x010 : Data signal of X_data
//         bit 31~0 - X_data[31:0] (Read/Write)
// 0x014 : Data signal of X_data
//         bit 31~0 - X_data[63:32] (Read/Write)
// 0x018 : reserved
// 0x01c : Data signal of msp_conv_weight
//         bit 31~0 - msp_conv_weight[31:0] (Read/Write)
// 0x020 : Data signal of msp_conv_weight
//         bit 31~0 - msp_conv_weight[63:32] (Read/Write)
// 0x024 : reserved
// 0x028 : Data signal of msp_conv_bias
//         bit 31~0 - msp_conv_bias[31:0] (Read/Write)
// 0x02c : Data signal of msp_conv_bias
//         bit 31~0 - msp_conv_bias[63:32] (Read/Write)
// 0x030 : reserved
// 0x034 : Data signal of msp_norm_weight
//         bit 31~0 - msp_norm_weight[31:0] (Read/Write)
// 0x038 : Data signal of msp_norm_weight
//         bit 31~0 - msp_norm_weight[63:32] (Read/Write)
// 0x03c : reserved
// 0x040 : Data signal of msp_norm_bias
//         bit 31~0 - msp_norm_bias[31:0] (Read/Write)
// 0x044 : Data signal of msp_norm_bias
//         bit 31~0 - msp_norm_bias[63:32] (Read/Write)
// 0x048 : reserved
// 0x04c : Data signal of msp_norm_running_mean
//         bit 31~0 - msp_norm_running_mean[31:0] (Read/Write)
// 0x050 : Data signal of msp_norm_running_mean
//         bit 31~0 - msp_norm_running_mean[63:32] (Read/Write)
// 0x054 : reserved
// 0x058 : Data signal of msp_norm_running_var
//         bit 31~0 - msp_norm_running_var[31:0] (Read/Write)
// 0x05c : Data signal of msp_norm_running_var
//         bit 31~0 - msp_norm_running_var[63:32] (Read/Write)
// 0x060 : reserved
// 0x064 : Data signal of dw_conv_weight
//         bit 31~0 - dw_conv_weight[31:0] (Read/Write)
// 0x068 : Data signal of dw_conv_weight
//         bit 31~0 - dw_conv_weight[63:32] (Read/Write)
// 0x06c : reserved
// 0x070 : Data signal of norm_1_weight
//         bit 31~0 - norm_1_weight[31:0] (Read/Write)
// 0x074 : Data signal of norm_1_weight
//         bit 31~0 - norm_1_weight[63:32] (Read/Write)
// 0x078 : reserved
// 0x07c : Data signal of norm_1_bias
//         bit 31~0 - norm_1_bias[31:0] (Read/Write)
// 0x080 : Data signal of norm_1_bias
//         bit 31~0 - norm_1_bias[63:32] (Read/Write)
// 0x084 : reserved
// 0x088 : Data signal of norm_1_running_mean
//         bit 31~0 - norm_1_running_mean[31:0] (Read/Write)
// 0x08c : Data signal of norm_1_running_mean
//         bit 31~0 - norm_1_running_mean[63:32] (Read/Write)
// 0x090 : reserved
// 0x094 : Data signal of norm_1_running_var
//         bit 31~0 - norm_1_running_var[31:0] (Read/Write)
// 0x098 : Data signal of norm_1_running_var
//         bit 31~0 - norm_1_running_var[63:32] (Read/Write)
// 0x09c : reserved
// 0x0a0 : Data signal of se_conv_reduce_weight
//         bit 31~0 - se_conv_reduce_weight[31:0] (Read/Write)
// 0x0a4 : Data signal of se_conv_reduce_weight
//         bit 31~0 - se_conv_reduce_weight[63:32] (Read/Write)
// 0x0a8 : reserved
// 0x0ac : Data signal of se_conv_reduce_bias
//         bit 31~0 - se_conv_reduce_bias[31:0] (Read/Write)
// 0x0b0 : Data signal of se_conv_reduce_bias
//         bit 31~0 - se_conv_reduce_bias[63:32] (Read/Write)
// 0x0b4 : reserved
// 0x0b8 : Data signal of se_conv_expand_weight
//         bit 31~0 - se_conv_expand_weight[31:0] (Read/Write)
// 0x0bc : Data signal of se_conv_expand_weight
//         bit 31~0 - se_conv_expand_weight[63:32] (Read/Write)
// 0x0c0 : reserved
// 0x0c4 : Data signal of se_conv_expand_bias
//         bit 31~0 - se_conv_expand_bias[31:0] (Read/Write)
// 0x0c8 : Data signal of se_conv_expand_bias
//         bit 31~0 - se_conv_expand_bias[63:32] (Read/Write)
// 0x0cc : reserved
// 0x0d0 : Data signal of proj_conv_weight
//         bit 31~0 - proj_conv_weight[31:0] (Read/Write)
// 0x0d4 : Data signal of proj_conv_weight
//         bit 31~0 - proj_conv_weight[63:32] (Read/Write)
// 0x0d8 : reserved
// 0x0dc : Data signal of Y_msp_conv
//         bit 31~0 - Y_msp_conv[31:0] (Read/Write)
// 0x0e0 : Data signal of Y_msp_conv
//         bit 31~0 - Y_msp_conv[63:32] (Read/Write)
// 0x0e4 : reserved
// 0x0e8 : Data signal of Y_msp_norm
//         bit 31~0 - Y_msp_norm[31:0] (Read/Write)
// 0x0ec : Data signal of Y_msp_norm
//         bit 31~0 - Y_msp_norm[63:32] (Read/Write)
// 0x0f0 : reserved
// 0x0f4 : Data signal of Y_dw_conv
//         bit 31~0 - Y_dw_conv[31:0] (Read/Write)
// 0x0f8 : Data signal of Y_dw_conv
//         bit 31~0 - Y_dw_conv[63:32] (Read/Write)
// 0x0fc : reserved
// 0x100 : Data signal of Y_dw_norm
//         bit 31~0 - Y_dw_norm[31:0] (Read/Write)
// 0x104 : Data signal of Y_dw_norm
//         bit 31~0 - Y_dw_norm[63:32] (Read/Write)
// 0x108 : reserved
// 0x10c : Data signal of Y_dw_act
//         bit 31~0 - Y_dw_act[31:0] (Read/Write)
// 0x110 : Data signal of Y_dw_act
//         bit 31~0 - Y_dw_act[63:32] (Read/Write)
// 0x114 : reserved
// 0x118 : Data signal of Y_mean
//         bit 31~0 - Y_mean[31:0] (Read/Write)
// 0x11c : Data signal of Y_mean
//         bit 31~0 - Y_mean[63:32] (Read/Write)
// 0x120 : reserved
// 0x124 : Data signal of Y_reduce
//         bit 31~0 - Y_reduce[31:0] (Read/Write)
// 0x128 : Data signal of Y_reduce
//         bit 31~0 - Y_reduce[63:32] (Read/Write)
// 0x12c : reserved
// 0x130 : Data signal of Y_relu
//         bit 31~0 - Y_relu[31:0] (Read/Write)
// 0x134 : Data signal of Y_relu
//         bit 31~0 - Y_relu[63:32] (Read/Write)
// 0x138 : reserved
// 0x13c : Data signal of Y_expand
//         bit 31~0 - Y_expand[31:0] (Read/Write)
// 0x140 : Data signal of Y_expand
//         bit 31~0 - Y_expand[63:32] (Read/Write)
// 0x144 : reserved
// 0x148 : Data signal of Y_sigmoid
//         bit 31~0 - Y_sigmoid[31:0] (Read/Write)
// 0x14c : Data signal of Y_sigmoid
//         bit 31~0 - Y_sigmoid[63:32] (Read/Write)
// 0x150 : reserved
// 0x154 : Data signal of Y_se
//         bit 31~0 - Y_se[31:0] (Read/Write)
// 0x158 : Data signal of Y_se
//         bit 31~0 - Y_se[63:32] (Read/Write)
// 0x15c : reserved
// 0x160 : Data signal of Y_proj
//         bit 31~0 - Y_proj[31:0] (Read/Write)
// 0x164 : Data signal of Y_proj
//         bit 31~0 - Y_proj[63:32] (Read/Write)
// 0x168 : reserved
// (SC = Self Clear, COR = Clear on Read, TOW = Toggle on Write, COH = Clear on Handshake)

#define CONTROL_ADDR_X_DATA_DATA                0x010
#define CONTROL_BITS_X_DATA_DATA                64
#define CONTROL_ADDR_MSP_CONV_WEIGHT_DATA       0x01c
#define CONTROL_BITS_MSP_CONV_WEIGHT_DATA       64
#define CONTROL_ADDR_MSP_CONV_BIAS_DATA         0x028
#define CONTROL_BITS_MSP_CONV_BIAS_DATA         64
#define CONTROL_ADDR_MSP_NORM_WEIGHT_DATA       0x034
#define CONTROL_BITS_MSP_NORM_WEIGHT_DATA       64
#define CONTROL_ADDR_MSP_NORM_BIAS_DATA         0x040
#define CONTROL_BITS_MSP_NORM_BIAS_DATA         64
#define CONTROL_ADDR_MSP_NORM_RUNNING_MEAN_DATA 0x04c
#define CONTROL_BITS_MSP_NORM_RUNNING_MEAN_DATA 64
#define CONTROL_ADDR_MSP_NORM_RUNNING_VAR_DATA  0x058
#define CONTROL_BITS_MSP_NORM_RUNNING_VAR_DATA  64
#define CONTROL_ADDR_DW_CONV_WEIGHT_DATA        0x064
#define CONTROL_BITS_DW_CONV_WEIGHT_DATA        64
#define CONTROL_ADDR_NORM_1_WEIGHT_DATA         0x070
#define CONTROL_BITS_NORM_1_WEIGHT_DATA         64
#define CONTROL_ADDR_NORM_1_BIAS_DATA           0x07c
#define CONTROL_BITS_NORM_1_BIAS_DATA           64
#define CONTROL_ADDR_NORM_1_RUNNING_MEAN_DATA   0x088
#define CONTROL_BITS_NORM_1_RUNNING_MEAN_DATA   64
#define CONTROL_ADDR_NORM_1_RUNNING_VAR_DATA    0x094
#define CONTROL_BITS_NORM_1_RUNNING_VAR_DATA    64
#define CONTROL_ADDR_SE_CONV_REDUCE_WEIGHT_DATA 0x0a0
#define CONTROL_BITS_SE_CONV_REDUCE_WEIGHT_DATA 64
#define CONTROL_ADDR_SE_CONV_REDUCE_BIAS_DATA   0x0ac
#define CONTROL_BITS_SE_CONV_REDUCE_BIAS_DATA   64
#define CONTROL_ADDR_SE_CONV_EXPAND_WEIGHT_DATA 0x0b8
#define CONTROL_BITS_SE_CONV_EXPAND_WEIGHT_DATA 64
#define CONTROL_ADDR_SE_CONV_EXPAND_BIAS_DATA   0x0c4
#define CONTROL_BITS_SE_CONV_EXPAND_BIAS_DATA   64
#define CONTROL_ADDR_PROJ_CONV_WEIGHT_DATA      0x0d0
#define CONTROL_BITS_PROJ_CONV_WEIGHT_DATA      64
#define CONTROL_ADDR_Y_MSP_CONV_DATA            0x0dc
#define CONTROL_BITS_Y_MSP_CONV_DATA            64
#define CONTROL_ADDR_Y_MSP_NORM_DATA            0x0e8
#define CONTROL_BITS_Y_MSP_NORM_DATA            64
#define CONTROL_ADDR_Y_DW_CONV_DATA             0x0f4
#define CONTROL_BITS_Y_DW_CONV_DATA             64
#define CONTROL_ADDR_Y_DW_NORM_DATA             0x100
#define CONTROL_BITS_Y_DW_NORM_DATA             64
#define CONTROL_ADDR_Y_DW_ACT_DATA              0x10c
#define CONTROL_BITS_Y_DW_ACT_DATA              64
#define CONTROL_ADDR_Y_MEAN_DATA                0x118
#define CONTROL_BITS_Y_MEAN_DATA                64
#define CONTROL_ADDR_Y_REDUCE_DATA              0x124
#define CONTROL_BITS_Y_REDUCE_DATA              64
#define CONTROL_ADDR_Y_RELU_DATA                0x130
#define CONTROL_BITS_Y_RELU_DATA                64
#define CONTROL_ADDR_Y_EXPAND_DATA              0x13c
#define CONTROL_BITS_Y_EXPAND_DATA              64
#define CONTROL_ADDR_Y_SIGMOID_DATA             0x148
#define CONTROL_BITS_Y_SIGMOID_DATA             64
#define CONTROL_ADDR_Y_SE_DATA                  0x154
#define CONTROL_BITS_Y_SE_DATA                  64
#define CONTROL_ADDR_Y_PROJ_DATA                0x160
#define CONTROL_BITS_Y_PROJ_DATA                64
