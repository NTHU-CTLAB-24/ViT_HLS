set moduleName DW_conv_1_2_3_12_1_Pipeline_In_Channel
set isTopModule 0
set isCombinational 0
set isDatapathOnly 0
set isPipelined 0
set pipeline_type none
set FunctionProtocol ap_ctrl_hs
set isOneStateSeq 0
set ProfileFlag 0
set StallSigGenFlag 0
set isEnableWaveformDebug 1
set hasInterrupt 0
set C_modelName {DW_conv.1.2.3.12.1_Pipeline_In_Channel}
set C_modelType { int 1 }
set C_modelArgList {
	{ sext_ln60 int 32 regular  }
	{ bitcast_ln64 float 32 regular  }
	{ sext_ln62 int 17 regular  }
	{ in_r int 64 regular  }
	{ gmem0 int 32 regular {axi_master 0}  }
	{ sext_ln63 int 11 regular  }
	{ kernel int 64 regular  }
	{ gmem int 32 regular {axi_master 0}  }
	{ add8122_out float 32 regular {pointer 1}  }
	{ add_out float 32 regular {pointer 1}  }
}
set C_modelArgMapList {[ 
	{ "Name" : "sext_ln60", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "bitcast_ln64", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "sext_ln62", "interface" : "wire", "bitwidth" : 17, "direction" : "READONLY"} , 
 	{ "Name" : "in_r", "interface" : "wire", "bitwidth" : 64, "direction" : "READONLY"} , 
 	{ "Name" : "gmem0", "interface" : "axi_master", "bitwidth" : 32, "direction" : "READONLY", "bitSlice":[ {"cElement": [{"cName": "X_data","offset": { "type": "dynamic","port_name": "X_data","bundle": "control"},"direction": "READONLY"},{"cName": "Y_dw_norm","offset": { "type": "dynamic","port_name": "Y_dw_norm","bundle": "control"},"direction": "READWRITE"},{"cName": "Y_relu","offset": { "type": "dynamic","port_name": "Y_relu","bundle": "control"},"direction": "READWRITE"},{"cName": "Y_proj","offset": { "type": "dynamic","port_name": "Y_proj","bundle": "control"},"direction": "READWRITE"}]}]} , 
 	{ "Name" : "sext_ln63", "interface" : "wire", "bitwidth" : 11, "direction" : "READONLY"} , 
 	{ "Name" : "kernel", "interface" : "wire", "bitwidth" : 64, "direction" : "READONLY"} , 
 	{ "Name" : "gmem", "interface" : "axi_master", "bitwidth" : 32, "direction" : "READONLY", "bitSlice":[ {"cElement": [{"cName": "msp_conv_weight","offset": { "type": "dynamic","port_name": "msp_conv_weight","bundle": "control"},"direction": "READONLY"},{"cName": "msp_conv_bias","offset": { "type": "dynamic","port_name": "msp_conv_bias","bundle": "control"},"direction": "READONLY"},{"cName": "msp_norm_weight","offset": { "type": "dynamic","port_name": "msp_norm_weight","bundle": "control"},"direction": "READONLY"},{"cName": "msp_norm_bias","offset": { "type": "dynamic","port_name": "msp_norm_bias","bundle": "control"},"direction": "READONLY"},{"cName": "msp_norm_running_mean","offset": { "type": "dynamic","port_name": "msp_norm_running_mean","bundle": "control"},"direction": "READONLY"},{"cName": "msp_norm_running_var","offset": { "type": "dynamic","port_name": "msp_norm_running_var","bundle": "control"},"direction": "READONLY"},{"cName": "dw_conv_weight","offset": { "type": "dynamic","port_name": "dw_conv_weight","bundle": "control"},"direction": "READONLY"},{"cName": "norm_1_weight","offset": { "type": "dynamic","port_name": "norm_1_weight","bundle": "control"},"direction": "READONLY"},{"cName": "norm_1_bias","offset": { "type": "dynamic","port_name": "norm_1_bias","bundle": "control"},"direction": "READONLY"},{"cName": "norm_1_running_mean","offset": { "type": "dynamic","port_name": "norm_1_running_mean","bundle": "control"},"direction": "READONLY"},{"cName": "norm_1_running_var","offset": { "type": "dynamic","port_name": "norm_1_running_var","bundle": "control"},"direction": "READONLY"},{"cName": "se_conv_reduce_weight","offset": { "type": "dynamic","port_name": "se_conv_reduce_weight","bundle": "control"},"direction": "READONLY"},{"cName": "se_conv_reduce_bias","offset": { "type": "dynamic","port_name": "se_conv_reduce_bias","bundle": "control"},"direction": "READONLY"},{"cName": "se_conv_expand_weight","offset": { "type": "dynamic","port_name": "se_conv_expand_weight","bundle": "control"},"direction": "READONLY"},{"cName": "se_conv_expand_bias","offset": { "type": "dynamic","port_name": "se_conv_expand_bias","bundle": "control"},"direction": "READONLY"},{"cName": "proj_conv_weight","offset": { "type": "dynamic","port_name": "proj_conv_weight","bundle": "control"},"direction": "READONLY"}]}]} , 
 	{ "Name" : "add8122_out", "interface" : "wire", "bitwidth" : 32, "direction" : "WRITEONLY"} , 
 	{ "Name" : "add_out", "interface" : "wire", "bitwidth" : 32, "direction" : "WRITEONLY"} , 
 	{ "Name" : "ap_return", "interface" : "wire", "bitwidth" : 1} ]}
# RTL Port declarations: 
set portNum 118
set portList { 
	{ ap_clk sc_in sc_logic 1 clock -1 } 
	{ ap_rst sc_in sc_logic 1 reset -1 active_high_sync } 
	{ ap_start sc_in sc_logic 1 start -1 } 
	{ ap_done sc_out sc_logic 1 predone -1 } 
	{ ap_idle sc_out sc_logic 1 done -1 } 
	{ ap_ready sc_out sc_logic 1 ready -1 } 
	{ sext_ln60 sc_in sc_lv 32 signal 0 } 
	{ bitcast_ln64 sc_in sc_lv 32 signal 1 } 
	{ sext_ln62 sc_in sc_lv 17 signal 2 } 
	{ in_r sc_in sc_lv 64 signal 3 } 
	{ m_axi_gmem0_AWVALID sc_out sc_logic 1 signal 4 } 
	{ m_axi_gmem0_AWREADY sc_in sc_logic 1 signal 4 } 
	{ m_axi_gmem0_AWADDR sc_out sc_lv 64 signal 4 } 
	{ m_axi_gmem0_AWID sc_out sc_lv 1 signal 4 } 
	{ m_axi_gmem0_AWLEN sc_out sc_lv 32 signal 4 } 
	{ m_axi_gmem0_AWSIZE sc_out sc_lv 3 signal 4 } 
	{ m_axi_gmem0_AWBURST sc_out sc_lv 2 signal 4 } 
	{ m_axi_gmem0_AWLOCK sc_out sc_lv 2 signal 4 } 
	{ m_axi_gmem0_AWCACHE sc_out sc_lv 4 signal 4 } 
	{ m_axi_gmem0_AWPROT sc_out sc_lv 3 signal 4 } 
	{ m_axi_gmem0_AWQOS sc_out sc_lv 4 signal 4 } 
	{ m_axi_gmem0_AWREGION sc_out sc_lv 4 signal 4 } 
	{ m_axi_gmem0_AWUSER sc_out sc_lv 1 signal 4 } 
	{ m_axi_gmem0_WVALID sc_out sc_logic 1 signal 4 } 
	{ m_axi_gmem0_WREADY sc_in sc_logic 1 signal 4 } 
	{ m_axi_gmem0_WDATA sc_out sc_lv 32 signal 4 } 
	{ m_axi_gmem0_WSTRB sc_out sc_lv 4 signal 4 } 
	{ m_axi_gmem0_WLAST sc_out sc_logic 1 signal 4 } 
	{ m_axi_gmem0_WID sc_out sc_lv 1 signal 4 } 
	{ m_axi_gmem0_WUSER sc_out sc_lv 1 signal 4 } 
	{ m_axi_gmem0_ARVALID sc_out sc_logic 1 signal 4 } 
	{ m_axi_gmem0_ARREADY sc_in sc_logic 1 signal 4 } 
	{ m_axi_gmem0_ARADDR sc_out sc_lv 64 signal 4 } 
	{ m_axi_gmem0_ARID sc_out sc_lv 1 signal 4 } 
	{ m_axi_gmem0_ARLEN sc_out sc_lv 32 signal 4 } 
	{ m_axi_gmem0_ARSIZE sc_out sc_lv 3 signal 4 } 
	{ m_axi_gmem0_ARBURST sc_out sc_lv 2 signal 4 } 
	{ m_axi_gmem0_ARLOCK sc_out sc_lv 2 signal 4 } 
	{ m_axi_gmem0_ARCACHE sc_out sc_lv 4 signal 4 } 
	{ m_axi_gmem0_ARPROT sc_out sc_lv 3 signal 4 } 
	{ m_axi_gmem0_ARQOS sc_out sc_lv 4 signal 4 } 
	{ m_axi_gmem0_ARREGION sc_out sc_lv 4 signal 4 } 
	{ m_axi_gmem0_ARUSER sc_out sc_lv 1 signal 4 } 
	{ m_axi_gmem0_RVALID sc_in sc_logic 1 signal 4 } 
	{ m_axi_gmem0_RREADY sc_out sc_logic 1 signal 4 } 
	{ m_axi_gmem0_RDATA sc_in sc_lv 32 signal 4 } 
	{ m_axi_gmem0_RLAST sc_in sc_logic 1 signal 4 } 
	{ m_axi_gmem0_RID sc_in sc_lv 1 signal 4 } 
	{ m_axi_gmem0_RFIFONUM sc_in sc_lv 9 signal 4 } 
	{ m_axi_gmem0_RUSER sc_in sc_lv 1 signal 4 } 
	{ m_axi_gmem0_RRESP sc_in sc_lv 2 signal 4 } 
	{ m_axi_gmem0_BVALID sc_in sc_logic 1 signal 4 } 
	{ m_axi_gmem0_BREADY sc_out sc_logic 1 signal 4 } 
	{ m_axi_gmem0_BRESP sc_in sc_lv 2 signal 4 } 
	{ m_axi_gmem0_BID sc_in sc_lv 1 signal 4 } 
	{ m_axi_gmem0_BUSER sc_in sc_lv 1 signal 4 } 
	{ sext_ln63 sc_in sc_lv 11 signal 5 } 
	{ kernel sc_in sc_lv 64 signal 6 } 
	{ m_axi_gmem_AWVALID sc_out sc_logic 1 signal 7 } 
	{ m_axi_gmem_AWREADY sc_in sc_logic 1 signal 7 } 
	{ m_axi_gmem_AWADDR sc_out sc_lv 64 signal 7 } 
	{ m_axi_gmem_AWID sc_out sc_lv 1 signal 7 } 
	{ m_axi_gmem_AWLEN sc_out sc_lv 32 signal 7 } 
	{ m_axi_gmem_AWSIZE sc_out sc_lv 3 signal 7 } 
	{ m_axi_gmem_AWBURST sc_out sc_lv 2 signal 7 } 
	{ m_axi_gmem_AWLOCK sc_out sc_lv 2 signal 7 } 
	{ m_axi_gmem_AWCACHE sc_out sc_lv 4 signal 7 } 
	{ m_axi_gmem_AWPROT sc_out sc_lv 3 signal 7 } 
	{ m_axi_gmem_AWQOS sc_out sc_lv 4 signal 7 } 
	{ m_axi_gmem_AWREGION sc_out sc_lv 4 signal 7 } 
	{ m_axi_gmem_AWUSER sc_out sc_lv 1 signal 7 } 
	{ m_axi_gmem_WVALID sc_out sc_logic 1 signal 7 } 
	{ m_axi_gmem_WREADY sc_in sc_logic 1 signal 7 } 
	{ m_axi_gmem_WDATA sc_out sc_lv 32 signal 7 } 
	{ m_axi_gmem_WSTRB sc_out sc_lv 4 signal 7 } 
	{ m_axi_gmem_WLAST sc_out sc_logic 1 signal 7 } 
	{ m_axi_gmem_WID sc_out sc_lv 1 signal 7 } 
	{ m_axi_gmem_WUSER sc_out sc_lv 1 signal 7 } 
	{ m_axi_gmem_ARVALID sc_out sc_logic 1 signal 7 } 
	{ m_axi_gmem_ARREADY sc_in sc_logic 1 signal 7 } 
	{ m_axi_gmem_ARADDR sc_out sc_lv 64 signal 7 } 
	{ m_axi_gmem_ARID sc_out sc_lv 1 signal 7 } 
	{ m_axi_gmem_ARLEN sc_out sc_lv 32 signal 7 } 
	{ m_axi_gmem_ARSIZE sc_out sc_lv 3 signal 7 } 
	{ m_axi_gmem_ARBURST sc_out sc_lv 2 signal 7 } 
	{ m_axi_gmem_ARLOCK sc_out sc_lv 2 signal 7 } 
	{ m_axi_gmem_ARCACHE sc_out sc_lv 4 signal 7 } 
	{ m_axi_gmem_ARPROT sc_out sc_lv 3 signal 7 } 
	{ m_axi_gmem_ARQOS sc_out sc_lv 4 signal 7 } 
	{ m_axi_gmem_ARREGION sc_out sc_lv 4 signal 7 } 
	{ m_axi_gmem_ARUSER sc_out sc_lv 1 signal 7 } 
	{ m_axi_gmem_RVALID sc_in sc_logic 1 signal 7 } 
	{ m_axi_gmem_RREADY sc_out sc_logic 1 signal 7 } 
	{ m_axi_gmem_RDATA sc_in sc_lv 32 signal 7 } 
	{ m_axi_gmem_RLAST sc_in sc_logic 1 signal 7 } 
	{ m_axi_gmem_RID sc_in sc_lv 1 signal 7 } 
	{ m_axi_gmem_RFIFONUM sc_in sc_lv 9 signal 7 } 
	{ m_axi_gmem_RUSER sc_in sc_lv 1 signal 7 } 
	{ m_axi_gmem_RRESP sc_in sc_lv 2 signal 7 } 
	{ m_axi_gmem_BVALID sc_in sc_logic 1 signal 7 } 
	{ m_axi_gmem_BREADY sc_out sc_logic 1 signal 7 } 
	{ m_axi_gmem_BRESP sc_in sc_lv 2 signal 7 } 
	{ m_axi_gmem_BID sc_in sc_lv 1 signal 7 } 
	{ m_axi_gmem_BUSER sc_in sc_lv 1 signal 7 } 
	{ add8122_out sc_out sc_lv 32 signal 8 } 
	{ add8122_out_ap_vld sc_out sc_logic 1 outvld 8 } 
	{ add_out sc_out sc_lv 32 signal 9 } 
	{ add_out_ap_vld sc_out sc_logic 1 outvld 9 } 
	{ ap_return sc_out sc_lv 1 signal -1 } 
	{ grp_fu_348_p_din0 sc_out sc_lv 32 signal -1 } 
	{ grp_fu_348_p_din1 sc_out sc_lv 32 signal -1 } 
	{ grp_fu_348_p_opcode sc_out sc_lv 2 signal -1 } 
	{ grp_fu_348_p_dout0 sc_in sc_lv 32 signal -1 } 
	{ grp_fu_348_p_ce sc_out sc_logic 1 signal -1 } 
	{ grp_fu_1590_p_din0 sc_out sc_lv 32 signal -1 } 
	{ grp_fu_1590_p_din1 sc_out sc_lv 32 signal -1 } 
	{ grp_fu_1590_p_dout0 sc_in sc_lv 32 signal -1 } 
	{ grp_fu_1590_p_ce sc_out sc_logic 1 signal -1 } 
}
set NewPortList {[ 
	{ "name": "ap_clk", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "clock", "bundle":{"name": "ap_clk", "role": "default" }} , 
 	{ "name": "ap_rst", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "reset", "bundle":{"name": "ap_rst", "role": "default" }} , 
 	{ "name": "ap_start", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "start", "bundle":{"name": "ap_start", "role": "default" }} , 
 	{ "name": "ap_done", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "predone", "bundle":{"name": "ap_done", "role": "default" }} , 
 	{ "name": "ap_idle", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "done", "bundle":{"name": "ap_idle", "role": "default" }} , 
 	{ "name": "ap_ready", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "ready", "bundle":{"name": "ap_ready", "role": "default" }} , 
 	{ "name": "sext_ln60", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "sext_ln60", "role": "default" }} , 
 	{ "name": "bitcast_ln64", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "bitcast_ln64", "role": "default" }} , 
 	{ "name": "sext_ln62", "direction": "in", "datatype": "sc_lv", "bitwidth":17, "type": "signal", "bundle":{"name": "sext_ln62", "role": "default" }} , 
 	{ "name": "in_r", "direction": "in", "datatype": "sc_lv", "bitwidth":64, "type": "signal", "bundle":{"name": "in_r", "role": "default" }} , 
 	{ "name": "m_axi_gmem0_AWVALID", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem0", "role": "AWVALID" }} , 
 	{ "name": "m_axi_gmem0_AWREADY", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem0", "role": "AWREADY" }} , 
 	{ "name": "m_axi_gmem0_AWADDR", "direction": "out", "datatype": "sc_lv", "bitwidth":64, "type": "signal", "bundle":{"name": "gmem0", "role": "AWADDR" }} , 
 	{ "name": "m_axi_gmem0_AWID", "direction": "out", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem0", "role": "AWID" }} , 
 	{ "name": "m_axi_gmem0_AWLEN", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "gmem0", "role": "AWLEN" }} , 
 	{ "name": "m_axi_gmem0_AWSIZE", "direction": "out", "datatype": "sc_lv", "bitwidth":3, "type": "signal", "bundle":{"name": "gmem0", "role": "AWSIZE" }} , 
 	{ "name": "m_axi_gmem0_AWBURST", "direction": "out", "datatype": "sc_lv", "bitwidth":2, "type": "signal", "bundle":{"name": "gmem0", "role": "AWBURST" }} , 
 	{ "name": "m_axi_gmem0_AWLOCK", "direction": "out", "datatype": "sc_lv", "bitwidth":2, "type": "signal", "bundle":{"name": "gmem0", "role": "AWLOCK" }} , 
 	{ "name": "m_axi_gmem0_AWCACHE", "direction": "out", "datatype": "sc_lv", "bitwidth":4, "type": "signal", "bundle":{"name": "gmem0", "role": "AWCACHE" }} , 
 	{ "name": "m_axi_gmem0_AWPROT", "direction": "out", "datatype": "sc_lv", "bitwidth":3, "type": "signal", "bundle":{"name": "gmem0", "role": "AWPROT" }} , 
 	{ "name": "m_axi_gmem0_AWQOS", "direction": "out", "datatype": "sc_lv", "bitwidth":4, "type": "signal", "bundle":{"name": "gmem0", "role": "AWQOS" }} , 
 	{ "name": "m_axi_gmem0_AWREGION", "direction": "out", "datatype": "sc_lv", "bitwidth":4, "type": "signal", "bundle":{"name": "gmem0", "role": "AWREGION" }} , 
 	{ "name": "m_axi_gmem0_AWUSER", "direction": "out", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem0", "role": "AWUSER" }} , 
 	{ "name": "m_axi_gmem0_WVALID", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem0", "role": "WVALID" }} , 
 	{ "name": "m_axi_gmem0_WREADY", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem0", "role": "WREADY" }} , 
 	{ "name": "m_axi_gmem0_WDATA", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "gmem0", "role": "WDATA" }} , 
 	{ "name": "m_axi_gmem0_WSTRB", "direction": "out", "datatype": "sc_lv", "bitwidth":4, "type": "signal", "bundle":{"name": "gmem0", "role": "WSTRB" }} , 
 	{ "name": "m_axi_gmem0_WLAST", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem0", "role": "WLAST" }} , 
 	{ "name": "m_axi_gmem0_WID", "direction": "out", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem0", "role": "WID" }} , 
 	{ "name": "m_axi_gmem0_WUSER", "direction": "out", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem0", "role": "WUSER" }} , 
 	{ "name": "m_axi_gmem0_ARVALID", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem0", "role": "ARVALID" }} , 
 	{ "name": "m_axi_gmem0_ARREADY", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem0", "role": "ARREADY" }} , 
 	{ "name": "m_axi_gmem0_ARADDR", "direction": "out", "datatype": "sc_lv", "bitwidth":64, "type": "signal", "bundle":{"name": "gmem0", "role": "ARADDR" }} , 
 	{ "name": "m_axi_gmem0_ARID", "direction": "out", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem0", "role": "ARID" }} , 
 	{ "name": "m_axi_gmem0_ARLEN", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "gmem0", "role": "ARLEN" }} , 
 	{ "name": "m_axi_gmem0_ARSIZE", "direction": "out", "datatype": "sc_lv", "bitwidth":3, "type": "signal", "bundle":{"name": "gmem0", "role": "ARSIZE" }} , 
 	{ "name": "m_axi_gmem0_ARBURST", "direction": "out", "datatype": "sc_lv", "bitwidth":2, "type": "signal", "bundle":{"name": "gmem0", "role": "ARBURST" }} , 
 	{ "name": "m_axi_gmem0_ARLOCK", "direction": "out", "datatype": "sc_lv", "bitwidth":2, "type": "signal", "bundle":{"name": "gmem0", "role": "ARLOCK" }} , 
 	{ "name": "m_axi_gmem0_ARCACHE", "direction": "out", "datatype": "sc_lv", "bitwidth":4, "type": "signal", "bundle":{"name": "gmem0", "role": "ARCACHE" }} , 
 	{ "name": "m_axi_gmem0_ARPROT", "direction": "out", "datatype": "sc_lv", "bitwidth":3, "type": "signal", "bundle":{"name": "gmem0", "role": "ARPROT" }} , 
 	{ "name": "m_axi_gmem0_ARQOS", "direction": "out", "datatype": "sc_lv", "bitwidth":4, "type": "signal", "bundle":{"name": "gmem0", "role": "ARQOS" }} , 
 	{ "name": "m_axi_gmem0_ARREGION", "direction": "out", "datatype": "sc_lv", "bitwidth":4, "type": "signal", "bundle":{"name": "gmem0", "role": "ARREGION" }} , 
 	{ "name": "m_axi_gmem0_ARUSER", "direction": "out", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem0", "role": "ARUSER" }} , 
 	{ "name": "m_axi_gmem0_RVALID", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem0", "role": "RVALID" }} , 
 	{ "name": "m_axi_gmem0_RREADY", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem0", "role": "RREADY" }} , 
 	{ "name": "m_axi_gmem0_RDATA", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "gmem0", "role": "RDATA" }} , 
 	{ "name": "m_axi_gmem0_RLAST", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem0", "role": "RLAST" }} , 
 	{ "name": "m_axi_gmem0_RID", "direction": "in", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem0", "role": "RID" }} , 
 	{ "name": "m_axi_gmem0_RFIFONUM", "direction": "in", "datatype": "sc_lv", "bitwidth":9, "type": "signal", "bundle":{"name": "gmem0", "role": "RFIFONUM" }} , 
 	{ "name": "m_axi_gmem0_RUSER", "direction": "in", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem0", "role": "RUSER" }} , 
 	{ "name": "m_axi_gmem0_RRESP", "direction": "in", "datatype": "sc_lv", "bitwidth":2, "type": "signal", "bundle":{"name": "gmem0", "role": "RRESP" }} , 
 	{ "name": "m_axi_gmem0_BVALID", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem0", "role": "BVALID" }} , 
 	{ "name": "m_axi_gmem0_BREADY", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem0", "role": "BREADY" }} , 
 	{ "name": "m_axi_gmem0_BRESP", "direction": "in", "datatype": "sc_lv", "bitwidth":2, "type": "signal", "bundle":{"name": "gmem0", "role": "BRESP" }} , 
 	{ "name": "m_axi_gmem0_BID", "direction": "in", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem0", "role": "BID" }} , 
 	{ "name": "m_axi_gmem0_BUSER", "direction": "in", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem0", "role": "BUSER" }} , 
 	{ "name": "sext_ln63", "direction": "in", "datatype": "sc_lv", "bitwidth":11, "type": "signal", "bundle":{"name": "sext_ln63", "role": "default" }} , 
 	{ "name": "kernel", "direction": "in", "datatype": "sc_lv", "bitwidth":64, "type": "signal", "bundle":{"name": "kernel", "role": "default" }} , 
 	{ "name": "m_axi_gmem_AWVALID", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem", "role": "AWVALID" }} , 
 	{ "name": "m_axi_gmem_AWREADY", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem", "role": "AWREADY" }} , 
 	{ "name": "m_axi_gmem_AWADDR", "direction": "out", "datatype": "sc_lv", "bitwidth":64, "type": "signal", "bundle":{"name": "gmem", "role": "AWADDR" }} , 
 	{ "name": "m_axi_gmem_AWID", "direction": "out", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem", "role": "AWID" }} , 
 	{ "name": "m_axi_gmem_AWLEN", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "gmem", "role": "AWLEN" }} , 
 	{ "name": "m_axi_gmem_AWSIZE", "direction": "out", "datatype": "sc_lv", "bitwidth":3, "type": "signal", "bundle":{"name": "gmem", "role": "AWSIZE" }} , 
 	{ "name": "m_axi_gmem_AWBURST", "direction": "out", "datatype": "sc_lv", "bitwidth":2, "type": "signal", "bundle":{"name": "gmem", "role": "AWBURST" }} , 
 	{ "name": "m_axi_gmem_AWLOCK", "direction": "out", "datatype": "sc_lv", "bitwidth":2, "type": "signal", "bundle":{"name": "gmem", "role": "AWLOCK" }} , 
 	{ "name": "m_axi_gmem_AWCACHE", "direction": "out", "datatype": "sc_lv", "bitwidth":4, "type": "signal", "bundle":{"name": "gmem", "role": "AWCACHE" }} , 
 	{ "name": "m_axi_gmem_AWPROT", "direction": "out", "datatype": "sc_lv", "bitwidth":3, "type": "signal", "bundle":{"name": "gmem", "role": "AWPROT" }} , 
 	{ "name": "m_axi_gmem_AWQOS", "direction": "out", "datatype": "sc_lv", "bitwidth":4, "type": "signal", "bundle":{"name": "gmem", "role": "AWQOS" }} , 
 	{ "name": "m_axi_gmem_AWREGION", "direction": "out", "datatype": "sc_lv", "bitwidth":4, "type": "signal", "bundle":{"name": "gmem", "role": "AWREGION" }} , 
 	{ "name": "m_axi_gmem_AWUSER", "direction": "out", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem", "role": "AWUSER" }} , 
 	{ "name": "m_axi_gmem_WVALID", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem", "role": "WVALID" }} , 
 	{ "name": "m_axi_gmem_WREADY", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem", "role": "WREADY" }} , 
 	{ "name": "m_axi_gmem_WDATA", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "gmem", "role": "WDATA" }} , 
 	{ "name": "m_axi_gmem_WSTRB", "direction": "out", "datatype": "sc_lv", "bitwidth":4, "type": "signal", "bundle":{"name": "gmem", "role": "WSTRB" }} , 
 	{ "name": "m_axi_gmem_WLAST", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem", "role": "WLAST" }} , 
 	{ "name": "m_axi_gmem_WID", "direction": "out", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem", "role": "WID" }} , 
 	{ "name": "m_axi_gmem_WUSER", "direction": "out", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem", "role": "WUSER" }} , 
 	{ "name": "m_axi_gmem_ARVALID", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem", "role": "ARVALID" }} , 
 	{ "name": "m_axi_gmem_ARREADY", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem", "role": "ARREADY" }} , 
 	{ "name": "m_axi_gmem_ARADDR", "direction": "out", "datatype": "sc_lv", "bitwidth":64, "type": "signal", "bundle":{"name": "gmem", "role": "ARADDR" }} , 
 	{ "name": "m_axi_gmem_ARID", "direction": "out", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem", "role": "ARID" }} , 
 	{ "name": "m_axi_gmem_ARLEN", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "gmem", "role": "ARLEN" }} , 
 	{ "name": "m_axi_gmem_ARSIZE", "direction": "out", "datatype": "sc_lv", "bitwidth":3, "type": "signal", "bundle":{"name": "gmem", "role": "ARSIZE" }} , 
 	{ "name": "m_axi_gmem_ARBURST", "direction": "out", "datatype": "sc_lv", "bitwidth":2, "type": "signal", "bundle":{"name": "gmem", "role": "ARBURST" }} , 
 	{ "name": "m_axi_gmem_ARLOCK", "direction": "out", "datatype": "sc_lv", "bitwidth":2, "type": "signal", "bundle":{"name": "gmem", "role": "ARLOCK" }} , 
 	{ "name": "m_axi_gmem_ARCACHE", "direction": "out", "datatype": "sc_lv", "bitwidth":4, "type": "signal", "bundle":{"name": "gmem", "role": "ARCACHE" }} , 
 	{ "name": "m_axi_gmem_ARPROT", "direction": "out", "datatype": "sc_lv", "bitwidth":3, "type": "signal", "bundle":{"name": "gmem", "role": "ARPROT" }} , 
 	{ "name": "m_axi_gmem_ARQOS", "direction": "out", "datatype": "sc_lv", "bitwidth":4, "type": "signal", "bundle":{"name": "gmem", "role": "ARQOS" }} , 
 	{ "name": "m_axi_gmem_ARREGION", "direction": "out", "datatype": "sc_lv", "bitwidth":4, "type": "signal", "bundle":{"name": "gmem", "role": "ARREGION" }} , 
 	{ "name": "m_axi_gmem_ARUSER", "direction": "out", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem", "role": "ARUSER" }} , 
 	{ "name": "m_axi_gmem_RVALID", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem", "role": "RVALID" }} , 
 	{ "name": "m_axi_gmem_RREADY", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem", "role": "RREADY" }} , 
 	{ "name": "m_axi_gmem_RDATA", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "gmem", "role": "RDATA" }} , 
 	{ "name": "m_axi_gmem_RLAST", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem", "role": "RLAST" }} , 
 	{ "name": "m_axi_gmem_RID", "direction": "in", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem", "role": "RID" }} , 
 	{ "name": "m_axi_gmem_RFIFONUM", "direction": "in", "datatype": "sc_lv", "bitwidth":9, "type": "signal", "bundle":{"name": "gmem", "role": "RFIFONUM" }} , 
 	{ "name": "m_axi_gmem_RUSER", "direction": "in", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem", "role": "RUSER" }} , 
 	{ "name": "m_axi_gmem_RRESP", "direction": "in", "datatype": "sc_lv", "bitwidth":2, "type": "signal", "bundle":{"name": "gmem", "role": "RRESP" }} , 
 	{ "name": "m_axi_gmem_BVALID", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem", "role": "BVALID" }} , 
 	{ "name": "m_axi_gmem_BREADY", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem", "role": "BREADY" }} , 
 	{ "name": "m_axi_gmem_BRESP", "direction": "in", "datatype": "sc_lv", "bitwidth":2, "type": "signal", "bundle":{"name": "gmem", "role": "BRESP" }} , 
 	{ "name": "m_axi_gmem_BID", "direction": "in", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem", "role": "BID" }} , 
 	{ "name": "m_axi_gmem_BUSER", "direction": "in", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem", "role": "BUSER" }} , 
 	{ "name": "add8122_out", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "add8122_out", "role": "default" }} , 
 	{ "name": "add8122_out_ap_vld", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "outvld", "bundle":{"name": "add8122_out", "role": "ap_vld" }} , 
 	{ "name": "add_out", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "add_out", "role": "default" }} , 
 	{ "name": "add_out_ap_vld", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "outvld", "bundle":{"name": "add_out", "role": "ap_vld" }} , 
 	{ "name": "ap_return", "direction": "out", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "ap_return", "role": "default" }} , 
 	{ "name": "grp_fu_348_p_din0", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "grp_fu_348_p_din0", "role": "default" }} , 
 	{ "name": "grp_fu_348_p_din1", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "grp_fu_348_p_din1", "role": "default" }} , 
 	{ "name": "grp_fu_348_p_opcode", "direction": "out", "datatype": "sc_lv", "bitwidth":2, "type": "signal", "bundle":{"name": "grp_fu_348_p_opcode", "role": "default" }} , 
 	{ "name": "grp_fu_348_p_dout0", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "grp_fu_348_p_dout0", "role": "default" }} , 
 	{ "name": "grp_fu_348_p_ce", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "grp_fu_348_p_ce", "role": "default" }} , 
 	{ "name": "grp_fu_1590_p_din0", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "grp_fu_1590_p_din0", "role": "default" }} , 
 	{ "name": "grp_fu_1590_p_din1", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "grp_fu_1590_p_din1", "role": "default" }} , 
 	{ "name": "grp_fu_1590_p_dout0", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "grp_fu_1590_p_dout0", "role": "default" }} , 
 	{ "name": "grp_fu_1590_p_ce", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "grp_fu_1590_p_ce", "role": "default" }}  ]}

set RtlHierarchyInfo {[
	{"ID" : "0", "Level" : "0", "Path" : "`AUTOTB_DUT_INST", "Parent" : "", "Child" : ["1", "2"],
		"CDFG" : "DW_conv_1_2_3_12_1_Pipeline_In_Channel",
		"Protocol" : "ap_ctrl_hs",
		"ControlExist" : "1", "ap_start" : "1", "ap_ready" : "1", "ap_done" : "1", "ap_continue" : "0", "ap_idle" : "1", "real_start" : "0",
		"Pipeline" : "None", "UnalignedPipeline" : "0", "RewindPipeline" : "0", "ProcessNetwork" : "0",
		"II" : "0",
		"VariableLatency" : "1", "ExactLatency" : "-1", "EstimateLatencyMin" : "-1", "EstimateLatencyMax" : "-1",
		"Combinational" : "0",
		"Datapath" : "0",
		"ClockEnable" : "0",
		"HasSubDataflow" : "0",
		"InDataflowNetwork" : "0",
		"HasNonBlockingOperation" : "0",
		"IsBlackBox" : "0",
		"Port" : [
			{"Name" : "sext_ln60", "Type" : "None", "Direction" : "I"},
			{"Name" : "bitcast_ln64", "Type" : "None", "Direction" : "I"},
			{"Name" : "sext_ln62", "Type" : "None", "Direction" : "I"},
			{"Name" : "in_r", "Type" : "None", "Direction" : "I"},
			{"Name" : "gmem0", "Type" : "MAXI", "Direction" : "I",
				"BlockSignal" : [
					{"Name" : "gmem0_blk_n_AR", "Type" : "RtlSignal"},
					{"Name" : "gmem0_blk_n_R", "Type" : "RtlSignal"}]},
			{"Name" : "sext_ln63", "Type" : "None", "Direction" : "I"},
			{"Name" : "kernel", "Type" : "None", "Direction" : "I"},
			{"Name" : "gmem", "Type" : "MAXI", "Direction" : "I",
				"BlockSignal" : [
					{"Name" : "gmem_blk_n_AR", "Type" : "RtlSignal"},
					{"Name" : "gmem_blk_n_R", "Type" : "RtlSignal"}]},
			{"Name" : "add8122_out", "Type" : "Vld", "Direction" : "O"},
			{"Name" : "add_out", "Type" : "Vld", "Direction" : "O"}],
		"Loop" : [
			{"Name" : "In_Channel", "PipelineType" : "no",
				"LoopDec" : {"FSMBitwidth" : "39", "FirstState" : "ap_ST_fsm_state2", "LastState" : ["ap_ST_fsm_state37"], "QuitState" : ["ap_ST_fsm_state37"], "PreState" : ["ap_ST_fsm_state1"], "PostState" : ["ap_ST_fsm_state38", "ap_ST_fsm_state39"], "OneDepthLoop" : "0", "OneStateBlock": ""}}]},
	{"ID" : "1", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.mul_62s_17ns_62_1_1_U3", "Parent" : "0"},
	{"ID" : "2", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.srem_32ns_3ns_3_36_1_U4", "Parent" : "0"}]}


set ArgLastReadFirstWriteLatency {
	DW_conv_1_2_3_12_1_Pipeline_In_Channel {
		sext_ln60 {Type I LastRead 0 FirstWrite -1}
		bitcast_ln64 {Type I LastRead 0 FirstWrite -1}
		sext_ln62 {Type I LastRead 0 FirstWrite -1}
		in_r {Type I LastRead 0 FirstWrite -1}
		gmem0 {Type I LastRead 9 FirstWrite -1}
		sext_ln63 {Type I LastRead 0 FirstWrite -1}
		kernel {Type I LastRead 0 FirstWrite -1}
		gmem {Type I LastRead 9 FirstWrite -1}
		add8122_out {Type O LastRead -1 FirstWrite 2}
		add_out {Type O LastRead -1 FirstWrite 37}}}

set hasDtUnsupportedChannel 0

set PerformanceInfo {[
	{"Name" : "Latency", "Min" : "-1", "Max" : "-1"}
	, {"Name" : "Interval", "Min" : "-1", "Max" : "-1"}
]}

set PipelineEnableSignalInfo {[
]}

set Spec2ImplPortList { 
	sext_ln60 { ap_none {  { sext_ln60 in_data 0 32 } } }
	bitcast_ln64 { ap_none {  { bitcast_ln64 in_data 0 32 } } }
	sext_ln62 { ap_none {  { sext_ln62 in_data 0 17 } } }
	in_r { ap_none {  { in_r in_data 0 64 } } }
	 { m_axi {  { m_axi_gmem0_AWVALID VALID 1 1 }  { m_axi_gmem0_AWREADY READY 0 1 }  { m_axi_gmem0_AWADDR ADDR 1 64 }  { m_axi_gmem0_AWID ID 1 1 }  { m_axi_gmem0_AWLEN SIZE 1 32 }  { m_axi_gmem0_AWSIZE BURST 1 3 }  { m_axi_gmem0_AWBURST LOCK 1 2 }  { m_axi_gmem0_AWLOCK CACHE 1 2 }  { m_axi_gmem0_AWCACHE PROT 1 4 }  { m_axi_gmem0_AWPROT QOS 1 3 }  { m_axi_gmem0_AWQOS REGION 1 4 }  { m_axi_gmem0_AWREGION USER 1 4 }  { m_axi_gmem0_AWUSER DATA 1 1 }  { m_axi_gmem0_WVALID VALID 1 1 }  { m_axi_gmem0_WREADY READY 0 1 }  { m_axi_gmem0_WDATA FIFONUM 1 32 }  { m_axi_gmem0_WSTRB STRB 1 4 }  { m_axi_gmem0_WLAST LAST 1 1 }  { m_axi_gmem0_WID ID 1 1 }  { m_axi_gmem0_WUSER DATA 1 1 }  { m_axi_gmem0_ARVALID VALID 1 1 }  { m_axi_gmem0_ARREADY READY 0 1 }  { m_axi_gmem0_ARADDR ADDR 1 64 }  { m_axi_gmem0_ARID ID 1 1 }  { m_axi_gmem0_ARLEN SIZE 1 32 }  { m_axi_gmem0_ARSIZE BURST 1 3 }  { m_axi_gmem0_ARBURST LOCK 1 2 }  { m_axi_gmem0_ARLOCK CACHE 1 2 }  { m_axi_gmem0_ARCACHE PROT 1 4 }  { m_axi_gmem0_ARPROT QOS 1 3 }  { m_axi_gmem0_ARQOS REGION 1 4 }  { m_axi_gmem0_ARREGION USER 1 4 }  { m_axi_gmem0_ARUSER DATA 1 1 }  { m_axi_gmem0_RVALID VALID 0 1 }  { m_axi_gmem0_RREADY READY 1 1 }  { m_axi_gmem0_RDATA FIFONUM 0 32 }  { m_axi_gmem0_RLAST LAST 0 1 }  { m_axi_gmem0_RID ID 0 1 }  { m_axi_gmem0_RFIFONUM LEN 0 9 }  { m_axi_gmem0_RUSER DATA 0 1 }  { m_axi_gmem0_RRESP RESP 0 2 }  { m_axi_gmem0_BVALID VALID 0 1 }  { m_axi_gmem0_BREADY READY 1 1 }  { m_axi_gmem0_BRESP RESP 0 2 }  { m_axi_gmem0_BID ID 0 1 }  { m_axi_gmem0_BUSER DATA 0 1 } } }
	sext_ln63 { ap_none {  { sext_ln63 in_data 0 11 } } }
	kernel { ap_none {  { kernel in_data 0 64 } } }
	 { m_axi {  { m_axi_gmem_AWVALID VALID 1 1 }  { m_axi_gmem_AWREADY READY 0 1 }  { m_axi_gmem_AWADDR ADDR 1 64 }  { m_axi_gmem_AWID ID 1 1 }  { m_axi_gmem_AWLEN SIZE 1 32 }  { m_axi_gmem_AWSIZE BURST 1 3 }  { m_axi_gmem_AWBURST LOCK 1 2 }  { m_axi_gmem_AWLOCK CACHE 1 2 }  { m_axi_gmem_AWCACHE PROT 1 4 }  { m_axi_gmem_AWPROT QOS 1 3 }  { m_axi_gmem_AWQOS REGION 1 4 }  { m_axi_gmem_AWREGION USER 1 4 }  { m_axi_gmem_AWUSER DATA 1 1 }  { m_axi_gmem_WVALID VALID 1 1 }  { m_axi_gmem_WREADY READY 0 1 }  { m_axi_gmem_WDATA FIFONUM 1 32 }  { m_axi_gmem_WSTRB STRB 1 4 }  { m_axi_gmem_WLAST LAST 1 1 }  { m_axi_gmem_WID ID 1 1 }  { m_axi_gmem_WUSER DATA 1 1 }  { m_axi_gmem_ARVALID VALID 1 1 }  { m_axi_gmem_ARREADY READY 0 1 }  { m_axi_gmem_ARADDR ADDR 1 64 }  { m_axi_gmem_ARID ID 1 1 }  { m_axi_gmem_ARLEN SIZE 1 32 }  { m_axi_gmem_ARSIZE BURST 1 3 }  { m_axi_gmem_ARBURST LOCK 1 2 }  { m_axi_gmem_ARLOCK CACHE 1 2 }  { m_axi_gmem_ARCACHE PROT 1 4 }  { m_axi_gmem_ARPROT QOS 1 3 }  { m_axi_gmem_ARQOS REGION 1 4 }  { m_axi_gmem_ARREGION USER 1 4 }  { m_axi_gmem_ARUSER DATA 1 1 }  { m_axi_gmem_RVALID VALID 0 1 }  { m_axi_gmem_RREADY READY 1 1 }  { m_axi_gmem_RDATA FIFONUM 0 32 }  { m_axi_gmem_RLAST LAST 0 1 }  { m_axi_gmem_RID ID 0 1 }  { m_axi_gmem_RFIFONUM LEN 0 9 }  { m_axi_gmem_RUSER DATA 0 1 }  { m_axi_gmem_RRESP RESP 0 2 }  { m_axi_gmem_BVALID VALID 0 1 }  { m_axi_gmem_BREADY READY 1 1 }  { m_axi_gmem_BRESP RESP 0 2 }  { m_axi_gmem_BID ID 0 1 }  { m_axi_gmem_BUSER DATA 0 1 } } }
	add8122_out { ap_vld {  { add8122_out out_data 1 32 }  { add8122_out_ap_vld out_vld 1 1 } } }
	add_out { ap_vld {  { add_out out_data 1 32 }  { add_out_ap_vld out_vld 1 1 } } }
}
