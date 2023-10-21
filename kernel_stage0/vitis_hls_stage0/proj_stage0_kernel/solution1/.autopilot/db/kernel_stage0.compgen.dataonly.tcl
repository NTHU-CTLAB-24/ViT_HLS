# This script segment is generated automatically by AutoPilot

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


