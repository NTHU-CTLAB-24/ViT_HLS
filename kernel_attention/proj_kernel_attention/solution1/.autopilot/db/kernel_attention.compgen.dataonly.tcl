# This script segment is generated automatically by AutoPilot

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


