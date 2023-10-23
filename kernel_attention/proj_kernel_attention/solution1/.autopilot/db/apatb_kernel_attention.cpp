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
#define AUTOTB_TVIN_buffer_DataIn_1 "../tv/cdatafile/c.kernel_attention.autotvin_buffer_DataIn_1.dat"
#define AUTOTB_TVOUT_buffer_DataIn_1 "../tv/cdatafile/c.kernel_attention.autotvout_buffer_DataIn_1.dat"
#define AUTOTB_TVIN_afterNorm "../tv/cdatafile/c.kernel_attention.autotvin_afterNorm.dat"
#define AUTOTB_TVOUT_afterNorm "../tv/cdatafile/c.kernel_attention.autotvout_afterNorm.dat"
#define AUTOTB_TVIN_norm1_mean "../tv/cdatafile/c.kernel_attention.autotvin_norm1_mean.dat"
#define AUTOTB_TVOUT_norm1_mean "../tv/cdatafile/c.kernel_attention.autotvout_norm1_mean.dat"
#define AUTOTB_TVIN_norm1_var "../tv/cdatafile/c.kernel_attention.autotvin_norm1_var.dat"
#define AUTOTB_TVOUT_norm1_var "../tv/cdatafile/c.kernel_attention.autotvout_norm1_var.dat"
#define AUTOTB_TVIN_norm1_weight "../tv/cdatafile/c.kernel_attention.autotvin_norm1_weight.dat"
#define AUTOTB_TVOUT_norm1_weight "../tv/cdatafile/c.kernel_attention.autotvout_norm1_weight.dat"
#define AUTOTB_TVIN_norm1_bias "../tv/cdatafile/c.kernel_attention.autotvin_norm1_bias.dat"
#define AUTOTB_TVOUT_norm1_bias "../tv/cdatafile/c.kernel_attention.autotvout_norm1_bias.dat"
#define AUTOTB_TVIN_afterPad "../tv/cdatafile/c.kernel_attention.autotvin_afterPad.dat"
#define AUTOTB_TVOUT_afterPad "../tv/cdatafile/c.kernel_attention.autotvout_afterPad.dat"
#define AUTOTB_TVIN_afterRearrangeX "../tv/cdatafile/c.kernel_attention.autotvin_afterRearrangeX.dat"
#define AUTOTB_TVOUT_afterRearrangeX "../tv/cdatafile/c.kernel_attention.autotvout_afterRearrangeX.dat"
#define AUTOTB_TVIN_afterPad1 "../tv/cdatafile/c.kernel_attention.autotvin_afterPad1.dat"
#define AUTOTB_TVOUT_afterPad1 "../tv/cdatafile/c.kernel_attention.autotvout_afterPad1.dat"
#define AUTOTB_TVIN_afterConv1 "../tv/cdatafile/c.kernel_attention.autotvin_afterConv1.dat"
#define AUTOTB_TVOUT_afterConv1 "../tv/cdatafile/c.kernel_attention.autotvout_afterConv1.dat"
#define AUTOTB_TVIN_kernel1 "../tv/cdatafile/c.kernel_attention.autotvin_kernel1.dat"
#define AUTOTB_TVOUT_kernel1 "../tv/cdatafile/c.kernel_attention.autotvout_kernel1.dat"
#define AUTOTB_TVIN_bias1 "../tv/cdatafile/c.kernel_attention.autotvin_bias1.dat"
#define AUTOTB_TVOUT_bias1 "../tv/cdatafile/c.kernel_attention.autotvout_bias1.dat"
#define AUTOTB_TVIN_in_qk "../tv/cdatafile/c.kernel_attention.autotvin_in_qk.dat"
#define AUTOTB_TVOUT_in_qk "../tv/cdatafile/c.kernel_attention.autotvout_in_qk.dat"
#define AUTOTB_TVIN_in_q "../tv/cdatafile/c.kernel_attention.autotvin_in_q.dat"
#define AUTOTB_TVOUT_in_q "../tv/cdatafile/c.kernel_attention.autotvout_in_q.dat"
#define AUTOTB_TVIN_in_k "../tv/cdatafile/c.kernel_attention.autotvin_in_k.dat"
#define AUTOTB_TVOUT_in_k "../tv/cdatafile/c.kernel_attention.autotvout_in_k.dat"
#define AUTOTB_TVIN_afterQKMultiplication "../tv/cdatafile/c.kernel_attention.autotvin_afterQKMultiplication.dat"
#define AUTOTB_TVOUT_afterQKMultiplication "../tv/cdatafile/c.kernel_attention.autotvout_afterQKMultiplication.dat"
#define AUTOTB_TVIN_afterSoftmax "../tv/cdatafile/c.kernel_attention.autotvin_afterSoftmax.dat"
#define AUTOTB_TVOUT_afterSoftmax "../tv/cdatafile/c.kernel_attention.autotvout_afterSoftmax.dat"
#define AUTOTB_TVIN_afterRearrangeX2 "../tv/cdatafile/c.kernel_attention.autotvin_afterRearrangeX2.dat"
#define AUTOTB_TVOUT_afterRearrangeX2 "../tv/cdatafile/c.kernel_attention.autotvout_afterRearrangeX2.dat"
#define AUTOTB_TVIN_afterQKXMultiplication "../tv/cdatafile/c.kernel_attention.autotvin_afterQKXMultiplication.dat"
#define AUTOTB_TVOUT_afterQKXMultiplication "../tv/cdatafile/c.kernel_attention.autotvout_afterQKXMultiplication.dat"
#define AUTOTB_TVIN_afterRearrangeQKX "../tv/cdatafile/c.kernel_attention.autotvin_afterRearrangeQKX.dat"
#define AUTOTB_TVOUT_afterRearrangeQKX "../tv/cdatafile/c.kernel_attention.autotvout_afterRearrangeQKX.dat"
#define AUTOTB_TVIN_afterPad2 "../tv/cdatafile/c.kernel_attention.autotvin_afterPad2.dat"
#define AUTOTB_TVOUT_afterPad2 "../tv/cdatafile/c.kernel_attention.autotvout_afterPad2.dat"
#define AUTOTB_TVIN_afterConv2 "../tv/cdatafile/c.kernel_attention.autotvin_afterConv2.dat"
#define AUTOTB_TVOUT_afterConv2 "../tv/cdatafile/c.kernel_attention.autotvout_afterConv2.dat"
#define AUTOTB_TVIN_kernel2 "../tv/cdatafile/c.kernel_attention.autotvin_kernel2.dat"
#define AUTOTB_TVOUT_kernel2 "../tv/cdatafile/c.kernel_attention.autotvout_kernel2.dat"
#define AUTOTB_TVIN_bias2 "../tv/cdatafile/c.kernel_attention.autotvin_bias2.dat"
#define AUTOTB_TVOUT_bias2 "../tv/cdatafile/c.kernel_attention.autotvout_bias2.dat"
#define AUTOTB_TVIN_afterAct2 "../tv/cdatafile/c.kernel_attention.autotvin_afterAct2.dat"
#define AUTOTB_TVOUT_afterAct2 "../tv/cdatafile/c.kernel_attention.autotvout_afterAct2.dat"
#define AUTOTB_TVIN_QKV "../tv/cdatafile/c.kernel_attention.autotvin_QKV.dat"
#define AUTOTB_TVOUT_QKV "../tv/cdatafile/c.kernel_attention.autotvout_QKV.dat"
#define AUTOTB_TVIN_buffer_out "../tv/cdatafile/c.kernel_attention.autotvin_buffer_out.dat"
#define AUTOTB_TVOUT_buffer_out "../tv/cdatafile/c.kernel_attention.autotvout_buffer_out.dat"
#define AUTOTB_TVIN_buffer_result "../tv/cdatafile/c.kernel_attention.autotvin_buffer_result.dat"
#define AUTOTB_TVOUT_buffer_result "../tv/cdatafile/c.kernel_attention.autotvout_buffer_result.dat"
#define AUTOTB_TVIN_gmem "../tv/cdatafile/c.kernel_attention.autotvin_gmem.dat"
#define AUTOTB_TVOUT_gmem "../tv/cdatafile/c.kernel_attention.autotvout_gmem.dat"
#define AUTOTB_TVIN_gmem0 "../tv/cdatafile/c.kernel_attention.autotvin_gmem0.dat"
#define AUTOTB_TVOUT_gmem0 "../tv/cdatafile/c.kernel_attention.autotvout_gmem0.dat"
#define AUTOTB_TVIN_gmem1 "../tv/cdatafile/c.kernel_attention.autotvin_gmem1.dat"
#define AUTOTB_TVOUT_gmem1 "../tv/cdatafile/c.kernel_attention.autotvout_gmem1.dat"

#define INTER_TCL "../tv/cdatafile/ref.tcl"

// tvout file define:
#define AUTOTB_TVOUT_PC_buffer_DataIn_1 "../tv/rtldatafile/rtl.kernel_attention.autotvout_buffer_DataIn_1.dat"
#define AUTOTB_TVOUT_PC_afterNorm "../tv/rtldatafile/rtl.kernel_attention.autotvout_afterNorm.dat"
#define AUTOTB_TVOUT_PC_norm1_mean "../tv/rtldatafile/rtl.kernel_attention.autotvout_norm1_mean.dat"
#define AUTOTB_TVOUT_PC_norm1_var "../tv/rtldatafile/rtl.kernel_attention.autotvout_norm1_var.dat"
#define AUTOTB_TVOUT_PC_norm1_weight "../tv/rtldatafile/rtl.kernel_attention.autotvout_norm1_weight.dat"
#define AUTOTB_TVOUT_PC_norm1_bias "../tv/rtldatafile/rtl.kernel_attention.autotvout_norm1_bias.dat"
#define AUTOTB_TVOUT_PC_afterPad "../tv/rtldatafile/rtl.kernel_attention.autotvout_afterPad.dat"
#define AUTOTB_TVOUT_PC_afterRearrangeX "../tv/rtldatafile/rtl.kernel_attention.autotvout_afterRearrangeX.dat"
#define AUTOTB_TVOUT_PC_afterPad1 "../tv/rtldatafile/rtl.kernel_attention.autotvout_afterPad1.dat"
#define AUTOTB_TVOUT_PC_afterConv1 "../tv/rtldatafile/rtl.kernel_attention.autotvout_afterConv1.dat"
#define AUTOTB_TVOUT_PC_kernel1 "../tv/rtldatafile/rtl.kernel_attention.autotvout_kernel1.dat"
#define AUTOTB_TVOUT_PC_bias1 "../tv/rtldatafile/rtl.kernel_attention.autotvout_bias1.dat"
#define AUTOTB_TVOUT_PC_in_qk "../tv/rtldatafile/rtl.kernel_attention.autotvout_in_qk.dat"
#define AUTOTB_TVOUT_PC_in_q "../tv/rtldatafile/rtl.kernel_attention.autotvout_in_q.dat"
#define AUTOTB_TVOUT_PC_in_k "../tv/rtldatafile/rtl.kernel_attention.autotvout_in_k.dat"
#define AUTOTB_TVOUT_PC_afterQKMultiplication "../tv/rtldatafile/rtl.kernel_attention.autotvout_afterQKMultiplication.dat"
#define AUTOTB_TVOUT_PC_afterSoftmax "../tv/rtldatafile/rtl.kernel_attention.autotvout_afterSoftmax.dat"
#define AUTOTB_TVOUT_PC_afterRearrangeX2 "../tv/rtldatafile/rtl.kernel_attention.autotvout_afterRearrangeX2.dat"
#define AUTOTB_TVOUT_PC_afterQKXMultiplication "../tv/rtldatafile/rtl.kernel_attention.autotvout_afterQKXMultiplication.dat"
#define AUTOTB_TVOUT_PC_afterRearrangeQKX "../tv/rtldatafile/rtl.kernel_attention.autotvout_afterRearrangeQKX.dat"
#define AUTOTB_TVOUT_PC_afterPad2 "../tv/rtldatafile/rtl.kernel_attention.autotvout_afterPad2.dat"
#define AUTOTB_TVOUT_PC_afterConv2 "../tv/rtldatafile/rtl.kernel_attention.autotvout_afterConv2.dat"
#define AUTOTB_TVOUT_PC_kernel2 "../tv/rtldatafile/rtl.kernel_attention.autotvout_kernel2.dat"
#define AUTOTB_TVOUT_PC_bias2 "../tv/rtldatafile/rtl.kernel_attention.autotvout_bias2.dat"
#define AUTOTB_TVOUT_PC_afterAct2 "../tv/rtldatafile/rtl.kernel_attention.autotvout_afterAct2.dat"
#define AUTOTB_TVOUT_PC_QKV "../tv/rtldatafile/rtl.kernel_attention.autotvout_QKV.dat"
#define AUTOTB_TVOUT_PC_buffer_out "../tv/rtldatafile/rtl.kernel_attention.autotvout_buffer_out.dat"
#define AUTOTB_TVOUT_PC_buffer_result "../tv/rtldatafile/rtl.kernel_attention.autotvout_buffer_result.dat"
#define AUTOTB_TVOUT_PC_gmem "../tv/rtldatafile/rtl.kernel_attention.autotvout_gmem.dat"
#define AUTOTB_TVOUT_PC_gmem0 "../tv/rtldatafile/rtl.kernel_attention.autotvout_gmem0.dat"
#define AUTOTB_TVOUT_PC_gmem1 "../tv/rtldatafile/rtl.kernel_attention.autotvout_gmem1.dat"


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
  buffer_DataIn_1_depth = 0;
  afterNorm_depth = 0;
  norm1_mean_depth = 0;
  norm1_var_depth = 0;
  norm1_weight_depth = 0;
  norm1_bias_depth = 0;
  afterPad_depth = 0;
  afterRearrangeX_depth = 0;
  afterPad1_depth = 0;
  afterConv1_depth = 0;
  kernel1_depth = 0;
  bias1_depth = 0;
  in_qk_depth = 0;
  in_q_depth = 0;
  in_k_depth = 0;
  afterQKMultiplication_depth = 0;
  afterSoftmax_depth = 0;
  afterRearrangeX2_depth = 0;
  afterQKXMultiplication_depth = 0;
  afterRearrangeQKX_depth = 0;
  afterPad2_depth = 0;
  afterConv2_depth = 0;
  kernel2_depth = 0;
  bias2_depth = 0;
  afterAct2_depth = 0;
  QKV_depth = 0;
  buffer_out_depth = 0;
  buffer_result_depth = 0;
  gmem_depth = 0;
  gmem0_depth = 0;
  gmem1_depth = 0;
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
  total_list << "{buffer_DataIn_1 " << buffer_DataIn_1_depth << "}\n";
  total_list << "{afterNorm " << afterNorm_depth << "}\n";
  total_list << "{norm1_mean " << norm1_mean_depth << "}\n";
  total_list << "{norm1_var " << norm1_var_depth << "}\n";
  total_list << "{norm1_weight " << norm1_weight_depth << "}\n";
  total_list << "{norm1_bias " << norm1_bias_depth << "}\n";
  total_list << "{afterPad " << afterPad_depth << "}\n";
  total_list << "{afterRearrangeX " << afterRearrangeX_depth << "}\n";
  total_list << "{afterPad1 " << afterPad1_depth << "}\n";
  total_list << "{afterConv1 " << afterConv1_depth << "}\n";
  total_list << "{kernel1 " << kernel1_depth << "}\n";
  total_list << "{bias1 " << bias1_depth << "}\n";
  total_list << "{in_qk " << in_qk_depth << "}\n";
  total_list << "{in_q " << in_q_depth << "}\n";
  total_list << "{in_k " << in_k_depth << "}\n";
  total_list << "{afterQKMultiplication " << afterQKMultiplication_depth << "}\n";
  total_list << "{afterSoftmax " << afterSoftmax_depth << "}\n";
  total_list << "{afterRearrangeX2 " << afterRearrangeX2_depth << "}\n";
  total_list << "{afterQKXMultiplication " << afterQKXMultiplication_depth << "}\n";
  total_list << "{afterRearrangeQKX " << afterRearrangeQKX_depth << "}\n";
  total_list << "{afterPad2 " << afterPad2_depth << "}\n";
  total_list << "{afterConv2 " << afterConv2_depth << "}\n";
  total_list << "{kernel2 " << kernel2_depth << "}\n";
  total_list << "{bias2 " << bias2_depth << "}\n";
  total_list << "{afterAct2 " << afterAct2_depth << "}\n";
  total_list << "{QKV " << QKV_depth << "}\n";
  total_list << "{buffer_out " << buffer_out_depth << "}\n";
  total_list << "{buffer_result " << buffer_result_depth << "}\n";
  total_list << "{gmem " << gmem_depth << "}\n";
  total_list << "{gmem0 " << gmem0_depth << "}\n";
  total_list << "{gmem1 " << gmem1_depth << "}\n";
  return total_list.str();
}
void set_num (int num , int* class_num) {
  (*class_num) = (*class_num) > num ? (*class_num) : num;
}
void set_string(std::string list, std::string* class_list) {
  (*class_list) = list;
}
  public:
    int buffer_DataIn_1_depth;
    int afterNorm_depth;
    int norm1_mean_depth;
    int norm1_var_depth;
    int norm1_weight_depth;
    int norm1_bias_depth;
    int afterPad_depth;
    int afterRearrangeX_depth;
    int afterPad1_depth;
    int afterConv1_depth;
    int kernel1_depth;
    int bias1_depth;
    int in_qk_depth;
    int in_q_depth;
    int in_k_depth;
    int afterQKMultiplication_depth;
    int afterSoftmax_depth;
    int afterRearrangeX2_depth;
    int afterQKXMultiplication_depth;
    int afterRearrangeQKX_depth;
    int afterPad2_depth;
    int afterConv2_depth;
    int kernel2_depth;
    int bias2_depth;
    int afterAct2_depth;
    int QKV_depth;
    int buffer_out_depth;
    int buffer_result_depth;
    int gmem_depth;
    int gmem0_depth;
    int gmem1_depth;
    int trans_num;
  private:
    ofstream mFile;
    const char* mName;
};


extern "C" void kernel_attention_hw_stub_wrapper(volatile void *, volatile void *, volatile void *, volatile void *, volatile void *, volatile void *, volatile void *, volatile void *, volatile void *, volatile void *, volatile void *, volatile void *, volatile void *, volatile void *, volatile void *, volatile void *, volatile void *, volatile void *, volatile void *, volatile void *, volatile void *, volatile void *, volatile void *, volatile void *, volatile void *, volatile void *, volatile void *, volatile void *);

extern "C" void apatb_kernel_attention_hw(volatile void * __xlx_apatb_param_buffer_DataIn_1, volatile void * __xlx_apatb_param_afterNorm, volatile void * __xlx_apatb_param_norm1_mean, volatile void * __xlx_apatb_param_norm1_var, volatile void * __xlx_apatb_param_norm1_weight, volatile void * __xlx_apatb_param_norm1_bias, volatile void * __xlx_apatb_param_afterPad, volatile void * __xlx_apatb_param_afterRearrangeX, volatile void * __xlx_apatb_param_afterPad1, volatile void * __xlx_apatb_param_afterConv1, volatile void * __xlx_apatb_param_kernel1, volatile void * __xlx_apatb_param_bias1, volatile void * __xlx_apatb_param_in_qk, volatile void * __xlx_apatb_param_in_q, volatile void * __xlx_apatb_param_in_k, volatile void * __xlx_apatb_param_afterQKMultiplication, volatile void * __xlx_apatb_param_afterSoftmax, volatile void * __xlx_apatb_param_afterRearrangeX2, volatile void * __xlx_apatb_param_afterQKXMultiplication, volatile void * __xlx_apatb_param_afterRearrangeQKX, volatile void * __xlx_apatb_param_afterPad2, volatile void * __xlx_apatb_param_afterConv2, volatile void * __xlx_apatb_param_kernel2, volatile void * __xlx_apatb_param_bias2, volatile void * __xlx_apatb_param_afterAct2, volatile void * __xlx_apatb_param_QKV, volatile void * __xlx_apatb_param_buffer_out, volatile void * __xlx_apatb_param_buffer_result) {
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
transaction<32> tr(501552);
aesl_fh.read(AUTOTB_TVOUT_PC_gmem, tr.p, tr.tbytes);
if (little_endian()) { tr.reorder(); }
tr.send<4>((char*)__xlx_apatb_param_norm1_mean, 80, 0);
tr.send<4>((char*)__xlx_apatb_param_norm1_var, 80, 80);
tr.send<4>((char*)__xlx_apatb_param_norm1_weight, 80, 160);
tr.send<4>((char*)__xlx_apatb_param_norm1_bias, 80, 240);
tr.send<4>((char*)__xlx_apatb_param_afterPad, 15680, 320);
tr.send<4>((char*)__xlx_apatb_param_afterRearrangeX, 15680, 16000);
tr.send<4>((char*)__xlx_apatb_param_afterPad1, 15680, 31680);
tr.send<4>((char*)__xlx_apatb_param_afterConv1, 31360, 47360);
tr.send<4>((char*)__xlx_apatb_param_kernel1, 12800, 78720);
tr.send<4>((char*)__xlx_apatb_param_bias1, 160, 91520);
tr.send<4>((char*)__xlx_apatb_param_in_qk, 31360, 91680);
tr.send<4>((char*)__xlx_apatb_param_in_q, 15680, 123040);
tr.send<4>((char*)__xlx_apatb_param_in_k, 15680, 138720);
tr.send<4>((char*)__xlx_apatb_param_afterQKMultiplication, 38416, 154400);
tr.send<4>((char*)__xlx_apatb_param_afterSoftmax, 38416, 192816);
tr.send<4>((char*)__xlx_apatb_param_afterRearrangeX2, 15680, 231232);
tr.send<4>((char*)__xlx_apatb_param_afterQKXMultiplication, 15680, 246912);
tr.send<4>((char*)__xlx_apatb_param_afterRearrangeQKX, 15680, 262592);
tr.send<4>((char*)__xlx_apatb_param_afterPad2, 15680, 278272);
tr.send<4>((char*)__xlx_apatb_param_afterConv2, 47040, 293952);
tr.send<4>((char*)__xlx_apatb_param_kernel2, 19200, 340992);
tr.send<4>((char*)__xlx_apatb_param_bias2, 240, 360192);
tr.send<4>((char*)__xlx_apatb_param_afterAct2, 47040, 360432);
tr.send<4>((char*)__xlx_apatb_param_QKV, 47040, 407472);
tr.send<4>((char*)__xlx_apatb_param_buffer_out, 47040, 454512);
}
#else
try {
static PostCheck<32> pc(AUTOTB_TVOUT_PC_gmem);
pc.psize = 4;
pc.param = (char*)__xlx_apatb_param_norm1_mean;
pc.depth = 80;
pc.run(AESL_transaction_pc, 0);pc.param = (char*)__xlx_apatb_param_norm1_var;
pc.depth = 80;
pc.run(AESL_transaction_pc, 0);
pc.param = (char*)__xlx_apatb_param_norm1_weight;
pc.depth = 80;
pc.run(AESL_transaction_pc, 0);
pc.param = (char*)__xlx_apatb_param_norm1_bias;
pc.depth = 80;
pc.run(AESL_transaction_pc, 0);
pc.param = (char*)__xlx_apatb_param_afterPad;
pc.depth = 15680;
pc.run(AESL_transaction_pc, 0);
pc.param = (char*)__xlx_apatb_param_afterRearrangeX;
pc.depth = 15680;
pc.run(AESL_transaction_pc, 0);
pc.param = (char*)__xlx_apatb_param_afterPad1;
pc.depth = 15680;
pc.run(AESL_transaction_pc, 0);
pc.param = (char*)__xlx_apatb_param_afterConv1;
pc.depth = 31360;
pc.run(AESL_transaction_pc, 0);
pc.param = (char*)__xlx_apatb_param_kernel1;
pc.depth = 12800;
pc.run(AESL_transaction_pc, 0);
pc.param = (char*)__xlx_apatb_param_bias1;
pc.depth = 160;
pc.run(AESL_transaction_pc, 0);
pc.param = (char*)__xlx_apatb_param_in_qk;
pc.depth = 31360;
pc.run(AESL_transaction_pc, 0);
pc.param = (char*)__xlx_apatb_param_in_q;
pc.depth = 15680;
pc.run(AESL_transaction_pc, 0);
pc.param = (char*)__xlx_apatb_param_in_k;
pc.depth = 15680;
pc.run(AESL_transaction_pc, 0);
pc.param = (char*)__xlx_apatb_param_afterQKMultiplication;
pc.depth = 38416;
pc.run(AESL_transaction_pc, 0);
pc.param = (char*)__xlx_apatb_param_afterSoftmax;
pc.depth = 38416;
pc.run(AESL_transaction_pc, 0);
pc.param = (char*)__xlx_apatb_param_afterRearrangeX2;
pc.depth = 15680;
pc.run(AESL_transaction_pc, 0);
pc.param = (char*)__xlx_apatb_param_afterQKXMultiplication;
pc.depth = 15680;
pc.run(AESL_transaction_pc, 0);
pc.param = (char*)__xlx_apatb_param_afterRearrangeQKX;
pc.depth = 15680;
pc.run(AESL_transaction_pc, 0);
pc.param = (char*)__xlx_apatb_param_afterPad2;
pc.depth = 15680;
pc.run(AESL_transaction_pc, 0);
pc.param = (char*)__xlx_apatb_param_afterConv2;
pc.depth = 47040;
pc.run(AESL_transaction_pc, 0);
pc.param = (char*)__xlx_apatb_param_kernel2;
pc.depth = 19200;
pc.run(AESL_transaction_pc, 0);
pc.param = (char*)__xlx_apatb_param_bias2;
pc.depth = 240;
pc.run(AESL_transaction_pc, 0);
pc.param = (char*)__xlx_apatb_param_afterAct2;
pc.depth = 47040;
pc.run(AESL_transaction_pc, 0);
pc.param = (char*)__xlx_apatb_param_QKV;
pc.depth = 47040;
pc.run(AESL_transaction_pc, 0);
pc.param = (char*)__xlx_apatb_param_buffer_out;
pc.depth = 47040;
pc.run(AESL_transaction_pc, 0);

} catch (SimException &e) {
  std::cout << "at line " << e.line << " occurred exception, " << e.msg << "\n";
}
#endif
#ifdef USE_BINARY_TV_FILE
{
transaction<32> tr(62720);
aesl_fh.read(AUTOTB_TVOUT_PC_gmem0, tr.p, tr.tbytes);
if (little_endian()) { tr.reorder(); }
tr.send<4>((char*)__xlx_apatb_param_buffer_DataIn_1, 15680, 0);
tr.send<4>((char*)__xlx_apatb_param_buffer_result, 47040, 15680);
}
#else
try {
static PostCheck<32> pc(AUTOTB_TVOUT_PC_gmem0);
pc.psize = 4;
pc.param = (char*)__xlx_apatb_param_buffer_DataIn_1;
pc.depth = 15680;
pc.run(AESL_transaction_pc, 0);pc.param = (char*)__xlx_apatb_param_buffer_result;
pc.depth = 47040;
pc.run(AESL_transaction_pc, 0);

} catch (SimException &e) {
  std::cout << "at line " << e.line << " occurred exception, " << e.msg << "\n";
}
#endif
#ifdef USE_BINARY_TV_FILE
{
transaction<32> tr(15680);
aesl_fh.read(AUTOTB_TVOUT_PC_gmem1, tr.p, tr.tbytes);
if (little_endian()) { tr.reorder(); }
tr.send<4>((char*)__xlx_apatb_param_afterNorm, 15680, 0);
}
#else
try {
static PostCheck<32> pc(AUTOTB_TVOUT_PC_gmem1);
pc.psize = 4;
pc.param = (char*)__xlx_apatb_param_afterNorm;
pc.depth = 15680;
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
unsigned __xlx_offset_byte_param_buffer_DataIn_1 = 0;
unsigned __xlx_offset_byte_param_buffer_result = 0;
unsigned __xlx_offset_byte_param_afterNorm = 0;
unsigned __xlx_offset_byte_param_norm1_mean = 0;
unsigned __xlx_offset_byte_param_norm1_var = 0;
unsigned __xlx_offset_byte_param_norm1_weight = 0;
unsigned __xlx_offset_byte_param_norm1_bias = 0;
unsigned __xlx_offset_byte_param_afterPad = 0;
unsigned __xlx_offset_byte_param_afterRearrangeX = 0;
unsigned __xlx_offset_byte_param_afterPad1 = 0;
unsigned __xlx_offset_byte_param_afterConv1 = 0;
unsigned __xlx_offset_byte_param_kernel1 = 0;
unsigned __xlx_offset_byte_param_bias1 = 0;
unsigned __xlx_offset_byte_param_in_qk = 0;
unsigned __xlx_offset_byte_param_in_q = 0;
unsigned __xlx_offset_byte_param_in_k = 0;
unsigned __xlx_offset_byte_param_afterQKMultiplication = 0;
unsigned __xlx_offset_byte_param_afterSoftmax = 0;
unsigned __xlx_offset_byte_param_afterRearrangeX2 = 0;
unsigned __xlx_offset_byte_param_afterQKXMultiplication = 0;
unsigned __xlx_offset_byte_param_afterRearrangeQKX = 0;
unsigned __xlx_offset_byte_param_afterPad2 = 0;
unsigned __xlx_offset_byte_param_afterConv2 = 0;
unsigned __xlx_offset_byte_param_kernel2 = 0;
unsigned __xlx_offset_byte_param_bias2 = 0;
unsigned __xlx_offset_byte_param_afterAct2 = 0;
unsigned __xlx_offset_byte_param_QKV = 0;
unsigned __xlx_offset_byte_param_buffer_out = 0;
#ifdef USE_BINARY_TV_FILE
{
aesl_fh.touch(AUTOTB_TVIN_gmem, 'b');
transaction<32> tr(501552);
__xlx_offset_byte_param_norm1_mean = 0*4;
if (__xlx_apatb_param_norm1_mean) {
  tr.import<4>((char*)__xlx_apatb_param_norm1_mean, 80, 0);
}
__xlx_offset_byte_param_norm1_var = 80*4;
if (__xlx_apatb_param_norm1_var) {
  tr.import<4>((char*)__xlx_apatb_param_norm1_var, 80, 0);
}
__xlx_offset_byte_param_norm1_weight = 160*4;
if (__xlx_apatb_param_norm1_weight) {
  tr.import<4>((char*)__xlx_apatb_param_norm1_weight, 80, 0);
}
__xlx_offset_byte_param_norm1_bias = 240*4;
if (__xlx_apatb_param_norm1_bias) {
  tr.import<4>((char*)__xlx_apatb_param_norm1_bias, 80, 0);
}
__xlx_offset_byte_param_afterPad = 320*4;
if (__xlx_apatb_param_afterPad) {
  tr.import<4>((char*)__xlx_apatb_param_afterPad, 15680, 0);
}
__xlx_offset_byte_param_afterRearrangeX = 16000*4;
if (__xlx_apatb_param_afterRearrangeX) {
  tr.import<4>((char*)__xlx_apatb_param_afterRearrangeX, 15680, 0);
}
__xlx_offset_byte_param_afterPad1 = 31680*4;
if (__xlx_apatb_param_afterPad1) {
  tr.import<4>((char*)__xlx_apatb_param_afterPad1, 15680, 0);
}
__xlx_offset_byte_param_afterConv1 = 47360*4;
if (__xlx_apatb_param_afterConv1) {
  tr.import<4>((char*)__xlx_apatb_param_afterConv1, 31360, 0);
}
__xlx_offset_byte_param_kernel1 = 78720*4;
if (__xlx_apatb_param_kernel1) {
  tr.import<4>((char*)__xlx_apatb_param_kernel1, 12800, 0);
}
__xlx_offset_byte_param_bias1 = 91520*4;
if (__xlx_apatb_param_bias1) {
  tr.import<4>((char*)__xlx_apatb_param_bias1, 160, 0);
}
__xlx_offset_byte_param_in_qk = 91680*4;
if (__xlx_apatb_param_in_qk) {
  tr.import<4>((char*)__xlx_apatb_param_in_qk, 31360, 0);
}
__xlx_offset_byte_param_in_q = 123040*4;
if (__xlx_apatb_param_in_q) {
  tr.import<4>((char*)__xlx_apatb_param_in_q, 15680, 0);
}
__xlx_offset_byte_param_in_k = 138720*4;
if (__xlx_apatb_param_in_k) {
  tr.import<4>((char*)__xlx_apatb_param_in_k, 15680, 0);
}
__xlx_offset_byte_param_afterQKMultiplication = 154400*4;
if (__xlx_apatb_param_afterQKMultiplication) {
  tr.import<4>((char*)__xlx_apatb_param_afterQKMultiplication, 38416, 0);
}
__xlx_offset_byte_param_afterSoftmax = 192816*4;
if (__xlx_apatb_param_afterSoftmax) {
  tr.import<4>((char*)__xlx_apatb_param_afterSoftmax, 38416, 0);
}
__xlx_offset_byte_param_afterRearrangeX2 = 231232*4;
if (__xlx_apatb_param_afterRearrangeX2) {
  tr.import<4>((char*)__xlx_apatb_param_afterRearrangeX2, 15680, 0);
}
__xlx_offset_byte_param_afterQKXMultiplication = 246912*4;
if (__xlx_apatb_param_afterQKXMultiplication) {
  tr.import<4>((char*)__xlx_apatb_param_afterQKXMultiplication, 15680, 0);
}
__xlx_offset_byte_param_afterRearrangeQKX = 262592*4;
if (__xlx_apatb_param_afterRearrangeQKX) {
  tr.import<4>((char*)__xlx_apatb_param_afterRearrangeQKX, 15680, 0);
}
__xlx_offset_byte_param_afterPad2 = 278272*4;
if (__xlx_apatb_param_afterPad2) {
  tr.import<4>((char*)__xlx_apatb_param_afterPad2, 15680, 0);
}
__xlx_offset_byte_param_afterConv2 = 293952*4;
if (__xlx_apatb_param_afterConv2) {
  tr.import<4>((char*)__xlx_apatb_param_afterConv2, 47040, 0);
}
__xlx_offset_byte_param_kernel2 = 340992*4;
if (__xlx_apatb_param_kernel2) {
  tr.import<4>((char*)__xlx_apatb_param_kernel2, 19200, 0);
}
__xlx_offset_byte_param_bias2 = 360192*4;
if (__xlx_apatb_param_bias2) {
  tr.import<4>((char*)__xlx_apatb_param_bias2, 240, 0);
}
__xlx_offset_byte_param_afterAct2 = 360432*4;
if (__xlx_apatb_param_afterAct2) {
  tr.import<4>((char*)__xlx_apatb_param_afterAct2, 47040, 0);
}
__xlx_offset_byte_param_QKV = 407472*4;
if (__xlx_apatb_param_QKV) {
  tr.import<4>((char*)__xlx_apatb_param_QKV, 47040, 0);
}
__xlx_offset_byte_param_buffer_out = 454512*4;
if (__xlx_apatb_param_buffer_out) {
  tr.import<4>((char*)__xlx_apatb_param_buffer_out, 47040, 0);
}
aesl_fh.write(AUTOTB_TVIN_gmem, tr.p, tr.tbytes);
tcl_file.set_num(501552, &tcl_file.gmem_depth);
}
#else
aesl_fh.touch(AUTOTB_TVIN_gmem);
{
aesl_fh.write(AUTOTB_TVIN_gmem, begin_str(AESL_transaction));
__xlx_offset_byte_param_norm1_mean = 0*4;
if (__xlx_apatb_param_norm1_mean) {
for (size_t i = 0; i < 80; ++i) {
unsigned char *pos = (unsigned char*)__xlx_apatb_param_norm1_mean + i * 4;
std::string s = formatData(pos, 32);
aesl_fh.write(AUTOTB_TVIN_gmem, s);
}
}
__xlx_offset_byte_param_norm1_var = 80*4;
if (__xlx_apatb_param_norm1_var) {
for (size_t i = 0; i < 80; ++i) {
unsigned char *pos = (unsigned char*)__xlx_apatb_param_norm1_var + i * 4;
std::string s = formatData(pos, 32);
aesl_fh.write(AUTOTB_TVIN_gmem, s);
}
}
__xlx_offset_byte_param_norm1_weight = 160*4;
if (__xlx_apatb_param_norm1_weight) {
for (size_t i = 0; i < 80; ++i) {
unsigned char *pos = (unsigned char*)__xlx_apatb_param_norm1_weight + i * 4;
std::string s = formatData(pos, 32);
aesl_fh.write(AUTOTB_TVIN_gmem, s);
}
}
__xlx_offset_byte_param_norm1_bias = 240*4;
if (__xlx_apatb_param_norm1_bias) {
for (size_t i = 0; i < 80; ++i) {
unsigned char *pos = (unsigned char*)__xlx_apatb_param_norm1_bias + i * 4;
std::string s = formatData(pos, 32);
aesl_fh.write(AUTOTB_TVIN_gmem, s);
}
}
__xlx_offset_byte_param_afterPad = 320*4;
if (__xlx_apatb_param_afterPad) {
for (size_t i = 0; i < 15680; ++i) {
unsigned char *pos = (unsigned char*)__xlx_apatb_param_afterPad + i * 4;
std::string s = formatData(pos, 32);
aesl_fh.write(AUTOTB_TVIN_gmem, s);
}
}
__xlx_offset_byte_param_afterRearrangeX = 16000*4;
if (__xlx_apatb_param_afterRearrangeX) {
for (size_t i = 0; i < 15680; ++i) {
unsigned char *pos = (unsigned char*)__xlx_apatb_param_afterRearrangeX + i * 4;
std::string s = formatData(pos, 32);
aesl_fh.write(AUTOTB_TVIN_gmem, s);
}
}
__xlx_offset_byte_param_afterPad1 = 31680*4;
if (__xlx_apatb_param_afterPad1) {
for (size_t i = 0; i < 15680; ++i) {
unsigned char *pos = (unsigned char*)__xlx_apatb_param_afterPad1 + i * 4;
std::string s = formatData(pos, 32);
aesl_fh.write(AUTOTB_TVIN_gmem, s);
}
}
__xlx_offset_byte_param_afterConv1 = 47360*4;
if (__xlx_apatb_param_afterConv1) {
for (size_t i = 0; i < 31360; ++i) {
unsigned char *pos = (unsigned char*)__xlx_apatb_param_afterConv1 + i * 4;
std::string s = formatData(pos, 32);
aesl_fh.write(AUTOTB_TVIN_gmem, s);
}
}
__xlx_offset_byte_param_kernel1 = 78720*4;
if (__xlx_apatb_param_kernel1) {
for (size_t i = 0; i < 12800; ++i) {
unsigned char *pos = (unsigned char*)__xlx_apatb_param_kernel1 + i * 4;
std::string s = formatData(pos, 32);
aesl_fh.write(AUTOTB_TVIN_gmem, s);
}
}
__xlx_offset_byte_param_bias1 = 91520*4;
if (__xlx_apatb_param_bias1) {
for (size_t i = 0; i < 160; ++i) {
unsigned char *pos = (unsigned char*)__xlx_apatb_param_bias1 + i * 4;
std::string s = formatData(pos, 32);
aesl_fh.write(AUTOTB_TVIN_gmem, s);
}
}
__xlx_offset_byte_param_in_qk = 91680*4;
if (__xlx_apatb_param_in_qk) {
for (size_t i = 0; i < 31360; ++i) {
unsigned char *pos = (unsigned char*)__xlx_apatb_param_in_qk + i * 4;
std::string s = formatData(pos, 32);
aesl_fh.write(AUTOTB_TVIN_gmem, s);
}
}
__xlx_offset_byte_param_in_q = 123040*4;
if (__xlx_apatb_param_in_q) {
for (size_t i = 0; i < 15680; ++i) {
unsigned char *pos = (unsigned char*)__xlx_apatb_param_in_q + i * 4;
std::string s = formatData(pos, 32);
aesl_fh.write(AUTOTB_TVIN_gmem, s);
}
}
__xlx_offset_byte_param_in_k = 138720*4;
if (__xlx_apatb_param_in_k) {
for (size_t i = 0; i < 15680; ++i) {
unsigned char *pos = (unsigned char*)__xlx_apatb_param_in_k + i * 4;
std::string s = formatData(pos, 32);
aesl_fh.write(AUTOTB_TVIN_gmem, s);
}
}
__xlx_offset_byte_param_afterQKMultiplication = 154400*4;
if (__xlx_apatb_param_afterQKMultiplication) {
for (size_t i = 0; i < 38416; ++i) {
unsigned char *pos = (unsigned char*)__xlx_apatb_param_afterQKMultiplication + i * 4;
std::string s = formatData(pos, 32);
aesl_fh.write(AUTOTB_TVIN_gmem, s);
}
}
__xlx_offset_byte_param_afterSoftmax = 192816*4;
if (__xlx_apatb_param_afterSoftmax) {
for (size_t i = 0; i < 38416; ++i) {
unsigned char *pos = (unsigned char*)__xlx_apatb_param_afterSoftmax + i * 4;
std::string s = formatData(pos, 32);
aesl_fh.write(AUTOTB_TVIN_gmem, s);
}
}
__xlx_offset_byte_param_afterRearrangeX2 = 231232*4;
if (__xlx_apatb_param_afterRearrangeX2) {
for (size_t i = 0; i < 15680; ++i) {
unsigned char *pos = (unsigned char*)__xlx_apatb_param_afterRearrangeX2 + i * 4;
std::string s = formatData(pos, 32);
aesl_fh.write(AUTOTB_TVIN_gmem, s);
}
}
__xlx_offset_byte_param_afterQKXMultiplication = 246912*4;
if (__xlx_apatb_param_afterQKXMultiplication) {
for (size_t i = 0; i < 15680; ++i) {
unsigned char *pos = (unsigned char*)__xlx_apatb_param_afterQKXMultiplication + i * 4;
std::string s = formatData(pos, 32);
aesl_fh.write(AUTOTB_TVIN_gmem, s);
}
}
__xlx_offset_byte_param_afterRearrangeQKX = 262592*4;
if (__xlx_apatb_param_afterRearrangeQKX) {
for (size_t i = 0; i < 15680; ++i) {
unsigned char *pos = (unsigned char*)__xlx_apatb_param_afterRearrangeQKX + i * 4;
std::string s = formatData(pos, 32);
aesl_fh.write(AUTOTB_TVIN_gmem, s);
}
}
__xlx_offset_byte_param_afterPad2 = 278272*4;
if (__xlx_apatb_param_afterPad2) {
for (size_t i = 0; i < 15680; ++i) {
unsigned char *pos = (unsigned char*)__xlx_apatb_param_afterPad2 + i * 4;
std::string s = formatData(pos, 32);
aesl_fh.write(AUTOTB_TVIN_gmem, s);
}
}
__xlx_offset_byte_param_afterConv2 = 293952*4;
if (__xlx_apatb_param_afterConv2) {
for (size_t i = 0; i < 47040; ++i) {
unsigned char *pos = (unsigned char*)__xlx_apatb_param_afterConv2 + i * 4;
std::string s = formatData(pos, 32);
aesl_fh.write(AUTOTB_TVIN_gmem, s);
}
}
__xlx_offset_byte_param_kernel2 = 340992*4;
if (__xlx_apatb_param_kernel2) {
for (size_t i = 0; i < 19200; ++i) {
unsigned char *pos = (unsigned char*)__xlx_apatb_param_kernel2 + i * 4;
std::string s = formatData(pos, 32);
aesl_fh.write(AUTOTB_TVIN_gmem, s);
}
}
__xlx_offset_byte_param_bias2 = 360192*4;
if (__xlx_apatb_param_bias2) {
for (size_t i = 0; i < 240; ++i) {
unsigned char *pos = (unsigned char*)__xlx_apatb_param_bias2 + i * 4;
std::string s = formatData(pos, 32);
aesl_fh.write(AUTOTB_TVIN_gmem, s);
}
}
__xlx_offset_byte_param_afterAct2 = 360432*4;
if (__xlx_apatb_param_afterAct2) {
for (size_t i = 0; i < 47040; ++i) {
unsigned char *pos = (unsigned char*)__xlx_apatb_param_afterAct2 + i * 4;
std::string s = formatData(pos, 32);
aesl_fh.write(AUTOTB_TVIN_gmem, s);
}
}
__xlx_offset_byte_param_QKV = 407472*4;
if (__xlx_apatb_param_QKV) {
for (size_t i = 0; i < 47040; ++i) {
unsigned char *pos = (unsigned char*)__xlx_apatb_param_QKV + i * 4;
std::string s = formatData(pos, 32);
aesl_fh.write(AUTOTB_TVIN_gmem, s);
}
}
__xlx_offset_byte_param_buffer_out = 454512*4;
if (__xlx_apatb_param_buffer_out) {
for (size_t i = 0; i < 47040; ++i) {
unsigned char *pos = (unsigned char*)__xlx_apatb_param_buffer_out + i * 4;
std::string s = formatData(pos, 32);
aesl_fh.write(AUTOTB_TVIN_gmem, s);
}
}
tcl_file.set_num(501552, &tcl_file.gmem_depth);
aesl_fh.write(AUTOTB_TVIN_gmem, end_str());
}
#endif
#ifdef USE_BINARY_TV_FILE
{
aesl_fh.touch(AUTOTB_TVIN_gmem0, 'b');
transaction<32> tr(62720);
__xlx_offset_byte_param_buffer_DataIn_1 = 0*4;
if (__xlx_apatb_param_buffer_DataIn_1) {
  tr.import<4>((char*)__xlx_apatb_param_buffer_DataIn_1, 15680, 0);
}
__xlx_offset_byte_param_buffer_result = 15680*4;
if (__xlx_apatb_param_buffer_result) {
  tr.import<4>((char*)__xlx_apatb_param_buffer_result, 47040, 0);
}
aesl_fh.write(AUTOTB_TVIN_gmem0, tr.p, tr.tbytes);
tcl_file.set_num(62720, &tcl_file.gmem0_depth);
}
#else
aesl_fh.touch(AUTOTB_TVIN_gmem0);
{
aesl_fh.write(AUTOTB_TVIN_gmem0, begin_str(AESL_transaction));
__xlx_offset_byte_param_buffer_DataIn_1 = 0*4;
if (__xlx_apatb_param_buffer_DataIn_1) {
for (size_t i = 0; i < 15680; ++i) {
unsigned char *pos = (unsigned char*)__xlx_apatb_param_buffer_DataIn_1 + i * 4;
std::string s = formatData(pos, 32);
aesl_fh.write(AUTOTB_TVIN_gmem0, s);
}
}
__xlx_offset_byte_param_buffer_result = 15680*4;
if (__xlx_apatb_param_buffer_result) {
for (size_t i = 0; i < 47040; ++i) {
unsigned char *pos = (unsigned char*)__xlx_apatb_param_buffer_result + i * 4;
std::string s = formatData(pos, 32);
aesl_fh.write(AUTOTB_TVIN_gmem0, s);
}
}
tcl_file.set_num(62720, &tcl_file.gmem0_depth);
aesl_fh.write(AUTOTB_TVIN_gmem0, end_str());
}
#endif
#ifdef USE_BINARY_TV_FILE
{
aesl_fh.touch(AUTOTB_TVIN_gmem1, 'b');
transaction<32> tr(15680);
__xlx_offset_byte_param_afterNorm = 0*4;
if (__xlx_apatb_param_afterNorm) {
  tr.import<4>((char*)__xlx_apatb_param_afterNorm, 15680, 0);
}
aesl_fh.write(AUTOTB_TVIN_gmem1, tr.p, tr.tbytes);
tcl_file.set_num(15680, &tcl_file.gmem1_depth);
}
#else
aesl_fh.touch(AUTOTB_TVIN_gmem1);
{
aesl_fh.write(AUTOTB_TVIN_gmem1, begin_str(AESL_transaction));
__xlx_offset_byte_param_afterNorm = 0*4;
if (__xlx_apatb_param_afterNorm) {
for (size_t i = 0; i < 15680; ++i) {
unsigned char *pos = (unsigned char*)__xlx_apatb_param_afterNorm + i * 4;
std::string s = formatData(pos, 32);
aesl_fh.write(AUTOTB_TVIN_gmem1, s);
}
}
tcl_file.set_num(15680, &tcl_file.gmem1_depth);
aesl_fh.write(AUTOTB_TVIN_gmem1, end_str());
}
#endif
// print buffer_DataIn_1 Transactions
{
aesl_fh.write(AUTOTB_TVIN_buffer_DataIn_1, begin_str(AESL_transaction));
{
auto *pos = (unsigned char*)&__xlx_offset_byte_param_buffer_DataIn_1;
aesl_fh.write(AUTOTB_TVIN_buffer_DataIn_1, formatData(pos, 32));
}
  tcl_file.set_num(1, &tcl_file.buffer_DataIn_1_depth);
aesl_fh.write(AUTOTB_TVIN_buffer_DataIn_1, end_str());
}

// print afterNorm Transactions
{
aesl_fh.write(AUTOTB_TVIN_afterNorm, begin_str(AESL_transaction));
{
auto *pos = (unsigned char*)&__xlx_offset_byte_param_afterNorm;
aesl_fh.write(AUTOTB_TVIN_afterNorm, formatData(pos, 32));
}
  tcl_file.set_num(1, &tcl_file.afterNorm_depth);
aesl_fh.write(AUTOTB_TVIN_afterNorm, end_str());
}

// print norm1_mean Transactions
{
aesl_fh.write(AUTOTB_TVIN_norm1_mean, begin_str(AESL_transaction));
{
auto *pos = (unsigned char*)&__xlx_offset_byte_param_norm1_mean;
aesl_fh.write(AUTOTB_TVIN_norm1_mean, formatData(pos, 32));
}
  tcl_file.set_num(1, &tcl_file.norm1_mean_depth);
aesl_fh.write(AUTOTB_TVIN_norm1_mean, end_str());
}

// print norm1_var Transactions
{
aesl_fh.write(AUTOTB_TVIN_norm1_var, begin_str(AESL_transaction));
{
auto *pos = (unsigned char*)&__xlx_offset_byte_param_norm1_var;
aesl_fh.write(AUTOTB_TVIN_norm1_var, formatData(pos, 32));
}
  tcl_file.set_num(1, &tcl_file.norm1_var_depth);
aesl_fh.write(AUTOTB_TVIN_norm1_var, end_str());
}

// print norm1_weight Transactions
{
aesl_fh.write(AUTOTB_TVIN_norm1_weight, begin_str(AESL_transaction));
{
auto *pos = (unsigned char*)&__xlx_offset_byte_param_norm1_weight;
aesl_fh.write(AUTOTB_TVIN_norm1_weight, formatData(pos, 32));
}
  tcl_file.set_num(1, &tcl_file.norm1_weight_depth);
aesl_fh.write(AUTOTB_TVIN_norm1_weight, end_str());
}

// print norm1_bias Transactions
{
aesl_fh.write(AUTOTB_TVIN_norm1_bias, begin_str(AESL_transaction));
{
auto *pos = (unsigned char*)&__xlx_offset_byte_param_norm1_bias;
aesl_fh.write(AUTOTB_TVIN_norm1_bias, formatData(pos, 32));
}
  tcl_file.set_num(1, &tcl_file.norm1_bias_depth);
aesl_fh.write(AUTOTB_TVIN_norm1_bias, end_str());
}

// print afterPad Transactions
{
aesl_fh.write(AUTOTB_TVIN_afterPad, begin_str(AESL_transaction));
{
auto *pos = (unsigned char*)&__xlx_offset_byte_param_afterPad;
aesl_fh.write(AUTOTB_TVIN_afterPad, formatData(pos, 32));
}
  tcl_file.set_num(1, &tcl_file.afterPad_depth);
aesl_fh.write(AUTOTB_TVIN_afterPad, end_str());
}

// print afterRearrangeX Transactions
{
aesl_fh.write(AUTOTB_TVIN_afterRearrangeX, begin_str(AESL_transaction));
{
auto *pos = (unsigned char*)&__xlx_offset_byte_param_afterRearrangeX;
aesl_fh.write(AUTOTB_TVIN_afterRearrangeX, formatData(pos, 32));
}
  tcl_file.set_num(1, &tcl_file.afterRearrangeX_depth);
aesl_fh.write(AUTOTB_TVIN_afterRearrangeX, end_str());
}

// print afterPad1 Transactions
{
aesl_fh.write(AUTOTB_TVIN_afterPad1, begin_str(AESL_transaction));
{
auto *pos = (unsigned char*)&__xlx_offset_byte_param_afterPad1;
aesl_fh.write(AUTOTB_TVIN_afterPad1, formatData(pos, 32));
}
  tcl_file.set_num(1, &tcl_file.afterPad1_depth);
aesl_fh.write(AUTOTB_TVIN_afterPad1, end_str());
}

// print afterConv1 Transactions
{
aesl_fh.write(AUTOTB_TVIN_afterConv1, begin_str(AESL_transaction));
{
auto *pos = (unsigned char*)&__xlx_offset_byte_param_afterConv1;
aesl_fh.write(AUTOTB_TVIN_afterConv1, formatData(pos, 32));
}
  tcl_file.set_num(1, &tcl_file.afterConv1_depth);
aesl_fh.write(AUTOTB_TVIN_afterConv1, end_str());
}

// print kernel1 Transactions
{
aesl_fh.write(AUTOTB_TVIN_kernel1, begin_str(AESL_transaction));
{
auto *pos = (unsigned char*)&__xlx_offset_byte_param_kernel1;
aesl_fh.write(AUTOTB_TVIN_kernel1, formatData(pos, 32));
}
  tcl_file.set_num(1, &tcl_file.kernel1_depth);
aesl_fh.write(AUTOTB_TVIN_kernel1, end_str());
}

// print bias1 Transactions
{
aesl_fh.write(AUTOTB_TVIN_bias1, begin_str(AESL_transaction));
{
auto *pos = (unsigned char*)&__xlx_offset_byte_param_bias1;
aesl_fh.write(AUTOTB_TVIN_bias1, formatData(pos, 32));
}
  tcl_file.set_num(1, &tcl_file.bias1_depth);
aesl_fh.write(AUTOTB_TVIN_bias1, end_str());
}

// print in_qk Transactions
{
aesl_fh.write(AUTOTB_TVIN_in_qk, begin_str(AESL_transaction));
{
auto *pos = (unsigned char*)&__xlx_offset_byte_param_in_qk;
aesl_fh.write(AUTOTB_TVIN_in_qk, formatData(pos, 32));
}
  tcl_file.set_num(1, &tcl_file.in_qk_depth);
aesl_fh.write(AUTOTB_TVIN_in_qk, end_str());
}

// print in_q Transactions
{
aesl_fh.write(AUTOTB_TVIN_in_q, begin_str(AESL_transaction));
{
auto *pos = (unsigned char*)&__xlx_offset_byte_param_in_q;
aesl_fh.write(AUTOTB_TVIN_in_q, formatData(pos, 32));
}
  tcl_file.set_num(1, &tcl_file.in_q_depth);
aesl_fh.write(AUTOTB_TVIN_in_q, end_str());
}

// print in_k Transactions
{
aesl_fh.write(AUTOTB_TVIN_in_k, begin_str(AESL_transaction));
{
auto *pos = (unsigned char*)&__xlx_offset_byte_param_in_k;
aesl_fh.write(AUTOTB_TVIN_in_k, formatData(pos, 32));
}
  tcl_file.set_num(1, &tcl_file.in_k_depth);
aesl_fh.write(AUTOTB_TVIN_in_k, end_str());
}

// print afterQKMultiplication Transactions
{
aesl_fh.write(AUTOTB_TVIN_afterQKMultiplication, begin_str(AESL_transaction));
{
auto *pos = (unsigned char*)&__xlx_offset_byte_param_afterQKMultiplication;
aesl_fh.write(AUTOTB_TVIN_afterQKMultiplication, formatData(pos, 32));
}
  tcl_file.set_num(1, &tcl_file.afterQKMultiplication_depth);
aesl_fh.write(AUTOTB_TVIN_afterQKMultiplication, end_str());
}

// print afterSoftmax Transactions
{
aesl_fh.write(AUTOTB_TVIN_afterSoftmax, begin_str(AESL_transaction));
{
auto *pos = (unsigned char*)&__xlx_offset_byte_param_afterSoftmax;
aesl_fh.write(AUTOTB_TVIN_afterSoftmax, formatData(pos, 32));
}
  tcl_file.set_num(1, &tcl_file.afterSoftmax_depth);
aesl_fh.write(AUTOTB_TVIN_afterSoftmax, end_str());
}

// print afterRearrangeX2 Transactions
{
aesl_fh.write(AUTOTB_TVIN_afterRearrangeX2, begin_str(AESL_transaction));
{
auto *pos = (unsigned char*)&__xlx_offset_byte_param_afterRearrangeX2;
aesl_fh.write(AUTOTB_TVIN_afterRearrangeX2, formatData(pos, 32));
}
  tcl_file.set_num(1, &tcl_file.afterRearrangeX2_depth);
aesl_fh.write(AUTOTB_TVIN_afterRearrangeX2, end_str());
}

// print afterQKXMultiplication Transactions
{
aesl_fh.write(AUTOTB_TVIN_afterQKXMultiplication, begin_str(AESL_transaction));
{
auto *pos = (unsigned char*)&__xlx_offset_byte_param_afterQKXMultiplication;
aesl_fh.write(AUTOTB_TVIN_afterQKXMultiplication, formatData(pos, 32));
}
  tcl_file.set_num(1, &tcl_file.afterQKXMultiplication_depth);
aesl_fh.write(AUTOTB_TVIN_afterQKXMultiplication, end_str());
}

// print afterRearrangeQKX Transactions
{
aesl_fh.write(AUTOTB_TVIN_afterRearrangeQKX, begin_str(AESL_transaction));
{
auto *pos = (unsigned char*)&__xlx_offset_byte_param_afterRearrangeQKX;
aesl_fh.write(AUTOTB_TVIN_afterRearrangeQKX, formatData(pos, 32));
}
  tcl_file.set_num(1, &tcl_file.afterRearrangeQKX_depth);
aesl_fh.write(AUTOTB_TVIN_afterRearrangeQKX, end_str());
}

// print afterPad2 Transactions
{
aesl_fh.write(AUTOTB_TVIN_afterPad2, begin_str(AESL_transaction));
{
auto *pos = (unsigned char*)&__xlx_offset_byte_param_afterPad2;
aesl_fh.write(AUTOTB_TVIN_afterPad2, formatData(pos, 32));
}
  tcl_file.set_num(1, &tcl_file.afterPad2_depth);
aesl_fh.write(AUTOTB_TVIN_afterPad2, end_str());
}

// print afterConv2 Transactions
{
aesl_fh.write(AUTOTB_TVIN_afterConv2, begin_str(AESL_transaction));
{
auto *pos = (unsigned char*)&__xlx_offset_byte_param_afterConv2;
aesl_fh.write(AUTOTB_TVIN_afterConv2, formatData(pos, 32));
}
  tcl_file.set_num(1, &tcl_file.afterConv2_depth);
aesl_fh.write(AUTOTB_TVIN_afterConv2, end_str());
}

// print kernel2 Transactions
{
aesl_fh.write(AUTOTB_TVIN_kernel2, begin_str(AESL_transaction));
{
auto *pos = (unsigned char*)&__xlx_offset_byte_param_kernel2;
aesl_fh.write(AUTOTB_TVIN_kernel2, formatData(pos, 32));
}
  tcl_file.set_num(1, &tcl_file.kernel2_depth);
aesl_fh.write(AUTOTB_TVIN_kernel2, end_str());
}

// print bias2 Transactions
{
aesl_fh.write(AUTOTB_TVIN_bias2, begin_str(AESL_transaction));
{
auto *pos = (unsigned char*)&__xlx_offset_byte_param_bias2;
aesl_fh.write(AUTOTB_TVIN_bias2, formatData(pos, 32));
}
  tcl_file.set_num(1, &tcl_file.bias2_depth);
aesl_fh.write(AUTOTB_TVIN_bias2, end_str());
}

// print afterAct2 Transactions
{
aesl_fh.write(AUTOTB_TVIN_afterAct2, begin_str(AESL_transaction));
{
auto *pos = (unsigned char*)&__xlx_offset_byte_param_afterAct2;
aesl_fh.write(AUTOTB_TVIN_afterAct2, formatData(pos, 32));
}
  tcl_file.set_num(1, &tcl_file.afterAct2_depth);
aesl_fh.write(AUTOTB_TVIN_afterAct2, end_str());
}

// print QKV Transactions
{
aesl_fh.write(AUTOTB_TVIN_QKV, begin_str(AESL_transaction));
{
auto *pos = (unsigned char*)&__xlx_offset_byte_param_QKV;
aesl_fh.write(AUTOTB_TVIN_QKV, formatData(pos, 32));
}
  tcl_file.set_num(1, &tcl_file.QKV_depth);
aesl_fh.write(AUTOTB_TVIN_QKV, end_str());
}

// print buffer_out Transactions
{
aesl_fh.write(AUTOTB_TVIN_buffer_out, begin_str(AESL_transaction));
{
auto *pos = (unsigned char*)&__xlx_offset_byte_param_buffer_out;
aesl_fh.write(AUTOTB_TVIN_buffer_out, formatData(pos, 32));
}
  tcl_file.set_num(1, &tcl_file.buffer_out_depth);
aesl_fh.write(AUTOTB_TVIN_buffer_out, end_str());
}

// print buffer_result Transactions
{
aesl_fh.write(AUTOTB_TVIN_buffer_result, begin_str(AESL_transaction));
{
auto *pos = (unsigned char*)&__xlx_offset_byte_param_buffer_result;
aesl_fh.write(AUTOTB_TVIN_buffer_result, formatData(pos, 32));
}
  tcl_file.set_num(1, &tcl_file.buffer_result_depth);
aesl_fh.write(AUTOTB_TVIN_buffer_result, end_str());
}

CodeState = CALL_C_DUT;
kernel_attention_hw_stub_wrapper(__xlx_apatb_param_buffer_DataIn_1, __xlx_apatb_param_afterNorm, __xlx_apatb_param_norm1_mean, __xlx_apatb_param_norm1_var, __xlx_apatb_param_norm1_weight, __xlx_apatb_param_norm1_bias, __xlx_apatb_param_afterPad, __xlx_apatb_param_afterRearrangeX, __xlx_apatb_param_afterPad1, __xlx_apatb_param_afterConv1, __xlx_apatb_param_kernel1, __xlx_apatb_param_bias1, __xlx_apatb_param_in_qk, __xlx_apatb_param_in_q, __xlx_apatb_param_in_k, __xlx_apatb_param_afterQKMultiplication, __xlx_apatb_param_afterSoftmax, __xlx_apatb_param_afterRearrangeX2, __xlx_apatb_param_afterQKXMultiplication, __xlx_apatb_param_afterRearrangeQKX, __xlx_apatb_param_afterPad2, __xlx_apatb_param_afterConv2, __xlx_apatb_param_kernel2, __xlx_apatb_param_bias2, __xlx_apatb_param_afterAct2, __xlx_apatb_param_QKV, __xlx_apatb_param_buffer_out, __xlx_apatb_param_buffer_result);
CodeState = DUMP_OUTPUTS;
#ifdef USE_BINARY_TV_FILE
{
aesl_fh.touch(AUTOTB_TVOUT_gmem, 'b');
transaction<32> tr(501552);
__xlx_offset_byte_param_norm1_mean = 0*4;
if (__xlx_apatb_param_norm1_mean) {
  tr.import<4>((char*)__xlx_apatb_param_norm1_mean, 80, 0);
}
__xlx_offset_byte_param_norm1_var = 80*4;
if (__xlx_apatb_param_norm1_var) {
  tr.import<4>((char*)__xlx_apatb_param_norm1_var, 80, 0);
}
__xlx_offset_byte_param_norm1_weight = 160*4;
if (__xlx_apatb_param_norm1_weight) {
  tr.import<4>((char*)__xlx_apatb_param_norm1_weight, 80, 0);
}
__xlx_offset_byte_param_norm1_bias = 240*4;
if (__xlx_apatb_param_norm1_bias) {
  tr.import<4>((char*)__xlx_apatb_param_norm1_bias, 80, 0);
}
__xlx_offset_byte_param_afterPad = 320*4;
if (__xlx_apatb_param_afterPad) {
  tr.import<4>((char*)__xlx_apatb_param_afterPad, 15680, 0);
}
__xlx_offset_byte_param_afterRearrangeX = 16000*4;
if (__xlx_apatb_param_afterRearrangeX) {
  tr.import<4>((char*)__xlx_apatb_param_afterRearrangeX, 15680, 0);
}
__xlx_offset_byte_param_afterPad1 = 31680*4;
if (__xlx_apatb_param_afterPad1) {
  tr.import<4>((char*)__xlx_apatb_param_afterPad1, 15680, 0);
}
__xlx_offset_byte_param_afterConv1 = 47360*4;
if (__xlx_apatb_param_afterConv1) {
  tr.import<4>((char*)__xlx_apatb_param_afterConv1, 31360, 0);
}
__xlx_offset_byte_param_kernel1 = 78720*4;
if (__xlx_apatb_param_kernel1) {
  tr.import<4>((char*)__xlx_apatb_param_kernel1, 12800, 0);
}
__xlx_offset_byte_param_bias1 = 91520*4;
if (__xlx_apatb_param_bias1) {
  tr.import<4>((char*)__xlx_apatb_param_bias1, 160, 0);
}
__xlx_offset_byte_param_in_qk = 91680*4;
if (__xlx_apatb_param_in_qk) {
  tr.import<4>((char*)__xlx_apatb_param_in_qk, 31360, 0);
}
__xlx_offset_byte_param_in_q = 123040*4;
if (__xlx_apatb_param_in_q) {
  tr.import<4>((char*)__xlx_apatb_param_in_q, 15680, 0);
}
__xlx_offset_byte_param_in_k = 138720*4;
if (__xlx_apatb_param_in_k) {
  tr.import<4>((char*)__xlx_apatb_param_in_k, 15680, 0);
}
__xlx_offset_byte_param_afterQKMultiplication = 154400*4;
if (__xlx_apatb_param_afterQKMultiplication) {
  tr.import<4>((char*)__xlx_apatb_param_afterQKMultiplication, 38416, 0);
}
__xlx_offset_byte_param_afterSoftmax = 192816*4;
if (__xlx_apatb_param_afterSoftmax) {
  tr.import<4>((char*)__xlx_apatb_param_afterSoftmax, 38416, 0);
}
__xlx_offset_byte_param_afterRearrangeX2 = 231232*4;
if (__xlx_apatb_param_afterRearrangeX2) {
  tr.import<4>((char*)__xlx_apatb_param_afterRearrangeX2, 15680, 0);
}
__xlx_offset_byte_param_afterQKXMultiplication = 246912*4;
if (__xlx_apatb_param_afterQKXMultiplication) {
  tr.import<4>((char*)__xlx_apatb_param_afterQKXMultiplication, 15680, 0);
}
__xlx_offset_byte_param_afterRearrangeQKX = 262592*4;
if (__xlx_apatb_param_afterRearrangeQKX) {
  tr.import<4>((char*)__xlx_apatb_param_afterRearrangeQKX, 15680, 0);
}
__xlx_offset_byte_param_afterPad2 = 278272*4;
if (__xlx_apatb_param_afterPad2) {
  tr.import<4>((char*)__xlx_apatb_param_afterPad2, 15680, 0);
}
__xlx_offset_byte_param_afterConv2 = 293952*4;
if (__xlx_apatb_param_afterConv2) {
  tr.import<4>((char*)__xlx_apatb_param_afterConv2, 47040, 0);
}
__xlx_offset_byte_param_kernel2 = 340992*4;
if (__xlx_apatb_param_kernel2) {
  tr.import<4>((char*)__xlx_apatb_param_kernel2, 19200, 0);
}
__xlx_offset_byte_param_bias2 = 360192*4;
if (__xlx_apatb_param_bias2) {
  tr.import<4>((char*)__xlx_apatb_param_bias2, 240, 0);
}
__xlx_offset_byte_param_afterAct2 = 360432*4;
if (__xlx_apatb_param_afterAct2) {
  tr.import<4>((char*)__xlx_apatb_param_afterAct2, 47040, 0);
}
__xlx_offset_byte_param_QKV = 407472*4;
if (__xlx_apatb_param_QKV) {
  tr.import<4>((char*)__xlx_apatb_param_QKV, 47040, 0);
}
__xlx_offset_byte_param_buffer_out = 454512*4;
if (__xlx_apatb_param_buffer_out) {
  tr.import<4>((char*)__xlx_apatb_param_buffer_out, 47040, 0);
}
aesl_fh.write(AUTOTB_TVOUT_gmem, tr.p, tr.tbytes);
tcl_file.set_num(501552, &tcl_file.gmem_depth);
}
#else
aesl_fh.touch(AUTOTB_TVOUT_gmem);
{
aesl_fh.write(AUTOTB_TVOUT_gmem, begin_str(AESL_transaction));
__xlx_offset_byte_param_norm1_mean = 0*4;
if (__xlx_apatb_param_norm1_mean) {
for (size_t i = 0; i < 80; ++i) {
unsigned char *pos = (unsigned char*)__xlx_apatb_param_norm1_mean + i * 4;
std::string s = formatData(pos, 32);
aesl_fh.write(AUTOTB_TVOUT_gmem, s);
}
}
__xlx_offset_byte_param_norm1_var = 80*4;
if (__xlx_apatb_param_norm1_var) {
for (size_t i = 0; i < 80; ++i) {
unsigned char *pos = (unsigned char*)__xlx_apatb_param_norm1_var + i * 4;
std::string s = formatData(pos, 32);
aesl_fh.write(AUTOTB_TVOUT_gmem, s);
}
}
__xlx_offset_byte_param_norm1_weight = 160*4;
if (__xlx_apatb_param_norm1_weight) {
for (size_t i = 0; i < 80; ++i) {
unsigned char *pos = (unsigned char*)__xlx_apatb_param_norm1_weight + i * 4;
std::string s = formatData(pos, 32);
aesl_fh.write(AUTOTB_TVOUT_gmem, s);
}
}
__xlx_offset_byte_param_norm1_bias = 240*4;
if (__xlx_apatb_param_norm1_bias) {
for (size_t i = 0; i < 80; ++i) {
unsigned char *pos = (unsigned char*)__xlx_apatb_param_norm1_bias + i * 4;
std::string s = formatData(pos, 32);
aesl_fh.write(AUTOTB_TVOUT_gmem, s);
}
}
__xlx_offset_byte_param_afterPad = 320*4;
if (__xlx_apatb_param_afterPad) {
for (size_t i = 0; i < 15680; ++i) {
unsigned char *pos = (unsigned char*)__xlx_apatb_param_afterPad + i * 4;
std::string s = formatData(pos, 32);
aesl_fh.write(AUTOTB_TVOUT_gmem, s);
}
}
__xlx_offset_byte_param_afterRearrangeX = 16000*4;
if (__xlx_apatb_param_afterRearrangeX) {
for (size_t i = 0; i < 15680; ++i) {
unsigned char *pos = (unsigned char*)__xlx_apatb_param_afterRearrangeX + i * 4;
std::string s = formatData(pos, 32);
aesl_fh.write(AUTOTB_TVOUT_gmem, s);
}
}
__xlx_offset_byte_param_afterPad1 = 31680*4;
if (__xlx_apatb_param_afterPad1) {
for (size_t i = 0; i < 15680; ++i) {
unsigned char *pos = (unsigned char*)__xlx_apatb_param_afterPad1 + i * 4;
std::string s = formatData(pos, 32);
aesl_fh.write(AUTOTB_TVOUT_gmem, s);
}
}
__xlx_offset_byte_param_afterConv1 = 47360*4;
if (__xlx_apatb_param_afterConv1) {
for (size_t i = 0; i < 31360; ++i) {
unsigned char *pos = (unsigned char*)__xlx_apatb_param_afterConv1 + i * 4;
std::string s = formatData(pos, 32);
aesl_fh.write(AUTOTB_TVOUT_gmem, s);
}
}
__xlx_offset_byte_param_kernel1 = 78720*4;
if (__xlx_apatb_param_kernel1) {
for (size_t i = 0; i < 12800; ++i) {
unsigned char *pos = (unsigned char*)__xlx_apatb_param_kernel1 + i * 4;
std::string s = formatData(pos, 32);
aesl_fh.write(AUTOTB_TVOUT_gmem, s);
}
}
__xlx_offset_byte_param_bias1 = 91520*4;
if (__xlx_apatb_param_bias1) {
for (size_t i = 0; i < 160; ++i) {
unsigned char *pos = (unsigned char*)__xlx_apatb_param_bias1 + i * 4;
std::string s = formatData(pos, 32);
aesl_fh.write(AUTOTB_TVOUT_gmem, s);
}
}
__xlx_offset_byte_param_in_qk = 91680*4;
if (__xlx_apatb_param_in_qk) {
for (size_t i = 0; i < 31360; ++i) {
unsigned char *pos = (unsigned char*)__xlx_apatb_param_in_qk + i * 4;
std::string s = formatData(pos, 32);
aesl_fh.write(AUTOTB_TVOUT_gmem, s);
}
}
__xlx_offset_byte_param_in_q = 123040*4;
if (__xlx_apatb_param_in_q) {
for (size_t i = 0; i < 15680; ++i) {
unsigned char *pos = (unsigned char*)__xlx_apatb_param_in_q + i * 4;
std::string s = formatData(pos, 32);
aesl_fh.write(AUTOTB_TVOUT_gmem, s);
}
}
__xlx_offset_byte_param_in_k = 138720*4;
if (__xlx_apatb_param_in_k) {
for (size_t i = 0; i < 15680; ++i) {
unsigned char *pos = (unsigned char*)__xlx_apatb_param_in_k + i * 4;
std::string s = formatData(pos, 32);
aesl_fh.write(AUTOTB_TVOUT_gmem, s);
}
}
__xlx_offset_byte_param_afterQKMultiplication = 154400*4;
if (__xlx_apatb_param_afterQKMultiplication) {
for (size_t i = 0; i < 38416; ++i) {
unsigned char *pos = (unsigned char*)__xlx_apatb_param_afterQKMultiplication + i * 4;
std::string s = formatData(pos, 32);
aesl_fh.write(AUTOTB_TVOUT_gmem, s);
}
}
__xlx_offset_byte_param_afterSoftmax = 192816*4;
if (__xlx_apatb_param_afterSoftmax) {
for (size_t i = 0; i < 38416; ++i) {
unsigned char *pos = (unsigned char*)__xlx_apatb_param_afterSoftmax + i * 4;
std::string s = formatData(pos, 32);
aesl_fh.write(AUTOTB_TVOUT_gmem, s);
}
}
__xlx_offset_byte_param_afterRearrangeX2 = 231232*4;
if (__xlx_apatb_param_afterRearrangeX2) {
for (size_t i = 0; i < 15680; ++i) {
unsigned char *pos = (unsigned char*)__xlx_apatb_param_afterRearrangeX2 + i * 4;
std::string s = formatData(pos, 32);
aesl_fh.write(AUTOTB_TVOUT_gmem, s);
}
}
__xlx_offset_byte_param_afterQKXMultiplication = 246912*4;
if (__xlx_apatb_param_afterQKXMultiplication) {
for (size_t i = 0; i < 15680; ++i) {
unsigned char *pos = (unsigned char*)__xlx_apatb_param_afterQKXMultiplication + i * 4;
std::string s = formatData(pos, 32);
aesl_fh.write(AUTOTB_TVOUT_gmem, s);
}
}
__xlx_offset_byte_param_afterRearrangeQKX = 262592*4;
if (__xlx_apatb_param_afterRearrangeQKX) {
for (size_t i = 0; i < 15680; ++i) {
unsigned char *pos = (unsigned char*)__xlx_apatb_param_afterRearrangeQKX + i * 4;
std::string s = formatData(pos, 32);
aesl_fh.write(AUTOTB_TVOUT_gmem, s);
}
}
__xlx_offset_byte_param_afterPad2 = 278272*4;
if (__xlx_apatb_param_afterPad2) {
for (size_t i = 0; i < 15680; ++i) {
unsigned char *pos = (unsigned char*)__xlx_apatb_param_afterPad2 + i * 4;
std::string s = formatData(pos, 32);
aesl_fh.write(AUTOTB_TVOUT_gmem, s);
}
}
__xlx_offset_byte_param_afterConv2 = 293952*4;
if (__xlx_apatb_param_afterConv2) {
for (size_t i = 0; i < 47040; ++i) {
unsigned char *pos = (unsigned char*)__xlx_apatb_param_afterConv2 + i * 4;
std::string s = formatData(pos, 32);
aesl_fh.write(AUTOTB_TVOUT_gmem, s);
}
}
__xlx_offset_byte_param_kernel2 = 340992*4;
if (__xlx_apatb_param_kernel2) {
for (size_t i = 0; i < 19200; ++i) {
unsigned char *pos = (unsigned char*)__xlx_apatb_param_kernel2 + i * 4;
std::string s = formatData(pos, 32);
aesl_fh.write(AUTOTB_TVOUT_gmem, s);
}
}
__xlx_offset_byte_param_bias2 = 360192*4;
if (__xlx_apatb_param_bias2) {
for (size_t i = 0; i < 240; ++i) {
unsigned char *pos = (unsigned char*)__xlx_apatb_param_bias2 + i * 4;
std::string s = formatData(pos, 32);
aesl_fh.write(AUTOTB_TVOUT_gmem, s);
}
}
__xlx_offset_byte_param_afterAct2 = 360432*4;
if (__xlx_apatb_param_afterAct2) {
for (size_t i = 0; i < 47040; ++i) {
unsigned char *pos = (unsigned char*)__xlx_apatb_param_afterAct2 + i * 4;
std::string s = formatData(pos, 32);
aesl_fh.write(AUTOTB_TVOUT_gmem, s);
}
}
__xlx_offset_byte_param_QKV = 407472*4;
if (__xlx_apatb_param_QKV) {
for (size_t i = 0; i < 47040; ++i) {
unsigned char *pos = (unsigned char*)__xlx_apatb_param_QKV + i * 4;
std::string s = formatData(pos, 32);
aesl_fh.write(AUTOTB_TVOUT_gmem, s);
}
}
__xlx_offset_byte_param_buffer_out = 454512*4;
if (__xlx_apatb_param_buffer_out) {
for (size_t i = 0; i < 47040; ++i) {
unsigned char *pos = (unsigned char*)__xlx_apatb_param_buffer_out + i * 4;
std::string s = formatData(pos, 32);
aesl_fh.write(AUTOTB_TVOUT_gmem, s);
}
}
tcl_file.set_num(501552, &tcl_file.gmem_depth);
aesl_fh.write(AUTOTB_TVOUT_gmem, end_str());
}
#endif
#ifdef USE_BINARY_TV_FILE
{
aesl_fh.touch(AUTOTB_TVOUT_gmem0, 'b');
transaction<32> tr(62720);
__xlx_offset_byte_param_buffer_DataIn_1 = 0*4;
if (__xlx_apatb_param_buffer_DataIn_1) {
  tr.import<4>((char*)__xlx_apatb_param_buffer_DataIn_1, 15680, 0);
}
__xlx_offset_byte_param_buffer_result = 15680*4;
if (__xlx_apatb_param_buffer_result) {
  tr.import<4>((char*)__xlx_apatb_param_buffer_result, 47040, 0);
}
aesl_fh.write(AUTOTB_TVOUT_gmem0, tr.p, tr.tbytes);
tcl_file.set_num(62720, &tcl_file.gmem0_depth);
}
#else
aesl_fh.touch(AUTOTB_TVOUT_gmem0);
{
aesl_fh.write(AUTOTB_TVOUT_gmem0, begin_str(AESL_transaction));
__xlx_offset_byte_param_buffer_DataIn_1 = 0*4;
if (__xlx_apatb_param_buffer_DataIn_1) {
for (size_t i = 0; i < 15680; ++i) {
unsigned char *pos = (unsigned char*)__xlx_apatb_param_buffer_DataIn_1 + i * 4;
std::string s = formatData(pos, 32);
aesl_fh.write(AUTOTB_TVOUT_gmem0, s);
}
}
__xlx_offset_byte_param_buffer_result = 15680*4;
if (__xlx_apatb_param_buffer_result) {
for (size_t i = 0; i < 47040; ++i) {
unsigned char *pos = (unsigned char*)__xlx_apatb_param_buffer_result + i * 4;
std::string s = formatData(pos, 32);
aesl_fh.write(AUTOTB_TVOUT_gmem0, s);
}
}
tcl_file.set_num(62720, &tcl_file.gmem0_depth);
aesl_fh.write(AUTOTB_TVOUT_gmem0, end_str());
}
#endif
#ifdef USE_BINARY_TV_FILE
{
aesl_fh.touch(AUTOTB_TVOUT_gmem1, 'b');
transaction<32> tr(15680);
__xlx_offset_byte_param_afterNorm = 0*4;
if (__xlx_apatb_param_afterNorm) {
  tr.import<4>((char*)__xlx_apatb_param_afterNorm, 15680, 0);
}
aesl_fh.write(AUTOTB_TVOUT_gmem1, tr.p, tr.tbytes);
tcl_file.set_num(15680, &tcl_file.gmem1_depth);
}
#else
aesl_fh.touch(AUTOTB_TVOUT_gmem1);
{
aesl_fh.write(AUTOTB_TVOUT_gmem1, begin_str(AESL_transaction));
__xlx_offset_byte_param_afterNorm = 0*4;
if (__xlx_apatb_param_afterNorm) {
for (size_t i = 0; i < 15680; ++i) {
unsigned char *pos = (unsigned char*)__xlx_apatb_param_afterNorm + i * 4;
std::string s = formatData(pos, 32);
aesl_fh.write(AUTOTB_TVOUT_gmem1, s);
}
}
tcl_file.set_num(15680, &tcl_file.gmem1_depth);
aesl_fh.write(AUTOTB_TVOUT_gmem1, end_str());
}
#endif
CodeState = DELETE_CHAR_BUFFERS;
AESL_transaction++;
tcl_file.set_num(AESL_transaction , &tcl_file.trans_num);
}
