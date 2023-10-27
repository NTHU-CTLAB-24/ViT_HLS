// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2022.1 (64-bit)
// Tool Version Limit: 2022.04
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// ==============================================================
`timescale 1ns/1ps
module kernel_stage0_control_s_axi
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
    output wire [63:0]                   X_data,
    output wire [63:0]                   msp_conv_weight,
    output wire [63:0]                   msp_conv_bias,
    output wire [63:0]                   msp_norm_weight,
    output wire [63:0]                   msp_norm_bias,
    output wire [63:0]                   msp_norm_running_mean,
    output wire [63:0]                   msp_norm_running_var,
    output wire [63:0]                   dw_conv_weight,
    output wire [63:0]                   norm_1_weight,
    output wire [63:0]                   norm_1_bias,
    output wire [63:0]                   norm_1_running_mean,
    output wire [63:0]                   norm_1_running_var,
    output wire [63:0]                   se_conv_reduce_weight,
    output wire [63:0]                   se_conv_reduce_bias,
    output wire [63:0]                   se_conv_expand_weight,
    output wire [63:0]                   se_conv_expand_bias,
    output wire [63:0]                   proj_conv_weight,
    output wire [63:0]                   Y_msp_conv,
    output wire [63:0]                   Y_msp_norm,
    output wire [63:0]                   Y_dw_conv,
    output wire [63:0]                   Y_dw_norm,
    output wire [63:0]                   Y_dw_act,
    output wire [63:0]                   Y_se_mean,
    output wire [63:0]                   Y_se_reduce,
    output wire [63:0]                   Y_se_act,
    output wire [63:0]                   Y_se_expand,
    output wire [63:0]                   Y_se_sigmoid,
    output wire [63:0]                   Y_se,
    output wire [63:0]                   Y_proj
);
//------------------------Address Info-------------------
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
// 0x118 : Data signal of Y_se_mean
//         bit 31~0 - Y_se_mean[31:0] (Read/Write)
// 0x11c : Data signal of Y_se_mean
//         bit 31~0 - Y_se_mean[63:32] (Read/Write)
// 0x120 : reserved
// 0x124 : Data signal of Y_se_reduce
//         bit 31~0 - Y_se_reduce[31:0] (Read/Write)
// 0x128 : Data signal of Y_se_reduce
//         bit 31~0 - Y_se_reduce[63:32] (Read/Write)
// 0x12c : reserved
// 0x130 : Data signal of Y_se_act
//         bit 31~0 - Y_se_act[31:0] (Read/Write)
// 0x134 : Data signal of Y_se_act
//         bit 31~0 - Y_se_act[63:32] (Read/Write)
// 0x138 : reserved
// 0x13c : Data signal of Y_se_expand
//         bit 31~0 - Y_se_expand[31:0] (Read/Write)
// 0x140 : Data signal of Y_se_expand
//         bit 31~0 - Y_se_expand[63:32] (Read/Write)
// 0x144 : reserved
// 0x148 : Data signal of Y_se_sigmoid
//         bit 31~0 - Y_se_sigmoid[31:0] (Read/Write)
// 0x14c : Data signal of Y_se_sigmoid
//         bit 31~0 - Y_se_sigmoid[63:32] (Read/Write)
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

//------------------------Parameter----------------------
localparam
    ADDR_X_DATA_DATA_0                = 9'h010,
    ADDR_X_DATA_DATA_1                = 9'h014,
    ADDR_X_DATA_CTRL                  = 9'h018,
    ADDR_MSP_CONV_WEIGHT_DATA_0       = 9'h01c,
    ADDR_MSP_CONV_WEIGHT_DATA_1       = 9'h020,
    ADDR_MSP_CONV_WEIGHT_CTRL         = 9'h024,
    ADDR_MSP_CONV_BIAS_DATA_0         = 9'h028,
    ADDR_MSP_CONV_BIAS_DATA_1         = 9'h02c,
    ADDR_MSP_CONV_BIAS_CTRL           = 9'h030,
    ADDR_MSP_NORM_WEIGHT_DATA_0       = 9'h034,
    ADDR_MSP_NORM_WEIGHT_DATA_1       = 9'h038,
    ADDR_MSP_NORM_WEIGHT_CTRL         = 9'h03c,
    ADDR_MSP_NORM_BIAS_DATA_0         = 9'h040,
    ADDR_MSP_NORM_BIAS_DATA_1         = 9'h044,
    ADDR_MSP_NORM_BIAS_CTRL           = 9'h048,
    ADDR_MSP_NORM_RUNNING_MEAN_DATA_0 = 9'h04c,
    ADDR_MSP_NORM_RUNNING_MEAN_DATA_1 = 9'h050,
    ADDR_MSP_NORM_RUNNING_MEAN_CTRL   = 9'h054,
    ADDR_MSP_NORM_RUNNING_VAR_DATA_0  = 9'h058,
    ADDR_MSP_NORM_RUNNING_VAR_DATA_1  = 9'h05c,
    ADDR_MSP_NORM_RUNNING_VAR_CTRL    = 9'h060,
    ADDR_DW_CONV_WEIGHT_DATA_0        = 9'h064,
    ADDR_DW_CONV_WEIGHT_DATA_1        = 9'h068,
    ADDR_DW_CONV_WEIGHT_CTRL          = 9'h06c,
    ADDR_NORM_1_WEIGHT_DATA_0         = 9'h070,
    ADDR_NORM_1_WEIGHT_DATA_1         = 9'h074,
    ADDR_NORM_1_WEIGHT_CTRL           = 9'h078,
    ADDR_NORM_1_BIAS_DATA_0           = 9'h07c,
    ADDR_NORM_1_BIAS_DATA_1           = 9'h080,
    ADDR_NORM_1_BIAS_CTRL             = 9'h084,
    ADDR_NORM_1_RUNNING_MEAN_DATA_0   = 9'h088,
    ADDR_NORM_1_RUNNING_MEAN_DATA_1   = 9'h08c,
    ADDR_NORM_1_RUNNING_MEAN_CTRL     = 9'h090,
    ADDR_NORM_1_RUNNING_VAR_DATA_0    = 9'h094,
    ADDR_NORM_1_RUNNING_VAR_DATA_1    = 9'h098,
    ADDR_NORM_1_RUNNING_VAR_CTRL      = 9'h09c,
    ADDR_SE_CONV_REDUCE_WEIGHT_DATA_0 = 9'h0a0,
    ADDR_SE_CONV_REDUCE_WEIGHT_DATA_1 = 9'h0a4,
    ADDR_SE_CONV_REDUCE_WEIGHT_CTRL   = 9'h0a8,
    ADDR_SE_CONV_REDUCE_BIAS_DATA_0   = 9'h0ac,
    ADDR_SE_CONV_REDUCE_BIAS_DATA_1   = 9'h0b0,
    ADDR_SE_CONV_REDUCE_BIAS_CTRL     = 9'h0b4,
    ADDR_SE_CONV_EXPAND_WEIGHT_DATA_0 = 9'h0b8,
    ADDR_SE_CONV_EXPAND_WEIGHT_DATA_1 = 9'h0bc,
    ADDR_SE_CONV_EXPAND_WEIGHT_CTRL   = 9'h0c0,
    ADDR_SE_CONV_EXPAND_BIAS_DATA_0   = 9'h0c4,
    ADDR_SE_CONV_EXPAND_BIAS_DATA_1   = 9'h0c8,
    ADDR_SE_CONV_EXPAND_BIAS_CTRL     = 9'h0cc,
    ADDR_PROJ_CONV_WEIGHT_DATA_0      = 9'h0d0,
    ADDR_PROJ_CONV_WEIGHT_DATA_1      = 9'h0d4,
    ADDR_PROJ_CONV_WEIGHT_CTRL        = 9'h0d8,
    ADDR_Y_MSP_CONV_DATA_0            = 9'h0dc,
    ADDR_Y_MSP_CONV_DATA_1            = 9'h0e0,
    ADDR_Y_MSP_CONV_CTRL              = 9'h0e4,
    ADDR_Y_MSP_NORM_DATA_0            = 9'h0e8,
    ADDR_Y_MSP_NORM_DATA_1            = 9'h0ec,
    ADDR_Y_MSP_NORM_CTRL              = 9'h0f0,
    ADDR_Y_DW_CONV_DATA_0             = 9'h0f4,
    ADDR_Y_DW_CONV_DATA_1             = 9'h0f8,
    ADDR_Y_DW_CONV_CTRL               = 9'h0fc,
    ADDR_Y_DW_NORM_DATA_0             = 9'h100,
    ADDR_Y_DW_NORM_DATA_1             = 9'h104,
    ADDR_Y_DW_NORM_CTRL               = 9'h108,
    ADDR_Y_DW_ACT_DATA_0              = 9'h10c,
    ADDR_Y_DW_ACT_DATA_1              = 9'h110,
    ADDR_Y_DW_ACT_CTRL                = 9'h114,
    ADDR_Y_SE_MEAN_DATA_0             = 9'h118,
    ADDR_Y_SE_MEAN_DATA_1             = 9'h11c,
    ADDR_Y_SE_MEAN_CTRL               = 9'h120,
    ADDR_Y_SE_REDUCE_DATA_0           = 9'h124,
    ADDR_Y_SE_REDUCE_DATA_1           = 9'h128,
    ADDR_Y_SE_REDUCE_CTRL             = 9'h12c,
    ADDR_Y_SE_ACT_DATA_0              = 9'h130,
    ADDR_Y_SE_ACT_DATA_1              = 9'h134,
    ADDR_Y_SE_ACT_CTRL                = 9'h138,
    ADDR_Y_SE_EXPAND_DATA_0           = 9'h13c,
    ADDR_Y_SE_EXPAND_DATA_1           = 9'h140,
    ADDR_Y_SE_EXPAND_CTRL             = 9'h144,
    ADDR_Y_SE_SIGMOID_DATA_0          = 9'h148,
    ADDR_Y_SE_SIGMOID_DATA_1          = 9'h14c,
    ADDR_Y_SE_SIGMOID_CTRL            = 9'h150,
    ADDR_Y_SE_DATA_0                  = 9'h154,
    ADDR_Y_SE_DATA_1                  = 9'h158,
    ADDR_Y_SE_CTRL                    = 9'h15c,
    ADDR_Y_PROJ_DATA_0                = 9'h160,
    ADDR_Y_PROJ_DATA_1                = 9'h164,
    ADDR_Y_PROJ_CTRL                  = 9'h168,
    WRIDLE                            = 2'd0,
    WRDATA                            = 2'd1,
    WRRESP                            = 2'd2,
    WRRESET                           = 2'd3,
    RDIDLE                            = 2'd0,
    RDDATA                            = 2'd1,
    RDRESET                           = 2'd2,
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
    reg  [63:0]                   int_X_data = 'b0;
    reg  [63:0]                   int_msp_conv_weight = 'b0;
    reg  [63:0]                   int_msp_conv_bias = 'b0;
    reg  [63:0]                   int_msp_norm_weight = 'b0;
    reg  [63:0]                   int_msp_norm_bias = 'b0;
    reg  [63:0]                   int_msp_norm_running_mean = 'b0;
    reg  [63:0]                   int_msp_norm_running_var = 'b0;
    reg  [63:0]                   int_dw_conv_weight = 'b0;
    reg  [63:0]                   int_norm_1_weight = 'b0;
    reg  [63:0]                   int_norm_1_bias = 'b0;
    reg  [63:0]                   int_norm_1_running_mean = 'b0;
    reg  [63:0]                   int_norm_1_running_var = 'b0;
    reg  [63:0]                   int_se_conv_reduce_weight = 'b0;
    reg  [63:0]                   int_se_conv_reduce_bias = 'b0;
    reg  [63:0]                   int_se_conv_expand_weight = 'b0;
    reg  [63:0]                   int_se_conv_expand_bias = 'b0;
    reg  [63:0]                   int_proj_conv_weight = 'b0;
    reg  [63:0]                   int_Y_msp_conv = 'b0;
    reg  [63:0]                   int_Y_msp_norm = 'b0;
    reg  [63:0]                   int_Y_dw_conv = 'b0;
    reg  [63:0]                   int_Y_dw_norm = 'b0;
    reg  [63:0]                   int_Y_dw_act = 'b0;
    reg  [63:0]                   int_Y_se_mean = 'b0;
    reg  [63:0]                   int_Y_se_reduce = 'b0;
    reg  [63:0]                   int_Y_se_act = 'b0;
    reg  [63:0]                   int_Y_se_expand = 'b0;
    reg  [63:0]                   int_Y_se_sigmoid = 'b0;
    reg  [63:0]                   int_Y_se = 'b0;
    reg  [63:0]                   int_Y_proj = 'b0;

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
                ADDR_X_DATA_DATA_0: begin
                    rdata <= int_X_data[31:0];
                end
                ADDR_X_DATA_DATA_1: begin
                    rdata <= int_X_data[63:32];
                end
                ADDR_MSP_CONV_WEIGHT_DATA_0: begin
                    rdata <= int_msp_conv_weight[31:0];
                end
                ADDR_MSP_CONV_WEIGHT_DATA_1: begin
                    rdata <= int_msp_conv_weight[63:32];
                end
                ADDR_MSP_CONV_BIAS_DATA_0: begin
                    rdata <= int_msp_conv_bias[31:0];
                end
                ADDR_MSP_CONV_BIAS_DATA_1: begin
                    rdata <= int_msp_conv_bias[63:32];
                end
                ADDR_MSP_NORM_WEIGHT_DATA_0: begin
                    rdata <= int_msp_norm_weight[31:0];
                end
                ADDR_MSP_NORM_WEIGHT_DATA_1: begin
                    rdata <= int_msp_norm_weight[63:32];
                end
                ADDR_MSP_NORM_BIAS_DATA_0: begin
                    rdata <= int_msp_norm_bias[31:0];
                end
                ADDR_MSP_NORM_BIAS_DATA_1: begin
                    rdata <= int_msp_norm_bias[63:32];
                end
                ADDR_MSP_NORM_RUNNING_MEAN_DATA_0: begin
                    rdata <= int_msp_norm_running_mean[31:0];
                end
                ADDR_MSP_NORM_RUNNING_MEAN_DATA_1: begin
                    rdata <= int_msp_norm_running_mean[63:32];
                end
                ADDR_MSP_NORM_RUNNING_VAR_DATA_0: begin
                    rdata <= int_msp_norm_running_var[31:0];
                end
                ADDR_MSP_NORM_RUNNING_VAR_DATA_1: begin
                    rdata <= int_msp_norm_running_var[63:32];
                end
                ADDR_DW_CONV_WEIGHT_DATA_0: begin
                    rdata <= int_dw_conv_weight[31:0];
                end
                ADDR_DW_CONV_WEIGHT_DATA_1: begin
                    rdata <= int_dw_conv_weight[63:32];
                end
                ADDR_NORM_1_WEIGHT_DATA_0: begin
                    rdata <= int_norm_1_weight[31:0];
                end
                ADDR_NORM_1_WEIGHT_DATA_1: begin
                    rdata <= int_norm_1_weight[63:32];
                end
                ADDR_NORM_1_BIAS_DATA_0: begin
                    rdata <= int_norm_1_bias[31:0];
                end
                ADDR_NORM_1_BIAS_DATA_1: begin
                    rdata <= int_norm_1_bias[63:32];
                end
                ADDR_NORM_1_RUNNING_MEAN_DATA_0: begin
                    rdata <= int_norm_1_running_mean[31:0];
                end
                ADDR_NORM_1_RUNNING_MEAN_DATA_1: begin
                    rdata <= int_norm_1_running_mean[63:32];
                end
                ADDR_NORM_1_RUNNING_VAR_DATA_0: begin
                    rdata <= int_norm_1_running_var[31:0];
                end
                ADDR_NORM_1_RUNNING_VAR_DATA_1: begin
                    rdata <= int_norm_1_running_var[63:32];
                end
                ADDR_SE_CONV_REDUCE_WEIGHT_DATA_0: begin
                    rdata <= int_se_conv_reduce_weight[31:0];
                end
                ADDR_SE_CONV_REDUCE_WEIGHT_DATA_1: begin
                    rdata <= int_se_conv_reduce_weight[63:32];
                end
                ADDR_SE_CONV_REDUCE_BIAS_DATA_0: begin
                    rdata <= int_se_conv_reduce_bias[31:0];
                end
                ADDR_SE_CONV_REDUCE_BIAS_DATA_1: begin
                    rdata <= int_se_conv_reduce_bias[63:32];
                end
                ADDR_SE_CONV_EXPAND_WEIGHT_DATA_0: begin
                    rdata <= int_se_conv_expand_weight[31:0];
                end
                ADDR_SE_CONV_EXPAND_WEIGHT_DATA_1: begin
                    rdata <= int_se_conv_expand_weight[63:32];
                end
                ADDR_SE_CONV_EXPAND_BIAS_DATA_0: begin
                    rdata <= int_se_conv_expand_bias[31:0];
                end
                ADDR_SE_CONV_EXPAND_BIAS_DATA_1: begin
                    rdata <= int_se_conv_expand_bias[63:32];
                end
                ADDR_PROJ_CONV_WEIGHT_DATA_0: begin
                    rdata <= int_proj_conv_weight[31:0];
                end
                ADDR_PROJ_CONV_WEIGHT_DATA_1: begin
                    rdata <= int_proj_conv_weight[63:32];
                end
                ADDR_Y_MSP_CONV_DATA_0: begin
                    rdata <= int_Y_msp_conv[31:0];
                end
                ADDR_Y_MSP_CONV_DATA_1: begin
                    rdata <= int_Y_msp_conv[63:32];
                end
                ADDR_Y_MSP_NORM_DATA_0: begin
                    rdata <= int_Y_msp_norm[31:0];
                end
                ADDR_Y_MSP_NORM_DATA_1: begin
                    rdata <= int_Y_msp_norm[63:32];
                end
                ADDR_Y_DW_CONV_DATA_0: begin
                    rdata <= int_Y_dw_conv[31:0];
                end
                ADDR_Y_DW_CONV_DATA_1: begin
                    rdata <= int_Y_dw_conv[63:32];
                end
                ADDR_Y_DW_NORM_DATA_0: begin
                    rdata <= int_Y_dw_norm[31:0];
                end
                ADDR_Y_DW_NORM_DATA_1: begin
                    rdata <= int_Y_dw_norm[63:32];
                end
                ADDR_Y_DW_ACT_DATA_0: begin
                    rdata <= int_Y_dw_act[31:0];
                end
                ADDR_Y_DW_ACT_DATA_1: begin
                    rdata <= int_Y_dw_act[63:32];
                end
                ADDR_Y_SE_MEAN_DATA_0: begin
                    rdata <= int_Y_se_mean[31:0];
                end
                ADDR_Y_SE_MEAN_DATA_1: begin
                    rdata <= int_Y_se_mean[63:32];
                end
                ADDR_Y_SE_REDUCE_DATA_0: begin
                    rdata <= int_Y_se_reduce[31:0];
                end
                ADDR_Y_SE_REDUCE_DATA_1: begin
                    rdata <= int_Y_se_reduce[63:32];
                end
                ADDR_Y_SE_ACT_DATA_0: begin
                    rdata <= int_Y_se_act[31:0];
                end
                ADDR_Y_SE_ACT_DATA_1: begin
                    rdata <= int_Y_se_act[63:32];
                end
                ADDR_Y_SE_EXPAND_DATA_0: begin
                    rdata <= int_Y_se_expand[31:0];
                end
                ADDR_Y_SE_EXPAND_DATA_1: begin
                    rdata <= int_Y_se_expand[63:32];
                end
                ADDR_Y_SE_SIGMOID_DATA_0: begin
                    rdata <= int_Y_se_sigmoid[31:0];
                end
                ADDR_Y_SE_SIGMOID_DATA_1: begin
                    rdata <= int_Y_se_sigmoid[63:32];
                end
                ADDR_Y_SE_DATA_0: begin
                    rdata <= int_Y_se[31:0];
                end
                ADDR_Y_SE_DATA_1: begin
                    rdata <= int_Y_se[63:32];
                end
                ADDR_Y_PROJ_DATA_0: begin
                    rdata <= int_Y_proj[31:0];
                end
                ADDR_Y_PROJ_DATA_1: begin
                    rdata <= int_Y_proj[63:32];
                end
            endcase
        end
    end
end


//------------------------Register logic-----------------
assign X_data                = int_X_data;
assign msp_conv_weight       = int_msp_conv_weight;
assign msp_conv_bias         = int_msp_conv_bias;
assign msp_norm_weight       = int_msp_norm_weight;
assign msp_norm_bias         = int_msp_norm_bias;
assign msp_norm_running_mean = int_msp_norm_running_mean;
assign msp_norm_running_var  = int_msp_norm_running_var;
assign dw_conv_weight        = int_dw_conv_weight;
assign norm_1_weight         = int_norm_1_weight;
assign norm_1_bias           = int_norm_1_bias;
assign norm_1_running_mean   = int_norm_1_running_mean;
assign norm_1_running_var    = int_norm_1_running_var;
assign se_conv_reduce_weight = int_se_conv_reduce_weight;
assign se_conv_reduce_bias   = int_se_conv_reduce_bias;
assign se_conv_expand_weight = int_se_conv_expand_weight;
assign se_conv_expand_bias   = int_se_conv_expand_bias;
assign proj_conv_weight      = int_proj_conv_weight;
assign Y_msp_conv            = int_Y_msp_conv;
assign Y_msp_norm            = int_Y_msp_norm;
assign Y_dw_conv             = int_Y_dw_conv;
assign Y_dw_norm             = int_Y_dw_norm;
assign Y_dw_act              = int_Y_dw_act;
assign Y_se_mean             = int_Y_se_mean;
assign Y_se_reduce           = int_Y_se_reduce;
assign Y_se_act              = int_Y_se_act;
assign Y_se_expand           = int_Y_se_expand;
assign Y_se_sigmoid          = int_Y_se_sigmoid;
assign Y_se                  = int_Y_se;
assign Y_proj                = int_Y_proj;
// int_X_data[31:0]
always @(posedge ACLK) begin
    if (ARESET)
        int_X_data[31:0] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_X_DATA_DATA_0)
            int_X_data[31:0] <= (WDATA[31:0] & wmask) | (int_X_data[31:0] & ~wmask);
    end
end

// int_X_data[63:32]
always @(posedge ACLK) begin
    if (ARESET)
        int_X_data[63:32] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_X_DATA_DATA_1)
            int_X_data[63:32] <= (WDATA[31:0] & wmask) | (int_X_data[63:32] & ~wmask);
    end
end

// int_msp_conv_weight[31:0]
always @(posedge ACLK) begin
    if (ARESET)
        int_msp_conv_weight[31:0] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_MSP_CONV_WEIGHT_DATA_0)
            int_msp_conv_weight[31:0] <= (WDATA[31:0] & wmask) | (int_msp_conv_weight[31:0] & ~wmask);
    end
end

// int_msp_conv_weight[63:32]
always @(posedge ACLK) begin
    if (ARESET)
        int_msp_conv_weight[63:32] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_MSP_CONV_WEIGHT_DATA_1)
            int_msp_conv_weight[63:32] <= (WDATA[31:0] & wmask) | (int_msp_conv_weight[63:32] & ~wmask);
    end
end

// int_msp_conv_bias[31:0]
always @(posedge ACLK) begin
    if (ARESET)
        int_msp_conv_bias[31:0] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_MSP_CONV_BIAS_DATA_0)
            int_msp_conv_bias[31:0] <= (WDATA[31:0] & wmask) | (int_msp_conv_bias[31:0] & ~wmask);
    end
end

// int_msp_conv_bias[63:32]
always @(posedge ACLK) begin
    if (ARESET)
        int_msp_conv_bias[63:32] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_MSP_CONV_BIAS_DATA_1)
            int_msp_conv_bias[63:32] <= (WDATA[31:0] & wmask) | (int_msp_conv_bias[63:32] & ~wmask);
    end
end

// int_msp_norm_weight[31:0]
always @(posedge ACLK) begin
    if (ARESET)
        int_msp_norm_weight[31:0] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_MSP_NORM_WEIGHT_DATA_0)
            int_msp_norm_weight[31:0] <= (WDATA[31:0] & wmask) | (int_msp_norm_weight[31:0] & ~wmask);
    end
end

// int_msp_norm_weight[63:32]
always @(posedge ACLK) begin
    if (ARESET)
        int_msp_norm_weight[63:32] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_MSP_NORM_WEIGHT_DATA_1)
            int_msp_norm_weight[63:32] <= (WDATA[31:0] & wmask) | (int_msp_norm_weight[63:32] & ~wmask);
    end
end

// int_msp_norm_bias[31:0]
always @(posedge ACLK) begin
    if (ARESET)
        int_msp_norm_bias[31:0] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_MSP_NORM_BIAS_DATA_0)
            int_msp_norm_bias[31:0] <= (WDATA[31:0] & wmask) | (int_msp_norm_bias[31:0] & ~wmask);
    end
end

// int_msp_norm_bias[63:32]
always @(posedge ACLK) begin
    if (ARESET)
        int_msp_norm_bias[63:32] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_MSP_NORM_BIAS_DATA_1)
            int_msp_norm_bias[63:32] <= (WDATA[31:0] & wmask) | (int_msp_norm_bias[63:32] & ~wmask);
    end
end

// int_msp_norm_running_mean[31:0]
always @(posedge ACLK) begin
    if (ARESET)
        int_msp_norm_running_mean[31:0] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_MSP_NORM_RUNNING_MEAN_DATA_0)
            int_msp_norm_running_mean[31:0] <= (WDATA[31:0] & wmask) | (int_msp_norm_running_mean[31:0] & ~wmask);
    end
end

// int_msp_norm_running_mean[63:32]
always @(posedge ACLK) begin
    if (ARESET)
        int_msp_norm_running_mean[63:32] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_MSP_NORM_RUNNING_MEAN_DATA_1)
            int_msp_norm_running_mean[63:32] <= (WDATA[31:0] & wmask) | (int_msp_norm_running_mean[63:32] & ~wmask);
    end
end

// int_msp_norm_running_var[31:0]
always @(posedge ACLK) begin
    if (ARESET)
        int_msp_norm_running_var[31:0] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_MSP_NORM_RUNNING_VAR_DATA_0)
            int_msp_norm_running_var[31:0] <= (WDATA[31:0] & wmask) | (int_msp_norm_running_var[31:0] & ~wmask);
    end
end

// int_msp_norm_running_var[63:32]
always @(posedge ACLK) begin
    if (ARESET)
        int_msp_norm_running_var[63:32] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_MSP_NORM_RUNNING_VAR_DATA_1)
            int_msp_norm_running_var[63:32] <= (WDATA[31:0] & wmask) | (int_msp_norm_running_var[63:32] & ~wmask);
    end
end

// int_dw_conv_weight[31:0]
always @(posedge ACLK) begin
    if (ARESET)
        int_dw_conv_weight[31:0] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_DW_CONV_WEIGHT_DATA_0)
            int_dw_conv_weight[31:0] <= (WDATA[31:0] & wmask) | (int_dw_conv_weight[31:0] & ~wmask);
    end
end

// int_dw_conv_weight[63:32]
always @(posedge ACLK) begin
    if (ARESET)
        int_dw_conv_weight[63:32] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_DW_CONV_WEIGHT_DATA_1)
            int_dw_conv_weight[63:32] <= (WDATA[31:0] & wmask) | (int_dw_conv_weight[63:32] & ~wmask);
    end
end

// int_norm_1_weight[31:0]
always @(posedge ACLK) begin
    if (ARESET)
        int_norm_1_weight[31:0] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_NORM_1_WEIGHT_DATA_0)
            int_norm_1_weight[31:0] <= (WDATA[31:0] & wmask) | (int_norm_1_weight[31:0] & ~wmask);
    end
end

// int_norm_1_weight[63:32]
always @(posedge ACLK) begin
    if (ARESET)
        int_norm_1_weight[63:32] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_NORM_1_WEIGHT_DATA_1)
            int_norm_1_weight[63:32] <= (WDATA[31:0] & wmask) | (int_norm_1_weight[63:32] & ~wmask);
    end
end

// int_norm_1_bias[31:0]
always @(posedge ACLK) begin
    if (ARESET)
        int_norm_1_bias[31:0] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_NORM_1_BIAS_DATA_0)
            int_norm_1_bias[31:0] <= (WDATA[31:0] & wmask) | (int_norm_1_bias[31:0] & ~wmask);
    end
end

// int_norm_1_bias[63:32]
always @(posedge ACLK) begin
    if (ARESET)
        int_norm_1_bias[63:32] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_NORM_1_BIAS_DATA_1)
            int_norm_1_bias[63:32] <= (WDATA[31:0] & wmask) | (int_norm_1_bias[63:32] & ~wmask);
    end
end

// int_norm_1_running_mean[31:0]
always @(posedge ACLK) begin
    if (ARESET)
        int_norm_1_running_mean[31:0] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_NORM_1_RUNNING_MEAN_DATA_0)
            int_norm_1_running_mean[31:0] <= (WDATA[31:0] & wmask) | (int_norm_1_running_mean[31:0] & ~wmask);
    end
end

// int_norm_1_running_mean[63:32]
always @(posedge ACLK) begin
    if (ARESET)
        int_norm_1_running_mean[63:32] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_NORM_1_RUNNING_MEAN_DATA_1)
            int_norm_1_running_mean[63:32] <= (WDATA[31:0] & wmask) | (int_norm_1_running_mean[63:32] & ~wmask);
    end
end

// int_norm_1_running_var[31:0]
always @(posedge ACLK) begin
    if (ARESET)
        int_norm_1_running_var[31:0] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_NORM_1_RUNNING_VAR_DATA_0)
            int_norm_1_running_var[31:0] <= (WDATA[31:0] & wmask) | (int_norm_1_running_var[31:0] & ~wmask);
    end
end

// int_norm_1_running_var[63:32]
always @(posedge ACLK) begin
    if (ARESET)
        int_norm_1_running_var[63:32] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_NORM_1_RUNNING_VAR_DATA_1)
            int_norm_1_running_var[63:32] <= (WDATA[31:0] & wmask) | (int_norm_1_running_var[63:32] & ~wmask);
    end
end

// int_se_conv_reduce_weight[31:0]
always @(posedge ACLK) begin
    if (ARESET)
        int_se_conv_reduce_weight[31:0] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_SE_CONV_REDUCE_WEIGHT_DATA_0)
            int_se_conv_reduce_weight[31:0] <= (WDATA[31:0] & wmask) | (int_se_conv_reduce_weight[31:0] & ~wmask);
    end
end

// int_se_conv_reduce_weight[63:32]
always @(posedge ACLK) begin
    if (ARESET)
        int_se_conv_reduce_weight[63:32] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_SE_CONV_REDUCE_WEIGHT_DATA_1)
            int_se_conv_reduce_weight[63:32] <= (WDATA[31:0] & wmask) | (int_se_conv_reduce_weight[63:32] & ~wmask);
    end
end

// int_se_conv_reduce_bias[31:0]
always @(posedge ACLK) begin
    if (ARESET)
        int_se_conv_reduce_bias[31:0] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_SE_CONV_REDUCE_BIAS_DATA_0)
            int_se_conv_reduce_bias[31:0] <= (WDATA[31:0] & wmask) | (int_se_conv_reduce_bias[31:0] & ~wmask);
    end
end

// int_se_conv_reduce_bias[63:32]
always @(posedge ACLK) begin
    if (ARESET)
        int_se_conv_reduce_bias[63:32] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_SE_CONV_REDUCE_BIAS_DATA_1)
            int_se_conv_reduce_bias[63:32] <= (WDATA[31:0] & wmask) | (int_se_conv_reduce_bias[63:32] & ~wmask);
    end
end

// int_se_conv_expand_weight[31:0]
always @(posedge ACLK) begin
    if (ARESET)
        int_se_conv_expand_weight[31:0] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_SE_CONV_EXPAND_WEIGHT_DATA_0)
            int_se_conv_expand_weight[31:0] <= (WDATA[31:0] & wmask) | (int_se_conv_expand_weight[31:0] & ~wmask);
    end
end

// int_se_conv_expand_weight[63:32]
always @(posedge ACLK) begin
    if (ARESET)
        int_se_conv_expand_weight[63:32] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_SE_CONV_EXPAND_WEIGHT_DATA_1)
            int_se_conv_expand_weight[63:32] <= (WDATA[31:0] & wmask) | (int_se_conv_expand_weight[63:32] & ~wmask);
    end
end

// int_se_conv_expand_bias[31:0]
always @(posedge ACLK) begin
    if (ARESET)
        int_se_conv_expand_bias[31:0] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_SE_CONV_EXPAND_BIAS_DATA_0)
            int_se_conv_expand_bias[31:0] <= (WDATA[31:0] & wmask) | (int_se_conv_expand_bias[31:0] & ~wmask);
    end
end

// int_se_conv_expand_bias[63:32]
always @(posedge ACLK) begin
    if (ARESET)
        int_se_conv_expand_bias[63:32] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_SE_CONV_EXPAND_BIAS_DATA_1)
            int_se_conv_expand_bias[63:32] <= (WDATA[31:0] & wmask) | (int_se_conv_expand_bias[63:32] & ~wmask);
    end
end

// int_proj_conv_weight[31:0]
always @(posedge ACLK) begin
    if (ARESET)
        int_proj_conv_weight[31:0] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_PROJ_CONV_WEIGHT_DATA_0)
            int_proj_conv_weight[31:0] <= (WDATA[31:0] & wmask) | (int_proj_conv_weight[31:0] & ~wmask);
    end
end

// int_proj_conv_weight[63:32]
always @(posedge ACLK) begin
    if (ARESET)
        int_proj_conv_weight[63:32] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_PROJ_CONV_WEIGHT_DATA_1)
            int_proj_conv_weight[63:32] <= (WDATA[31:0] & wmask) | (int_proj_conv_weight[63:32] & ~wmask);
    end
end

// int_Y_msp_conv[31:0]
always @(posedge ACLK) begin
    if (ARESET)
        int_Y_msp_conv[31:0] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_Y_MSP_CONV_DATA_0)
            int_Y_msp_conv[31:0] <= (WDATA[31:0] & wmask) | (int_Y_msp_conv[31:0] & ~wmask);
    end
end

// int_Y_msp_conv[63:32]
always @(posedge ACLK) begin
    if (ARESET)
        int_Y_msp_conv[63:32] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_Y_MSP_CONV_DATA_1)
            int_Y_msp_conv[63:32] <= (WDATA[31:0] & wmask) | (int_Y_msp_conv[63:32] & ~wmask);
    end
end

// int_Y_msp_norm[31:0]
always @(posedge ACLK) begin
    if (ARESET)
        int_Y_msp_norm[31:0] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_Y_MSP_NORM_DATA_0)
            int_Y_msp_norm[31:0] <= (WDATA[31:0] & wmask) | (int_Y_msp_norm[31:0] & ~wmask);
    end
end

// int_Y_msp_norm[63:32]
always @(posedge ACLK) begin
    if (ARESET)
        int_Y_msp_norm[63:32] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_Y_MSP_NORM_DATA_1)
            int_Y_msp_norm[63:32] <= (WDATA[31:0] & wmask) | (int_Y_msp_norm[63:32] & ~wmask);
    end
end

// int_Y_dw_conv[31:0]
always @(posedge ACLK) begin
    if (ARESET)
        int_Y_dw_conv[31:0] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_Y_DW_CONV_DATA_0)
            int_Y_dw_conv[31:0] <= (WDATA[31:0] & wmask) | (int_Y_dw_conv[31:0] & ~wmask);
    end
end

// int_Y_dw_conv[63:32]
always @(posedge ACLK) begin
    if (ARESET)
        int_Y_dw_conv[63:32] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_Y_DW_CONV_DATA_1)
            int_Y_dw_conv[63:32] <= (WDATA[31:0] & wmask) | (int_Y_dw_conv[63:32] & ~wmask);
    end
end

// int_Y_dw_norm[31:0]
always @(posedge ACLK) begin
    if (ARESET)
        int_Y_dw_norm[31:0] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_Y_DW_NORM_DATA_0)
            int_Y_dw_norm[31:0] <= (WDATA[31:0] & wmask) | (int_Y_dw_norm[31:0] & ~wmask);
    end
end

// int_Y_dw_norm[63:32]
always @(posedge ACLK) begin
    if (ARESET)
        int_Y_dw_norm[63:32] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_Y_DW_NORM_DATA_1)
            int_Y_dw_norm[63:32] <= (WDATA[31:0] & wmask) | (int_Y_dw_norm[63:32] & ~wmask);
    end
end

// int_Y_dw_act[31:0]
always @(posedge ACLK) begin
    if (ARESET)
        int_Y_dw_act[31:0] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_Y_DW_ACT_DATA_0)
            int_Y_dw_act[31:0] <= (WDATA[31:0] & wmask) | (int_Y_dw_act[31:0] & ~wmask);
    end
end

// int_Y_dw_act[63:32]
always @(posedge ACLK) begin
    if (ARESET)
        int_Y_dw_act[63:32] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_Y_DW_ACT_DATA_1)
            int_Y_dw_act[63:32] <= (WDATA[31:0] & wmask) | (int_Y_dw_act[63:32] & ~wmask);
    end
end

// int_Y_se_mean[31:0]
always @(posedge ACLK) begin
    if (ARESET)
        int_Y_se_mean[31:0] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_Y_SE_MEAN_DATA_0)
            int_Y_se_mean[31:0] <= (WDATA[31:0] & wmask) | (int_Y_se_mean[31:0] & ~wmask);
    end
end

// int_Y_se_mean[63:32]
always @(posedge ACLK) begin
    if (ARESET)
        int_Y_se_mean[63:32] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_Y_SE_MEAN_DATA_1)
            int_Y_se_mean[63:32] <= (WDATA[31:0] & wmask) | (int_Y_se_mean[63:32] & ~wmask);
    end
end

// int_Y_se_reduce[31:0]
always @(posedge ACLK) begin
    if (ARESET)
        int_Y_se_reduce[31:0] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_Y_SE_REDUCE_DATA_0)
            int_Y_se_reduce[31:0] <= (WDATA[31:0] & wmask) | (int_Y_se_reduce[31:0] & ~wmask);
    end
end

// int_Y_se_reduce[63:32]
always @(posedge ACLK) begin
    if (ARESET)
        int_Y_se_reduce[63:32] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_Y_SE_REDUCE_DATA_1)
            int_Y_se_reduce[63:32] <= (WDATA[31:0] & wmask) | (int_Y_se_reduce[63:32] & ~wmask);
    end
end

// int_Y_se_act[31:0]
always @(posedge ACLK) begin
    if (ARESET)
        int_Y_se_act[31:0] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_Y_SE_ACT_DATA_0)
            int_Y_se_act[31:0] <= (WDATA[31:0] & wmask) | (int_Y_se_act[31:0] & ~wmask);
    end
end

// int_Y_se_act[63:32]
always @(posedge ACLK) begin
    if (ARESET)
        int_Y_se_act[63:32] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_Y_SE_ACT_DATA_1)
            int_Y_se_act[63:32] <= (WDATA[31:0] & wmask) | (int_Y_se_act[63:32] & ~wmask);
    end
end

// int_Y_se_expand[31:0]
always @(posedge ACLK) begin
    if (ARESET)
        int_Y_se_expand[31:0] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_Y_SE_EXPAND_DATA_0)
            int_Y_se_expand[31:0] <= (WDATA[31:0] & wmask) | (int_Y_se_expand[31:0] & ~wmask);
    end
end

// int_Y_se_expand[63:32]
always @(posedge ACLK) begin
    if (ARESET)
        int_Y_se_expand[63:32] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_Y_SE_EXPAND_DATA_1)
            int_Y_se_expand[63:32] <= (WDATA[31:0] & wmask) | (int_Y_se_expand[63:32] & ~wmask);
    end
end

// int_Y_se_sigmoid[31:0]
always @(posedge ACLK) begin
    if (ARESET)
        int_Y_se_sigmoid[31:0] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_Y_SE_SIGMOID_DATA_0)
            int_Y_se_sigmoid[31:0] <= (WDATA[31:0] & wmask) | (int_Y_se_sigmoid[31:0] & ~wmask);
    end
end

// int_Y_se_sigmoid[63:32]
always @(posedge ACLK) begin
    if (ARESET)
        int_Y_se_sigmoid[63:32] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_Y_SE_SIGMOID_DATA_1)
            int_Y_se_sigmoid[63:32] <= (WDATA[31:0] & wmask) | (int_Y_se_sigmoid[63:32] & ~wmask);
    end
end

// int_Y_se[31:0]
always @(posedge ACLK) begin
    if (ARESET)
        int_Y_se[31:0] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_Y_SE_DATA_0)
            int_Y_se[31:0] <= (WDATA[31:0] & wmask) | (int_Y_se[31:0] & ~wmask);
    end
end

// int_Y_se[63:32]
always @(posedge ACLK) begin
    if (ARESET)
        int_Y_se[63:32] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_Y_SE_DATA_1)
            int_Y_se[63:32] <= (WDATA[31:0] & wmask) | (int_Y_se[63:32] & ~wmask);
    end
end

// int_Y_proj[31:0]
always @(posedge ACLK) begin
    if (ARESET)
        int_Y_proj[31:0] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_Y_PROJ_DATA_0)
            int_Y_proj[31:0] <= (WDATA[31:0] & wmask) | (int_Y_proj[31:0] & ~wmask);
    end
end

// int_Y_proj[63:32]
always @(posedge ACLK) begin
    if (ARESET)
        int_Y_proj[63:32] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_Y_PROJ_DATA_1)
            int_Y_proj[63:32] <= (WDATA[31:0] & wmask) | (int_Y_proj[63:32] & ~wmask);
    end
end


//------------------------Memory logic-------------------

endmodule
