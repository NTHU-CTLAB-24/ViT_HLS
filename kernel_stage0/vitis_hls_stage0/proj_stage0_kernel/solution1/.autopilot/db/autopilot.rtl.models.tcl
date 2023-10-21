set SynModuleInfo {
  {SRCNAME DW_conv.1.2.3.12.1_Pipeline_In_Channel MODELNAME DW_conv_1_2_3_12_1_Pipeline_In_Channel RTLNAME kernel_stage0_DW_conv_1_2_3_12_1_Pipeline_In_Channel
    SUBMODULES {
      {MODELNAME kernel_stage0_mul_62s_17ns_62_1_1 RTLNAME kernel_stage0_mul_62s_17ns_62_1_1 BINDTYPE op TYPE mul IMPL auto LATENCY 0 ALLOW_PRAGMA 1}
      {MODELNAME kernel_stage0_srem_32ns_3ns_3_36_1 RTLNAME kernel_stage0_srem_32ns_3ns_3_36_1 BINDTYPE op TYPE srem IMPL auto LATENCY 35 ALLOW_PRAGMA 1}
    }
  }
  {SRCNAME DW_conv.1.2.3.12.1 MODELNAME DW_conv_1_2_3_12_1 RTLNAME kernel_stage0_DW_conv_1_2_3_12_1}
  {SRCNAME BatchNorm.4.5.6.7.11.13.1_Pipeline_VITIS_LOOP_16_4 MODELNAME BatchNorm_4_5_6_7_11_13_1_Pipeline_VITIS_LOOP_16_4 RTLNAME kernel_stage0_BatchNorm_4_5_6_7_11_13_1_Pipeline_VITIS_LOOP_16_4
    SUBMODULES {
      {MODELNAME kernel_stage0_fsub_32ns_32ns_32_2_full_dsp_1 RTLNAME kernel_stage0_fsub_32ns_32ns_32_2_full_dsp_1 BINDTYPE op TYPE fsub IMPL fulldsp LATENCY 1 ALLOW_PRAGMA 1}
      {MODELNAME kernel_stage0_fptrunc_64ns_32_1_no_dsp_1 RTLNAME kernel_stage0_fptrunc_64ns_32_1_no_dsp_1 BINDTYPE op TYPE fptrunc IMPL auto LATENCY 0 ALLOW_PRAGMA 1}
      {MODELNAME kernel_stage0_fpext_32ns_64_1_no_dsp_1 RTLNAME kernel_stage0_fpext_32ns_64_1_no_dsp_1 BINDTYPE op TYPE fpext IMPL auto LATENCY 0 ALLOW_PRAGMA 1}
      {MODELNAME kernel_stage0_dmul_64ns_64ns_64_2_max_dsp_1 RTLNAME kernel_stage0_dmul_64ns_64ns_64_2_max_dsp_1 BINDTYPE op TYPE dmul IMPL maxdsp LATENCY 1 ALLOW_PRAGMA 1}
      {MODELNAME kernel_stage0_ddiv_64ns_64ns_64_9_no_dsp_1 RTLNAME kernel_stage0_ddiv_64ns_64ns_64_9_no_dsp_1 BINDTYPE op TYPE ddiv IMPL fabric LATENCY 8 ALLOW_PRAGMA 1}
      {MODELNAME kernel_stage0_flow_control_loop_pipe_sequential_init RTLNAME kernel_stage0_flow_control_loop_pipe_sequential_init BINDTYPE interface TYPE internal_upc_flow_control INSTNAME kernel_stage0_flow_control_loop_pipe_sequential_init_U}
    }
  }
  {SRCNAME BatchNorm.4.5.6.7.11.13.1 MODELNAME BatchNorm_4_5_6_7_11_13_1 RTLNAME kernel_stage0_BatchNorm_4_5_6_7_11_13_1
    SUBMODULES {
      {MODELNAME kernel_stage0_dadd_64ns_64ns_64_2_full_dsp_1 RTLNAME kernel_stage0_dadd_64ns_64ns_64_2_full_dsp_1 BINDTYPE op TYPE dadd IMPL fulldsp LATENCY 1 ALLOW_PRAGMA 1}
      {MODELNAME kernel_stage0_dsqrt_64ns_64ns_64_8_no_dsp_1 RTLNAME kernel_stage0_dsqrt_64ns_64ns_64_8_no_dsp_1 BINDTYPE op TYPE dsqrt IMPL fabric LATENCY 7 ALLOW_PRAGMA 1}
    }
  }
  {SRCNAME DW_conv.1.2.14.1 MODELNAME DW_conv_1_2_14_1 RTLNAME kernel_stage0_DW_conv_1_2_14_1}
  {SRCNAME kernel_stage0_Pipeline_VITIS_LOOP_17_3_VITIS_LOOP_18_4 MODELNAME kernel_stage0_Pipeline_VITIS_LOOP_17_3_VITIS_LOOP_18_4 RTLNAME kernel_stage0_kernel_stage0_Pipeline_VITIS_LOOP_17_3_VITIS_LOOP_18_4}
  {SRCNAME Pointwise_conv.9.10.15.16.1 MODELNAME Pointwise_conv_9_10_15_16_1 RTLNAME kernel_stage0_Pointwise_conv_9_10_15_16_1}
  {SRCNAME kernel_stage0_Pipeline_VITIS_LOOP_7_1 MODELNAME kernel_stage0_Pipeline_VITIS_LOOP_7_1 RTLNAME kernel_stage0_kernel_stage0_Pipeline_VITIS_LOOP_7_1
    SUBMODULES {
      {MODELNAME kernel_stage0_fcmp_32ns_32ns_1_1_no_dsp_1 RTLNAME kernel_stage0_fcmp_32ns_32ns_1_1_no_dsp_1 BINDTYPE op TYPE fcmp IMPL auto LATENCY 0 ALLOW_PRAGMA 1}
    }
  }
  {SRCNAME kernel_stage0_Pipeline_VITIS_LOOP_34_2 MODELNAME kernel_stage0_Pipeline_VITIS_LOOP_34_2 RTLNAME kernel_stage0_kernel_stage0_Pipeline_VITIS_LOOP_34_2
    SUBMODULES {
      {MODELNAME kernel_stage0_dexp_64ns_64ns_64_6_full_dsp_1 RTLNAME kernel_stage0_dexp_64ns_64ns_64_6_full_dsp_1 BINDTYPE op TYPE dexp IMPL fulldsp LATENCY 5 ALLOW_PRAGMA 1}
    }
  }
  {SRCNAME kernel_stage0_Pipeline_VITIS_LOOP_56_3_VITIS_LOOP_57_4 MODELNAME kernel_stage0_Pipeline_VITIS_LOOP_56_3_VITIS_LOOP_57_4 RTLNAME kernel_stage0_kernel_stage0_Pipeline_VITIS_LOOP_56_3_VITIS_LOOP_57_4}
  {SRCNAME kernel_stage0_Pipeline_Output_Channel MODELNAME kernel_stage0_Pipeline_Output_Channel RTLNAME kernel_stage0_kernel_stage0_Pipeline_Output_Channel
    SUBMODULES {
      {MODELNAME kernel_stage0_mac_muladd_5ns_14ns_15s_20_4_1 RTLNAME kernel_stage0_mac_muladd_5ns_14ns_15s_20_4_1 BINDTYPE op TYPE all IMPL dsp48 LATENCY 3 ALLOW_PRAGMA 1}
    }
  }
  {SRCNAME kernel_stage0 MODELNAME kernel_stage0 RTLNAME kernel_stage0 IS_TOP 1
    SUBMODULES {
      {MODELNAME kernel_stage0_fdiv_32ns_32ns_32_5_no_dsp_1 RTLNAME kernel_stage0_fdiv_32ns_32ns_32_5_no_dsp_1 BINDTYPE op TYPE fdiv IMPL fabric LATENCY 4 ALLOW_PRAGMA 1}
      {MODELNAME kernel_stage0_fmul_32ns_32ns_32_2_max_dsp_1 RTLNAME kernel_stage0_fmul_32ns_32ns_32_2_max_dsp_1 BINDTYPE op TYPE fmul IMPL maxdsp LATENCY 1 ALLOW_PRAGMA 1}
      {MODELNAME kernel_stage0_fadd_32ns_32ns_32_2_full_dsp_1 RTLNAME kernel_stage0_fadd_32ns_32ns_32_2_full_dsp_1 BINDTYPE op TYPE fadd IMPL fulldsp LATENCY 1 ALLOW_PRAGMA 1}
      {MODELNAME kernel_stage0_gmem0_m_axi RTLNAME kernel_stage0_gmem0_m_axi BINDTYPE interface TYPE adapter IMPL m_axi}
      {MODELNAME kernel_stage0_gmem_m_axi RTLNAME kernel_stage0_gmem_m_axi BINDTYPE interface TYPE adapter IMPL m_axi}
      {MODELNAME kernel_stage0_gmem1_m_axi RTLNAME kernel_stage0_gmem1_m_axi BINDTYPE interface TYPE adapter IMPL m_axi}
      {MODELNAME kernel_stage0_gmem2_m_axi RTLNAME kernel_stage0_gmem2_m_axi BINDTYPE interface TYPE adapter IMPL m_axi}
      {MODELNAME kernel_stage0_gmem3_m_axi RTLNAME kernel_stage0_gmem3_m_axi BINDTYPE interface TYPE adapter IMPL m_axi}
      {MODELNAME kernel_stage0_control_s_axi RTLNAME kernel_stage0_control_s_axi BINDTYPE interface TYPE interface_s_axilite}
    }
  }
}
