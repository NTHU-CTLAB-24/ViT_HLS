set moduleName DW_conv_Pipeline_In_Channel
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
set C_modelName {DW_conv_Pipeline_In_Channel}
set C_modelType { int 1 }
set C_modelArgList {
	{ sext_ln335 int 32 regular  }
	{ bitcast_ln339 float 32 regular  }
	{ select_ln317 int 7 regular  }
	{ p_mid2156 int 14 regular  }
	{ select_ln317_7 int 3 regular  }
	{ in_r int 64 regular  }
	{ gmem int 32 regular {axi_master 0}  }
	{ select_ln317_8 int 1 regular  }
	{ zext_ln339_2 int 15 regular  }
	{ kernel int 64 regular  }
	{ add8122_out float 32 regular {pointer 1}  }
	{ add_out float 32 regular {pointer 1}  }
}
set C_modelArgMapList {[ 
	{ "Name" : "sext_ln335", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "bitcast_ln339", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "select_ln317", "interface" : "wire", "bitwidth" : 7, "direction" : "READONLY"} , 
 	{ "Name" : "p_mid2156", "interface" : "wire", "bitwidth" : 14, "direction" : "READONLY"} , 
 	{ "Name" : "select_ln317_7", "interface" : "wire", "bitwidth" : 3, "direction" : "READONLY"} , 
 	{ "Name" : "in_r", "interface" : "wire", "bitwidth" : 64, "direction" : "READONLY"} , 
 	{ "Name" : "gmem", "interface" : "axi_master", "bitwidth" : 32, "direction" : "READONLY", "bitSlice":[ {"cElement": [{"cName": "norm1_mean","offset": { "type": "dynamic","port_name": "norm1_mean","bundle": "control"},"direction": "READONLY"},{"cName": "norm1_var","offset": { "type": "dynamic","port_name": "norm1_var","bundle": "control"},"direction": "READONLY"},{"cName": "norm1_weight","offset": { "type": "dynamic","port_name": "norm1_weight","bundle": "control"},"direction": "READONLY"},{"cName": "norm1_bias","offset": { "type": "dynamic","port_name": "norm1_bias","bundle": "control"},"direction": "READONLY"},{"cName": "afterPad","offset": { "type": "dynamic","port_name": "afterPad","bundle": "control"},"direction": "READWRITE"},{"cName": "afterRearrangeX","offset": { "type": "dynamic","port_name": "afterRearrangeX","bundle": "control"},"direction": "READWRITE"},{"cName": "afterPad1","offset": { "type": "dynamic","port_name": "afterPad1","bundle": "control"},},{"cName": "afterConv1","offset": { "type": "dynamic","port_name": "afterConv1","bundle": "control"},"direction": "READWRITE"},{"cName": "kernel1","offset": { "type": "dynamic","port_name": "kernel1","bundle": "control"},"direction": "READONLY"},{"cName": "bias1","offset": { "type": "dynamic","port_name": "bias1","bundle": "control"},"direction": "READONLY"},{"cName": "in_qk","offset": { "type": "dynamic","port_name": "in_qk","bundle": "control"},"direction": "READWRITE"},{"cName": "in_q","offset": { "type": "dynamic","port_name": "in_q","bundle": "control"},"direction": "READWRITE"},{"cName": "in_k","offset": { "type": "dynamic","port_name": "in_k","bundle": "control"},"direction": "READWRITE"},{"cName": "afterQKMultiplication","offset": { "type": "dynamic","port_name": "afterQKMultiplication","bundle": "control"},"direction": "READWRITE"},{"cName": "afterSoftmax","offset": { "type": "dynamic","port_name": "afterSoftmax","bundle": "control"},"direction": "READWRITE"},{"cName": "afterRearrangeX2","offset": { "type": "dynamic","port_name": "afterRearrangeX2","bundle": "control"},"direction": "READWRITE"},{"cName": "afterQKXMultiplication","offset": { "type": "dynamic","port_name": "afterQKXMultiplication","bundle": "control"},"direction": "READWRITE"},{"cName": "afterRearrangeQKX","offset": { "type": "dynamic","port_name": "afterRearrangeQKX","bundle": "control"},"direction": "READWRITE"},{"cName": "afterPad2","offset": { "type": "dynamic","port_name": "afterPad2","bundle": "control"},},{"cName": "afterConv2","offset": { "type": "dynamic","port_name": "afterConv2","bundle": "control"},"direction": "READWRITE"},{"cName": "kernel2","offset": { "type": "dynamic","port_name": "kernel2","bundle": "control"},"direction": "READONLY"},{"cName": "bias2","offset": { "type": "dynamic","port_name": "bias2","bundle": "control"},"direction": "READONLY"},{"cName": "afterAct2","offset": { "type": "dynamic","port_name": "afterAct2","bundle": "control"},"direction": "READWRITE"},{"cName": "QKV","offset": { "type": "dynamic","port_name": "QKV","bundle": "control"},"direction": "READWRITE"},{"cName": "buffer_out","offset": { "type": "dynamic","port_name": "buffer_out","bundle": "control"},"direction": "READWRITE"}]}]} , 
 	{ "Name" : "select_ln317_8", "interface" : "wire", "bitwidth" : 1, "direction" : "READONLY"} , 
 	{ "Name" : "zext_ln339_2", "interface" : "wire", "bitwidth" : 15, "direction" : "READONLY"} , 
 	{ "Name" : "kernel", "interface" : "wire", "bitwidth" : 64, "direction" : "READONLY"} , 
 	{ "Name" : "add8122_out", "interface" : "wire", "bitwidth" : 32, "direction" : "WRITEONLY"} , 
 	{ "Name" : "add_out", "interface" : "wire", "bitwidth" : 32, "direction" : "WRITEONLY"} , 
 	{ "Name" : "ap_return", "interface" : "wire", "bitwidth" : 1} ]}
# RTL Port declarations: 
set portNum 66
set portList { 
	{ ap_clk sc_in sc_logic 1 clock -1 } 
	{ ap_rst sc_in sc_logic 1 reset -1 active_high_sync } 
	{ ap_start sc_in sc_logic 1 start -1 } 
	{ ap_done sc_out sc_logic 1 predone -1 } 
	{ ap_idle sc_out sc_logic 1 done -1 } 
	{ ap_ready sc_out sc_logic 1 ready -1 } 
	{ sext_ln335 sc_in sc_lv 32 signal 0 } 
	{ bitcast_ln339 sc_in sc_lv 32 signal 1 } 
	{ select_ln317 sc_in sc_lv 7 signal 2 } 
	{ p_mid2156 sc_in sc_lv 14 signal 3 } 
	{ select_ln317_7 sc_in sc_lv 3 signal 4 } 
	{ in_r sc_in sc_lv 64 signal 5 } 
	{ m_axi_gmem_AWVALID sc_out sc_logic 1 signal 6 } 
	{ m_axi_gmem_AWREADY sc_in sc_logic 1 signal 6 } 
	{ m_axi_gmem_AWADDR sc_out sc_lv 64 signal 6 } 
	{ m_axi_gmem_AWID sc_out sc_lv 1 signal 6 } 
	{ m_axi_gmem_AWLEN sc_out sc_lv 32 signal 6 } 
	{ m_axi_gmem_AWSIZE sc_out sc_lv 3 signal 6 } 
	{ m_axi_gmem_AWBURST sc_out sc_lv 2 signal 6 } 
	{ m_axi_gmem_AWLOCK sc_out sc_lv 2 signal 6 } 
	{ m_axi_gmem_AWCACHE sc_out sc_lv 4 signal 6 } 
	{ m_axi_gmem_AWPROT sc_out sc_lv 3 signal 6 } 
	{ m_axi_gmem_AWQOS sc_out sc_lv 4 signal 6 } 
	{ m_axi_gmem_AWREGION sc_out sc_lv 4 signal 6 } 
	{ m_axi_gmem_AWUSER sc_out sc_lv 1 signal 6 } 
	{ m_axi_gmem_WVALID sc_out sc_logic 1 signal 6 } 
	{ m_axi_gmem_WREADY sc_in sc_logic 1 signal 6 } 
	{ m_axi_gmem_WDATA sc_out sc_lv 32 signal 6 } 
	{ m_axi_gmem_WSTRB sc_out sc_lv 4 signal 6 } 
	{ m_axi_gmem_WLAST sc_out sc_logic 1 signal 6 } 
	{ m_axi_gmem_WID sc_out sc_lv 1 signal 6 } 
	{ m_axi_gmem_WUSER sc_out sc_lv 1 signal 6 } 
	{ m_axi_gmem_ARVALID sc_out sc_logic 1 signal 6 } 
	{ m_axi_gmem_ARREADY sc_in sc_logic 1 signal 6 } 
	{ m_axi_gmem_ARADDR sc_out sc_lv 64 signal 6 } 
	{ m_axi_gmem_ARID sc_out sc_lv 1 signal 6 } 
	{ m_axi_gmem_ARLEN sc_out sc_lv 32 signal 6 } 
	{ m_axi_gmem_ARSIZE sc_out sc_lv 3 signal 6 } 
	{ m_axi_gmem_ARBURST sc_out sc_lv 2 signal 6 } 
	{ m_axi_gmem_ARLOCK sc_out sc_lv 2 signal 6 } 
	{ m_axi_gmem_ARCACHE sc_out sc_lv 4 signal 6 } 
	{ m_axi_gmem_ARPROT sc_out sc_lv 3 signal 6 } 
	{ m_axi_gmem_ARQOS sc_out sc_lv 4 signal 6 } 
	{ m_axi_gmem_ARREGION sc_out sc_lv 4 signal 6 } 
	{ m_axi_gmem_ARUSER sc_out sc_lv 1 signal 6 } 
	{ m_axi_gmem_RVALID sc_in sc_logic 1 signal 6 } 
	{ m_axi_gmem_RREADY sc_out sc_logic 1 signal 6 } 
	{ m_axi_gmem_RDATA sc_in sc_lv 32 signal 6 } 
	{ m_axi_gmem_RLAST sc_in sc_logic 1 signal 6 } 
	{ m_axi_gmem_RID sc_in sc_lv 1 signal 6 } 
	{ m_axi_gmem_RFIFONUM sc_in sc_lv 9 signal 6 } 
	{ m_axi_gmem_RUSER sc_in sc_lv 1 signal 6 } 
	{ m_axi_gmem_RRESP sc_in sc_lv 2 signal 6 } 
	{ m_axi_gmem_BVALID sc_in sc_logic 1 signal 6 } 
	{ m_axi_gmem_BREADY sc_out sc_logic 1 signal 6 } 
	{ m_axi_gmem_BRESP sc_in sc_lv 2 signal 6 } 
	{ m_axi_gmem_BID sc_in sc_lv 1 signal 6 } 
	{ m_axi_gmem_BUSER sc_in sc_lv 1 signal 6 } 
	{ select_ln317_8 sc_in sc_lv 1 signal 7 } 
	{ zext_ln339_2 sc_in sc_lv 15 signal 8 } 
	{ kernel sc_in sc_lv 64 signal 9 } 
	{ add8122_out sc_out sc_lv 32 signal 10 } 
	{ add8122_out_ap_vld sc_out sc_logic 1 outvld 10 } 
	{ add_out sc_out sc_lv 32 signal 11 } 
	{ add_out_ap_vld sc_out sc_logic 1 outvld 11 } 
	{ ap_return sc_out sc_lv 1 signal -1 } 
}
set NewPortList {[ 
	{ "name": "ap_clk", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "clock", "bundle":{"name": "ap_clk", "role": "default" }} , 
 	{ "name": "ap_rst", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "reset", "bundle":{"name": "ap_rst", "role": "default" }} , 
 	{ "name": "ap_start", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "start", "bundle":{"name": "ap_start", "role": "default" }} , 
 	{ "name": "ap_done", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "predone", "bundle":{"name": "ap_done", "role": "default" }} , 
 	{ "name": "ap_idle", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "done", "bundle":{"name": "ap_idle", "role": "default" }} , 
 	{ "name": "ap_ready", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "ready", "bundle":{"name": "ap_ready", "role": "default" }} , 
 	{ "name": "sext_ln335", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "sext_ln335", "role": "default" }} , 
 	{ "name": "bitcast_ln339", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "bitcast_ln339", "role": "default" }} , 
 	{ "name": "select_ln317", "direction": "in", "datatype": "sc_lv", "bitwidth":7, "type": "signal", "bundle":{"name": "select_ln317", "role": "default" }} , 
 	{ "name": "p_mid2156", "direction": "in", "datatype": "sc_lv", "bitwidth":14, "type": "signal", "bundle":{"name": "p_mid2156", "role": "default" }} , 
 	{ "name": "select_ln317_7", "direction": "in", "datatype": "sc_lv", "bitwidth":3, "type": "signal", "bundle":{"name": "select_ln317_7", "role": "default" }} , 
 	{ "name": "in_r", "direction": "in", "datatype": "sc_lv", "bitwidth":64, "type": "signal", "bundle":{"name": "in_r", "role": "default" }} , 
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
 	{ "name": "select_ln317_8", "direction": "in", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "select_ln317_8", "role": "default" }} , 
 	{ "name": "zext_ln339_2", "direction": "in", "datatype": "sc_lv", "bitwidth":15, "type": "signal", "bundle":{"name": "zext_ln339_2", "role": "default" }} , 
 	{ "name": "kernel", "direction": "in", "datatype": "sc_lv", "bitwidth":64, "type": "signal", "bundle":{"name": "kernel", "role": "default" }} , 
 	{ "name": "add8122_out", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "add8122_out", "role": "default" }} , 
 	{ "name": "add8122_out_ap_vld", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "outvld", "bundle":{"name": "add8122_out", "role": "ap_vld" }} , 
 	{ "name": "add_out", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "add_out", "role": "default" }} , 
 	{ "name": "add_out_ap_vld", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "outvld", "bundle":{"name": "add_out", "role": "ap_vld" }} , 
 	{ "name": "ap_return", "direction": "out", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "ap_return", "role": "default" }}  ]}

set RtlHierarchyInfo {[
	{"ID" : "0", "Level" : "0", "Path" : "`AUTOTB_DUT_INST", "Parent" : "", "Child" : ["1", "2", "3", "4"],
		"CDFG" : "DW_conv_Pipeline_In_Channel",
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
			{"Name" : "sext_ln335", "Type" : "None", "Direction" : "I"},
			{"Name" : "bitcast_ln339", "Type" : "None", "Direction" : "I"},
			{"Name" : "select_ln317", "Type" : "None", "Direction" : "I"},
			{"Name" : "p_mid2156", "Type" : "None", "Direction" : "I"},
			{"Name" : "select_ln317_7", "Type" : "None", "Direction" : "I"},
			{"Name" : "in_r", "Type" : "None", "Direction" : "I"},
			{"Name" : "gmem", "Type" : "MAXI", "Direction" : "I",
				"BlockSignal" : [
					{"Name" : "gmem_blk_n_AR", "Type" : "RtlSignal"},
					{"Name" : "gmem_blk_n_R", "Type" : "RtlSignal"}]},
			{"Name" : "select_ln317_8", "Type" : "None", "Direction" : "I"},
			{"Name" : "zext_ln339_2", "Type" : "None", "Direction" : "I"},
			{"Name" : "kernel", "Type" : "None", "Direction" : "I"},
			{"Name" : "add8122_out", "Type" : "Vld", "Direction" : "O"},
			{"Name" : "add_out", "Type" : "Vld", "Direction" : "O"}],
		"Loop" : [
			{"Name" : "In_Channel", "PipelineType" : "no",
				"LoopDec" : {"FSMBitwidth" : "39", "FirstState" : "ap_ST_fsm_state2", "LastState" : ["ap_ST_fsm_state37"], "QuitState" : ["ap_ST_fsm_state37"], "PreState" : ["ap_ST_fsm_state1"], "PostState" : ["ap_ST_fsm_state38", "ap_ST_fsm_state39"], "OneDepthLoop" : "0", "OneStateBlock": ""}}]},
	{"ID" : "1", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.fadd_32ns_32ns_32_1_full_dsp_1_U32", "Parent" : "0"},
	{"ID" : "2", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.fmul_32ns_32ns_32_1_max_dsp_1_U33", "Parent" : "0"},
	{"ID" : "3", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.mul_62s_7ns_62_1_1_U34", "Parent" : "0"},
	{"ID" : "4", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.srem_32ns_8ns_8_36_1_U35", "Parent" : "0"}]}


set ArgLastReadFirstWriteLatency {
	DW_conv_Pipeline_In_Channel {
		sext_ln335 {Type I LastRead 0 FirstWrite -1}
		bitcast_ln339 {Type I LastRead 0 FirstWrite -1}
		select_ln317 {Type I LastRead 0 FirstWrite -1}
		p_mid2156 {Type I LastRead 0 FirstWrite -1}
		select_ln317_7 {Type I LastRead 0 FirstWrite -1}
		in_r {Type I LastRead 0 FirstWrite -1}
		gmem {Type I LastRead 10 FirstWrite -1}
		select_ln317_8 {Type I LastRead 0 FirstWrite -1}
		zext_ln339_2 {Type I LastRead 0 FirstWrite -1}
		kernel {Type I LastRead 0 FirstWrite -1}
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
	sext_ln335 { ap_none {  { sext_ln335 in_data 0 32 } } }
	bitcast_ln339 { ap_none {  { bitcast_ln339 in_data 0 32 } } }
	select_ln317 { ap_none {  { select_ln317 in_data 0 7 } } }
	p_mid2156 { ap_none {  { p_mid2156 in_data 0 14 } } }
	select_ln317_7 { ap_none {  { select_ln317_7 in_data 0 3 } } }
	in_r { ap_none {  { in_r in_data 0 64 } } }
	 { m_axi {  { m_axi_gmem_AWVALID VALID 1 1 }  { m_axi_gmem_AWREADY READY 0 1 }  { m_axi_gmem_AWADDR ADDR 1 64 }  { m_axi_gmem_AWID ID 1 1 }  { m_axi_gmem_AWLEN SIZE 1 32 }  { m_axi_gmem_AWSIZE BURST 1 3 }  { m_axi_gmem_AWBURST LOCK 1 2 }  { m_axi_gmem_AWLOCK CACHE 1 2 }  { m_axi_gmem_AWCACHE PROT 1 4 }  { m_axi_gmem_AWPROT QOS 1 3 }  { m_axi_gmem_AWQOS REGION 1 4 }  { m_axi_gmem_AWREGION USER 1 4 }  { m_axi_gmem_AWUSER DATA 1 1 }  { m_axi_gmem_WVALID VALID 1 1 }  { m_axi_gmem_WREADY READY 0 1 }  { m_axi_gmem_WDATA FIFONUM 1 32 }  { m_axi_gmem_WSTRB STRB 1 4 }  { m_axi_gmem_WLAST LAST 1 1 }  { m_axi_gmem_WID ID 1 1 }  { m_axi_gmem_WUSER DATA 1 1 }  { m_axi_gmem_ARVALID VALID 1 1 }  { m_axi_gmem_ARREADY READY 0 1 }  { m_axi_gmem_ARADDR ADDR 1 64 }  { m_axi_gmem_ARID ID 1 1 }  { m_axi_gmem_ARLEN SIZE 1 32 }  { m_axi_gmem_ARSIZE BURST 1 3 }  { m_axi_gmem_ARBURST LOCK 1 2 }  { m_axi_gmem_ARLOCK CACHE 1 2 }  { m_axi_gmem_ARCACHE PROT 1 4 }  { m_axi_gmem_ARPROT QOS 1 3 }  { m_axi_gmem_ARQOS REGION 1 4 }  { m_axi_gmem_ARREGION USER 1 4 }  { m_axi_gmem_ARUSER DATA 1 1 }  { m_axi_gmem_RVALID VALID 0 1 }  { m_axi_gmem_RREADY READY 1 1 }  { m_axi_gmem_RDATA FIFONUM 0 32 }  { m_axi_gmem_RLAST LAST 0 1 }  { m_axi_gmem_RID ID 0 1 }  { m_axi_gmem_RFIFONUM LEN 0 9 }  { m_axi_gmem_RUSER DATA 0 1 }  { m_axi_gmem_RRESP RESP 0 2 }  { m_axi_gmem_BVALID VALID 0 1 }  { m_axi_gmem_BREADY READY 1 1 }  { m_axi_gmem_BRESP RESP 0 2 }  { m_axi_gmem_BID ID 0 1 }  { m_axi_gmem_BUSER DATA 0 1 } } }
	select_ln317_8 { ap_none {  { select_ln317_8 in_data 0 1 } } }
	zext_ln339_2 { ap_none {  { zext_ln339_2 in_data 0 15 } } }
	kernel { ap_none {  { kernel in_data 0 64 } } }
	add8122_out { ap_vld {  { add8122_out out_data 1 32 }  { add8122_out_ap_vld out_vld 1 1 } } }
	add_out { ap_vld {  { add_out out_data 1 32 }  { add_out_ap_vld out_vld 1 1 } } }
}
