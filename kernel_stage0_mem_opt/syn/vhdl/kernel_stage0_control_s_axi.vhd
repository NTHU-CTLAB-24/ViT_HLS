-- ==============================================================
-- Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2022.1 (64-bit)
-- Tool Version Limit: 2022.04
-- Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
-- ==============================================================
library IEEE;
use IEEE.STD_LOGIC_1164.all;
use IEEE.NUMERIC_STD.all;

entity kernel_stage0_control_s_axi is
generic (
    C_S_AXI_ADDR_WIDTH    : INTEGER := 9;
    C_S_AXI_DATA_WIDTH    : INTEGER := 32);
port (
    ACLK                  :in   STD_LOGIC;
    ARESET                :in   STD_LOGIC;
    ACLK_EN               :in   STD_LOGIC;
    AWADDR                :in   STD_LOGIC_VECTOR(C_S_AXI_ADDR_WIDTH-1 downto 0);
    AWVALID               :in   STD_LOGIC;
    AWREADY               :out  STD_LOGIC;
    WDATA                 :in   STD_LOGIC_VECTOR(C_S_AXI_DATA_WIDTH-1 downto 0);
    WSTRB                 :in   STD_LOGIC_VECTOR(C_S_AXI_DATA_WIDTH/8-1 downto 0);
    WVALID                :in   STD_LOGIC;
    WREADY                :out  STD_LOGIC;
    BRESP                 :out  STD_LOGIC_VECTOR(1 downto 0);
    BVALID                :out  STD_LOGIC;
    BREADY                :in   STD_LOGIC;
    ARADDR                :in   STD_LOGIC_VECTOR(C_S_AXI_ADDR_WIDTH-1 downto 0);
    ARVALID               :in   STD_LOGIC;
    ARREADY               :out  STD_LOGIC;
    RDATA                 :out  STD_LOGIC_VECTOR(C_S_AXI_DATA_WIDTH-1 downto 0);
    RRESP                 :out  STD_LOGIC_VECTOR(1 downto 0);
    RVALID                :out  STD_LOGIC;
    RREADY                :in   STD_LOGIC;
    X_data                :out  STD_LOGIC_VECTOR(63 downto 0);
    msp_conv_weight       :out  STD_LOGIC_VECTOR(63 downto 0);
    msp_conv_bias         :out  STD_LOGIC_VECTOR(63 downto 0);
    msp_norm_weight       :out  STD_LOGIC_VECTOR(63 downto 0);
    msp_norm_bias         :out  STD_LOGIC_VECTOR(63 downto 0);
    msp_norm_running_mean :out  STD_LOGIC_VECTOR(63 downto 0);
    msp_norm_running_var  :out  STD_LOGIC_VECTOR(63 downto 0);
    dw_conv_weight        :out  STD_LOGIC_VECTOR(63 downto 0);
    norm_1_weight         :out  STD_LOGIC_VECTOR(63 downto 0);
    norm_1_bias           :out  STD_LOGIC_VECTOR(63 downto 0);
    norm_1_running_mean   :out  STD_LOGIC_VECTOR(63 downto 0);
    norm_1_running_var    :out  STD_LOGIC_VECTOR(63 downto 0);
    se_conv_reduce_weight :out  STD_LOGIC_VECTOR(63 downto 0);
    se_conv_reduce_bias   :out  STD_LOGIC_VECTOR(63 downto 0);
    se_conv_expand_weight :out  STD_LOGIC_VECTOR(63 downto 0);
    se_conv_expand_bias   :out  STD_LOGIC_VECTOR(63 downto 0);
    proj_conv_weight      :out  STD_LOGIC_VECTOR(63 downto 0);
    Y_msp_conv            :out  STD_LOGIC_VECTOR(63 downto 0);
    Y_msp_norm            :out  STD_LOGIC_VECTOR(63 downto 0);
    Y_dw_conv             :out  STD_LOGIC_VECTOR(63 downto 0);
    Y_dw_norm             :out  STD_LOGIC_VECTOR(63 downto 0);
    Y_dw_act              :out  STD_LOGIC_VECTOR(63 downto 0);
    Y_se_mean             :out  STD_LOGIC_VECTOR(63 downto 0);
    Y_se_reduce           :out  STD_LOGIC_VECTOR(63 downto 0);
    Y_se_act              :out  STD_LOGIC_VECTOR(63 downto 0);
    Y_se_expand           :out  STD_LOGIC_VECTOR(63 downto 0);
    Y_se_sigmoid          :out  STD_LOGIC_VECTOR(63 downto 0);
    Y_se                  :out  STD_LOGIC_VECTOR(63 downto 0);
    Y_proj                :out  STD_LOGIC_VECTOR(63 downto 0)
);
end entity kernel_stage0_control_s_axi;

-- ------------------------Address Info-------------------
-- 0x000 : reserved
-- 0x004 : reserved
-- 0x008 : reserved
-- 0x00c : reserved
-- 0x010 : Data signal of X_data
--         bit 31~0 - X_data[31:0] (Read/Write)
-- 0x014 : Data signal of X_data
--         bit 31~0 - X_data[63:32] (Read/Write)
-- 0x018 : reserved
-- 0x01c : Data signal of msp_conv_weight
--         bit 31~0 - msp_conv_weight[31:0] (Read/Write)
-- 0x020 : Data signal of msp_conv_weight
--         bit 31~0 - msp_conv_weight[63:32] (Read/Write)
-- 0x024 : reserved
-- 0x028 : Data signal of msp_conv_bias
--         bit 31~0 - msp_conv_bias[31:0] (Read/Write)
-- 0x02c : Data signal of msp_conv_bias
--         bit 31~0 - msp_conv_bias[63:32] (Read/Write)
-- 0x030 : reserved
-- 0x034 : Data signal of msp_norm_weight
--         bit 31~0 - msp_norm_weight[31:0] (Read/Write)
-- 0x038 : Data signal of msp_norm_weight
--         bit 31~0 - msp_norm_weight[63:32] (Read/Write)
-- 0x03c : reserved
-- 0x040 : Data signal of msp_norm_bias
--         bit 31~0 - msp_norm_bias[31:0] (Read/Write)
-- 0x044 : Data signal of msp_norm_bias
--         bit 31~0 - msp_norm_bias[63:32] (Read/Write)
-- 0x048 : reserved
-- 0x04c : Data signal of msp_norm_running_mean
--         bit 31~0 - msp_norm_running_mean[31:0] (Read/Write)
-- 0x050 : Data signal of msp_norm_running_mean
--         bit 31~0 - msp_norm_running_mean[63:32] (Read/Write)
-- 0x054 : reserved
-- 0x058 : Data signal of msp_norm_running_var
--         bit 31~0 - msp_norm_running_var[31:0] (Read/Write)
-- 0x05c : Data signal of msp_norm_running_var
--         bit 31~0 - msp_norm_running_var[63:32] (Read/Write)
-- 0x060 : reserved
-- 0x064 : Data signal of dw_conv_weight
--         bit 31~0 - dw_conv_weight[31:0] (Read/Write)
-- 0x068 : Data signal of dw_conv_weight
--         bit 31~0 - dw_conv_weight[63:32] (Read/Write)
-- 0x06c : reserved
-- 0x070 : Data signal of norm_1_weight
--         bit 31~0 - norm_1_weight[31:0] (Read/Write)
-- 0x074 : Data signal of norm_1_weight
--         bit 31~0 - norm_1_weight[63:32] (Read/Write)
-- 0x078 : reserved
-- 0x07c : Data signal of norm_1_bias
--         bit 31~0 - norm_1_bias[31:0] (Read/Write)
-- 0x080 : Data signal of norm_1_bias
--         bit 31~0 - norm_1_bias[63:32] (Read/Write)
-- 0x084 : reserved
-- 0x088 : Data signal of norm_1_running_mean
--         bit 31~0 - norm_1_running_mean[31:0] (Read/Write)
-- 0x08c : Data signal of norm_1_running_mean
--         bit 31~0 - norm_1_running_mean[63:32] (Read/Write)
-- 0x090 : reserved
-- 0x094 : Data signal of norm_1_running_var
--         bit 31~0 - norm_1_running_var[31:0] (Read/Write)
-- 0x098 : Data signal of norm_1_running_var
--         bit 31~0 - norm_1_running_var[63:32] (Read/Write)
-- 0x09c : reserved
-- 0x0a0 : Data signal of se_conv_reduce_weight
--         bit 31~0 - se_conv_reduce_weight[31:0] (Read/Write)
-- 0x0a4 : Data signal of se_conv_reduce_weight
--         bit 31~0 - se_conv_reduce_weight[63:32] (Read/Write)
-- 0x0a8 : reserved
-- 0x0ac : Data signal of se_conv_reduce_bias
--         bit 31~0 - se_conv_reduce_bias[31:0] (Read/Write)
-- 0x0b0 : Data signal of se_conv_reduce_bias
--         bit 31~0 - se_conv_reduce_bias[63:32] (Read/Write)
-- 0x0b4 : reserved
-- 0x0b8 : Data signal of se_conv_expand_weight
--         bit 31~0 - se_conv_expand_weight[31:0] (Read/Write)
-- 0x0bc : Data signal of se_conv_expand_weight
--         bit 31~0 - se_conv_expand_weight[63:32] (Read/Write)
-- 0x0c0 : reserved
-- 0x0c4 : Data signal of se_conv_expand_bias
--         bit 31~0 - se_conv_expand_bias[31:0] (Read/Write)
-- 0x0c8 : Data signal of se_conv_expand_bias
--         bit 31~0 - se_conv_expand_bias[63:32] (Read/Write)
-- 0x0cc : reserved
-- 0x0d0 : Data signal of proj_conv_weight
--         bit 31~0 - proj_conv_weight[31:0] (Read/Write)
-- 0x0d4 : Data signal of proj_conv_weight
--         bit 31~0 - proj_conv_weight[63:32] (Read/Write)
-- 0x0d8 : reserved
-- 0x0dc : Data signal of Y_msp_conv
--         bit 31~0 - Y_msp_conv[31:0] (Read/Write)
-- 0x0e0 : Data signal of Y_msp_conv
--         bit 31~0 - Y_msp_conv[63:32] (Read/Write)
-- 0x0e4 : reserved
-- 0x0e8 : Data signal of Y_msp_norm
--         bit 31~0 - Y_msp_norm[31:0] (Read/Write)
-- 0x0ec : Data signal of Y_msp_norm
--         bit 31~0 - Y_msp_norm[63:32] (Read/Write)
-- 0x0f0 : reserved
-- 0x0f4 : Data signal of Y_dw_conv
--         bit 31~0 - Y_dw_conv[31:0] (Read/Write)
-- 0x0f8 : Data signal of Y_dw_conv
--         bit 31~0 - Y_dw_conv[63:32] (Read/Write)
-- 0x0fc : reserved
-- 0x100 : Data signal of Y_dw_norm
--         bit 31~0 - Y_dw_norm[31:0] (Read/Write)
-- 0x104 : Data signal of Y_dw_norm
--         bit 31~0 - Y_dw_norm[63:32] (Read/Write)
-- 0x108 : reserved
-- 0x10c : Data signal of Y_dw_act
--         bit 31~0 - Y_dw_act[31:0] (Read/Write)
-- 0x110 : Data signal of Y_dw_act
--         bit 31~0 - Y_dw_act[63:32] (Read/Write)
-- 0x114 : reserved
-- 0x118 : Data signal of Y_se_mean
--         bit 31~0 - Y_se_mean[31:0] (Read/Write)
-- 0x11c : Data signal of Y_se_mean
--         bit 31~0 - Y_se_mean[63:32] (Read/Write)
-- 0x120 : reserved
-- 0x124 : Data signal of Y_se_reduce
--         bit 31~0 - Y_se_reduce[31:0] (Read/Write)
-- 0x128 : Data signal of Y_se_reduce
--         bit 31~0 - Y_se_reduce[63:32] (Read/Write)
-- 0x12c : reserved
-- 0x130 : Data signal of Y_se_act
--         bit 31~0 - Y_se_act[31:0] (Read/Write)
-- 0x134 : Data signal of Y_se_act
--         bit 31~0 - Y_se_act[63:32] (Read/Write)
-- 0x138 : reserved
-- 0x13c : Data signal of Y_se_expand
--         bit 31~0 - Y_se_expand[31:0] (Read/Write)
-- 0x140 : Data signal of Y_se_expand
--         bit 31~0 - Y_se_expand[63:32] (Read/Write)
-- 0x144 : reserved
-- 0x148 : Data signal of Y_se_sigmoid
--         bit 31~0 - Y_se_sigmoid[31:0] (Read/Write)
-- 0x14c : Data signal of Y_se_sigmoid
--         bit 31~0 - Y_se_sigmoid[63:32] (Read/Write)
-- 0x150 : reserved
-- 0x154 : Data signal of Y_se
--         bit 31~0 - Y_se[31:0] (Read/Write)
-- 0x158 : Data signal of Y_se
--         bit 31~0 - Y_se[63:32] (Read/Write)
-- 0x15c : reserved
-- 0x160 : Data signal of Y_proj
--         bit 31~0 - Y_proj[31:0] (Read/Write)
-- 0x164 : Data signal of Y_proj
--         bit 31~0 - Y_proj[63:32] (Read/Write)
-- 0x168 : reserved
-- (SC = Self Clear, COR = Clear on Read, TOW = Toggle on Write, COH = Clear on Handshake)

architecture behave of kernel_stage0_control_s_axi is
    type states is (wridle, wrdata, wrresp, wrreset, rdidle, rddata, rdreset);  -- read and write fsm states
    signal wstate  : states := wrreset;
    signal rstate  : states := rdreset;
    signal wnext, rnext: states;
    constant ADDR_X_DATA_DATA_0                : INTEGER := 16#010#;
    constant ADDR_X_DATA_DATA_1                : INTEGER := 16#014#;
    constant ADDR_X_DATA_CTRL                  : INTEGER := 16#018#;
    constant ADDR_MSP_CONV_WEIGHT_DATA_0       : INTEGER := 16#01c#;
    constant ADDR_MSP_CONV_WEIGHT_DATA_1       : INTEGER := 16#020#;
    constant ADDR_MSP_CONV_WEIGHT_CTRL         : INTEGER := 16#024#;
    constant ADDR_MSP_CONV_BIAS_DATA_0         : INTEGER := 16#028#;
    constant ADDR_MSP_CONV_BIAS_DATA_1         : INTEGER := 16#02c#;
    constant ADDR_MSP_CONV_BIAS_CTRL           : INTEGER := 16#030#;
    constant ADDR_MSP_NORM_WEIGHT_DATA_0       : INTEGER := 16#034#;
    constant ADDR_MSP_NORM_WEIGHT_DATA_1       : INTEGER := 16#038#;
    constant ADDR_MSP_NORM_WEIGHT_CTRL         : INTEGER := 16#03c#;
    constant ADDR_MSP_NORM_BIAS_DATA_0         : INTEGER := 16#040#;
    constant ADDR_MSP_NORM_BIAS_DATA_1         : INTEGER := 16#044#;
    constant ADDR_MSP_NORM_BIAS_CTRL           : INTEGER := 16#048#;
    constant ADDR_MSP_NORM_RUNNING_MEAN_DATA_0 : INTEGER := 16#04c#;
    constant ADDR_MSP_NORM_RUNNING_MEAN_DATA_1 : INTEGER := 16#050#;
    constant ADDR_MSP_NORM_RUNNING_MEAN_CTRL   : INTEGER := 16#054#;
    constant ADDR_MSP_NORM_RUNNING_VAR_DATA_0  : INTEGER := 16#058#;
    constant ADDR_MSP_NORM_RUNNING_VAR_DATA_1  : INTEGER := 16#05c#;
    constant ADDR_MSP_NORM_RUNNING_VAR_CTRL    : INTEGER := 16#060#;
    constant ADDR_DW_CONV_WEIGHT_DATA_0        : INTEGER := 16#064#;
    constant ADDR_DW_CONV_WEIGHT_DATA_1        : INTEGER := 16#068#;
    constant ADDR_DW_CONV_WEIGHT_CTRL          : INTEGER := 16#06c#;
    constant ADDR_NORM_1_WEIGHT_DATA_0         : INTEGER := 16#070#;
    constant ADDR_NORM_1_WEIGHT_DATA_1         : INTEGER := 16#074#;
    constant ADDR_NORM_1_WEIGHT_CTRL           : INTEGER := 16#078#;
    constant ADDR_NORM_1_BIAS_DATA_0           : INTEGER := 16#07c#;
    constant ADDR_NORM_1_BIAS_DATA_1           : INTEGER := 16#080#;
    constant ADDR_NORM_1_BIAS_CTRL             : INTEGER := 16#084#;
    constant ADDR_NORM_1_RUNNING_MEAN_DATA_0   : INTEGER := 16#088#;
    constant ADDR_NORM_1_RUNNING_MEAN_DATA_1   : INTEGER := 16#08c#;
    constant ADDR_NORM_1_RUNNING_MEAN_CTRL     : INTEGER := 16#090#;
    constant ADDR_NORM_1_RUNNING_VAR_DATA_0    : INTEGER := 16#094#;
    constant ADDR_NORM_1_RUNNING_VAR_DATA_1    : INTEGER := 16#098#;
    constant ADDR_NORM_1_RUNNING_VAR_CTRL      : INTEGER := 16#09c#;
    constant ADDR_SE_CONV_REDUCE_WEIGHT_DATA_0 : INTEGER := 16#0a0#;
    constant ADDR_SE_CONV_REDUCE_WEIGHT_DATA_1 : INTEGER := 16#0a4#;
    constant ADDR_SE_CONV_REDUCE_WEIGHT_CTRL   : INTEGER := 16#0a8#;
    constant ADDR_SE_CONV_REDUCE_BIAS_DATA_0   : INTEGER := 16#0ac#;
    constant ADDR_SE_CONV_REDUCE_BIAS_DATA_1   : INTEGER := 16#0b0#;
    constant ADDR_SE_CONV_REDUCE_BIAS_CTRL     : INTEGER := 16#0b4#;
    constant ADDR_SE_CONV_EXPAND_WEIGHT_DATA_0 : INTEGER := 16#0b8#;
    constant ADDR_SE_CONV_EXPAND_WEIGHT_DATA_1 : INTEGER := 16#0bc#;
    constant ADDR_SE_CONV_EXPAND_WEIGHT_CTRL   : INTEGER := 16#0c0#;
    constant ADDR_SE_CONV_EXPAND_BIAS_DATA_0   : INTEGER := 16#0c4#;
    constant ADDR_SE_CONV_EXPAND_BIAS_DATA_1   : INTEGER := 16#0c8#;
    constant ADDR_SE_CONV_EXPAND_BIAS_CTRL     : INTEGER := 16#0cc#;
    constant ADDR_PROJ_CONV_WEIGHT_DATA_0      : INTEGER := 16#0d0#;
    constant ADDR_PROJ_CONV_WEIGHT_DATA_1      : INTEGER := 16#0d4#;
    constant ADDR_PROJ_CONV_WEIGHT_CTRL        : INTEGER := 16#0d8#;
    constant ADDR_Y_MSP_CONV_DATA_0            : INTEGER := 16#0dc#;
    constant ADDR_Y_MSP_CONV_DATA_1            : INTEGER := 16#0e0#;
    constant ADDR_Y_MSP_CONV_CTRL              : INTEGER := 16#0e4#;
    constant ADDR_Y_MSP_NORM_DATA_0            : INTEGER := 16#0e8#;
    constant ADDR_Y_MSP_NORM_DATA_1            : INTEGER := 16#0ec#;
    constant ADDR_Y_MSP_NORM_CTRL              : INTEGER := 16#0f0#;
    constant ADDR_Y_DW_CONV_DATA_0             : INTEGER := 16#0f4#;
    constant ADDR_Y_DW_CONV_DATA_1             : INTEGER := 16#0f8#;
    constant ADDR_Y_DW_CONV_CTRL               : INTEGER := 16#0fc#;
    constant ADDR_Y_DW_NORM_DATA_0             : INTEGER := 16#100#;
    constant ADDR_Y_DW_NORM_DATA_1             : INTEGER := 16#104#;
    constant ADDR_Y_DW_NORM_CTRL               : INTEGER := 16#108#;
    constant ADDR_Y_DW_ACT_DATA_0              : INTEGER := 16#10c#;
    constant ADDR_Y_DW_ACT_DATA_1              : INTEGER := 16#110#;
    constant ADDR_Y_DW_ACT_CTRL                : INTEGER := 16#114#;
    constant ADDR_Y_SE_MEAN_DATA_0             : INTEGER := 16#118#;
    constant ADDR_Y_SE_MEAN_DATA_1             : INTEGER := 16#11c#;
    constant ADDR_Y_SE_MEAN_CTRL               : INTEGER := 16#120#;
    constant ADDR_Y_SE_REDUCE_DATA_0           : INTEGER := 16#124#;
    constant ADDR_Y_SE_REDUCE_DATA_1           : INTEGER := 16#128#;
    constant ADDR_Y_SE_REDUCE_CTRL             : INTEGER := 16#12c#;
    constant ADDR_Y_SE_ACT_DATA_0              : INTEGER := 16#130#;
    constant ADDR_Y_SE_ACT_DATA_1              : INTEGER := 16#134#;
    constant ADDR_Y_SE_ACT_CTRL                : INTEGER := 16#138#;
    constant ADDR_Y_SE_EXPAND_DATA_0           : INTEGER := 16#13c#;
    constant ADDR_Y_SE_EXPAND_DATA_1           : INTEGER := 16#140#;
    constant ADDR_Y_SE_EXPAND_CTRL             : INTEGER := 16#144#;
    constant ADDR_Y_SE_SIGMOID_DATA_0          : INTEGER := 16#148#;
    constant ADDR_Y_SE_SIGMOID_DATA_1          : INTEGER := 16#14c#;
    constant ADDR_Y_SE_SIGMOID_CTRL            : INTEGER := 16#150#;
    constant ADDR_Y_SE_DATA_0                  : INTEGER := 16#154#;
    constant ADDR_Y_SE_DATA_1                  : INTEGER := 16#158#;
    constant ADDR_Y_SE_CTRL                    : INTEGER := 16#15c#;
    constant ADDR_Y_PROJ_DATA_0                : INTEGER := 16#160#;
    constant ADDR_Y_PROJ_DATA_1                : INTEGER := 16#164#;
    constant ADDR_Y_PROJ_CTRL                  : INTEGER := 16#168#;
    constant ADDR_BITS         : INTEGER := 9;

    signal waddr               : UNSIGNED(ADDR_BITS-1 downto 0);
    signal wmask               : UNSIGNED(C_S_AXI_DATA_WIDTH-1 downto 0);
    signal aw_hs               : STD_LOGIC;
    signal w_hs                : STD_LOGIC;
    signal rdata_data          : UNSIGNED(C_S_AXI_DATA_WIDTH-1 downto 0);
    signal ar_hs               : STD_LOGIC;
    signal raddr               : UNSIGNED(ADDR_BITS-1 downto 0);
    signal AWREADY_t           : STD_LOGIC;
    signal WREADY_t            : STD_LOGIC;
    signal ARREADY_t           : STD_LOGIC;
    signal RVALID_t            : STD_LOGIC;
    -- internal registers
    signal int_X_data          : UNSIGNED(63 downto 0) := (others => '0');
    signal int_msp_conv_weight : UNSIGNED(63 downto 0) := (others => '0');
    signal int_msp_conv_bias   : UNSIGNED(63 downto 0) := (others => '0');
    signal int_msp_norm_weight : UNSIGNED(63 downto 0) := (others => '0');
    signal int_msp_norm_bias   : UNSIGNED(63 downto 0) := (others => '0');
    signal int_msp_norm_running_mean : UNSIGNED(63 downto 0) := (others => '0');
    signal int_msp_norm_running_var : UNSIGNED(63 downto 0) := (others => '0');
    signal int_dw_conv_weight  : UNSIGNED(63 downto 0) := (others => '0');
    signal int_norm_1_weight   : UNSIGNED(63 downto 0) := (others => '0');
    signal int_norm_1_bias     : UNSIGNED(63 downto 0) := (others => '0');
    signal int_norm_1_running_mean : UNSIGNED(63 downto 0) := (others => '0');
    signal int_norm_1_running_var : UNSIGNED(63 downto 0) := (others => '0');
    signal int_se_conv_reduce_weight : UNSIGNED(63 downto 0) := (others => '0');
    signal int_se_conv_reduce_bias : UNSIGNED(63 downto 0) := (others => '0');
    signal int_se_conv_expand_weight : UNSIGNED(63 downto 0) := (others => '0');
    signal int_se_conv_expand_bias : UNSIGNED(63 downto 0) := (others => '0');
    signal int_proj_conv_weight : UNSIGNED(63 downto 0) := (others => '0');
    signal int_Y_msp_conv      : UNSIGNED(63 downto 0) := (others => '0');
    signal int_Y_msp_norm      : UNSIGNED(63 downto 0) := (others => '0');
    signal int_Y_dw_conv       : UNSIGNED(63 downto 0) := (others => '0');
    signal int_Y_dw_norm       : UNSIGNED(63 downto 0) := (others => '0');
    signal int_Y_dw_act        : UNSIGNED(63 downto 0) := (others => '0');
    signal int_Y_se_mean       : UNSIGNED(63 downto 0) := (others => '0');
    signal int_Y_se_reduce     : UNSIGNED(63 downto 0) := (others => '0');
    signal int_Y_se_act        : UNSIGNED(63 downto 0) := (others => '0');
    signal int_Y_se_expand     : UNSIGNED(63 downto 0) := (others => '0');
    signal int_Y_se_sigmoid    : UNSIGNED(63 downto 0) := (others => '0');
    signal int_Y_se            : UNSIGNED(63 downto 0) := (others => '0');
    signal int_Y_proj          : UNSIGNED(63 downto 0) := (others => '0');


begin
-- ----------------------- Instantiation------------------


-- ----------------------- AXI WRITE ---------------------
    AWREADY_t <=  '1' when wstate = wridle else '0';
    AWREADY   <=  AWREADY_t;
    WREADY_t  <=  '1' when wstate = wrdata else '0';
    WREADY    <=  WREADY_t;
    BRESP     <=  "00";  -- OKAY
    BVALID    <=  '1' when wstate = wrresp else '0';
    wmask     <=  (31 downto 24 => WSTRB(3), 23 downto 16 => WSTRB(2), 15 downto 8 => WSTRB(1), 7 downto 0 => WSTRB(0));
    aw_hs     <=  AWVALID and AWREADY_t;
    w_hs      <=  WVALID and WREADY_t;

    -- write FSM
    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ARESET = '1') then
                wstate <= wrreset;
            elsif (ACLK_EN = '1') then
                wstate <= wnext;
            end if;
        end if;
    end process;

    process (wstate, AWVALID, WVALID, BREADY)
    begin
        case (wstate) is
        when wridle =>
            if (AWVALID = '1') then
                wnext <= wrdata;
            else
                wnext <= wridle;
            end if;
        when wrdata =>
            if (WVALID = '1') then
                wnext <= wrresp;
            else
                wnext <= wrdata;
            end if;
        when wrresp =>
            if (BREADY = '1') then
                wnext <= wridle;
            else
                wnext <= wrresp;
            end if;
        when others =>
            wnext <= wridle;
        end case;
    end process;

    waddr_proc : process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (aw_hs = '1') then
                    waddr <= UNSIGNED(AWADDR(ADDR_BITS-1 downto 0));
                end if;
            end if;
        end if;
    end process;

-- ----------------------- AXI READ ----------------------
    ARREADY_t <= '1' when (rstate = rdidle) else '0';
    ARREADY <= ARREADY_t;
    RDATA   <= STD_LOGIC_VECTOR(rdata_data);
    RRESP   <= "00";  -- OKAY
    RVALID_t  <= '1' when (rstate = rddata) else '0';
    RVALID    <= RVALID_t;
    ar_hs   <= ARVALID and ARREADY_t;
    raddr   <= UNSIGNED(ARADDR(ADDR_BITS-1 downto 0));

    -- read FSM
    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ARESET = '1') then
                rstate <= rdreset;
            elsif (ACLK_EN = '1') then
                rstate <= rnext;
            end if;
        end if;
    end process;

    process (rstate, ARVALID, RREADY, RVALID_t)
    begin
        case (rstate) is
        when rdidle =>
            if (ARVALID = '1') then
                rnext <= rddata;
            else
                rnext <= rdidle;
            end if;
        when rddata =>
            if (RREADY = '1' and RVALID_t = '1') then
                rnext <= rdidle;
            else
                rnext <= rddata;
            end if;
        when others =>
            rnext <= rdidle;
        end case;
    end process;

    rdata_proc : process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (ar_hs = '1') then
                    rdata_data <= (others => '0');
                    case (TO_INTEGER(raddr)) is
                    when ADDR_X_DATA_DATA_0 =>
                        rdata_data <= RESIZE(int_X_data(31 downto 0), 32);
                    when ADDR_X_DATA_DATA_1 =>
                        rdata_data <= RESIZE(int_X_data(63 downto 32), 32);
                    when ADDR_MSP_CONV_WEIGHT_DATA_0 =>
                        rdata_data <= RESIZE(int_msp_conv_weight(31 downto 0), 32);
                    when ADDR_MSP_CONV_WEIGHT_DATA_1 =>
                        rdata_data <= RESIZE(int_msp_conv_weight(63 downto 32), 32);
                    when ADDR_MSP_CONV_BIAS_DATA_0 =>
                        rdata_data <= RESIZE(int_msp_conv_bias(31 downto 0), 32);
                    when ADDR_MSP_CONV_BIAS_DATA_1 =>
                        rdata_data <= RESIZE(int_msp_conv_bias(63 downto 32), 32);
                    when ADDR_MSP_NORM_WEIGHT_DATA_0 =>
                        rdata_data <= RESIZE(int_msp_norm_weight(31 downto 0), 32);
                    when ADDR_MSP_NORM_WEIGHT_DATA_1 =>
                        rdata_data <= RESIZE(int_msp_norm_weight(63 downto 32), 32);
                    when ADDR_MSP_NORM_BIAS_DATA_0 =>
                        rdata_data <= RESIZE(int_msp_norm_bias(31 downto 0), 32);
                    when ADDR_MSP_NORM_BIAS_DATA_1 =>
                        rdata_data <= RESIZE(int_msp_norm_bias(63 downto 32), 32);
                    when ADDR_MSP_NORM_RUNNING_MEAN_DATA_0 =>
                        rdata_data <= RESIZE(int_msp_norm_running_mean(31 downto 0), 32);
                    when ADDR_MSP_NORM_RUNNING_MEAN_DATA_1 =>
                        rdata_data <= RESIZE(int_msp_norm_running_mean(63 downto 32), 32);
                    when ADDR_MSP_NORM_RUNNING_VAR_DATA_0 =>
                        rdata_data <= RESIZE(int_msp_norm_running_var(31 downto 0), 32);
                    when ADDR_MSP_NORM_RUNNING_VAR_DATA_1 =>
                        rdata_data <= RESIZE(int_msp_norm_running_var(63 downto 32), 32);
                    when ADDR_DW_CONV_WEIGHT_DATA_0 =>
                        rdata_data <= RESIZE(int_dw_conv_weight(31 downto 0), 32);
                    when ADDR_DW_CONV_WEIGHT_DATA_1 =>
                        rdata_data <= RESIZE(int_dw_conv_weight(63 downto 32), 32);
                    when ADDR_NORM_1_WEIGHT_DATA_0 =>
                        rdata_data <= RESIZE(int_norm_1_weight(31 downto 0), 32);
                    when ADDR_NORM_1_WEIGHT_DATA_1 =>
                        rdata_data <= RESIZE(int_norm_1_weight(63 downto 32), 32);
                    when ADDR_NORM_1_BIAS_DATA_0 =>
                        rdata_data <= RESIZE(int_norm_1_bias(31 downto 0), 32);
                    when ADDR_NORM_1_BIAS_DATA_1 =>
                        rdata_data <= RESIZE(int_norm_1_bias(63 downto 32), 32);
                    when ADDR_NORM_1_RUNNING_MEAN_DATA_0 =>
                        rdata_data <= RESIZE(int_norm_1_running_mean(31 downto 0), 32);
                    when ADDR_NORM_1_RUNNING_MEAN_DATA_1 =>
                        rdata_data <= RESIZE(int_norm_1_running_mean(63 downto 32), 32);
                    when ADDR_NORM_1_RUNNING_VAR_DATA_0 =>
                        rdata_data <= RESIZE(int_norm_1_running_var(31 downto 0), 32);
                    when ADDR_NORM_1_RUNNING_VAR_DATA_1 =>
                        rdata_data <= RESIZE(int_norm_1_running_var(63 downto 32), 32);
                    when ADDR_SE_CONV_REDUCE_WEIGHT_DATA_0 =>
                        rdata_data <= RESIZE(int_se_conv_reduce_weight(31 downto 0), 32);
                    when ADDR_SE_CONV_REDUCE_WEIGHT_DATA_1 =>
                        rdata_data <= RESIZE(int_se_conv_reduce_weight(63 downto 32), 32);
                    when ADDR_SE_CONV_REDUCE_BIAS_DATA_0 =>
                        rdata_data <= RESIZE(int_se_conv_reduce_bias(31 downto 0), 32);
                    when ADDR_SE_CONV_REDUCE_BIAS_DATA_1 =>
                        rdata_data <= RESIZE(int_se_conv_reduce_bias(63 downto 32), 32);
                    when ADDR_SE_CONV_EXPAND_WEIGHT_DATA_0 =>
                        rdata_data <= RESIZE(int_se_conv_expand_weight(31 downto 0), 32);
                    when ADDR_SE_CONV_EXPAND_WEIGHT_DATA_1 =>
                        rdata_data <= RESIZE(int_se_conv_expand_weight(63 downto 32), 32);
                    when ADDR_SE_CONV_EXPAND_BIAS_DATA_0 =>
                        rdata_data <= RESIZE(int_se_conv_expand_bias(31 downto 0), 32);
                    when ADDR_SE_CONV_EXPAND_BIAS_DATA_1 =>
                        rdata_data <= RESIZE(int_se_conv_expand_bias(63 downto 32), 32);
                    when ADDR_PROJ_CONV_WEIGHT_DATA_0 =>
                        rdata_data <= RESIZE(int_proj_conv_weight(31 downto 0), 32);
                    when ADDR_PROJ_CONV_WEIGHT_DATA_1 =>
                        rdata_data <= RESIZE(int_proj_conv_weight(63 downto 32), 32);
                    when ADDR_Y_MSP_CONV_DATA_0 =>
                        rdata_data <= RESIZE(int_Y_msp_conv(31 downto 0), 32);
                    when ADDR_Y_MSP_CONV_DATA_1 =>
                        rdata_data <= RESIZE(int_Y_msp_conv(63 downto 32), 32);
                    when ADDR_Y_MSP_NORM_DATA_0 =>
                        rdata_data <= RESIZE(int_Y_msp_norm(31 downto 0), 32);
                    when ADDR_Y_MSP_NORM_DATA_1 =>
                        rdata_data <= RESIZE(int_Y_msp_norm(63 downto 32), 32);
                    when ADDR_Y_DW_CONV_DATA_0 =>
                        rdata_data <= RESIZE(int_Y_dw_conv(31 downto 0), 32);
                    when ADDR_Y_DW_CONV_DATA_1 =>
                        rdata_data <= RESIZE(int_Y_dw_conv(63 downto 32), 32);
                    when ADDR_Y_DW_NORM_DATA_0 =>
                        rdata_data <= RESIZE(int_Y_dw_norm(31 downto 0), 32);
                    when ADDR_Y_DW_NORM_DATA_1 =>
                        rdata_data <= RESIZE(int_Y_dw_norm(63 downto 32), 32);
                    when ADDR_Y_DW_ACT_DATA_0 =>
                        rdata_data <= RESIZE(int_Y_dw_act(31 downto 0), 32);
                    when ADDR_Y_DW_ACT_DATA_1 =>
                        rdata_data <= RESIZE(int_Y_dw_act(63 downto 32), 32);
                    when ADDR_Y_SE_MEAN_DATA_0 =>
                        rdata_data <= RESIZE(int_Y_se_mean(31 downto 0), 32);
                    when ADDR_Y_SE_MEAN_DATA_1 =>
                        rdata_data <= RESIZE(int_Y_se_mean(63 downto 32), 32);
                    when ADDR_Y_SE_REDUCE_DATA_0 =>
                        rdata_data <= RESIZE(int_Y_se_reduce(31 downto 0), 32);
                    when ADDR_Y_SE_REDUCE_DATA_1 =>
                        rdata_data <= RESIZE(int_Y_se_reduce(63 downto 32), 32);
                    when ADDR_Y_SE_ACT_DATA_0 =>
                        rdata_data <= RESIZE(int_Y_se_act(31 downto 0), 32);
                    when ADDR_Y_SE_ACT_DATA_1 =>
                        rdata_data <= RESIZE(int_Y_se_act(63 downto 32), 32);
                    when ADDR_Y_SE_EXPAND_DATA_0 =>
                        rdata_data <= RESIZE(int_Y_se_expand(31 downto 0), 32);
                    when ADDR_Y_SE_EXPAND_DATA_1 =>
                        rdata_data <= RESIZE(int_Y_se_expand(63 downto 32), 32);
                    when ADDR_Y_SE_SIGMOID_DATA_0 =>
                        rdata_data <= RESIZE(int_Y_se_sigmoid(31 downto 0), 32);
                    when ADDR_Y_SE_SIGMOID_DATA_1 =>
                        rdata_data <= RESIZE(int_Y_se_sigmoid(63 downto 32), 32);
                    when ADDR_Y_SE_DATA_0 =>
                        rdata_data <= RESIZE(int_Y_se(31 downto 0), 32);
                    when ADDR_Y_SE_DATA_1 =>
                        rdata_data <= RESIZE(int_Y_se(63 downto 32), 32);
                    when ADDR_Y_PROJ_DATA_0 =>
                        rdata_data <= RESIZE(int_Y_proj(31 downto 0), 32);
                    when ADDR_Y_PROJ_DATA_1 =>
                        rdata_data <= RESIZE(int_Y_proj(63 downto 32), 32);
                    when others =>
                        NULL;
                    end case;
                end if;
            end if;
        end if;
    end process;

-- ----------------------- Register logic ----------------
    X_data               <= STD_LOGIC_VECTOR(int_X_data);
    msp_conv_weight      <= STD_LOGIC_VECTOR(int_msp_conv_weight);
    msp_conv_bias        <= STD_LOGIC_VECTOR(int_msp_conv_bias);
    msp_norm_weight      <= STD_LOGIC_VECTOR(int_msp_norm_weight);
    msp_norm_bias        <= STD_LOGIC_VECTOR(int_msp_norm_bias);
    msp_norm_running_mean <= STD_LOGIC_VECTOR(int_msp_norm_running_mean);
    msp_norm_running_var <= STD_LOGIC_VECTOR(int_msp_norm_running_var);
    dw_conv_weight       <= STD_LOGIC_VECTOR(int_dw_conv_weight);
    norm_1_weight        <= STD_LOGIC_VECTOR(int_norm_1_weight);
    norm_1_bias          <= STD_LOGIC_VECTOR(int_norm_1_bias);
    norm_1_running_mean  <= STD_LOGIC_VECTOR(int_norm_1_running_mean);
    norm_1_running_var   <= STD_LOGIC_VECTOR(int_norm_1_running_var);
    se_conv_reduce_weight <= STD_LOGIC_VECTOR(int_se_conv_reduce_weight);
    se_conv_reduce_bias  <= STD_LOGIC_VECTOR(int_se_conv_reduce_bias);
    se_conv_expand_weight <= STD_LOGIC_VECTOR(int_se_conv_expand_weight);
    se_conv_expand_bias  <= STD_LOGIC_VECTOR(int_se_conv_expand_bias);
    proj_conv_weight     <= STD_LOGIC_VECTOR(int_proj_conv_weight);
    Y_msp_conv           <= STD_LOGIC_VECTOR(int_Y_msp_conv);
    Y_msp_norm           <= STD_LOGIC_VECTOR(int_Y_msp_norm);
    Y_dw_conv            <= STD_LOGIC_VECTOR(int_Y_dw_conv);
    Y_dw_norm            <= STD_LOGIC_VECTOR(int_Y_dw_norm);
    Y_dw_act             <= STD_LOGIC_VECTOR(int_Y_dw_act);
    Y_se_mean            <= STD_LOGIC_VECTOR(int_Y_se_mean);
    Y_se_reduce          <= STD_LOGIC_VECTOR(int_Y_se_reduce);
    Y_se_act             <= STD_LOGIC_VECTOR(int_Y_se_act);
    Y_se_expand          <= STD_LOGIC_VECTOR(int_Y_se_expand);
    Y_se_sigmoid         <= STD_LOGIC_VECTOR(int_Y_se_sigmoid);
    Y_se                 <= STD_LOGIC_VECTOR(int_Y_se);
    Y_proj               <= STD_LOGIC_VECTOR(int_Y_proj);

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_X_DATA_DATA_0) then
                    int_X_data(31 downto 0) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_X_data(31 downto 0));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_X_DATA_DATA_1) then
                    int_X_data(63 downto 32) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_X_data(63 downto 32));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_MSP_CONV_WEIGHT_DATA_0) then
                    int_msp_conv_weight(31 downto 0) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_msp_conv_weight(31 downto 0));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_MSP_CONV_WEIGHT_DATA_1) then
                    int_msp_conv_weight(63 downto 32) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_msp_conv_weight(63 downto 32));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_MSP_CONV_BIAS_DATA_0) then
                    int_msp_conv_bias(31 downto 0) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_msp_conv_bias(31 downto 0));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_MSP_CONV_BIAS_DATA_1) then
                    int_msp_conv_bias(63 downto 32) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_msp_conv_bias(63 downto 32));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_MSP_NORM_WEIGHT_DATA_0) then
                    int_msp_norm_weight(31 downto 0) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_msp_norm_weight(31 downto 0));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_MSP_NORM_WEIGHT_DATA_1) then
                    int_msp_norm_weight(63 downto 32) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_msp_norm_weight(63 downto 32));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_MSP_NORM_BIAS_DATA_0) then
                    int_msp_norm_bias(31 downto 0) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_msp_norm_bias(31 downto 0));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_MSP_NORM_BIAS_DATA_1) then
                    int_msp_norm_bias(63 downto 32) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_msp_norm_bias(63 downto 32));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_MSP_NORM_RUNNING_MEAN_DATA_0) then
                    int_msp_norm_running_mean(31 downto 0) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_msp_norm_running_mean(31 downto 0));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_MSP_NORM_RUNNING_MEAN_DATA_1) then
                    int_msp_norm_running_mean(63 downto 32) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_msp_norm_running_mean(63 downto 32));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_MSP_NORM_RUNNING_VAR_DATA_0) then
                    int_msp_norm_running_var(31 downto 0) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_msp_norm_running_var(31 downto 0));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_MSP_NORM_RUNNING_VAR_DATA_1) then
                    int_msp_norm_running_var(63 downto 32) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_msp_norm_running_var(63 downto 32));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_DW_CONV_WEIGHT_DATA_0) then
                    int_dw_conv_weight(31 downto 0) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_dw_conv_weight(31 downto 0));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_DW_CONV_WEIGHT_DATA_1) then
                    int_dw_conv_weight(63 downto 32) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_dw_conv_weight(63 downto 32));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_NORM_1_WEIGHT_DATA_0) then
                    int_norm_1_weight(31 downto 0) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_norm_1_weight(31 downto 0));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_NORM_1_WEIGHT_DATA_1) then
                    int_norm_1_weight(63 downto 32) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_norm_1_weight(63 downto 32));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_NORM_1_BIAS_DATA_0) then
                    int_norm_1_bias(31 downto 0) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_norm_1_bias(31 downto 0));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_NORM_1_BIAS_DATA_1) then
                    int_norm_1_bias(63 downto 32) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_norm_1_bias(63 downto 32));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_NORM_1_RUNNING_MEAN_DATA_0) then
                    int_norm_1_running_mean(31 downto 0) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_norm_1_running_mean(31 downto 0));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_NORM_1_RUNNING_MEAN_DATA_1) then
                    int_norm_1_running_mean(63 downto 32) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_norm_1_running_mean(63 downto 32));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_NORM_1_RUNNING_VAR_DATA_0) then
                    int_norm_1_running_var(31 downto 0) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_norm_1_running_var(31 downto 0));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_NORM_1_RUNNING_VAR_DATA_1) then
                    int_norm_1_running_var(63 downto 32) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_norm_1_running_var(63 downto 32));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_SE_CONV_REDUCE_WEIGHT_DATA_0) then
                    int_se_conv_reduce_weight(31 downto 0) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_se_conv_reduce_weight(31 downto 0));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_SE_CONV_REDUCE_WEIGHT_DATA_1) then
                    int_se_conv_reduce_weight(63 downto 32) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_se_conv_reduce_weight(63 downto 32));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_SE_CONV_REDUCE_BIAS_DATA_0) then
                    int_se_conv_reduce_bias(31 downto 0) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_se_conv_reduce_bias(31 downto 0));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_SE_CONV_REDUCE_BIAS_DATA_1) then
                    int_se_conv_reduce_bias(63 downto 32) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_se_conv_reduce_bias(63 downto 32));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_SE_CONV_EXPAND_WEIGHT_DATA_0) then
                    int_se_conv_expand_weight(31 downto 0) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_se_conv_expand_weight(31 downto 0));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_SE_CONV_EXPAND_WEIGHT_DATA_1) then
                    int_se_conv_expand_weight(63 downto 32) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_se_conv_expand_weight(63 downto 32));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_SE_CONV_EXPAND_BIAS_DATA_0) then
                    int_se_conv_expand_bias(31 downto 0) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_se_conv_expand_bias(31 downto 0));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_SE_CONV_EXPAND_BIAS_DATA_1) then
                    int_se_conv_expand_bias(63 downto 32) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_se_conv_expand_bias(63 downto 32));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_PROJ_CONV_WEIGHT_DATA_0) then
                    int_proj_conv_weight(31 downto 0) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_proj_conv_weight(31 downto 0));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_PROJ_CONV_WEIGHT_DATA_1) then
                    int_proj_conv_weight(63 downto 32) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_proj_conv_weight(63 downto 32));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_Y_MSP_CONV_DATA_0) then
                    int_Y_msp_conv(31 downto 0) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_Y_msp_conv(31 downto 0));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_Y_MSP_CONV_DATA_1) then
                    int_Y_msp_conv(63 downto 32) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_Y_msp_conv(63 downto 32));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_Y_MSP_NORM_DATA_0) then
                    int_Y_msp_norm(31 downto 0) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_Y_msp_norm(31 downto 0));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_Y_MSP_NORM_DATA_1) then
                    int_Y_msp_norm(63 downto 32) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_Y_msp_norm(63 downto 32));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_Y_DW_CONV_DATA_0) then
                    int_Y_dw_conv(31 downto 0) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_Y_dw_conv(31 downto 0));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_Y_DW_CONV_DATA_1) then
                    int_Y_dw_conv(63 downto 32) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_Y_dw_conv(63 downto 32));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_Y_DW_NORM_DATA_0) then
                    int_Y_dw_norm(31 downto 0) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_Y_dw_norm(31 downto 0));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_Y_DW_NORM_DATA_1) then
                    int_Y_dw_norm(63 downto 32) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_Y_dw_norm(63 downto 32));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_Y_DW_ACT_DATA_0) then
                    int_Y_dw_act(31 downto 0) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_Y_dw_act(31 downto 0));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_Y_DW_ACT_DATA_1) then
                    int_Y_dw_act(63 downto 32) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_Y_dw_act(63 downto 32));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_Y_SE_MEAN_DATA_0) then
                    int_Y_se_mean(31 downto 0) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_Y_se_mean(31 downto 0));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_Y_SE_MEAN_DATA_1) then
                    int_Y_se_mean(63 downto 32) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_Y_se_mean(63 downto 32));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_Y_SE_REDUCE_DATA_0) then
                    int_Y_se_reduce(31 downto 0) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_Y_se_reduce(31 downto 0));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_Y_SE_REDUCE_DATA_1) then
                    int_Y_se_reduce(63 downto 32) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_Y_se_reduce(63 downto 32));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_Y_SE_ACT_DATA_0) then
                    int_Y_se_act(31 downto 0) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_Y_se_act(31 downto 0));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_Y_SE_ACT_DATA_1) then
                    int_Y_se_act(63 downto 32) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_Y_se_act(63 downto 32));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_Y_SE_EXPAND_DATA_0) then
                    int_Y_se_expand(31 downto 0) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_Y_se_expand(31 downto 0));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_Y_SE_EXPAND_DATA_1) then
                    int_Y_se_expand(63 downto 32) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_Y_se_expand(63 downto 32));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_Y_SE_SIGMOID_DATA_0) then
                    int_Y_se_sigmoid(31 downto 0) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_Y_se_sigmoid(31 downto 0));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_Y_SE_SIGMOID_DATA_1) then
                    int_Y_se_sigmoid(63 downto 32) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_Y_se_sigmoid(63 downto 32));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_Y_SE_DATA_0) then
                    int_Y_se(31 downto 0) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_Y_se(31 downto 0));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_Y_SE_DATA_1) then
                    int_Y_se(63 downto 32) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_Y_se(63 downto 32));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_Y_PROJ_DATA_0) then
                    int_Y_proj(31 downto 0) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_Y_proj(31 downto 0));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_Y_PROJ_DATA_1) then
                    int_Y_proj(63 downto 32) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_Y_proj(63 downto 32));
                end if;
            end if;
        end if;
    end process;


-- ----------------------- Memory logic ------------------

end architecture behave;
