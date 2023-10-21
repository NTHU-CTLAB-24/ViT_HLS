; ModuleID = '/users/student/mr111/cppan22/git_ViT_HLS/ViT_HLS/kernel_attention/proj_kernel_attention/solution1/.autopilot/db/a.g.ld.5.gdce.bc'
source_filename = "llvm-link"
target datalayout = "e-m:e-i64:64-i128:128-i256:256-i512:512-i1024:1024-i2048:2048-i4096:4096-n8:16:32:64-S128-v16:16-v24:32-v32:32-v48:64-v96:128-v192:256-v256:256-v512:512-v1024:1024"
target triple = "fpga64-xilinx-none"

; Function Attrs: noinline
define void @apatb_kernel_attention_ir(float* noalias nocapture nonnull readonly %buffer_DataIn_1, float* noalias nocapture nonnull %afterNorm, float* noalias nocapture nonnull readonly %norm1_mean, float* noalias nocapture nonnull readonly %norm1_var, float* noalias nocapture nonnull readonly %norm1_weight, float* noalias nocapture nonnull readonly %norm1_bias, float* noalias nocapture nonnull %afterPad, float* noalias nocapture nonnull %afterRearrangeX, float* noalias nocapture nonnull readonly %afterPad1, float* noalias nocapture nonnull %afterConv1, float* noalias nocapture nonnull readonly %kernel1, float* noalias nocapture nonnull readonly %bias1, float* noalias nocapture nonnull %in_qk, float* noalias nocapture nonnull %in_q, float* noalias nocapture nonnull %in_k, float* noalias nocapture nonnull %afterQKMultiplication, float* noalias nocapture nonnull %afterSoftmax, float* noalias nocapture nonnull %afterRearrangeX2, float* noalias nocapture nonnull %afterQKXMultiplication, float* noalias nocapture nonnull %afterRearrangeQKX, float* noalias nocapture nonnull readonly %afterPad2, float* noalias nocapture nonnull %afterConv2, float* noalias nocapture nonnull readonly %kernel2, float* noalias nocapture nonnull readonly %bias2, float* noalias nocapture nonnull %afterAct2, float* noalias nocapture nonnull %QKV, float* noalias nocapture nonnull %buffer_out, float* noalias nocapture nonnull %buffer_result) local_unnamed_addr #0 {
entry:
  %malloccall = tail call i8* @malloc(i64 62720)
  %buffer_DataIn_1_copy = bitcast i8* %malloccall to [15680 x float]*
  %malloccall1 = tail call i8* @malloc(i64 62720)
  %afterNorm_copy = bitcast i8* %malloccall1 to [15680 x float]*
  %norm1_mean_copy = alloca [80 x float], align 512
  %norm1_var_copy = alloca [80 x float], align 512
  %norm1_weight_copy = alloca [80 x float], align 512
  %norm1_bias_copy = alloca [80 x float], align 512
  %malloccall2 = tail call i8* @malloc(i64 62720)
  %afterPad_copy = bitcast i8* %malloccall2 to [15680 x float]*
  %malloccall3 = tail call i8* @malloc(i64 62720)
  %afterRearrangeX_copy = bitcast i8* %malloccall3 to [15680 x float]*
  %malloccall4 = tail call i8* @malloc(i64 62720)
  %afterPad1_copy = bitcast i8* %malloccall4 to [15680 x float]*
  %malloccall5 = tail call i8* @malloc(i64 125440)
  %afterConv1_copy = bitcast i8* %malloccall5 to [31360 x float]*
  %malloccall6 = tail call i8* @malloc(i64 51200)
  %kernel1_copy = bitcast i8* %malloccall6 to [12800 x float]*
  %bias1_copy = alloca [160 x float], align 512
  %malloccall7 = tail call i8* @malloc(i64 125440)
  %in_qk_copy = bitcast i8* %malloccall7 to [31360 x float]*
  %malloccall8 = tail call i8* @malloc(i64 62720)
  %in_q_copy = bitcast i8* %malloccall8 to [15680 x float]*
  %malloccall9 = tail call i8* @malloc(i64 62720)
  %in_k_copy = bitcast i8* %malloccall9 to [15680 x float]*
  %malloccall10 = tail call i8* @malloc(i64 153664)
  %afterQKMultiplication_copy = bitcast i8* %malloccall10 to [38416 x float]*
  %malloccall11 = tail call i8* @malloc(i64 153664)
  %afterSoftmax_copy = bitcast i8* %malloccall11 to [38416 x float]*
  %malloccall12 = tail call i8* @malloc(i64 62720)
  %afterRearrangeX2_copy = bitcast i8* %malloccall12 to [15680 x float]*
  %malloccall13 = tail call i8* @malloc(i64 62720)
  %afterQKXMultiplication_copy = bitcast i8* %malloccall13 to [15680 x float]*
  %malloccall14 = tail call i8* @malloc(i64 62720)
  %afterRearrangeQKX_copy = bitcast i8* %malloccall14 to [15680 x float]*
  %malloccall15 = tail call i8* @malloc(i64 62720)
  %afterPad2_copy = bitcast i8* %malloccall15 to [15680 x float]*
  %malloccall16 = tail call i8* @malloc(i64 188160)
  %afterConv2_copy = bitcast i8* %malloccall16 to [47040 x float]*
  %malloccall17 = tail call i8* @malloc(i64 76800)
  %kernel2_copy = bitcast i8* %malloccall17 to [19200 x float]*
  %bias2_copy = alloca [240 x float], align 512
  %malloccall18 = tail call i8* @malloc(i64 188160)
  %afterAct2_copy = bitcast i8* %malloccall18 to [47040 x float]*
  %malloccall19 = tail call i8* @malloc(i64 188160)
  %QKV_copy = bitcast i8* %malloccall19 to [47040 x float]*
  %malloccall20 = tail call i8* @malloc(i64 188160)
  %buffer_out_copy = bitcast i8* %malloccall20 to [47040 x float]*
  %malloccall21 = tail call i8* @malloc(i64 188160)
  %buffer_result_copy = bitcast i8* %malloccall21 to [47040 x float]*
  %0 = bitcast float* %buffer_DataIn_1 to [15680 x float]*
  %1 = bitcast float* %afterNorm to [15680 x float]*
  %2 = bitcast float* %norm1_mean to [80 x float]*
  %3 = bitcast float* %norm1_var to [80 x float]*
  %4 = bitcast float* %norm1_weight to [80 x float]*
  %5 = bitcast float* %norm1_bias to [80 x float]*
  %6 = bitcast float* %afterPad to [15680 x float]*
  %7 = bitcast float* %afterRearrangeX to [15680 x float]*
  %8 = bitcast float* %afterPad1 to [15680 x float]*
  %9 = bitcast float* %afterConv1 to [31360 x float]*
  %10 = bitcast float* %kernel1 to [12800 x float]*
  %11 = bitcast float* %bias1 to [160 x float]*
  %12 = bitcast float* %in_qk to [31360 x float]*
  %13 = bitcast float* %in_q to [15680 x float]*
  %14 = bitcast float* %in_k to [15680 x float]*
  %15 = bitcast float* %afterQKMultiplication to [38416 x float]*
  %16 = bitcast float* %afterSoftmax to [38416 x float]*
  %17 = bitcast float* %afterRearrangeX2 to [15680 x float]*
  %18 = bitcast float* %afterQKXMultiplication to [15680 x float]*
  %19 = bitcast float* %afterRearrangeQKX to [15680 x float]*
  %20 = bitcast float* %afterPad2 to [15680 x float]*
  %21 = bitcast float* %afterConv2 to [47040 x float]*
  %22 = bitcast float* %kernel2 to [19200 x float]*
  %23 = bitcast float* %bias2 to [240 x float]*
  %24 = bitcast float* %afterAct2 to [47040 x float]*
  %25 = bitcast float* %QKV to [47040 x float]*
  %26 = bitcast float* %buffer_out to [47040 x float]*
  %27 = bitcast float* %buffer_result to [47040 x float]*
  call fastcc void @copy_in([15680 x float]* nonnull %0, [15680 x float]* %buffer_DataIn_1_copy, [15680 x float]* nonnull %1, [15680 x float]* %afterNorm_copy, [80 x float]* nonnull %2, [80 x float]* nonnull align 512 %norm1_mean_copy, [80 x float]* nonnull %3, [80 x float]* nonnull align 512 %norm1_var_copy, [80 x float]* nonnull %4, [80 x float]* nonnull align 512 %norm1_weight_copy, [80 x float]* nonnull %5, [80 x float]* nonnull align 512 %norm1_bias_copy, [15680 x float]* nonnull %6, [15680 x float]* %afterPad_copy, [15680 x float]* nonnull %7, [15680 x float]* %afterRearrangeX_copy, [15680 x float]* nonnull %8, [15680 x float]* %afterPad1_copy, [31360 x float]* nonnull %9, [31360 x float]* %afterConv1_copy, [12800 x float]* nonnull %10, [12800 x float]* %kernel1_copy, [160 x float]* nonnull %11, [160 x float]* nonnull align 512 %bias1_copy, [31360 x float]* nonnull %12, [31360 x float]* %in_qk_copy, [15680 x float]* nonnull %13, [15680 x float]* %in_q_copy, [15680 x float]* nonnull %14, [15680 x float]* %in_k_copy, [38416 x float]* nonnull %15, [38416 x float]* %afterQKMultiplication_copy, [38416 x float]* nonnull %16, [38416 x float]* %afterSoftmax_copy, [15680 x float]* nonnull %17, [15680 x float]* %afterRearrangeX2_copy, [15680 x float]* nonnull %18, [15680 x float]* %afterQKXMultiplication_copy, [15680 x float]* nonnull %19, [15680 x float]* %afterRearrangeQKX_copy, [15680 x float]* nonnull %20, [15680 x float]* %afterPad2_copy, [47040 x float]* nonnull %21, [47040 x float]* %afterConv2_copy, [19200 x float]* nonnull %22, [19200 x float]* %kernel2_copy, [240 x float]* nonnull %23, [240 x float]* nonnull align 512 %bias2_copy, [47040 x float]* nonnull %24, [47040 x float]* %afterAct2_copy, [47040 x float]* nonnull %25, [47040 x float]* %QKV_copy, [47040 x float]* nonnull %26, [47040 x float]* %buffer_out_copy, [47040 x float]* nonnull %27, [47040 x float]* %buffer_result_copy)
  %28 = getelementptr inbounds [15680 x float], [15680 x float]* %buffer_DataIn_1_copy, i32 0, i32 0
  %29 = getelementptr inbounds [15680 x float], [15680 x float]* %afterNorm_copy, i32 0, i32 0
  %30 = getelementptr inbounds [80 x float], [80 x float]* %norm1_mean_copy, i32 0, i32 0
  %31 = getelementptr inbounds [80 x float], [80 x float]* %norm1_var_copy, i32 0, i32 0
  %32 = getelementptr inbounds [80 x float], [80 x float]* %norm1_weight_copy, i32 0, i32 0
  %33 = getelementptr inbounds [80 x float], [80 x float]* %norm1_bias_copy, i32 0, i32 0
  %34 = getelementptr inbounds [15680 x float], [15680 x float]* %afterPad_copy, i32 0, i32 0
  %35 = getelementptr inbounds [15680 x float], [15680 x float]* %afterRearrangeX_copy, i32 0, i32 0
  %36 = getelementptr inbounds [15680 x float], [15680 x float]* %afterPad1_copy, i32 0, i32 0
  %37 = getelementptr inbounds [31360 x float], [31360 x float]* %afterConv1_copy, i32 0, i32 0
  %38 = getelementptr inbounds [12800 x float], [12800 x float]* %kernel1_copy, i32 0, i32 0
  %39 = getelementptr inbounds [160 x float], [160 x float]* %bias1_copy, i32 0, i32 0
  %40 = getelementptr inbounds [31360 x float], [31360 x float]* %in_qk_copy, i32 0, i32 0
  %41 = getelementptr inbounds [15680 x float], [15680 x float]* %in_q_copy, i32 0, i32 0
  %42 = getelementptr inbounds [15680 x float], [15680 x float]* %in_k_copy, i32 0, i32 0
  %43 = getelementptr inbounds [38416 x float], [38416 x float]* %afterQKMultiplication_copy, i32 0, i32 0
  %44 = getelementptr inbounds [38416 x float], [38416 x float]* %afterSoftmax_copy, i32 0, i32 0
  %45 = getelementptr inbounds [15680 x float], [15680 x float]* %afterRearrangeX2_copy, i32 0, i32 0
  %46 = getelementptr inbounds [15680 x float], [15680 x float]* %afterQKXMultiplication_copy, i32 0, i32 0
  %47 = getelementptr inbounds [15680 x float], [15680 x float]* %afterRearrangeQKX_copy, i32 0, i32 0
  %48 = getelementptr inbounds [15680 x float], [15680 x float]* %afterPad2_copy, i32 0, i32 0
  %49 = getelementptr inbounds [47040 x float], [47040 x float]* %afterConv2_copy, i32 0, i32 0
  %50 = getelementptr inbounds [19200 x float], [19200 x float]* %kernel2_copy, i32 0, i32 0
  %51 = getelementptr inbounds [240 x float], [240 x float]* %bias2_copy, i32 0, i32 0
  %52 = getelementptr inbounds [47040 x float], [47040 x float]* %afterAct2_copy, i32 0, i32 0
  %53 = getelementptr inbounds [47040 x float], [47040 x float]* %QKV_copy, i32 0, i32 0
  %54 = getelementptr inbounds [47040 x float], [47040 x float]* %buffer_out_copy, i32 0, i32 0
  %55 = getelementptr inbounds [47040 x float], [47040 x float]* %buffer_result_copy, i32 0, i32 0
  call void @apatb_kernel_attention_hw(float* %28, float* %29, float* %30, float* %31, float* %32, float* %33, float* %34, float* %35, float* %36, float* %37, float* %38, float* %39, float* %40, float* %41, float* %42, float* %43, float* %44, float* %45, float* %46, float* %47, float* %48, float* %49, float* %50, float* %51, float* %52, float* %53, float* %54, float* %55)
  call void @copy_back([15680 x float]* %0, [15680 x float]* %buffer_DataIn_1_copy, [15680 x float]* %1, [15680 x float]* %afterNorm_copy, [80 x float]* %2, [80 x float]* %norm1_mean_copy, [80 x float]* %3, [80 x float]* %norm1_var_copy, [80 x float]* %4, [80 x float]* %norm1_weight_copy, [80 x float]* %5, [80 x float]* %norm1_bias_copy, [15680 x float]* %6, [15680 x float]* %afterPad_copy, [15680 x float]* %7, [15680 x float]* %afterRearrangeX_copy, [15680 x float]* %8, [15680 x float]* %afterPad1_copy, [31360 x float]* %9, [31360 x float]* %afterConv1_copy, [12800 x float]* %10, [12800 x float]* %kernel1_copy, [160 x float]* %11, [160 x float]* %bias1_copy, [31360 x float]* %12, [31360 x float]* %in_qk_copy, [15680 x float]* %13, [15680 x float]* %in_q_copy, [15680 x float]* %14, [15680 x float]* %in_k_copy, [38416 x float]* %15, [38416 x float]* %afterQKMultiplication_copy, [38416 x float]* %16, [38416 x float]* %afterSoftmax_copy, [15680 x float]* %17, [15680 x float]* %afterRearrangeX2_copy, [15680 x float]* %18, [15680 x float]* %afterQKXMultiplication_copy, [15680 x float]* %19, [15680 x float]* %afterRearrangeQKX_copy, [15680 x float]* %20, [15680 x float]* %afterPad2_copy, [47040 x float]* %21, [47040 x float]* %afterConv2_copy, [19200 x float]* %22, [19200 x float]* %kernel2_copy, [240 x float]* %23, [240 x float]* %bias2_copy, [47040 x float]* %24, [47040 x float]* %afterAct2_copy, [47040 x float]* %25, [47040 x float]* %QKV_copy, [47040 x float]* %26, [47040 x float]* %buffer_out_copy, [47040 x float]* %27, [47040 x float]* %buffer_result_copy)
  tail call void @free(i8* %malloccall)
  tail call void @free(i8* %malloccall1)
  tail call void @free(i8* %malloccall2)
  tail call void @free(i8* %malloccall3)
  tail call void @free(i8* %malloccall4)
  tail call void @free(i8* %malloccall5)
  tail call void @free(i8* %malloccall6)
  tail call void @free(i8* %malloccall7)
  tail call void @free(i8* %malloccall8)
  tail call void @free(i8* %malloccall9)
  tail call void @free(i8* %malloccall10)
  tail call void @free(i8* %malloccall11)
  tail call void @free(i8* %malloccall12)
  tail call void @free(i8* %malloccall13)
  tail call void @free(i8* %malloccall14)
  tail call void @free(i8* %malloccall15)
  tail call void @free(i8* %malloccall16)
  tail call void @free(i8* %malloccall17)
  tail call void @free(i8* %malloccall18)
  tail call void @free(i8* %malloccall19)
  tail call void @free(i8* %malloccall20)
  tail call void @free(i8* %malloccall21)
  ret void
}

declare noalias i8* @malloc(i64) local_unnamed_addr

; Function Attrs: argmemonly noinline norecurse
define internal fastcc void @copy_in([15680 x float]* noalias readonly, [15680 x float]* noalias, [15680 x float]* noalias readonly, [15680 x float]* noalias, [80 x float]* noalias readonly, [80 x float]* noalias align 512, [80 x float]* noalias readonly, [80 x float]* noalias align 512, [80 x float]* noalias readonly, [80 x float]* noalias align 512, [80 x float]* noalias readonly, [80 x float]* noalias align 512, [15680 x float]* noalias readonly, [15680 x float]* noalias, [15680 x float]* noalias readonly, [15680 x float]* noalias, [15680 x float]* noalias readonly, [15680 x float]* noalias, [31360 x float]* noalias readonly, [31360 x float]* noalias, [12800 x float]* noalias readonly, [12800 x float]* noalias, [160 x float]* noalias readonly, [160 x float]* noalias align 512, [31360 x float]* noalias readonly, [31360 x float]* noalias, [15680 x float]* noalias readonly, [15680 x float]* noalias, [15680 x float]* noalias readonly, [15680 x float]* noalias, [38416 x float]* noalias readonly, [38416 x float]* noalias, [38416 x float]* noalias readonly, [38416 x float]* noalias, [15680 x float]* noalias readonly, [15680 x float]* noalias, [15680 x float]* noalias readonly, [15680 x float]* noalias, [15680 x float]* noalias readonly, [15680 x float]* noalias, [15680 x float]* noalias readonly, [15680 x float]* noalias, [47040 x float]* noalias readonly, [47040 x float]* noalias, [19200 x float]* noalias readonly, [19200 x float]* noalias, [240 x float]* noalias readonly, [240 x float]* noalias align 512, [47040 x float]* noalias readonly, [47040 x float]* noalias, [47040 x float]* noalias readonly, [47040 x float]* noalias, [47040 x float]* noalias readonly, [47040 x float]* noalias, [47040 x float]* noalias readonly, [47040 x float]* noalias) unnamed_addr #1 {
entry:
  call fastcc void @onebyonecpy_hls.p0a15680f32([15680 x float]* %1, [15680 x float]* %0)
  call fastcc void @onebyonecpy_hls.p0a15680f32([15680 x float]* %3, [15680 x float]* %2)
  call fastcc void @onebyonecpy_hls.p0a80f32([80 x float]* align 512 %5, [80 x float]* %4)
  call fastcc void @onebyonecpy_hls.p0a80f32([80 x float]* align 512 %7, [80 x float]* %6)
  call fastcc void @onebyonecpy_hls.p0a80f32([80 x float]* align 512 %9, [80 x float]* %8)
  call fastcc void @onebyonecpy_hls.p0a80f32([80 x float]* align 512 %11, [80 x float]* %10)
  call fastcc void @onebyonecpy_hls.p0a15680f32([15680 x float]* %13, [15680 x float]* %12)
  call fastcc void @onebyonecpy_hls.p0a15680f32([15680 x float]* %15, [15680 x float]* %14)
  call fastcc void @onebyonecpy_hls.p0a15680f32([15680 x float]* %17, [15680 x float]* %16)
  call fastcc void @onebyonecpy_hls.p0a31360f32([31360 x float]* %19, [31360 x float]* %18)
  call fastcc void @onebyonecpy_hls.p0a12800f32([12800 x float]* %21, [12800 x float]* %20)
  call fastcc void @onebyonecpy_hls.p0a160f32([160 x float]* align 512 %23, [160 x float]* %22)
  call fastcc void @onebyonecpy_hls.p0a31360f32([31360 x float]* %25, [31360 x float]* %24)
  call fastcc void @onebyonecpy_hls.p0a15680f32([15680 x float]* %27, [15680 x float]* %26)
  call fastcc void @onebyonecpy_hls.p0a15680f32([15680 x float]* %29, [15680 x float]* %28)
  call fastcc void @onebyonecpy_hls.p0a38416f32([38416 x float]* %31, [38416 x float]* %30)
  call fastcc void @onebyonecpy_hls.p0a38416f32([38416 x float]* %33, [38416 x float]* %32)
  call fastcc void @onebyonecpy_hls.p0a15680f32([15680 x float]* %35, [15680 x float]* %34)
  call fastcc void @onebyonecpy_hls.p0a15680f32([15680 x float]* %37, [15680 x float]* %36)
  call fastcc void @onebyonecpy_hls.p0a15680f32([15680 x float]* %39, [15680 x float]* %38)
  call fastcc void @onebyonecpy_hls.p0a15680f32([15680 x float]* %41, [15680 x float]* %40)
  call fastcc void @onebyonecpy_hls.p0a47040f32([47040 x float]* %43, [47040 x float]* %42)
  call fastcc void @onebyonecpy_hls.p0a19200f32([19200 x float]* %45, [19200 x float]* %44)
  call fastcc void @onebyonecpy_hls.p0a240f32([240 x float]* align 512 %47, [240 x float]* %46)
  call fastcc void @onebyonecpy_hls.p0a47040f32([47040 x float]* %49, [47040 x float]* %48)
  call fastcc void @onebyonecpy_hls.p0a47040f32([47040 x float]* %51, [47040 x float]* %50)
  call fastcc void @onebyonecpy_hls.p0a47040f32([47040 x float]* %53, [47040 x float]* %52)
  call fastcc void @onebyonecpy_hls.p0a47040f32([47040 x float]* %55, [47040 x float]* %54)
  ret void
}

; Function Attrs: argmemonly noinline norecurse
define internal fastcc void @onebyonecpy_hls.p0a15680f32([15680 x float]* noalias, [15680 x float]* noalias readonly) unnamed_addr #2 {
entry:
  %2 = icmp eq [15680 x float]* %0, null
  %3 = icmp eq [15680 x float]* %1, null
  %4 = or i1 %2, %3
  br i1 %4, label %ret, label %copy

copy:                                             ; preds = %entry
  br label %for.loop

for.loop:                                         ; preds = %for.loop, %copy
  %for.loop.idx1 = phi i64 [ 0, %copy ], [ %for.loop.idx.next, %for.loop ]
  %dst.addr = getelementptr [15680 x float], [15680 x float]* %0, i64 0, i64 %for.loop.idx1
  %src.addr = getelementptr [15680 x float], [15680 x float]* %1, i64 0, i64 %for.loop.idx1
  %5 = load float, float* %src.addr, align 4
  store float %5, float* %dst.addr, align 4
  %for.loop.idx.next = add nuw nsw i64 %for.loop.idx1, 1
  %exitcond = icmp ne i64 %for.loop.idx.next, 15680
  br i1 %exitcond, label %for.loop, label %ret

ret:                                              ; preds = %for.loop, %entry
  ret void
}

; Function Attrs: argmemonly noinline norecurse
define internal fastcc void @onebyonecpy_hls.p0a80f32([80 x float]* noalias align 512, [80 x float]* noalias readonly) unnamed_addr #2 {
entry:
  %2 = icmp eq [80 x float]* %0, null
  %3 = icmp eq [80 x float]* %1, null
  %4 = or i1 %2, %3
  br i1 %4, label %ret, label %copy

copy:                                             ; preds = %entry
  br label %for.loop

for.loop:                                         ; preds = %for.loop, %copy
  %for.loop.idx1 = phi i64 [ 0, %copy ], [ %for.loop.idx.next, %for.loop ]
  %dst.addr = getelementptr [80 x float], [80 x float]* %0, i64 0, i64 %for.loop.idx1
  %src.addr = getelementptr [80 x float], [80 x float]* %1, i64 0, i64 %for.loop.idx1
  %5 = load float, float* %src.addr, align 4
  store float %5, float* %dst.addr, align 4
  %for.loop.idx.next = add nuw nsw i64 %for.loop.idx1, 1
  %exitcond = icmp ne i64 %for.loop.idx.next, 80
  br i1 %exitcond, label %for.loop, label %ret

ret:                                              ; preds = %for.loop, %entry
  ret void
}

; Function Attrs: argmemonly noinline norecurse
define internal fastcc void @onebyonecpy_hls.p0a31360f32([31360 x float]* noalias, [31360 x float]* noalias readonly) unnamed_addr #2 {
entry:
  %2 = icmp eq [31360 x float]* %0, null
  %3 = icmp eq [31360 x float]* %1, null
  %4 = or i1 %2, %3
  br i1 %4, label %ret, label %copy

copy:                                             ; preds = %entry
  br label %for.loop

for.loop:                                         ; preds = %for.loop, %copy
  %for.loop.idx1 = phi i64 [ 0, %copy ], [ %for.loop.idx.next, %for.loop ]
  %dst.addr = getelementptr [31360 x float], [31360 x float]* %0, i64 0, i64 %for.loop.idx1
  %src.addr = getelementptr [31360 x float], [31360 x float]* %1, i64 0, i64 %for.loop.idx1
  %5 = load float, float* %src.addr, align 4
  store float %5, float* %dst.addr, align 4
  %for.loop.idx.next = add nuw nsw i64 %for.loop.idx1, 1
  %exitcond = icmp ne i64 %for.loop.idx.next, 31360
  br i1 %exitcond, label %for.loop, label %ret

ret:                                              ; preds = %for.loop, %entry
  ret void
}

; Function Attrs: argmemonly noinline norecurse
define internal fastcc void @onebyonecpy_hls.p0a12800f32([12800 x float]* noalias, [12800 x float]* noalias readonly) unnamed_addr #2 {
entry:
  %2 = icmp eq [12800 x float]* %0, null
  %3 = icmp eq [12800 x float]* %1, null
  %4 = or i1 %2, %3
  br i1 %4, label %ret, label %copy

copy:                                             ; preds = %entry
  br label %for.loop

for.loop:                                         ; preds = %for.loop, %copy
  %for.loop.idx1 = phi i64 [ 0, %copy ], [ %for.loop.idx.next, %for.loop ]
  %dst.addr = getelementptr [12800 x float], [12800 x float]* %0, i64 0, i64 %for.loop.idx1
  %src.addr = getelementptr [12800 x float], [12800 x float]* %1, i64 0, i64 %for.loop.idx1
  %5 = load float, float* %src.addr, align 4
  store float %5, float* %dst.addr, align 4
  %for.loop.idx.next = add nuw nsw i64 %for.loop.idx1, 1
  %exitcond = icmp ne i64 %for.loop.idx.next, 12800
  br i1 %exitcond, label %for.loop, label %ret

ret:                                              ; preds = %for.loop, %entry
  ret void
}

; Function Attrs: argmemonly noinline norecurse
define internal fastcc void @onebyonecpy_hls.p0a160f32([160 x float]* noalias align 512, [160 x float]* noalias readonly) unnamed_addr #2 {
entry:
  %2 = icmp eq [160 x float]* %0, null
  %3 = icmp eq [160 x float]* %1, null
  %4 = or i1 %2, %3
  br i1 %4, label %ret, label %copy

copy:                                             ; preds = %entry
  br label %for.loop

for.loop:                                         ; preds = %for.loop, %copy
  %for.loop.idx1 = phi i64 [ 0, %copy ], [ %for.loop.idx.next, %for.loop ]
  %dst.addr = getelementptr [160 x float], [160 x float]* %0, i64 0, i64 %for.loop.idx1
  %src.addr = getelementptr [160 x float], [160 x float]* %1, i64 0, i64 %for.loop.idx1
  %5 = load float, float* %src.addr, align 4
  store float %5, float* %dst.addr, align 4
  %for.loop.idx.next = add nuw nsw i64 %for.loop.idx1, 1
  %exitcond = icmp ne i64 %for.loop.idx.next, 160
  br i1 %exitcond, label %for.loop, label %ret

ret:                                              ; preds = %for.loop, %entry
  ret void
}

; Function Attrs: argmemonly noinline norecurse
define internal fastcc void @onebyonecpy_hls.p0a38416f32([38416 x float]* noalias, [38416 x float]* noalias readonly) unnamed_addr #2 {
entry:
  %2 = icmp eq [38416 x float]* %0, null
  %3 = icmp eq [38416 x float]* %1, null
  %4 = or i1 %2, %3
  br i1 %4, label %ret, label %copy

copy:                                             ; preds = %entry
  br label %for.loop

for.loop:                                         ; preds = %for.loop, %copy
  %for.loop.idx1 = phi i64 [ 0, %copy ], [ %for.loop.idx.next, %for.loop ]
  %dst.addr = getelementptr [38416 x float], [38416 x float]* %0, i64 0, i64 %for.loop.idx1
  %src.addr = getelementptr [38416 x float], [38416 x float]* %1, i64 0, i64 %for.loop.idx1
  %5 = load float, float* %src.addr, align 4
  store float %5, float* %dst.addr, align 4
  %for.loop.idx.next = add nuw nsw i64 %for.loop.idx1, 1
  %exitcond = icmp ne i64 %for.loop.idx.next, 38416
  br i1 %exitcond, label %for.loop, label %ret

ret:                                              ; preds = %for.loop, %entry
  ret void
}

; Function Attrs: argmemonly noinline norecurse
define internal fastcc void @onebyonecpy_hls.p0a47040f32([47040 x float]* noalias, [47040 x float]* noalias readonly) unnamed_addr #2 {
entry:
  %2 = icmp eq [47040 x float]* %0, null
  %3 = icmp eq [47040 x float]* %1, null
  %4 = or i1 %2, %3
  br i1 %4, label %ret, label %copy

copy:                                             ; preds = %entry
  br label %for.loop

for.loop:                                         ; preds = %for.loop, %copy
  %for.loop.idx1 = phi i64 [ 0, %copy ], [ %for.loop.idx.next, %for.loop ]
  %dst.addr = getelementptr [47040 x float], [47040 x float]* %0, i64 0, i64 %for.loop.idx1
  %src.addr = getelementptr [47040 x float], [47040 x float]* %1, i64 0, i64 %for.loop.idx1
  %5 = load float, float* %src.addr, align 4
  store float %5, float* %dst.addr, align 4
  %for.loop.idx.next = add nuw nsw i64 %for.loop.idx1, 1
  %exitcond = icmp ne i64 %for.loop.idx.next, 47040
  br i1 %exitcond, label %for.loop, label %ret

ret:                                              ; preds = %for.loop, %entry
  ret void
}

; Function Attrs: argmemonly noinline norecurse
define internal fastcc void @onebyonecpy_hls.p0a19200f32([19200 x float]* noalias, [19200 x float]* noalias readonly) unnamed_addr #2 {
entry:
  %2 = icmp eq [19200 x float]* %0, null
  %3 = icmp eq [19200 x float]* %1, null
  %4 = or i1 %2, %3
  br i1 %4, label %ret, label %copy

copy:                                             ; preds = %entry
  br label %for.loop

for.loop:                                         ; preds = %for.loop, %copy
  %for.loop.idx1 = phi i64 [ 0, %copy ], [ %for.loop.idx.next, %for.loop ]
  %dst.addr = getelementptr [19200 x float], [19200 x float]* %0, i64 0, i64 %for.loop.idx1
  %src.addr = getelementptr [19200 x float], [19200 x float]* %1, i64 0, i64 %for.loop.idx1
  %5 = load float, float* %src.addr, align 4
  store float %5, float* %dst.addr, align 4
  %for.loop.idx.next = add nuw nsw i64 %for.loop.idx1, 1
  %exitcond = icmp ne i64 %for.loop.idx.next, 19200
  br i1 %exitcond, label %for.loop, label %ret

ret:                                              ; preds = %for.loop, %entry
  ret void
}

; Function Attrs: argmemonly noinline norecurse
define internal fastcc void @onebyonecpy_hls.p0a240f32([240 x float]* noalias align 512, [240 x float]* noalias readonly) unnamed_addr #2 {
entry:
  %2 = icmp eq [240 x float]* %0, null
  %3 = icmp eq [240 x float]* %1, null
  %4 = or i1 %2, %3
  br i1 %4, label %ret, label %copy

copy:                                             ; preds = %entry
  br label %for.loop

for.loop:                                         ; preds = %for.loop, %copy
  %for.loop.idx1 = phi i64 [ 0, %copy ], [ %for.loop.idx.next, %for.loop ]
  %dst.addr = getelementptr [240 x float], [240 x float]* %0, i64 0, i64 %for.loop.idx1
  %src.addr = getelementptr [240 x float], [240 x float]* %1, i64 0, i64 %for.loop.idx1
  %5 = load float, float* %src.addr, align 4
  store float %5, float* %dst.addr, align 4
  %for.loop.idx.next = add nuw nsw i64 %for.loop.idx1, 1
  %exitcond = icmp ne i64 %for.loop.idx.next, 240
  br i1 %exitcond, label %for.loop, label %ret

ret:                                              ; preds = %for.loop, %entry
  ret void
}

; Function Attrs: argmemonly noinline norecurse
define internal fastcc void @copy_out([15680 x float]* noalias, [15680 x float]* noalias readonly, [15680 x float]* noalias, [15680 x float]* noalias readonly, [80 x float]* noalias, [80 x float]* noalias readonly align 512, [80 x float]* noalias, [80 x float]* noalias readonly align 512, [80 x float]* noalias, [80 x float]* noalias readonly align 512, [80 x float]* noalias, [80 x float]* noalias readonly align 512, [15680 x float]* noalias, [15680 x float]* noalias readonly, [15680 x float]* noalias, [15680 x float]* noalias readonly, [15680 x float]* noalias, [15680 x float]* noalias readonly, [31360 x float]* noalias, [31360 x float]* noalias readonly, [12800 x float]* noalias, [12800 x float]* noalias readonly, [160 x float]* noalias, [160 x float]* noalias readonly align 512, [31360 x float]* noalias, [31360 x float]* noalias readonly, [15680 x float]* noalias, [15680 x float]* noalias readonly, [15680 x float]* noalias, [15680 x float]* noalias readonly, [38416 x float]* noalias, [38416 x float]* noalias readonly, [38416 x float]* noalias, [38416 x float]* noalias readonly, [15680 x float]* noalias, [15680 x float]* noalias readonly, [15680 x float]* noalias, [15680 x float]* noalias readonly, [15680 x float]* noalias, [15680 x float]* noalias readonly, [15680 x float]* noalias, [15680 x float]* noalias readonly, [47040 x float]* noalias, [47040 x float]* noalias readonly, [19200 x float]* noalias, [19200 x float]* noalias readonly, [240 x float]* noalias, [240 x float]* noalias readonly align 512, [47040 x float]* noalias, [47040 x float]* noalias readonly, [47040 x float]* noalias, [47040 x float]* noalias readonly, [47040 x float]* noalias, [47040 x float]* noalias readonly, [47040 x float]* noalias, [47040 x float]* noalias readonly) unnamed_addr #3 {
entry:
  call fastcc void @onebyonecpy_hls.p0a15680f32([15680 x float]* %0, [15680 x float]* %1)
  call fastcc void @onebyonecpy_hls.p0a15680f32([15680 x float]* %2, [15680 x float]* %3)
  call fastcc void @onebyonecpy_hls.p0a80f32([80 x float]* %4, [80 x float]* align 512 %5)
  call fastcc void @onebyonecpy_hls.p0a80f32([80 x float]* %6, [80 x float]* align 512 %7)
  call fastcc void @onebyonecpy_hls.p0a80f32([80 x float]* %8, [80 x float]* align 512 %9)
  call fastcc void @onebyonecpy_hls.p0a80f32([80 x float]* %10, [80 x float]* align 512 %11)
  call fastcc void @onebyonecpy_hls.p0a15680f32([15680 x float]* %12, [15680 x float]* %13)
  call fastcc void @onebyonecpy_hls.p0a15680f32([15680 x float]* %14, [15680 x float]* %15)
  call fastcc void @onebyonecpy_hls.p0a15680f32([15680 x float]* %16, [15680 x float]* %17)
  call fastcc void @onebyonecpy_hls.p0a31360f32([31360 x float]* %18, [31360 x float]* %19)
  call fastcc void @onebyonecpy_hls.p0a12800f32([12800 x float]* %20, [12800 x float]* %21)
  call fastcc void @onebyonecpy_hls.p0a160f32([160 x float]* %22, [160 x float]* align 512 %23)
  call fastcc void @onebyonecpy_hls.p0a31360f32([31360 x float]* %24, [31360 x float]* %25)
  call fastcc void @onebyonecpy_hls.p0a15680f32([15680 x float]* %26, [15680 x float]* %27)
  call fastcc void @onebyonecpy_hls.p0a15680f32([15680 x float]* %28, [15680 x float]* %29)
  call fastcc void @onebyonecpy_hls.p0a38416f32([38416 x float]* %30, [38416 x float]* %31)
  call fastcc void @onebyonecpy_hls.p0a38416f32([38416 x float]* %32, [38416 x float]* %33)
  call fastcc void @onebyonecpy_hls.p0a15680f32([15680 x float]* %34, [15680 x float]* %35)
  call fastcc void @onebyonecpy_hls.p0a15680f32([15680 x float]* %36, [15680 x float]* %37)
  call fastcc void @onebyonecpy_hls.p0a15680f32([15680 x float]* %38, [15680 x float]* %39)
  call fastcc void @onebyonecpy_hls.p0a15680f32([15680 x float]* %40, [15680 x float]* %41)
  call fastcc void @onebyonecpy_hls.p0a47040f32([47040 x float]* %42, [47040 x float]* %43)
  call fastcc void @onebyonecpy_hls.p0a19200f32([19200 x float]* %44, [19200 x float]* %45)
  call fastcc void @onebyonecpy_hls.p0a240f32([240 x float]* %46, [240 x float]* align 512 %47)
  call fastcc void @onebyonecpy_hls.p0a47040f32([47040 x float]* %48, [47040 x float]* %49)
  call fastcc void @onebyonecpy_hls.p0a47040f32([47040 x float]* %50, [47040 x float]* %51)
  call fastcc void @onebyonecpy_hls.p0a47040f32([47040 x float]* %52, [47040 x float]* %53)
  call fastcc void @onebyonecpy_hls.p0a47040f32([47040 x float]* %54, [47040 x float]* %55)
  ret void
}

declare void @free(i8*) local_unnamed_addr

declare void @apatb_kernel_attention_hw(float*, float*, float*, float*, float*, float*, float*, float*, float*, float*, float*, float*, float*, float*, float*, float*, float*, float*, float*, float*, float*, float*, float*, float*, float*, float*, float*, float*)

; Function Attrs: argmemonly noinline norecurse
define internal fastcc void @copy_back([15680 x float]* noalias, [15680 x float]* noalias readonly, [15680 x float]* noalias, [15680 x float]* noalias readonly, [80 x float]* noalias, [80 x float]* noalias readonly align 512, [80 x float]* noalias, [80 x float]* noalias readonly align 512, [80 x float]* noalias, [80 x float]* noalias readonly align 512, [80 x float]* noalias, [80 x float]* noalias readonly align 512, [15680 x float]* noalias, [15680 x float]* noalias readonly, [15680 x float]* noalias, [15680 x float]* noalias readonly, [15680 x float]* noalias, [15680 x float]* noalias readonly, [31360 x float]* noalias, [31360 x float]* noalias readonly, [12800 x float]* noalias, [12800 x float]* noalias readonly, [160 x float]* noalias, [160 x float]* noalias readonly align 512, [31360 x float]* noalias, [31360 x float]* noalias readonly, [15680 x float]* noalias, [15680 x float]* noalias readonly, [15680 x float]* noalias, [15680 x float]* noalias readonly, [38416 x float]* noalias, [38416 x float]* noalias readonly, [38416 x float]* noalias, [38416 x float]* noalias readonly, [15680 x float]* noalias, [15680 x float]* noalias readonly, [15680 x float]* noalias, [15680 x float]* noalias readonly, [15680 x float]* noalias, [15680 x float]* noalias readonly, [15680 x float]* noalias, [15680 x float]* noalias readonly, [47040 x float]* noalias, [47040 x float]* noalias readonly, [19200 x float]* noalias, [19200 x float]* noalias readonly, [240 x float]* noalias, [240 x float]* noalias readonly align 512, [47040 x float]* noalias, [47040 x float]* noalias readonly, [47040 x float]* noalias, [47040 x float]* noalias readonly, [47040 x float]* noalias, [47040 x float]* noalias readonly, [47040 x float]* noalias, [47040 x float]* noalias readonly) unnamed_addr #3 {
entry:
  call fastcc void @onebyonecpy_hls.p0a15680f32([15680 x float]* %2, [15680 x float]* %3)
  call fastcc void @onebyonecpy_hls.p0a15680f32([15680 x float]* %12, [15680 x float]* %13)
  call fastcc void @onebyonecpy_hls.p0a15680f32([15680 x float]* %14, [15680 x float]* %15)
  call fastcc void @onebyonecpy_hls.p0a31360f32([31360 x float]* %18, [31360 x float]* %19)
  call fastcc void @onebyonecpy_hls.p0a31360f32([31360 x float]* %24, [31360 x float]* %25)
  call fastcc void @onebyonecpy_hls.p0a15680f32([15680 x float]* %26, [15680 x float]* %27)
  call fastcc void @onebyonecpy_hls.p0a15680f32([15680 x float]* %28, [15680 x float]* %29)
  call fastcc void @onebyonecpy_hls.p0a38416f32([38416 x float]* %30, [38416 x float]* %31)
  call fastcc void @onebyonecpy_hls.p0a38416f32([38416 x float]* %32, [38416 x float]* %33)
  call fastcc void @onebyonecpy_hls.p0a15680f32([15680 x float]* %34, [15680 x float]* %35)
  call fastcc void @onebyonecpy_hls.p0a15680f32([15680 x float]* %36, [15680 x float]* %37)
  call fastcc void @onebyonecpy_hls.p0a15680f32([15680 x float]* %38, [15680 x float]* %39)
  call fastcc void @onebyonecpy_hls.p0a47040f32([47040 x float]* %42, [47040 x float]* %43)
  call fastcc void @onebyonecpy_hls.p0a47040f32([47040 x float]* %48, [47040 x float]* %49)
  call fastcc void @onebyonecpy_hls.p0a47040f32([47040 x float]* %50, [47040 x float]* %51)
  call fastcc void @onebyonecpy_hls.p0a47040f32([47040 x float]* %52, [47040 x float]* %53)
  call fastcc void @onebyonecpy_hls.p0a47040f32([47040 x float]* %54, [47040 x float]* %55)
  ret void
}

define void @kernel_attention_hw_stub_wrapper(float*, float*, float*, float*, float*, float*, float*, float*, float*, float*, float*, float*, float*, float*, float*, float*, float*, float*, float*, float*, float*, float*, float*, float*, float*, float*, float*, float*) #4 {
entry:
  %28 = bitcast float* %0 to [15680 x float]*
  %29 = bitcast float* %1 to [15680 x float]*
  %30 = bitcast float* %2 to [80 x float]*
  %31 = bitcast float* %3 to [80 x float]*
  %32 = bitcast float* %4 to [80 x float]*
  %33 = bitcast float* %5 to [80 x float]*
  %34 = bitcast float* %6 to [15680 x float]*
  %35 = bitcast float* %7 to [15680 x float]*
  %36 = bitcast float* %8 to [15680 x float]*
  %37 = bitcast float* %9 to [31360 x float]*
  %38 = bitcast float* %10 to [12800 x float]*
  %39 = bitcast float* %11 to [160 x float]*
  %40 = bitcast float* %12 to [31360 x float]*
  %41 = bitcast float* %13 to [15680 x float]*
  %42 = bitcast float* %14 to [15680 x float]*
  %43 = bitcast float* %15 to [38416 x float]*
  %44 = bitcast float* %16 to [38416 x float]*
  %45 = bitcast float* %17 to [15680 x float]*
  %46 = bitcast float* %18 to [15680 x float]*
  %47 = bitcast float* %19 to [15680 x float]*
  %48 = bitcast float* %20 to [15680 x float]*
  %49 = bitcast float* %21 to [47040 x float]*
  %50 = bitcast float* %22 to [19200 x float]*
  %51 = bitcast float* %23 to [240 x float]*
  %52 = bitcast float* %24 to [47040 x float]*
  %53 = bitcast float* %25 to [47040 x float]*
  %54 = bitcast float* %26 to [47040 x float]*
  %55 = bitcast float* %27 to [47040 x float]*
  call void @copy_out([15680 x float]* null, [15680 x float]* %28, [15680 x float]* null, [15680 x float]* %29, [80 x float]* null, [80 x float]* %30, [80 x float]* null, [80 x float]* %31, [80 x float]* null, [80 x float]* %32, [80 x float]* null, [80 x float]* %33, [15680 x float]* null, [15680 x float]* %34, [15680 x float]* null, [15680 x float]* %35, [15680 x float]* null, [15680 x float]* %36, [31360 x float]* null, [31360 x float]* %37, [12800 x float]* null, [12800 x float]* %38, [160 x float]* null, [160 x float]* %39, [31360 x float]* null, [31360 x float]* %40, [15680 x float]* null, [15680 x float]* %41, [15680 x float]* null, [15680 x float]* %42, [38416 x float]* null, [38416 x float]* %43, [38416 x float]* null, [38416 x float]* %44, [15680 x float]* null, [15680 x float]* %45, [15680 x float]* null, [15680 x float]* %46, [15680 x float]* null, [15680 x float]* %47, [15680 x float]* null, [15680 x float]* %48, [47040 x float]* null, [47040 x float]* %49, [19200 x float]* null, [19200 x float]* %50, [240 x float]* null, [240 x float]* %51, [47040 x float]* null, [47040 x float]* %52, [47040 x float]* null, [47040 x float]* %53, [47040 x float]* null, [47040 x float]* %54, [47040 x float]* null, [47040 x float]* %55)
  %56 = bitcast [15680 x float]* %28 to float*
  %57 = bitcast [15680 x float]* %29 to float*
  %58 = bitcast [80 x float]* %30 to float*
  %59 = bitcast [80 x float]* %31 to float*
  %60 = bitcast [80 x float]* %32 to float*
  %61 = bitcast [80 x float]* %33 to float*
  %62 = bitcast [15680 x float]* %34 to float*
  %63 = bitcast [15680 x float]* %35 to float*
  %64 = bitcast [15680 x float]* %36 to float*
  %65 = bitcast [31360 x float]* %37 to float*
  %66 = bitcast [12800 x float]* %38 to float*
  %67 = bitcast [160 x float]* %39 to float*
  %68 = bitcast [31360 x float]* %40 to float*
  %69 = bitcast [15680 x float]* %41 to float*
  %70 = bitcast [15680 x float]* %42 to float*
  %71 = bitcast [38416 x float]* %43 to float*
  %72 = bitcast [38416 x float]* %44 to float*
  %73 = bitcast [15680 x float]* %45 to float*
  %74 = bitcast [15680 x float]* %46 to float*
  %75 = bitcast [15680 x float]* %47 to float*
  %76 = bitcast [15680 x float]* %48 to float*
  %77 = bitcast [47040 x float]* %49 to float*
  %78 = bitcast [19200 x float]* %50 to float*
  %79 = bitcast [240 x float]* %51 to float*
  %80 = bitcast [47040 x float]* %52 to float*
  %81 = bitcast [47040 x float]* %53 to float*
  %82 = bitcast [47040 x float]* %54 to float*
  %83 = bitcast [47040 x float]* %55 to float*
  call void @kernel_attention_hw_stub(float* %56, float* %57, float* %58, float* %59, float* %60, float* %61, float* %62, float* %63, float* %64, float* %65, float* %66, float* %67, float* %68, float* %69, float* %70, float* %71, float* %72, float* %73, float* %74, float* %75, float* %76, float* %77, float* %78, float* %79, float* %80, float* %81, float* %82, float* %83)
  call void @copy_in([15680 x float]* null, [15680 x float]* %28, [15680 x float]* null, [15680 x float]* %29, [80 x float]* null, [80 x float]* %30, [80 x float]* null, [80 x float]* %31, [80 x float]* null, [80 x float]* %32, [80 x float]* null, [80 x float]* %33, [15680 x float]* null, [15680 x float]* %34, [15680 x float]* null, [15680 x float]* %35, [15680 x float]* null, [15680 x float]* %36, [31360 x float]* null, [31360 x float]* %37, [12800 x float]* null, [12800 x float]* %38, [160 x float]* null, [160 x float]* %39, [31360 x float]* null, [31360 x float]* %40, [15680 x float]* null, [15680 x float]* %41, [15680 x float]* null, [15680 x float]* %42, [38416 x float]* null, [38416 x float]* %43, [38416 x float]* null, [38416 x float]* %44, [15680 x float]* null, [15680 x float]* %45, [15680 x float]* null, [15680 x float]* %46, [15680 x float]* null, [15680 x float]* %47, [15680 x float]* null, [15680 x float]* %48, [47040 x float]* null, [47040 x float]* %49, [19200 x float]* null, [19200 x float]* %50, [240 x float]* null, [240 x float]* %51, [47040 x float]* null, [47040 x float]* %52, [47040 x float]* null, [47040 x float]* %53, [47040 x float]* null, [47040 x float]* %54, [47040 x float]* null, [47040 x float]* %55)
  ret void
}

declare void @kernel_attention_hw_stub(float*, float*, float*, float*, float*, float*, float*, float*, float*, float*, float*, float*, float*, float*, float*, float*, float*, float*, float*, float*, float*, float*, float*, float*, float*, float*, float*, float*)

attributes #0 = { noinline "fpga.wrapper.func"="wrapper" }
attributes #1 = { argmemonly noinline norecurse "fpga.wrapper.func"="copyin" }
attributes #2 = { argmemonly noinline norecurse "fpga.wrapper.func"="onebyonecpy_hls" }
attributes #3 = { argmemonly noinline norecurse "fpga.wrapper.func"="copyout" }
attributes #4 = { "fpga.wrapper.func"="stub" }

!llvm.dbg.cu = !{}
!llvm.ident = !{!0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0}
!llvm.module.flags = !{!1, !2, !3}
!blackbox_cfg = !{!4}

!0 = !{!"clang version 7.0.0 "}
!1 = !{i32 2, !"Dwarf Version", i32 4}
!2 = !{i32 2, !"Debug Info Version", i32 3}
!3 = !{i32 1, !"wchar_size", i32 4}
!4 = !{}
