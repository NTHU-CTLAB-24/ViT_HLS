// 0x000 : reserved
// 0x004 : reserved
// 0x008 : reserved
// 0x00c : reserved
// 0x010 : Data signal of buffer_DataIn_1
//         bit 31~0 - buffer_DataIn_1[31:0] (Read/Write)
// 0x014 : Data signal of buffer_DataIn_1
//         bit 31~0 - buffer_DataIn_1[63:32] (Read/Write)
// 0x018 : reserved
// 0x01c : Data signal of afterNorm
//         bit 31~0 - afterNorm[31:0] (Read/Write)
// 0x020 : Data signal of afterNorm
//         bit 31~0 - afterNorm[63:32] (Read/Write)
// 0x024 : reserved
// 0x028 : Data signal of norm1_mean
//         bit 31~0 - norm1_mean[31:0] (Read/Write)
// 0x02c : Data signal of norm1_mean
//         bit 31~0 - norm1_mean[63:32] (Read/Write)
// 0x030 : reserved
// 0x034 : Data signal of norm1_var
//         bit 31~0 - norm1_var[31:0] (Read/Write)
// 0x038 : Data signal of norm1_var
//         bit 31~0 - norm1_var[63:32] (Read/Write)
// 0x03c : reserved
// 0x040 : Data signal of norm1_weight
//         bit 31~0 - norm1_weight[31:0] (Read/Write)
// 0x044 : Data signal of norm1_weight
//         bit 31~0 - norm1_weight[63:32] (Read/Write)
// 0x048 : reserved
// 0x04c : Data signal of norm1_bias
//         bit 31~0 - norm1_bias[31:0] (Read/Write)
// 0x050 : Data signal of norm1_bias
//         bit 31~0 - norm1_bias[63:32] (Read/Write)
// 0x054 : reserved
// 0x058 : Data signal of afterPad
//         bit 31~0 - afterPad[31:0] (Read/Write)
// 0x05c : Data signal of afterPad
//         bit 31~0 - afterPad[63:32] (Read/Write)
// 0x060 : reserved
// 0x064 : Data signal of afterRearrangeX
//         bit 31~0 - afterRearrangeX[31:0] (Read/Write)
// 0x068 : Data signal of afterRearrangeX
//         bit 31~0 - afterRearrangeX[63:32] (Read/Write)
// 0x06c : reserved
// 0x070 : Data signal of afterPad1
//         bit 31~0 - afterPad1[31:0] (Read/Write)
// 0x074 : Data signal of afterPad1
//         bit 31~0 - afterPad1[63:32] (Read/Write)
// 0x078 : reserved
// 0x07c : Data signal of afterConv1
//         bit 31~0 - afterConv1[31:0] (Read/Write)
// 0x080 : Data signal of afterConv1
//         bit 31~0 - afterConv1[63:32] (Read/Write)
// 0x084 : reserved
// 0x088 : Data signal of kernel1
//         bit 31~0 - kernel1[31:0] (Read/Write)
// 0x08c : Data signal of kernel1
//         bit 31~0 - kernel1[63:32] (Read/Write)
// 0x090 : reserved
// 0x094 : Data signal of bias1
//         bit 31~0 - bias1[31:0] (Read/Write)
// 0x098 : Data signal of bias1
//         bit 31~0 - bias1[63:32] (Read/Write)
// 0x09c : reserved
// 0x0a0 : Data signal of in_qk
//         bit 31~0 - in_qk[31:0] (Read/Write)
// 0x0a4 : Data signal of in_qk
//         bit 31~0 - in_qk[63:32] (Read/Write)
// 0x0a8 : reserved
// 0x0ac : Data signal of in_q
//         bit 31~0 - in_q[31:0] (Read/Write)
// 0x0b0 : Data signal of in_q
//         bit 31~0 - in_q[63:32] (Read/Write)
// 0x0b4 : reserved
// 0x0b8 : Data signal of in_k
//         bit 31~0 - in_k[31:0] (Read/Write)
// 0x0bc : Data signal of in_k
//         bit 31~0 - in_k[63:32] (Read/Write)
// 0x0c0 : reserved
// 0x0c4 : Data signal of afterQKMultiplication
//         bit 31~0 - afterQKMultiplication[31:0] (Read/Write)
// 0x0c8 : Data signal of afterQKMultiplication
//         bit 31~0 - afterQKMultiplication[63:32] (Read/Write)
// 0x0cc : reserved
// 0x0d0 : Data signal of afterSoftmax
//         bit 31~0 - afterSoftmax[31:0] (Read/Write)
// 0x0d4 : Data signal of afterSoftmax
//         bit 31~0 - afterSoftmax[63:32] (Read/Write)
// 0x0d8 : reserved
// 0x0dc : Data signal of afterRearrangeX2
//         bit 31~0 - afterRearrangeX2[31:0] (Read/Write)
// 0x0e0 : Data signal of afterRearrangeX2
//         bit 31~0 - afterRearrangeX2[63:32] (Read/Write)
// 0x0e4 : reserved
// 0x0e8 : Data signal of afterQKXMultiplication
//         bit 31~0 - afterQKXMultiplication[31:0] (Read/Write)
// 0x0ec : Data signal of afterQKXMultiplication
//         bit 31~0 - afterQKXMultiplication[63:32] (Read/Write)
// 0x0f0 : reserved
// 0x0f4 : Data signal of afterRearrangeQKX
//         bit 31~0 - afterRearrangeQKX[31:0] (Read/Write)
// 0x0f8 : Data signal of afterRearrangeQKX
//         bit 31~0 - afterRearrangeQKX[63:32] (Read/Write)
// 0x0fc : reserved
// 0x100 : Data signal of afterPad2
//         bit 31~0 - afterPad2[31:0] (Read/Write)
// 0x104 : Data signal of afterPad2
//         bit 31~0 - afterPad2[63:32] (Read/Write)
// 0x108 : reserved
// 0x10c : Data signal of afterConv2
//         bit 31~0 - afterConv2[31:0] (Read/Write)
// 0x110 : Data signal of afterConv2
//         bit 31~0 - afterConv2[63:32] (Read/Write)
// 0x114 : reserved
// 0x118 : Data signal of kernel2
//         bit 31~0 - kernel2[31:0] (Read/Write)
// 0x11c : Data signal of kernel2
//         bit 31~0 - kernel2[63:32] (Read/Write)
// 0x120 : reserved
// 0x124 : Data signal of bias2
//         bit 31~0 - bias2[31:0] (Read/Write)
// 0x128 : Data signal of bias2
//         bit 31~0 - bias2[63:32] (Read/Write)
// 0x12c : reserved
// 0x130 : Data signal of afterAct2
//         bit 31~0 - afterAct2[31:0] (Read/Write)
// 0x134 : Data signal of afterAct2
//         bit 31~0 - afterAct2[63:32] (Read/Write)
// 0x138 : reserved
// 0x13c : Data signal of QKV
//         bit 31~0 - QKV[31:0] (Read/Write)
// 0x140 : Data signal of QKV
//         bit 31~0 - QKV[63:32] (Read/Write)
// 0x144 : reserved
// 0x148 : Data signal of buffer_out
//         bit 31~0 - buffer_out[31:0] (Read/Write)
// 0x14c : Data signal of buffer_out
//         bit 31~0 - buffer_out[63:32] (Read/Write)
// 0x150 : reserved
// 0x154 : Data signal of buffer_result
//         bit 31~0 - buffer_result[31:0] (Read/Write)
// 0x158 : Data signal of buffer_result
//         bit 31~0 - buffer_result[63:32] (Read/Write)
// 0x15c : reserved
// (SC = Self Clear, COR = Clear on Read, TOW = Toggle on Write, COH = Clear on Handshake)

#define CONTROL_ADDR_BUFFER_DATAIN_1_DATA        0x010
#define CONTROL_BITS_BUFFER_DATAIN_1_DATA        64
#define CONTROL_ADDR_AFTERNORM_DATA              0x01c
#define CONTROL_BITS_AFTERNORM_DATA              64
#define CONTROL_ADDR_NORM1_MEAN_DATA             0x028
#define CONTROL_BITS_NORM1_MEAN_DATA             64
#define CONTROL_ADDR_NORM1_VAR_DATA              0x034
#define CONTROL_BITS_NORM1_VAR_DATA              64
#define CONTROL_ADDR_NORM1_WEIGHT_DATA           0x040
#define CONTROL_BITS_NORM1_WEIGHT_DATA           64
#define CONTROL_ADDR_NORM1_BIAS_DATA             0x04c
#define CONTROL_BITS_NORM1_BIAS_DATA             64
#define CONTROL_ADDR_AFTERPAD_DATA               0x058
#define CONTROL_BITS_AFTERPAD_DATA               64
#define CONTROL_ADDR_AFTERREARRANGEX_DATA        0x064
#define CONTROL_BITS_AFTERREARRANGEX_DATA        64
#define CONTROL_ADDR_AFTERPAD1_DATA              0x070
#define CONTROL_BITS_AFTERPAD1_DATA              64
#define CONTROL_ADDR_AFTERCONV1_DATA             0x07c
#define CONTROL_BITS_AFTERCONV1_DATA             64
#define CONTROL_ADDR_KERNEL1_DATA                0x088
#define CONTROL_BITS_KERNEL1_DATA                64
#define CONTROL_ADDR_BIAS1_DATA                  0x094
#define CONTROL_BITS_BIAS1_DATA                  64
#define CONTROL_ADDR_IN_QK_DATA                  0x0a0
#define CONTROL_BITS_IN_QK_DATA                  64
#define CONTROL_ADDR_IN_Q_DATA                   0x0ac
#define CONTROL_BITS_IN_Q_DATA                   64
#define CONTROL_ADDR_IN_K_DATA                   0x0b8
#define CONTROL_BITS_IN_K_DATA                   64
#define CONTROL_ADDR_AFTERQKMULTIPLICATION_DATA  0x0c4
#define CONTROL_BITS_AFTERQKMULTIPLICATION_DATA  64
#define CONTROL_ADDR_AFTERSOFTMAX_DATA           0x0d0
#define CONTROL_BITS_AFTERSOFTMAX_DATA           64
#define CONTROL_ADDR_AFTERREARRANGEX2_DATA       0x0dc
#define CONTROL_BITS_AFTERREARRANGEX2_DATA       64
#define CONTROL_ADDR_AFTERQKXMULTIPLICATION_DATA 0x0e8
#define CONTROL_BITS_AFTERQKXMULTIPLICATION_DATA 64
#define CONTROL_ADDR_AFTERREARRANGEQKX_DATA      0x0f4
#define CONTROL_BITS_AFTERREARRANGEQKX_DATA      64
#define CONTROL_ADDR_AFTERPAD2_DATA              0x100
#define CONTROL_BITS_AFTERPAD2_DATA              64
#define CONTROL_ADDR_AFTERCONV2_DATA             0x10c
#define CONTROL_BITS_AFTERCONV2_DATA             64
#define CONTROL_ADDR_KERNEL2_DATA                0x118
#define CONTROL_BITS_KERNEL2_DATA                64
#define CONTROL_ADDR_BIAS2_DATA                  0x124
#define CONTROL_BITS_BIAS2_DATA                  64
#define CONTROL_ADDR_AFTERACT2_DATA              0x130
#define CONTROL_BITS_AFTERACT2_DATA              64
#define CONTROL_ADDR_QKV_DATA                    0x13c
#define CONTROL_BITS_QKV_DATA                    64
#define CONTROL_ADDR_BUFFER_OUT_DATA             0x148
#define CONTROL_BITS_BUFFER_OUT_DATA             64
#define CONTROL_ADDR_BUFFER_RESULT_DATA          0x154
#define CONTROL_BITS_BUFFER_RESULT_DATA          64
