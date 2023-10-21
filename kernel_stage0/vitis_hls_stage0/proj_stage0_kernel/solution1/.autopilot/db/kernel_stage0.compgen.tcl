# This script segment is generated automatically by AutoPilot

set name kernel_stage0_fdiv_32ns_32ns_32_5_no_dsp_1
if {${::AESL::PGuard_rtl_comp_handler}} {
	::AP::rtl_comp_handler $name BINDTYPE {op} TYPE {fdiv} IMPL {fabric} LATENCY 4 ALLOW_PRAGMA 1
}


set name kernel_stage0_fmul_32ns_32ns_32_2_max_dsp_1
if {${::AESL::PGuard_rtl_comp_handler}} {
	::AP::rtl_comp_handler $name BINDTYPE {op} TYPE {fmul} IMPL {maxdsp} LATENCY 1 ALLOW_PRAGMA 1
}


set name kernel_stage0_fadd_32ns_32ns_32_2_full_dsp_1
if {${::AESL::PGuard_rtl_comp_handler}} {
	::AP::rtl_comp_handler $name BINDTYPE {op} TYPE {fadd} IMPL {fulldsp} LATENCY 1 ALLOW_PRAGMA 1
}


set name kernel_stage0_gmem0_m_axi
if {${::AESL::PGuard_rtl_comp_handler}} {
	::AP::rtl_comp_handler $name BINDTYPE {interface} TYPE {adapter} IMPL {m_axi}
}


set name kernel_stage0_gmem_m_axi
if {${::AESL::PGuard_rtl_comp_handler}} {
	::AP::rtl_comp_handler $name BINDTYPE {interface} TYPE {adapter} IMPL {m_axi}
}


set name kernel_stage0_gmem1_m_axi
if {${::AESL::PGuard_rtl_comp_handler}} {
	::AP::rtl_comp_handler $name BINDTYPE {interface} TYPE {adapter} IMPL {m_axi}
}


set name kernel_stage0_gmem2_m_axi
if {${::AESL::PGuard_rtl_comp_handler}} {
	::AP::rtl_comp_handler $name BINDTYPE {interface} TYPE {adapter} IMPL {m_axi}
}


set name kernel_stage0_gmem3_m_axi
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
X_data { 
	dir I
	width 64
	depth 1
	mode ap_none
	offset 16
	offset_end 27
}
msp_conv_weight { 
	dir I
	width 64
	depth 1
	mode ap_none
	offset 28
	offset_end 39
}
msp_conv_bias { 
	dir I
	width 64
	depth 1
	mode ap_none
	offset 40
	offset_end 51
}
msp_norm_weight { 
	dir I
	width 64
	depth 1
	mode ap_none
	offset 52
	offset_end 63
}
msp_norm_bias { 
	dir I
	width 64
	depth 1
	mode ap_none
	offset 64
	offset_end 75
}
msp_norm_running_mean { 
	dir I
	width 64
	depth 1
	mode ap_none
	offset 76
	offset_end 87
}
msp_norm_running_var { 
	dir I
	width 64
	depth 1
	mode ap_none
	offset 88
	offset_end 99
}
dw_conv_weight { 
	dir I
	width 64
	depth 1
	mode ap_none
	offset 100
	offset_end 111
}
norm_1_weight { 
	dir I
	width 64
	depth 1
	mode ap_none
	offset 112
	offset_end 123
}
norm_1_bias { 
	dir I
	width 64
	depth 1
	mode ap_none
	offset 124
	offset_end 135
}
norm_1_running_mean { 
	dir I
	width 64
	depth 1
	mode ap_none
	offset 136
	offset_end 147
}
norm_1_running_var { 
	dir I
	width 64
	depth 1
	mode ap_none
	offset 148
	offset_end 159
}
se_conv_reduce_weight { 
	dir I
	width 64
	depth 1
	mode ap_none
	offset 160
	offset_end 171
}
se_conv_reduce_bias { 
	dir I
	width 64
	depth 1
	mode ap_none
	offset 172
	offset_end 183
}
se_conv_expand_weight { 
	dir I
	width 64
	depth 1
	mode ap_none
	offset 184
	offset_end 195
}
se_conv_expand_bias { 
	dir I
	width 64
	depth 1
	mode ap_none
	offset 196
	offset_end 207
}
proj_conv_weight { 
	dir I
	width 64
	depth 1
	mode ap_none
	offset 208
	offset_end 219
}
Y_msp_conv { 
	dir I
	width 64
	depth 1
	mode ap_none
	offset 220
	offset_end 231
}
Y_msp_norm { 
	dir I
	width 64
	depth 1
	mode ap_none
	offset 232
	offset_end 243
}
Y_dw_conv { 
	dir I
	width 64
	depth 1
	mode ap_none
	offset 244
	offset_end 255
}
Y_dw_norm { 
	dir I
	width 64
	depth 1
	mode ap_none
	offset 256
	offset_end 267
}
Y_dw_act { 
	dir I
	width 64
	depth 1
	mode ap_none
	offset 268
	offset_end 279
}
Y_mean { 
	dir I
	width 64
	depth 1
	mode ap_none
	offset 280
	offset_end 291
}
Y_reduce { 
	dir I
	width 64
	depth 1
	mode ap_none
	offset 292
	offset_end 303
}
Y_relu { 
	dir I
	width 64
	depth 1
	mode ap_none
	offset 304
	offset_end 315
}
Y_expand { 
	dir I
	width 64
	depth 1
	mode ap_none
	offset 316
	offset_end 327
}
Y_sigmoid { 
	dir I
	width 64
	depth 1
	mode ap_none
	offset 328
	offset_end 339
}
Y_se { 
	dir I
	width 64
	depth 1
	mode ap_none
	offset 340
	offset_end 351
}
Y_proj { 
	dir I
	width 64
	depth 1
	mode ap_none
	offset 352
	offset_end 363
}
}
dict set axilite_register_dict control $port_control


# Native S_AXILite:
if {${::AESL::PGuard_simmodel_gen}} {
	if {[info proc ::AESL_LIB_XILADAPTER::s_axilite_gen] == "::AESL_LIB_XILADAPTER::s_axilite_gen"} {
		eval "::AESL_LIB_XILADAPTER::s_axilite_gen { \
			id 119 \
			corename kernel_stage0_control_axilite \
			name kernel_stage0_control_s_axi \
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
	::AP::rtl_comp_handler kernel_stage0_control_s_axi BINDTYPE interface TYPE interface_s_axilite
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


