; ModuleID = '/users/student/mr111/cppan22/git_ViT_HLS/ViT_HLS/kernel_stage0/vitis_hls_stage0/proj_stage0_kernel/solution1/.autopilot/db/a.g.ld.5.gdce.bc'
source_filename = "llvm-link"
target datalayout = "e-m:e-i64:64-i128:128-i256:256-i512:512-i1024:1024-i2048:2048-i4096:4096-n8:16:32:64-S128-v16:16-v24:32-v32:32-v48:64-v96:128-v192:256-v256:256-v512:512-v1024:1024"
target triple = "fpga64-xilinx-none"

; Function Attrs: noinline
define void @apatb_kernel_stage0_ir(float* noalias nocapture nonnull readonly %X_data, float* noalias nocapture nonnull readonly %msp_conv_weight, float* noalias nocapture nonnull readonly %msp_conv_bias, float* noalias nocapture nonnull readonly %msp_norm_weight, float* noalias nocapture nonnull readonly %msp_norm_bias, float* noalias nocapture nonnull readonly %msp_norm_running_mean, float* noalias nocapture nonnull readonly %msp_norm_running_var, float* noalias nocapture nonnull readonly %dw_conv_weight, float* noalias nocapture nonnull readonly %norm_1_weight, float* noalias nocapture nonnull readonly %norm_1_bias, float* noalias nocapture nonnull readonly %norm_1_running_mean, float* noalias nocapture nonnull readonly %norm_1_running_var, float* noalias nocapture nonnull readonly %se_conv_reduce_weight, float* noalias nocapture nonnull readonly %se_conv_reduce_bias, float* noalias nocapture nonnull readonly %se_conv_expand_weight, float* noalias nocapture nonnull readonly %se_conv_expand_bias, float* noalias nocapture nonnull readonly %proj_conv_weight, float* noalias nocapture nonnull %Y_msp_conv, float* noalias nocapture nonnull %Y_msp_norm, float* noalias nocapture nonnull %Y_dw_conv, float* noalias nocapture nonnull %Y_dw_norm, float* noalias nocapture nonnull readonly %Y_dw_act, float* noalias nocapture nonnull %Y_mean, float* noalias nocapture nonnull %Y_reduce, float* noalias nocapture nonnull %Y_relu, float* noalias nocapture nonnull %Y_expand, float* noalias nocapture nonnull %Y_sigmoid, float* noalias nocapture nonnull %Y_se, float* noalias nocapture nonnull %Y_proj) local_unnamed_addr #0 {
entry:
  %malloccall = tail call i8* @malloc(i64 602112)
  %X_data_copy = bitcast i8* %malloccall to [150528 x float]*
  %msp_conv_weight_copy = alloca [648 x float], align 512
  %msp_conv_bias_copy = alloca [24 x float], align 512
  %msp_norm_weight_copy = alloca [24 x float], align 512
  %msp_norm_bias_copy = alloca [24 x float], align 512
  %msp_norm_running_mean_copy = alloca [24 x float], align 512
  %msp_norm_running_var_copy = alloca [24 x float], align 512
  %dw_conv_weight_copy = alloca [216 x float], align 512
  %norm_1_weight_copy = alloca [24 x float], align 512
  %norm_1_bias_copy = alloca [24 x float], align 512
  %norm_1_running_mean_copy = alloca [24 x float], align 512
  %norm_1_running_var_copy = alloca [24 x float], align 512
  %se_conv_reduce_weight_copy = alloca [576 x float], align 512
  %se_conv_reduce_bias_copy = alloca [24 x float], align 512
  %se_conv_expand_weight_copy = alloca [576 x float], align 512
  %se_conv_expand_bias_copy = alloca [24 x float], align 512
  %proj_conv_weight_copy = alloca [576 x float], align 512
  %malloccall1 = tail call i8* @malloc(i64 1204224)
  %Y_msp_conv_copy = bitcast i8* %malloccall1 to [301056 x float]*
  %malloccall2 = tail call i8* @malloc(i64 1204224)
  %Y_msp_norm_copy = bitcast i8* %malloccall2 to [301056 x float]*
  %malloccall3 = tail call i8* @malloc(i64 1204224)
  %Y_dw_conv_copy = bitcast i8* %malloccall3 to [301056 x float]*
  %malloccall4 = tail call i8* @malloc(i64 1204224)
  %Y_dw_norm_copy = bitcast i8* %malloccall4 to [301056 x float]*
  %malloccall5 = tail call i8* @malloc(i64 1204224)
  %Y_dw_act_copy = bitcast i8* %malloccall5 to [301056 x float]*
  %Y_mean_copy = alloca [24 x float], align 512
  %Y_reduce_copy = alloca [24 x float], align 512
  %Y_relu_copy = alloca [24 x float], align 512
  %Y_expand_copy = alloca [24 x float], align 512
  %Y_sigmoid_copy = alloca [24 x float], align 512
  %malloccall6 = tail call i8* @malloc(i64 1204224)
  %Y_se_copy = bitcast i8* %malloccall6 to [301056 x float]*
  %malloccall7 = tail call i8* @malloc(i64 1204224)
  %Y_proj_copy = bitcast i8* %malloccall7 to [301056 x float]*
  %0 = bitcast float* %X_data to [150528 x float]*
  %1 = bitcast float* %msp_conv_weight to [648 x float]*
  %2 = bitcast float* %msp_conv_bias to [24 x float]*
  %3 = bitcast float* %msp_norm_weight to [24 x float]*
  %4 = bitcast float* %msp_norm_bias to [24 x float]*
  %5 = bitcast float* %msp_norm_running_mean to [24 x float]*
  %6 = bitcast float* %msp_norm_running_var to [24 x float]*
  %7 = bitcast float* %dw_conv_weight to [216 x float]*
  %8 = bitcast float* %norm_1_weight to [24 x float]*
  %9 = bitcast float* %norm_1_bias to [24 x float]*
  %10 = bitcast float* %norm_1_running_mean to [24 x float]*
  %11 = bitcast float* %norm_1_running_var to [24 x float]*
  %12 = bitcast float* %se_conv_reduce_weight to [576 x float]*
  %13 = bitcast float* %se_conv_reduce_bias to [24 x float]*
  %14 = bitcast float* %se_conv_expand_weight to [576 x float]*
  %15 = bitcast float* %se_conv_expand_bias to [24 x float]*
  %16 = bitcast float* %proj_conv_weight to [576 x float]*
  %17 = bitcast float* %Y_msp_conv to [301056 x float]*
  %18 = bitcast float* %Y_msp_norm to [301056 x float]*
  %19 = bitcast float* %Y_dw_conv to [301056 x float]*
  %20 = bitcast float* %Y_dw_norm to [301056 x float]*
  %21 = bitcast float* %Y_dw_act to [301056 x float]*
  %22 = bitcast float* %Y_mean to [24 x float]*
  %23 = bitcast float* %Y_reduce to [24 x float]*
  %24 = bitcast float* %Y_relu to [24 x float]*
  %25 = bitcast float* %Y_expand to [24 x float]*
  %26 = bitcast float* %Y_sigmoid to [24 x float]*
  %27 = bitcast float* %Y_se to [301056 x float]*
  %28 = bitcast float* %Y_proj to [301056 x float]*
  call fastcc void @copy_in([150528 x float]* nonnull %0, [150528 x float]* %X_data_copy, [648 x float]* nonnull %1, [648 x float]* nonnull align 512 %msp_conv_weight_copy, [24 x float]* nonnull %2, [24 x float]* nonnull align 512 %msp_conv_bias_copy, [24 x float]* nonnull %3, [24 x float]* nonnull align 512 %msp_norm_weight_copy, [24 x float]* nonnull %4, [24 x float]* nonnull align 512 %msp_norm_bias_copy, [24 x float]* nonnull %5, [24 x float]* nonnull align 512 %msp_norm_running_mean_copy, [24 x float]* nonnull %6, [24 x float]* nonnull align 512 %msp_norm_running_var_copy, [216 x float]* nonnull %7, [216 x float]* nonnull align 512 %dw_conv_weight_copy, [24 x float]* nonnull %8, [24 x float]* nonnull align 512 %norm_1_weight_copy, [24 x float]* nonnull %9, [24 x float]* nonnull align 512 %norm_1_bias_copy, [24 x float]* nonnull %10, [24 x float]* nonnull align 512 %norm_1_running_mean_copy, [24 x float]* nonnull %11, [24 x float]* nonnull align 512 %norm_1_running_var_copy, [576 x float]* nonnull %12, [576 x float]* nonnull align 512 %se_conv_reduce_weight_copy, [24 x float]* nonnull %13, [24 x float]* nonnull align 512 %se_conv_reduce_bias_copy, [576 x float]* nonnull %14, [576 x float]* nonnull align 512 %se_conv_expand_weight_copy, [24 x float]* nonnull %15, [24 x float]* nonnull align 512 %se_conv_expand_bias_copy, [576 x float]* nonnull %16, [576 x float]* nonnull align 512 %proj_conv_weight_copy, [301056 x float]* nonnull %17, [301056 x float]* %Y_msp_conv_copy, [301056 x float]* nonnull %18, [301056 x float]* %Y_msp_norm_copy, [301056 x float]* nonnull %19, [301056 x float]* %Y_dw_conv_copy, [301056 x float]* nonnull %20, [301056 x float]* %Y_dw_norm_copy, [301056 x float]* nonnull %21, [301056 x float]* %Y_dw_act_copy, [24 x float]* nonnull %22, [24 x float]* nonnull align 512 %Y_mean_copy, [24 x float]* nonnull %23, [24 x float]* nonnull align 512 %Y_reduce_copy, [24 x float]* nonnull %24, [24 x float]* nonnull align 512 %Y_relu_copy, [24 x float]* nonnull %25, [24 x float]* nonnull align 512 %Y_expand_copy, [24 x float]* nonnull %26, [24 x float]* nonnull align 512 %Y_sigmoid_copy, [301056 x float]* nonnull %27, [301056 x float]* %Y_se_copy, [301056 x float]* nonnull %28, [301056 x float]* %Y_proj_copy)
  %29 = getelementptr inbounds [150528 x float], [150528 x float]* %X_data_copy, i32 0, i32 0
  %30 = getelementptr inbounds [648 x float], [648 x float]* %msp_conv_weight_copy, i32 0, i32 0
  %31 = getelementptr inbounds [24 x float], [24 x float]* %msp_conv_bias_copy, i32 0, i32 0
  %32 = getelementptr inbounds [24 x float], [24 x float]* %msp_norm_weight_copy, i32 0, i32 0
  %33 = getelementptr inbounds [24 x float], [24 x float]* %msp_norm_bias_copy, i32 0, i32 0
  %34 = getelementptr inbounds [24 x float], [24 x float]* %msp_norm_running_mean_copy, i32 0, i32 0
  %35 = getelementptr inbounds [24 x float], [24 x float]* %msp_norm_running_var_copy, i32 0, i32 0
  %36 = getelementptr inbounds [216 x float], [216 x float]* %dw_conv_weight_copy, i32 0, i32 0
  %37 = getelementptr inbounds [24 x float], [24 x float]* %norm_1_weight_copy, i32 0, i32 0
  %38 = getelementptr inbounds [24 x float], [24 x float]* %norm_1_bias_copy, i32 0, i32 0
  %39 = getelementptr inbounds [24 x float], [24 x float]* %norm_1_running_mean_copy, i32 0, i32 0
  %40 = getelementptr inbounds [24 x float], [24 x float]* %norm_1_running_var_copy, i32 0, i32 0
  %41 = getelementptr inbounds [576 x float], [576 x float]* %se_conv_reduce_weight_copy, i32 0, i32 0
  %42 = getelementptr inbounds [24 x float], [24 x float]* %se_conv_reduce_bias_copy, i32 0, i32 0
  %43 = getelementptr inbounds [576 x float], [576 x float]* %se_conv_expand_weight_copy, i32 0, i32 0
  %44 = getelementptr inbounds [24 x float], [24 x float]* %se_conv_expand_bias_copy, i32 0, i32 0
  %45 = getelementptr inbounds [576 x float], [576 x float]* %proj_conv_weight_copy, i32 0, i32 0
  %46 = getelementptr inbounds [301056 x float], [301056 x float]* %Y_msp_conv_copy, i32 0, i32 0
  %47 = getelementptr inbounds [301056 x float], [301056 x float]* %Y_msp_norm_copy, i32 0, i32 0
  %48 = getelementptr inbounds [301056 x float], [301056 x float]* %Y_dw_conv_copy, i32 0, i32 0
  %49 = getelementptr inbounds [301056 x float], [301056 x float]* %Y_dw_norm_copy, i32 0, i32 0
  %50 = getelementptr inbounds [301056 x float], [301056 x float]* %Y_dw_act_copy, i32 0, i32 0
  %51 = getelementptr inbounds [24 x float], [24 x float]* %Y_mean_copy, i32 0, i32 0
  %52 = getelementptr inbounds [24 x float], [24 x float]* %Y_reduce_copy, i32 0, i32 0
  %53 = getelementptr inbounds [24 x float], [24 x float]* %Y_relu_copy, i32 0, i32 0
  %54 = getelementptr inbounds [24 x float], [24 x float]* %Y_expand_copy, i32 0, i32 0
  %55 = getelementptr inbounds [24 x float], [24 x float]* %Y_sigmoid_copy, i32 0, i32 0
  %56 = getelementptr inbounds [301056 x float], [301056 x float]* %Y_se_copy, i32 0, i32 0
  %57 = getelementptr inbounds [301056 x float], [301056 x float]* %Y_proj_copy, i32 0, i32 0
  call void @apatb_kernel_stage0_hw(float* %29, float* %30, float* %31, float* %32, float* %33, float* %34, float* %35, float* %36, float* %37, float* %38, float* %39, float* %40, float* %41, float* %42, float* %43, float* %44, float* %45, float* %46, float* %47, float* %48, float* %49, float* %50, float* %51, float* %52, float* %53, float* %54, float* %55, float* %56, float* %57)
  call void @copy_back([150528 x float]* %0, [150528 x float]* %X_data_copy, [648 x float]* %1, [648 x float]* %msp_conv_weight_copy, [24 x float]* %2, [24 x float]* %msp_conv_bias_copy, [24 x float]* %3, [24 x float]* %msp_norm_weight_copy, [24 x float]* %4, [24 x float]* %msp_norm_bias_copy, [24 x float]* %5, [24 x float]* %msp_norm_running_mean_copy, [24 x float]* %6, [24 x float]* %msp_norm_running_var_copy, [216 x float]* %7, [216 x float]* %dw_conv_weight_copy, [24 x float]* %8, [24 x float]* %norm_1_weight_copy, [24 x float]* %9, [24 x float]* %norm_1_bias_copy, [24 x float]* %10, [24 x float]* %norm_1_running_mean_copy, [24 x float]* %11, [24 x float]* %norm_1_running_var_copy, [576 x float]* %12, [576 x float]* %se_conv_reduce_weight_copy, [24 x float]* %13, [24 x float]* %se_conv_reduce_bias_copy, [576 x float]* %14, [576 x float]* %se_conv_expand_weight_copy, [24 x float]* %15, [24 x float]* %se_conv_expand_bias_copy, [576 x float]* %16, [576 x float]* %proj_conv_weight_copy, [301056 x float]* %17, [301056 x float]* %Y_msp_conv_copy, [301056 x float]* %18, [301056 x float]* %Y_msp_norm_copy, [301056 x float]* %19, [301056 x float]* %Y_dw_conv_copy, [301056 x float]* %20, [301056 x float]* %Y_dw_norm_copy, [301056 x float]* %21, [301056 x float]* %Y_dw_act_copy, [24 x float]* %22, [24 x float]* %Y_mean_copy, [24 x float]* %23, [24 x float]* %Y_reduce_copy, [24 x float]* %24, [24 x float]* %Y_relu_copy, [24 x float]* %25, [24 x float]* %Y_expand_copy, [24 x float]* %26, [24 x float]* %Y_sigmoid_copy, [301056 x float]* %27, [301056 x float]* %Y_se_copy, [301056 x float]* %28, [301056 x float]* %Y_proj_copy)
  tail call void @free(i8* %malloccall)
  tail call void @free(i8* %malloccall1)
  tail call void @free(i8* %malloccall2)
  tail call void @free(i8* %malloccall3)
  tail call void @free(i8* %malloccall4)
  tail call void @free(i8* %malloccall5)
  tail call void @free(i8* %malloccall6)
  tail call void @free(i8* %malloccall7)
  ret void
}

declare noalias i8* @malloc(i64) local_unnamed_addr

; Function Attrs: argmemonly noinline norecurse
define internal fastcc void @copy_in([150528 x float]* noalias readonly, [150528 x float]* noalias, [648 x float]* noalias readonly, [648 x float]* noalias align 512, [24 x float]* noalias readonly, [24 x float]* noalias align 512, [24 x float]* noalias readonly, [24 x float]* noalias align 512, [24 x float]* noalias readonly, [24 x float]* noalias align 512, [24 x float]* noalias readonly, [24 x float]* noalias align 512, [24 x float]* noalias readonly, [24 x float]* noalias align 512, [216 x float]* noalias readonly, [216 x float]* noalias align 512, [24 x float]* noalias readonly, [24 x float]* noalias align 512, [24 x float]* noalias readonly, [24 x float]* noalias align 512, [24 x float]* noalias readonly, [24 x float]* noalias align 512, [24 x float]* noalias readonly, [24 x float]* noalias align 512, [576 x float]* noalias readonly, [576 x float]* noalias align 512, [24 x float]* noalias readonly, [24 x float]* noalias align 512, [576 x float]* noalias readonly, [576 x float]* noalias align 512, [24 x float]* noalias readonly, [24 x float]* noalias align 512, [576 x float]* noalias readonly, [576 x float]* noalias align 512, [301056 x float]* noalias readonly, [301056 x float]* noalias, [301056 x float]* noalias readonly, [301056 x float]* noalias, [301056 x float]* noalias readonly, [301056 x float]* noalias, [301056 x float]* noalias readonly, [301056 x float]* noalias, [301056 x float]* noalias readonly, [301056 x float]* noalias, [24 x float]* noalias readonly, [24 x float]* noalias align 512, [24 x float]* noalias readonly, [24 x float]* noalias align 512, [24 x float]* noalias readonly, [24 x float]* noalias align 512, [24 x float]* noalias readonly, [24 x float]* noalias align 512, [24 x float]* noalias readonly, [24 x float]* noalias align 512, [301056 x float]* noalias readonly, [301056 x float]* noalias, [301056 x float]* noalias readonly, [301056 x float]* noalias) unnamed_addr #1 {
entry:
  call fastcc void @onebyonecpy_hls.p0a150528f32([150528 x float]* %1, [150528 x float]* %0)
  call fastcc void @onebyonecpy_hls.p0a648f32([648 x float]* align 512 %3, [648 x float]* %2)
  call fastcc void @onebyonecpy_hls.p0a24f32([24 x float]* align 512 %5, [24 x float]* %4)
  call fastcc void @onebyonecpy_hls.p0a24f32([24 x float]* align 512 %7, [24 x float]* %6)
  call fastcc void @onebyonecpy_hls.p0a24f32([24 x float]* align 512 %9, [24 x float]* %8)
  call fastcc void @onebyonecpy_hls.p0a24f32([24 x float]* align 512 %11, [24 x float]* %10)
  call fastcc void @onebyonecpy_hls.p0a24f32([24 x float]* align 512 %13, [24 x float]* %12)
  call fastcc void @onebyonecpy_hls.p0a216f32([216 x float]* align 512 %15, [216 x float]* %14)
  call fastcc void @onebyonecpy_hls.p0a24f32([24 x float]* align 512 %17, [24 x float]* %16)
  call fastcc void @onebyonecpy_hls.p0a24f32([24 x float]* align 512 %19, [24 x float]* %18)
  call fastcc void @onebyonecpy_hls.p0a24f32([24 x float]* align 512 %21, [24 x float]* %20)
  call fastcc void @onebyonecpy_hls.p0a24f32([24 x float]* align 512 %23, [24 x float]* %22)
  call fastcc void @onebyonecpy_hls.p0a576f32([576 x float]* align 512 %25, [576 x float]* %24)
  call fastcc void @onebyonecpy_hls.p0a24f32([24 x float]* align 512 %27, [24 x float]* %26)
  call fastcc void @onebyonecpy_hls.p0a576f32([576 x float]* align 512 %29, [576 x float]* %28)
  call fastcc void @onebyonecpy_hls.p0a24f32([24 x float]* align 512 %31, [24 x float]* %30)
  call fastcc void @onebyonecpy_hls.p0a576f32([576 x float]* align 512 %33, [576 x float]* %32)
  call fastcc void @onebyonecpy_hls.p0a301056f32([301056 x float]* %35, [301056 x float]* %34)
  call fastcc void @onebyonecpy_hls.p0a301056f32([301056 x float]* %37, [301056 x float]* %36)
  call fastcc void @onebyonecpy_hls.p0a301056f32([301056 x float]* %39, [301056 x float]* %38)
  call fastcc void @onebyonecpy_hls.p0a301056f32([301056 x float]* %41, [301056 x float]* %40)
  call fastcc void @onebyonecpy_hls.p0a301056f32([301056 x float]* %43, [301056 x float]* %42)
  call fastcc void @onebyonecpy_hls.p0a24f32([24 x float]* align 512 %45, [24 x float]* %44)
  call fastcc void @onebyonecpy_hls.p0a24f32([24 x float]* align 512 %47, [24 x float]* %46)
  call fastcc void @onebyonecpy_hls.p0a24f32([24 x float]* align 512 %49, [24 x float]* %48)
  call fastcc void @onebyonecpy_hls.p0a24f32([24 x float]* align 512 %51, [24 x float]* %50)
  call fastcc void @onebyonecpy_hls.p0a24f32([24 x float]* align 512 %53, [24 x float]* %52)
  call fastcc void @onebyonecpy_hls.p0a301056f32([301056 x float]* %55, [301056 x float]* %54)
  call fastcc void @onebyonecpy_hls.p0a301056f32([301056 x float]* %57, [301056 x float]* %56)
  ret void
}

; Function Attrs: argmemonly noinline norecurse
define internal fastcc void @onebyonecpy_hls.p0a150528f32([150528 x float]* noalias, [150528 x float]* noalias readonly) unnamed_addr #2 {
entry:
  %2 = icmp eq [150528 x float]* %0, null
  %3 = icmp eq [150528 x float]* %1, null
  %4 = or i1 %2, %3
  br i1 %4, label %ret, label %copy

copy:                                             ; preds = %entry
  br label %for.loop

for.loop:                                         ; preds = %for.loop, %copy
  %for.loop.idx1 = phi i64 [ 0, %copy ], [ %for.loop.idx.next, %for.loop ]
  %dst.addr = getelementptr [150528 x float], [150528 x float]* %0, i64 0, i64 %for.loop.idx1
  %src.addr = getelementptr [150528 x float], [150528 x float]* %1, i64 0, i64 %for.loop.idx1
  %5 = load float, float* %src.addr, align 4
  store float %5, float* %dst.addr, align 4
  %for.loop.idx.next = add nuw nsw i64 %for.loop.idx1, 1
  %exitcond = icmp ne i64 %for.loop.idx.next, 150528
  br i1 %exitcond, label %for.loop, label %ret

ret:                                              ; preds = %for.loop, %entry
  ret void
}

; Function Attrs: argmemonly noinline norecurse
define internal fastcc void @onebyonecpy_hls.p0a648f32([648 x float]* noalias align 512, [648 x float]* noalias readonly) unnamed_addr #2 {
entry:
  %2 = icmp eq [648 x float]* %0, null
  %3 = icmp eq [648 x float]* %1, null
  %4 = or i1 %2, %3
  br i1 %4, label %ret, label %copy

copy:                                             ; preds = %entry
  br label %for.loop

for.loop:                                         ; preds = %for.loop, %copy
  %for.loop.idx1 = phi i64 [ 0, %copy ], [ %for.loop.idx.next, %for.loop ]
  %dst.addr = getelementptr [648 x float], [648 x float]* %0, i64 0, i64 %for.loop.idx1
  %src.addr = getelementptr [648 x float], [648 x float]* %1, i64 0, i64 %for.loop.idx1
  %5 = load float, float* %src.addr, align 4
  store float %5, float* %dst.addr, align 4
  %for.loop.idx.next = add nuw nsw i64 %for.loop.idx1, 1
  %exitcond = icmp ne i64 %for.loop.idx.next, 648
  br i1 %exitcond, label %for.loop, label %ret

ret:                                              ; preds = %for.loop, %entry
  ret void
}

; Function Attrs: argmemonly noinline norecurse
define internal fastcc void @onebyonecpy_hls.p0a24f32([24 x float]* noalias align 512, [24 x float]* noalias readonly) unnamed_addr #2 {
entry:
  %2 = icmp eq [24 x float]* %0, null
  %3 = icmp eq [24 x float]* %1, null
  %4 = or i1 %2, %3
  br i1 %4, label %ret, label %copy

copy:                                             ; preds = %entry
  br label %for.loop

for.loop:                                         ; preds = %for.loop, %copy
  %for.loop.idx1 = phi i64 [ 0, %copy ], [ %for.loop.idx.next, %for.loop ]
  %dst.addr = getelementptr [24 x float], [24 x float]* %0, i64 0, i64 %for.loop.idx1
  %src.addr = getelementptr [24 x float], [24 x float]* %1, i64 0, i64 %for.loop.idx1
  %5 = load float, float* %src.addr, align 4
  store float %5, float* %dst.addr, align 4
  %for.loop.idx.next = add nuw nsw i64 %for.loop.idx1, 1
  %exitcond = icmp ne i64 %for.loop.idx.next, 24
  br i1 %exitcond, label %for.loop, label %ret

ret:                                              ; preds = %for.loop, %entry
  ret void
}

; Function Attrs: argmemonly noinline norecurse
define internal fastcc void @onebyonecpy_hls.p0a216f32([216 x float]* noalias align 512, [216 x float]* noalias readonly) unnamed_addr #2 {
entry:
  %2 = icmp eq [216 x float]* %0, null
  %3 = icmp eq [216 x float]* %1, null
  %4 = or i1 %2, %3
  br i1 %4, label %ret, label %copy

copy:                                             ; preds = %entry
  br label %for.loop

for.loop:                                         ; preds = %for.loop, %copy
  %for.loop.idx1 = phi i64 [ 0, %copy ], [ %for.loop.idx.next, %for.loop ]
  %dst.addr = getelementptr [216 x float], [216 x float]* %0, i64 0, i64 %for.loop.idx1
  %src.addr = getelementptr [216 x float], [216 x float]* %1, i64 0, i64 %for.loop.idx1
  %5 = load float, float* %src.addr, align 4
  store float %5, float* %dst.addr, align 4
  %for.loop.idx.next = add nuw nsw i64 %for.loop.idx1, 1
  %exitcond = icmp ne i64 %for.loop.idx.next, 216
  br i1 %exitcond, label %for.loop, label %ret

ret:                                              ; preds = %for.loop, %entry
  ret void
}

; Function Attrs: argmemonly noinline norecurse
define internal fastcc void @onebyonecpy_hls.p0a576f32([576 x float]* noalias align 512, [576 x float]* noalias readonly) unnamed_addr #2 {
entry:
  %2 = icmp eq [576 x float]* %0, null
  %3 = icmp eq [576 x float]* %1, null
  %4 = or i1 %2, %3
  br i1 %4, label %ret, label %copy

copy:                                             ; preds = %entry
  br label %for.loop

for.loop:                                         ; preds = %for.loop, %copy
  %for.loop.idx1 = phi i64 [ 0, %copy ], [ %for.loop.idx.next, %for.loop ]
  %dst.addr = getelementptr [576 x float], [576 x float]* %0, i64 0, i64 %for.loop.idx1
  %src.addr = getelementptr [576 x float], [576 x float]* %1, i64 0, i64 %for.loop.idx1
  %5 = load float, float* %src.addr, align 4
  store float %5, float* %dst.addr, align 4
  %for.loop.idx.next = add nuw nsw i64 %for.loop.idx1, 1
  %exitcond = icmp ne i64 %for.loop.idx.next, 576
  br i1 %exitcond, label %for.loop, label %ret

ret:                                              ; preds = %for.loop, %entry
  ret void
}

; Function Attrs: argmemonly noinline norecurse
define internal fastcc void @onebyonecpy_hls.p0a301056f32([301056 x float]* noalias, [301056 x float]* noalias readonly) unnamed_addr #2 {
entry:
  %2 = icmp eq [301056 x float]* %0, null
  %3 = icmp eq [301056 x float]* %1, null
  %4 = or i1 %2, %3
  br i1 %4, label %ret, label %copy

copy:                                             ; preds = %entry
  br label %for.loop

for.loop:                                         ; preds = %for.loop, %copy
  %for.loop.idx1 = phi i64 [ 0, %copy ], [ %for.loop.idx.next, %for.loop ]
  %dst.addr = getelementptr [301056 x float], [301056 x float]* %0, i64 0, i64 %for.loop.idx1
  %src.addr = getelementptr [301056 x float], [301056 x float]* %1, i64 0, i64 %for.loop.idx1
  %5 = load float, float* %src.addr, align 4
  store float %5, float* %dst.addr, align 4
  %for.loop.idx.next = add nuw nsw i64 %for.loop.idx1, 1
  %exitcond = icmp ne i64 %for.loop.idx.next, 301056
  br i1 %exitcond, label %for.loop, label %ret

ret:                                              ; preds = %for.loop, %entry
  ret void
}

; Function Attrs: argmemonly noinline norecurse
define internal fastcc void @copy_out([150528 x float]* noalias, [150528 x float]* noalias readonly, [648 x float]* noalias, [648 x float]* noalias readonly align 512, [24 x float]* noalias, [24 x float]* noalias readonly align 512, [24 x float]* noalias, [24 x float]* noalias readonly align 512, [24 x float]* noalias, [24 x float]* noalias readonly align 512, [24 x float]* noalias, [24 x float]* noalias readonly align 512, [24 x float]* noalias, [24 x float]* noalias readonly align 512, [216 x float]* noalias, [216 x float]* noalias readonly align 512, [24 x float]* noalias, [24 x float]* noalias readonly align 512, [24 x float]* noalias, [24 x float]* noalias readonly align 512, [24 x float]* noalias, [24 x float]* noalias readonly align 512, [24 x float]* noalias, [24 x float]* noalias readonly align 512, [576 x float]* noalias, [576 x float]* noalias readonly align 512, [24 x float]* noalias, [24 x float]* noalias readonly align 512, [576 x float]* noalias, [576 x float]* noalias readonly align 512, [24 x float]* noalias, [24 x float]* noalias readonly align 512, [576 x float]* noalias, [576 x float]* noalias readonly align 512, [301056 x float]* noalias, [301056 x float]* noalias readonly, [301056 x float]* noalias, [301056 x float]* noalias readonly, [301056 x float]* noalias, [301056 x float]* noalias readonly, [301056 x float]* noalias, [301056 x float]* noalias readonly, [301056 x float]* noalias, [301056 x float]* noalias readonly, [24 x float]* noalias, [24 x float]* noalias readonly align 512, [24 x float]* noalias, [24 x float]* noalias readonly align 512, [24 x float]* noalias, [24 x float]* noalias readonly align 512, [24 x float]* noalias, [24 x float]* noalias readonly align 512, [24 x float]* noalias, [24 x float]* noalias readonly align 512, [301056 x float]* noalias, [301056 x float]* noalias readonly, [301056 x float]* noalias, [301056 x float]* noalias readonly) unnamed_addr #3 {
entry:
  call fastcc void @onebyonecpy_hls.p0a150528f32([150528 x float]* %0, [150528 x float]* %1)
  call fastcc void @onebyonecpy_hls.p0a648f32([648 x float]* %2, [648 x float]* align 512 %3)
  call fastcc void @onebyonecpy_hls.p0a24f32([24 x float]* %4, [24 x float]* align 512 %5)
  call fastcc void @onebyonecpy_hls.p0a24f32([24 x float]* %6, [24 x float]* align 512 %7)
  call fastcc void @onebyonecpy_hls.p0a24f32([24 x float]* %8, [24 x float]* align 512 %9)
  call fastcc void @onebyonecpy_hls.p0a24f32([24 x float]* %10, [24 x float]* align 512 %11)
  call fastcc void @onebyonecpy_hls.p0a24f32([24 x float]* %12, [24 x float]* align 512 %13)
  call fastcc void @onebyonecpy_hls.p0a216f32([216 x float]* %14, [216 x float]* align 512 %15)
  call fastcc void @onebyonecpy_hls.p0a24f32([24 x float]* %16, [24 x float]* align 512 %17)
  call fastcc void @onebyonecpy_hls.p0a24f32([24 x float]* %18, [24 x float]* align 512 %19)
  call fastcc void @onebyonecpy_hls.p0a24f32([24 x float]* %20, [24 x float]* align 512 %21)
  call fastcc void @onebyonecpy_hls.p0a24f32([24 x float]* %22, [24 x float]* align 512 %23)
  call fastcc void @onebyonecpy_hls.p0a576f32([576 x float]* %24, [576 x float]* align 512 %25)
  call fastcc void @onebyonecpy_hls.p0a24f32([24 x float]* %26, [24 x float]* align 512 %27)
  call fastcc void @onebyonecpy_hls.p0a576f32([576 x float]* %28, [576 x float]* align 512 %29)
  call fastcc void @onebyonecpy_hls.p0a24f32([24 x float]* %30, [24 x float]* align 512 %31)
  call fastcc void @onebyonecpy_hls.p0a576f32([576 x float]* %32, [576 x float]* align 512 %33)
  call fastcc void @onebyonecpy_hls.p0a301056f32([301056 x float]* %34, [301056 x float]* %35)
  call fastcc void @onebyonecpy_hls.p0a301056f32([301056 x float]* %36, [301056 x float]* %37)
  call fastcc void @onebyonecpy_hls.p0a301056f32([301056 x float]* %38, [301056 x float]* %39)
  call fastcc void @onebyonecpy_hls.p0a301056f32([301056 x float]* %40, [301056 x float]* %41)
  call fastcc void @onebyonecpy_hls.p0a301056f32([301056 x float]* %42, [301056 x float]* %43)
  call fastcc void @onebyonecpy_hls.p0a24f32([24 x float]* %44, [24 x float]* align 512 %45)
  call fastcc void @onebyonecpy_hls.p0a24f32([24 x float]* %46, [24 x float]* align 512 %47)
  call fastcc void @onebyonecpy_hls.p0a24f32([24 x float]* %48, [24 x float]* align 512 %49)
  call fastcc void @onebyonecpy_hls.p0a24f32([24 x float]* %50, [24 x float]* align 512 %51)
  call fastcc void @onebyonecpy_hls.p0a24f32([24 x float]* %52, [24 x float]* align 512 %53)
  call fastcc void @onebyonecpy_hls.p0a301056f32([301056 x float]* %54, [301056 x float]* %55)
  call fastcc void @onebyonecpy_hls.p0a301056f32([301056 x float]* %56, [301056 x float]* %57)
  ret void
}

declare void @free(i8*) local_unnamed_addr

declare void @apatb_kernel_stage0_hw(float*, float*, float*, float*, float*, float*, float*, float*, float*, float*, float*, float*, float*, float*, float*, float*, float*, float*, float*, float*, float*, float*, float*, float*, float*, float*, float*, float*, float*)

; Function Attrs: argmemonly noinline norecurse
define internal fastcc void @copy_back([150528 x float]* noalias, [150528 x float]* noalias readonly, [648 x float]* noalias, [648 x float]* noalias readonly align 512, [24 x float]* noalias, [24 x float]* noalias readonly align 512, [24 x float]* noalias, [24 x float]* noalias readonly align 512, [24 x float]* noalias, [24 x float]* noalias readonly align 512, [24 x float]* noalias, [24 x float]* noalias readonly align 512, [24 x float]* noalias, [24 x float]* noalias readonly align 512, [216 x float]* noalias, [216 x float]* noalias readonly align 512, [24 x float]* noalias, [24 x float]* noalias readonly align 512, [24 x float]* noalias, [24 x float]* noalias readonly align 512, [24 x float]* noalias, [24 x float]* noalias readonly align 512, [24 x float]* noalias, [24 x float]* noalias readonly align 512, [576 x float]* noalias, [576 x float]* noalias readonly align 512, [24 x float]* noalias, [24 x float]* noalias readonly align 512, [576 x float]* noalias, [576 x float]* noalias readonly align 512, [24 x float]* noalias, [24 x float]* noalias readonly align 512, [576 x float]* noalias, [576 x float]* noalias readonly align 512, [301056 x float]* noalias, [301056 x float]* noalias readonly, [301056 x float]* noalias, [301056 x float]* noalias readonly, [301056 x float]* noalias, [301056 x float]* noalias readonly, [301056 x float]* noalias, [301056 x float]* noalias readonly, [301056 x float]* noalias, [301056 x float]* noalias readonly, [24 x float]* noalias, [24 x float]* noalias readonly align 512, [24 x float]* noalias, [24 x float]* noalias readonly align 512, [24 x float]* noalias, [24 x float]* noalias readonly align 512, [24 x float]* noalias, [24 x float]* noalias readonly align 512, [24 x float]* noalias, [24 x float]* noalias readonly align 512, [301056 x float]* noalias, [301056 x float]* noalias readonly, [301056 x float]* noalias, [301056 x float]* noalias readonly) unnamed_addr #3 {
entry:
  call fastcc void @onebyonecpy_hls.p0a301056f32([301056 x float]* %34, [301056 x float]* %35)
  call fastcc void @onebyonecpy_hls.p0a301056f32([301056 x float]* %36, [301056 x float]* %37)
  call fastcc void @onebyonecpy_hls.p0a301056f32([301056 x float]* %38, [301056 x float]* %39)
  call fastcc void @onebyonecpy_hls.p0a301056f32([301056 x float]* %40, [301056 x float]* %41)
  call fastcc void @onebyonecpy_hls.p0a24f32([24 x float]* %44, [24 x float]* align 512 %45)
  call fastcc void @onebyonecpy_hls.p0a24f32([24 x float]* %46, [24 x float]* align 512 %47)
  call fastcc void @onebyonecpy_hls.p0a24f32([24 x float]* %48, [24 x float]* align 512 %49)
  call fastcc void @onebyonecpy_hls.p0a24f32([24 x float]* %50, [24 x float]* align 512 %51)
  call fastcc void @onebyonecpy_hls.p0a24f32([24 x float]* %52, [24 x float]* align 512 %53)
  call fastcc void @onebyonecpy_hls.p0a301056f32([301056 x float]* %54, [301056 x float]* %55)
  call fastcc void @onebyonecpy_hls.p0a301056f32([301056 x float]* %56, [301056 x float]* %57)
  ret void
}

define void @kernel_stage0_hw_stub_wrapper(float*, float*, float*, float*, float*, float*, float*, float*, float*, float*, float*, float*, float*, float*, float*, float*, float*, float*, float*, float*, float*, float*, float*, float*, float*, float*, float*, float*, float*) #4 {
entry:
  %29 = bitcast float* %0 to [150528 x float]*
  %30 = bitcast float* %1 to [648 x float]*
  %31 = bitcast float* %2 to [24 x float]*
  %32 = bitcast float* %3 to [24 x float]*
  %33 = bitcast float* %4 to [24 x float]*
  %34 = bitcast float* %5 to [24 x float]*
  %35 = bitcast float* %6 to [24 x float]*
  %36 = bitcast float* %7 to [216 x float]*
  %37 = bitcast float* %8 to [24 x float]*
  %38 = bitcast float* %9 to [24 x float]*
  %39 = bitcast float* %10 to [24 x float]*
  %40 = bitcast float* %11 to [24 x float]*
  %41 = bitcast float* %12 to [576 x float]*
  %42 = bitcast float* %13 to [24 x float]*
  %43 = bitcast float* %14 to [576 x float]*
  %44 = bitcast float* %15 to [24 x float]*
  %45 = bitcast float* %16 to [576 x float]*
  %46 = bitcast float* %17 to [301056 x float]*
  %47 = bitcast float* %18 to [301056 x float]*
  %48 = bitcast float* %19 to [301056 x float]*
  %49 = bitcast float* %20 to [301056 x float]*
  %50 = bitcast float* %21 to [301056 x float]*
  %51 = bitcast float* %22 to [24 x float]*
  %52 = bitcast float* %23 to [24 x float]*
  %53 = bitcast float* %24 to [24 x float]*
  %54 = bitcast float* %25 to [24 x float]*
  %55 = bitcast float* %26 to [24 x float]*
  %56 = bitcast float* %27 to [301056 x float]*
  %57 = bitcast float* %28 to [301056 x float]*
  call void @copy_out([150528 x float]* null, [150528 x float]* %29, [648 x float]* null, [648 x float]* %30, [24 x float]* null, [24 x float]* %31, [24 x float]* null, [24 x float]* %32, [24 x float]* null, [24 x float]* %33, [24 x float]* null, [24 x float]* %34, [24 x float]* null, [24 x float]* %35, [216 x float]* null, [216 x float]* %36, [24 x float]* null, [24 x float]* %37, [24 x float]* null, [24 x float]* %38, [24 x float]* null, [24 x float]* %39, [24 x float]* null, [24 x float]* %40, [576 x float]* null, [576 x float]* %41, [24 x float]* null, [24 x float]* %42, [576 x float]* null, [576 x float]* %43, [24 x float]* null, [24 x float]* %44, [576 x float]* null, [576 x float]* %45, [301056 x float]* null, [301056 x float]* %46, [301056 x float]* null, [301056 x float]* %47, [301056 x float]* null, [301056 x float]* %48, [301056 x float]* null, [301056 x float]* %49, [301056 x float]* null, [301056 x float]* %50, [24 x float]* null, [24 x float]* %51, [24 x float]* null, [24 x float]* %52, [24 x float]* null, [24 x float]* %53, [24 x float]* null, [24 x float]* %54, [24 x float]* null, [24 x float]* %55, [301056 x float]* null, [301056 x float]* %56, [301056 x float]* null, [301056 x float]* %57)
  %58 = bitcast [150528 x float]* %29 to float*
  %59 = bitcast [648 x float]* %30 to float*
  %60 = bitcast [24 x float]* %31 to float*
  %61 = bitcast [24 x float]* %32 to float*
  %62 = bitcast [24 x float]* %33 to float*
  %63 = bitcast [24 x float]* %34 to float*
  %64 = bitcast [24 x float]* %35 to float*
  %65 = bitcast [216 x float]* %36 to float*
  %66 = bitcast [24 x float]* %37 to float*
  %67 = bitcast [24 x float]* %38 to float*
  %68 = bitcast [24 x float]* %39 to float*
  %69 = bitcast [24 x float]* %40 to float*
  %70 = bitcast [576 x float]* %41 to float*
  %71 = bitcast [24 x float]* %42 to float*
  %72 = bitcast [576 x float]* %43 to float*
  %73 = bitcast [24 x float]* %44 to float*
  %74 = bitcast [576 x float]* %45 to float*
  %75 = bitcast [301056 x float]* %46 to float*
  %76 = bitcast [301056 x float]* %47 to float*
  %77 = bitcast [301056 x float]* %48 to float*
  %78 = bitcast [301056 x float]* %49 to float*
  %79 = bitcast [301056 x float]* %50 to float*
  %80 = bitcast [24 x float]* %51 to float*
  %81 = bitcast [24 x float]* %52 to float*
  %82 = bitcast [24 x float]* %53 to float*
  %83 = bitcast [24 x float]* %54 to float*
  %84 = bitcast [24 x float]* %55 to float*
  %85 = bitcast [301056 x float]* %56 to float*
  %86 = bitcast [301056 x float]* %57 to float*
  call void @kernel_stage0_hw_stub(float* %58, float* %59, float* %60, float* %61, float* %62, float* %63, float* %64, float* %65, float* %66, float* %67, float* %68, float* %69, float* %70, float* %71, float* %72, float* %73, float* %74, float* %75, float* %76, float* %77, float* %78, float* %79, float* %80, float* %81, float* %82, float* %83, float* %84, float* %85, float* %86)
  call void @copy_in([150528 x float]* null, [150528 x float]* %29, [648 x float]* null, [648 x float]* %30, [24 x float]* null, [24 x float]* %31, [24 x float]* null, [24 x float]* %32, [24 x float]* null, [24 x float]* %33, [24 x float]* null, [24 x float]* %34, [24 x float]* null, [24 x float]* %35, [216 x float]* null, [216 x float]* %36, [24 x float]* null, [24 x float]* %37, [24 x float]* null, [24 x float]* %38, [24 x float]* null, [24 x float]* %39, [24 x float]* null, [24 x float]* %40, [576 x float]* null, [576 x float]* %41, [24 x float]* null, [24 x float]* %42, [576 x float]* null, [576 x float]* %43, [24 x float]* null, [24 x float]* %44, [576 x float]* null, [576 x float]* %45, [301056 x float]* null, [301056 x float]* %46, [301056 x float]* null, [301056 x float]* %47, [301056 x float]* null, [301056 x float]* %48, [301056 x float]* null, [301056 x float]* %49, [301056 x float]* null, [301056 x float]* %50, [24 x float]* null, [24 x float]* %51, [24 x float]* null, [24 x float]* %52, [24 x float]* null, [24 x float]* %53, [24 x float]* null, [24 x float]* %54, [24 x float]* null, [24 x float]* %55, [301056 x float]* null, [301056 x float]* %56, [301056 x float]* null, [301056 x float]* %57)
  ret void
}

declare void @kernel_stage0_hw_stub(float*, float*, float*, float*, float*, float*, float*, float*, float*, float*, float*, float*, float*, float*, float*, float*, float*, float*, float*, float*, float*, float*, float*, float*, float*, float*, float*, float*, float*)

attributes #0 = { noinline "fpga.wrapper.func"="wrapper" }
attributes #1 = { argmemonly noinline norecurse "fpga.wrapper.func"="copyin" }
attributes #2 = { argmemonly noinline norecurse "fpga.wrapper.func"="onebyonecpy_hls" }
attributes #3 = { argmemonly noinline norecurse "fpga.wrapper.func"="copyout" }
attributes #4 = { "fpga.wrapper.func"="stub" }

!llvm.dbg.cu = !{}
!llvm.ident = !{!0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0}
!llvm.module.flags = !{!1, !2, !3}
!blackbox_cfg = !{!4}

!0 = !{!"clang version 7.0.0 "}
!1 = !{i32 2, !"Dwarf Version", i32 4}
!2 = !{i32 2, !"Debug Info Version", i32 3}
!3 = !{i32 1, !"wchar_size", i32 4}
!4 = !{}
