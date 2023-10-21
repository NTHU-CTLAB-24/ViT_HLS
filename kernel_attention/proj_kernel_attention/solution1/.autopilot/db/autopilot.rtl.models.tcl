set SynModuleInfo {
  {SRCNAME kernel_attention_Pipeline_VITIS_LOOP_373_3_VITIS_LOOP_375_4 MODELNAME kernel_attention_Pipeline_VITIS_LOOP_373_3_VITIS_LOOP_375_4 RTLNAME kernel_attention_kernel_attention_Pipeline_VITIS_LOOP_373_3_VITIS_LOOP_375_4
    SUBMODULES {
      {MODELNAME kernel_attention_fsub_32ns_32ns_32_1_full_dsp_1 RTLNAME kernel_attention_fsub_32ns_32ns_32_1_full_dsp_1 BINDTYPE op TYPE fsub IMPL fulldsp LATENCY 0 ALLOW_PRAGMA 1}
      {MODELNAME kernel_attention_fptrunc_64ns_32_1_no_dsp_1 RTLNAME kernel_attention_fptrunc_64ns_32_1_no_dsp_1 BINDTYPE op TYPE fptrunc IMPL auto LATENCY 0 ALLOW_PRAGMA 1}
      {MODELNAME kernel_attention_fpext_32ns_64_1_no_dsp_1 RTLNAME kernel_attention_fpext_32ns_64_1_no_dsp_1 BINDTYPE op TYPE fpext IMPL auto LATENCY 0 ALLOW_PRAGMA 1}
      {MODELNAME kernel_attention_dadd_64ns_64ns_64_1_full_dsp_1 RTLNAME kernel_attention_dadd_64ns_64ns_64_1_full_dsp_1 BINDTYPE op TYPE dadd IMPL fulldsp LATENCY 0 ALLOW_PRAGMA 1}
      {MODELNAME kernel_attention_dmul_64ns_64ns_64_2_max_dsp_1 RTLNAME kernel_attention_dmul_64ns_64ns_64_2_max_dsp_1 BINDTYPE op TYPE dmul IMPL maxdsp LATENCY 1 ALLOW_PRAGMA 1}
      {MODELNAME kernel_attention_ddiv_64ns_64ns_64_5_no_dsp_1 RTLNAME kernel_attention_ddiv_64ns_64ns_64_5_no_dsp_1 BINDTYPE op TYPE ddiv IMPL fabric LATENCY 4 ALLOW_PRAGMA 1}
      {MODELNAME kernel_attention_flow_control_loop_pipe_sequential_init RTLNAME kernel_attention_flow_control_loop_pipe_sequential_init BINDTYPE interface TYPE internal_upc_flow_control INSTNAME kernel_attention_flow_control_loop_pipe_sequential_init_U}
    }
  }
  {SRCNAME kernel_attention_Pipeline_VITIS_LOOP_17_2_VITIS_LOOP_18_3_VITIS_LOOP_19_4 MODELNAME kernel_attention_Pipeline_VITIS_LOOP_17_2_VITIS_LOOP_18_3_VITIS_LOOP_19_4 RTLNAME kernel_attention_kernel_attention_Pipeline_VITIS_LOOP_17_2_VITIS_LOOP_18_3_VITIS_LOOP_19_4}
  {SRCNAME kernel_attention_Pipeline_VITIS_LOOP_80_2_VITIS_LOOP_82_3 MODELNAME kernel_attention_Pipeline_VITIS_LOOP_80_2_VITIS_LOOP_82_3 RTLNAME kernel_attention_kernel_attention_Pipeline_VITIS_LOOP_80_2_VITIS_LOOP_82_3
    SUBMODULES {
      {MODELNAME kernel_attention_mac_muladd_7ns_8ns_9s_15_4_1 RTLNAME kernel_attention_mac_muladd_7ns_8ns_9s_15_4_1 BINDTYPE op TYPE all IMPL dsp48 LATENCY 3 ALLOW_PRAGMA 1}
      {MODELNAME kernel_attention_mac_muladd_7ns_6ns_7s_13_4_1 RTLNAME kernel_attention_mac_muladd_7ns_6ns_7s_13_4_1 BINDTYPE op TYPE all IMPL dsp48 LATENCY 3 ALLOW_PRAGMA 1}
    }
  }
  {SRCNAME DW_conv_Pipeline_In_Channel MODELNAME DW_conv_Pipeline_In_Channel RTLNAME kernel_attention_DW_conv_Pipeline_In_Channel
    SUBMODULES {
      {MODELNAME kernel_attention_fadd_32ns_32ns_32_1_full_dsp_1 RTLNAME kernel_attention_fadd_32ns_32ns_32_1_full_dsp_1 BINDTYPE op TYPE fadd IMPL fulldsp LATENCY 0 ALLOW_PRAGMA 1}
      {MODELNAME kernel_attention_fmul_32ns_32ns_32_1_max_dsp_1 RTLNAME kernel_attention_fmul_32ns_32ns_32_1_max_dsp_1 BINDTYPE op TYPE fmul IMPL maxdsp LATENCY 0 ALLOW_PRAGMA 1}
      {MODELNAME kernel_attention_mul_62s_7ns_62_1_1 RTLNAME kernel_attention_mul_62s_7ns_62_1_1 BINDTYPE op TYPE mul IMPL auto LATENCY 0 ALLOW_PRAGMA 1}
      {MODELNAME kernel_attention_srem_32ns_8ns_8_36_1 RTLNAME kernel_attention_srem_32ns_8ns_8_36_1 BINDTYPE op TYPE srem IMPL auto LATENCY 35 ALLOW_PRAGMA 1}
    }
  }
  {SRCNAME DW_conv MODELNAME DW_conv RTLNAME kernel_attention_DW_conv
    SUBMODULES {
      {MODELNAME kernel_attention_mul_2ns_13ns_14_1_1 RTLNAME kernel_attention_mul_2ns_13ns_14_1_1 BINDTYPE op TYPE mul IMPL auto LATENCY 0 ALLOW_PRAGMA 1}
      {MODELNAME kernel_attention_urem_8ns_8ns_8_12_seq_1 RTLNAME kernel_attention_urem_8ns_8ns_8_12_seq_1 BINDTYPE op TYPE urem IMPL auto_seq LATENCY 11 ALLOW_PRAGMA 1}
      {MODELNAME kernel_attention_mac_muladd_3ns_8ns_8ns_10_4_1 RTLNAME kernel_attention_mac_muladd_3ns_8ns_8ns_10_4_1 BINDTYPE op TYPE all IMPL dsp48 LATENCY 3 ALLOW_PRAGMA 1}
    }
  }
  {SRCNAME compute_skip_Pipeline_VITIS_LOOP_584_3 MODELNAME compute_skip_Pipeline_VITIS_LOOP_584_3 RTLNAME kernel_attention_compute_skip_Pipeline_VITIS_LOOP_584_3
    SUBMODULES {
      {MODELNAME kernel_attention_mul_3ns_8ns_10_1_1 RTLNAME kernel_attention_mul_3ns_8ns_10_1_1 BINDTYPE op TYPE mul IMPL auto LATENCY 0 ALLOW_PRAGMA 1}
    }
  }
  {SRCNAME compute_skip MODELNAME compute_skip RTLNAME kernel_attention_compute_skip
    SUBMODULES {
      {MODELNAME kernel_attention_mul_8ns_7ns_14_1_1 RTLNAME kernel_attention_mul_8ns_7ns_14_1_1 BINDTYPE op TYPE mul IMPL auto LATENCY 0 ALLOW_PRAGMA 1}
    }
  }
  {SRCNAME get_qk MODELNAME get_qk RTLNAME kernel_attention_get_qk
    SUBMODULES {
      {MODELNAME kernel_attention_mul_3ns_13ns_14_1_1 RTLNAME kernel_attention_mul_3ns_13ns_14_1_1 BINDTYPE op TYPE mul IMPL auto LATENCY 0 ALLOW_PRAGMA 1}
      {MODELNAME kernel_attention_mac_muladd_3ns_13ns_14ns_15_4_1 RTLNAME kernel_attention_mac_muladd_3ns_13ns_14ns_15_4_1 BINDTYPE op TYPE all IMPL dsp48 LATENCY 3 ALLOW_PRAGMA 1}
      {MODELNAME kernel_attention_mac_muladd_3ns_10ns_14ns_14_4_1 RTLNAME kernel_attention_mac_muladd_3ns_10ns_14ns_14_4_1 BINDTYPE op TYPE all IMPL dsp48 LATENCY 3 ALLOW_PRAGMA 1}
      {MODELNAME kernel_attention_mac_muladd_5ns_6ns_14ns_14_4_1 RTLNAME kernel_attention_mac_muladd_5ns_6ns_14ns_14_4_1 BINDTYPE op TYPE all IMPL dsp48 LATENCY 3 ALLOW_PRAGMA 1}
    }
  }
  {SRCNAME compute_multiplication_Pipeline_VITIS_LOOP_207_4 MODELNAME compute_multiplication_Pipeline_VITIS_LOOP_207_4 RTLNAME kernel_attention_compute_multiplication_Pipeline_VITIS_LOOP_207_4
    SUBMODULES {
      {MODELNAME kernel_attention_ama_addmuladd_6ns_10ns_6ns_6ns_16_4_1 RTLNAME kernel_attention_ama_addmuladd_6ns_10ns_6ns_6ns_16_4_1 BINDTYPE op TYPE all IMPL dsp48 LATENCY 3 ALLOW_PRAGMA 1}
    }
  }
  {SRCNAME compute_multiplication MODELNAME compute_multiplication RTLNAME kernel_attention_compute_multiplication
    SUBMODULES {
      {MODELNAME kernel_attention_mul_4ns_6ns_10_1_1 RTLNAME kernel_attention_mul_4ns_6ns_10_1_1 BINDTYPE op TYPE mul IMPL auto LATENCY 0 ALLOW_PRAGMA 1}
      {MODELNAME kernel_attention_mac_muladd_4ns_6ns_6ns_10_4_1 RTLNAME kernel_attention_mac_muladd_4ns_6ns_6ns_10_4_1 BINDTYPE op TYPE all IMPL dsp48 LATENCY 3 ALLOW_PRAGMA 1}
      {MODELNAME kernel_attention_mul_mul_10ns_6ns_16_4_1 RTLNAME kernel_attention_mul_mul_10ns_6ns_16_4_1 BINDTYPE op TYPE all IMPL dsp48 LATENCY 3 ALLOW_PRAGMA 1}
    }
  }
  {SRCNAME pow_generic<double> MODELNAME pow_generic_double_s RTLNAME kernel_attention_pow_generic_double_s
    SUBMODULES {
      {MODELNAME kernel_attention_mul_54s_67ns_120_1_1 RTLNAME kernel_attention_mul_54s_67ns_120_1_1 BINDTYPE op TYPE mul IMPL auto LATENCY 0 ALLOW_PRAGMA 1}
      {MODELNAME kernel_attention_mul_13s_71s_71_1_1 RTLNAME kernel_attention_mul_13s_71s_71_1_1 BINDTYPE op TYPE mul IMPL auto LATENCY 0 ALLOW_PRAGMA 1}
      {MODELNAME kernel_attention_mul_43ns_36ns_79_1_1 RTLNAME kernel_attention_mul_43ns_36ns_79_1_1 BINDTYPE op TYPE mul IMPL auto LATENCY 0 ALLOW_PRAGMA 1}
      {MODELNAME kernel_attention_mul_49ns_44ns_93_1_1 RTLNAME kernel_attention_mul_49ns_44ns_93_1_1 BINDTYPE op TYPE mul IMPL auto LATENCY 0 ALLOW_PRAGMA 1}
      {MODELNAME kernel_attention_mul_50ns_50ns_100_1_1 RTLNAME kernel_attention_mul_50ns_50ns_100_1_1 BINDTYPE op TYPE mul IMPL auto LATENCY 0 ALLOW_PRAGMA 1}
      {MODELNAME kernel_attention_mac_muladd_16s_15ns_19s_31_4_1 RTLNAME kernel_attention_mac_muladd_16s_15ns_19s_31_4_1 BINDTYPE op TYPE all IMPL dsp48 LATENCY 3 ALLOW_PRAGMA 1}
      {MODELNAME kernel_attention_pow_generic_double_s_pow_reduce_anonymous_namespace_table_exp_Z1_ap_ufixed_arbkb RTLNAME kernel_attention_pow_generic_double_s_pow_reduce_anonymous_namespace_table_exp_Z1_ap_ufixed_arbkb BINDTYPE storage TYPE rom IMPL auto LATENCY 2 ALLOW_PRAGMA 1}
      {MODELNAME kernel_attention_pow_generic_double_s_pow_reduce_anonymous_namespace_table_f_Z3_ap_ufixed_arracud RTLNAME kernel_attention_pow_generic_double_s_pow_reduce_anonymous_namespace_table_f_Z3_ap_ufixed_arracud BINDTYPE storage TYPE rom IMPL auto LATENCY 2 ALLOW_PRAGMA 1}
      {MODELNAME kernel_attention_pow_generic_double_s_pow_reduce_anonymous_namespace_table_f_Z2_ap_ufixed_arradEe RTLNAME kernel_attention_pow_generic_double_s_pow_reduce_anonymous_namespace_table_f_Z2_ap_ufixed_arradEe BINDTYPE storage TYPE rom IMPL auto LATENCY 2 ALLOW_PRAGMA 1}
    }
  }
  {SRCNAME kernel_attention_Pipeline_VITIS_LOOP_230_1_VITIS_LOOP_232_3_count_sum MODELNAME kernel_attention_Pipeline_VITIS_LOOP_230_1_VITIS_LOOP_232_3_count_sum RTLNAME kernel_attention_kernel_attention_Pipeline_VITIS_LOOP_230_1_VITIS_LOOP_232_3_count_sum
    SUBMODULES {
      {MODELNAME kernel_attention_fdiv_32ns_32ns_32_2_no_dsp_1 RTLNAME kernel_attention_fdiv_32ns_32ns_32_2_no_dsp_1 BINDTYPE op TYPE fdiv IMPL fabric LATENCY 1 ALLOW_PRAGMA 1}
      {MODELNAME kernel_attention_mul_3ns_15ns_15_1_1 RTLNAME kernel_attention_mul_3ns_15ns_15_1_1 BINDTYPE op TYPE mul IMPL auto LATENCY 0 ALLOW_PRAGMA 1}
      {MODELNAME kernel_attention_mul_3ns_13ns_15_1_1 RTLNAME kernel_attention_mul_3ns_13ns_15_1_1 BINDTYPE op TYPE mul IMPL auto LATENCY 0 ALLOW_PRAGMA 1}
      {MODELNAME kernel_attention_mac_muladd_6ns_6ns_15ns_15_4_1 RTLNAME kernel_attention_mac_muladd_6ns_6ns_15ns_15_4_1 BINDTYPE op TYPE all IMPL dsp48 LATENCY 3 ALLOW_PRAGMA 1}
    }
  }
  {SRCNAME kernel_attention_Pipeline_VITIS_LOOP_110_1_VITIS_LOOP_114_3_VITIS_LOOP_116_4_VIT MODELNAME kernel_attention_Pipeline_VITIS_LOOP_110_1_VITIS_LOOP_114_3_VITIS_LOOP_116_4_VIT RTLNAME kernel_attention_kernel_attention_Pipeline_VITIS_LOOP_110_1_VITIS_LOOP_114_3_VITIS_LOOP_116_4_VIT}
  {SRCNAME kernel_attention_Pipeline_VITIS_LOOP_177_1_VITIS_LOOP_181_3_VITIS_LOOP_183_4_VIT MODELNAME kernel_attention_Pipeline_VITIS_LOOP_177_1_VITIS_LOOP_181_3_VITIS_LOOP_183_4_VIT RTLNAME kernel_attention_kernel_attention_Pipeline_VITIS_LOOP_177_1_VITIS_LOOP_181_3_VITIS_LOOP_183_4_VIT
    SUBMODULES {
      {MODELNAME kernel_attention_ama_addmuladd_5ns_6ns_6ns_3ns_12_4_1 RTLNAME kernel_attention_ama_addmuladd_5ns_6ns_6ns_3ns_12_4_1 BINDTYPE op TYPE all IMPL dsp48 LATENCY 3 ALLOW_PRAGMA 1}
    }
  }
  {SRCNAME kernel_attention_Pipeline_VITIS_LOOP_511_1_VITIS_LOOP_515_3_VITIS_LOOP_517_4 MODELNAME kernel_attention_Pipeline_VITIS_LOOP_511_1_VITIS_LOOP_515_3_VITIS_LOOP_517_4 RTLNAME kernel_attention_kernel_attention_Pipeline_VITIS_LOOP_511_1_VITIS_LOOP_515_3_VITIS_LOOP_517_4
    SUBMODULES {
      {MODELNAME kernel_attention_fcmp_32ns_32ns_1_1_no_dsp_1 RTLNAME kernel_attention_fcmp_32ns_32ns_1_1_no_dsp_1 BINDTYPE op TYPE fcmp IMPL auto LATENCY 0 ALLOW_PRAGMA 1}
      {MODELNAME kernel_attention_mul_3ns_15ns_16_1_1 RTLNAME kernel_attention_mul_3ns_15ns_16_1_1 BINDTYPE op TYPE mul IMPL auto LATENCY 0 ALLOW_PRAGMA 1}
      {MODELNAME kernel_attention_mac_muladd_8ns_6ns_16ns_16_4_1 RTLNAME kernel_attention_mac_muladd_8ns_6ns_16ns_16_4_1 BINDTYPE op TYPE all IMPL dsp48 LATENCY 3 ALLOW_PRAGMA 1}
    }
  }
  {SRCNAME kernel_attention_Pipeline_VITIS_LOOP_146_2_VITIS_LOOP_150_4_VITIS_LOOP_152_5_VIT MODELNAME kernel_attention_Pipeline_VITIS_LOOP_146_2_VITIS_LOOP_150_4_VITIS_LOOP_152_5_VIT RTLNAME kernel_attention_kernel_attention_Pipeline_VITIS_LOOP_146_2_VITIS_LOOP_150_4_VITIS_LOOP_152_5_VIT
    SUBMODULES {
      {MODELNAME kernel_attention_mul_8ns_9ns_16_1_1 RTLNAME kernel_attention_mul_8ns_9ns_16_1_1 BINDTYPE op TYPE mul IMPL auto LATENCY 0 ALLOW_PRAGMA 1}
    }
  }
  {SRCNAME kernel_attention_Pipeline_VITIS_LOOP_268_2_VITIS_LOOP_269_3_VITIS_LOOP_270_4 MODELNAME kernel_attention_Pipeline_VITIS_LOOP_268_2_VITIS_LOOP_269_3_VITIS_LOOP_270_4 RTLNAME kernel_attention_kernel_attention_Pipeline_VITIS_LOOP_268_2_VITIS_LOOP_269_3_VITIS_LOOP_270_4}
  {SRCNAME kernel_attention MODELNAME kernel_attention RTLNAME kernel_attention IS_TOP 1
    SUBMODULES {
      {MODELNAME kernel_attention_dsqrt_64ns_64ns_64_5_no_dsp_1 RTLNAME kernel_attention_dsqrt_64ns_64ns_64_5_no_dsp_1 BINDTYPE op TYPE dsqrt IMPL fabric LATENCY 4 ALLOW_PRAGMA 1}
      {MODELNAME kernel_attention_gmem0_m_axi RTLNAME kernel_attention_gmem0_m_axi BINDTYPE interface TYPE adapter IMPL m_axi}
      {MODELNAME kernel_attention_gmem1_m_axi RTLNAME kernel_attention_gmem1_m_axi BINDTYPE interface TYPE adapter IMPL m_axi}
      {MODELNAME kernel_attention_gmem_m_axi RTLNAME kernel_attention_gmem_m_axi BINDTYPE interface TYPE adapter IMPL m_axi}
      {MODELNAME kernel_attention_control_s_axi RTLNAME kernel_attention_control_s_axi BINDTYPE interface TYPE interface_s_axilite}
    }
  }
}
