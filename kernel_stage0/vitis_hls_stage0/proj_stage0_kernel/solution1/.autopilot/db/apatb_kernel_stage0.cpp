#include <systemc>
#include <iostream>
#include <cstdlib>
#include <cstddef>
#include <stdint.h>
#include "SysCFileHandler.h"
#include "ap_int.h"
#include "ap_fixed.h"
#include <complex>
#include <stdbool.h>
#include "autopilot_cbe.h"
#include "hls_stream.h"
#include "hls_half.h"
#include "hls_signal_handler.h"

using namespace std;
using namespace sc_core;
using namespace sc_dt;

// wrapc file define:
#define AUTOTB_TVIN_X_data "../tv/cdatafile/c.kernel_stage0.autotvin_X_data.dat"
#define AUTOTB_TVOUT_X_data "../tv/cdatafile/c.kernel_stage0.autotvout_X_data.dat"
#define AUTOTB_TVIN_msp_conv_weight "../tv/cdatafile/c.kernel_stage0.autotvin_msp_conv_weight.dat"
#define AUTOTB_TVOUT_msp_conv_weight "../tv/cdatafile/c.kernel_stage0.autotvout_msp_conv_weight.dat"
#define AUTOTB_TVIN_msp_conv_bias "../tv/cdatafile/c.kernel_stage0.autotvin_msp_conv_bias.dat"
#define AUTOTB_TVOUT_msp_conv_bias "../tv/cdatafile/c.kernel_stage0.autotvout_msp_conv_bias.dat"
#define AUTOTB_TVIN_msp_norm_weight "../tv/cdatafile/c.kernel_stage0.autotvin_msp_norm_weight.dat"
#define AUTOTB_TVOUT_msp_norm_weight "../tv/cdatafile/c.kernel_stage0.autotvout_msp_norm_weight.dat"
#define AUTOTB_TVIN_msp_norm_bias "../tv/cdatafile/c.kernel_stage0.autotvin_msp_norm_bias.dat"
#define AUTOTB_TVOUT_msp_norm_bias "../tv/cdatafile/c.kernel_stage0.autotvout_msp_norm_bias.dat"
#define AUTOTB_TVIN_msp_norm_running_mean "../tv/cdatafile/c.kernel_stage0.autotvin_msp_norm_running_mean.dat"
#define AUTOTB_TVOUT_msp_norm_running_mean "../tv/cdatafile/c.kernel_stage0.autotvout_msp_norm_running_mean.dat"
#define AUTOTB_TVIN_msp_norm_running_var "../tv/cdatafile/c.kernel_stage0.autotvin_msp_norm_running_var.dat"
#define AUTOTB_TVOUT_msp_norm_running_var "../tv/cdatafile/c.kernel_stage0.autotvout_msp_norm_running_var.dat"
#define AUTOTB_TVIN_dw_conv_weight "../tv/cdatafile/c.kernel_stage0.autotvin_dw_conv_weight.dat"
#define AUTOTB_TVOUT_dw_conv_weight "../tv/cdatafile/c.kernel_stage0.autotvout_dw_conv_weight.dat"
#define AUTOTB_TVIN_norm_1_weight "../tv/cdatafile/c.kernel_stage0.autotvin_norm_1_weight.dat"
#define AUTOTB_TVOUT_norm_1_weight "../tv/cdatafile/c.kernel_stage0.autotvout_norm_1_weight.dat"
#define AUTOTB_TVIN_norm_1_bias "../tv/cdatafile/c.kernel_stage0.autotvin_norm_1_bias.dat"
#define AUTOTB_TVOUT_norm_1_bias "../tv/cdatafile/c.kernel_stage0.autotvout_norm_1_bias.dat"
#define AUTOTB_TVIN_norm_1_running_mean "../tv/cdatafile/c.kernel_stage0.autotvin_norm_1_running_mean.dat"
#define AUTOTB_TVOUT_norm_1_running_mean "../tv/cdatafile/c.kernel_stage0.autotvout_norm_1_running_mean.dat"
#define AUTOTB_TVIN_norm_1_running_var "../tv/cdatafile/c.kernel_stage0.autotvin_norm_1_running_var.dat"
#define AUTOTB_TVOUT_norm_1_running_var "../tv/cdatafile/c.kernel_stage0.autotvout_norm_1_running_var.dat"
#define AUTOTB_TVIN_se_conv_reduce_weight "../tv/cdatafile/c.kernel_stage0.autotvin_se_conv_reduce_weight.dat"
#define AUTOTB_TVOUT_se_conv_reduce_weight "../tv/cdatafile/c.kernel_stage0.autotvout_se_conv_reduce_weight.dat"
#define AUTOTB_TVIN_se_conv_reduce_bias "../tv/cdatafile/c.kernel_stage0.autotvin_se_conv_reduce_bias.dat"
#define AUTOTB_TVOUT_se_conv_reduce_bias "../tv/cdatafile/c.kernel_stage0.autotvout_se_conv_reduce_bias.dat"
#define AUTOTB_TVIN_se_conv_expand_weight "../tv/cdatafile/c.kernel_stage0.autotvin_se_conv_expand_weight.dat"
#define AUTOTB_TVOUT_se_conv_expand_weight "../tv/cdatafile/c.kernel_stage0.autotvout_se_conv_expand_weight.dat"
#define AUTOTB_TVIN_se_conv_expand_bias "../tv/cdatafile/c.kernel_stage0.autotvin_se_conv_expand_bias.dat"
#define AUTOTB_TVOUT_se_conv_expand_bias "../tv/cdatafile/c.kernel_stage0.autotvout_se_conv_expand_bias.dat"
#define AUTOTB_TVIN_proj_conv_weight "../tv/cdatafile/c.kernel_stage0.autotvin_proj_conv_weight.dat"
#define AUTOTB_TVOUT_proj_conv_weight "../tv/cdatafile/c.kernel_stage0.autotvout_proj_conv_weight.dat"
#define AUTOTB_TVIN_Y_msp_conv "../tv/cdatafile/c.kernel_stage0.autotvin_Y_msp_conv.dat"
#define AUTOTB_TVOUT_Y_msp_conv "../tv/cdatafile/c.kernel_stage0.autotvout_Y_msp_conv.dat"
#define AUTOTB_TVIN_Y_msp_norm "../tv/cdatafile/c.kernel_stage0.autotvin_Y_msp_norm.dat"
#define AUTOTB_TVOUT_Y_msp_norm "../tv/cdatafile/c.kernel_stage0.autotvout_Y_msp_norm.dat"
#define AUTOTB_TVIN_Y_dw_conv "../tv/cdatafile/c.kernel_stage0.autotvin_Y_dw_conv.dat"
#define AUTOTB_TVOUT_Y_dw_conv "../tv/cdatafile/c.kernel_stage0.autotvout_Y_dw_conv.dat"
#define AUTOTB_TVIN_Y_dw_norm "../tv/cdatafile/c.kernel_stage0.autotvin_Y_dw_norm.dat"
#define AUTOTB_TVOUT_Y_dw_norm "../tv/cdatafile/c.kernel_stage0.autotvout_Y_dw_norm.dat"
#define AUTOTB_TVIN_Y_dw_act "../tv/cdatafile/c.kernel_stage0.autotvin_Y_dw_act.dat"
#define AUTOTB_TVOUT_Y_dw_act "../tv/cdatafile/c.kernel_stage0.autotvout_Y_dw_act.dat"
#define AUTOTB_TVIN_Y_mean "../tv/cdatafile/c.kernel_stage0.autotvin_Y_mean.dat"
#define AUTOTB_TVOUT_Y_mean "../tv/cdatafile/c.kernel_stage0.autotvout_Y_mean.dat"
#define AUTOTB_TVIN_Y_reduce "../tv/cdatafile/c.kernel_stage0.autotvin_Y_reduce.dat"
#define AUTOTB_TVOUT_Y_reduce "../tv/cdatafile/c.kernel_stage0.autotvout_Y_reduce.dat"
#define AUTOTB_TVIN_Y_relu "../tv/cdatafile/c.kernel_stage0.autotvin_Y_relu.dat"
#define AUTOTB_TVOUT_Y_relu "../tv/cdatafile/c.kernel_stage0.autotvout_Y_relu.dat"
#define AUTOTB_TVIN_Y_expand "../tv/cdatafile/c.kernel_stage0.autotvin_Y_expand.dat"
#define AUTOTB_TVOUT_Y_expand "../tv/cdatafile/c.kernel_stage0.autotvout_Y_expand.dat"
#define AUTOTB_TVIN_Y_sigmoid "../tv/cdatafile/c.kernel_stage0.autotvin_Y_sigmoid.dat"
#define AUTOTB_TVOUT_Y_sigmoid "../tv/cdatafile/c.kernel_stage0.autotvout_Y_sigmoid.dat"
#define AUTOTB_TVIN_Y_se "../tv/cdatafile/c.kernel_stage0.autotvin_Y_se.dat"
#define AUTOTB_TVOUT_Y_se "../tv/cdatafile/c.kernel_stage0.autotvout_Y_se.dat"
#define AUTOTB_TVIN_Y_proj "../tv/cdatafile/c.kernel_stage0.autotvin_Y_proj.dat"
#define AUTOTB_TVOUT_Y_proj "../tv/cdatafile/c.kernel_stage0.autotvout_Y_proj.dat"
#define AUTOTB_TVIN_gmem "../tv/cdatafile/c.kernel_stage0.autotvin_gmem.dat"
#define AUTOTB_TVOUT_gmem "../tv/cdatafile/c.kernel_stage0.autotvout_gmem.dat"
#define AUTOTB_TVIN_gmem0 "../tv/cdatafile/c.kernel_stage0.autotvin_gmem0.dat"
#define AUTOTB_TVOUT_gmem0 "../tv/cdatafile/c.kernel_stage0.autotvout_gmem0.dat"
#define AUTOTB_TVIN_gmem1 "../tv/cdatafile/c.kernel_stage0.autotvin_gmem1.dat"
#define AUTOTB_TVOUT_gmem1 "../tv/cdatafile/c.kernel_stage0.autotvout_gmem1.dat"
#define AUTOTB_TVIN_gmem2 "../tv/cdatafile/c.kernel_stage0.autotvin_gmem2.dat"
#define AUTOTB_TVOUT_gmem2 "../tv/cdatafile/c.kernel_stage0.autotvout_gmem2.dat"
#define AUTOTB_TVIN_gmem3 "../tv/cdatafile/c.kernel_stage0.autotvin_gmem3.dat"
#define AUTOTB_TVOUT_gmem3 "../tv/cdatafile/c.kernel_stage0.autotvout_gmem3.dat"

#define INTER_TCL "../tv/cdatafile/ref.tcl"

// tvout file define:
#define AUTOTB_TVOUT_PC_X_data "../tv/rtldatafile/rtl.kernel_stage0.autotvout_X_data.dat"
#define AUTOTB_TVOUT_PC_msp_conv_weight "../tv/rtldatafile/rtl.kernel_stage0.autotvout_msp_conv_weight.dat"
#define AUTOTB_TVOUT_PC_msp_conv_bias "../tv/rtldatafile/rtl.kernel_stage0.autotvout_msp_conv_bias.dat"
#define AUTOTB_TVOUT_PC_msp_norm_weight "../tv/rtldatafile/rtl.kernel_stage0.autotvout_msp_norm_weight.dat"
#define AUTOTB_TVOUT_PC_msp_norm_bias "../tv/rtldatafile/rtl.kernel_stage0.autotvout_msp_norm_bias.dat"
#define AUTOTB_TVOUT_PC_msp_norm_running_mean "../tv/rtldatafile/rtl.kernel_stage0.autotvout_msp_norm_running_mean.dat"
#define AUTOTB_TVOUT_PC_msp_norm_running_var "../tv/rtldatafile/rtl.kernel_stage0.autotvout_msp_norm_running_var.dat"
#define AUTOTB_TVOUT_PC_dw_conv_weight "../tv/rtldatafile/rtl.kernel_stage0.autotvout_dw_conv_weight.dat"
#define AUTOTB_TVOUT_PC_norm_1_weight "../tv/rtldatafile/rtl.kernel_stage0.autotvout_norm_1_weight.dat"
#define AUTOTB_TVOUT_PC_norm_1_bias "../tv/rtldatafile/rtl.kernel_stage0.autotvout_norm_1_bias.dat"
#define AUTOTB_TVOUT_PC_norm_1_running_mean "../tv/rtldatafile/rtl.kernel_stage0.autotvout_norm_1_running_mean.dat"
#define AUTOTB_TVOUT_PC_norm_1_running_var "../tv/rtldatafile/rtl.kernel_stage0.autotvout_norm_1_running_var.dat"
#define AUTOTB_TVOUT_PC_se_conv_reduce_weight "../tv/rtldatafile/rtl.kernel_stage0.autotvout_se_conv_reduce_weight.dat"
#define AUTOTB_TVOUT_PC_se_conv_reduce_bias "../tv/rtldatafile/rtl.kernel_stage0.autotvout_se_conv_reduce_bias.dat"
#define AUTOTB_TVOUT_PC_se_conv_expand_weight "../tv/rtldatafile/rtl.kernel_stage0.autotvout_se_conv_expand_weight.dat"
#define AUTOTB_TVOUT_PC_se_conv_expand_bias "../tv/rtldatafile/rtl.kernel_stage0.autotvout_se_conv_expand_bias.dat"
#define AUTOTB_TVOUT_PC_proj_conv_weight "../tv/rtldatafile/rtl.kernel_stage0.autotvout_proj_conv_weight.dat"
#define AUTOTB_TVOUT_PC_Y_msp_conv "../tv/rtldatafile/rtl.kernel_stage0.autotvout_Y_msp_conv.dat"
#define AUTOTB_TVOUT_PC_Y_msp_norm "../tv/rtldatafile/rtl.kernel_stage0.autotvout_Y_msp_norm.dat"
#define AUTOTB_TVOUT_PC_Y_dw_conv "../tv/rtldatafile/rtl.kernel_stage0.autotvout_Y_dw_conv.dat"
#define AUTOTB_TVOUT_PC_Y_dw_norm "../tv/rtldatafile/rtl.kernel_stage0.autotvout_Y_dw_norm.dat"
#define AUTOTB_TVOUT_PC_Y_dw_act "../tv/rtldatafile/rtl.kernel_stage0.autotvout_Y_dw_act.dat"
#define AUTOTB_TVOUT_PC_Y_mean "../tv/rtldatafile/rtl.kernel_stage0.autotvout_Y_mean.dat"
#define AUTOTB_TVOUT_PC_Y_reduce "../tv/rtldatafile/rtl.kernel_stage0.autotvout_Y_reduce.dat"
#define AUTOTB_TVOUT_PC_Y_relu "../tv/rtldatafile/rtl.kernel_stage0.autotvout_Y_relu.dat"
#define AUTOTB_TVOUT_PC_Y_expand "../tv/rtldatafile/rtl.kernel_stage0.autotvout_Y_expand.dat"
#define AUTOTB_TVOUT_PC_Y_sigmoid "../tv/rtldatafile/rtl.kernel_stage0.autotvout_Y_sigmoid.dat"
#define AUTOTB_TVOUT_PC_Y_se "../tv/rtldatafile/rtl.kernel_stage0.autotvout_Y_se.dat"
#define AUTOTB_TVOUT_PC_Y_proj "../tv/rtldatafile/rtl.kernel_stage0.autotvout_Y_proj.dat"
#define AUTOTB_TVOUT_PC_gmem "../tv/rtldatafile/rtl.kernel_stage0.autotvout_gmem.dat"
#define AUTOTB_TVOUT_PC_gmem0 "../tv/rtldatafile/rtl.kernel_stage0.autotvout_gmem0.dat"
#define AUTOTB_TVOUT_PC_gmem1 "../tv/rtldatafile/rtl.kernel_stage0.autotvout_gmem1.dat"
#define AUTOTB_TVOUT_PC_gmem2 "../tv/rtldatafile/rtl.kernel_stage0.autotvout_gmem2.dat"
#define AUTOTB_TVOUT_PC_gmem3 "../tv/rtldatafile/rtl.kernel_stage0.autotvout_gmem3.dat"


static const bool little_endian()
{
  int a = 1;
  return *(char*)&a == 1;
}

inline static void rev_endian(char* p, size_t nbytes)
{
  std::reverse(p, p+nbytes);
}

template<size_t bit_width>
struct transaction {
  typedef uint64_t depth_t;
  static const size_t wbytes = (bit_width+7)>>3;
  static const size_t dbytes = sizeof(depth_t);
  const depth_t depth;
  const size_t vbytes;
  const size_t tbytes;
  char * const p;
  typedef char (*p_dat)[wbytes];
  p_dat vp;

  transaction(depth_t depth)
    : depth(depth), vbytes(wbytes*depth), tbytes(dbytes+vbytes),
      p(new char[tbytes]) {
    *(depth_t*)p = depth;
    rev_endian(p, dbytes);
    vp = (p_dat) (p+dbytes);
  }

  void reorder() {
    rev_endian(p, dbytes);
    p_dat vp = (p_dat) (p+dbytes);
    for (depth_t i = 0; i < depth; ++i) {
      rev_endian(vp[i], wbytes);
    }
  }

  template<size_t psize>
  void import(char* param, depth_t num, int64_t offset) {
    param -= offset*psize;
    for (depth_t i = 0; i < num; ++i) {
      memcpy(vp[i], param, wbytes);
      param += psize;
      if (little_endian()) {
        rev_endian(vp[i], wbytes);
      }
    }
    vp += num;
  }

  template<size_t psize>
  void send(char* param, depth_t num) {
    for (depth_t i = 0; i < num; ++i) {
      memcpy(param, vp[i], wbytes);
      param += psize;
    }
    vp += num;
  }

  template<size_t psize>
  void send(char* param, depth_t num, int64_t skip) {
    for (depth_t i = 0; i < num; ++i) {
      memcpy(param, vp[skip+i], wbytes);
      param += psize;
    }
  }

  ~transaction() { if (p) { delete[] p; } }
};


inline static const std::string begin_str(int num)
{
  return std::string("[[transaction]]           ")
         .append(std::to_string(num))
         .append("\n");
}

inline static const std::string end_str()
{
  return std::string("[[/transaction]]\n");
}

const std::string formatData(unsigned char *pos, size_t wbits)
{
  bool LE = little_endian();
  size_t wbytes = (wbits+7)>>3;
  size_t i = LE ? wbytes-1 : 0;
  auto next = [&] () {
    auto c = pos[i];
    LE ? --i : ++i;
    return c;
  };
  std::ostringstream ss;
  ss << "0x";
  if (int t = (wbits & 0x7)) {
    if (t <= 4) {
      unsigned char mask = (1<<t)-1;
      ss << std::hex << std::setfill('0') << std::setw(1)
         << (int) (next() & mask);
      wbytes -= 1;
    }
  }
  for (size_t i = 0; i < wbytes; ++i) {
    ss << std::hex << std::setfill('0') << std::setw(2) << (int)next();
  }
  ss.put('\n');
  return ss.str();
}

static bool RTLOutputCheckAndReplacement(std::string &data)
{
  bool changed = false;
  for (size_t i = 2; i < data.size(); ++i) {
    if (data[i] == 'X' || data[i] == 'x') {
      data[i] = '0';
      changed = true;
    }
  }
  return changed;
}

struct SimException : public std::exception {
  const char *msg;
  const size_t line;
  SimException(const char *msg, const size_t line)
    : msg(msg), line(line)
  {
  }
};

template<size_t bit_width>
class PostCheck
{
  static const char *bad;
  static const char *err;
  std::fstream stream;
  std::string s;

  void send(char *p, ap_uint<bit_width> &data, size_t l, size_t rest)
  {
    if (rest == 0) {
      if (!little_endian()) {
        const size_t wbytes = (bit_width+7)>>3;
        rev_endian(p-wbytes, wbytes);
      }
    } else if (rest < 8) {
      *p = data.range(l+rest-1, l).to_uint();
      send(p+1, data, l+rest, 0);
    } else {
      *p = data.range(l+8-1, l).to_uint();
      send(p+1, data, l+8, rest-8);
    }
  }

  void readline()
  {
    std::getline(stream, s);
    if (stream.eof()) {
      throw SimException(bad, __LINE__);
    }
  }

public:
  char *param;
  size_t psize;
  size_t depth;

  PostCheck(const char *file)
  {
    stream.open(file);
    if (stream.fail()) {
      throw SimException(err, __LINE__);
    } else {
      readline();
      if (s != "[[[runtime]]]") {
        throw SimException(bad, __LINE__);
      }
    }
  }

  ~PostCheck() noexcept(false)
  {
    stream.close();
  }

  void run(size_t AESL_transaction_pc, size_t skip)
  {
    if (stream.peek() == '[') {
      readline();
    }

    for (size_t i = 0; i < skip; ++i) {
      readline();
    }

    bool foundX = false;
    for (size_t i = 0; i < depth; ++i) {
      readline();
      foundX |= RTLOutputCheckAndReplacement(s);
      ap_uint<bit_width> data(s.c_str(), 16);
      send(param+i*psize, data, 0, bit_width);
    }
    if (foundX) {
      std::cerr << "WARNING: [SIM 212-201] RTL produces unknown value "
                << "'x' or 'X' on some port, possible cause: "
                << "There are uninitialized variables in the design.\n";
    }

    if (stream.peek() == '[') {
      readline();
    }
  }
};

template<size_t bit_width>
const char* PostCheck<bit_width>::bad = "Bad TV file";

template<size_t bit_width>
const char* PostCheck<bit_width>::err = "Error on TV file";
      
class INTER_TCL_FILE {
  public:
INTER_TCL_FILE(const char* name) {
  mName = name; 
  X_data_depth = 0;
  msp_conv_weight_depth = 0;
  msp_conv_bias_depth = 0;
  msp_norm_weight_depth = 0;
  msp_norm_bias_depth = 0;
  msp_norm_running_mean_depth = 0;
  msp_norm_running_var_depth = 0;
  dw_conv_weight_depth = 0;
  norm_1_weight_depth = 0;
  norm_1_bias_depth = 0;
  norm_1_running_mean_depth = 0;
  norm_1_running_var_depth = 0;
  se_conv_reduce_weight_depth = 0;
  se_conv_reduce_bias_depth = 0;
  se_conv_expand_weight_depth = 0;
  se_conv_expand_bias_depth = 0;
  proj_conv_weight_depth = 0;
  Y_msp_conv_depth = 0;
  Y_msp_norm_depth = 0;
  Y_dw_conv_depth = 0;
  Y_dw_norm_depth = 0;
  Y_dw_act_depth = 0;
  Y_mean_depth = 0;
  Y_reduce_depth = 0;
  Y_relu_depth = 0;
  Y_expand_depth = 0;
  Y_sigmoid_depth = 0;
  Y_se_depth = 0;
  Y_proj_depth = 0;
  gmem_depth = 0;
  gmem0_depth = 0;
  gmem1_depth = 0;
  gmem2_depth = 0;
  gmem3_depth = 0;
  trans_num =0;
}
~INTER_TCL_FILE() {
  mFile.open(mName);
  if (!mFile.good()) {
    cout << "Failed to open file ref.tcl" << endl;
    exit (1); 
  }
  string total_list = get_depth_list();
  mFile << "set depth_list {\n";
  mFile << total_list;
  mFile << "}\n";
  mFile << "set trans_num "<<trans_num<<endl;
  mFile.close();
}
string get_depth_list () {
  stringstream total_list;
  total_list << "{X_data " << X_data_depth << "}\n";
  total_list << "{msp_conv_weight " << msp_conv_weight_depth << "}\n";
  total_list << "{msp_conv_bias " << msp_conv_bias_depth << "}\n";
  total_list << "{msp_norm_weight " << msp_norm_weight_depth << "}\n";
  total_list << "{msp_norm_bias " << msp_norm_bias_depth << "}\n";
  total_list << "{msp_norm_running_mean " << msp_norm_running_mean_depth << "}\n";
  total_list << "{msp_norm_running_var " << msp_norm_running_var_depth << "}\n";
  total_list << "{dw_conv_weight " << dw_conv_weight_depth << "}\n";
  total_list << "{norm_1_weight " << norm_1_weight_depth << "}\n";
  total_list << "{norm_1_bias " << norm_1_bias_depth << "}\n";
  total_list << "{norm_1_running_mean " << norm_1_running_mean_depth << "}\n";
  total_list << "{norm_1_running_var " << norm_1_running_var_depth << "}\n";
  total_list << "{se_conv_reduce_weight " << se_conv_reduce_weight_depth << "}\n";
  total_list << "{se_conv_reduce_bias " << se_conv_reduce_bias_depth << "}\n";
  total_list << "{se_conv_expand_weight " << se_conv_expand_weight_depth << "}\n";
  total_list << "{se_conv_expand_bias " << se_conv_expand_bias_depth << "}\n";
  total_list << "{proj_conv_weight " << proj_conv_weight_depth << "}\n";
  total_list << "{Y_msp_conv " << Y_msp_conv_depth << "}\n";
  total_list << "{Y_msp_norm " << Y_msp_norm_depth << "}\n";
  total_list << "{Y_dw_conv " << Y_dw_conv_depth << "}\n";
  total_list << "{Y_dw_norm " << Y_dw_norm_depth << "}\n";
  total_list << "{Y_dw_act " << Y_dw_act_depth << "}\n";
  total_list << "{Y_mean " << Y_mean_depth << "}\n";
  total_list << "{Y_reduce " << Y_reduce_depth << "}\n";
  total_list << "{Y_relu " << Y_relu_depth << "}\n";
  total_list << "{Y_expand " << Y_expand_depth << "}\n";
  total_list << "{Y_sigmoid " << Y_sigmoid_depth << "}\n";
  total_list << "{Y_se " << Y_se_depth << "}\n";
  total_list << "{Y_proj " << Y_proj_depth << "}\n";
  total_list << "{gmem " << gmem_depth << "}\n";
  total_list << "{gmem0 " << gmem0_depth << "}\n";
  total_list << "{gmem1 " << gmem1_depth << "}\n";
  total_list << "{gmem2 " << gmem2_depth << "}\n";
  total_list << "{gmem3 " << gmem3_depth << "}\n";
  return total_list.str();
}
void set_num (int num , int* class_num) {
  (*class_num) = (*class_num) > num ? (*class_num) : num;
}
void set_string(std::string list, std::string* class_list) {
  (*class_list) = list;
}
  public:
    int X_data_depth;
    int msp_conv_weight_depth;
    int msp_conv_bias_depth;
    int msp_norm_weight_depth;
    int msp_norm_bias_depth;
    int msp_norm_running_mean_depth;
    int msp_norm_running_var_depth;
    int dw_conv_weight_depth;
    int norm_1_weight_depth;
    int norm_1_bias_depth;
    int norm_1_running_mean_depth;
    int norm_1_running_var_depth;
    int se_conv_reduce_weight_depth;
    int se_conv_reduce_bias_depth;
    int se_conv_expand_weight_depth;
    int se_conv_expand_bias_depth;
    int proj_conv_weight_depth;
    int Y_msp_conv_depth;
    int Y_msp_norm_depth;
    int Y_dw_conv_depth;
    int Y_dw_norm_depth;
    int Y_dw_act_depth;
    int Y_mean_depth;
    int Y_reduce_depth;
    int Y_relu_depth;
    int Y_expand_depth;
    int Y_sigmoid_depth;
    int Y_se_depth;
    int Y_proj_depth;
    int gmem_depth;
    int gmem0_depth;
    int gmem1_depth;
    int gmem2_depth;
    int gmem3_depth;
    int trans_num;
  private:
    ofstream mFile;
    const char* mName;
};


extern "C" void kernel_stage0_hw_stub_wrapper(volatile void *, volatile void *, volatile void *, volatile void *, volatile void *, volatile void *, volatile void *, volatile void *, volatile void *, volatile void *, volatile void *, volatile void *, volatile void *, volatile void *, volatile void *, volatile void *, volatile void *, volatile void *, volatile void *, volatile void *, volatile void *, volatile void *, volatile void *, volatile void *, volatile void *, volatile void *, volatile void *, volatile void *, volatile void *);

extern "C" void apatb_kernel_stage0_hw(volatile void * __xlx_apatb_param_X_data, volatile void * __xlx_apatb_param_msp_conv_weight, volatile void * __xlx_apatb_param_msp_conv_bias, volatile void * __xlx_apatb_param_msp_norm_weight, volatile void * __xlx_apatb_param_msp_norm_bias, volatile void * __xlx_apatb_param_msp_norm_running_mean, volatile void * __xlx_apatb_param_msp_norm_running_var, volatile void * __xlx_apatb_param_dw_conv_weight, volatile void * __xlx_apatb_param_norm_1_weight, volatile void * __xlx_apatb_param_norm_1_bias, volatile void * __xlx_apatb_param_norm_1_running_mean, volatile void * __xlx_apatb_param_norm_1_running_var, volatile void * __xlx_apatb_param_se_conv_reduce_weight, volatile void * __xlx_apatb_param_se_conv_reduce_bias, volatile void * __xlx_apatb_param_se_conv_expand_weight, volatile void * __xlx_apatb_param_se_conv_expand_bias, volatile void * __xlx_apatb_param_proj_conv_weight, volatile void * __xlx_apatb_param_Y_msp_conv, volatile void * __xlx_apatb_param_Y_msp_norm, volatile void * __xlx_apatb_param_Y_dw_conv, volatile void * __xlx_apatb_param_Y_dw_norm, volatile void * __xlx_apatb_param_Y_dw_act, volatile void * __xlx_apatb_param_Y_mean, volatile void * __xlx_apatb_param_Y_reduce, volatile void * __xlx_apatb_param_Y_relu, volatile void * __xlx_apatb_param_Y_expand, volatile void * __xlx_apatb_param_Y_sigmoid, volatile void * __xlx_apatb_param_Y_se, volatile void * __xlx_apatb_param_Y_proj) {
  refine_signal_handler();
  fstream wrapc_switch_file_token;
  wrapc_switch_file_token.open(".hls_cosim_wrapc_switch.log");
static AESL_FILE_HANDLER aesl_fh;
  int AESL_i;
  if (wrapc_switch_file_token.good())
  {

    CodeState = ENTER_WRAPC_PC;
    static unsigned AESL_transaction_pc = 0;
    string AESL_token;
    string AESL_num;
#ifdef USE_BINARY_TV_FILE
{
transaction<32> tr(752664);
aesl_fh.read(AUTOTB_TVOUT_PC_gmem0, tr.p, tr.tbytes);
if (little_endian()) { tr.reorder(); }
tr.send<4>((char*)__xlx_apatb_param_X_data, 150528, 0);
tr.send<4>((char*)__xlx_apatb_param_Y_dw_norm, 301056, 150528);
tr.send<4>((char*)__xlx_apatb_param_Y_relu, 24, 451584);
tr.send<4>((char*)__xlx_apatb_param_Y_proj, 301056, 451608);
}
#else
try {
static PostCheck<32> pc(AUTOTB_TVOUT_PC_gmem0);
pc.psize = 4;
pc.param = (char*)__xlx_apatb_param_X_data;
pc.depth = 150528;
pc.run(AESL_transaction_pc, 0);pc.param = (char*)__xlx_apatb_param_Y_dw_norm;
pc.depth = 301056;
pc.run(AESL_transaction_pc, 0);
pc.param = (char*)__xlx_apatb_param_Y_relu;
pc.depth = 24;
pc.run(AESL_transaction_pc, 0);
pc.param = (char*)__xlx_apatb_param_Y_proj;
pc.depth = 301056;
pc.run(AESL_transaction_pc, 0);

} catch (SimException &e) {
  std::cout << "at line " << e.line << " occurred exception, " << e.msg << "\n";
}
#endif
#ifdef USE_BINARY_TV_FILE
{
transaction<32> tr(602136);
aesl_fh.read(AUTOTB_TVOUT_PC_gmem1, tr.p, tr.tbytes);
if (little_endian()) { tr.reorder(); }
tr.send<4>((char*)__xlx_apatb_param_Y_msp_conv, 301056, 0);
tr.send<4>((char*)__xlx_apatb_param_Y_dw_act, 301056, 301056);
tr.send<4>((char*)__xlx_apatb_param_Y_expand, 24, 602112);
}
#else
try {
static PostCheck<32> pc(AUTOTB_TVOUT_PC_gmem1);
pc.psize = 4;
pc.param = (char*)__xlx_apatb_param_Y_msp_conv;
pc.depth = 301056;
pc.run(AESL_transaction_pc, 0);pc.param = (char*)__xlx_apatb_param_Y_dw_act;
pc.depth = 301056;
pc.run(AESL_transaction_pc, 0);
pc.param = (char*)__xlx_apatb_param_Y_expand;
pc.depth = 24;
pc.run(AESL_transaction_pc, 0);

} catch (SimException &e) {
  std::cout << "at line " << e.line << " occurred exception, " << e.msg << "\n";
}
#endif
#ifdef USE_BINARY_TV_FILE
{
transaction<32> tr(301104);
aesl_fh.read(AUTOTB_TVOUT_PC_gmem2, tr.p, tr.tbytes);
if (little_endian()) { tr.reorder(); }
tr.send<4>((char*)__xlx_apatb_param_Y_msp_norm, 301056, 0);
tr.send<4>((char*)__xlx_apatb_param_Y_mean, 24, 301056);
tr.send<4>((char*)__xlx_apatb_param_Y_sigmoid, 24, 301080);
}
#else
try {
static PostCheck<32> pc(AUTOTB_TVOUT_PC_gmem2);
pc.psize = 4;
pc.param = (char*)__xlx_apatb_param_Y_msp_norm;
pc.depth = 301056;
pc.run(AESL_transaction_pc, 0);pc.param = (char*)__xlx_apatb_param_Y_mean;
pc.depth = 24;
pc.run(AESL_transaction_pc, 0);
pc.param = (char*)__xlx_apatb_param_Y_sigmoid;
pc.depth = 24;
pc.run(AESL_transaction_pc, 0);

} catch (SimException &e) {
  std::cout << "at line " << e.line << " occurred exception, " << e.msg << "\n";
}
#endif
#ifdef USE_BINARY_TV_FILE
{
transaction<32> tr(602136);
aesl_fh.read(AUTOTB_TVOUT_PC_gmem3, tr.p, tr.tbytes);
if (little_endian()) { tr.reorder(); }
tr.send<4>((char*)__xlx_apatb_param_Y_dw_conv, 301056, 0);
tr.send<4>((char*)__xlx_apatb_param_Y_reduce, 24, 301056);
tr.send<4>((char*)__xlx_apatb_param_Y_se, 301056, 301080);
}
#else
try {
static PostCheck<32> pc(AUTOTB_TVOUT_PC_gmem3);
pc.psize = 4;
pc.param = (char*)__xlx_apatb_param_Y_dw_conv;
pc.depth = 301056;
pc.run(AESL_transaction_pc, 0);pc.param = (char*)__xlx_apatb_param_Y_reduce;
pc.depth = 24;
pc.run(AESL_transaction_pc, 0);
pc.param = (char*)__xlx_apatb_param_Y_se;
pc.depth = 301056;
pc.run(AESL_transaction_pc, 0);

} catch (SimException &e) {
  std::cout << "at line " << e.line << " occurred exception, " << e.msg << "\n";
}
#endif

    AESL_transaction_pc++;
    return ;
  }
static unsigned AESL_transaction;
static INTER_TCL_FILE tcl_file(INTER_TCL);
std::vector<char> __xlx_sprintf_buffer(1024);
CodeState = ENTER_WRAPC;
CodeState = DUMP_INPUTS;
unsigned __xlx_offset_byte_param_X_data = 0;
unsigned __xlx_offset_byte_param_Y_dw_norm = 0;
unsigned __xlx_offset_byte_param_Y_relu = 0;
unsigned __xlx_offset_byte_param_Y_proj = 0;
unsigned __xlx_offset_byte_param_msp_conv_weight = 0;
unsigned __xlx_offset_byte_param_msp_conv_bias = 0;
unsigned __xlx_offset_byte_param_msp_norm_weight = 0;
unsigned __xlx_offset_byte_param_msp_norm_bias = 0;
unsigned __xlx_offset_byte_param_msp_norm_running_mean = 0;
unsigned __xlx_offset_byte_param_msp_norm_running_var = 0;
unsigned __xlx_offset_byte_param_dw_conv_weight = 0;
unsigned __xlx_offset_byte_param_norm_1_weight = 0;
unsigned __xlx_offset_byte_param_norm_1_bias = 0;
unsigned __xlx_offset_byte_param_norm_1_running_mean = 0;
unsigned __xlx_offset_byte_param_norm_1_running_var = 0;
unsigned __xlx_offset_byte_param_se_conv_reduce_weight = 0;
unsigned __xlx_offset_byte_param_se_conv_reduce_bias = 0;
unsigned __xlx_offset_byte_param_se_conv_expand_weight = 0;
unsigned __xlx_offset_byte_param_se_conv_expand_bias = 0;
unsigned __xlx_offset_byte_param_proj_conv_weight = 0;
unsigned __xlx_offset_byte_param_Y_msp_conv = 0;
unsigned __xlx_offset_byte_param_Y_dw_act = 0;
unsigned __xlx_offset_byte_param_Y_expand = 0;
unsigned __xlx_offset_byte_param_Y_msp_norm = 0;
unsigned __xlx_offset_byte_param_Y_mean = 0;
unsigned __xlx_offset_byte_param_Y_sigmoid = 0;
unsigned __xlx_offset_byte_param_Y_dw_conv = 0;
unsigned __xlx_offset_byte_param_Y_reduce = 0;
unsigned __xlx_offset_byte_param_Y_se = 0;
#ifdef USE_BINARY_TV_FILE
{
aesl_fh.touch(AUTOTB_TVIN_gmem, 'b');
transaction<32> tr(2856);
__xlx_offset_byte_param_msp_conv_weight = 0*4;
if (__xlx_apatb_param_msp_conv_weight) {
  tr.import<4>((char*)__xlx_apatb_param_msp_conv_weight, 648, 0);
}
__xlx_offset_byte_param_msp_conv_bias = 648*4;
if (__xlx_apatb_param_msp_conv_bias) {
  tr.import<4>((char*)__xlx_apatb_param_msp_conv_bias, 24, 0);
}
__xlx_offset_byte_param_msp_norm_weight = 672*4;
if (__xlx_apatb_param_msp_norm_weight) {
  tr.import<4>((char*)__xlx_apatb_param_msp_norm_weight, 24, 0);
}
__xlx_offset_byte_param_msp_norm_bias = 696*4;
if (__xlx_apatb_param_msp_norm_bias) {
  tr.import<4>((char*)__xlx_apatb_param_msp_norm_bias, 24, 0);
}
__xlx_offset_byte_param_msp_norm_running_mean = 720*4;
if (__xlx_apatb_param_msp_norm_running_mean) {
  tr.import<4>((char*)__xlx_apatb_param_msp_norm_running_mean, 24, 0);
}
__xlx_offset_byte_param_msp_norm_running_var = 744*4;
if (__xlx_apatb_param_msp_norm_running_var) {
  tr.import<4>((char*)__xlx_apatb_param_msp_norm_running_var, 24, 0);
}
__xlx_offset_byte_param_dw_conv_weight = 768*4;
if (__xlx_apatb_param_dw_conv_weight) {
  tr.import<4>((char*)__xlx_apatb_param_dw_conv_weight, 216, 0);
}
__xlx_offset_byte_param_norm_1_weight = 984*4;
if (__xlx_apatb_param_norm_1_weight) {
  tr.import<4>((char*)__xlx_apatb_param_norm_1_weight, 24, 0);
}
__xlx_offset_byte_param_norm_1_bias = 1008*4;
if (__xlx_apatb_param_norm_1_bias) {
  tr.import<4>((char*)__xlx_apatb_param_norm_1_bias, 24, 0);
}
__xlx_offset_byte_param_norm_1_running_mean = 1032*4;
if (__xlx_apatb_param_norm_1_running_mean) {
  tr.import<4>((char*)__xlx_apatb_param_norm_1_running_mean, 24, 0);
}
__xlx_offset_byte_param_norm_1_running_var = 1056*4;
if (__xlx_apatb_param_norm_1_running_var) {
  tr.import<4>((char*)__xlx_apatb_param_norm_1_running_var, 24, 0);
}
__xlx_offset_byte_param_se_conv_reduce_weight = 1080*4;
if (__xlx_apatb_param_se_conv_reduce_weight) {
  tr.import<4>((char*)__xlx_apatb_param_se_conv_reduce_weight, 576, 0);
}
__xlx_offset_byte_param_se_conv_reduce_bias = 1656*4;
if (__xlx_apatb_param_se_conv_reduce_bias) {
  tr.import<4>((char*)__xlx_apatb_param_se_conv_reduce_bias, 24, 0);
}
__xlx_offset_byte_param_se_conv_expand_weight = 1680*4;
if (__xlx_apatb_param_se_conv_expand_weight) {
  tr.import<4>((char*)__xlx_apatb_param_se_conv_expand_weight, 576, 0);
}
__xlx_offset_byte_param_se_conv_expand_bias = 2256*4;
if (__xlx_apatb_param_se_conv_expand_bias) {
  tr.import<4>((char*)__xlx_apatb_param_se_conv_expand_bias, 24, 0);
}
__xlx_offset_byte_param_proj_conv_weight = 2280*4;
if (__xlx_apatb_param_proj_conv_weight) {
  tr.import<4>((char*)__xlx_apatb_param_proj_conv_weight, 576, 0);
}
aesl_fh.write(AUTOTB_TVIN_gmem, tr.p, tr.tbytes);
tcl_file.set_num(2856, &tcl_file.gmem_depth);
}
#else
aesl_fh.touch(AUTOTB_TVIN_gmem);
{
aesl_fh.write(AUTOTB_TVIN_gmem, begin_str(AESL_transaction));
__xlx_offset_byte_param_msp_conv_weight = 0*4;
if (__xlx_apatb_param_msp_conv_weight) {
for (size_t i = 0; i < 648; ++i) {
unsigned char *pos = (unsigned char*)__xlx_apatb_param_msp_conv_weight + i * 4;
std::string s = formatData(pos, 32);
aesl_fh.write(AUTOTB_TVIN_gmem, s);
}
}
__xlx_offset_byte_param_msp_conv_bias = 648*4;
if (__xlx_apatb_param_msp_conv_bias) {
for (size_t i = 0; i < 24; ++i) {
unsigned char *pos = (unsigned char*)__xlx_apatb_param_msp_conv_bias + i * 4;
std::string s = formatData(pos, 32);
aesl_fh.write(AUTOTB_TVIN_gmem, s);
}
}
__xlx_offset_byte_param_msp_norm_weight = 672*4;
if (__xlx_apatb_param_msp_norm_weight) {
for (size_t i = 0; i < 24; ++i) {
unsigned char *pos = (unsigned char*)__xlx_apatb_param_msp_norm_weight + i * 4;
std::string s = formatData(pos, 32);
aesl_fh.write(AUTOTB_TVIN_gmem, s);
}
}
__xlx_offset_byte_param_msp_norm_bias = 696*4;
if (__xlx_apatb_param_msp_norm_bias) {
for (size_t i = 0; i < 24; ++i) {
unsigned char *pos = (unsigned char*)__xlx_apatb_param_msp_norm_bias + i * 4;
std::string s = formatData(pos, 32);
aesl_fh.write(AUTOTB_TVIN_gmem, s);
}
}
__xlx_offset_byte_param_msp_norm_running_mean = 720*4;
if (__xlx_apatb_param_msp_norm_running_mean) {
for (size_t i = 0; i < 24; ++i) {
unsigned char *pos = (unsigned char*)__xlx_apatb_param_msp_norm_running_mean + i * 4;
std::string s = formatData(pos, 32);
aesl_fh.write(AUTOTB_TVIN_gmem, s);
}
}
__xlx_offset_byte_param_msp_norm_running_var = 744*4;
if (__xlx_apatb_param_msp_norm_running_var) {
for (size_t i = 0; i < 24; ++i) {
unsigned char *pos = (unsigned char*)__xlx_apatb_param_msp_norm_running_var + i * 4;
std::string s = formatData(pos, 32);
aesl_fh.write(AUTOTB_TVIN_gmem, s);
}
}
__xlx_offset_byte_param_dw_conv_weight = 768*4;
if (__xlx_apatb_param_dw_conv_weight) {
for (size_t i = 0; i < 216; ++i) {
unsigned char *pos = (unsigned char*)__xlx_apatb_param_dw_conv_weight + i * 4;
std::string s = formatData(pos, 32);
aesl_fh.write(AUTOTB_TVIN_gmem, s);
}
}
__xlx_offset_byte_param_norm_1_weight = 984*4;
if (__xlx_apatb_param_norm_1_weight) {
for (size_t i = 0; i < 24; ++i) {
unsigned char *pos = (unsigned char*)__xlx_apatb_param_norm_1_weight + i * 4;
std::string s = formatData(pos, 32);
aesl_fh.write(AUTOTB_TVIN_gmem, s);
}
}
__xlx_offset_byte_param_norm_1_bias = 1008*4;
if (__xlx_apatb_param_norm_1_bias) {
for (size_t i = 0; i < 24; ++i) {
unsigned char *pos = (unsigned char*)__xlx_apatb_param_norm_1_bias + i * 4;
std::string s = formatData(pos, 32);
aesl_fh.write(AUTOTB_TVIN_gmem, s);
}
}
__xlx_offset_byte_param_norm_1_running_mean = 1032*4;
if (__xlx_apatb_param_norm_1_running_mean) {
for (size_t i = 0; i < 24; ++i) {
unsigned char *pos = (unsigned char*)__xlx_apatb_param_norm_1_running_mean + i * 4;
std::string s = formatData(pos, 32);
aesl_fh.write(AUTOTB_TVIN_gmem, s);
}
}
__xlx_offset_byte_param_norm_1_running_var = 1056*4;
if (__xlx_apatb_param_norm_1_running_var) {
for (size_t i = 0; i < 24; ++i) {
unsigned char *pos = (unsigned char*)__xlx_apatb_param_norm_1_running_var + i * 4;
std::string s = formatData(pos, 32);
aesl_fh.write(AUTOTB_TVIN_gmem, s);
}
}
__xlx_offset_byte_param_se_conv_reduce_weight = 1080*4;
if (__xlx_apatb_param_se_conv_reduce_weight) {
for (size_t i = 0; i < 576; ++i) {
unsigned char *pos = (unsigned char*)__xlx_apatb_param_se_conv_reduce_weight + i * 4;
std::string s = formatData(pos, 32);
aesl_fh.write(AUTOTB_TVIN_gmem, s);
}
}
__xlx_offset_byte_param_se_conv_reduce_bias = 1656*4;
if (__xlx_apatb_param_se_conv_reduce_bias) {
for (size_t i = 0; i < 24; ++i) {
unsigned char *pos = (unsigned char*)__xlx_apatb_param_se_conv_reduce_bias + i * 4;
std::string s = formatData(pos, 32);
aesl_fh.write(AUTOTB_TVIN_gmem, s);
}
}
__xlx_offset_byte_param_se_conv_expand_weight = 1680*4;
if (__xlx_apatb_param_se_conv_expand_weight) {
for (size_t i = 0; i < 576; ++i) {
unsigned char *pos = (unsigned char*)__xlx_apatb_param_se_conv_expand_weight + i * 4;
std::string s = formatData(pos, 32);
aesl_fh.write(AUTOTB_TVIN_gmem, s);
}
}
__xlx_offset_byte_param_se_conv_expand_bias = 2256*4;
if (__xlx_apatb_param_se_conv_expand_bias) {
for (size_t i = 0; i < 24; ++i) {
unsigned char *pos = (unsigned char*)__xlx_apatb_param_se_conv_expand_bias + i * 4;
std::string s = formatData(pos, 32);
aesl_fh.write(AUTOTB_TVIN_gmem, s);
}
}
__xlx_offset_byte_param_proj_conv_weight = 2280*4;
if (__xlx_apatb_param_proj_conv_weight) {
for (size_t i = 0; i < 576; ++i) {
unsigned char *pos = (unsigned char*)__xlx_apatb_param_proj_conv_weight + i * 4;
std::string s = formatData(pos, 32);
aesl_fh.write(AUTOTB_TVIN_gmem, s);
}
}
tcl_file.set_num(2856, &tcl_file.gmem_depth);
aesl_fh.write(AUTOTB_TVIN_gmem, end_str());
}
#endif
#ifdef USE_BINARY_TV_FILE
{
aesl_fh.touch(AUTOTB_TVIN_gmem0, 'b');
transaction<32> tr(752664);
__xlx_offset_byte_param_X_data = 0*4;
if (__xlx_apatb_param_X_data) {
  tr.import<4>((char*)__xlx_apatb_param_X_data, 150528, 0);
}
__xlx_offset_byte_param_Y_dw_norm = 150528*4;
if (__xlx_apatb_param_Y_dw_norm) {
  tr.import<4>((char*)__xlx_apatb_param_Y_dw_norm, 301056, 0);
}
__xlx_offset_byte_param_Y_relu = 451584*4;
if (__xlx_apatb_param_Y_relu) {
  tr.import<4>((char*)__xlx_apatb_param_Y_relu, 24, 0);
}
__xlx_offset_byte_param_Y_proj = 451608*4;
if (__xlx_apatb_param_Y_proj) {
  tr.import<4>((char*)__xlx_apatb_param_Y_proj, 301056, 0);
}
aesl_fh.write(AUTOTB_TVIN_gmem0, tr.p, tr.tbytes);
tcl_file.set_num(752664, &tcl_file.gmem0_depth);
}
#else
aesl_fh.touch(AUTOTB_TVIN_gmem0);
{
aesl_fh.write(AUTOTB_TVIN_gmem0, begin_str(AESL_transaction));
__xlx_offset_byte_param_X_data = 0*4;
if (__xlx_apatb_param_X_data) {
for (size_t i = 0; i < 150528; ++i) {
unsigned char *pos = (unsigned char*)__xlx_apatb_param_X_data + i * 4;
std::string s = formatData(pos, 32);
aesl_fh.write(AUTOTB_TVIN_gmem0, s);
}
}
__xlx_offset_byte_param_Y_dw_norm = 150528*4;
if (__xlx_apatb_param_Y_dw_norm) {
for (size_t i = 0; i < 301056; ++i) {
unsigned char *pos = (unsigned char*)__xlx_apatb_param_Y_dw_norm + i * 4;
std::string s = formatData(pos, 32);
aesl_fh.write(AUTOTB_TVIN_gmem0, s);
}
}
__xlx_offset_byte_param_Y_relu = 451584*4;
if (__xlx_apatb_param_Y_relu) {
for (size_t i = 0; i < 24; ++i) {
unsigned char *pos = (unsigned char*)__xlx_apatb_param_Y_relu + i * 4;
std::string s = formatData(pos, 32);
aesl_fh.write(AUTOTB_TVIN_gmem0, s);
}
}
__xlx_offset_byte_param_Y_proj = 451608*4;
if (__xlx_apatb_param_Y_proj) {
for (size_t i = 0; i < 301056; ++i) {
unsigned char *pos = (unsigned char*)__xlx_apatb_param_Y_proj + i * 4;
std::string s = formatData(pos, 32);
aesl_fh.write(AUTOTB_TVIN_gmem0, s);
}
}
tcl_file.set_num(752664, &tcl_file.gmem0_depth);
aesl_fh.write(AUTOTB_TVIN_gmem0, end_str());
}
#endif
#ifdef USE_BINARY_TV_FILE
{
aesl_fh.touch(AUTOTB_TVIN_gmem1, 'b');
transaction<32> tr(602136);
__xlx_offset_byte_param_Y_msp_conv = 0*4;
if (__xlx_apatb_param_Y_msp_conv) {
  tr.import<4>((char*)__xlx_apatb_param_Y_msp_conv, 301056, 0);
}
__xlx_offset_byte_param_Y_dw_act = 301056*4;
if (__xlx_apatb_param_Y_dw_act) {
  tr.import<4>((char*)__xlx_apatb_param_Y_dw_act, 301056, 0);
}
__xlx_offset_byte_param_Y_expand = 602112*4;
if (__xlx_apatb_param_Y_expand) {
  tr.import<4>((char*)__xlx_apatb_param_Y_expand, 24, 0);
}
aesl_fh.write(AUTOTB_TVIN_gmem1, tr.p, tr.tbytes);
tcl_file.set_num(602136, &tcl_file.gmem1_depth);
}
#else
aesl_fh.touch(AUTOTB_TVIN_gmem1);
{
aesl_fh.write(AUTOTB_TVIN_gmem1, begin_str(AESL_transaction));
__xlx_offset_byte_param_Y_msp_conv = 0*4;
if (__xlx_apatb_param_Y_msp_conv) {
for (size_t i = 0; i < 301056; ++i) {
unsigned char *pos = (unsigned char*)__xlx_apatb_param_Y_msp_conv + i * 4;
std::string s = formatData(pos, 32);
aesl_fh.write(AUTOTB_TVIN_gmem1, s);
}
}
__xlx_offset_byte_param_Y_dw_act = 301056*4;
if (__xlx_apatb_param_Y_dw_act) {
for (size_t i = 0; i < 301056; ++i) {
unsigned char *pos = (unsigned char*)__xlx_apatb_param_Y_dw_act + i * 4;
std::string s = formatData(pos, 32);
aesl_fh.write(AUTOTB_TVIN_gmem1, s);
}
}
__xlx_offset_byte_param_Y_expand = 602112*4;
if (__xlx_apatb_param_Y_expand) {
for (size_t i = 0; i < 24; ++i) {
unsigned char *pos = (unsigned char*)__xlx_apatb_param_Y_expand + i * 4;
std::string s = formatData(pos, 32);
aesl_fh.write(AUTOTB_TVIN_gmem1, s);
}
}
tcl_file.set_num(602136, &tcl_file.gmem1_depth);
aesl_fh.write(AUTOTB_TVIN_gmem1, end_str());
}
#endif
#ifdef USE_BINARY_TV_FILE
{
aesl_fh.touch(AUTOTB_TVIN_gmem2, 'b');
transaction<32> tr(301104);
__xlx_offset_byte_param_Y_msp_norm = 0*4;
if (__xlx_apatb_param_Y_msp_norm) {
  tr.import<4>((char*)__xlx_apatb_param_Y_msp_norm, 301056, 0);
}
__xlx_offset_byte_param_Y_mean = 301056*4;
if (__xlx_apatb_param_Y_mean) {
  tr.import<4>((char*)__xlx_apatb_param_Y_mean, 24, 0);
}
__xlx_offset_byte_param_Y_sigmoid = 301080*4;
if (__xlx_apatb_param_Y_sigmoid) {
  tr.import<4>((char*)__xlx_apatb_param_Y_sigmoid, 24, 0);
}
aesl_fh.write(AUTOTB_TVIN_gmem2, tr.p, tr.tbytes);
tcl_file.set_num(301104, &tcl_file.gmem2_depth);
}
#else
aesl_fh.touch(AUTOTB_TVIN_gmem2);
{
aesl_fh.write(AUTOTB_TVIN_gmem2, begin_str(AESL_transaction));
__xlx_offset_byte_param_Y_msp_norm = 0*4;
if (__xlx_apatb_param_Y_msp_norm) {
for (size_t i = 0; i < 301056; ++i) {
unsigned char *pos = (unsigned char*)__xlx_apatb_param_Y_msp_norm + i * 4;
std::string s = formatData(pos, 32);
aesl_fh.write(AUTOTB_TVIN_gmem2, s);
}
}
__xlx_offset_byte_param_Y_mean = 301056*4;
if (__xlx_apatb_param_Y_mean) {
for (size_t i = 0; i < 24; ++i) {
unsigned char *pos = (unsigned char*)__xlx_apatb_param_Y_mean + i * 4;
std::string s = formatData(pos, 32);
aesl_fh.write(AUTOTB_TVIN_gmem2, s);
}
}
__xlx_offset_byte_param_Y_sigmoid = 301080*4;
if (__xlx_apatb_param_Y_sigmoid) {
for (size_t i = 0; i < 24; ++i) {
unsigned char *pos = (unsigned char*)__xlx_apatb_param_Y_sigmoid + i * 4;
std::string s = formatData(pos, 32);
aesl_fh.write(AUTOTB_TVIN_gmem2, s);
}
}
tcl_file.set_num(301104, &tcl_file.gmem2_depth);
aesl_fh.write(AUTOTB_TVIN_gmem2, end_str());
}
#endif
#ifdef USE_BINARY_TV_FILE
{
aesl_fh.touch(AUTOTB_TVIN_gmem3, 'b');
transaction<32> tr(602136);
__xlx_offset_byte_param_Y_dw_conv = 0*4;
if (__xlx_apatb_param_Y_dw_conv) {
  tr.import<4>((char*)__xlx_apatb_param_Y_dw_conv, 301056, 0);
}
__xlx_offset_byte_param_Y_reduce = 301056*4;
if (__xlx_apatb_param_Y_reduce) {
  tr.import<4>((char*)__xlx_apatb_param_Y_reduce, 24, 0);
}
__xlx_offset_byte_param_Y_se = 301080*4;
if (__xlx_apatb_param_Y_se) {
  tr.import<4>((char*)__xlx_apatb_param_Y_se, 301056, 0);
}
aesl_fh.write(AUTOTB_TVIN_gmem3, tr.p, tr.tbytes);
tcl_file.set_num(602136, &tcl_file.gmem3_depth);
}
#else
aesl_fh.touch(AUTOTB_TVIN_gmem3);
{
aesl_fh.write(AUTOTB_TVIN_gmem3, begin_str(AESL_transaction));
__xlx_offset_byte_param_Y_dw_conv = 0*4;
if (__xlx_apatb_param_Y_dw_conv) {
for (size_t i = 0; i < 301056; ++i) {
unsigned char *pos = (unsigned char*)__xlx_apatb_param_Y_dw_conv + i * 4;
std::string s = formatData(pos, 32);
aesl_fh.write(AUTOTB_TVIN_gmem3, s);
}
}
__xlx_offset_byte_param_Y_reduce = 301056*4;
if (__xlx_apatb_param_Y_reduce) {
for (size_t i = 0; i < 24; ++i) {
unsigned char *pos = (unsigned char*)__xlx_apatb_param_Y_reduce + i * 4;
std::string s = formatData(pos, 32);
aesl_fh.write(AUTOTB_TVIN_gmem3, s);
}
}
__xlx_offset_byte_param_Y_se = 301080*4;
if (__xlx_apatb_param_Y_se) {
for (size_t i = 0; i < 301056; ++i) {
unsigned char *pos = (unsigned char*)__xlx_apatb_param_Y_se + i * 4;
std::string s = formatData(pos, 32);
aesl_fh.write(AUTOTB_TVIN_gmem3, s);
}
}
tcl_file.set_num(602136, &tcl_file.gmem3_depth);
aesl_fh.write(AUTOTB_TVIN_gmem3, end_str());
}
#endif
// print X_data Transactions
{
aesl_fh.write(AUTOTB_TVIN_X_data, begin_str(AESL_transaction));
{
auto *pos = (unsigned char*)&__xlx_offset_byte_param_X_data;
aesl_fh.write(AUTOTB_TVIN_X_data, formatData(pos, 32));
}
  tcl_file.set_num(1, &tcl_file.X_data_depth);
aesl_fh.write(AUTOTB_TVIN_X_data, end_str());
}

// print msp_conv_weight Transactions
{
aesl_fh.write(AUTOTB_TVIN_msp_conv_weight, begin_str(AESL_transaction));
{
auto *pos = (unsigned char*)&__xlx_offset_byte_param_msp_conv_weight;
aesl_fh.write(AUTOTB_TVIN_msp_conv_weight, formatData(pos, 32));
}
  tcl_file.set_num(1, &tcl_file.msp_conv_weight_depth);
aesl_fh.write(AUTOTB_TVIN_msp_conv_weight, end_str());
}

// print msp_conv_bias Transactions
{
aesl_fh.write(AUTOTB_TVIN_msp_conv_bias, begin_str(AESL_transaction));
{
auto *pos = (unsigned char*)&__xlx_offset_byte_param_msp_conv_bias;
aesl_fh.write(AUTOTB_TVIN_msp_conv_bias, formatData(pos, 32));
}
  tcl_file.set_num(1, &tcl_file.msp_conv_bias_depth);
aesl_fh.write(AUTOTB_TVIN_msp_conv_bias, end_str());
}

// print msp_norm_weight Transactions
{
aesl_fh.write(AUTOTB_TVIN_msp_norm_weight, begin_str(AESL_transaction));
{
auto *pos = (unsigned char*)&__xlx_offset_byte_param_msp_norm_weight;
aesl_fh.write(AUTOTB_TVIN_msp_norm_weight, formatData(pos, 32));
}
  tcl_file.set_num(1, &tcl_file.msp_norm_weight_depth);
aesl_fh.write(AUTOTB_TVIN_msp_norm_weight, end_str());
}

// print msp_norm_bias Transactions
{
aesl_fh.write(AUTOTB_TVIN_msp_norm_bias, begin_str(AESL_transaction));
{
auto *pos = (unsigned char*)&__xlx_offset_byte_param_msp_norm_bias;
aesl_fh.write(AUTOTB_TVIN_msp_norm_bias, formatData(pos, 32));
}
  tcl_file.set_num(1, &tcl_file.msp_norm_bias_depth);
aesl_fh.write(AUTOTB_TVIN_msp_norm_bias, end_str());
}

// print msp_norm_running_mean Transactions
{
aesl_fh.write(AUTOTB_TVIN_msp_norm_running_mean, begin_str(AESL_transaction));
{
auto *pos = (unsigned char*)&__xlx_offset_byte_param_msp_norm_running_mean;
aesl_fh.write(AUTOTB_TVIN_msp_norm_running_mean, formatData(pos, 32));
}
  tcl_file.set_num(1, &tcl_file.msp_norm_running_mean_depth);
aesl_fh.write(AUTOTB_TVIN_msp_norm_running_mean, end_str());
}

// print msp_norm_running_var Transactions
{
aesl_fh.write(AUTOTB_TVIN_msp_norm_running_var, begin_str(AESL_transaction));
{
auto *pos = (unsigned char*)&__xlx_offset_byte_param_msp_norm_running_var;
aesl_fh.write(AUTOTB_TVIN_msp_norm_running_var, formatData(pos, 32));
}
  tcl_file.set_num(1, &tcl_file.msp_norm_running_var_depth);
aesl_fh.write(AUTOTB_TVIN_msp_norm_running_var, end_str());
}

// print dw_conv_weight Transactions
{
aesl_fh.write(AUTOTB_TVIN_dw_conv_weight, begin_str(AESL_transaction));
{
auto *pos = (unsigned char*)&__xlx_offset_byte_param_dw_conv_weight;
aesl_fh.write(AUTOTB_TVIN_dw_conv_weight, formatData(pos, 32));
}
  tcl_file.set_num(1, &tcl_file.dw_conv_weight_depth);
aesl_fh.write(AUTOTB_TVIN_dw_conv_weight, end_str());
}

// print norm_1_weight Transactions
{
aesl_fh.write(AUTOTB_TVIN_norm_1_weight, begin_str(AESL_transaction));
{
auto *pos = (unsigned char*)&__xlx_offset_byte_param_norm_1_weight;
aesl_fh.write(AUTOTB_TVIN_norm_1_weight, formatData(pos, 32));
}
  tcl_file.set_num(1, &tcl_file.norm_1_weight_depth);
aesl_fh.write(AUTOTB_TVIN_norm_1_weight, end_str());
}

// print norm_1_bias Transactions
{
aesl_fh.write(AUTOTB_TVIN_norm_1_bias, begin_str(AESL_transaction));
{
auto *pos = (unsigned char*)&__xlx_offset_byte_param_norm_1_bias;
aesl_fh.write(AUTOTB_TVIN_norm_1_bias, formatData(pos, 32));
}
  tcl_file.set_num(1, &tcl_file.norm_1_bias_depth);
aesl_fh.write(AUTOTB_TVIN_norm_1_bias, end_str());
}

// print norm_1_running_mean Transactions
{
aesl_fh.write(AUTOTB_TVIN_norm_1_running_mean, begin_str(AESL_transaction));
{
auto *pos = (unsigned char*)&__xlx_offset_byte_param_norm_1_running_mean;
aesl_fh.write(AUTOTB_TVIN_norm_1_running_mean, formatData(pos, 32));
}
  tcl_file.set_num(1, &tcl_file.norm_1_running_mean_depth);
aesl_fh.write(AUTOTB_TVIN_norm_1_running_mean, end_str());
}

// print norm_1_running_var Transactions
{
aesl_fh.write(AUTOTB_TVIN_norm_1_running_var, begin_str(AESL_transaction));
{
auto *pos = (unsigned char*)&__xlx_offset_byte_param_norm_1_running_var;
aesl_fh.write(AUTOTB_TVIN_norm_1_running_var, formatData(pos, 32));
}
  tcl_file.set_num(1, &tcl_file.norm_1_running_var_depth);
aesl_fh.write(AUTOTB_TVIN_norm_1_running_var, end_str());
}

// print se_conv_reduce_weight Transactions
{
aesl_fh.write(AUTOTB_TVIN_se_conv_reduce_weight, begin_str(AESL_transaction));
{
auto *pos = (unsigned char*)&__xlx_offset_byte_param_se_conv_reduce_weight;
aesl_fh.write(AUTOTB_TVIN_se_conv_reduce_weight, formatData(pos, 32));
}
  tcl_file.set_num(1, &tcl_file.se_conv_reduce_weight_depth);
aesl_fh.write(AUTOTB_TVIN_se_conv_reduce_weight, end_str());
}

// print se_conv_reduce_bias Transactions
{
aesl_fh.write(AUTOTB_TVIN_se_conv_reduce_bias, begin_str(AESL_transaction));
{
auto *pos = (unsigned char*)&__xlx_offset_byte_param_se_conv_reduce_bias;
aesl_fh.write(AUTOTB_TVIN_se_conv_reduce_bias, formatData(pos, 32));
}
  tcl_file.set_num(1, &tcl_file.se_conv_reduce_bias_depth);
aesl_fh.write(AUTOTB_TVIN_se_conv_reduce_bias, end_str());
}

// print se_conv_expand_weight Transactions
{
aesl_fh.write(AUTOTB_TVIN_se_conv_expand_weight, begin_str(AESL_transaction));
{
auto *pos = (unsigned char*)&__xlx_offset_byte_param_se_conv_expand_weight;
aesl_fh.write(AUTOTB_TVIN_se_conv_expand_weight, formatData(pos, 32));
}
  tcl_file.set_num(1, &tcl_file.se_conv_expand_weight_depth);
aesl_fh.write(AUTOTB_TVIN_se_conv_expand_weight, end_str());
}

// print se_conv_expand_bias Transactions
{
aesl_fh.write(AUTOTB_TVIN_se_conv_expand_bias, begin_str(AESL_transaction));
{
auto *pos = (unsigned char*)&__xlx_offset_byte_param_se_conv_expand_bias;
aesl_fh.write(AUTOTB_TVIN_se_conv_expand_bias, formatData(pos, 32));
}
  tcl_file.set_num(1, &tcl_file.se_conv_expand_bias_depth);
aesl_fh.write(AUTOTB_TVIN_se_conv_expand_bias, end_str());
}

// print proj_conv_weight Transactions
{
aesl_fh.write(AUTOTB_TVIN_proj_conv_weight, begin_str(AESL_transaction));
{
auto *pos = (unsigned char*)&__xlx_offset_byte_param_proj_conv_weight;
aesl_fh.write(AUTOTB_TVIN_proj_conv_weight, formatData(pos, 32));
}
  tcl_file.set_num(1, &tcl_file.proj_conv_weight_depth);
aesl_fh.write(AUTOTB_TVIN_proj_conv_weight, end_str());
}

// print Y_msp_conv Transactions
{
aesl_fh.write(AUTOTB_TVIN_Y_msp_conv, begin_str(AESL_transaction));
{
auto *pos = (unsigned char*)&__xlx_offset_byte_param_Y_msp_conv;
aesl_fh.write(AUTOTB_TVIN_Y_msp_conv, formatData(pos, 32));
}
  tcl_file.set_num(1, &tcl_file.Y_msp_conv_depth);
aesl_fh.write(AUTOTB_TVIN_Y_msp_conv, end_str());
}

// print Y_msp_norm Transactions
{
aesl_fh.write(AUTOTB_TVIN_Y_msp_norm, begin_str(AESL_transaction));
{
auto *pos = (unsigned char*)&__xlx_offset_byte_param_Y_msp_norm;
aesl_fh.write(AUTOTB_TVIN_Y_msp_norm, formatData(pos, 32));
}
  tcl_file.set_num(1, &tcl_file.Y_msp_norm_depth);
aesl_fh.write(AUTOTB_TVIN_Y_msp_norm, end_str());
}

// print Y_dw_conv Transactions
{
aesl_fh.write(AUTOTB_TVIN_Y_dw_conv, begin_str(AESL_transaction));
{
auto *pos = (unsigned char*)&__xlx_offset_byte_param_Y_dw_conv;
aesl_fh.write(AUTOTB_TVIN_Y_dw_conv, formatData(pos, 32));
}
  tcl_file.set_num(1, &tcl_file.Y_dw_conv_depth);
aesl_fh.write(AUTOTB_TVIN_Y_dw_conv, end_str());
}

// print Y_dw_norm Transactions
{
aesl_fh.write(AUTOTB_TVIN_Y_dw_norm, begin_str(AESL_transaction));
{
auto *pos = (unsigned char*)&__xlx_offset_byte_param_Y_dw_norm;
aesl_fh.write(AUTOTB_TVIN_Y_dw_norm, formatData(pos, 32));
}
  tcl_file.set_num(1, &tcl_file.Y_dw_norm_depth);
aesl_fh.write(AUTOTB_TVIN_Y_dw_norm, end_str());
}

// print Y_dw_act Transactions
{
aesl_fh.write(AUTOTB_TVIN_Y_dw_act, begin_str(AESL_transaction));
{
auto *pos = (unsigned char*)&__xlx_offset_byte_param_Y_dw_act;
aesl_fh.write(AUTOTB_TVIN_Y_dw_act, formatData(pos, 32));
}
  tcl_file.set_num(1, &tcl_file.Y_dw_act_depth);
aesl_fh.write(AUTOTB_TVIN_Y_dw_act, end_str());
}

// print Y_mean Transactions
{
aesl_fh.write(AUTOTB_TVIN_Y_mean, begin_str(AESL_transaction));
{
auto *pos = (unsigned char*)&__xlx_offset_byte_param_Y_mean;
aesl_fh.write(AUTOTB_TVIN_Y_mean, formatData(pos, 32));
}
  tcl_file.set_num(1, &tcl_file.Y_mean_depth);
aesl_fh.write(AUTOTB_TVIN_Y_mean, end_str());
}

// print Y_reduce Transactions
{
aesl_fh.write(AUTOTB_TVIN_Y_reduce, begin_str(AESL_transaction));
{
auto *pos = (unsigned char*)&__xlx_offset_byte_param_Y_reduce;
aesl_fh.write(AUTOTB_TVIN_Y_reduce, formatData(pos, 32));
}
  tcl_file.set_num(1, &tcl_file.Y_reduce_depth);
aesl_fh.write(AUTOTB_TVIN_Y_reduce, end_str());
}

// print Y_relu Transactions
{
aesl_fh.write(AUTOTB_TVIN_Y_relu, begin_str(AESL_transaction));
{
auto *pos = (unsigned char*)&__xlx_offset_byte_param_Y_relu;
aesl_fh.write(AUTOTB_TVIN_Y_relu, formatData(pos, 32));
}
  tcl_file.set_num(1, &tcl_file.Y_relu_depth);
aesl_fh.write(AUTOTB_TVIN_Y_relu, end_str());
}

// print Y_expand Transactions
{
aesl_fh.write(AUTOTB_TVIN_Y_expand, begin_str(AESL_transaction));
{
auto *pos = (unsigned char*)&__xlx_offset_byte_param_Y_expand;
aesl_fh.write(AUTOTB_TVIN_Y_expand, formatData(pos, 32));
}
  tcl_file.set_num(1, &tcl_file.Y_expand_depth);
aesl_fh.write(AUTOTB_TVIN_Y_expand, end_str());
}

// print Y_sigmoid Transactions
{
aesl_fh.write(AUTOTB_TVIN_Y_sigmoid, begin_str(AESL_transaction));
{
auto *pos = (unsigned char*)&__xlx_offset_byte_param_Y_sigmoid;
aesl_fh.write(AUTOTB_TVIN_Y_sigmoid, formatData(pos, 32));
}
  tcl_file.set_num(1, &tcl_file.Y_sigmoid_depth);
aesl_fh.write(AUTOTB_TVIN_Y_sigmoid, end_str());
}

// print Y_se Transactions
{
aesl_fh.write(AUTOTB_TVIN_Y_se, begin_str(AESL_transaction));
{
auto *pos = (unsigned char*)&__xlx_offset_byte_param_Y_se;
aesl_fh.write(AUTOTB_TVIN_Y_se, formatData(pos, 32));
}
  tcl_file.set_num(1, &tcl_file.Y_se_depth);
aesl_fh.write(AUTOTB_TVIN_Y_se, end_str());
}

// print Y_proj Transactions
{
aesl_fh.write(AUTOTB_TVIN_Y_proj, begin_str(AESL_transaction));
{
auto *pos = (unsigned char*)&__xlx_offset_byte_param_Y_proj;
aesl_fh.write(AUTOTB_TVIN_Y_proj, formatData(pos, 32));
}
  tcl_file.set_num(1, &tcl_file.Y_proj_depth);
aesl_fh.write(AUTOTB_TVIN_Y_proj, end_str());
}

CodeState = CALL_C_DUT;
kernel_stage0_hw_stub_wrapper(__xlx_apatb_param_X_data, __xlx_apatb_param_msp_conv_weight, __xlx_apatb_param_msp_conv_bias, __xlx_apatb_param_msp_norm_weight, __xlx_apatb_param_msp_norm_bias, __xlx_apatb_param_msp_norm_running_mean, __xlx_apatb_param_msp_norm_running_var, __xlx_apatb_param_dw_conv_weight, __xlx_apatb_param_norm_1_weight, __xlx_apatb_param_norm_1_bias, __xlx_apatb_param_norm_1_running_mean, __xlx_apatb_param_norm_1_running_var, __xlx_apatb_param_se_conv_reduce_weight, __xlx_apatb_param_se_conv_reduce_bias, __xlx_apatb_param_se_conv_expand_weight, __xlx_apatb_param_se_conv_expand_bias, __xlx_apatb_param_proj_conv_weight, __xlx_apatb_param_Y_msp_conv, __xlx_apatb_param_Y_msp_norm, __xlx_apatb_param_Y_dw_conv, __xlx_apatb_param_Y_dw_norm, __xlx_apatb_param_Y_dw_act, __xlx_apatb_param_Y_mean, __xlx_apatb_param_Y_reduce, __xlx_apatb_param_Y_relu, __xlx_apatb_param_Y_expand, __xlx_apatb_param_Y_sigmoid, __xlx_apatb_param_Y_se, __xlx_apatb_param_Y_proj);
CodeState = DUMP_OUTPUTS;
#ifdef USE_BINARY_TV_FILE
{
aesl_fh.touch(AUTOTB_TVOUT_gmem0, 'b');
transaction<32> tr(752664);
__xlx_offset_byte_param_X_data = 0*4;
if (__xlx_apatb_param_X_data) {
  tr.import<4>((char*)__xlx_apatb_param_X_data, 150528, 0);
}
__xlx_offset_byte_param_Y_dw_norm = 150528*4;
if (__xlx_apatb_param_Y_dw_norm) {
  tr.import<4>((char*)__xlx_apatb_param_Y_dw_norm, 301056, 0);
}
__xlx_offset_byte_param_Y_relu = 451584*4;
if (__xlx_apatb_param_Y_relu) {
  tr.import<4>((char*)__xlx_apatb_param_Y_relu, 24, 0);
}
__xlx_offset_byte_param_Y_proj = 451608*4;
if (__xlx_apatb_param_Y_proj) {
  tr.import<4>((char*)__xlx_apatb_param_Y_proj, 301056, 0);
}
aesl_fh.write(AUTOTB_TVOUT_gmem0, tr.p, tr.tbytes);
tcl_file.set_num(752664, &tcl_file.gmem0_depth);
}
#else
aesl_fh.touch(AUTOTB_TVOUT_gmem0);
{
aesl_fh.write(AUTOTB_TVOUT_gmem0, begin_str(AESL_transaction));
__xlx_offset_byte_param_X_data = 0*4;
if (__xlx_apatb_param_X_data) {
for (size_t i = 0; i < 150528; ++i) {
unsigned char *pos = (unsigned char*)__xlx_apatb_param_X_data + i * 4;
std::string s = formatData(pos, 32);
aesl_fh.write(AUTOTB_TVOUT_gmem0, s);
}
}
__xlx_offset_byte_param_Y_dw_norm = 150528*4;
if (__xlx_apatb_param_Y_dw_norm) {
for (size_t i = 0; i < 301056; ++i) {
unsigned char *pos = (unsigned char*)__xlx_apatb_param_Y_dw_norm + i * 4;
std::string s = formatData(pos, 32);
aesl_fh.write(AUTOTB_TVOUT_gmem0, s);
}
}
__xlx_offset_byte_param_Y_relu = 451584*4;
if (__xlx_apatb_param_Y_relu) {
for (size_t i = 0; i < 24; ++i) {
unsigned char *pos = (unsigned char*)__xlx_apatb_param_Y_relu + i * 4;
std::string s = formatData(pos, 32);
aesl_fh.write(AUTOTB_TVOUT_gmem0, s);
}
}
__xlx_offset_byte_param_Y_proj = 451608*4;
if (__xlx_apatb_param_Y_proj) {
for (size_t i = 0; i < 301056; ++i) {
unsigned char *pos = (unsigned char*)__xlx_apatb_param_Y_proj + i * 4;
std::string s = formatData(pos, 32);
aesl_fh.write(AUTOTB_TVOUT_gmem0, s);
}
}
tcl_file.set_num(752664, &tcl_file.gmem0_depth);
aesl_fh.write(AUTOTB_TVOUT_gmem0, end_str());
}
#endif
#ifdef USE_BINARY_TV_FILE
{
aesl_fh.touch(AUTOTB_TVOUT_gmem1, 'b');
transaction<32> tr(602136);
__xlx_offset_byte_param_Y_msp_conv = 0*4;
if (__xlx_apatb_param_Y_msp_conv) {
  tr.import<4>((char*)__xlx_apatb_param_Y_msp_conv, 301056, 0);
}
__xlx_offset_byte_param_Y_dw_act = 301056*4;
if (__xlx_apatb_param_Y_dw_act) {
  tr.import<4>((char*)__xlx_apatb_param_Y_dw_act, 301056, 0);
}
__xlx_offset_byte_param_Y_expand = 602112*4;
if (__xlx_apatb_param_Y_expand) {
  tr.import<4>((char*)__xlx_apatb_param_Y_expand, 24, 0);
}
aesl_fh.write(AUTOTB_TVOUT_gmem1, tr.p, tr.tbytes);
tcl_file.set_num(602136, &tcl_file.gmem1_depth);
}
#else
aesl_fh.touch(AUTOTB_TVOUT_gmem1);
{
aesl_fh.write(AUTOTB_TVOUT_gmem1, begin_str(AESL_transaction));
__xlx_offset_byte_param_Y_msp_conv = 0*4;
if (__xlx_apatb_param_Y_msp_conv) {
for (size_t i = 0; i < 301056; ++i) {
unsigned char *pos = (unsigned char*)__xlx_apatb_param_Y_msp_conv + i * 4;
std::string s = formatData(pos, 32);
aesl_fh.write(AUTOTB_TVOUT_gmem1, s);
}
}
__xlx_offset_byte_param_Y_dw_act = 301056*4;
if (__xlx_apatb_param_Y_dw_act) {
for (size_t i = 0; i < 301056; ++i) {
unsigned char *pos = (unsigned char*)__xlx_apatb_param_Y_dw_act + i * 4;
std::string s = formatData(pos, 32);
aesl_fh.write(AUTOTB_TVOUT_gmem1, s);
}
}
__xlx_offset_byte_param_Y_expand = 602112*4;
if (__xlx_apatb_param_Y_expand) {
for (size_t i = 0; i < 24; ++i) {
unsigned char *pos = (unsigned char*)__xlx_apatb_param_Y_expand + i * 4;
std::string s = formatData(pos, 32);
aesl_fh.write(AUTOTB_TVOUT_gmem1, s);
}
}
tcl_file.set_num(602136, &tcl_file.gmem1_depth);
aesl_fh.write(AUTOTB_TVOUT_gmem1, end_str());
}
#endif
#ifdef USE_BINARY_TV_FILE
{
aesl_fh.touch(AUTOTB_TVOUT_gmem2, 'b');
transaction<32> tr(301104);
__xlx_offset_byte_param_Y_msp_norm = 0*4;
if (__xlx_apatb_param_Y_msp_norm) {
  tr.import<4>((char*)__xlx_apatb_param_Y_msp_norm, 301056, 0);
}
__xlx_offset_byte_param_Y_mean = 301056*4;
if (__xlx_apatb_param_Y_mean) {
  tr.import<4>((char*)__xlx_apatb_param_Y_mean, 24, 0);
}
__xlx_offset_byte_param_Y_sigmoid = 301080*4;
if (__xlx_apatb_param_Y_sigmoid) {
  tr.import<4>((char*)__xlx_apatb_param_Y_sigmoid, 24, 0);
}
aesl_fh.write(AUTOTB_TVOUT_gmem2, tr.p, tr.tbytes);
tcl_file.set_num(301104, &tcl_file.gmem2_depth);
}
#else
aesl_fh.touch(AUTOTB_TVOUT_gmem2);
{
aesl_fh.write(AUTOTB_TVOUT_gmem2, begin_str(AESL_transaction));
__xlx_offset_byte_param_Y_msp_norm = 0*4;
if (__xlx_apatb_param_Y_msp_norm) {
for (size_t i = 0; i < 301056; ++i) {
unsigned char *pos = (unsigned char*)__xlx_apatb_param_Y_msp_norm + i * 4;
std::string s = formatData(pos, 32);
aesl_fh.write(AUTOTB_TVOUT_gmem2, s);
}
}
__xlx_offset_byte_param_Y_mean = 301056*4;
if (__xlx_apatb_param_Y_mean) {
for (size_t i = 0; i < 24; ++i) {
unsigned char *pos = (unsigned char*)__xlx_apatb_param_Y_mean + i * 4;
std::string s = formatData(pos, 32);
aesl_fh.write(AUTOTB_TVOUT_gmem2, s);
}
}
__xlx_offset_byte_param_Y_sigmoid = 301080*4;
if (__xlx_apatb_param_Y_sigmoid) {
for (size_t i = 0; i < 24; ++i) {
unsigned char *pos = (unsigned char*)__xlx_apatb_param_Y_sigmoid + i * 4;
std::string s = formatData(pos, 32);
aesl_fh.write(AUTOTB_TVOUT_gmem2, s);
}
}
tcl_file.set_num(301104, &tcl_file.gmem2_depth);
aesl_fh.write(AUTOTB_TVOUT_gmem2, end_str());
}
#endif
#ifdef USE_BINARY_TV_FILE
{
aesl_fh.touch(AUTOTB_TVOUT_gmem3, 'b');
transaction<32> tr(602136);
__xlx_offset_byte_param_Y_dw_conv = 0*4;
if (__xlx_apatb_param_Y_dw_conv) {
  tr.import<4>((char*)__xlx_apatb_param_Y_dw_conv, 301056, 0);
}
__xlx_offset_byte_param_Y_reduce = 301056*4;
if (__xlx_apatb_param_Y_reduce) {
  tr.import<4>((char*)__xlx_apatb_param_Y_reduce, 24, 0);
}
__xlx_offset_byte_param_Y_se = 301080*4;
if (__xlx_apatb_param_Y_se) {
  tr.import<4>((char*)__xlx_apatb_param_Y_se, 301056, 0);
}
aesl_fh.write(AUTOTB_TVOUT_gmem3, tr.p, tr.tbytes);
tcl_file.set_num(602136, &tcl_file.gmem3_depth);
}
#else
aesl_fh.touch(AUTOTB_TVOUT_gmem3);
{
aesl_fh.write(AUTOTB_TVOUT_gmem3, begin_str(AESL_transaction));
__xlx_offset_byte_param_Y_dw_conv = 0*4;
if (__xlx_apatb_param_Y_dw_conv) {
for (size_t i = 0; i < 301056; ++i) {
unsigned char *pos = (unsigned char*)__xlx_apatb_param_Y_dw_conv + i * 4;
std::string s = formatData(pos, 32);
aesl_fh.write(AUTOTB_TVOUT_gmem3, s);
}
}
__xlx_offset_byte_param_Y_reduce = 301056*4;
if (__xlx_apatb_param_Y_reduce) {
for (size_t i = 0; i < 24; ++i) {
unsigned char *pos = (unsigned char*)__xlx_apatb_param_Y_reduce + i * 4;
std::string s = formatData(pos, 32);
aesl_fh.write(AUTOTB_TVOUT_gmem3, s);
}
}
__xlx_offset_byte_param_Y_se = 301080*4;
if (__xlx_apatb_param_Y_se) {
for (size_t i = 0; i < 301056; ++i) {
unsigned char *pos = (unsigned char*)__xlx_apatb_param_Y_se + i * 4;
std::string s = formatData(pos, 32);
aesl_fh.write(AUTOTB_TVOUT_gmem3, s);
}
}
tcl_file.set_num(602136, &tcl_file.gmem3_depth);
aesl_fh.write(AUTOTB_TVOUT_gmem3, end_str());
}
#endif
CodeState = DELETE_CHAR_BUFFERS;
AESL_transaction++;
tcl_file.set_num(AESL_transaction , &tcl_file.trans_num);
}
