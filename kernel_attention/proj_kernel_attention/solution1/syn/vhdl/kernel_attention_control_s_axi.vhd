-- ==============================================================
-- Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2022.1 (64-bit)
-- Tool Version Limit: 2022.04
-- Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
-- ==============================================================
library IEEE;
use IEEE.STD_LOGIC_1164.all;
use IEEE.NUMERIC_STD.all;

entity kernel_attention_control_s_axi is
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
    buffer_DataIn_1       :out  STD_LOGIC_VECTOR(63 downto 0);
    afterNorm             :out  STD_LOGIC_VECTOR(63 downto 0);
    norm1_mean            :out  STD_LOGIC_VECTOR(63 downto 0);
    norm1_var             :out  STD_LOGIC_VECTOR(63 downto 0);
    norm1_weight          :out  STD_LOGIC_VECTOR(63 downto 0);
    norm1_bias            :out  STD_LOGIC_VECTOR(63 downto 0);
    afterPad              :out  STD_LOGIC_VECTOR(63 downto 0);
    afterRearrangeX       :out  STD_LOGIC_VECTOR(63 downto 0);
    afterPad1             :out  STD_LOGIC_VECTOR(63 downto 0);
    afterConv1            :out  STD_LOGIC_VECTOR(63 downto 0);
    kernel1               :out  STD_LOGIC_VECTOR(63 downto 0);
    bias1                 :out  STD_LOGIC_VECTOR(63 downto 0);
    in_qk                 :out  STD_LOGIC_VECTOR(63 downto 0);
    in_q                  :out  STD_LOGIC_VECTOR(63 downto 0);
    in_k                  :out  STD_LOGIC_VECTOR(63 downto 0);
    afterQKMultiplication :out  STD_LOGIC_VECTOR(63 downto 0);
    afterSoftmax          :out  STD_LOGIC_VECTOR(63 downto 0);
    afterRearrangeX2      :out  STD_LOGIC_VECTOR(63 downto 0);
    afterQKXMultiplication :out  STD_LOGIC_VECTOR(63 downto 0);
    afterRearrangeQKX     :out  STD_LOGIC_VECTOR(63 downto 0);
    afterPad2             :out  STD_LOGIC_VECTOR(63 downto 0);
    afterConv2            :out  STD_LOGIC_VECTOR(63 downto 0);
    kernel2               :out  STD_LOGIC_VECTOR(63 downto 0);
    bias2                 :out  STD_LOGIC_VECTOR(63 downto 0);
    afterAct2             :out  STD_LOGIC_VECTOR(63 downto 0);
    QKV                   :out  STD_LOGIC_VECTOR(63 downto 0);
    buffer_out            :out  STD_LOGIC_VECTOR(63 downto 0);
    buffer_result         :out  STD_LOGIC_VECTOR(63 downto 0)
);
end entity kernel_attention_control_s_axi;

-- ------------------------Address Info-------------------
-- 0x000 : reserved
-- 0x004 : reserved
-- 0x008 : reserved
-- 0x00c : reserved
-- 0x010 : Data signal of buffer_DataIn_1
--         bit 31~0 - buffer_DataIn_1[31:0] (Read/Write)
-- 0x014 : Data signal of buffer_DataIn_1
--         bit 31~0 - buffer_DataIn_1[63:32] (Read/Write)
-- 0x018 : reserved
-- 0x01c : Data signal of afterNorm
--         bit 31~0 - afterNorm[31:0] (Read/Write)
-- 0x020 : Data signal of afterNorm
--         bit 31~0 - afterNorm[63:32] (Read/Write)
-- 0x024 : reserved
-- 0x028 : Data signal of norm1_mean
--         bit 31~0 - norm1_mean[31:0] (Read/Write)
-- 0x02c : Data signal of norm1_mean
--         bit 31~0 - norm1_mean[63:32] (Read/Write)
-- 0x030 : reserved
-- 0x034 : Data signal of norm1_var
--         bit 31~0 - norm1_var[31:0] (Read/Write)
-- 0x038 : Data signal of norm1_var
--         bit 31~0 - norm1_var[63:32] (Read/Write)
-- 0x03c : reserved
-- 0x040 : Data signal of norm1_weight
--         bit 31~0 - norm1_weight[31:0] (Read/Write)
-- 0x044 : Data signal of norm1_weight
--         bit 31~0 - norm1_weight[63:32] (Read/Write)
-- 0x048 : reserved
-- 0x04c : Data signal of norm1_bias
--         bit 31~0 - norm1_bias[31:0] (Read/Write)
-- 0x050 : Data signal of norm1_bias
--         bit 31~0 - norm1_bias[63:32] (Read/Write)
-- 0x054 : reserved
-- 0x058 : Data signal of afterPad
--         bit 31~0 - afterPad[31:0] (Read/Write)
-- 0x05c : Data signal of afterPad
--         bit 31~0 - afterPad[63:32] (Read/Write)
-- 0x060 : reserved
-- 0x064 : Data signal of afterRearrangeX
--         bit 31~0 - afterRearrangeX[31:0] (Read/Write)
-- 0x068 : Data signal of afterRearrangeX
--         bit 31~0 - afterRearrangeX[63:32] (Read/Write)
-- 0x06c : reserved
-- 0x070 : Data signal of afterPad1
--         bit 31~0 - afterPad1[31:0] (Read/Write)
-- 0x074 : Data signal of afterPad1
--         bit 31~0 - afterPad1[63:32] (Read/Write)
-- 0x078 : reserved
-- 0x07c : Data signal of afterConv1
--         bit 31~0 - afterConv1[31:0] (Read/Write)
-- 0x080 : Data signal of afterConv1
--         bit 31~0 - afterConv1[63:32] (Read/Write)
-- 0x084 : reserved
-- 0x088 : Data signal of kernel1
--         bit 31~0 - kernel1[31:0] (Read/Write)
-- 0x08c : Data signal of kernel1
--         bit 31~0 - kernel1[63:32] (Read/Write)
-- 0x090 : reserved
-- 0x094 : Data signal of bias1
--         bit 31~0 - bias1[31:0] (Read/Write)
-- 0x098 : Data signal of bias1
--         bit 31~0 - bias1[63:32] (Read/Write)
-- 0x09c : reserved
-- 0x0a0 : Data signal of in_qk
--         bit 31~0 - in_qk[31:0] (Read/Write)
-- 0x0a4 : Data signal of in_qk
--         bit 31~0 - in_qk[63:32] (Read/Write)
-- 0x0a8 : reserved
-- 0x0ac : Data signal of in_q
--         bit 31~0 - in_q[31:0] (Read/Write)
-- 0x0b0 : Data signal of in_q
--         bit 31~0 - in_q[63:32] (Read/Write)
-- 0x0b4 : reserved
-- 0x0b8 : Data signal of in_k
--         bit 31~0 - in_k[31:0] (Read/Write)
-- 0x0bc : Data signal of in_k
--         bit 31~0 - in_k[63:32] (Read/Write)
-- 0x0c0 : reserved
-- 0x0c4 : Data signal of afterQKMultiplication
--         bit 31~0 - afterQKMultiplication[31:0] (Read/Write)
-- 0x0c8 : Data signal of afterQKMultiplication
--         bit 31~0 - afterQKMultiplication[63:32] (Read/Write)
-- 0x0cc : reserved
-- 0x0d0 : Data signal of afterSoftmax
--         bit 31~0 - afterSoftmax[31:0] (Read/Write)
-- 0x0d4 : Data signal of afterSoftmax
--         bit 31~0 - afterSoftmax[63:32] (Read/Write)
-- 0x0d8 : reserved
-- 0x0dc : Data signal of afterRearrangeX2
--         bit 31~0 - afterRearrangeX2[31:0] (Read/Write)
-- 0x0e0 : Data signal of afterRearrangeX2
--         bit 31~0 - afterRearrangeX2[63:32] (Read/Write)
-- 0x0e4 : reserved
-- 0x0e8 : Data signal of afterQKXMultiplication
--         bit 31~0 - afterQKXMultiplication[31:0] (Read/Write)
-- 0x0ec : Data signal of afterQKXMultiplication
--         bit 31~0 - afterQKXMultiplication[63:32] (Read/Write)
-- 0x0f0 : reserved
-- 0x0f4 : Data signal of afterRearrangeQKX
--         bit 31~0 - afterRearrangeQKX[31:0] (Read/Write)
-- 0x0f8 : Data signal of afterRearrangeQKX
--         bit 31~0 - afterRearrangeQKX[63:32] (Read/Write)
-- 0x0fc : reserved
-- 0x100 : Data signal of afterPad2
--         bit 31~0 - afterPad2[31:0] (Read/Write)
-- 0x104 : Data signal of afterPad2
--         bit 31~0 - afterPad2[63:32] (Read/Write)
-- 0x108 : reserved
-- 0x10c : Data signal of afterConv2
--         bit 31~0 - afterConv2[31:0] (Read/Write)
-- 0x110 : Data signal of afterConv2
--         bit 31~0 - afterConv2[63:32] (Read/Write)
-- 0x114 : reserved
-- 0x118 : Data signal of kernel2
--         bit 31~0 - kernel2[31:0] (Read/Write)
-- 0x11c : Data signal of kernel2
--         bit 31~0 - kernel2[63:32] (Read/Write)
-- 0x120 : reserved
-- 0x124 : Data signal of bias2
--         bit 31~0 - bias2[31:0] (Read/Write)
-- 0x128 : Data signal of bias2
--         bit 31~0 - bias2[63:32] (Read/Write)
-- 0x12c : reserved
-- 0x130 : Data signal of afterAct2
--         bit 31~0 - afterAct2[31:0] (Read/Write)
-- 0x134 : Data signal of afterAct2
--         bit 31~0 - afterAct2[63:32] (Read/Write)
-- 0x138 : reserved
-- 0x13c : Data signal of QKV
--         bit 31~0 - QKV[31:0] (Read/Write)
-- 0x140 : Data signal of QKV
--         bit 31~0 - QKV[63:32] (Read/Write)
-- 0x144 : reserved
-- 0x148 : Data signal of buffer_out
--         bit 31~0 - buffer_out[31:0] (Read/Write)
-- 0x14c : Data signal of buffer_out
--         bit 31~0 - buffer_out[63:32] (Read/Write)
-- 0x150 : reserved
-- 0x154 : Data signal of buffer_result
--         bit 31~0 - buffer_result[31:0] (Read/Write)
-- 0x158 : Data signal of buffer_result
--         bit 31~0 - buffer_result[63:32] (Read/Write)
-- 0x15c : reserved
-- (SC = Self Clear, COR = Clear on Read, TOW = Toggle on Write, COH = Clear on Handshake)

architecture behave of kernel_attention_control_s_axi is
    type states is (wridle, wrdata, wrresp, wrreset, rdidle, rddata, rdreset);  -- read and write fsm states
    signal wstate  : states := wrreset;
    signal rstate  : states := rdreset;
    signal wnext, rnext: states;
    constant ADDR_BUFFER_DATAIN_1_DATA_0        : INTEGER := 16#010#;
    constant ADDR_BUFFER_DATAIN_1_DATA_1        : INTEGER := 16#014#;
    constant ADDR_BUFFER_DATAIN_1_CTRL          : INTEGER := 16#018#;
    constant ADDR_AFTERNORM_DATA_0              : INTEGER := 16#01c#;
    constant ADDR_AFTERNORM_DATA_1              : INTEGER := 16#020#;
    constant ADDR_AFTERNORM_CTRL                : INTEGER := 16#024#;
    constant ADDR_NORM1_MEAN_DATA_0             : INTEGER := 16#028#;
    constant ADDR_NORM1_MEAN_DATA_1             : INTEGER := 16#02c#;
    constant ADDR_NORM1_MEAN_CTRL               : INTEGER := 16#030#;
    constant ADDR_NORM1_VAR_DATA_0              : INTEGER := 16#034#;
    constant ADDR_NORM1_VAR_DATA_1              : INTEGER := 16#038#;
    constant ADDR_NORM1_VAR_CTRL                : INTEGER := 16#03c#;
    constant ADDR_NORM1_WEIGHT_DATA_0           : INTEGER := 16#040#;
    constant ADDR_NORM1_WEIGHT_DATA_1           : INTEGER := 16#044#;
    constant ADDR_NORM1_WEIGHT_CTRL             : INTEGER := 16#048#;
    constant ADDR_NORM1_BIAS_DATA_0             : INTEGER := 16#04c#;
    constant ADDR_NORM1_BIAS_DATA_1             : INTEGER := 16#050#;
    constant ADDR_NORM1_BIAS_CTRL               : INTEGER := 16#054#;
    constant ADDR_AFTERPAD_DATA_0               : INTEGER := 16#058#;
    constant ADDR_AFTERPAD_DATA_1               : INTEGER := 16#05c#;
    constant ADDR_AFTERPAD_CTRL                 : INTEGER := 16#060#;
    constant ADDR_AFTERREARRANGEX_DATA_0        : INTEGER := 16#064#;
    constant ADDR_AFTERREARRANGEX_DATA_1        : INTEGER := 16#068#;
    constant ADDR_AFTERREARRANGEX_CTRL          : INTEGER := 16#06c#;
    constant ADDR_AFTERPAD1_DATA_0              : INTEGER := 16#070#;
    constant ADDR_AFTERPAD1_DATA_1              : INTEGER := 16#074#;
    constant ADDR_AFTERPAD1_CTRL                : INTEGER := 16#078#;
    constant ADDR_AFTERCONV1_DATA_0             : INTEGER := 16#07c#;
    constant ADDR_AFTERCONV1_DATA_1             : INTEGER := 16#080#;
    constant ADDR_AFTERCONV1_CTRL               : INTEGER := 16#084#;
    constant ADDR_KERNEL1_DATA_0                : INTEGER := 16#088#;
    constant ADDR_KERNEL1_DATA_1                : INTEGER := 16#08c#;
    constant ADDR_KERNEL1_CTRL                  : INTEGER := 16#090#;
    constant ADDR_BIAS1_DATA_0                  : INTEGER := 16#094#;
    constant ADDR_BIAS1_DATA_1                  : INTEGER := 16#098#;
    constant ADDR_BIAS1_CTRL                    : INTEGER := 16#09c#;
    constant ADDR_IN_QK_DATA_0                  : INTEGER := 16#0a0#;
    constant ADDR_IN_QK_DATA_1                  : INTEGER := 16#0a4#;
    constant ADDR_IN_QK_CTRL                    : INTEGER := 16#0a8#;
    constant ADDR_IN_Q_DATA_0                   : INTEGER := 16#0ac#;
    constant ADDR_IN_Q_DATA_1                   : INTEGER := 16#0b0#;
    constant ADDR_IN_Q_CTRL                     : INTEGER := 16#0b4#;
    constant ADDR_IN_K_DATA_0                   : INTEGER := 16#0b8#;
    constant ADDR_IN_K_DATA_1                   : INTEGER := 16#0bc#;
    constant ADDR_IN_K_CTRL                     : INTEGER := 16#0c0#;
    constant ADDR_AFTERQKMULTIPLICATION_DATA_0  : INTEGER := 16#0c4#;
    constant ADDR_AFTERQKMULTIPLICATION_DATA_1  : INTEGER := 16#0c8#;
    constant ADDR_AFTERQKMULTIPLICATION_CTRL    : INTEGER := 16#0cc#;
    constant ADDR_AFTERSOFTMAX_DATA_0           : INTEGER := 16#0d0#;
    constant ADDR_AFTERSOFTMAX_DATA_1           : INTEGER := 16#0d4#;
    constant ADDR_AFTERSOFTMAX_CTRL             : INTEGER := 16#0d8#;
    constant ADDR_AFTERREARRANGEX2_DATA_0       : INTEGER := 16#0dc#;
    constant ADDR_AFTERREARRANGEX2_DATA_1       : INTEGER := 16#0e0#;
    constant ADDR_AFTERREARRANGEX2_CTRL         : INTEGER := 16#0e4#;
    constant ADDR_AFTERQKXMULTIPLICATION_DATA_0 : INTEGER := 16#0e8#;
    constant ADDR_AFTERQKXMULTIPLICATION_DATA_1 : INTEGER := 16#0ec#;
    constant ADDR_AFTERQKXMULTIPLICATION_CTRL   : INTEGER := 16#0f0#;
    constant ADDR_AFTERREARRANGEQKX_DATA_0      : INTEGER := 16#0f4#;
    constant ADDR_AFTERREARRANGEQKX_DATA_1      : INTEGER := 16#0f8#;
    constant ADDR_AFTERREARRANGEQKX_CTRL        : INTEGER := 16#0fc#;
    constant ADDR_AFTERPAD2_DATA_0              : INTEGER := 16#100#;
    constant ADDR_AFTERPAD2_DATA_1              : INTEGER := 16#104#;
    constant ADDR_AFTERPAD2_CTRL                : INTEGER := 16#108#;
    constant ADDR_AFTERCONV2_DATA_0             : INTEGER := 16#10c#;
    constant ADDR_AFTERCONV2_DATA_1             : INTEGER := 16#110#;
    constant ADDR_AFTERCONV2_CTRL               : INTEGER := 16#114#;
    constant ADDR_KERNEL2_DATA_0                : INTEGER := 16#118#;
    constant ADDR_KERNEL2_DATA_1                : INTEGER := 16#11c#;
    constant ADDR_KERNEL2_CTRL                  : INTEGER := 16#120#;
    constant ADDR_BIAS2_DATA_0                  : INTEGER := 16#124#;
    constant ADDR_BIAS2_DATA_1                  : INTEGER := 16#128#;
    constant ADDR_BIAS2_CTRL                    : INTEGER := 16#12c#;
    constant ADDR_AFTERACT2_DATA_0              : INTEGER := 16#130#;
    constant ADDR_AFTERACT2_DATA_1              : INTEGER := 16#134#;
    constant ADDR_AFTERACT2_CTRL                : INTEGER := 16#138#;
    constant ADDR_QKV_DATA_0                    : INTEGER := 16#13c#;
    constant ADDR_QKV_DATA_1                    : INTEGER := 16#140#;
    constant ADDR_QKV_CTRL                      : INTEGER := 16#144#;
    constant ADDR_BUFFER_OUT_DATA_0             : INTEGER := 16#148#;
    constant ADDR_BUFFER_OUT_DATA_1             : INTEGER := 16#14c#;
    constant ADDR_BUFFER_OUT_CTRL               : INTEGER := 16#150#;
    constant ADDR_BUFFER_RESULT_DATA_0          : INTEGER := 16#154#;
    constant ADDR_BUFFER_RESULT_DATA_1          : INTEGER := 16#158#;
    constant ADDR_BUFFER_RESULT_CTRL            : INTEGER := 16#15c#;
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
    signal int_buffer_DataIn_1 : UNSIGNED(63 downto 0) := (others => '0');
    signal int_afterNorm       : UNSIGNED(63 downto 0) := (others => '0');
    signal int_norm1_mean      : UNSIGNED(63 downto 0) := (others => '0');
    signal int_norm1_var       : UNSIGNED(63 downto 0) := (others => '0');
    signal int_norm1_weight    : UNSIGNED(63 downto 0) := (others => '0');
    signal int_norm1_bias      : UNSIGNED(63 downto 0) := (others => '0');
    signal int_afterPad        : UNSIGNED(63 downto 0) := (others => '0');
    signal int_afterRearrangeX : UNSIGNED(63 downto 0) := (others => '0');
    signal int_afterPad1       : UNSIGNED(63 downto 0) := (others => '0');
    signal int_afterConv1      : UNSIGNED(63 downto 0) := (others => '0');
    signal int_kernel1         : UNSIGNED(63 downto 0) := (others => '0');
    signal int_bias1           : UNSIGNED(63 downto 0) := (others => '0');
    signal int_in_qk           : UNSIGNED(63 downto 0) := (others => '0');
    signal int_in_q            : UNSIGNED(63 downto 0) := (others => '0');
    signal int_in_k            : UNSIGNED(63 downto 0) := (others => '0');
    signal int_afterQKMultiplication : UNSIGNED(63 downto 0) := (others => '0');
    signal int_afterSoftmax    : UNSIGNED(63 downto 0) := (others => '0');
    signal int_afterRearrangeX2 : UNSIGNED(63 downto 0) := (others => '0');
    signal int_afterQKXMultiplication : UNSIGNED(63 downto 0) := (others => '0');
    signal int_afterRearrangeQKX : UNSIGNED(63 downto 0) := (others => '0');
    signal int_afterPad2       : UNSIGNED(63 downto 0) := (others => '0');
    signal int_afterConv2      : UNSIGNED(63 downto 0) := (others => '0');
    signal int_kernel2         : UNSIGNED(63 downto 0) := (others => '0');
    signal int_bias2           : UNSIGNED(63 downto 0) := (others => '0');
    signal int_afterAct2       : UNSIGNED(63 downto 0) := (others => '0');
    signal int_QKV             : UNSIGNED(63 downto 0) := (others => '0');
    signal int_buffer_out      : UNSIGNED(63 downto 0) := (others => '0');
    signal int_buffer_result   : UNSIGNED(63 downto 0) := (others => '0');


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
                    when ADDR_BUFFER_DATAIN_1_DATA_0 =>
                        rdata_data <= RESIZE(int_buffer_DataIn_1(31 downto 0), 32);
                    when ADDR_BUFFER_DATAIN_1_DATA_1 =>
                        rdata_data <= RESIZE(int_buffer_DataIn_1(63 downto 32), 32);
                    when ADDR_AFTERNORM_DATA_0 =>
                        rdata_data <= RESIZE(int_afterNorm(31 downto 0), 32);
                    when ADDR_AFTERNORM_DATA_1 =>
                        rdata_data <= RESIZE(int_afterNorm(63 downto 32), 32);
                    when ADDR_NORM1_MEAN_DATA_0 =>
                        rdata_data <= RESIZE(int_norm1_mean(31 downto 0), 32);
                    when ADDR_NORM1_MEAN_DATA_1 =>
                        rdata_data <= RESIZE(int_norm1_mean(63 downto 32), 32);
                    when ADDR_NORM1_VAR_DATA_0 =>
                        rdata_data <= RESIZE(int_norm1_var(31 downto 0), 32);
                    when ADDR_NORM1_VAR_DATA_1 =>
                        rdata_data <= RESIZE(int_norm1_var(63 downto 32), 32);
                    when ADDR_NORM1_WEIGHT_DATA_0 =>
                        rdata_data <= RESIZE(int_norm1_weight(31 downto 0), 32);
                    when ADDR_NORM1_WEIGHT_DATA_1 =>
                        rdata_data <= RESIZE(int_norm1_weight(63 downto 32), 32);
                    when ADDR_NORM1_BIAS_DATA_0 =>
                        rdata_data <= RESIZE(int_norm1_bias(31 downto 0), 32);
                    when ADDR_NORM1_BIAS_DATA_1 =>
                        rdata_data <= RESIZE(int_norm1_bias(63 downto 32), 32);
                    when ADDR_AFTERPAD_DATA_0 =>
                        rdata_data <= RESIZE(int_afterPad(31 downto 0), 32);
                    when ADDR_AFTERPAD_DATA_1 =>
                        rdata_data <= RESIZE(int_afterPad(63 downto 32), 32);
                    when ADDR_AFTERREARRANGEX_DATA_0 =>
                        rdata_data <= RESIZE(int_afterRearrangeX(31 downto 0), 32);
                    when ADDR_AFTERREARRANGEX_DATA_1 =>
                        rdata_data <= RESIZE(int_afterRearrangeX(63 downto 32), 32);
                    when ADDR_AFTERPAD1_DATA_0 =>
                        rdata_data <= RESIZE(int_afterPad1(31 downto 0), 32);
                    when ADDR_AFTERPAD1_DATA_1 =>
                        rdata_data <= RESIZE(int_afterPad1(63 downto 32), 32);
                    when ADDR_AFTERCONV1_DATA_0 =>
                        rdata_data <= RESIZE(int_afterConv1(31 downto 0), 32);
                    when ADDR_AFTERCONV1_DATA_1 =>
                        rdata_data <= RESIZE(int_afterConv1(63 downto 32), 32);
                    when ADDR_KERNEL1_DATA_0 =>
                        rdata_data <= RESIZE(int_kernel1(31 downto 0), 32);
                    when ADDR_KERNEL1_DATA_1 =>
                        rdata_data <= RESIZE(int_kernel1(63 downto 32), 32);
                    when ADDR_BIAS1_DATA_0 =>
                        rdata_data <= RESIZE(int_bias1(31 downto 0), 32);
                    when ADDR_BIAS1_DATA_1 =>
                        rdata_data <= RESIZE(int_bias1(63 downto 32), 32);
                    when ADDR_IN_QK_DATA_0 =>
                        rdata_data <= RESIZE(int_in_qk(31 downto 0), 32);
                    when ADDR_IN_QK_DATA_1 =>
                        rdata_data <= RESIZE(int_in_qk(63 downto 32), 32);
                    when ADDR_IN_Q_DATA_0 =>
                        rdata_data <= RESIZE(int_in_q(31 downto 0), 32);
                    when ADDR_IN_Q_DATA_1 =>
                        rdata_data <= RESIZE(int_in_q(63 downto 32), 32);
                    when ADDR_IN_K_DATA_0 =>
                        rdata_data <= RESIZE(int_in_k(31 downto 0), 32);
                    when ADDR_IN_K_DATA_1 =>
                        rdata_data <= RESIZE(int_in_k(63 downto 32), 32);
                    when ADDR_AFTERQKMULTIPLICATION_DATA_0 =>
                        rdata_data <= RESIZE(int_afterQKMultiplication(31 downto 0), 32);
                    when ADDR_AFTERQKMULTIPLICATION_DATA_1 =>
                        rdata_data <= RESIZE(int_afterQKMultiplication(63 downto 32), 32);
                    when ADDR_AFTERSOFTMAX_DATA_0 =>
                        rdata_data <= RESIZE(int_afterSoftmax(31 downto 0), 32);
                    when ADDR_AFTERSOFTMAX_DATA_1 =>
                        rdata_data <= RESIZE(int_afterSoftmax(63 downto 32), 32);
                    when ADDR_AFTERREARRANGEX2_DATA_0 =>
                        rdata_data <= RESIZE(int_afterRearrangeX2(31 downto 0), 32);
                    when ADDR_AFTERREARRANGEX2_DATA_1 =>
                        rdata_data <= RESIZE(int_afterRearrangeX2(63 downto 32), 32);
                    when ADDR_AFTERQKXMULTIPLICATION_DATA_0 =>
                        rdata_data <= RESIZE(int_afterQKXMultiplication(31 downto 0), 32);
                    when ADDR_AFTERQKXMULTIPLICATION_DATA_1 =>
                        rdata_data <= RESIZE(int_afterQKXMultiplication(63 downto 32), 32);
                    when ADDR_AFTERREARRANGEQKX_DATA_0 =>
                        rdata_data <= RESIZE(int_afterRearrangeQKX(31 downto 0), 32);
                    when ADDR_AFTERREARRANGEQKX_DATA_1 =>
                        rdata_data <= RESIZE(int_afterRearrangeQKX(63 downto 32), 32);
                    when ADDR_AFTERPAD2_DATA_0 =>
                        rdata_data <= RESIZE(int_afterPad2(31 downto 0), 32);
                    when ADDR_AFTERPAD2_DATA_1 =>
                        rdata_data <= RESIZE(int_afterPad2(63 downto 32), 32);
                    when ADDR_AFTERCONV2_DATA_0 =>
                        rdata_data <= RESIZE(int_afterConv2(31 downto 0), 32);
                    when ADDR_AFTERCONV2_DATA_1 =>
                        rdata_data <= RESIZE(int_afterConv2(63 downto 32), 32);
                    when ADDR_KERNEL2_DATA_0 =>
                        rdata_data <= RESIZE(int_kernel2(31 downto 0), 32);
                    when ADDR_KERNEL2_DATA_1 =>
                        rdata_data <= RESIZE(int_kernel2(63 downto 32), 32);
                    when ADDR_BIAS2_DATA_0 =>
                        rdata_data <= RESIZE(int_bias2(31 downto 0), 32);
                    when ADDR_BIAS2_DATA_1 =>
                        rdata_data <= RESIZE(int_bias2(63 downto 32), 32);
                    when ADDR_AFTERACT2_DATA_0 =>
                        rdata_data <= RESIZE(int_afterAct2(31 downto 0), 32);
                    when ADDR_AFTERACT2_DATA_1 =>
                        rdata_data <= RESIZE(int_afterAct2(63 downto 32), 32);
                    when ADDR_QKV_DATA_0 =>
                        rdata_data <= RESIZE(int_QKV(31 downto 0), 32);
                    when ADDR_QKV_DATA_1 =>
                        rdata_data <= RESIZE(int_QKV(63 downto 32), 32);
                    when ADDR_BUFFER_OUT_DATA_0 =>
                        rdata_data <= RESIZE(int_buffer_out(31 downto 0), 32);
                    when ADDR_BUFFER_OUT_DATA_1 =>
                        rdata_data <= RESIZE(int_buffer_out(63 downto 32), 32);
                    when ADDR_BUFFER_RESULT_DATA_0 =>
                        rdata_data <= RESIZE(int_buffer_result(31 downto 0), 32);
                    when ADDR_BUFFER_RESULT_DATA_1 =>
                        rdata_data <= RESIZE(int_buffer_result(63 downto 32), 32);
                    when others =>
                        NULL;
                    end case;
                end if;
            end if;
        end if;
    end process;

-- ----------------------- Register logic ----------------
    buffer_DataIn_1      <= STD_LOGIC_VECTOR(int_buffer_DataIn_1);
    afterNorm            <= STD_LOGIC_VECTOR(int_afterNorm);
    norm1_mean           <= STD_LOGIC_VECTOR(int_norm1_mean);
    norm1_var            <= STD_LOGIC_VECTOR(int_norm1_var);
    norm1_weight         <= STD_LOGIC_VECTOR(int_norm1_weight);
    norm1_bias           <= STD_LOGIC_VECTOR(int_norm1_bias);
    afterPad             <= STD_LOGIC_VECTOR(int_afterPad);
    afterRearrangeX      <= STD_LOGIC_VECTOR(int_afterRearrangeX);
    afterPad1            <= STD_LOGIC_VECTOR(int_afterPad1);
    afterConv1           <= STD_LOGIC_VECTOR(int_afterConv1);
    kernel1              <= STD_LOGIC_VECTOR(int_kernel1);
    bias1                <= STD_LOGIC_VECTOR(int_bias1);
    in_qk                <= STD_LOGIC_VECTOR(int_in_qk);
    in_q                 <= STD_LOGIC_VECTOR(int_in_q);
    in_k                 <= STD_LOGIC_VECTOR(int_in_k);
    afterQKMultiplication <= STD_LOGIC_VECTOR(int_afterQKMultiplication);
    afterSoftmax         <= STD_LOGIC_VECTOR(int_afterSoftmax);
    afterRearrangeX2     <= STD_LOGIC_VECTOR(int_afterRearrangeX2);
    afterQKXMultiplication <= STD_LOGIC_VECTOR(int_afterQKXMultiplication);
    afterRearrangeQKX    <= STD_LOGIC_VECTOR(int_afterRearrangeQKX);
    afterPad2            <= STD_LOGIC_VECTOR(int_afterPad2);
    afterConv2           <= STD_LOGIC_VECTOR(int_afterConv2);
    kernel2              <= STD_LOGIC_VECTOR(int_kernel2);
    bias2                <= STD_LOGIC_VECTOR(int_bias2);
    afterAct2            <= STD_LOGIC_VECTOR(int_afterAct2);
    QKV                  <= STD_LOGIC_VECTOR(int_QKV);
    buffer_out           <= STD_LOGIC_VECTOR(int_buffer_out);
    buffer_result        <= STD_LOGIC_VECTOR(int_buffer_result);

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_BUFFER_DATAIN_1_DATA_0) then
                    int_buffer_DataIn_1(31 downto 0) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_buffer_DataIn_1(31 downto 0));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_BUFFER_DATAIN_1_DATA_1) then
                    int_buffer_DataIn_1(63 downto 32) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_buffer_DataIn_1(63 downto 32));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_AFTERNORM_DATA_0) then
                    int_afterNorm(31 downto 0) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_afterNorm(31 downto 0));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_AFTERNORM_DATA_1) then
                    int_afterNorm(63 downto 32) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_afterNorm(63 downto 32));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_NORM1_MEAN_DATA_0) then
                    int_norm1_mean(31 downto 0) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_norm1_mean(31 downto 0));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_NORM1_MEAN_DATA_1) then
                    int_norm1_mean(63 downto 32) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_norm1_mean(63 downto 32));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_NORM1_VAR_DATA_0) then
                    int_norm1_var(31 downto 0) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_norm1_var(31 downto 0));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_NORM1_VAR_DATA_1) then
                    int_norm1_var(63 downto 32) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_norm1_var(63 downto 32));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_NORM1_WEIGHT_DATA_0) then
                    int_norm1_weight(31 downto 0) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_norm1_weight(31 downto 0));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_NORM1_WEIGHT_DATA_1) then
                    int_norm1_weight(63 downto 32) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_norm1_weight(63 downto 32));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_NORM1_BIAS_DATA_0) then
                    int_norm1_bias(31 downto 0) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_norm1_bias(31 downto 0));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_NORM1_BIAS_DATA_1) then
                    int_norm1_bias(63 downto 32) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_norm1_bias(63 downto 32));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_AFTERPAD_DATA_0) then
                    int_afterPad(31 downto 0) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_afterPad(31 downto 0));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_AFTERPAD_DATA_1) then
                    int_afterPad(63 downto 32) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_afterPad(63 downto 32));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_AFTERREARRANGEX_DATA_0) then
                    int_afterRearrangeX(31 downto 0) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_afterRearrangeX(31 downto 0));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_AFTERREARRANGEX_DATA_1) then
                    int_afterRearrangeX(63 downto 32) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_afterRearrangeX(63 downto 32));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_AFTERPAD1_DATA_0) then
                    int_afterPad1(31 downto 0) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_afterPad1(31 downto 0));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_AFTERPAD1_DATA_1) then
                    int_afterPad1(63 downto 32) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_afterPad1(63 downto 32));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_AFTERCONV1_DATA_0) then
                    int_afterConv1(31 downto 0) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_afterConv1(31 downto 0));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_AFTERCONV1_DATA_1) then
                    int_afterConv1(63 downto 32) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_afterConv1(63 downto 32));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_KERNEL1_DATA_0) then
                    int_kernel1(31 downto 0) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_kernel1(31 downto 0));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_KERNEL1_DATA_1) then
                    int_kernel1(63 downto 32) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_kernel1(63 downto 32));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_BIAS1_DATA_0) then
                    int_bias1(31 downto 0) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_bias1(31 downto 0));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_BIAS1_DATA_1) then
                    int_bias1(63 downto 32) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_bias1(63 downto 32));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_IN_QK_DATA_0) then
                    int_in_qk(31 downto 0) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_in_qk(31 downto 0));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_IN_QK_DATA_1) then
                    int_in_qk(63 downto 32) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_in_qk(63 downto 32));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_IN_Q_DATA_0) then
                    int_in_q(31 downto 0) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_in_q(31 downto 0));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_IN_Q_DATA_1) then
                    int_in_q(63 downto 32) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_in_q(63 downto 32));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_IN_K_DATA_0) then
                    int_in_k(31 downto 0) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_in_k(31 downto 0));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_IN_K_DATA_1) then
                    int_in_k(63 downto 32) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_in_k(63 downto 32));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_AFTERQKMULTIPLICATION_DATA_0) then
                    int_afterQKMultiplication(31 downto 0) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_afterQKMultiplication(31 downto 0));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_AFTERQKMULTIPLICATION_DATA_1) then
                    int_afterQKMultiplication(63 downto 32) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_afterQKMultiplication(63 downto 32));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_AFTERSOFTMAX_DATA_0) then
                    int_afterSoftmax(31 downto 0) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_afterSoftmax(31 downto 0));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_AFTERSOFTMAX_DATA_1) then
                    int_afterSoftmax(63 downto 32) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_afterSoftmax(63 downto 32));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_AFTERREARRANGEX2_DATA_0) then
                    int_afterRearrangeX2(31 downto 0) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_afterRearrangeX2(31 downto 0));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_AFTERREARRANGEX2_DATA_1) then
                    int_afterRearrangeX2(63 downto 32) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_afterRearrangeX2(63 downto 32));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_AFTERQKXMULTIPLICATION_DATA_0) then
                    int_afterQKXMultiplication(31 downto 0) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_afterQKXMultiplication(31 downto 0));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_AFTERQKXMULTIPLICATION_DATA_1) then
                    int_afterQKXMultiplication(63 downto 32) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_afterQKXMultiplication(63 downto 32));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_AFTERREARRANGEQKX_DATA_0) then
                    int_afterRearrangeQKX(31 downto 0) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_afterRearrangeQKX(31 downto 0));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_AFTERREARRANGEQKX_DATA_1) then
                    int_afterRearrangeQKX(63 downto 32) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_afterRearrangeQKX(63 downto 32));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_AFTERPAD2_DATA_0) then
                    int_afterPad2(31 downto 0) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_afterPad2(31 downto 0));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_AFTERPAD2_DATA_1) then
                    int_afterPad2(63 downto 32) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_afterPad2(63 downto 32));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_AFTERCONV2_DATA_0) then
                    int_afterConv2(31 downto 0) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_afterConv2(31 downto 0));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_AFTERCONV2_DATA_1) then
                    int_afterConv2(63 downto 32) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_afterConv2(63 downto 32));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_KERNEL2_DATA_0) then
                    int_kernel2(31 downto 0) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_kernel2(31 downto 0));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_KERNEL2_DATA_1) then
                    int_kernel2(63 downto 32) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_kernel2(63 downto 32));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_BIAS2_DATA_0) then
                    int_bias2(31 downto 0) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_bias2(31 downto 0));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_BIAS2_DATA_1) then
                    int_bias2(63 downto 32) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_bias2(63 downto 32));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_AFTERACT2_DATA_0) then
                    int_afterAct2(31 downto 0) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_afterAct2(31 downto 0));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_AFTERACT2_DATA_1) then
                    int_afterAct2(63 downto 32) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_afterAct2(63 downto 32));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_QKV_DATA_0) then
                    int_QKV(31 downto 0) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_QKV(31 downto 0));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_QKV_DATA_1) then
                    int_QKV(63 downto 32) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_QKV(63 downto 32));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_BUFFER_OUT_DATA_0) then
                    int_buffer_out(31 downto 0) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_buffer_out(31 downto 0));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_BUFFER_OUT_DATA_1) then
                    int_buffer_out(63 downto 32) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_buffer_out(63 downto 32));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_BUFFER_RESULT_DATA_0) then
                    int_buffer_result(31 downto 0) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_buffer_result(31 downto 0));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_BUFFER_RESULT_DATA_1) then
                    int_buffer_result(63 downto 32) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_buffer_result(63 downto 32));
                end if;
            end if;
        end if;
    end process;


-- ----------------------- Memory logic ------------------

end architecture behave;
