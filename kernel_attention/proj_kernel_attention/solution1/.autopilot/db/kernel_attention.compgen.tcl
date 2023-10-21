# This script segment is generated automatically by AutoPilot

set name kernel_attention_dsqrt_64ns_64ns_64_5_no_dsp_1
if {${::AESL::PGuard_rtl_comp_handler}} {
	::AP::rtl_comp_handler $name BINDTYPE {op} TYPE {dsqrt} IMPL {fabric} LATENCY 4 ALLOW_PRAGMA 1
}


set name kernel_attention_gmem0_m_axi
if {${::AESL::PGuard_rtl_comp_handler}} {
	::AP::rtl_comp_handler $name BINDTYPE {interface} TYPE {adapter} IMPL {m_axi}
}


set name kernel_attention_gmem1_m_axi
if {${::AESL::PGuard_rtl_comp_handler}} {
	::AP::rtl_comp_handler $name BINDTYPE {interface} TYPE {adapter} IMPL {m_axi}
}


set name kernel_attention_gmem_m_axi
if {${::AESL::PGuard_rtl_comp_handler}} {
	::AP::rtl_comp_handler $name BINDTYPE {interface} TYPE {adapter} IMPL {m_axi}
}


# clear list
if {${::AESL::PGuard_autoexp_gen}} {
    cg_default_interface_gen_dc_begin
    cg_default_interface_gen_bundle_begin
    AESL_LIB_XILADAPTER::native_axis_begin
}

set axilite_register_dict [dict create]
set port_control {
buffer_DataIn_1 { 
	dir I
	width 64
	depth 1
	mode ap_none
	offset 16
	offset_end 27
}
afterNorm { 
	dir I
	width 64
	depth 1
	mode ap_none
	offset 28
	offset_end 39
}
norm1_mean { 
	dir I
	width 64
	depth 1
	mode ap_none
	offset 40
	offset_end 51
}
norm1_var { 
	dir I
	width 64
	depth 1
	mode ap_none
	offset 52
	offset_end 63
}
norm1_weight { 
	dir I
	width 64
	depth 1
	mode ap_none
	offset 64
	offset_end 75
}
norm1_bias { 
	dir I
	width 64
	depth 1
	mode ap_none
	offset 76
	offset_end 87
}
afterPad { 
	dir I
	width 64
	depth 1
	mode ap_none
	offset 88
	offset_end 99
}
afterRearrangeX { 
	dir I
	width 64
	depth 1
	mode ap_none
	offset 100
	offset_end 111
}
afterPad1 { 
	dir I
	width 64
	depth 1
	mode ap_none
	offset 112
	offset_end 123
}
afterConv1 { 
	dir I
	width 64
	depth 1
	mode ap_none
	offset 124
	offset_end 135
}
kernel1 { 
	dir I
	width 64
	depth 1
	mode ap_none
	offset 136
	offset_end 147
}
bias1 { 
	dir I
	width 64
	depth 1
	mode ap_none
	offset 148
	offset_end 159
}
in_qk { 
	dir I
	width 64
	depth 1
	mode ap_none
	offset 160
	offset_end 171
}
in_q { 
	dir I
	width 64
	depth 1
	mode ap_none
	offset 172
	offset_end 183
}
in_k { 
	dir I
	width 64
	depth 1
	mode ap_none
	offset 184
	offset_end 195
}
afterQKMultiplication { 
	dir I
	width 64
	depth 1
	mode ap_none
	offset 196
	offset_end 207
}
afterSoftmax { 
	dir I
	width 64
	depth 1
	mode ap_none
	offset 208
	offset_end 219
}
afterRearrangeX2 { 
	dir I
	width 64
	depth 1
	mode ap_none
	offset 220
	offset_end 231
}
afterQKXMultiplication { 
	dir I
	width 64
	depth 1
	mode ap_none
	offset 232
	offset_end 243
}
afterRearrangeQKX { 
	dir I
	width 64
	depth 1
	mode ap_none
	offset 244
	offset_end 255
}
afterPad2 { 
	dir I
	width 64
	depth 1
	mode ap_none
	offset 256
	offset_end 267
}
afterConv2 { 
	dir I
	width 64
	depth 1
	mode ap_none
	offset 268
	offset_end 279
}
kernel2 { 
	dir I
	width 64
	depth 1
	mode ap_none
	offset 280
	offset_end 291
}
bias2 { 
	dir I
	width 64
	depth 1
	mode ap_none
	offset 292
	offset_end 303
}
afterAct2 { 
	dir I
	width 64
	depth 1
	mode ap_none
	offset 304
	offset_end 315
}
QKV { 
	dir I
	width 64
	depth 1
	mode ap_none
	offset 316
	offset_end 327
}
buffer_out { 
	dir I
	width 64
	depth 1
	mode ap_none
	offset 328
	offset_end 339
}
buffer_result { 
	dir I
	width 64
	depth 1
	mode ap_none
	offset 340
	offset_end 351
}
}
dict set axilite_register_dict control $port_control


# Native S_AXILite:
if {${::AESL::PGuard_simmodel_gen}} {
	if {[info proc ::AESL_LIB_XILADAPTER::s_axilite_gen] == "::AESL_LIB_XILADAPTER::s_axilite_gen"} {
		eval "::AESL_LIB_XILADAPTER::s_axilite_gen { \
			id 201 \
			corename kernel_attention_control_axilite \
			name kernel_attention_control_s_axi \
			ports {$port_control} \
			op interface \
			interrupt_clear_mode COR \
			interrupt_trigger_type default \
			is_flushable 0 \
			is_datawidth64 0 \
			is_addrwidth64 1 \
		} "
	} else {
		puts "@W \[IMPL-110\] Cannot find AXI Lite interface model in the library. Ignored generation of AXI Lite  interface for 'control'"
	}
}

if {${::AESL::PGuard_rtl_comp_handler}} {
	::AP::rtl_comp_handler kernel_attention_control_s_axi BINDTYPE interface TYPE interface_s_axilite
}

# Direct connection:
if {${::AESL::PGuard_autoexp_gen}} {
eval "cg_default_interface_gen_dc { \
    id -1 \
    name ap_ctrl \
    type ap_ctrl \
    reset_level 0 \
    sync_rst true \
    corename ap_ctrl \
    op interface \
    ports { ap_start { I 1 bit } ap_ready { O 1 bit } ap_done { O 1 bit } ap_idle { O 1 bit } } \
} "
}


# Adapter definition:
set PortName ap_clk
set DataWd 1 
if {${::AESL::PGuard_autoexp_gen}} {
if {[info proc cg_default_interface_gen_clock] == "cg_default_interface_gen_clock"} {
eval "cg_default_interface_gen_clock { \
    id -2 \
    name ${PortName} \
    reset_level 0 \
    sync_rst true \
    corename apif_ap_clk \
    data_wd ${DataWd} \
    op interface \
}"
} else {
puts "@W \[IMPL-113\] Cannot find bus interface model in the library. Ignored generation of bus interface for '${PortName}'"
}
}


# Adapter definition:
set PortName ap_rst_n
set DataWd 1 
if {${::AESL::PGuard_autoexp_gen}} {
if {[info proc cg_default_interface_gen_reset] == "cg_default_interface_gen_reset"} {
eval "cg_default_interface_gen_reset { \
    id -3 \
    name ${PortName} \
    reset_level 0 \
    sync_rst true \
    corename apif_ap_rst_n \
    data_wd ${DataWd} \
    op interface \
}"
} else {
puts "@W \[IMPL-114\] Cannot find bus interface model in the library. Ignored generation of bus interface for '${PortName}'"
}
}



# merge
if {${::AESL::PGuard_autoexp_gen}} {
    cg_default_interface_gen_dc_end
    cg_default_interface_gen_bundle_end
    AESL_LIB_XILADAPTER::native_axis_end
}


