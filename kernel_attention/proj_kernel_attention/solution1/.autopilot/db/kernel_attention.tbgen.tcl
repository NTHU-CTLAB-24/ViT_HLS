set moduleName kernel_attention
set isTopModule 1
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
set C_modelName {kernel_attention}
set C_modelType { void 0 }
set C_modelArgList {
	{ gmem0 int 32 regular {axi_master 2}  }
	{ gmem1 int 32 regular {axi_master 2}  }
	{ gmem int 32 regular {axi_master 2}  }
	{ buffer_DataIn_1 int 64 regular {axi_slave 0}  }
	{ afterNorm int 64 regular {axi_slave 0}  }
	{ norm1_mean int 64 regular {axi_slave 0}  }
	{ norm1_var int 64 regular {axi_slave 0}  }
	{ norm1_weight int 64 regular {axi_slave 0}  }
	{ norm1_bias int 64 regular {axi_slave 0}  }
	{ afterPad int 64 regular {axi_slave 0}  }
	{ afterRearrangeX int 64 regular {axi_slave 0}  }
	{ afterPad1 int 64 unused {axi_slave 0}  }
	{ afterConv1 int 64 regular {axi_slave 0}  }
	{ kernel1 int 64 regular {axi_slave 0}  }
	{ bias1 int 64 regular {axi_slave 0}  }
	{ in_qk int 64 regular {axi_slave 0}  }
	{ in_q int 64 regular {axi_slave 0}  }
	{ in_k int 64 regular {axi_slave 0}  }
	{ afterQKMultiplication int 64 regular {axi_slave 0}  }
	{ afterSoftmax int 64 regular {axi_slave 0}  }
	{ afterRearrangeX2 int 64 regular {axi_slave 0}  }
	{ afterQKXMultiplication int 64 regular {axi_slave 0}  }
	{ afterRearrangeQKX int 64 regular {axi_slave 0}  }
	{ afterPad2 int 64 unused {axi_slave 0}  }
	{ afterConv2 int 64 regular {axi_slave 0}  }
	{ kernel2 int 64 regular {axi_slave 0}  }
	{ bias2 int 64 regular {axi_slave 0}  }
	{ afterAct2 int 64 regular {axi_slave 0}  }
	{ QKV int 64 regular {axi_slave 0}  }
	{ buffer_out int 64 regular {axi_slave 0}  }
	{ buffer_result int 64 regular {axi_slave 0}  }
}
set C_modelArgMapList {[ 
	{ "Name" : "gmem0", "interface" : "axi_master", "bitwidth" : 32, "direction" : "READWRITE", "bitSlice":[ {"cElement": [{"cName": "buffer_DataIn_1","offset": { "type": "dynamic","port_name": "buffer_DataIn_1","bundle": "control"},"direction": "READONLY"},{"cName": "buffer_result","offset": { "type": "dynamic","port_name": "buffer_result","bundle": "control"},"direction": "WRITEONLY"}]}]} , 
 	{ "Name" : "gmem1", "interface" : "axi_master", "bitwidth" : 32, "direction" : "READWRITE", "bitSlice":[ {"cElement": [{"cName": "afterNorm","offset": { "type": "dynamic","port_name": "afterNorm","bundle": "control"},"direction": "READWRITE"}]}]} , 
 	{ "Name" : "gmem", "interface" : "axi_master", "bitwidth" : 32, "direction" : "READWRITE", "bitSlice":[ {"cElement": [{"cName": "norm1_mean","offset": { "type": "dynamic","port_name": "norm1_mean","bundle": "control"},"direction": "READONLY"},{"cName": "norm1_var","offset": { "type": "dynamic","port_name": "norm1_var","bundle": "control"},"direction": "READONLY"},{"cName": "norm1_weight","offset": { "type": "dynamic","port_name": "norm1_weight","bundle": "control"},"direction": "READONLY"},{"cName": "norm1_bias","offset": { "type": "dynamic","port_name": "norm1_bias","bundle": "control"},"direction": "READONLY"},{"cName": "afterPad","offset": { "type": "dynamic","port_name": "afterPad","bundle": "control"},"direction": "READWRITE"},{"cName": "afterRearrangeX","offset": { "type": "dynamic","port_name": "afterRearrangeX","bundle": "control"},"direction": "READWRITE"},{"cName": "afterPad1","offset": { "type": "dynamic","port_name": "afterPad1","bundle": "control"},},{"cName": "afterConv1","offset": { "type": "dynamic","port_name": "afterConv1","bundle": "control"},"direction": "READWRITE"},{"cName": "kernel1","offset": { "type": "dynamic","port_name": "kernel1","bundle": "control"},"direction": "READONLY"},{"cName": "bias1","offset": { "type": "dynamic","port_name": "bias1","bundle": "control"},"direction": "READONLY"},{"cName": "in_qk","offset": { "type": "dynamic","port_name": "in_qk","bundle": "control"},"direction": "READWRITE"},{"cName": "in_q","offset": { "type": "dynamic","port_name": "in_q","bundle": "control"},"direction": "READWRITE"},{"cName": "in_k","offset": { "type": "dynamic","port_name": "in_k","bundle": "control"},"direction": "READWRITE"},{"cName": "afterQKMultiplication","offset": { "type": "dynamic","port_name": "afterQKMultiplication","bundle": "control"},"direction": "READWRITE"},{"cName": "afterSoftmax","offset": { "type": "dynamic","port_name": "afterSoftmax","bundle": "control"},"direction": "READWRITE"},{"cName": "afterRearrangeX2","offset": { "type": "dynamic","port_name": "afterRearrangeX2","bundle": "control"},"direction": "READWRITE"},{"cName": "afterQKXMultiplication","offset": { "type": "dynamic","port_name": "afterQKXMultiplication","bundle": "control"},"direction": "READWRITE"},{"cName": "afterRearrangeQKX","offset": { "type": "dynamic","port_name": "afterRearrangeQKX","bundle": "control"},"direction": "READWRITE"},{"cName": "afterPad2","offset": { "type": "dynamic","port_name": "afterPad2","bundle": "control"},},{"cName": "afterConv2","offset": { "type": "dynamic","port_name": "afterConv2","bundle": "control"},"direction": "READWRITE"},{"cName": "kernel2","offset": { "type": "dynamic","port_name": "kernel2","bundle": "control"},"direction": "READONLY"},{"cName": "bias2","offset": { "type": "dynamic","port_name": "bias2","bundle": "control"},"direction": "READONLY"},{"cName": "afterAct2","offset": { "type": "dynamic","port_name": "afterAct2","bundle": "control"},"direction": "READWRITE"},{"cName": "QKV","offset": { "type": "dynamic","port_name": "QKV","bundle": "control"},"direction": "READWRITE"},{"cName": "buffer_out","offset": { "type": "dynamic","port_name": "buffer_out","bundle": "control"},"direction": "READWRITE"}]}]} , 
 	{ "Name" : "buffer_DataIn_1", "interface" : "axi_slave", "bundle":"control","type":"ap_none","bitwidth" : 64, "direction" : "READONLY", "offset" : {"in":16}, "offset_end" : {"in":27}} , 
 	{ "Name" : "afterNorm", "interface" : "axi_slave", "bundle":"control","type":"ap_none","bitwidth" : 64, "direction" : "READONLY", "offset" : {"in":28}, "offset_end" : {"in":39}} , 
 	{ "Name" : "norm1_mean", "interface" : "axi_slave", "bundle":"control","type":"ap_none","bitwidth" : 64, "direction" : "READONLY", "offset" : {"in":40}, "offset_end" : {"in":51}} , 
 	{ "Name" : "norm1_var", "interface" : "axi_slave", "bundle":"control","type":"ap_none","bitwidth" : 64, "direction" : "READONLY", "offset" : {"in":52}, "offset_end" : {"in":63}} , 
 	{ "Name" : "norm1_weight", "interface" : "axi_slave", "bundle":"control","type":"ap_none","bitwidth" : 64, "direction" : "READONLY", "offset" : {"in":64}, "offset_end" : {"in":75}} , 
 	{ "Name" : "norm1_bias", "interface" : "axi_slave", "bundle":"control","type":"ap_none","bitwidth" : 64, "direction" : "READONLY", "offset" : {"in":76}, "offset_end" : {"in":87}} , 
 	{ "Name" : "afterPad", "interface" : "axi_slave", "bundle":"control","type":"ap_none","bitwidth" : 64, "direction" : "READONLY", "offset" : {"in":88}, "offset_end" : {"in":99}} , 
 	{ "Name" : "afterRearrangeX", "interface" : "axi_slave", "bundle":"control","type":"ap_none","bitwidth" : 64, "direction" : "READONLY", "offset" : {"in":100}, "offset_end" : {"in":111}} , 
 	{ "Name" : "afterPad1", "interface" : "axi_slave", "bundle":"control","type":"ap_none","bitwidth" : 64, "direction" : "READONLY", "offset" : {"in":112}, "offset_end" : {"in":123}} , 
 	{ "Name" : "afterConv1", "interface" : "axi_slave", "bundle":"control","type":"ap_none","bitwidth" : 64, "direction" : "READONLY", "offset" : {"in":124}, "offset_end" : {"in":135}} , 
 	{ "Name" : "kernel1", "interface" : "axi_slave", "bundle":"control","type":"ap_none","bitwidth" : 64, "direction" : "READONLY", "offset" : {"in":136}, "offset_end" : {"in":147}} , 
 	{ "Name" : "bias1", "interface" : "axi_slave", "bundle":"control","type":"ap_none","bitwidth" : 64, "direction" : "READONLY", "offset" : {"in":148}, "offset_end" : {"in":159}} , 
 	{ "Name" : "in_qk", "interface" : "axi_slave", "bundle":"control","type":"ap_none","bitwidth" : 64, "direction" : "READONLY", "offset" : {"in":160}, "offset_end" : {"in":171}} , 
 	{ "Name" : "in_q", "interface" : "axi_slave", "bundle":"control","type":"ap_none","bitwidth" : 64, "direction" : "READONLY", "offset" : {"in":172}, "offset_end" : {"in":183}} , 
 	{ "Name" : "in_k", "interface" : "axi_slave", "bundle":"control","type":"ap_none","bitwidth" : 64, "direction" : "READONLY", "offset" : {"in":184}, "offset_end" : {"in":195}} , 
 	{ "Name" : "afterQKMultiplication", "interface" : "axi_slave", "bundle":"control","type":"ap_none","bitwidth" : 64, "direction" : "READONLY", "offset" : {"in":196}, "offset_end" : {"in":207}} , 
 	{ "Name" : "afterSoftmax", "interface" : "axi_slave", "bundle":"control","type":"ap_none","bitwidth" : 64, "direction" : "READONLY", "offset" : {"in":208}, "offset_end" : {"in":219}} , 
 	{ "Name" : "afterRearrangeX2", "interface" : "axi_slave", "bundle":"control","type":"ap_none","bitwidth" : 64, "direction" : "READONLY", "offset" : {"in":220}, "offset_end" : {"in":231}} , 
 	{ "Name" : "afterQKXMultiplication", "interface" : "axi_slave", "bundle":"control","type":"ap_none","bitwidth" : 64, "direction" : "READONLY", "offset" : {"in":232}, "offset_end" : {"in":243}} , 
 	{ "Name" : "afterRearrangeQKX", "interface" : "axi_slave", "bundle":"control","type":"ap_none","bitwidth" : 64, "direction" : "READONLY", "offset" : {"in":244}, "offset_end" : {"in":255}} , 
 	{ "Name" : "afterPad2", "interface" : "axi_slave", "bundle":"control","type":"ap_none","bitwidth" : 64, "direction" : "READONLY", "offset" : {"in":256}, "offset_end" : {"in":267}} , 
 	{ "Name" : "afterConv2", "interface" : "axi_slave", "bundle":"control","type":"ap_none","bitwidth" : 64, "direction" : "READONLY", "offset" : {"in":268}, "offset_end" : {"in":279}} , 
 	{ "Name" : "kernel2", "interface" : "axi_slave", "bundle":"control","type":"ap_none","bitwidth" : 64, "direction" : "READONLY", "offset" : {"in":280}, "offset_end" : {"in":291}} , 
 	{ "Name" : "bias2", "interface" : "axi_slave", "bundle":"control","type":"ap_none","bitwidth" : 64, "direction" : "READONLY", "offset" : {"in":292}, "offset_end" : {"in":303}} , 
 	{ "Name" : "afterAct2", "interface" : "axi_slave", "bundle":"control","type":"ap_none","bitwidth" : 64, "direction" : "READONLY", "offset" : {"in":304}, "offset_end" : {"in":315}} , 
 	{ "Name" : "QKV", "interface" : "axi_slave", "bundle":"control","type":"ap_none","bitwidth" : 64, "direction" : "READONLY", "offset" : {"in":316}, "offset_end" : {"in":327}} , 
 	{ "Name" : "buffer_out", "interface" : "axi_slave", "bundle":"control","type":"ap_none","bitwidth" : 64, "direction" : "READONLY", "offset" : {"in":328}, "offset_end" : {"in":339}} , 
 	{ "Name" : "buffer_result", "interface" : "axi_slave", "bundle":"control","type":"ap_none","bitwidth" : 64, "direction" : "READONLY", "offset" : {"in":340}, "offset_end" : {"in":351}} ]}
# RTL Port declarations: 
set portNum 158
set portList { 
	{ ap_clk sc_in sc_logic 1 clock -1 } 
	{ ap_rst_n sc_in sc_logic 1 reset -1 active_low_sync } 
	{ ap_start sc_in sc_logic 1 start -1 } 
	{ ap_done sc_out sc_logic 1 predone -1 } 
	{ ap_idle sc_out sc_logic 1 done -1 } 
	{ ap_ready sc_out sc_logic 1 ready -1 } 
	{ m_axi_gmem0_AWVALID sc_out sc_logic 1 signal 0 } 
	{ m_axi_gmem0_AWREADY sc_in sc_logic 1 signal 0 } 
	{ m_axi_gmem0_AWADDR sc_out sc_lv 64 signal 0 } 
	{ m_axi_gmem0_AWID sc_out sc_lv 1 signal 0 } 
	{ m_axi_gmem0_AWLEN sc_out sc_lv 8 signal 0 } 
	{ m_axi_gmem0_AWSIZE sc_out sc_lv 3 signal 0 } 
	{ m_axi_gmem0_AWBURST sc_out sc_lv 2 signal 0 } 
	{ m_axi_gmem0_AWLOCK sc_out sc_lv 2 signal 0 } 
	{ m_axi_gmem0_AWCACHE sc_out sc_lv 4 signal 0 } 
	{ m_axi_gmem0_AWPROT sc_out sc_lv 3 signal 0 } 
	{ m_axi_gmem0_AWQOS sc_out sc_lv 4 signal 0 } 
	{ m_axi_gmem0_AWREGION sc_out sc_lv 4 signal 0 } 
	{ m_axi_gmem0_AWUSER sc_out sc_lv 1 signal 0 } 
	{ m_axi_gmem0_WVALID sc_out sc_logic 1 signal 0 } 
	{ m_axi_gmem0_WREADY sc_in sc_logic 1 signal 0 } 
	{ m_axi_gmem0_WDATA sc_out sc_lv 32 signal 0 } 
	{ m_axi_gmem0_WSTRB sc_out sc_lv 4 signal 0 } 
	{ m_axi_gmem0_WLAST sc_out sc_logic 1 signal 0 } 
	{ m_axi_gmem0_WID sc_out sc_lv 1 signal 0 } 
	{ m_axi_gmem0_WUSER sc_out sc_lv 1 signal 0 } 
	{ m_axi_gmem0_ARVALID sc_out sc_logic 1 signal 0 } 
	{ m_axi_gmem0_ARREADY sc_in sc_logic 1 signal 0 } 
	{ m_axi_gmem0_ARADDR sc_out sc_lv 64 signal 0 } 
	{ m_axi_gmem0_ARID sc_out sc_lv 1 signal 0 } 
	{ m_axi_gmem0_ARLEN sc_out sc_lv 8 signal 0 } 
	{ m_axi_gmem0_ARSIZE sc_out sc_lv 3 signal 0 } 
	{ m_axi_gmem0_ARBURST sc_out sc_lv 2 signal 0 } 
	{ m_axi_gmem0_ARLOCK sc_out sc_lv 2 signal 0 } 
	{ m_axi_gmem0_ARCACHE sc_out sc_lv 4 signal 0 } 
	{ m_axi_gmem0_ARPROT sc_out sc_lv 3 signal 0 } 
	{ m_axi_gmem0_ARQOS sc_out sc_lv 4 signal 0 } 
	{ m_axi_gmem0_ARREGION sc_out sc_lv 4 signal 0 } 
	{ m_axi_gmem0_ARUSER sc_out sc_lv 1 signal 0 } 
	{ m_axi_gmem0_RVALID sc_in sc_logic 1 signal 0 } 
	{ m_axi_gmem0_RREADY sc_out sc_logic 1 signal 0 } 
	{ m_axi_gmem0_RDATA sc_in sc_lv 32 signal 0 } 
	{ m_axi_gmem0_RLAST sc_in sc_logic 1 signal 0 } 
	{ m_axi_gmem0_RID sc_in sc_lv 1 signal 0 } 
	{ m_axi_gmem0_RUSER sc_in sc_lv 1 signal 0 } 
	{ m_axi_gmem0_RRESP sc_in sc_lv 2 signal 0 } 
	{ m_axi_gmem0_BVALID sc_in sc_logic 1 signal 0 } 
	{ m_axi_gmem0_BREADY sc_out sc_logic 1 signal 0 } 
	{ m_axi_gmem0_BRESP sc_in sc_lv 2 signal 0 } 
	{ m_axi_gmem0_BID sc_in sc_lv 1 signal 0 } 
	{ m_axi_gmem0_BUSER sc_in sc_lv 1 signal 0 } 
	{ m_axi_gmem1_AWVALID sc_out sc_logic 1 signal 1 } 
	{ m_axi_gmem1_AWREADY sc_in sc_logic 1 signal 1 } 
	{ m_axi_gmem1_AWADDR sc_out sc_lv 64 signal 1 } 
	{ m_axi_gmem1_AWID sc_out sc_lv 1 signal 1 } 
	{ m_axi_gmem1_AWLEN sc_out sc_lv 8 signal 1 } 
	{ m_axi_gmem1_AWSIZE sc_out sc_lv 3 signal 1 } 
	{ m_axi_gmem1_AWBURST sc_out sc_lv 2 signal 1 } 
	{ m_axi_gmem1_AWLOCK sc_out sc_lv 2 signal 1 } 
	{ m_axi_gmem1_AWCACHE sc_out sc_lv 4 signal 1 } 
	{ m_axi_gmem1_AWPROT sc_out sc_lv 3 signal 1 } 
	{ m_axi_gmem1_AWQOS sc_out sc_lv 4 signal 1 } 
	{ m_axi_gmem1_AWREGION sc_out sc_lv 4 signal 1 } 
	{ m_axi_gmem1_AWUSER sc_out sc_lv 1 signal 1 } 
	{ m_axi_gmem1_WVALID sc_out sc_logic 1 signal 1 } 
	{ m_axi_gmem1_WREADY sc_in sc_logic 1 signal 1 } 
	{ m_axi_gmem1_WDATA sc_out sc_lv 32 signal 1 } 
	{ m_axi_gmem1_WSTRB sc_out sc_lv 4 signal 1 } 
	{ m_axi_gmem1_WLAST sc_out sc_logic 1 signal 1 } 
	{ m_axi_gmem1_WID sc_out sc_lv 1 signal 1 } 
	{ m_axi_gmem1_WUSER sc_out sc_lv 1 signal 1 } 
	{ m_axi_gmem1_ARVALID sc_out sc_logic 1 signal 1 } 
	{ m_axi_gmem1_ARREADY sc_in sc_logic 1 signal 1 } 
	{ m_axi_gmem1_ARADDR sc_out sc_lv 64 signal 1 } 
	{ m_axi_gmem1_ARID sc_out sc_lv 1 signal 1 } 
	{ m_axi_gmem1_ARLEN sc_out sc_lv 8 signal 1 } 
	{ m_axi_gmem1_ARSIZE sc_out sc_lv 3 signal 1 } 
	{ m_axi_gmem1_ARBURST sc_out sc_lv 2 signal 1 } 
	{ m_axi_gmem1_ARLOCK sc_out sc_lv 2 signal 1 } 
	{ m_axi_gmem1_ARCACHE sc_out sc_lv 4 signal 1 } 
	{ m_axi_gmem1_ARPROT sc_out sc_lv 3 signal 1 } 
	{ m_axi_gmem1_ARQOS sc_out sc_lv 4 signal 1 } 
	{ m_axi_gmem1_ARREGION sc_out sc_lv 4 signal 1 } 
	{ m_axi_gmem1_ARUSER sc_out sc_lv 1 signal 1 } 
	{ m_axi_gmem1_RVALID sc_in sc_logic 1 signal 1 } 
	{ m_axi_gmem1_RREADY sc_out sc_logic 1 signal 1 } 
	{ m_axi_gmem1_RDATA sc_in sc_lv 32 signal 1 } 
	{ m_axi_gmem1_RLAST sc_in sc_logic 1 signal 1 } 
	{ m_axi_gmem1_RID sc_in sc_lv 1 signal 1 } 
	{ m_axi_gmem1_RUSER sc_in sc_lv 1 signal 1 } 
	{ m_axi_gmem1_RRESP sc_in sc_lv 2 signal 1 } 
	{ m_axi_gmem1_BVALID sc_in sc_logic 1 signal 1 } 
	{ m_axi_gmem1_BREADY sc_out sc_logic 1 signal 1 } 
	{ m_axi_gmem1_BRESP sc_in sc_lv 2 signal 1 } 
	{ m_axi_gmem1_BID sc_in sc_lv 1 signal 1 } 
	{ m_axi_gmem1_BUSER sc_in sc_lv 1 signal 1 } 
	{ m_axi_gmem_AWVALID sc_out sc_logic 1 signal 2 } 
	{ m_axi_gmem_AWREADY sc_in sc_logic 1 signal 2 } 
	{ m_axi_gmem_AWADDR sc_out sc_lv 64 signal 2 } 
	{ m_axi_gmem_AWID sc_out sc_lv 1 signal 2 } 
	{ m_axi_gmem_AWLEN sc_out sc_lv 8 signal 2 } 
	{ m_axi_gmem_AWSIZE sc_out sc_lv 3 signal 2 } 
	{ m_axi_gmem_AWBURST sc_out sc_lv 2 signal 2 } 
	{ m_axi_gmem_AWLOCK sc_out sc_lv 2 signal 2 } 
	{ m_axi_gmem_AWCACHE sc_out sc_lv 4 signal 2 } 
	{ m_axi_gmem_AWPROT sc_out sc_lv 3 signal 2 } 
	{ m_axi_gmem_AWQOS sc_out sc_lv 4 signal 2 } 
	{ m_axi_gmem_AWREGION sc_out sc_lv 4 signal 2 } 
	{ m_axi_gmem_AWUSER sc_out sc_lv 1 signal 2 } 
	{ m_axi_gmem_WVALID sc_out sc_logic 1 signal 2 } 
	{ m_axi_gmem_WREADY sc_in sc_logic 1 signal 2 } 
	{ m_axi_gmem_WDATA sc_out sc_lv 32 signal 2 } 
	{ m_axi_gmem_WSTRB sc_out sc_lv 4 signal 2 } 
	{ m_axi_gmem_WLAST sc_out sc_logic 1 signal 2 } 
	{ m_axi_gmem_WID sc_out sc_lv 1 signal 2 } 
	{ m_axi_gmem_WUSER sc_out sc_lv 1 signal 2 } 
	{ m_axi_gmem_ARVALID sc_out sc_logic 1 signal 2 } 
	{ m_axi_gmem_ARREADY sc_in sc_logic 1 signal 2 } 
	{ m_axi_gmem_ARADDR sc_out sc_lv 64 signal 2 } 
	{ m_axi_gmem_ARID sc_out sc_lv 1 signal 2 } 
	{ m_axi_gmem_ARLEN sc_out sc_lv 8 signal 2 } 
	{ m_axi_gmem_ARSIZE sc_out sc_lv 3 signal 2 } 
	{ m_axi_gmem_ARBURST sc_out sc_lv 2 signal 2 } 
	{ m_axi_gmem_ARLOCK sc_out sc_lv 2 signal 2 } 
	{ m_axi_gmem_ARCACHE sc_out sc_lv 4 signal 2 } 
	{ m_axi_gmem_ARPROT sc_out sc_lv 3 signal 2 } 
	{ m_axi_gmem_ARQOS sc_out sc_lv 4 signal 2 } 
	{ m_axi_gmem_ARREGION sc_out sc_lv 4 signal 2 } 
	{ m_axi_gmem_ARUSER sc_out sc_lv 1 signal 2 } 
	{ m_axi_gmem_RVALID sc_in sc_logic 1 signal 2 } 
	{ m_axi_gmem_RREADY sc_out sc_logic 1 signal 2 } 
	{ m_axi_gmem_RDATA sc_in sc_lv 32 signal 2 } 
	{ m_axi_gmem_RLAST sc_in sc_logic 1 signal 2 } 
	{ m_axi_gmem_RID sc_in sc_lv 1 signal 2 } 
	{ m_axi_gmem_RUSER sc_in sc_lv 1 signal 2 } 
	{ m_axi_gmem_RRESP sc_in sc_lv 2 signal 2 } 
	{ m_axi_gmem_BVALID sc_in sc_logic 1 signal 2 } 
	{ m_axi_gmem_BREADY sc_out sc_logic 1 signal 2 } 
	{ m_axi_gmem_BRESP sc_in sc_lv 2 signal 2 } 
	{ m_axi_gmem_BID sc_in sc_lv 1 signal 2 } 
	{ m_axi_gmem_BUSER sc_in sc_lv 1 signal 2 } 
	{ s_axi_control_AWVALID sc_in sc_logic 1 signal -1 } 
	{ s_axi_control_AWREADY sc_out sc_logic 1 signal -1 } 
	{ s_axi_control_AWADDR sc_in sc_lv 9 signal -1 } 
	{ s_axi_control_WVALID sc_in sc_logic 1 signal -1 } 
	{ s_axi_control_WREADY sc_out sc_logic 1 signal -1 } 
	{ s_axi_control_WDATA sc_in sc_lv 32 signal -1 } 
	{ s_axi_control_WSTRB sc_in sc_lv 4 signal -1 } 
	{ s_axi_control_ARVALID sc_in sc_logic 1 signal -1 } 
	{ s_axi_control_ARREADY sc_out sc_logic 1 signal -1 } 
	{ s_axi_control_ARADDR sc_in sc_lv 9 signal -1 } 
	{ s_axi_control_RVALID sc_out sc_logic 1 signal -1 } 
	{ s_axi_control_RREADY sc_in sc_logic 1 signal -1 } 
	{ s_axi_control_RDATA sc_out sc_lv 32 signal -1 } 
	{ s_axi_control_RRESP sc_out sc_lv 2 signal -1 } 
	{ s_axi_control_BVALID sc_out sc_logic 1 signal -1 } 
	{ s_axi_control_BREADY sc_in sc_logic 1 signal -1 } 
	{ s_axi_control_BRESP sc_out sc_lv 2 signal -1 } 
}
set NewPortList {[ 
	{ "name": "s_axi_control_AWADDR", "direction": "in", "datatype": "sc_lv", "bitwidth":9, "type": "signal", "bundle":{"name": "control", "role": "AWADDR" },"address":[{"name":"buffer_DataIn_1","role":"data","value":"16"},{"name":"afterNorm","role":"data","value":"28"},{"name":"norm1_mean","role":"data","value":"40"},{"name":"norm1_var","role":"data","value":"52"},{"name":"norm1_weight","role":"data","value":"64"},{"name":"norm1_bias","role":"data","value":"76"},{"name":"afterPad","role":"data","value":"88"},{"name":"afterRearrangeX","role":"data","value":"100"},{"name":"afterPad1","role":"data","value":"112"},{"name":"afterConv1","role":"data","value":"124"},{"name":"kernel1","role":"data","value":"136"},{"name":"bias1","role":"data","value":"148"},{"name":"in_qk","role":"data","value":"160"},{"name":"in_q","role":"data","value":"172"},{"name":"in_k","role":"data","value":"184"},{"name":"afterQKMultiplication","role":"data","value":"196"},{"name":"afterSoftmax","role":"data","value":"208"},{"name":"afterRearrangeX2","role":"data","value":"220"},{"name":"afterQKXMultiplication","role":"data","value":"232"},{"name":"afterRearrangeQKX","role":"data","value":"244"},{"name":"afterPad2","role":"data","value":"256"},{"name":"afterConv2","role":"data","value":"268"},{"name":"kernel2","role":"data","value":"280"},{"name":"bias2","role":"data","value":"292"},{"name":"afterAct2","role":"data","value":"304"},{"name":"QKV","role":"data","value":"316"},{"name":"buffer_out","role":"data","value":"328"},{"name":"buffer_result","role":"data","value":"340"}] },
	{ "name": "s_axi_control_AWVALID", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "control", "role": "AWVALID" } },
	{ "name": "s_axi_control_AWREADY", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "control", "role": "AWREADY" } },
	{ "name": "s_axi_control_WVALID", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "control", "role": "WVALID" } },
	{ "name": "s_axi_control_WREADY", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "control", "role": "WREADY" } },
	{ "name": "s_axi_control_WDATA", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "control", "role": "WDATA" } },
	{ "name": "s_axi_control_WSTRB", "direction": "in", "datatype": "sc_lv", "bitwidth":4, "type": "signal", "bundle":{"name": "control", "role": "WSTRB" } },
	{ "name": "s_axi_control_ARADDR", "direction": "in", "datatype": "sc_lv", "bitwidth":9, "type": "signal", "bundle":{"name": "control", "role": "ARADDR" },"address":[] },
	{ "name": "s_axi_control_ARVALID", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "control", "role": "ARVALID" } },
	{ "name": "s_axi_control_ARREADY", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "control", "role": "ARREADY" } },
	{ "name": "s_axi_control_RVALID", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "control", "role": "RVALID" } },
	{ "name": "s_axi_control_RREADY", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "control", "role": "RREADY" } },
	{ "name": "s_axi_control_RDATA", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "control", "role": "RDATA" } },
	{ "name": "s_axi_control_RRESP", "direction": "out", "datatype": "sc_lv", "bitwidth":2, "type": "signal", "bundle":{"name": "control", "role": "RRESP" } },
	{ "name": "s_axi_control_BVALID", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "control", "role": "BVALID" } },
	{ "name": "s_axi_control_BREADY", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "control", "role": "BREADY" } },
	{ "name": "s_axi_control_BRESP", "direction": "out", "datatype": "sc_lv", "bitwidth":2, "type": "signal", "bundle":{"name": "control", "role": "BRESP" } }, 
 	{ "name": "ap_clk", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "clock", "bundle":{"name": "ap_clk", "role": "default" }} , 
 	{ "name": "ap_rst_n", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "reset", "bundle":{"name": "ap_rst_n", "role": "default" }} , 
 	{ "name": "ap_start", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "start", "bundle":{"name": "ap_start", "role": "default" }} , 
 	{ "name": "ap_done", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "predone", "bundle":{"name": "ap_done", "role": "default" }} , 
 	{ "name": "ap_idle", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "done", "bundle":{"name": "ap_idle", "role": "default" }} , 
 	{ "name": "ap_ready", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "ready", "bundle":{"name": "ap_ready", "role": "default" }} , 
 	{ "name": "m_axi_gmem0_AWVALID", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem0", "role": "AWVALID" }} , 
 	{ "name": "m_axi_gmem0_AWREADY", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem0", "role": "AWREADY" }} , 
 	{ "name": "m_axi_gmem0_AWADDR", "direction": "out", "datatype": "sc_lv", "bitwidth":64, "type": "signal", "bundle":{"name": "gmem0", "role": "AWADDR" }} , 
 	{ "name": "m_axi_gmem0_AWID", "direction": "out", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem0", "role": "AWID" }} , 
 	{ "name": "m_axi_gmem0_AWLEN", "direction": "out", "datatype": "sc_lv", "bitwidth":8, "type": "signal", "bundle":{"name": "gmem0", "role": "AWLEN" }} , 
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
 	{ "name": "m_axi_gmem0_ARLEN", "direction": "out", "datatype": "sc_lv", "bitwidth":8, "type": "signal", "bundle":{"name": "gmem0", "role": "ARLEN" }} , 
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
 	{ "name": "m_axi_gmem0_RUSER", "direction": "in", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem0", "role": "RUSER" }} , 
 	{ "name": "m_axi_gmem0_RRESP", "direction": "in", "datatype": "sc_lv", "bitwidth":2, "type": "signal", "bundle":{"name": "gmem0", "role": "RRESP" }} , 
 	{ "name": "m_axi_gmem0_BVALID", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem0", "role": "BVALID" }} , 
 	{ "name": "m_axi_gmem0_BREADY", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem0", "role": "BREADY" }} , 
 	{ "name": "m_axi_gmem0_BRESP", "direction": "in", "datatype": "sc_lv", "bitwidth":2, "type": "signal", "bundle":{"name": "gmem0", "role": "BRESP" }} , 
 	{ "name": "m_axi_gmem0_BID", "direction": "in", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem0", "role": "BID" }} , 
 	{ "name": "m_axi_gmem0_BUSER", "direction": "in", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem0", "role": "BUSER" }} , 
 	{ "name": "m_axi_gmem1_AWVALID", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem1", "role": "AWVALID" }} , 
 	{ "name": "m_axi_gmem1_AWREADY", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem1", "role": "AWREADY" }} , 
 	{ "name": "m_axi_gmem1_AWADDR", "direction": "out", "datatype": "sc_lv", "bitwidth":64, "type": "signal", "bundle":{"name": "gmem1", "role": "AWADDR" }} , 
 	{ "name": "m_axi_gmem1_AWID", "direction": "out", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem1", "role": "AWID" }} , 
 	{ "name": "m_axi_gmem1_AWLEN", "direction": "out", "datatype": "sc_lv", "bitwidth":8, "type": "signal", "bundle":{"name": "gmem1", "role": "AWLEN" }} , 
 	{ "name": "m_axi_gmem1_AWSIZE", "direction": "out", "datatype": "sc_lv", "bitwidth":3, "type": "signal", "bundle":{"name": "gmem1", "role": "AWSIZE" }} , 
 	{ "name": "m_axi_gmem1_AWBURST", "direction": "out", "datatype": "sc_lv", "bitwidth":2, "type": "signal", "bundle":{"name": "gmem1", "role": "AWBURST" }} , 
 	{ "name": "m_axi_gmem1_AWLOCK", "direction": "out", "datatype": "sc_lv", "bitwidth":2, "type": "signal", "bundle":{"name": "gmem1", "role": "AWLOCK" }} , 
 	{ "name": "m_axi_gmem1_AWCACHE", "direction": "out", "datatype": "sc_lv", "bitwidth":4, "type": "signal", "bundle":{"name": "gmem1", "role": "AWCACHE" }} , 
 	{ "name": "m_axi_gmem1_AWPROT", "direction": "out", "datatype": "sc_lv", "bitwidth":3, "type": "signal", "bundle":{"name": "gmem1", "role": "AWPROT" }} , 
 	{ "name": "m_axi_gmem1_AWQOS", "direction": "out", "datatype": "sc_lv", "bitwidth":4, "type": "signal", "bundle":{"name": "gmem1", "role": "AWQOS" }} , 
 	{ "name": "m_axi_gmem1_AWREGION", "direction": "out", "datatype": "sc_lv", "bitwidth":4, "type": "signal", "bundle":{"name": "gmem1", "role": "AWREGION" }} , 
 	{ "name": "m_axi_gmem1_AWUSER", "direction": "out", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem1", "role": "AWUSER" }} , 
 	{ "name": "m_axi_gmem1_WVALID", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem1", "role": "WVALID" }} , 
 	{ "name": "m_axi_gmem1_WREADY", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem1", "role": "WREADY" }} , 
 	{ "name": "m_axi_gmem1_WDATA", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "gmem1", "role": "WDATA" }} , 
 	{ "name": "m_axi_gmem1_WSTRB", "direction": "out", "datatype": "sc_lv", "bitwidth":4, "type": "signal", "bundle":{"name": "gmem1", "role": "WSTRB" }} , 
 	{ "name": "m_axi_gmem1_WLAST", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem1", "role": "WLAST" }} , 
 	{ "name": "m_axi_gmem1_WID", "direction": "out", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem1", "role": "WID" }} , 
 	{ "name": "m_axi_gmem1_WUSER", "direction": "out", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem1", "role": "WUSER" }} , 
 	{ "name": "m_axi_gmem1_ARVALID", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem1", "role": "ARVALID" }} , 
 	{ "name": "m_axi_gmem1_ARREADY", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem1", "role": "ARREADY" }} , 
 	{ "name": "m_axi_gmem1_ARADDR", "direction": "out", "datatype": "sc_lv", "bitwidth":64, "type": "signal", "bundle":{"name": "gmem1", "role": "ARADDR" }} , 
 	{ "name": "m_axi_gmem1_ARID", "direction": "out", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem1", "role": "ARID" }} , 
 	{ "name": "m_axi_gmem1_ARLEN", "direction": "out", "datatype": "sc_lv", "bitwidth":8, "type": "signal", "bundle":{"name": "gmem1", "role": "ARLEN" }} , 
 	{ "name": "m_axi_gmem1_ARSIZE", "direction": "out", "datatype": "sc_lv", "bitwidth":3, "type": "signal", "bundle":{"name": "gmem1", "role": "ARSIZE" }} , 
 	{ "name": "m_axi_gmem1_ARBURST", "direction": "out", "datatype": "sc_lv", "bitwidth":2, "type": "signal", "bundle":{"name": "gmem1", "role": "ARBURST" }} , 
 	{ "name": "m_axi_gmem1_ARLOCK", "direction": "out", "datatype": "sc_lv", "bitwidth":2, "type": "signal", "bundle":{"name": "gmem1", "role": "ARLOCK" }} , 
 	{ "name": "m_axi_gmem1_ARCACHE", "direction": "out", "datatype": "sc_lv", "bitwidth":4, "type": "signal", "bundle":{"name": "gmem1", "role": "ARCACHE" }} , 
 	{ "name": "m_axi_gmem1_ARPROT", "direction": "out", "datatype": "sc_lv", "bitwidth":3, "type": "signal", "bundle":{"name": "gmem1", "role": "ARPROT" }} , 
 	{ "name": "m_axi_gmem1_ARQOS", "direction": "out", "datatype": "sc_lv", "bitwidth":4, "type": "signal", "bundle":{"name": "gmem1", "role": "ARQOS" }} , 
 	{ "name": "m_axi_gmem1_ARREGION", "direction": "out", "datatype": "sc_lv", "bitwidth":4, "type": "signal", "bundle":{"name": "gmem1", "role": "ARREGION" }} , 
 	{ "name": "m_axi_gmem1_ARUSER", "direction": "out", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem1", "role": "ARUSER" }} , 
 	{ "name": "m_axi_gmem1_RVALID", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem1", "role": "RVALID" }} , 
 	{ "name": "m_axi_gmem1_RREADY", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem1", "role": "RREADY" }} , 
 	{ "name": "m_axi_gmem1_RDATA", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "gmem1", "role": "RDATA" }} , 
 	{ "name": "m_axi_gmem1_RLAST", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem1", "role": "RLAST" }} , 
 	{ "name": "m_axi_gmem1_RID", "direction": "in", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem1", "role": "RID" }} , 
 	{ "name": "m_axi_gmem1_RUSER", "direction": "in", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem1", "role": "RUSER" }} , 
 	{ "name": "m_axi_gmem1_RRESP", "direction": "in", "datatype": "sc_lv", "bitwidth":2, "type": "signal", "bundle":{"name": "gmem1", "role": "RRESP" }} , 
 	{ "name": "m_axi_gmem1_BVALID", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem1", "role": "BVALID" }} , 
 	{ "name": "m_axi_gmem1_BREADY", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem1", "role": "BREADY" }} , 
 	{ "name": "m_axi_gmem1_BRESP", "direction": "in", "datatype": "sc_lv", "bitwidth":2, "type": "signal", "bundle":{"name": "gmem1", "role": "BRESP" }} , 
 	{ "name": "m_axi_gmem1_BID", "direction": "in", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem1", "role": "BID" }} , 
 	{ "name": "m_axi_gmem1_BUSER", "direction": "in", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem1", "role": "BUSER" }} , 
 	{ "name": "m_axi_gmem_AWVALID", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem", "role": "AWVALID" }} , 
 	{ "name": "m_axi_gmem_AWREADY", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem", "role": "AWREADY" }} , 
 	{ "name": "m_axi_gmem_AWADDR", "direction": "out", "datatype": "sc_lv", "bitwidth":64, "type": "signal", "bundle":{"name": "gmem", "role": "AWADDR" }} , 
 	{ "name": "m_axi_gmem_AWID", "direction": "out", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem", "role": "AWID" }} , 
 	{ "name": "m_axi_gmem_AWLEN", "direction": "out", "datatype": "sc_lv", "bitwidth":8, "type": "signal", "bundle":{"name": "gmem", "role": "AWLEN" }} , 
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
 	{ "name": "m_axi_gmem_ARLEN", "direction": "out", "datatype": "sc_lv", "bitwidth":8, "type": "signal", "bundle":{"name": "gmem", "role": "ARLEN" }} , 
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
 	{ "name": "m_axi_gmem_RUSER", "direction": "in", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem", "role": "RUSER" }} , 
 	{ "name": "m_axi_gmem_RRESP", "direction": "in", "datatype": "sc_lv", "bitwidth":2, "type": "signal", "bundle":{"name": "gmem", "role": "RRESP" }} , 
 	{ "name": "m_axi_gmem_BVALID", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem", "role": "BVALID" }} , 
 	{ "name": "m_axi_gmem_BREADY", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem", "role": "BREADY" }} , 
 	{ "name": "m_axi_gmem_BRESP", "direction": "in", "datatype": "sc_lv", "bitwidth":2, "type": "signal", "bundle":{"name": "gmem", "role": "BRESP" }} , 
 	{ "name": "m_axi_gmem_BID", "direction": "in", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem", "role": "BID" }} , 
 	{ "name": "m_axi_gmem_BUSER", "direction": "in", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem", "role": "BUSER" }}  ]}

set RtlHierarchyInfo {[
	{"ID" : "0", "Level" : "0", "Path" : "`AUTOTB_DUT_INST", "Parent" : "", "Child" : ["1", "9", "11", "15", "25", "31", "43", "53", "77", "83", "88", "95", "99", "101", "102", "103", "104", "105", "106", "107", "108"],
		"CDFG" : "kernel_attention",
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
			{"Name" : "gmem0", "Type" : "MAXI", "Direction" : "IO",
				"BlockSignal" : [
					{"Name" : "gmem0_blk_n_AR", "Type" : "RtlSignal"},
					{"Name" : "gmem0_blk_n_AW", "Type" : "RtlSignal"},
					{"Name" : "gmem0_blk_n_B", "Type" : "RtlSignal"}],
				"SubConnect" : [
					{"ID" : "1", "SubInstance" : "grp_kernel_attention_Pipeline_VITIS_LOOP_373_3_VITIS_LOOP_375_4_fu_525", "Port" : "gmem0", "Inst_start_state" : "25", "Inst_end_state" : "26"},
					{"ID" : "99", "SubInstance" : "grp_kernel_attention_Pipeline_VITIS_LOOP_268_2_VITIS_LOOP_269_3_VITIS_LOOP_270_4_fu_655", "Port" : "gmem0", "Inst_start_state" : "113", "Inst_end_state" : "114"}]},
			{"Name" : "gmem1", "Type" : "MAXI", "Direction" : "IO",
				"BlockSignal" : [
					{"Name" : "gmem1_blk_n_AW", "Type" : "RtlSignal"},
					{"Name" : "gmem1_blk_n_B", "Type" : "RtlSignal"},
					{"Name" : "gmem1_blk_n_AR", "Type" : "RtlSignal"}],
				"SubConnect" : [
					{"ID" : "1", "SubInstance" : "grp_kernel_attention_Pipeline_VITIS_LOOP_373_3_VITIS_LOOP_375_4_fu_525", "Port" : "gmem1", "Inst_start_state" : "25", "Inst_end_state" : "26"},
					{"ID" : "9", "SubInstance" : "grp_kernel_attention_Pipeline_VITIS_LOOP_17_2_VITIS_LOOP_18_3_VITIS_LOOP_19_4_fu_539", "Port" : "gmem1", "Inst_start_state" : "39", "Inst_end_state" : "40"}]},
			{"Name" : "gmem", "Type" : "MAXI", "Direction" : "IO",
				"BlockSignal" : [
					{"Name" : "gmem_blk_n_AR", "Type" : "RtlSignal"},
					{"Name" : "gmem_blk_n_R", "Type" : "RtlSignal"},
					{"Name" : "gmem_blk_n_AW", "Type" : "RtlSignal"},
					{"Name" : "gmem_blk_n_B", "Type" : "RtlSignal"}],
				"SubConnect" : [
					{"ID" : "77", "SubInstance" : "grp_kernel_attention_Pipeline_VITIS_LOOP_110_1_VITIS_LOOP_114_3_VITIS_LOOP_116_4_VIT_fu_623", "Port" : "gmem", "Inst_start_state" : "71", "Inst_end_state" : "72"},
					{"ID" : "9", "SubInstance" : "grp_kernel_attention_Pipeline_VITIS_LOOP_17_2_VITIS_LOOP_18_3_VITIS_LOOP_19_4_fu_539", "Port" : "gmem", "Inst_start_state" : "39", "Inst_end_state" : "40"},
					{"ID" : "83", "SubInstance" : "grp_kernel_attention_Pipeline_VITIS_LOOP_177_1_VITIS_LOOP_181_3_VITIS_LOOP_183_4_VIT_fu_631", "Port" : "gmem", "Inst_start_state" : "82", "Inst_end_state" : "83"},
					{"ID" : "25", "SubInstance" : "grp_compute_skip_fu_570", "Port" : "gmem", "Inst_start_state" : "95", "Inst_end_state" : "96"},
					{"ID" : "31", "SubInstance" : "grp_get_qk_fu_581", "Port" : "gmem", "Inst_start_state" : "52", "Inst_end_state" : "53"},
					{"ID" : "53", "SubInstance" : "grp_kernel_attention_Pipeline_VITIS_LOOP_230_1_VITIS_LOOP_232_3_count_sum_fu_608", "Port" : "gmem", "Inst_start_state" : "57", "Inst_end_state" : "58"},
					{"ID" : "11", "SubInstance" : "grp_kernel_attention_Pipeline_VITIS_LOOP_80_2_VITIS_LOOP_82_3_fu_549", "Port" : "gmem", "Inst_start_state" : "46", "Inst_end_state" : "47"},
					{"ID" : "95", "SubInstance" : "grp_kernel_attention_Pipeline_VITIS_LOOP_146_2_VITIS_LOOP_150_4_VITIS_LOOP_152_5_VIT_fu_647", "Port" : "gmem", "Inst_start_state" : "104", "Inst_end_state" : "105"},
					{"ID" : "88", "SubInstance" : "grp_kernel_attention_Pipeline_VITIS_LOOP_511_1_VITIS_LOOP_515_3_VITIS_LOOP_517_4_fu_639", "Port" : "gmem", "Inst_start_state" : "93", "Inst_end_state" : "94"},
					{"ID" : "15", "SubInstance" : "grp_DW_conv_fu_557", "Port" : "gmem", "Inst_start_state" : "84", "Inst_end_state" : "85"},
					{"ID" : "43", "SubInstance" : "grp_compute_multiplication_fu_590", "Port" : "gmem", "Inst_start_state" : "73", "Inst_end_state" : "74"},
					{"ID" : "99", "SubInstance" : "grp_kernel_attention_Pipeline_VITIS_LOOP_268_2_VITIS_LOOP_269_3_VITIS_LOOP_270_4_fu_655", "Port" : "gmem", "Inst_start_state" : "113", "Inst_end_state" : "114"}]},
			{"Name" : "buffer_DataIn_1", "Type" : "None", "Direction" : "I"},
			{"Name" : "afterNorm", "Type" : "None", "Direction" : "I"},
			{"Name" : "norm1_mean", "Type" : "None", "Direction" : "I"},
			{"Name" : "norm1_var", "Type" : "None", "Direction" : "I"},
			{"Name" : "norm1_weight", "Type" : "None", "Direction" : "I"},
			{"Name" : "norm1_bias", "Type" : "None", "Direction" : "I"},
			{"Name" : "afterPad", "Type" : "None", "Direction" : "I"},
			{"Name" : "afterRearrangeX", "Type" : "None", "Direction" : "I"},
			{"Name" : "afterPad1", "Type" : "None", "Direction" : "I"},
			{"Name" : "afterConv1", "Type" : "None", "Direction" : "I"},
			{"Name" : "kernel1", "Type" : "None", "Direction" : "I"},
			{"Name" : "bias1", "Type" : "None", "Direction" : "I"},
			{"Name" : "in_qk", "Type" : "None", "Direction" : "I"},
			{"Name" : "in_q", "Type" : "None", "Direction" : "I"},
			{"Name" : "in_k", "Type" : "None", "Direction" : "I"},
			{"Name" : "afterQKMultiplication", "Type" : "None", "Direction" : "I"},
			{"Name" : "afterSoftmax", "Type" : "None", "Direction" : "I"},
			{"Name" : "afterRearrangeX2", "Type" : "None", "Direction" : "I"},
			{"Name" : "afterQKXMultiplication", "Type" : "None", "Direction" : "I"},
			{"Name" : "afterRearrangeQKX", "Type" : "None", "Direction" : "I"},
			{"Name" : "afterPad2", "Type" : "None", "Direction" : "I"},
			{"Name" : "afterConv2", "Type" : "None", "Direction" : "I"},
			{"Name" : "kernel2", "Type" : "None", "Direction" : "I"},
			{"Name" : "bias2", "Type" : "None", "Direction" : "I"},
			{"Name" : "afterAct2", "Type" : "None", "Direction" : "I"},
			{"Name" : "QKV", "Type" : "None", "Direction" : "I"},
			{"Name" : "buffer_out", "Type" : "None", "Direction" : "I"},
			{"Name" : "buffer_result", "Type" : "None", "Direction" : "I"},
			{"Name" : "pow_reduce_anonymous_namespace_table_exp_Z1_ap_ufixed_array_V", "Type" : "Memory", "Direction" : "I",
				"SubConnect" : [
					{"ID" : "53", "SubInstance" : "grp_kernel_attention_Pipeline_VITIS_LOOP_230_1_VITIS_LOOP_232_3_count_sum_fu_608", "Port" : "pow_reduce_anonymous_namespace_table_exp_Z1_ap_ufixed_array_V", "Inst_start_state" : "57", "Inst_end_state" : "58"}]},
			{"Name" : "pow_reduce_anonymous_namespace_table_f_Z3_ap_ufixed_array_V", "Type" : "Memory", "Direction" : "I",
				"SubConnect" : [
					{"ID" : "53", "SubInstance" : "grp_kernel_attention_Pipeline_VITIS_LOOP_230_1_VITIS_LOOP_232_3_count_sum_fu_608", "Port" : "pow_reduce_anonymous_namespace_table_f_Z3_ap_ufixed_array_V", "Inst_start_state" : "57", "Inst_end_state" : "58"}]},
			{"Name" : "pow_reduce_anonymous_namespace_table_f_Z2_ap_ufixed_array_V", "Type" : "Memory", "Direction" : "I",
				"SubConnect" : [
					{"ID" : "53", "SubInstance" : "grp_kernel_attention_Pipeline_VITIS_LOOP_230_1_VITIS_LOOP_232_3_count_sum_fu_608", "Port" : "pow_reduce_anonymous_namespace_table_f_Z2_ap_ufixed_array_V", "Inst_start_state" : "57", "Inst_end_state" : "58"}]}],
		"Loop" : [
			{"Name" : "VITIS_LOOP_371_2", "PipelineType" : "no",
				"LoopDec" : {"FSMBitwidth" : "119", "FirstState" : "ap_ST_fsm_state9", "LastState" : ["ap_ST_fsm_state26"], "QuitState" : ["ap_ST_fsm_state9"], "PreState" : ["ap_ST_fsm_state8"], "PostState" : ["ap_ST_fsm_state27"], "OneDepthLoop" : "0", "OneStateBlock": ""}}]},
	{"ID" : "1", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.grp_kernel_attention_Pipeline_VITIS_LOOP_373_3_VITIS_LOOP_375_4_fu_525", "Parent" : "0", "Child" : ["2", "3", "4", "5", "6", "7", "8"],
		"CDFG" : "kernel_attention_Pipeline_VITIS_LOOP_373_3_VITIS_LOOP_375_4",
		"Protocol" : "ap_ctrl_hs",
		"ControlExist" : "1", "ap_start" : "1", "ap_ready" : "1", "ap_done" : "1", "ap_continue" : "0", "ap_idle" : "1", "real_start" : "0",
		"Pipeline" : "None", "UnalignedPipeline" : "0", "RewindPipeline" : "0", "ProcessNetwork" : "0",
		"II" : "0",
		"VariableLatency" : "1", "ExactLatency" : "-1", "EstimateLatencyMin" : "208", "EstimateLatencyMax" : "208",
		"Combinational" : "0",
		"Datapath" : "0",
		"ClockEnable" : "0",
		"HasSubDataflow" : "0",
		"InDataflowNetwork" : "0",
		"HasNonBlockingOperation" : "0",
		"IsBlackBox" : "0",
		"Port" : [
			{"Name" : "gmem1", "Type" : "MAXI", "Direction" : "O",
				"BlockSignal" : [
					{"Name" : "gmem1_blk_n_W", "Type" : "RtlSignal"}]},
			{"Name" : "gmem0", "Type" : "MAXI", "Direction" : "I",
				"BlockSignal" : [
					{"Name" : "gmem0_blk_n_R", "Type" : "RtlSignal"}]},
			{"Name" : "sext_ln371_1", "Type" : "None", "Direction" : "I"},
			{"Name" : "sext_ln371", "Type" : "None", "Direction" : "I"},
			{"Name" : "empty", "Type" : "None", "Direction" : "I"},
			{"Name" : "tmp", "Type" : "None", "Direction" : "I"},
			{"Name" : "conv32_i", "Type" : "None", "Direction" : "I"},
			{"Name" : "conv36_i", "Type" : "None", "Direction" : "I"}],
		"Loop" : [
			{"Name" : "VITIS_LOOP_373_3_VITIS_LOOP_375_4", "PipelineType" : "UPC",
				"LoopDec" : {"FSMBitwidth" : "1", "FirstState" : "ap_ST_fsm_pp0_stage0", "FirstStateIter" : "ap_enable_reg_pp0_iter0", "FirstStateBlock" : "ap_block_pp0_stage0_subdone", "LastState" : "ap_ST_fsm_pp0_stage0", "LastStateIter" : "ap_enable_reg_pp0_iter11", "LastStateBlock" : "ap_block_pp0_stage0_subdone", "QuitState" : "ap_ST_fsm_pp0_stage0", "QuitStateIter" : "ap_enable_reg_pp0_iter10", "QuitStateBlock" : "ap_block_pp0_stage0_subdone", "OneDepthLoop" : "0", "has_ap_ctrl" : "1", "has_continue" : "0"}}]},
	{"ID" : "2", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_kernel_attention_Pipeline_VITIS_LOOP_373_3_VITIS_LOOP_375_4_fu_525.fsub_32ns_32ns_32_1_full_dsp_1_U1", "Parent" : "1"},
	{"ID" : "3", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_kernel_attention_Pipeline_VITIS_LOOP_373_3_VITIS_LOOP_375_4_fu_525.fptrunc_64ns_32_1_no_dsp_1_U2", "Parent" : "1"},
	{"ID" : "4", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_kernel_attention_Pipeline_VITIS_LOOP_373_3_VITIS_LOOP_375_4_fu_525.fpext_32ns_64_1_no_dsp_1_U3", "Parent" : "1"},
	{"ID" : "5", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_kernel_attention_Pipeline_VITIS_LOOP_373_3_VITIS_LOOP_375_4_fu_525.dadd_64ns_64ns_64_1_full_dsp_1_U4", "Parent" : "1"},
	{"ID" : "6", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_kernel_attention_Pipeline_VITIS_LOOP_373_3_VITIS_LOOP_375_4_fu_525.dmul_64ns_64ns_64_2_max_dsp_1_U5", "Parent" : "1"},
	{"ID" : "7", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_kernel_attention_Pipeline_VITIS_LOOP_373_3_VITIS_LOOP_375_4_fu_525.ddiv_64ns_64ns_64_5_no_dsp_1_U6", "Parent" : "1"},
	{"ID" : "8", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_kernel_attention_Pipeline_VITIS_LOOP_373_3_VITIS_LOOP_375_4_fu_525.flow_control_loop_pipe_sequential_init_U", "Parent" : "1"},
	{"ID" : "9", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.grp_kernel_attention_Pipeline_VITIS_LOOP_17_2_VITIS_LOOP_18_3_VITIS_LOOP_19_4_fu_539", "Parent" : "0", "Child" : ["10"],
		"CDFG" : "kernel_attention_Pipeline_VITIS_LOOP_17_2_VITIS_LOOP_18_3_VITIS_LOOP_19_4",
		"Protocol" : "ap_ctrl_hs",
		"ControlExist" : "1", "ap_start" : "1", "ap_ready" : "1", "ap_done" : "1", "ap_continue" : "0", "ap_idle" : "1", "real_start" : "0",
		"Pipeline" : "None", "UnalignedPipeline" : "0", "RewindPipeline" : "0", "ProcessNetwork" : "0",
		"II" : "0",
		"VariableLatency" : "1", "ExactLatency" : "-1", "EstimateLatencyMin" : "15683", "EstimateLatencyMax" : "15683",
		"Combinational" : "0",
		"Datapath" : "0",
		"ClockEnable" : "0",
		"HasSubDataflow" : "0",
		"InDataflowNetwork" : "0",
		"HasNonBlockingOperation" : "0",
		"IsBlackBox" : "0",
		"Port" : [
			{"Name" : "gmem", "Type" : "MAXI", "Direction" : "O",
				"BlockSignal" : [
					{"Name" : "gmem_blk_n_W", "Type" : "RtlSignal"}]},
			{"Name" : "gmem1", "Type" : "MAXI", "Direction" : "I",
				"BlockSignal" : [
					{"Name" : "gmem1_blk_n_R", "Type" : "RtlSignal"}]},
			{"Name" : "sext_ln17", "Type" : "None", "Direction" : "I"},
			{"Name" : "sext_ln371_1", "Type" : "None", "Direction" : "I"}],
		"Loop" : [
			{"Name" : "VITIS_LOOP_17_2_VITIS_LOOP_18_3_VITIS_LOOP_19_4", "PipelineType" : "UPC",
				"LoopDec" : {"FSMBitwidth" : "1", "FirstState" : "ap_ST_fsm_pp0_stage0", "FirstStateIter" : "ap_enable_reg_pp0_iter0", "FirstStateBlock" : "ap_block_pp0_stage0_subdone", "LastState" : "ap_ST_fsm_pp0_stage0", "LastStateIter" : "ap_enable_reg_pp0_iter2", "LastStateBlock" : "ap_block_pp0_stage0_subdone", "QuitState" : "ap_ST_fsm_pp0_stage0", "QuitStateIter" : "ap_enable_reg_pp0_iter1", "QuitStateBlock" : "ap_block_pp0_stage0_subdone", "OneDepthLoop" : "0", "has_ap_ctrl" : "1", "has_continue" : "0"}}]},
	{"ID" : "10", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_kernel_attention_Pipeline_VITIS_LOOP_17_2_VITIS_LOOP_18_3_VITIS_LOOP_19_4_fu_539.flow_control_loop_pipe_sequential_init_U", "Parent" : "9"},
	{"ID" : "11", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.grp_kernel_attention_Pipeline_VITIS_LOOP_80_2_VITIS_LOOP_82_3_fu_549", "Parent" : "0", "Child" : ["12", "13", "14"],
		"CDFG" : "kernel_attention_Pipeline_VITIS_LOOP_80_2_VITIS_LOOP_82_3",
		"Protocol" : "ap_ctrl_hs",
		"ControlExist" : "1", "ap_start" : "1", "ap_ready" : "1", "ap_done" : "1", "ap_continue" : "0", "ap_idle" : "1", "real_start" : "0",
		"Pipeline" : "None", "UnalignedPipeline" : "0", "RewindPipeline" : "0", "ProcessNetwork" : "0",
		"II" : "0",
		"VariableLatency" : "1", "ExactLatency" : "-1", "EstimateLatencyMin" : "15698", "EstimateLatencyMax" : "15698",
		"Combinational" : "0",
		"Datapath" : "0",
		"ClockEnable" : "0",
		"HasSubDataflow" : "0",
		"InDataflowNetwork" : "0",
		"HasNonBlockingOperation" : "0",
		"IsBlackBox" : "0",
		"Port" : [
			{"Name" : "gmem", "Type" : "MAXI", "Direction" : "IO",
				"BlockSignal" : [
					{"Name" : "gmem_blk_n_AR", "Type" : "RtlSignal"},
					{"Name" : "gmem_blk_n_R", "Type" : "RtlSignal"},
					{"Name" : "gmem_blk_n_AW", "Type" : "RtlSignal"},
					{"Name" : "gmem_blk_n_W", "Type" : "RtlSignal"},
					{"Name" : "gmem_blk_n_B", "Type" : "RtlSignal"}]},
			{"Name" : "afterPad", "Type" : "None", "Direction" : "I"},
			{"Name" : "afterRearrangeX", "Type" : "None", "Direction" : "I"}],
		"Loop" : [
			{"Name" : "VITIS_LOOP_80_2_VITIS_LOOP_82_3", "PipelineType" : "UPC",
				"LoopDec" : {"FSMBitwidth" : "28", "FirstState" : "ap_ST_fsm_pp0_stage0", "FirstStateIter" : "ap_enable_reg_pp0_iter0", "FirstStateBlock" : "ap_block_pp0_stage0_subdone", "LastState" : "ap_ST_fsm_pp0_stage16", "LastStateIter" : "ap_enable_reg_pp0_iter1", "LastStateBlock" : "ap_block_pp0_stage16_subdone", "QuitState" : "ap_ST_fsm_pp0_stage16", "QuitStateIter" : "ap_enable_reg_pp0_iter1", "QuitStateBlock" : "ap_block_pp0_stage16_subdone", "OneDepthLoop" : "0", "has_ap_ctrl" : "1", "has_continue" : "0"}}]},
	{"ID" : "12", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_kernel_attention_Pipeline_VITIS_LOOP_80_2_VITIS_LOOP_82_3_fu_549.mac_muladd_7ns_8ns_9s_15_4_1_U25", "Parent" : "11"},
	{"ID" : "13", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_kernel_attention_Pipeline_VITIS_LOOP_80_2_VITIS_LOOP_82_3_fu_549.mac_muladd_7ns_6ns_7s_13_4_1_U26", "Parent" : "11"},
	{"ID" : "14", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_kernel_attention_Pipeline_VITIS_LOOP_80_2_VITIS_LOOP_82_3_fu_549.flow_control_loop_pipe_sequential_init_U", "Parent" : "11"},
	{"ID" : "15", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.grp_DW_conv_fu_557", "Parent" : "0", "Child" : ["16", "21", "22", "23", "24"],
		"CDFG" : "DW_conv",
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
			{"Name" : "gmem", "Type" : "MAXI", "Direction" : "IO",
				"BlockSignal" : [
					{"Name" : "gmem_blk_n_AR", "Type" : "RtlSignal"},
					{"Name" : "gmem_blk_n_R", "Type" : "RtlSignal"},
					{"Name" : "gmem_blk_n_AW", "Type" : "RtlSignal"},
					{"Name" : "gmem_blk_n_W", "Type" : "RtlSignal"},
					{"Name" : "gmem_blk_n_B", "Type" : "RtlSignal"}],
				"SubConnect" : [
					{"ID" : "16", "SubInstance" : "grp_DW_conv_Pipeline_In_Channel_fu_316", "Port" : "gmem", "Inst_start_state" : "14", "Inst_end_state" : "15"}]},
			{"Name" : "in_r", "Type" : "None", "Direction" : "I"},
			{"Name" : "kernel", "Type" : "None", "Direction" : "I"},
			{"Name" : "bias", "Type" : "None", "Direction" : "I"},
			{"Name" : "p_read4", "Type" : "None", "Direction" : "I"},
			{"Name" : "out_r", "Type" : "None", "Direction" : "I"}],
		"Loop" : [
			{"Name" : "Batch_Out_Column_Kernel_Col_Output_Channel", "PipelineType" : "no",
				"LoopDec" : {"FSMBitwidth" : "54", "FirstState" : "ap_ST_fsm_state2", "LastState" : ["ap_ST_fsm_state54"], "QuitState" : ["ap_ST_fsm_state2"], "PreState" : ["ap_ST_fsm_state1"], "PostState" : ["ap_ST_fsm_state1"], "OneDepthLoop" : "0", "OneStateBlock": ""}}]},
	{"ID" : "16", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_DW_conv_fu_557.grp_DW_conv_Pipeline_In_Channel_fu_316", "Parent" : "15", "Child" : ["17", "18", "19", "20"],
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
	{"ID" : "17", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_DW_conv_fu_557.grp_DW_conv_Pipeline_In_Channel_fu_316.fadd_32ns_32ns_32_1_full_dsp_1_U32", "Parent" : "16"},
	{"ID" : "18", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_DW_conv_fu_557.grp_DW_conv_Pipeline_In_Channel_fu_316.fmul_32ns_32ns_32_1_max_dsp_1_U33", "Parent" : "16"},
	{"ID" : "19", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_DW_conv_fu_557.grp_DW_conv_Pipeline_In_Channel_fu_316.mul_62s_7ns_62_1_1_U34", "Parent" : "16"},
	{"ID" : "20", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_DW_conv_fu_557.grp_DW_conv_Pipeline_In_Channel_fu_316.srem_32ns_8ns_8_36_1_U35", "Parent" : "16"},
	{"ID" : "21", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_DW_conv_fu_557.fadd_32ns_32ns_32_1_full_dsp_1_U52", "Parent" : "15"},
	{"ID" : "22", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_DW_conv_fu_557.mul_2ns_13ns_14_1_1_U53", "Parent" : "15"},
	{"ID" : "23", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_DW_conv_fu_557.urem_8ns_8ns_8_12_seq_1_U54", "Parent" : "15"},
	{"ID" : "24", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_DW_conv_fu_557.mac_muladd_3ns_8ns_8ns_10_4_1_U55", "Parent" : "15"},
	{"ID" : "25", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.grp_compute_skip_fu_570", "Parent" : "0", "Child" : ["26", "30"],
		"CDFG" : "compute_skip",
		"Protocol" : "ap_ctrl_hs",
		"ControlExist" : "1", "ap_start" : "1", "ap_ready" : "1", "ap_done" : "1", "ap_continue" : "0", "ap_idle" : "1", "real_start" : "0",
		"Pipeline" : "None", "UnalignedPipeline" : "0", "RewindPipeline" : "0", "ProcessNetwork" : "0",
		"II" : "0",
		"VariableLatency" : "1", "ExactLatency" : "-1", "EstimateLatencyMin" : "439045", "EstimateLatencyMax" : "658565",
		"Combinational" : "0",
		"Datapath" : "0",
		"ClockEnable" : "0",
		"HasSubDataflow" : "0",
		"InDataflowNetwork" : "0",
		"HasNonBlockingOperation" : "0",
		"IsBlackBox" : "0",
		"Port" : [
			{"Name" : "gmem", "Type" : "MAXI", "Direction" : "IO",
				"SubConnect" : [
					{"ID" : "26", "SubInstance" : "grp_compute_skip_Pipeline_VITIS_LOOP_584_3_fu_56", "Port" : "gmem", "Inst_start_state" : "2", "Inst_end_state" : "3"}]},
			{"Name" : "afterAct", "Type" : "None", "Direction" : "I"},
			{"Name" : "buffer_result", "Type" : "None", "Direction" : "I"},
			{"Name" : "p_read1", "Type" : "None", "Direction" : "I"}]},
	{"ID" : "26", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_compute_skip_fu_570.grp_compute_skip_Pipeline_VITIS_LOOP_584_3_fu_56", "Parent" : "25", "Child" : ["27", "28", "29"],
		"CDFG" : "compute_skip_Pipeline_VITIS_LOOP_584_3",
		"Protocol" : "ap_ctrl_hs",
		"ControlExist" : "1", "ap_start" : "1", "ap_ready" : "1", "ap_done" : "1", "ap_continue" : "0", "ap_idle" : "1", "real_start" : "0",
		"Pipeline" : "None", "UnalignedPipeline" : "0", "RewindPipeline" : "0", "ProcessNetwork" : "0",
		"II" : "0",
		"VariableLatency" : "1", "ExactLatency" : "-1", "EstimateLatencyMin" : "439043", "EstimateLatencyMax" : "658563",
		"Combinational" : "0",
		"Datapath" : "0",
		"ClockEnable" : "0",
		"HasSubDataflow" : "0",
		"InDataflowNetwork" : "0",
		"HasNonBlockingOperation" : "0",
		"IsBlackBox" : "0",
		"Port" : [
			{"Name" : "zext_ln580", "Type" : "None", "Direction" : "I"},
			{"Name" : "bound66", "Type" : "None", "Direction" : "I"},
			{"Name" : "gmem", "Type" : "MAXI", "Direction" : "IO",
				"BlockSignal" : [
					{"Name" : "gmem_blk_n_R", "Type" : "RtlSignal"},
					{"Name" : "gmem_blk_n_B", "Type" : "RtlSignal"},
					{"Name" : "gmem_blk_n_W", "Type" : "RtlSignal"},
					{"Name" : "gmem_blk_n_AR", "Type" : "RtlSignal"},
					{"Name" : "gmem_blk_n_AW", "Type" : "RtlSignal"}]},
			{"Name" : "bound21", "Type" : "None", "Direction" : "I"},
			{"Name" : "afterAct", "Type" : "None", "Direction" : "I"},
			{"Name" : "buffer_result", "Type" : "None", "Direction" : "I"}],
		"Loop" : [
			{"Name" : "Skip_VITIS_LOOP_582_2_VITIS_LOOP_584_3", "PipelineType" : "UPC",
				"LoopDec" : {"FSMBitwidth" : "14", "FirstState" : "ap_ST_fsm_pp0_stage1", "FirstStateIter" : "ap_enable_reg_pp0_iter0", "FirstStateBlock" : "ap_block_pp0_stage1_subdone", "LastState" : "ap_ST_fsm_pp0_stage2", "LastStateIter" : "ap_enable_reg_pp0_iter1", "LastStateBlock" : "ap_block_pp0_stage2_subdone", "QuitState" : "ap_ST_fsm_pp0_stage2", "QuitStateIter" : "ap_enable_reg_pp0_iter0", "QuitStateBlock" : "ap_block_pp0_stage2_subdone", "OneDepthLoop" : "0", "has_ap_ctrl" : "1", "has_continue" : "0"}}]},
	{"ID" : "27", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_compute_skip_fu_570.grp_compute_skip_Pipeline_VITIS_LOOP_584_3_fu_56.mul_3ns_8ns_10_1_1_U65", "Parent" : "26"},
	{"ID" : "28", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_compute_skip_fu_570.grp_compute_skip_Pipeline_VITIS_LOOP_584_3_fu_56.mul_3ns_8ns_10_1_1_U66", "Parent" : "26"},
	{"ID" : "29", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_compute_skip_fu_570.grp_compute_skip_Pipeline_VITIS_LOOP_584_3_fu_56.flow_control_loop_pipe_sequential_init_U", "Parent" : "26"},
	{"ID" : "30", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_compute_skip_fu_570.mul_8ns_7ns_14_1_1_U74", "Parent" : "25"},
	{"ID" : "31", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.grp_get_qk_fu_581", "Parent" : "0", "Child" : ["32", "33", "34", "35", "36", "37", "38", "39", "40", "41", "42"],
		"CDFG" : "get_qk",
		"Protocol" : "ap_ctrl_hs",
		"ControlExist" : "1", "ap_start" : "1", "ap_ready" : "1", "ap_done" : "1", "ap_continue" : "0", "ap_idle" : "1", "real_start" : "0",
		"Pipeline" : "None", "UnalignedPipeline" : "0", "RewindPipeline" : "0", "ProcessNetwork" : "0",
		"II" : "0",
		"VariableLatency" : "1", "ExactLatency" : "-1", "EstimateLatencyMin" : "31378", "EstimateLatencyMax" : "31378",
		"Combinational" : "0",
		"Datapath" : "0",
		"ClockEnable" : "0",
		"HasSubDataflow" : "0",
		"InDataflowNetwork" : "0",
		"HasNonBlockingOperation" : "0",
		"IsBlackBox" : "0",
		"Port" : [
			{"Name" : "gmem", "Type" : "MAXI", "Direction" : "IO",
				"BlockSignal" : [
					{"Name" : "gmem_blk_n_AR", "Type" : "RtlSignal"},
					{"Name" : "gmem_blk_n_R", "Type" : "RtlSignal"},
					{"Name" : "gmem_blk_n_AW", "Type" : "RtlSignal"},
					{"Name" : "gmem_blk_n_W", "Type" : "RtlSignal"},
					{"Name" : "gmem_blk_n_B", "Type" : "RtlSignal"}]},
			{"Name" : "in_qk", "Type" : "None", "Direction" : "I"},
			{"Name" : "in_q", "Type" : "None", "Direction" : "I"},
			{"Name" : "in_k", "Type" : "None", "Direction" : "I"}],
		"Loop" : [
			{"Name" : "init_in_VITIS_LOOP_41_2_VITIS_LOOP_45_4_VITIS_LOOP_47_5", "PipelineType" : "UPC",
				"LoopDec" : {"FSMBitwidth" : "1", "FirstState" : "ap_ST_fsm_pp0_stage0", "FirstStateIter" : "ap_enable_reg_pp0_iter1", "FirstStateBlock" : "ap_block_pp0_stage0_subdone", "LastState" : "ap_ST_fsm_pp0_stage0", "LastStateIter" : "ap_enable_reg_pp0_iter18", "LastStateBlock" : "ap_block_pp0_stage0_subdone", "QuitState" : "ap_ST_fsm_pp0_stage0", "QuitStateIter" : "ap_enable_reg_pp0_iter18", "QuitStateBlock" : "ap_block_pp0_stage0_subdone", "OneDepthLoop" : "0", "has_ap_ctrl" : "1", "has_continue" : "0"}}]},
	{"ID" : "32", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_get_qk_fu_581.mul_2ns_13ns_14_1_1_U80", "Parent" : "31"},
	{"ID" : "33", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_get_qk_fu_581.mul_2ns_13ns_14_1_1_U81", "Parent" : "31"},
	{"ID" : "34", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_get_qk_fu_581.mul_3ns_13ns_14_1_1_U82", "Parent" : "31"},
	{"ID" : "35", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_get_qk_fu_581.mul_3ns_13ns_14_1_1_U83", "Parent" : "31"},
	{"ID" : "36", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_get_qk_fu_581.mac_muladd_3ns_13ns_14ns_15_4_1_U84", "Parent" : "31"},
	{"ID" : "37", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_get_qk_fu_581.mac_muladd_3ns_13ns_14ns_15_4_1_U85", "Parent" : "31"},
	{"ID" : "38", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_get_qk_fu_581.mac_muladd_3ns_10ns_14ns_14_4_1_U86", "Parent" : "31"},
	{"ID" : "39", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_get_qk_fu_581.mac_muladd_3ns_10ns_14ns_14_4_1_U87", "Parent" : "31"},
	{"ID" : "40", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_get_qk_fu_581.mac_muladd_5ns_6ns_14ns_14_4_1_U88", "Parent" : "31"},
	{"ID" : "41", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_get_qk_fu_581.mac_muladd_5ns_6ns_14ns_14_4_1_U89", "Parent" : "31"},
	{"ID" : "42", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_get_qk_fu_581.flow_control_loop_pipe_sequential_init_U", "Parent" : "31"},
	{"ID" : "43", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.grp_compute_multiplication_fu_590", "Parent" : "0", "Child" : ["44", "49", "50", "51", "52"],
		"CDFG" : "compute_multiplication",
		"Protocol" : "ap_ctrl_hs",
		"ControlExist" : "1", "ap_start" : "1", "ap_ready" : "1", "ap_done" : "1", "ap_continue" : "0", "ap_idle" : "1", "real_start" : "0",
		"Pipeline" : "None", "UnalignedPipeline" : "0", "RewindPipeline" : "0", "ProcessNetwork" : "0",
		"II" : "0",
		"VariableLatency" : "1", "ExactLatency" : "-1", "EstimateLatencyMin" : "904737", "EstimateLatencyMax" : "4428817",
		"Combinational" : "0",
		"Datapath" : "0",
		"ClockEnable" : "0",
		"HasSubDataflow" : "0",
		"InDataflowNetwork" : "0",
		"HasNonBlockingOperation" : "0",
		"IsBlackBox" : "0",
		"Port" : [
			{"Name" : "gmem", "Type" : "MAXI", "Direction" : "IO",
				"BlockSignal" : [
					{"Name" : "gmem_blk_n_W", "Type" : "RtlSignal"},
					{"Name" : "gmem_blk_n_B", "Type" : "RtlSignal"},
					{"Name" : "gmem_blk_n_AW", "Type" : "RtlSignal"}],
				"SubConnect" : [
					{"ID" : "44", "SubInstance" : "grp_compute_multiplication_Pipeline_VITIS_LOOP_207_4_fu_197", "Port" : "gmem", "Inst_start_state" : "10", "Inst_end_state" : "11"}]},
			{"Name" : "in_q", "Type" : "None", "Direction" : "I"},
			{"Name" : "in_k", "Type" : "None", "Direction" : "I"},
			{"Name" : "afterQKMultiplication", "Type" : "None", "Direction" : "I"},
			{"Name" : "p_read3", "Type" : "None", "Direction" : "I"},
			{"Name" : "p_read4", "Type" : "None", "Direction" : "I"},
			{"Name" : "scale", "Type" : "None", "Direction" : "I"}],
		"Loop" : [
			{"Name" : "VITIS_LOOP_206_3", "PipelineType" : "no",
				"LoopDec" : {"FSMBitwidth" : "17", "FirstState" : "ap_ST_fsm_state10", "LastState" : ["ap_ST_fsm_state12"], "QuitState" : ["ap_ST_fsm_state10"], "PreState" : ["ap_ST_fsm_state9"], "PostState" : ["ap_ST_fsm_state13"], "OneDepthLoop" : "0", "OneStateBlock": ""}},
			{"Name" : "execute_VITIS_LOOP_204_1_VITIS_LOOP_205_2", "PipelineType" : "no",
				"LoopDec" : {"FSMBitwidth" : "17", "FirstState" : "ap_ST_fsm_state2", "LastState" : ["ap_ST_fsm_state17"], "QuitState" : ["ap_ST_fsm_state2"], "PreState" : ["ap_ST_fsm_state1"], "PostState" : ["ap_ST_fsm_state1"], "OneDepthLoop" : "0", "OneStateBlock": ""}}]},
	{"ID" : "44", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_compute_multiplication_fu_590.grp_compute_multiplication_Pipeline_VITIS_LOOP_207_4_fu_197", "Parent" : "43", "Child" : ["45", "46", "47", "48"],
		"CDFG" : "compute_multiplication_Pipeline_VITIS_LOOP_207_4",
		"Protocol" : "ap_ctrl_hs",
		"ControlExist" : "1", "ap_start" : "1", "ap_ready" : "1", "ap_done" : "1", "ap_continue" : "0", "ap_idle" : "1", "real_start" : "0",
		"Pipeline" : "None", "UnalignedPipeline" : "0", "RewindPipeline" : "0", "ProcessNetwork" : "0",
		"II" : "0",
		"VariableLatency" : "1", "ExactLatency" : "-1", "EstimateLatencyMin" : "54", "EstimateLatencyMax" : "112",
		"Combinational" : "0",
		"Datapath" : "0",
		"ClockEnable" : "0",
		"HasSubDataflow" : "0",
		"InDataflowNetwork" : "0",
		"HasNonBlockingOperation" : "0",
		"IsBlackBox" : "0",
		"Port" : [
			{"Name" : "p_read3", "Type" : "None", "Direction" : "I"},
			{"Name" : "sext_ln206_1", "Type" : "None", "Direction" : "I"},
			{"Name" : "gmem", "Type" : "MAXI", "Direction" : "I",
				"BlockSignal" : [
					{"Name" : "gmem_blk_n_AR", "Type" : "RtlSignal"},
					{"Name" : "gmem_blk_n_R", "Type" : "RtlSignal"}]},
			{"Name" : "mul_ln204", "Type" : "None", "Direction" : "I"},
			{"Name" : "zext_ln203", "Type" : "None", "Direction" : "I"},
			{"Name" : "zext_ln206", "Type" : "None", "Direction" : "I"},
			{"Name" : "in_k", "Type" : "None", "Direction" : "I"},
			{"Name" : "scale", "Type" : "None", "Direction" : "I"},
			{"Name" : "sum_out", "Type" : "Vld", "Direction" : "O"}],
		"Loop" : [
			{"Name" : "VITIS_LOOP_207_4", "PipelineType" : "UPC",
				"LoopDec" : {"FSMBitwidth" : "2", "FirstState" : "ap_ST_fsm_pp0_stage0", "FirstStateIter" : "ap_enable_reg_pp0_iter0", "FirstStateBlock" : "ap_block_pp0_stage0_subdone", "LastState" : "ap_ST_fsm_pp0_stage0", "LastStateIter" : "ap_enable_reg_pp0_iter7", "LastStateBlock" : "ap_block_pp0_stage0_subdone", "QuitState" : "ap_ST_fsm_pp0_stage0", "QuitStateIter" : "ap_enable_reg_pp0_iter7", "QuitStateBlock" : "ap_block_pp0_stage0_subdone", "OneDepthLoop" : "0", "has_ap_ctrl" : "1", "has_continue" : "0"}}]},
	{"ID" : "45", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_compute_multiplication_fu_590.grp_compute_multiplication_Pipeline_VITIS_LOOP_207_4_fu_197.fadd_32ns_32ns_32_1_full_dsp_1_U98", "Parent" : "44"},
	{"ID" : "46", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_compute_multiplication_fu_590.grp_compute_multiplication_Pipeline_VITIS_LOOP_207_4_fu_197.fmul_32ns_32ns_32_1_max_dsp_1_U99", "Parent" : "44"},
	{"ID" : "47", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_compute_multiplication_fu_590.grp_compute_multiplication_Pipeline_VITIS_LOOP_207_4_fu_197.ama_addmuladd_6ns_10ns_6ns_6ns_16_4_1_U100", "Parent" : "44"},
	{"ID" : "48", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_compute_multiplication_fu_590.grp_compute_multiplication_Pipeline_VITIS_LOOP_207_4_fu_197.flow_control_loop_pipe_sequential_init_U", "Parent" : "44"},
	{"ID" : "49", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_compute_multiplication_fu_590.mul_4ns_6ns_10_1_1_U111", "Parent" : "43"},
	{"ID" : "50", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_compute_multiplication_fu_590.mac_muladd_4ns_6ns_6ns_10_4_1_U112", "Parent" : "43"},
	{"ID" : "51", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_compute_multiplication_fu_590.mul_mul_10ns_6ns_16_4_1_U113", "Parent" : "43"},
	{"ID" : "52", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_compute_multiplication_fu_590.mul_mul_10ns_6ns_16_4_1_U114", "Parent" : "43"},
	{"ID" : "53", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.grp_kernel_attention_Pipeline_VITIS_LOOP_230_1_VITIS_LOOP_232_3_count_sum_fu_608", "Parent" : "0", "Child" : ["54", "64", "65", "66", "67", "68", "69", "70", "71", "72", "73", "74", "75", "76"],
		"CDFG" : "kernel_attention_Pipeline_VITIS_LOOP_230_1_VITIS_LOOP_232_3_count_sum",
		"Protocol" : "ap_ctrl_hs",
		"ControlExist" : "1", "ap_start" : "1", "ap_ready" : "1", "ap_done" : "1", "ap_continue" : "0", "ap_idle" : "1", "real_start" : "0",
		"Pipeline" : "None", "UnalignedPipeline" : "0", "RewindPipeline" : "0", "ProcessNetwork" : "0",
		"II" : "0",
		"VariableLatency" : "1", "ExactLatency" : "-1", "EstimateLatencyMin" : "1920921", "EstimateLatencyMax" : "1920921",
		"Combinational" : "0",
		"Datapath" : "0",
		"ClockEnable" : "0",
		"HasSubDataflow" : "0",
		"InDataflowNetwork" : "0",
		"HasNonBlockingOperation" : "0",
		"IsBlackBox" : "0",
		"Port" : [
			{"Name" : "gmem", "Type" : "MAXI", "Direction" : "IO",
				"BlockSignal" : [
					{"Name" : "gmem_blk_n_W", "Type" : "RtlSignal"},
					{"Name" : "gmem_blk_n_AR", "Type" : "RtlSignal"},
					{"Name" : "gmem_blk_n_R", "Type" : "RtlSignal"}]},
			{"Name" : "sext_ln230_1", "Type" : "None", "Direction" : "I"},
			{"Name" : "afterQKMultiplication", "Type" : "None", "Direction" : "I"},
			{"Name" : "sext_ln230", "Type" : "None", "Direction" : "I"},
			{"Name" : "pow_reduce_anonymous_namespace_table_exp_Z1_ap_ufixed_array_V", "Type" : "Memory", "Direction" : "I",
				"SubConnect" : [
					{"ID" : "54", "SubInstance" : "grp_pow_generic_double_s_fu_868", "Port" : "pow_reduce_anonymous_namespace_table_exp_Z1_ap_ufixed_array_V", "Inst_start_state" : "64", "Inst_end_state" : "68"}]},
			{"Name" : "pow_reduce_anonymous_namespace_table_f_Z3_ap_ufixed_array_V", "Type" : "Memory", "Direction" : "I",
				"SubConnect" : [
					{"ID" : "54", "SubInstance" : "grp_pow_generic_double_s_fu_868", "Port" : "pow_reduce_anonymous_namespace_table_f_Z3_ap_ufixed_array_V", "Inst_start_state" : "64", "Inst_end_state" : "68"}]},
			{"Name" : "pow_reduce_anonymous_namespace_table_f_Z2_ap_ufixed_array_V", "Type" : "Memory", "Direction" : "I",
				"SubConnect" : [
					{"ID" : "54", "SubInstance" : "grp_pow_generic_double_s_fu_868", "Port" : "pow_reduce_anonymous_namespace_table_f_Z2_ap_ufixed_array_V", "Inst_start_state" : "64", "Inst_end_state" : "68"}]}],
		"Loop" : [
			{"Name" : "VITIS_LOOP_230_1_VITIS_LOOP_232_3_count_sum", "PipelineType" : "UPC",
				"LoopDec" : {"FSMBitwidth" : "50", "FirstState" : "ap_ST_fsm_pp0_stage0", "FirstStateIter" : "ap_enable_reg_pp0_iter0", "FirstStateBlock" : "ap_block_pp0_stage0_subdone", "LastState" : "ap_ST_fsm_pp0_stage20", "LastStateIter" : "ap_enable_reg_pp0_iter2", "LastStateBlock" : "ap_block_pp0_stage20_subdone", "QuitState" : "ap_ST_fsm_pp0_stage19", "QuitStateIter" : "ap_enable_reg_pp0_iter2", "QuitStateBlock" : "ap_block_pp0_stage19_subdone", "OneDepthLoop" : "0", "has_ap_ctrl" : "1", "has_continue" : "0"}}]},
	{"ID" : "54", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_kernel_attention_Pipeline_VITIS_LOOP_230_1_VITIS_LOOP_232_3_count_sum_fu_608.grp_pow_generic_double_s_fu_868", "Parent" : "53", "Child" : ["55", "56", "57", "58", "59", "60", "61", "62", "63"],
		"CDFG" : "pow_generic_double_s",
		"Protocol" : "ap_ctrl_hs",
		"ControlExist" : "1", "ap_start" : "1", "ap_ready" : "1", "ap_done" : "1", "ap_continue" : "0", "ap_idle" : "1", "real_start" : "0",
		"Pipeline" : "Aligned", "UnalignedPipeline" : "0", "RewindPipeline" : "0", "ProcessNetwork" : "0",
		"II" : "1",
		"VariableLatency" : "0", "ExactLatency" : "4", "EstimateLatencyMin" : "4", "EstimateLatencyMax" : "4",
		"Combinational" : "0",
		"Datapath" : "0",
		"ClockEnable" : "1",
		"HasSubDataflow" : "0",
		"InDataflowNetwork" : "0",
		"HasNonBlockingOperation" : "0",
		"IsBlackBox" : "0",
		"Port" : [
			{"Name" : "exp", "Type" : "None", "Direction" : "I"},
			{"Name" : "pow_reduce_anonymous_namespace_table_exp_Z1_ap_ufixed_array_V", "Type" : "Memory", "Direction" : "I"},
			{"Name" : "pow_reduce_anonymous_namespace_table_f_Z3_ap_ufixed_array_V", "Type" : "Memory", "Direction" : "I"},
			{"Name" : "pow_reduce_anonymous_namespace_table_f_Z2_ap_ufixed_array_V", "Type" : "Memory", "Direction" : "I"}]},
	{"ID" : "55", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_kernel_attention_Pipeline_VITIS_LOOP_230_1_VITIS_LOOP_232_3_count_sum_fu_608.grp_pow_generic_double_s_fu_868.pow_reduce_anonymous_namespace_table_exp_Z1_ap_ufixed_array_V_U", "Parent" : "54"},
	{"ID" : "56", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_kernel_attention_Pipeline_VITIS_LOOP_230_1_VITIS_LOOP_232_3_count_sum_fu_608.grp_pow_generic_double_s_fu_868.pow_reduce_anonymous_namespace_table_f_Z3_ap_ufixed_array_V_U", "Parent" : "54"},
	{"ID" : "57", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_kernel_attention_Pipeline_VITIS_LOOP_230_1_VITIS_LOOP_232_3_count_sum_fu_608.grp_pow_generic_double_s_fu_868.pow_reduce_anonymous_namespace_table_f_Z2_ap_ufixed_array_V_U", "Parent" : "54"},
	{"ID" : "58", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_kernel_attention_Pipeline_VITIS_LOOP_230_1_VITIS_LOOP_232_3_count_sum_fu_608.grp_pow_generic_double_s_fu_868.mul_54s_67ns_120_1_1_U125", "Parent" : "54"},
	{"ID" : "59", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_kernel_attention_Pipeline_VITIS_LOOP_230_1_VITIS_LOOP_232_3_count_sum_fu_608.grp_pow_generic_double_s_fu_868.mul_13s_71s_71_1_1_U126", "Parent" : "54"},
	{"ID" : "60", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_kernel_attention_Pipeline_VITIS_LOOP_230_1_VITIS_LOOP_232_3_count_sum_fu_608.grp_pow_generic_double_s_fu_868.mul_43ns_36ns_79_1_1_U127", "Parent" : "54"},
	{"ID" : "61", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_kernel_attention_Pipeline_VITIS_LOOP_230_1_VITIS_LOOP_232_3_count_sum_fu_608.grp_pow_generic_double_s_fu_868.mul_49ns_44ns_93_1_1_U128", "Parent" : "54"},
	{"ID" : "62", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_kernel_attention_Pipeline_VITIS_LOOP_230_1_VITIS_LOOP_232_3_count_sum_fu_608.grp_pow_generic_double_s_fu_868.mul_50ns_50ns_100_1_1_U129", "Parent" : "54"},
	{"ID" : "63", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_kernel_attention_Pipeline_VITIS_LOOP_230_1_VITIS_LOOP_232_3_count_sum_fu_608.grp_pow_generic_double_s_fu_868.mac_muladd_16s_15ns_19s_31_4_1_U130", "Parent" : "54"},
	{"ID" : "64", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_kernel_attention_Pipeline_VITIS_LOOP_230_1_VITIS_LOOP_232_3_count_sum_fu_608.fsub_32ns_32ns_32_1_full_dsp_1_U141", "Parent" : "53"},
	{"ID" : "65", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_kernel_attention_Pipeline_VITIS_LOOP_230_1_VITIS_LOOP_232_3_count_sum_fu_608.fdiv_32ns_32ns_32_2_no_dsp_1_U142", "Parent" : "53"},
	{"ID" : "66", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_kernel_attention_Pipeline_VITIS_LOOP_230_1_VITIS_LOOP_232_3_count_sum_fu_608.fptrunc_64ns_32_1_no_dsp_1_U143", "Parent" : "53"},
	{"ID" : "67", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_kernel_attention_Pipeline_VITIS_LOOP_230_1_VITIS_LOOP_232_3_count_sum_fu_608.fpext_32ns_64_1_no_dsp_1_U144", "Parent" : "53"},
	{"ID" : "68", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_kernel_attention_Pipeline_VITIS_LOOP_230_1_VITIS_LOOP_232_3_count_sum_fu_608.fpext_32ns_64_1_no_dsp_1_U145", "Parent" : "53"},
	{"ID" : "69", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_kernel_attention_Pipeline_VITIS_LOOP_230_1_VITIS_LOOP_232_3_count_sum_fu_608.dadd_64ns_64ns_64_1_full_dsp_1_U146", "Parent" : "53"},
	{"ID" : "70", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_kernel_attention_Pipeline_VITIS_LOOP_230_1_VITIS_LOOP_232_3_count_sum_fu_608.mul_3ns_15ns_15_1_1_U147", "Parent" : "53"},
	{"ID" : "71", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_kernel_attention_Pipeline_VITIS_LOOP_230_1_VITIS_LOOP_232_3_count_sum_fu_608.mul_3ns_15ns_15_1_1_U148", "Parent" : "53"},
	{"ID" : "72", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_kernel_attention_Pipeline_VITIS_LOOP_230_1_VITIS_LOOP_232_3_count_sum_fu_608.mul_3ns_13ns_15_1_1_U149", "Parent" : "53"},
	{"ID" : "73", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_kernel_attention_Pipeline_VITIS_LOOP_230_1_VITIS_LOOP_232_3_count_sum_fu_608.mul_3ns_13ns_15_1_1_U150", "Parent" : "53"},
	{"ID" : "74", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_kernel_attention_Pipeline_VITIS_LOOP_230_1_VITIS_LOOP_232_3_count_sum_fu_608.mac_muladd_6ns_6ns_15ns_15_4_1_U151", "Parent" : "53"},
	{"ID" : "75", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_kernel_attention_Pipeline_VITIS_LOOP_230_1_VITIS_LOOP_232_3_count_sum_fu_608.mac_muladd_6ns_6ns_15ns_15_4_1_U152", "Parent" : "53"},
	{"ID" : "76", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_kernel_attention_Pipeline_VITIS_LOOP_230_1_VITIS_LOOP_232_3_count_sum_fu_608.flow_control_loop_pipe_sequential_init_U", "Parent" : "53"},
	{"ID" : "77", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.grp_kernel_attention_Pipeline_VITIS_LOOP_110_1_VITIS_LOOP_114_3_VITIS_LOOP_116_4_VIT_fu_623", "Parent" : "0", "Child" : ["78", "79", "80", "81", "82"],
		"CDFG" : "kernel_attention_Pipeline_VITIS_LOOP_110_1_VITIS_LOOP_114_3_VITIS_LOOP_116_4_VIT",
		"Protocol" : "ap_ctrl_hs",
		"ControlExist" : "1", "ap_start" : "1", "ap_ready" : "1", "ap_done" : "1", "ap_continue" : "0", "ap_idle" : "1", "real_start" : "0",
		"Pipeline" : "None", "UnalignedPipeline" : "0", "RewindPipeline" : "0", "ProcessNetwork" : "0",
		"II" : "0",
		"VariableLatency" : "1", "ExactLatency" : "-1", "EstimateLatencyMin" : "15691", "EstimateLatencyMax" : "15691",
		"Combinational" : "0",
		"Datapath" : "0",
		"ClockEnable" : "0",
		"HasSubDataflow" : "0",
		"InDataflowNetwork" : "0",
		"HasNonBlockingOperation" : "0",
		"IsBlackBox" : "0",
		"Port" : [
			{"Name" : "gmem", "Type" : "MAXI", "Direction" : "IO",
				"BlockSignal" : [
					{"Name" : "gmem_blk_n_R", "Type" : "RtlSignal"},
					{"Name" : "gmem_blk_n_AW", "Type" : "RtlSignal"},
					{"Name" : "gmem_blk_n_W", "Type" : "RtlSignal"},
					{"Name" : "gmem_blk_n_B", "Type" : "RtlSignal"}]},
			{"Name" : "sext_ln110", "Type" : "None", "Direction" : "I"},
			{"Name" : "afterRearrangeX2", "Type" : "None", "Direction" : "I"}],
		"Loop" : [
			{"Name" : "VITIS_LOOP_110_1_VITIS_LOOP_114_3_VITIS_LOOP_116_4_VITIS_LOOP_118_5", "PipelineType" : "UPC",
				"LoopDec" : {"FSMBitwidth" : "1", "FirstState" : "ap_ST_fsm_pp0_stage0", "FirstStateIter" : "ap_enable_reg_pp0_iter1", "FirstStateBlock" : "ap_block_pp0_stage0_subdone", "LastState" : "ap_ST_fsm_pp0_stage0", "LastStateIter" : "ap_enable_reg_pp0_iter11", "LastStateBlock" : "ap_block_pp0_stage0_subdone", "QuitState" : "ap_ST_fsm_pp0_stage0", "QuitStateIter" : "ap_enable_reg_pp0_iter11", "QuitStateBlock" : "ap_block_pp0_stage0_subdone", "OneDepthLoop" : "0", "has_ap_ctrl" : "1", "has_continue" : "0"}}]},
	{"ID" : "78", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_kernel_attention_Pipeline_VITIS_LOOP_110_1_VITIS_LOOP_114_3_VITIS_LOOP_116_4_VIT_fu_623.mul_3ns_13ns_14_1_1_U161", "Parent" : "77"},
	{"ID" : "79", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_kernel_attention_Pipeline_VITIS_LOOP_110_1_VITIS_LOOP_114_3_VITIS_LOOP_116_4_VIT_fu_623.mul_3ns_13ns_14_1_1_U162", "Parent" : "77"},
	{"ID" : "80", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_kernel_attention_Pipeline_VITIS_LOOP_110_1_VITIS_LOOP_114_3_VITIS_LOOP_116_4_VIT_fu_623.mac_muladd_3ns_10ns_14ns_14_4_1_U163", "Parent" : "77"},
	{"ID" : "81", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_kernel_attention_Pipeline_VITIS_LOOP_110_1_VITIS_LOOP_114_3_VITIS_LOOP_116_4_VIT_fu_623.mac_muladd_3ns_10ns_14ns_14_4_1_U164", "Parent" : "77"},
	{"ID" : "82", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_kernel_attention_Pipeline_VITIS_LOOP_110_1_VITIS_LOOP_114_3_VITIS_LOOP_116_4_VIT_fu_623.flow_control_loop_pipe_sequential_init_U", "Parent" : "77"},
	{"ID" : "83", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.grp_kernel_attention_Pipeline_VITIS_LOOP_177_1_VITIS_LOOP_181_3_VITIS_LOOP_183_4_VIT_fu_631", "Parent" : "0", "Child" : ["84", "85", "86", "87"],
		"CDFG" : "kernel_attention_Pipeline_VITIS_LOOP_177_1_VITIS_LOOP_181_3_VITIS_LOOP_183_4_VIT",
		"Protocol" : "ap_ctrl_hs",
		"ControlExist" : "1", "ap_start" : "1", "ap_ready" : "1", "ap_done" : "1", "ap_continue" : "0", "ap_idle" : "1", "real_start" : "0",
		"Pipeline" : "None", "UnalignedPipeline" : "0", "RewindPipeline" : "0", "ProcessNetwork" : "0",
		"II" : "0",
		"VariableLatency" : "1", "ExactLatency" : "-1", "EstimateLatencyMin" : "15691", "EstimateLatencyMax" : "15691",
		"Combinational" : "0",
		"Datapath" : "0",
		"ClockEnable" : "0",
		"HasSubDataflow" : "0",
		"InDataflowNetwork" : "0",
		"HasNonBlockingOperation" : "0",
		"IsBlackBox" : "0",
		"Port" : [
			{"Name" : "gmem", "Type" : "MAXI", "Direction" : "IO",
				"BlockSignal" : [
					{"Name" : "gmem_blk_n_R", "Type" : "RtlSignal"},
					{"Name" : "gmem_blk_n_AW", "Type" : "RtlSignal"},
					{"Name" : "gmem_blk_n_W", "Type" : "RtlSignal"},
					{"Name" : "gmem_blk_n_B", "Type" : "RtlSignal"}]},
			{"Name" : "sext_ln177", "Type" : "None", "Direction" : "I"},
			{"Name" : "afterRearrangeQKX", "Type" : "None", "Direction" : "I"}],
		"Loop" : [
			{"Name" : "VITIS_LOOP_177_1_VITIS_LOOP_181_3_VITIS_LOOP_183_4_VITIS_LOOP_184_5", "PipelineType" : "UPC",
				"LoopDec" : {"FSMBitwidth" : "1", "FirstState" : "ap_ST_fsm_pp0_stage0", "FirstStateIter" : "ap_enable_reg_pp0_iter1", "FirstStateBlock" : "ap_block_pp0_stage0_subdone", "LastState" : "ap_ST_fsm_pp0_stage0", "LastStateIter" : "ap_enable_reg_pp0_iter11", "LastStateBlock" : "ap_block_pp0_stage0_subdone", "QuitState" : "ap_ST_fsm_pp0_stage0", "QuitStateIter" : "ap_enable_reg_pp0_iter11", "QuitStateBlock" : "ap_block_pp0_stage0_subdone", "OneDepthLoop" : "0", "has_ap_ctrl" : "1", "has_continue" : "0"}}]},
	{"ID" : "84", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_kernel_attention_Pipeline_VITIS_LOOP_177_1_VITIS_LOOP_181_3_VITIS_LOOP_183_4_VIT_fu_631.mul_3ns_13ns_15_1_1_U168", "Parent" : "83"},
	{"ID" : "85", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_kernel_attention_Pipeline_VITIS_LOOP_177_1_VITIS_LOOP_181_3_VITIS_LOOP_183_4_VIT_fu_631.mul_3ns_13ns_15_1_1_U169", "Parent" : "83"},
	{"ID" : "86", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_kernel_attention_Pipeline_VITIS_LOOP_177_1_VITIS_LOOP_181_3_VITIS_LOOP_183_4_VIT_fu_631.ama_addmuladd_5ns_6ns_6ns_3ns_12_4_1_U170", "Parent" : "83"},
	{"ID" : "87", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_kernel_attention_Pipeline_VITIS_LOOP_177_1_VITIS_LOOP_181_3_VITIS_LOOP_183_4_VIT_fu_631.flow_control_loop_pipe_sequential_init_U", "Parent" : "83"},
	{"ID" : "88", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.grp_kernel_attention_Pipeline_VITIS_LOOP_511_1_VITIS_LOOP_515_3_VITIS_LOOP_517_4_fu_639", "Parent" : "0", "Child" : ["89", "90", "91", "92", "93", "94"],
		"CDFG" : "kernel_attention_Pipeline_VITIS_LOOP_511_1_VITIS_LOOP_515_3_VITIS_LOOP_517_4",
		"Protocol" : "ap_ctrl_hs",
		"ControlExist" : "1", "ap_start" : "1", "ap_ready" : "1", "ap_done" : "1", "ap_continue" : "0", "ap_idle" : "1", "real_start" : "0",
		"Pipeline" : "None", "UnalignedPipeline" : "0", "RewindPipeline" : "0", "ProcessNetwork" : "0",
		"II" : "0",
		"VariableLatency" : "1", "ExactLatency" : "-1", "EstimateLatencyMin" : "47051", "EstimateLatencyMax" : "47051",
		"Combinational" : "0",
		"Datapath" : "0",
		"ClockEnable" : "0",
		"HasSubDataflow" : "0",
		"InDataflowNetwork" : "0",
		"HasNonBlockingOperation" : "0",
		"IsBlackBox" : "0",
		"Port" : [
			{"Name" : "gmem", "Type" : "MAXI", "Direction" : "IO",
				"BlockSignal" : [
					{"Name" : "gmem_blk_n_R", "Type" : "RtlSignal"},
					{"Name" : "gmem_blk_n_AW", "Type" : "RtlSignal"},
					{"Name" : "gmem_blk_n_W", "Type" : "RtlSignal"},
					{"Name" : "gmem_blk_n_B", "Type" : "RtlSignal"}]},
			{"Name" : "sext_ln511", "Type" : "None", "Direction" : "I"},
			{"Name" : "afterAct2", "Type" : "None", "Direction" : "I"}],
		"Loop" : [
			{"Name" : "VITIS_LOOP_511_1_VITIS_LOOP_515_3_VITIS_LOOP_517_4", "PipelineType" : "UPC",
				"LoopDec" : {"FSMBitwidth" : "1", "FirstState" : "ap_ST_fsm_pp0_stage0", "FirstStateIter" : "ap_enable_reg_pp0_iter1", "FirstStateBlock" : "ap_block_pp0_stage0_subdone", "LastState" : "ap_ST_fsm_pp0_stage0", "LastStateIter" : "ap_enable_reg_pp0_iter11", "LastStateBlock" : "ap_block_pp0_stage0_subdone", "QuitState" : "ap_ST_fsm_pp0_stage0", "QuitStateIter" : "ap_enable_reg_pp0_iter11", "QuitStateBlock" : "ap_block_pp0_stage0_subdone", "OneDepthLoop" : "0", "has_ap_ctrl" : "1", "has_continue" : "0"}}]},
	{"ID" : "89", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_kernel_attention_Pipeline_VITIS_LOOP_511_1_VITIS_LOOP_515_3_VITIS_LOOP_517_4_fu_639.fcmp_32ns_32ns_1_1_no_dsp_1_U175", "Parent" : "88"},
	{"ID" : "90", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_kernel_attention_Pipeline_VITIS_LOOP_511_1_VITIS_LOOP_515_3_VITIS_LOOP_517_4_fu_639.mul_3ns_15ns_16_1_1_U176", "Parent" : "88"},
	{"ID" : "91", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_kernel_attention_Pipeline_VITIS_LOOP_511_1_VITIS_LOOP_515_3_VITIS_LOOP_517_4_fu_639.mul_3ns_15ns_16_1_1_U177", "Parent" : "88"},
	{"ID" : "92", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_kernel_attention_Pipeline_VITIS_LOOP_511_1_VITIS_LOOP_515_3_VITIS_LOOP_517_4_fu_639.mac_muladd_8ns_6ns_16ns_16_4_1_U178", "Parent" : "88"},
	{"ID" : "93", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_kernel_attention_Pipeline_VITIS_LOOP_511_1_VITIS_LOOP_515_3_VITIS_LOOP_517_4_fu_639.mac_muladd_8ns_6ns_16ns_16_4_1_U179", "Parent" : "88"},
	{"ID" : "94", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_kernel_attention_Pipeline_VITIS_LOOP_511_1_VITIS_LOOP_515_3_VITIS_LOOP_517_4_fu_639.flow_control_loop_pipe_sequential_init_U", "Parent" : "88"},
	{"ID" : "95", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.grp_kernel_attention_Pipeline_VITIS_LOOP_146_2_VITIS_LOOP_150_4_VITIS_LOOP_152_5_VIT_fu_647", "Parent" : "0", "Child" : ["96", "97", "98"],
		"CDFG" : "kernel_attention_Pipeline_VITIS_LOOP_146_2_VITIS_LOOP_150_4_VITIS_LOOP_152_5_VIT",
		"Protocol" : "ap_ctrl_hs",
		"ControlExist" : "1", "ap_start" : "1", "ap_ready" : "1", "ap_done" : "1", "ap_continue" : "0", "ap_idle" : "1", "real_start" : "0",
		"Pipeline" : "None", "UnalignedPipeline" : "0", "RewindPipeline" : "0", "ProcessNetwork" : "0",
		"II" : "0",
		"VariableLatency" : "1", "ExactLatency" : "-1", "EstimateLatencyMin" : "47048", "EstimateLatencyMax" : "47048",
		"Combinational" : "0",
		"Datapath" : "0",
		"ClockEnable" : "0",
		"HasSubDataflow" : "0",
		"InDataflowNetwork" : "0",
		"HasNonBlockingOperation" : "0",
		"IsBlackBox" : "0",
		"Port" : [
			{"Name" : "gmem", "Type" : "MAXI", "Direction" : "IO",
				"BlockSignal" : [
					{"Name" : "gmem_blk_n_R", "Type" : "RtlSignal"},
					{"Name" : "gmem_blk_n_AW", "Type" : "RtlSignal"},
					{"Name" : "gmem_blk_n_W", "Type" : "RtlSignal"},
					{"Name" : "gmem_blk_n_B", "Type" : "RtlSignal"}]},
			{"Name" : "sext_ln146", "Type" : "None", "Direction" : "I"},
			{"Name" : "buffer_out", "Type" : "None", "Direction" : "I"}],
		"Loop" : [
			{"Name" : "VITIS_LOOP_146_2_VITIS_LOOP_150_4_VITIS_LOOP_152_5_VITIS_LOOP_154_6", "PipelineType" : "UPC",
				"LoopDec" : {"FSMBitwidth" : "1", "FirstState" : "ap_ST_fsm_pp0_stage0", "FirstStateIter" : "ap_enable_reg_pp0_iter1", "FirstStateBlock" : "ap_block_pp0_stage0_subdone", "LastState" : "ap_ST_fsm_pp0_stage0", "LastStateIter" : "ap_enable_reg_pp0_iter8", "LastStateBlock" : "ap_block_pp0_stage0_subdone", "QuitState" : "ap_ST_fsm_pp0_stage0", "QuitStateIter" : "ap_enable_reg_pp0_iter8", "QuitStateBlock" : "ap_block_pp0_stage0_subdone", "OneDepthLoop" : "0", "has_ap_ctrl" : "1", "has_continue" : "0"}}]},
	{"ID" : "96", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_kernel_attention_Pipeline_VITIS_LOOP_146_2_VITIS_LOOP_150_4_VITIS_LOOP_152_5_VIT_fu_647.mul_8ns_9ns_16_1_1_U186", "Parent" : "95"},
	{"ID" : "97", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_kernel_attention_Pipeline_VITIS_LOOP_146_2_VITIS_LOOP_150_4_VITIS_LOOP_152_5_VIT_fu_647.mul_8ns_9ns_16_1_1_U187", "Parent" : "95"},
	{"ID" : "98", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_kernel_attention_Pipeline_VITIS_LOOP_146_2_VITIS_LOOP_150_4_VITIS_LOOP_152_5_VIT_fu_647.flow_control_loop_pipe_sequential_init_U", "Parent" : "95"},
	{"ID" : "99", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.grp_kernel_attention_Pipeline_VITIS_LOOP_268_2_VITIS_LOOP_269_3_VITIS_LOOP_270_4_fu_655", "Parent" : "0", "Child" : ["100"],
		"CDFG" : "kernel_attention_Pipeline_VITIS_LOOP_268_2_VITIS_LOOP_269_3_VITIS_LOOP_270_4",
		"Protocol" : "ap_ctrl_hs",
		"ControlExist" : "1", "ap_start" : "1", "ap_ready" : "1", "ap_done" : "1", "ap_continue" : "0", "ap_idle" : "1", "real_start" : "0",
		"Pipeline" : "None", "UnalignedPipeline" : "0", "RewindPipeline" : "0", "ProcessNetwork" : "0",
		"II" : "0",
		"VariableLatency" : "1", "ExactLatency" : "-1", "EstimateLatencyMin" : "47043", "EstimateLatencyMax" : "47043",
		"Combinational" : "0",
		"Datapath" : "0",
		"ClockEnable" : "0",
		"HasSubDataflow" : "0",
		"InDataflowNetwork" : "0",
		"HasNonBlockingOperation" : "0",
		"IsBlackBox" : "0",
		"Port" : [
			{"Name" : "gmem", "Type" : "MAXI", "Direction" : "I",
				"BlockSignal" : [
					{"Name" : "gmem_blk_n_R", "Type" : "RtlSignal"}]},
			{"Name" : "gmem0", "Type" : "MAXI", "Direction" : "O",
				"BlockSignal" : [
					{"Name" : "gmem0_blk_n_W", "Type" : "RtlSignal"}]},
			{"Name" : "sext_ln268_1", "Type" : "None", "Direction" : "I"},
			{"Name" : "sext_ln268", "Type" : "None", "Direction" : "I"}],
		"Loop" : [
			{"Name" : "VITIS_LOOP_268_2_VITIS_LOOP_269_3_VITIS_LOOP_270_4", "PipelineType" : "UPC",
				"LoopDec" : {"FSMBitwidth" : "1", "FirstState" : "ap_ST_fsm_pp0_stage0", "FirstStateIter" : "ap_enable_reg_pp0_iter0", "FirstStateBlock" : "ap_block_pp0_stage0_subdone", "LastState" : "ap_ST_fsm_pp0_stage0", "LastStateIter" : "ap_enable_reg_pp0_iter2", "LastStateBlock" : "ap_block_pp0_stage0_subdone", "QuitState" : "ap_ST_fsm_pp0_stage0", "QuitStateIter" : "ap_enable_reg_pp0_iter1", "QuitStateBlock" : "ap_block_pp0_stage0_subdone", "OneDepthLoop" : "0", "has_ap_ctrl" : "1", "has_continue" : "0"}}]},
	{"ID" : "100", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_kernel_attention_Pipeline_VITIS_LOOP_268_2_VITIS_LOOP_269_3_VITIS_LOOP_270_4_fu_655.flow_control_loop_pipe_sequential_init_U", "Parent" : "99"},
	{"ID" : "101", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.control_s_axi_U", "Parent" : "0"},
	{"ID" : "102", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.gmem_m_axi_U", "Parent" : "0"},
	{"ID" : "103", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.gmem0_m_axi_U", "Parent" : "0"},
	{"ID" : "104", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.gmem1_m_axi_U", "Parent" : "0"},
	{"ID" : "105", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.fpext_32ns_64_1_no_dsp_1_U196", "Parent" : "0"},
	{"ID" : "106", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.fpext_32ns_64_1_no_dsp_1_U197", "Parent" : "0"},
	{"ID" : "107", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.dadd_64ns_64ns_64_1_full_dsp_1_U198", "Parent" : "0"},
	{"ID" : "108", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.dsqrt_64ns_64ns_64_5_no_dsp_1_U199", "Parent" : "0"}]}


set ArgLastReadFirstWriteLatency {
	kernel_attention {
		gmem0 {Type IO LastRead 97 FirstWrite -1}
		gmem1 {Type IO LastRead 14 FirstWrite -1}
		gmem {Type IO LastRead 88 FirstWrite -1}
		buffer_DataIn_1 {Type I LastRead 0 FirstWrite -1}
		afterNorm {Type I LastRead 0 FirstWrite -1}
		norm1_mean {Type I LastRead 0 FirstWrite -1}
		norm1_var {Type I LastRead 0 FirstWrite -1}
		norm1_weight {Type I LastRead 0 FirstWrite -1}
		norm1_bias {Type I LastRead 0 FirstWrite -1}
		afterPad {Type I LastRead 0 FirstWrite -1}
		afterRearrangeX {Type I LastRead 0 FirstWrite -1}
		afterPad1 {Type I LastRead -1 FirstWrite -1}
		afterConv1 {Type I LastRead 0 FirstWrite -1}
		kernel1 {Type I LastRead 0 FirstWrite -1}
		bias1 {Type I LastRead 0 FirstWrite -1}
		in_qk {Type I LastRead 0 FirstWrite -1}
		in_q {Type I LastRead 0 FirstWrite -1}
		in_k {Type I LastRead 0 FirstWrite -1}
		afterQKMultiplication {Type I LastRead 0 FirstWrite -1}
		afterSoftmax {Type I LastRead 0 FirstWrite -1}
		afterRearrangeX2 {Type I LastRead 0 FirstWrite -1}
		afterQKXMultiplication {Type I LastRead 0 FirstWrite -1}
		afterRearrangeQKX {Type I LastRead 0 FirstWrite -1}
		afterPad2 {Type I LastRead -1 FirstWrite -1}
		afterConv2 {Type I LastRead 0 FirstWrite -1}
		kernel2 {Type I LastRead 0 FirstWrite -1}
		bias2 {Type I LastRead 0 FirstWrite -1}
		afterAct2 {Type I LastRead 0 FirstWrite -1}
		QKV {Type I LastRead 0 FirstWrite -1}
		buffer_out {Type I LastRead 0 FirstWrite -1}
		buffer_result {Type I LastRead 0 FirstWrite -1}
		pow_reduce_anonymous_namespace_table_exp_Z1_ap_ufixed_array_V {Type I LastRead -1 FirstWrite -1}
		pow_reduce_anonymous_namespace_table_f_Z3_ap_ufixed_array_V {Type I LastRead -1 FirstWrite -1}
		pow_reduce_anonymous_namespace_table_f_Z2_ap_ufixed_array_V {Type I LastRead -1 FirstWrite -1}}
	kernel_attention_Pipeline_VITIS_LOOP_373_3_VITIS_LOOP_375_4 {
		gmem1 {Type O LastRead -1 FirstWrite 11}
		gmem0 {Type I LastRead 1 FirstWrite -1}
		sext_ln371_1 {Type I LastRead 0 FirstWrite -1}
		sext_ln371 {Type I LastRead 0 FirstWrite -1}
		empty {Type I LastRead 0 FirstWrite -1}
		tmp {Type I LastRead 0 FirstWrite -1}
		conv32_i {Type I LastRead 0 FirstWrite -1}
		conv36_i {Type I LastRead 0 FirstWrite -1}}
	kernel_attention_Pipeline_VITIS_LOOP_17_2_VITIS_LOOP_18_3_VITIS_LOOP_19_4 {
		gmem {Type O LastRead -1 FirstWrite 2}
		gmem1 {Type I LastRead 1 FirstWrite -1}
		sext_ln17 {Type I LastRead 0 FirstWrite -1}
		sext_ln371_1 {Type I LastRead 0 FirstWrite -1}}
	kernel_attention_Pipeline_VITIS_LOOP_80_2_VITIS_LOOP_82_3 {
		gmem {Type IO LastRead 44 FirstWrite 12}
		afterPad {Type I LastRead 0 FirstWrite -1}
		afterRearrangeX {Type I LastRead 0 FirstWrite -1}}
	DW_conv {
		gmem {Type IO LastRead 33 FirstWrite -1}
		in_r {Type I LastRead 0 FirstWrite -1}
		kernel {Type I LastRead 0 FirstWrite -1}
		bias {Type I LastRead 0 FirstWrite -1}
		p_read4 {Type I LastRead 0 FirstWrite -1}
		out_r {Type I LastRead 0 FirstWrite -1}}
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
		add_out {Type O LastRead -1 FirstWrite 37}}
	compute_skip {
		gmem {Type IO LastRead 12 FirstWrite 11}
		afterAct {Type I LastRead 1 FirstWrite -1}
		buffer_result {Type I LastRead 1 FirstWrite -1}
		p_read1 {Type I LastRead 0 FirstWrite -1}}
	compute_skip_Pipeline_VITIS_LOOP_584_3 {
		zext_ln580 {Type I LastRead 0 FirstWrite -1}
		bound66 {Type I LastRead 0 FirstWrite -1}
		gmem {Type IO LastRead 12 FirstWrite 11}
		bound21 {Type I LastRead 0 FirstWrite -1}
		afterAct {Type I LastRead 0 FirstWrite -1}
		buffer_result {Type I LastRead 0 FirstWrite -1}}
	get_qk {
		gmem {Type IO LastRead 15 FirstWrite 13}
		in_qk {Type I LastRead 0 FirstWrite -1}
		in_q {Type I LastRead 0 FirstWrite -1}
		in_k {Type I LastRead 0 FirstWrite -1}}
	compute_multiplication {
		gmem {Type IO LastRead 12 FirstWrite -1}
		in_q {Type I LastRead 0 FirstWrite -1}
		in_k {Type I LastRead 0 FirstWrite -1}
		afterQKMultiplication {Type I LastRead 0 FirstWrite -1}
		p_read3 {Type I LastRead 0 FirstWrite -1}
		p_read4 {Type I LastRead 0 FirstWrite -1}
		scale {Type I LastRead 0 FirstWrite -1}}
	compute_multiplication_Pipeline_VITIS_LOOP_207_4 {
		p_read3 {Type I LastRead 0 FirstWrite -1}
		sext_ln206_1 {Type I LastRead 0 FirstWrite -1}
		gmem {Type I LastRead 11 FirstWrite -1}
		mul_ln204 {Type I LastRead 0 FirstWrite -1}
		zext_ln203 {Type I LastRead 0 FirstWrite -1}
		zext_ln206 {Type I LastRead 0 FirstWrite -1}
		in_k {Type I LastRead 0 FirstWrite -1}
		scale {Type I LastRead 0 FirstWrite -1}
		sum_out {Type O LastRead -1 FirstWrite 12}}
	kernel_attention_Pipeline_VITIS_LOOP_230_1_VITIS_LOOP_232_3_count_sum {
		gmem {Type IO LastRead 61 FirstWrite 120}
		sext_ln230_1 {Type I LastRead 0 FirstWrite -1}
		afterQKMultiplication {Type I LastRead 0 FirstWrite -1}
		sext_ln230 {Type I LastRead 0 FirstWrite -1}
		pow_reduce_anonymous_namespace_table_exp_Z1_ap_ufixed_array_V {Type I LastRead -1 FirstWrite -1}
		pow_reduce_anonymous_namespace_table_f_Z3_ap_ufixed_array_V {Type I LastRead -1 FirstWrite -1}
		pow_reduce_anonymous_namespace_table_f_Z2_ap_ufixed_array_V {Type I LastRead -1 FirstWrite -1}}
	pow_generic_double_s {
		exp {Type I LastRead 0 FirstWrite -1}
		pow_reduce_anonymous_namespace_table_exp_Z1_ap_ufixed_array_V {Type I LastRead -1 FirstWrite -1}
		pow_reduce_anonymous_namespace_table_f_Z3_ap_ufixed_array_V {Type I LastRead -1 FirstWrite -1}
		pow_reduce_anonymous_namespace_table_f_Z2_ap_ufixed_array_V {Type I LastRead -1 FirstWrite -1}}
	kernel_attention_Pipeline_VITIS_LOOP_110_1_VITIS_LOOP_114_3_VITIS_LOOP_116_4_VIT {
		gmem {Type IO LastRead 7 FirstWrite 6}
		sext_ln110 {Type I LastRead 0 FirstWrite -1}
		afterRearrangeX2 {Type I LastRead 0 FirstWrite -1}}
	kernel_attention_Pipeline_VITIS_LOOP_177_1_VITIS_LOOP_181_3_VITIS_LOOP_183_4_VIT {
		gmem {Type IO LastRead 7 FirstWrite 6}
		sext_ln177 {Type I LastRead 0 FirstWrite -1}
		afterRearrangeQKX {Type I LastRead 0 FirstWrite -1}}
	kernel_attention_Pipeline_VITIS_LOOP_511_1_VITIS_LOOP_515_3_VITIS_LOOP_517_4 {
		gmem {Type IO LastRead 7 FirstWrite 6}
		sext_ln511 {Type I LastRead 0 FirstWrite -1}
		afterAct2 {Type I LastRead 0 FirstWrite -1}}
	kernel_attention_Pipeline_VITIS_LOOP_146_2_VITIS_LOOP_150_4_VITIS_LOOP_152_5_VIT {
		gmem {Type IO LastRead 4 FirstWrite 3}
		sext_ln146 {Type I LastRead 0 FirstWrite -1}
		buffer_out {Type I LastRead 0 FirstWrite -1}}
	kernel_attention_Pipeline_VITIS_LOOP_268_2_VITIS_LOOP_269_3_VITIS_LOOP_270_4 {
		gmem {Type I LastRead 1 FirstWrite -1}
		gmem0 {Type O LastRead -1 FirstWrite 2}
		sext_ln268_1 {Type I LastRead 0 FirstWrite -1}
		sext_ln268 {Type I LastRead 0 FirstWrite -1}}}

set hasDtUnsupportedChannel 0

set PerformanceInfo {[
	{"Name" : "Latency", "Min" : "-1", "Max" : "-1"}
	, {"Name" : "Interval", "Min" : "0", "Max" : "0"}
]}

set PipelineEnableSignalInfo {[
]}

set Spec2ImplPortList { 
	gmem0 { m_axi {  { m_axi_gmem0_AWVALID VALID 1 1 }  { m_axi_gmem0_AWREADY READY 0 1 }  { m_axi_gmem0_AWADDR ADDR 1 64 }  { m_axi_gmem0_AWID ID 1 1 }  { m_axi_gmem0_AWLEN SIZE 1 8 }  { m_axi_gmem0_AWSIZE BURST 1 3 }  { m_axi_gmem0_AWBURST LOCK 1 2 }  { m_axi_gmem0_AWLOCK CACHE 1 2 }  { m_axi_gmem0_AWCACHE PROT 1 4 }  { m_axi_gmem0_AWPROT QOS 1 3 }  { m_axi_gmem0_AWQOS REGION 1 4 }  { m_axi_gmem0_AWREGION USER 1 4 }  { m_axi_gmem0_AWUSER DATA 1 1 }  { m_axi_gmem0_WVALID VALID 1 1 }  { m_axi_gmem0_WREADY READY 0 1 }  { m_axi_gmem0_WDATA FIFONUM 1 32 }  { m_axi_gmem0_WSTRB STRB 1 4 }  { m_axi_gmem0_WLAST LAST 1 1 }  { m_axi_gmem0_WID ID 1 1 }  { m_axi_gmem0_WUSER DATA 1 1 }  { m_axi_gmem0_ARVALID VALID 1 1 }  { m_axi_gmem0_ARREADY READY 0 1 }  { m_axi_gmem0_ARADDR ADDR 1 64 }  { m_axi_gmem0_ARID ID 1 1 }  { m_axi_gmem0_ARLEN SIZE 1 8 }  { m_axi_gmem0_ARSIZE BURST 1 3 }  { m_axi_gmem0_ARBURST LOCK 1 2 }  { m_axi_gmem0_ARLOCK CACHE 1 2 }  { m_axi_gmem0_ARCACHE PROT 1 4 }  { m_axi_gmem0_ARPROT QOS 1 3 }  { m_axi_gmem0_ARQOS REGION 1 4 }  { m_axi_gmem0_ARREGION USER 1 4 }  { m_axi_gmem0_ARUSER DATA 1 1 }  { m_axi_gmem0_RVALID VALID 0 1 }  { m_axi_gmem0_RREADY READY 1 1 }  { m_axi_gmem0_RDATA FIFONUM 0 32 }  { m_axi_gmem0_RLAST LAST 0 1 }  { m_axi_gmem0_RID ID 0 1 }  { m_axi_gmem0_RUSER DATA 0 1 }  { m_axi_gmem0_RRESP RESP 0 2 }  { m_axi_gmem0_BVALID VALID 0 1 }  { m_axi_gmem0_BREADY READY 1 1 }  { m_axi_gmem0_BRESP RESP 0 2 }  { m_axi_gmem0_BID ID 0 1 }  { m_axi_gmem0_BUSER DATA 0 1 } } }
	gmem1 { m_axi {  { m_axi_gmem1_AWVALID VALID 1 1 }  { m_axi_gmem1_AWREADY READY 0 1 }  { m_axi_gmem1_AWADDR ADDR 1 64 }  { m_axi_gmem1_AWID ID 1 1 }  { m_axi_gmem1_AWLEN SIZE 1 8 }  { m_axi_gmem1_AWSIZE BURST 1 3 }  { m_axi_gmem1_AWBURST LOCK 1 2 }  { m_axi_gmem1_AWLOCK CACHE 1 2 }  { m_axi_gmem1_AWCACHE PROT 1 4 }  { m_axi_gmem1_AWPROT QOS 1 3 }  { m_axi_gmem1_AWQOS REGION 1 4 }  { m_axi_gmem1_AWREGION USER 1 4 }  { m_axi_gmem1_AWUSER DATA 1 1 }  { m_axi_gmem1_WVALID VALID 1 1 }  { m_axi_gmem1_WREADY READY 0 1 }  { m_axi_gmem1_WDATA FIFONUM 1 32 }  { m_axi_gmem1_WSTRB STRB 1 4 }  { m_axi_gmem1_WLAST LAST 1 1 }  { m_axi_gmem1_WID ID 1 1 }  { m_axi_gmem1_WUSER DATA 1 1 }  { m_axi_gmem1_ARVALID VALID 1 1 }  { m_axi_gmem1_ARREADY READY 0 1 }  { m_axi_gmem1_ARADDR ADDR 1 64 }  { m_axi_gmem1_ARID ID 1 1 }  { m_axi_gmem1_ARLEN SIZE 1 8 }  { m_axi_gmem1_ARSIZE BURST 1 3 }  { m_axi_gmem1_ARBURST LOCK 1 2 }  { m_axi_gmem1_ARLOCK CACHE 1 2 }  { m_axi_gmem1_ARCACHE PROT 1 4 }  { m_axi_gmem1_ARPROT QOS 1 3 }  { m_axi_gmem1_ARQOS REGION 1 4 }  { m_axi_gmem1_ARREGION USER 1 4 }  { m_axi_gmem1_ARUSER DATA 1 1 }  { m_axi_gmem1_RVALID VALID 0 1 }  { m_axi_gmem1_RREADY READY 1 1 }  { m_axi_gmem1_RDATA FIFONUM 0 32 }  { m_axi_gmem1_RLAST LAST 0 1 }  { m_axi_gmem1_RID ID 0 1 }  { m_axi_gmem1_RUSER DATA 0 1 }  { m_axi_gmem1_RRESP RESP 0 2 }  { m_axi_gmem1_BVALID VALID 0 1 }  { m_axi_gmem1_BREADY READY 1 1 }  { m_axi_gmem1_BRESP RESP 0 2 }  { m_axi_gmem1_BID ID 0 1 }  { m_axi_gmem1_BUSER DATA 0 1 } } }
	gmem { m_axi {  { m_axi_gmem_AWVALID VALID 1 1 }  { m_axi_gmem_AWREADY READY 0 1 }  { m_axi_gmem_AWADDR ADDR 1 64 }  { m_axi_gmem_AWID ID 1 1 }  { m_axi_gmem_AWLEN SIZE 1 8 }  { m_axi_gmem_AWSIZE BURST 1 3 }  { m_axi_gmem_AWBURST LOCK 1 2 }  { m_axi_gmem_AWLOCK CACHE 1 2 }  { m_axi_gmem_AWCACHE PROT 1 4 }  { m_axi_gmem_AWPROT QOS 1 3 }  { m_axi_gmem_AWQOS REGION 1 4 }  { m_axi_gmem_AWREGION USER 1 4 }  { m_axi_gmem_AWUSER DATA 1 1 }  { m_axi_gmem_WVALID VALID 1 1 }  { m_axi_gmem_WREADY READY 0 1 }  { m_axi_gmem_WDATA FIFONUM 1 32 }  { m_axi_gmem_WSTRB STRB 1 4 }  { m_axi_gmem_WLAST LAST 1 1 }  { m_axi_gmem_WID ID 1 1 }  { m_axi_gmem_WUSER DATA 1 1 }  { m_axi_gmem_ARVALID VALID 1 1 }  { m_axi_gmem_ARREADY READY 0 1 }  { m_axi_gmem_ARADDR ADDR 1 64 }  { m_axi_gmem_ARID ID 1 1 }  { m_axi_gmem_ARLEN SIZE 1 8 }  { m_axi_gmem_ARSIZE BURST 1 3 }  { m_axi_gmem_ARBURST LOCK 1 2 }  { m_axi_gmem_ARLOCK CACHE 1 2 }  { m_axi_gmem_ARCACHE PROT 1 4 }  { m_axi_gmem_ARPROT QOS 1 3 }  { m_axi_gmem_ARQOS REGION 1 4 }  { m_axi_gmem_ARREGION USER 1 4 }  { m_axi_gmem_ARUSER DATA 1 1 }  { m_axi_gmem_RVALID VALID 0 1 }  { m_axi_gmem_RREADY READY 1 1 }  { m_axi_gmem_RDATA FIFONUM 0 32 }  { m_axi_gmem_RLAST LAST 0 1 }  { m_axi_gmem_RID ID 0 1 }  { m_axi_gmem_RUSER DATA 0 1 }  { m_axi_gmem_RRESP RESP 0 2 }  { m_axi_gmem_BVALID VALID 0 1 }  { m_axi_gmem_BREADY READY 1 1 }  { m_axi_gmem_BRESP RESP 0 2 }  { m_axi_gmem_BID ID 0 1 }  { m_axi_gmem_BUSER DATA 0 1 } } }
}

set maxi_interface_dict [dict create]
dict set maxi_interface_dict gmem0 {NUM_READ_OUTSTANDING 16 NUM_WRITE_OUTSTANDING 16 MAX_READ_BURST_LENGTH 16 MAX_WRITE_BURST_LENGTH 16 READ_WRITE_MODE READ_WRITE}
dict set maxi_interface_dict gmem1 {NUM_READ_OUTSTANDING 16 NUM_WRITE_OUTSTANDING 16 MAX_READ_BURST_LENGTH 16 MAX_WRITE_BURST_LENGTH 16 READ_WRITE_MODE READ_WRITE}
dict set maxi_interface_dict gmem {NUM_READ_OUTSTANDING 16 NUM_WRITE_OUTSTANDING 16 MAX_READ_BURST_LENGTH 16 MAX_WRITE_BURST_LENGTH 16 READ_WRITE_MODE READ_WRITE}

# RTL port scheduling information:
set fifoSchedulingInfoList { 
}

# RTL bus port read request latency information:
set busReadReqLatencyList { 
	{ gmem0 1 }
	{ gmem1 1 }
	{ gmem 1 }
}

# RTL bus port write response latency information:
set busWriteResLatencyList { 
	{ gmem0 1 }
	{ gmem1 1 }
	{ gmem 1 }
}

# RTL array port load latency information:
set memoryLoadLatencyList { 
}
