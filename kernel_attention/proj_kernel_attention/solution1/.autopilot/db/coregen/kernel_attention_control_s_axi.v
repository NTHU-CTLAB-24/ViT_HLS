// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2022.1 (64-bit)
// Tool Version Limit: 2022.04
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// ==============================================================
`timescale 1ns/1ps
module kernel_attention_control_s_axi
#(parameter
    C_S_AXI_ADDR_WIDTH = 9,
    C_S_AXI_DATA_WIDTH = 32
)(
    input  wire                          ACLK,
    input  wire                          ARESET,
    input  wire                          ACLK_EN,
    input  wire [C_S_AXI_ADDR_WIDTH-1:0] AWADDR,
    input  wire                          AWVALID,
    output wire                          AWREADY,
    input  wire [C_S_AXI_DATA_WIDTH-1:0] WDATA,
    input  wire [C_S_AXI_DATA_WIDTH/8-1:0] WSTRB,
    input  wire                          WVALID,
    output wire                          WREADY,
    output wire [1:0]                    BRESP,
    output wire                          BVALID,
    input  wire                          BREADY,
    input  wire [C_S_AXI_ADDR_WIDTH-1:0] ARADDR,
    input  wire                          ARVALID,
    output wire                          ARREADY,
    output wire [C_S_AXI_DATA_WIDTH-1:0] RDATA,
    output wire [1:0]                    RRESP,
    output wire                          RVALID,
    input  wire                          RREADY,
    output wire [63:0]                   buffer_DataIn_1,
    output wire [63:0]                   afterNorm,
    output wire [63:0]                   norm1_mean,
    output wire [63:0]                   norm1_var,
    output wire [63:0]                   norm1_weight,
    output wire [63:0]                   norm1_bias,
    output wire [63:0]                   afterPad,
    output wire [63:0]                   afterRearrangeX,
    output wire [63:0]                   afterPad1,
    output wire [63:0]                   afterConv1,
    output wire [63:0]                   kernel1,
    output wire [63:0]                   bias1,
    output wire [63:0]                   in_qk,
    output wire [63:0]                   in_q,
    output wire [63:0]                   in_k,
    output wire [63:0]                   afterQKMultiplication,
    output wire [63:0]                   afterSoftmax,
    output wire [63:0]                   afterRearrangeX2,
    output wire [63:0]                   afterQKXMultiplication,
    output wire [63:0]                   afterRearrangeQKX,
    output wire [63:0]                   afterPad2,
    output wire [63:0]                   afterConv2,
    output wire [63:0]                   kernel2,
    output wire [63:0]                   bias2,
    output wire [63:0]                   afterAct2,
    output wire [63:0]                   QKV,
    output wire [63:0]                   buffer_out,
    output wire [63:0]                   buffer_result
);
//------------------------Address Info-------------------
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

//------------------------Parameter----------------------
localparam
    ADDR_BUFFER_DATAIN_1_DATA_0        = 9'h010,
    ADDR_BUFFER_DATAIN_1_DATA_1        = 9'h014,
    ADDR_BUFFER_DATAIN_1_CTRL          = 9'h018,
    ADDR_AFTERNORM_DATA_0              = 9'h01c,
    ADDR_AFTERNORM_DATA_1              = 9'h020,
    ADDR_AFTERNORM_CTRL                = 9'h024,
    ADDR_NORM1_MEAN_DATA_0             = 9'h028,
    ADDR_NORM1_MEAN_DATA_1             = 9'h02c,
    ADDR_NORM1_MEAN_CTRL               = 9'h030,
    ADDR_NORM1_VAR_DATA_0              = 9'h034,
    ADDR_NORM1_VAR_DATA_1              = 9'h038,
    ADDR_NORM1_VAR_CTRL                = 9'h03c,
    ADDR_NORM1_WEIGHT_DATA_0           = 9'h040,
    ADDR_NORM1_WEIGHT_DATA_1           = 9'h044,
    ADDR_NORM1_WEIGHT_CTRL             = 9'h048,
    ADDR_NORM1_BIAS_DATA_0             = 9'h04c,
    ADDR_NORM1_BIAS_DATA_1             = 9'h050,
    ADDR_NORM1_BIAS_CTRL               = 9'h054,
    ADDR_AFTERPAD_DATA_0               = 9'h058,
    ADDR_AFTERPAD_DATA_1               = 9'h05c,
    ADDR_AFTERPAD_CTRL                 = 9'h060,
    ADDR_AFTERREARRANGEX_DATA_0        = 9'h064,
    ADDR_AFTERREARRANGEX_DATA_1        = 9'h068,
    ADDR_AFTERREARRANGEX_CTRL          = 9'h06c,
    ADDR_AFTERPAD1_DATA_0              = 9'h070,
    ADDR_AFTERPAD1_DATA_1              = 9'h074,
    ADDR_AFTERPAD1_CTRL                = 9'h078,
    ADDR_AFTERCONV1_DATA_0             = 9'h07c,
    ADDR_AFTERCONV1_DATA_1             = 9'h080,
    ADDR_AFTERCONV1_CTRL               = 9'h084,
    ADDR_KERNEL1_DATA_0                = 9'h088,
    ADDR_KERNEL1_DATA_1                = 9'h08c,
    ADDR_KERNEL1_CTRL                  = 9'h090,
    ADDR_BIAS1_DATA_0                  = 9'h094,
    ADDR_BIAS1_DATA_1                  = 9'h098,
    ADDR_BIAS1_CTRL                    = 9'h09c,
    ADDR_IN_QK_DATA_0                  = 9'h0a0,
    ADDR_IN_QK_DATA_1                  = 9'h0a4,
    ADDR_IN_QK_CTRL                    = 9'h0a8,
    ADDR_IN_Q_DATA_0                   = 9'h0ac,
    ADDR_IN_Q_DATA_1                   = 9'h0b0,
    ADDR_IN_Q_CTRL                     = 9'h0b4,
    ADDR_IN_K_DATA_0                   = 9'h0b8,
    ADDR_IN_K_DATA_1                   = 9'h0bc,
    ADDR_IN_K_CTRL                     = 9'h0c0,
    ADDR_AFTERQKMULTIPLICATION_DATA_0  = 9'h0c4,
    ADDR_AFTERQKMULTIPLICATION_DATA_1  = 9'h0c8,
    ADDR_AFTERQKMULTIPLICATION_CTRL    = 9'h0cc,
    ADDR_AFTERSOFTMAX_DATA_0           = 9'h0d0,
    ADDR_AFTERSOFTMAX_DATA_1           = 9'h0d4,
    ADDR_AFTERSOFTMAX_CTRL             = 9'h0d8,
    ADDR_AFTERREARRANGEX2_DATA_0       = 9'h0dc,
    ADDR_AFTERREARRANGEX2_DATA_1       = 9'h0e0,
    ADDR_AFTERREARRANGEX2_CTRL         = 9'h0e4,
    ADDR_AFTERQKXMULTIPLICATION_DATA_0 = 9'h0e8,
    ADDR_AFTERQKXMULTIPLICATION_DATA_1 = 9'h0ec,
    ADDR_AFTERQKXMULTIPLICATION_CTRL   = 9'h0f0,
    ADDR_AFTERREARRANGEQKX_DATA_0      = 9'h0f4,
    ADDR_AFTERREARRANGEQKX_DATA_1      = 9'h0f8,
    ADDR_AFTERREARRANGEQKX_CTRL        = 9'h0fc,
    ADDR_AFTERPAD2_DATA_0              = 9'h100,
    ADDR_AFTERPAD2_DATA_1              = 9'h104,
    ADDR_AFTERPAD2_CTRL                = 9'h108,
    ADDR_AFTERCONV2_DATA_0             = 9'h10c,
    ADDR_AFTERCONV2_DATA_1             = 9'h110,
    ADDR_AFTERCONV2_CTRL               = 9'h114,
    ADDR_KERNEL2_DATA_0                = 9'h118,
    ADDR_KERNEL2_DATA_1                = 9'h11c,
    ADDR_KERNEL2_CTRL                  = 9'h120,
    ADDR_BIAS2_DATA_0                  = 9'h124,
    ADDR_BIAS2_DATA_1                  = 9'h128,
    ADDR_BIAS2_CTRL                    = 9'h12c,
    ADDR_AFTERACT2_DATA_0              = 9'h130,
    ADDR_AFTERACT2_DATA_1              = 9'h134,
    ADDR_AFTERACT2_CTRL                = 9'h138,
    ADDR_QKV_DATA_0                    = 9'h13c,
    ADDR_QKV_DATA_1                    = 9'h140,
    ADDR_QKV_CTRL                      = 9'h144,
    ADDR_BUFFER_OUT_DATA_0             = 9'h148,
    ADDR_BUFFER_OUT_DATA_1             = 9'h14c,
    ADDR_BUFFER_OUT_CTRL               = 9'h150,
    ADDR_BUFFER_RESULT_DATA_0          = 9'h154,
    ADDR_BUFFER_RESULT_DATA_1          = 9'h158,
    ADDR_BUFFER_RESULT_CTRL            = 9'h15c,
    WRIDLE                             = 2'd0,
    WRDATA                             = 2'd1,
    WRRESP                             = 2'd2,
    WRRESET                            = 2'd3,
    RDIDLE                             = 2'd0,
    RDDATA                             = 2'd1,
    RDRESET                            = 2'd2,
    ADDR_BITS                = 9;

//------------------------Local signal-------------------
    reg  [1:0]                    wstate = WRRESET;
    reg  [1:0]                    wnext;
    reg  [ADDR_BITS-1:0]          waddr;
    wire [C_S_AXI_DATA_WIDTH-1:0] wmask;
    wire                          aw_hs;
    wire                          w_hs;
    reg  [1:0]                    rstate = RDRESET;
    reg  [1:0]                    rnext;
    reg  [C_S_AXI_DATA_WIDTH-1:0] rdata;
    wire                          ar_hs;
    wire [ADDR_BITS-1:0]          raddr;
    // internal registers
    reg  [63:0]                   int_buffer_DataIn_1 = 'b0;
    reg  [63:0]                   int_afterNorm = 'b0;
    reg  [63:0]                   int_norm1_mean = 'b0;
    reg  [63:0]                   int_norm1_var = 'b0;
    reg  [63:0]                   int_norm1_weight = 'b0;
    reg  [63:0]                   int_norm1_bias = 'b0;
    reg  [63:0]                   int_afterPad = 'b0;
    reg  [63:0]                   int_afterRearrangeX = 'b0;
    reg  [63:0]                   int_afterPad1 = 'b0;
    reg  [63:0]                   int_afterConv1 = 'b0;
    reg  [63:0]                   int_kernel1 = 'b0;
    reg  [63:0]                   int_bias1 = 'b0;
    reg  [63:0]                   int_in_qk = 'b0;
    reg  [63:0]                   int_in_q = 'b0;
    reg  [63:0]                   int_in_k = 'b0;
    reg  [63:0]                   int_afterQKMultiplication = 'b0;
    reg  [63:0]                   int_afterSoftmax = 'b0;
    reg  [63:0]                   int_afterRearrangeX2 = 'b0;
    reg  [63:0]                   int_afterQKXMultiplication = 'b0;
    reg  [63:0]                   int_afterRearrangeQKX = 'b0;
    reg  [63:0]                   int_afterPad2 = 'b0;
    reg  [63:0]                   int_afterConv2 = 'b0;
    reg  [63:0]                   int_kernel2 = 'b0;
    reg  [63:0]                   int_bias2 = 'b0;
    reg  [63:0]                   int_afterAct2 = 'b0;
    reg  [63:0]                   int_QKV = 'b0;
    reg  [63:0]                   int_buffer_out = 'b0;
    reg  [63:0]                   int_buffer_result = 'b0;

//------------------------Instantiation------------------


//------------------------AXI write fsm------------------
assign AWREADY = (wstate == WRIDLE);
assign WREADY  = (wstate == WRDATA);
assign BRESP   = 2'b00;  // OKAY
assign BVALID  = (wstate == WRRESP);
assign wmask   = { {8{WSTRB[3]}}, {8{WSTRB[2]}}, {8{WSTRB[1]}}, {8{WSTRB[0]}} };
assign aw_hs   = AWVALID & AWREADY;
assign w_hs    = WVALID & WREADY;

// wstate
always @(posedge ACLK) begin
    if (ARESET)
        wstate <= WRRESET;
    else if (ACLK_EN)
        wstate <= wnext;
end

// wnext
always @(*) begin
    case (wstate)
        WRIDLE:
            if (AWVALID)
                wnext = WRDATA;
            else
                wnext = WRIDLE;
        WRDATA:
            if (WVALID)
                wnext = WRRESP;
            else
                wnext = WRDATA;
        WRRESP:
            if (BREADY)
                wnext = WRIDLE;
            else
                wnext = WRRESP;
        default:
            wnext = WRIDLE;
    endcase
end

// waddr
always @(posedge ACLK) begin
    if (ACLK_EN) begin
        if (aw_hs)
            waddr <= AWADDR[ADDR_BITS-1:0];
    end
end

//------------------------AXI read fsm-------------------
assign ARREADY = (rstate == RDIDLE);
assign RDATA   = rdata;
assign RRESP   = 2'b00;  // OKAY
assign RVALID  = (rstate == RDDATA);
assign ar_hs   = ARVALID & ARREADY;
assign raddr   = ARADDR[ADDR_BITS-1:0];

// rstate
always @(posedge ACLK) begin
    if (ARESET)
        rstate <= RDRESET;
    else if (ACLK_EN)
        rstate <= rnext;
end

// rnext
always @(*) begin
    case (rstate)
        RDIDLE:
            if (ARVALID)
                rnext = RDDATA;
            else
                rnext = RDIDLE;
        RDDATA:
            if (RREADY & RVALID)
                rnext = RDIDLE;
            else
                rnext = RDDATA;
        default:
            rnext = RDIDLE;
    endcase
end

// rdata
always @(posedge ACLK) begin
    if (ACLK_EN) begin
        if (ar_hs) begin
            rdata <= 'b0;
            case (raddr)
                ADDR_BUFFER_DATAIN_1_DATA_0: begin
                    rdata <= int_buffer_DataIn_1[31:0];
                end
                ADDR_BUFFER_DATAIN_1_DATA_1: begin
                    rdata <= int_buffer_DataIn_1[63:32];
                end
                ADDR_AFTERNORM_DATA_0: begin
                    rdata <= int_afterNorm[31:0];
                end
                ADDR_AFTERNORM_DATA_1: begin
                    rdata <= int_afterNorm[63:32];
                end
                ADDR_NORM1_MEAN_DATA_0: begin
                    rdata <= int_norm1_mean[31:0];
                end
                ADDR_NORM1_MEAN_DATA_1: begin
                    rdata <= int_norm1_mean[63:32];
                end
                ADDR_NORM1_VAR_DATA_0: begin
                    rdata <= int_norm1_var[31:0];
                end
                ADDR_NORM1_VAR_DATA_1: begin
                    rdata <= int_norm1_var[63:32];
                end
                ADDR_NORM1_WEIGHT_DATA_0: begin
                    rdata <= int_norm1_weight[31:0];
                end
                ADDR_NORM1_WEIGHT_DATA_1: begin
                    rdata <= int_norm1_weight[63:32];
                end
                ADDR_NORM1_BIAS_DATA_0: begin
                    rdata <= int_norm1_bias[31:0];
                end
                ADDR_NORM1_BIAS_DATA_1: begin
                    rdata <= int_norm1_bias[63:32];
                end
                ADDR_AFTERPAD_DATA_0: begin
                    rdata <= int_afterPad[31:0];
                end
                ADDR_AFTERPAD_DATA_1: begin
                    rdata <= int_afterPad[63:32];
                end
                ADDR_AFTERREARRANGEX_DATA_0: begin
                    rdata <= int_afterRearrangeX[31:0];
                end
                ADDR_AFTERREARRANGEX_DATA_1: begin
                    rdata <= int_afterRearrangeX[63:32];
                end
                ADDR_AFTERPAD1_DATA_0: begin
                    rdata <= int_afterPad1[31:0];
                end
                ADDR_AFTERPAD1_DATA_1: begin
                    rdata <= int_afterPad1[63:32];
                end
                ADDR_AFTERCONV1_DATA_0: begin
                    rdata <= int_afterConv1[31:0];
                end
                ADDR_AFTERCONV1_DATA_1: begin
                    rdata <= int_afterConv1[63:32];
                end
                ADDR_KERNEL1_DATA_0: begin
                    rdata <= int_kernel1[31:0];
                end
                ADDR_KERNEL1_DATA_1: begin
                    rdata <= int_kernel1[63:32];
                end
                ADDR_BIAS1_DATA_0: begin
                    rdata <= int_bias1[31:0];
                end
                ADDR_BIAS1_DATA_1: begin
                    rdata <= int_bias1[63:32];
                end
                ADDR_IN_QK_DATA_0: begin
                    rdata <= int_in_qk[31:0];
                end
                ADDR_IN_QK_DATA_1: begin
                    rdata <= int_in_qk[63:32];
                end
                ADDR_IN_Q_DATA_0: begin
                    rdata <= int_in_q[31:0];
                end
                ADDR_IN_Q_DATA_1: begin
                    rdata <= int_in_q[63:32];
                end
                ADDR_IN_K_DATA_0: begin
                    rdata <= int_in_k[31:0];
                end
                ADDR_IN_K_DATA_1: begin
                    rdata <= int_in_k[63:32];
                end
                ADDR_AFTERQKMULTIPLICATION_DATA_0: begin
                    rdata <= int_afterQKMultiplication[31:0];
                end
                ADDR_AFTERQKMULTIPLICATION_DATA_1: begin
                    rdata <= int_afterQKMultiplication[63:32];
                end
                ADDR_AFTERSOFTMAX_DATA_0: begin
                    rdata <= int_afterSoftmax[31:0];
                end
                ADDR_AFTERSOFTMAX_DATA_1: begin
                    rdata <= int_afterSoftmax[63:32];
                end
                ADDR_AFTERREARRANGEX2_DATA_0: begin
                    rdata <= int_afterRearrangeX2[31:0];
                end
                ADDR_AFTERREARRANGEX2_DATA_1: begin
                    rdata <= int_afterRearrangeX2[63:32];
                end
                ADDR_AFTERQKXMULTIPLICATION_DATA_0: begin
                    rdata <= int_afterQKXMultiplication[31:0];
                end
                ADDR_AFTERQKXMULTIPLICATION_DATA_1: begin
                    rdata <= int_afterQKXMultiplication[63:32];
                end
                ADDR_AFTERREARRANGEQKX_DATA_0: begin
                    rdata <= int_afterRearrangeQKX[31:0];
                end
                ADDR_AFTERREARRANGEQKX_DATA_1: begin
                    rdata <= int_afterRearrangeQKX[63:32];
                end
                ADDR_AFTERPAD2_DATA_0: begin
                    rdata <= int_afterPad2[31:0];
                end
                ADDR_AFTERPAD2_DATA_1: begin
                    rdata <= int_afterPad2[63:32];
                end
                ADDR_AFTERCONV2_DATA_0: begin
                    rdata <= int_afterConv2[31:0];
                end
                ADDR_AFTERCONV2_DATA_1: begin
                    rdata <= int_afterConv2[63:32];
                end
                ADDR_KERNEL2_DATA_0: begin
                    rdata <= int_kernel2[31:0];
                end
                ADDR_KERNEL2_DATA_1: begin
                    rdata <= int_kernel2[63:32];
                end
                ADDR_BIAS2_DATA_0: begin
                    rdata <= int_bias2[31:0];
                end
                ADDR_BIAS2_DATA_1: begin
                    rdata <= int_bias2[63:32];
                end
                ADDR_AFTERACT2_DATA_0: begin
                    rdata <= int_afterAct2[31:0];
                end
                ADDR_AFTERACT2_DATA_1: begin
                    rdata <= int_afterAct2[63:32];
                end
                ADDR_QKV_DATA_0: begin
                    rdata <= int_QKV[31:0];
                end
                ADDR_QKV_DATA_1: begin
                    rdata <= int_QKV[63:32];
                end
                ADDR_BUFFER_OUT_DATA_0: begin
                    rdata <= int_buffer_out[31:0];
                end
                ADDR_BUFFER_OUT_DATA_1: begin
                    rdata <= int_buffer_out[63:32];
                end
                ADDR_BUFFER_RESULT_DATA_0: begin
                    rdata <= int_buffer_result[31:0];
                end
                ADDR_BUFFER_RESULT_DATA_1: begin
                    rdata <= int_buffer_result[63:32];
                end
            endcase
        end
    end
end


//------------------------Register logic-----------------
assign buffer_DataIn_1        = int_buffer_DataIn_1;
assign afterNorm              = int_afterNorm;
assign norm1_mean             = int_norm1_mean;
assign norm1_var              = int_norm1_var;
assign norm1_weight           = int_norm1_weight;
assign norm1_bias             = int_norm1_bias;
assign afterPad               = int_afterPad;
assign afterRearrangeX        = int_afterRearrangeX;
assign afterPad1              = int_afterPad1;
assign afterConv1             = int_afterConv1;
assign kernel1                = int_kernel1;
assign bias1                  = int_bias1;
assign in_qk                  = int_in_qk;
assign in_q                   = int_in_q;
assign in_k                   = int_in_k;
assign afterQKMultiplication  = int_afterQKMultiplication;
assign afterSoftmax           = int_afterSoftmax;
assign afterRearrangeX2       = int_afterRearrangeX2;
assign afterQKXMultiplication = int_afterQKXMultiplication;
assign afterRearrangeQKX      = int_afterRearrangeQKX;
assign afterPad2              = int_afterPad2;
assign afterConv2             = int_afterConv2;
assign kernel2                = int_kernel2;
assign bias2                  = int_bias2;
assign afterAct2              = int_afterAct2;
assign QKV                    = int_QKV;
assign buffer_out             = int_buffer_out;
assign buffer_result          = int_buffer_result;
// int_buffer_DataIn_1[31:0]
always @(posedge ACLK) begin
    if (ARESET)
        int_buffer_DataIn_1[31:0] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_BUFFER_DATAIN_1_DATA_0)
            int_buffer_DataIn_1[31:0] <= (WDATA[31:0] & wmask) | (int_buffer_DataIn_1[31:0] & ~wmask);
    end
end

// int_buffer_DataIn_1[63:32]
always @(posedge ACLK) begin
    if (ARESET)
        int_buffer_DataIn_1[63:32] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_BUFFER_DATAIN_1_DATA_1)
            int_buffer_DataIn_1[63:32] <= (WDATA[31:0] & wmask) | (int_buffer_DataIn_1[63:32] & ~wmask);
    end
end

// int_afterNorm[31:0]
always @(posedge ACLK) begin
    if (ARESET)
        int_afterNorm[31:0] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_AFTERNORM_DATA_0)
            int_afterNorm[31:0] <= (WDATA[31:0] & wmask) | (int_afterNorm[31:0] & ~wmask);
    end
end

// int_afterNorm[63:32]
always @(posedge ACLK) begin
    if (ARESET)
        int_afterNorm[63:32] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_AFTERNORM_DATA_1)
            int_afterNorm[63:32] <= (WDATA[31:0] & wmask) | (int_afterNorm[63:32] & ~wmask);
    end
end

// int_norm1_mean[31:0]
always @(posedge ACLK) begin
    if (ARESET)
        int_norm1_mean[31:0] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_NORM1_MEAN_DATA_0)
            int_norm1_mean[31:0] <= (WDATA[31:0] & wmask) | (int_norm1_mean[31:0] & ~wmask);
    end
end

// int_norm1_mean[63:32]
always @(posedge ACLK) begin
    if (ARESET)
        int_norm1_mean[63:32] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_NORM1_MEAN_DATA_1)
            int_norm1_mean[63:32] <= (WDATA[31:0] & wmask) | (int_norm1_mean[63:32] & ~wmask);
    end
end

// int_norm1_var[31:0]
always @(posedge ACLK) begin
    if (ARESET)
        int_norm1_var[31:0] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_NORM1_VAR_DATA_0)
            int_norm1_var[31:0] <= (WDATA[31:0] & wmask) | (int_norm1_var[31:0] & ~wmask);
    end
end

// int_norm1_var[63:32]
always @(posedge ACLK) begin
    if (ARESET)
        int_norm1_var[63:32] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_NORM1_VAR_DATA_1)
            int_norm1_var[63:32] <= (WDATA[31:0] & wmask) | (int_norm1_var[63:32] & ~wmask);
    end
end

// int_norm1_weight[31:0]
always @(posedge ACLK) begin
    if (ARESET)
        int_norm1_weight[31:0] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_NORM1_WEIGHT_DATA_0)
            int_norm1_weight[31:0] <= (WDATA[31:0] & wmask) | (int_norm1_weight[31:0] & ~wmask);
    end
end

// int_norm1_weight[63:32]
always @(posedge ACLK) begin
    if (ARESET)
        int_norm1_weight[63:32] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_NORM1_WEIGHT_DATA_1)
            int_norm1_weight[63:32] <= (WDATA[31:0] & wmask) | (int_norm1_weight[63:32] & ~wmask);
    end
end

// int_norm1_bias[31:0]
always @(posedge ACLK) begin
    if (ARESET)
        int_norm1_bias[31:0] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_NORM1_BIAS_DATA_0)
            int_norm1_bias[31:0] <= (WDATA[31:0] & wmask) | (int_norm1_bias[31:0] & ~wmask);
    end
end

// int_norm1_bias[63:32]
always @(posedge ACLK) begin
    if (ARESET)
        int_norm1_bias[63:32] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_NORM1_BIAS_DATA_1)
            int_norm1_bias[63:32] <= (WDATA[31:0] & wmask) | (int_norm1_bias[63:32] & ~wmask);
    end
end

// int_afterPad[31:0]
always @(posedge ACLK) begin
    if (ARESET)
        int_afterPad[31:0] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_AFTERPAD_DATA_0)
            int_afterPad[31:0] <= (WDATA[31:0] & wmask) | (int_afterPad[31:0] & ~wmask);
    end
end

// int_afterPad[63:32]
always @(posedge ACLK) begin
    if (ARESET)
        int_afterPad[63:32] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_AFTERPAD_DATA_1)
            int_afterPad[63:32] <= (WDATA[31:0] & wmask) | (int_afterPad[63:32] & ~wmask);
    end
end

// int_afterRearrangeX[31:0]
always @(posedge ACLK) begin
    if (ARESET)
        int_afterRearrangeX[31:0] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_AFTERREARRANGEX_DATA_0)
            int_afterRearrangeX[31:0] <= (WDATA[31:0] & wmask) | (int_afterRearrangeX[31:0] & ~wmask);
    end
end

// int_afterRearrangeX[63:32]
always @(posedge ACLK) begin
    if (ARESET)
        int_afterRearrangeX[63:32] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_AFTERREARRANGEX_DATA_1)
            int_afterRearrangeX[63:32] <= (WDATA[31:0] & wmask) | (int_afterRearrangeX[63:32] & ~wmask);
    end
end

// int_afterPad1[31:0]
always @(posedge ACLK) begin
    if (ARESET)
        int_afterPad1[31:0] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_AFTERPAD1_DATA_0)
            int_afterPad1[31:0] <= (WDATA[31:0] & wmask) | (int_afterPad1[31:0] & ~wmask);
    end
end

// int_afterPad1[63:32]
always @(posedge ACLK) begin
    if (ARESET)
        int_afterPad1[63:32] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_AFTERPAD1_DATA_1)
            int_afterPad1[63:32] <= (WDATA[31:0] & wmask) | (int_afterPad1[63:32] & ~wmask);
    end
end

// int_afterConv1[31:0]
always @(posedge ACLK) begin
    if (ARESET)
        int_afterConv1[31:0] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_AFTERCONV1_DATA_0)
            int_afterConv1[31:0] <= (WDATA[31:0] & wmask) | (int_afterConv1[31:0] & ~wmask);
    end
end

// int_afterConv1[63:32]
always @(posedge ACLK) begin
    if (ARESET)
        int_afterConv1[63:32] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_AFTERCONV1_DATA_1)
            int_afterConv1[63:32] <= (WDATA[31:0] & wmask) | (int_afterConv1[63:32] & ~wmask);
    end
end

// int_kernel1[31:0]
always @(posedge ACLK) begin
    if (ARESET)
        int_kernel1[31:0] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_KERNEL1_DATA_0)
            int_kernel1[31:0] <= (WDATA[31:0] & wmask) | (int_kernel1[31:0] & ~wmask);
    end
end

// int_kernel1[63:32]
always @(posedge ACLK) begin
    if (ARESET)
        int_kernel1[63:32] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_KERNEL1_DATA_1)
            int_kernel1[63:32] <= (WDATA[31:0] & wmask) | (int_kernel1[63:32] & ~wmask);
    end
end

// int_bias1[31:0]
always @(posedge ACLK) begin
    if (ARESET)
        int_bias1[31:0] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_BIAS1_DATA_0)
            int_bias1[31:0] <= (WDATA[31:0] & wmask) | (int_bias1[31:0] & ~wmask);
    end
end

// int_bias1[63:32]
always @(posedge ACLK) begin
    if (ARESET)
        int_bias1[63:32] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_BIAS1_DATA_1)
            int_bias1[63:32] <= (WDATA[31:0] & wmask) | (int_bias1[63:32] & ~wmask);
    end
end

// int_in_qk[31:0]
always @(posedge ACLK) begin
    if (ARESET)
        int_in_qk[31:0] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_IN_QK_DATA_0)
            int_in_qk[31:0] <= (WDATA[31:0] & wmask) | (int_in_qk[31:0] & ~wmask);
    end
end

// int_in_qk[63:32]
always @(posedge ACLK) begin
    if (ARESET)
        int_in_qk[63:32] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_IN_QK_DATA_1)
            int_in_qk[63:32] <= (WDATA[31:0] & wmask) | (int_in_qk[63:32] & ~wmask);
    end
end

// int_in_q[31:0]
always @(posedge ACLK) begin
    if (ARESET)
        int_in_q[31:0] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_IN_Q_DATA_0)
            int_in_q[31:0] <= (WDATA[31:0] & wmask) | (int_in_q[31:0] & ~wmask);
    end
end

// int_in_q[63:32]
always @(posedge ACLK) begin
    if (ARESET)
        int_in_q[63:32] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_IN_Q_DATA_1)
            int_in_q[63:32] <= (WDATA[31:0] & wmask) | (int_in_q[63:32] & ~wmask);
    end
end

// int_in_k[31:0]
always @(posedge ACLK) begin
    if (ARESET)
        int_in_k[31:0] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_IN_K_DATA_0)
            int_in_k[31:0] <= (WDATA[31:0] & wmask) | (int_in_k[31:0] & ~wmask);
    end
end

// int_in_k[63:32]
always @(posedge ACLK) begin
    if (ARESET)
        int_in_k[63:32] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_IN_K_DATA_1)
            int_in_k[63:32] <= (WDATA[31:0] & wmask) | (int_in_k[63:32] & ~wmask);
    end
end

// int_afterQKMultiplication[31:0]
always @(posedge ACLK) begin
    if (ARESET)
        int_afterQKMultiplication[31:0] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_AFTERQKMULTIPLICATION_DATA_0)
            int_afterQKMultiplication[31:0] <= (WDATA[31:0] & wmask) | (int_afterQKMultiplication[31:0] & ~wmask);
    end
end

// int_afterQKMultiplication[63:32]
always @(posedge ACLK) begin
    if (ARESET)
        int_afterQKMultiplication[63:32] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_AFTERQKMULTIPLICATION_DATA_1)
            int_afterQKMultiplication[63:32] <= (WDATA[31:0] & wmask) | (int_afterQKMultiplication[63:32] & ~wmask);
    end
end

// int_afterSoftmax[31:0]
always @(posedge ACLK) begin
    if (ARESET)
        int_afterSoftmax[31:0] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_AFTERSOFTMAX_DATA_0)
            int_afterSoftmax[31:0] <= (WDATA[31:0] & wmask) | (int_afterSoftmax[31:0] & ~wmask);
    end
end

// int_afterSoftmax[63:32]
always @(posedge ACLK) begin
    if (ARESET)
        int_afterSoftmax[63:32] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_AFTERSOFTMAX_DATA_1)
            int_afterSoftmax[63:32] <= (WDATA[31:0] & wmask) | (int_afterSoftmax[63:32] & ~wmask);
    end
end

// int_afterRearrangeX2[31:0]
always @(posedge ACLK) begin
    if (ARESET)
        int_afterRearrangeX2[31:0] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_AFTERREARRANGEX2_DATA_0)
            int_afterRearrangeX2[31:0] <= (WDATA[31:0] & wmask) | (int_afterRearrangeX2[31:0] & ~wmask);
    end
end

// int_afterRearrangeX2[63:32]
always @(posedge ACLK) begin
    if (ARESET)
        int_afterRearrangeX2[63:32] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_AFTERREARRANGEX2_DATA_1)
            int_afterRearrangeX2[63:32] <= (WDATA[31:0] & wmask) | (int_afterRearrangeX2[63:32] & ~wmask);
    end
end

// int_afterQKXMultiplication[31:0]
always @(posedge ACLK) begin
    if (ARESET)
        int_afterQKXMultiplication[31:0] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_AFTERQKXMULTIPLICATION_DATA_0)
            int_afterQKXMultiplication[31:0] <= (WDATA[31:0] & wmask) | (int_afterQKXMultiplication[31:0] & ~wmask);
    end
end

// int_afterQKXMultiplication[63:32]
always @(posedge ACLK) begin
    if (ARESET)
        int_afterQKXMultiplication[63:32] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_AFTERQKXMULTIPLICATION_DATA_1)
            int_afterQKXMultiplication[63:32] <= (WDATA[31:0] & wmask) | (int_afterQKXMultiplication[63:32] & ~wmask);
    end
end

// int_afterRearrangeQKX[31:0]
always @(posedge ACLK) begin
    if (ARESET)
        int_afterRearrangeQKX[31:0] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_AFTERREARRANGEQKX_DATA_0)
            int_afterRearrangeQKX[31:0] <= (WDATA[31:0] & wmask) | (int_afterRearrangeQKX[31:0] & ~wmask);
    end
end

// int_afterRearrangeQKX[63:32]
always @(posedge ACLK) begin
    if (ARESET)
        int_afterRearrangeQKX[63:32] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_AFTERREARRANGEQKX_DATA_1)
            int_afterRearrangeQKX[63:32] <= (WDATA[31:0] & wmask) | (int_afterRearrangeQKX[63:32] & ~wmask);
    end
end

// int_afterPad2[31:0]
always @(posedge ACLK) begin
    if (ARESET)
        int_afterPad2[31:0] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_AFTERPAD2_DATA_0)
            int_afterPad2[31:0] <= (WDATA[31:0] & wmask) | (int_afterPad2[31:0] & ~wmask);
    end
end

// int_afterPad2[63:32]
always @(posedge ACLK) begin
    if (ARESET)
        int_afterPad2[63:32] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_AFTERPAD2_DATA_1)
            int_afterPad2[63:32] <= (WDATA[31:0] & wmask) | (int_afterPad2[63:32] & ~wmask);
    end
end

// int_afterConv2[31:0]
always @(posedge ACLK) begin
    if (ARESET)
        int_afterConv2[31:0] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_AFTERCONV2_DATA_0)
            int_afterConv2[31:0] <= (WDATA[31:0] & wmask) | (int_afterConv2[31:0] & ~wmask);
    end
end

// int_afterConv2[63:32]
always @(posedge ACLK) begin
    if (ARESET)
        int_afterConv2[63:32] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_AFTERCONV2_DATA_1)
            int_afterConv2[63:32] <= (WDATA[31:0] & wmask) | (int_afterConv2[63:32] & ~wmask);
    end
end

// int_kernel2[31:0]
always @(posedge ACLK) begin
    if (ARESET)
        int_kernel2[31:0] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_KERNEL2_DATA_0)
            int_kernel2[31:0] <= (WDATA[31:0] & wmask) | (int_kernel2[31:0] & ~wmask);
    end
end

// int_kernel2[63:32]
always @(posedge ACLK) begin
    if (ARESET)
        int_kernel2[63:32] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_KERNEL2_DATA_1)
            int_kernel2[63:32] <= (WDATA[31:0] & wmask) | (int_kernel2[63:32] & ~wmask);
    end
end

// int_bias2[31:0]
always @(posedge ACLK) begin
    if (ARESET)
        int_bias2[31:0] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_BIAS2_DATA_0)
            int_bias2[31:0] <= (WDATA[31:0] & wmask) | (int_bias2[31:0] & ~wmask);
    end
end

// int_bias2[63:32]
always @(posedge ACLK) begin
    if (ARESET)
        int_bias2[63:32] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_BIAS2_DATA_1)
            int_bias2[63:32] <= (WDATA[31:0] & wmask) | (int_bias2[63:32] & ~wmask);
    end
end

// int_afterAct2[31:0]
always @(posedge ACLK) begin
    if (ARESET)
        int_afterAct2[31:0] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_AFTERACT2_DATA_0)
            int_afterAct2[31:0] <= (WDATA[31:0] & wmask) | (int_afterAct2[31:0] & ~wmask);
    end
end

// int_afterAct2[63:32]
always @(posedge ACLK) begin
    if (ARESET)
        int_afterAct2[63:32] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_AFTERACT2_DATA_1)
            int_afterAct2[63:32] <= (WDATA[31:0] & wmask) | (int_afterAct2[63:32] & ~wmask);
    end
end

// int_QKV[31:0]
always @(posedge ACLK) begin
    if (ARESET)
        int_QKV[31:0] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_QKV_DATA_0)
            int_QKV[31:0] <= (WDATA[31:0] & wmask) | (int_QKV[31:0] & ~wmask);
    end
end

// int_QKV[63:32]
always @(posedge ACLK) begin
    if (ARESET)
        int_QKV[63:32] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_QKV_DATA_1)
            int_QKV[63:32] <= (WDATA[31:0] & wmask) | (int_QKV[63:32] & ~wmask);
    end
end

// int_buffer_out[31:0]
always @(posedge ACLK) begin
    if (ARESET)
        int_buffer_out[31:0] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_BUFFER_OUT_DATA_0)
            int_buffer_out[31:0] <= (WDATA[31:0] & wmask) | (int_buffer_out[31:0] & ~wmask);
    end
end

// int_buffer_out[63:32]
always @(posedge ACLK) begin
    if (ARESET)
        int_buffer_out[63:32] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_BUFFER_OUT_DATA_1)
            int_buffer_out[63:32] <= (WDATA[31:0] & wmask) | (int_buffer_out[63:32] & ~wmask);
    end
end

// int_buffer_result[31:0]
always @(posedge ACLK) begin
    if (ARESET)
        int_buffer_result[31:0] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_BUFFER_RESULT_DATA_0)
            int_buffer_result[31:0] <= (WDATA[31:0] & wmask) | (int_buffer_result[31:0] & ~wmask);
    end
end

// int_buffer_result[63:32]
always @(posedge ACLK) begin
    if (ARESET)
        int_buffer_result[63:32] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_BUFFER_RESULT_DATA_1)
            int_buffer_result[63:32] <= (WDATA[31:0] & wmask) | (int_buffer_result[63:32] & ~wmask);
    end
end


//------------------------Memory logic-------------------

endmodule
