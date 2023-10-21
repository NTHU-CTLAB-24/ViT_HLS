#include <systemc>
#include <list>
#include <map>
#include <vector>
#include <iostream>
#include "hls_stream.h"
#include "ap_int.h"
#include "ap_fixed.h"
using namespace std;
using namespace sc_dt;

namespace bcsim
{
  struct Buffer {
    char *first;
    Buffer(char *addr) : first(addr)
    {
    }
  };

  struct DBuffer : public Buffer {
    size_t ufree;

    DBuffer(size_t usize) : Buffer(nullptr), ufree(1<<10)
    {
      first = new char[usize*ufree];
    }

    ~DBuffer()
    {
      delete[] first;
    }
  };

  struct CStream {
    char *front;
    char *back;
    size_t num;
    size_t usize;
    std::list<Buffer*> bufs;
    bool dynamic;

    CStream() : front(nullptr), back(nullptr),
                num(0), usize(0), dynamic(true)
    {
    }

    ~CStream()
    {
      for (Buffer *p : bufs) {
        delete p;
      }
    }

    template<typename T>
    T* data()
    {
      return (T*)front;
    }

    template<typename T>
    void transfer(hls::stream<T> *param)
    {
      while (!empty()) {
        param->write(*(T*)nextRead());
      }
    }

    bool empty();
    char* nextRead();
    char* nextWrite();
  };

  bool CStream::empty()
  {
    return num == 0;
  }

  char* CStream::nextRead()
  {
    assert(num > 0);
    char *res = front;
    front += usize;
    --num;
    return res;
  }

  char* CStream::nextWrite()
  {
    if (dynamic) {
      if (static_cast<DBuffer*>(bufs.back())->ufree == 0) {
        bufs.push_back(new DBuffer(usize));
        back = bufs.back()->first;
      }
      --static_cast<DBuffer*>(bufs.back())->ufree;
    }
    char *res = back;
    back += usize;
    ++num;
    return res;
  }

  std::list<CStream> streams;
  std::map<char*, CStream*> prebuilt;

  CStream* createStream(size_t usize)
  {
    streams.emplace_front();
    CStream &s = streams.front();
    {
      s.dynamic = true;
      s.bufs.push_back(new DBuffer(usize));
      s.front = s.bufs.back()->first;
      s.back = s.front;
      s.num = 0;
      s.usize = usize;
    }
    return &s;
  }

  template<typename T>
  CStream* createStream(hls::stream<T> *param)
  {
    CStream *s = createStream(sizeof(T));
    {
      s->dynamic = true;
      while (!param->empty()) {
        T data = param->read();
        memcpy(s->nextWrite(), (char*)&data, sizeof(T));
      }
      prebuilt[s->front] = s;
    }
    return s;
  }

  template<typename T>
  CStream* createStream(T *param, size_t usize)
  {
    streams.emplace_front();
    CStream &s = streams.front();
    {
      s.dynamic = false;
      s.bufs.push_back(new Buffer((char*)param));
      s.front = s.back = s.bufs.back()->first;
      s.usize = usize;
      s.num = ~0UL;
    }
    prebuilt[s.front] = &s;
    return &s;
  }

  CStream* findStream(char *buf)
  {
    return prebuilt.at(buf);
  }
}
class AESL_RUNTIME_BC {
  public:
    AESL_RUNTIME_BC(const char* name) {
      file_token.open( name);
      if (!file_token.good()) {
        cout << "Failed to open tv file " << name << endl;
        exit (1);
      }
      file_token >> mName;//[[[runtime]]]
    }
    ~AESL_RUNTIME_BC() {
      file_token.close();
    }
    int read_size () {
      int size = 0;
      file_token >> mName;//[[transaction]]
      file_token >> mName;//transaction number
      file_token >> mName;//pop_size
      size = atoi(mName.c_str());
      file_token >> mName;//[[/transaction]]
      return size;
    }
  public:
    fstream file_token;
    string mName;
};
extern "C" void kernel_attention(int*, int*, int*, int, int, int, int, int, int, int, int, int, int, int, int, int, int, int, int, int, int, int, int, int, int, int, int, int, int, int, int);
extern "C" void apatb_kernel_attention_hw(volatile void * __xlx_apatb_param_buffer_DataIn_1, volatile void * __xlx_apatb_param_afterNorm, volatile void * __xlx_apatb_param_norm1_mean, volatile void * __xlx_apatb_param_norm1_var, volatile void * __xlx_apatb_param_norm1_weight, volatile void * __xlx_apatb_param_norm1_bias, volatile void * __xlx_apatb_param_afterPad, volatile void * __xlx_apatb_param_afterRearrangeX, volatile void * __xlx_apatb_param_afterPad1, volatile void * __xlx_apatb_param_afterConv1, volatile void * __xlx_apatb_param_kernel1, volatile void * __xlx_apatb_param_bias1, volatile void * __xlx_apatb_param_in_qk, volatile void * __xlx_apatb_param_in_q, volatile void * __xlx_apatb_param_in_k, volatile void * __xlx_apatb_param_afterQKMultiplication, volatile void * __xlx_apatb_param_afterSoftmax, volatile void * __xlx_apatb_param_afterRearrangeX2, volatile void * __xlx_apatb_param_afterQKXMultiplication, volatile void * __xlx_apatb_param_afterRearrangeQKX, volatile void * __xlx_apatb_param_afterPad2, volatile void * __xlx_apatb_param_afterConv2, volatile void * __xlx_apatb_param_kernel2, volatile void * __xlx_apatb_param_bias2, volatile void * __xlx_apatb_param_afterAct2, volatile void * __xlx_apatb_param_QKV, volatile void * __xlx_apatb_param_buffer_out, volatile void * __xlx_apatb_param_buffer_result) {
  // Collect __xlx_buffer_DataIn_1_buffer_result__tmp_vec
  vector<sc_bv<32> >__xlx_buffer_DataIn_1_buffer_result__tmp_vec;
  for (int j = 0, e = 15680; j != e; ++j) {
    sc_bv<32> _xlx_tmp_sc;
    _xlx_tmp_sc.range(7, 0) = ((char*)__xlx_apatb_param_buffer_DataIn_1)[j*4+0];
    _xlx_tmp_sc.range(15, 8) = ((char*)__xlx_apatb_param_buffer_DataIn_1)[j*4+1];
    _xlx_tmp_sc.range(23, 16) = ((char*)__xlx_apatb_param_buffer_DataIn_1)[j*4+2];
    _xlx_tmp_sc.range(31, 24) = ((char*)__xlx_apatb_param_buffer_DataIn_1)[j*4+3];
    __xlx_buffer_DataIn_1_buffer_result__tmp_vec.push_back(_xlx_tmp_sc);
  }
  int __xlx_size_param_buffer_DataIn_1 = 15680;
  int __xlx_offset_param_buffer_DataIn_1 = 0;
  int __xlx_offset_byte_param_buffer_DataIn_1 = 0*4;
  for (int j = 0, e = 47040; j != e; ++j) {
    sc_bv<32> _xlx_tmp_sc;
    _xlx_tmp_sc.range(7, 0) = ((char*)__xlx_apatb_param_buffer_result)[j*4+0];
    _xlx_tmp_sc.range(15, 8) = ((char*)__xlx_apatb_param_buffer_result)[j*4+1];
    _xlx_tmp_sc.range(23, 16) = ((char*)__xlx_apatb_param_buffer_result)[j*4+2];
    _xlx_tmp_sc.range(31, 24) = ((char*)__xlx_apatb_param_buffer_result)[j*4+3];
    __xlx_buffer_DataIn_1_buffer_result__tmp_vec.push_back(_xlx_tmp_sc);
  }
  int __xlx_size_param_buffer_result = 47040;
  int __xlx_offset_param_buffer_result = 15680;
  int __xlx_offset_byte_param_buffer_result = 15680*4;
  int* __xlx_buffer_DataIn_1_buffer_result__input_buffer= new int[__xlx_buffer_DataIn_1_buffer_result__tmp_vec.size()];
  for (int i = 0; i < __xlx_buffer_DataIn_1_buffer_result__tmp_vec.size(); ++i) {
    __xlx_buffer_DataIn_1_buffer_result__input_buffer[i] = __xlx_buffer_DataIn_1_buffer_result__tmp_vec[i].range(31, 0).to_uint64();
  }
  // Collect __xlx_afterNorm__tmp_vec
  vector<sc_bv<32> >__xlx_afterNorm__tmp_vec;
  for (int j = 0, e = 15680; j != e; ++j) {
    sc_bv<32> _xlx_tmp_sc;
    _xlx_tmp_sc.range(7, 0) = ((char*)__xlx_apatb_param_afterNorm)[j*4+0];
    _xlx_tmp_sc.range(15, 8) = ((char*)__xlx_apatb_param_afterNorm)[j*4+1];
    _xlx_tmp_sc.range(23, 16) = ((char*)__xlx_apatb_param_afterNorm)[j*4+2];
    _xlx_tmp_sc.range(31, 24) = ((char*)__xlx_apatb_param_afterNorm)[j*4+3];
    __xlx_afterNorm__tmp_vec.push_back(_xlx_tmp_sc);
  }
  int __xlx_size_param_afterNorm = 15680;
  int __xlx_offset_param_afterNorm = 0;
  int __xlx_offset_byte_param_afterNorm = 0*4;
  int* __xlx_afterNorm__input_buffer= new int[__xlx_afterNorm__tmp_vec.size()];
  for (int i = 0; i < __xlx_afterNorm__tmp_vec.size(); ++i) {
    __xlx_afterNorm__input_buffer[i] = __xlx_afterNorm__tmp_vec[i].range(31, 0).to_uint64();
  }
  // Collect __xlx_norm1_mean_norm1_var_norm1_weight_norm1_bias_afterPad_afterRearrangeX_afterPad1_afterConv1_kernel1_bias1_in_qk_in_q_in_k_afterQKMultiplication_afterSoftmax_afterRearrangeX2_afterQKXMultiplication_afterRearrangeQKX_afterPad2_afterConv2_kernel2_bias2_afterAct2_QKV_buffer_out__tmp_vec
  vector<sc_bv<32> >__xlx_norm1_mean_norm1_var_norm1_weight_norm1_bias_afterPad_afterRearrangeX_afterPad1_afterConv1_kernel1_bias1_in_qk_in_q_in_k_afterQKMultiplication_afterSoftmax_afterRearrangeX2_afterQKXMultiplication_afterRearrangeQKX_afterPad2_afterConv2_kernel2_bias2_afterAct2_QKV_buffer_out__tmp_vec;
  for (int j = 0, e = 80; j != e; ++j) {
    sc_bv<32> _xlx_tmp_sc;
    _xlx_tmp_sc.range(7, 0) = ((char*)__xlx_apatb_param_norm1_mean)[j*4+0];
    _xlx_tmp_sc.range(15, 8) = ((char*)__xlx_apatb_param_norm1_mean)[j*4+1];
    _xlx_tmp_sc.range(23, 16) = ((char*)__xlx_apatb_param_norm1_mean)[j*4+2];
    _xlx_tmp_sc.range(31, 24) = ((char*)__xlx_apatb_param_norm1_mean)[j*4+3];
    __xlx_norm1_mean_norm1_var_norm1_weight_norm1_bias_afterPad_afterRearrangeX_afterPad1_afterConv1_kernel1_bias1_in_qk_in_q_in_k_afterQKMultiplication_afterSoftmax_afterRearrangeX2_afterQKXMultiplication_afterRearrangeQKX_afterPad2_afterConv2_kernel2_bias2_afterAct2_QKV_buffer_out__tmp_vec.push_back(_xlx_tmp_sc);
  }
  int __xlx_size_param_norm1_mean = 80;
  int __xlx_offset_param_norm1_mean = 0;
  int __xlx_offset_byte_param_norm1_mean = 0*4;
  for (int j = 0, e = 80; j != e; ++j) {
    sc_bv<32> _xlx_tmp_sc;
    _xlx_tmp_sc.range(7, 0) = ((char*)__xlx_apatb_param_norm1_var)[j*4+0];
    _xlx_tmp_sc.range(15, 8) = ((char*)__xlx_apatb_param_norm1_var)[j*4+1];
    _xlx_tmp_sc.range(23, 16) = ((char*)__xlx_apatb_param_norm1_var)[j*4+2];
    _xlx_tmp_sc.range(31, 24) = ((char*)__xlx_apatb_param_norm1_var)[j*4+3];
    __xlx_norm1_mean_norm1_var_norm1_weight_norm1_bias_afterPad_afterRearrangeX_afterPad1_afterConv1_kernel1_bias1_in_qk_in_q_in_k_afterQKMultiplication_afterSoftmax_afterRearrangeX2_afterQKXMultiplication_afterRearrangeQKX_afterPad2_afterConv2_kernel2_bias2_afterAct2_QKV_buffer_out__tmp_vec.push_back(_xlx_tmp_sc);
  }
  int __xlx_size_param_norm1_var = 80;
  int __xlx_offset_param_norm1_var = 80;
  int __xlx_offset_byte_param_norm1_var = 80*4;
  for (int j = 0, e = 80; j != e; ++j) {
    sc_bv<32> _xlx_tmp_sc;
    _xlx_tmp_sc.range(7, 0) = ((char*)__xlx_apatb_param_norm1_weight)[j*4+0];
    _xlx_tmp_sc.range(15, 8) = ((char*)__xlx_apatb_param_norm1_weight)[j*4+1];
    _xlx_tmp_sc.range(23, 16) = ((char*)__xlx_apatb_param_norm1_weight)[j*4+2];
    _xlx_tmp_sc.range(31, 24) = ((char*)__xlx_apatb_param_norm1_weight)[j*4+3];
    __xlx_norm1_mean_norm1_var_norm1_weight_norm1_bias_afterPad_afterRearrangeX_afterPad1_afterConv1_kernel1_bias1_in_qk_in_q_in_k_afterQKMultiplication_afterSoftmax_afterRearrangeX2_afterQKXMultiplication_afterRearrangeQKX_afterPad2_afterConv2_kernel2_bias2_afterAct2_QKV_buffer_out__tmp_vec.push_back(_xlx_tmp_sc);
  }
  int __xlx_size_param_norm1_weight = 80;
  int __xlx_offset_param_norm1_weight = 160;
  int __xlx_offset_byte_param_norm1_weight = 160*4;
  for (int j = 0, e = 80; j != e; ++j) {
    sc_bv<32> _xlx_tmp_sc;
    _xlx_tmp_sc.range(7, 0) = ((char*)__xlx_apatb_param_norm1_bias)[j*4+0];
    _xlx_tmp_sc.range(15, 8) = ((char*)__xlx_apatb_param_norm1_bias)[j*4+1];
    _xlx_tmp_sc.range(23, 16) = ((char*)__xlx_apatb_param_norm1_bias)[j*4+2];
    _xlx_tmp_sc.range(31, 24) = ((char*)__xlx_apatb_param_norm1_bias)[j*4+3];
    __xlx_norm1_mean_norm1_var_norm1_weight_norm1_bias_afterPad_afterRearrangeX_afterPad1_afterConv1_kernel1_bias1_in_qk_in_q_in_k_afterQKMultiplication_afterSoftmax_afterRearrangeX2_afterQKXMultiplication_afterRearrangeQKX_afterPad2_afterConv2_kernel2_bias2_afterAct2_QKV_buffer_out__tmp_vec.push_back(_xlx_tmp_sc);
  }
  int __xlx_size_param_norm1_bias = 80;
  int __xlx_offset_param_norm1_bias = 240;
  int __xlx_offset_byte_param_norm1_bias = 240*4;
  for (int j = 0, e = 15680; j != e; ++j) {
    sc_bv<32> _xlx_tmp_sc;
    _xlx_tmp_sc.range(7, 0) = ((char*)__xlx_apatb_param_afterPad)[j*4+0];
    _xlx_tmp_sc.range(15, 8) = ((char*)__xlx_apatb_param_afterPad)[j*4+1];
    _xlx_tmp_sc.range(23, 16) = ((char*)__xlx_apatb_param_afterPad)[j*4+2];
    _xlx_tmp_sc.range(31, 24) = ((char*)__xlx_apatb_param_afterPad)[j*4+3];
    __xlx_norm1_mean_norm1_var_norm1_weight_norm1_bias_afterPad_afterRearrangeX_afterPad1_afterConv1_kernel1_bias1_in_qk_in_q_in_k_afterQKMultiplication_afterSoftmax_afterRearrangeX2_afterQKXMultiplication_afterRearrangeQKX_afterPad2_afterConv2_kernel2_bias2_afterAct2_QKV_buffer_out__tmp_vec.push_back(_xlx_tmp_sc);
  }
  int __xlx_size_param_afterPad = 15680;
  int __xlx_offset_param_afterPad = 320;
  int __xlx_offset_byte_param_afterPad = 320*4;
  for (int j = 0, e = 15680; j != e; ++j) {
    sc_bv<32> _xlx_tmp_sc;
    _xlx_tmp_sc.range(7, 0) = ((char*)__xlx_apatb_param_afterRearrangeX)[j*4+0];
    _xlx_tmp_sc.range(15, 8) = ((char*)__xlx_apatb_param_afterRearrangeX)[j*4+1];
    _xlx_tmp_sc.range(23, 16) = ((char*)__xlx_apatb_param_afterRearrangeX)[j*4+2];
    _xlx_tmp_sc.range(31, 24) = ((char*)__xlx_apatb_param_afterRearrangeX)[j*4+3];
    __xlx_norm1_mean_norm1_var_norm1_weight_norm1_bias_afterPad_afterRearrangeX_afterPad1_afterConv1_kernel1_bias1_in_qk_in_q_in_k_afterQKMultiplication_afterSoftmax_afterRearrangeX2_afterQKXMultiplication_afterRearrangeQKX_afterPad2_afterConv2_kernel2_bias2_afterAct2_QKV_buffer_out__tmp_vec.push_back(_xlx_tmp_sc);
  }
  int __xlx_size_param_afterRearrangeX = 15680;
  int __xlx_offset_param_afterRearrangeX = 16000;
  int __xlx_offset_byte_param_afterRearrangeX = 16000*4;
  for (int j = 0, e = 15680; j != e; ++j) {
    sc_bv<32> _xlx_tmp_sc;
    _xlx_tmp_sc.range(7, 0) = ((char*)__xlx_apatb_param_afterPad1)[j*4+0];
    _xlx_tmp_sc.range(15, 8) = ((char*)__xlx_apatb_param_afterPad1)[j*4+1];
    _xlx_tmp_sc.range(23, 16) = ((char*)__xlx_apatb_param_afterPad1)[j*4+2];
    _xlx_tmp_sc.range(31, 24) = ((char*)__xlx_apatb_param_afterPad1)[j*4+3];
    __xlx_norm1_mean_norm1_var_norm1_weight_norm1_bias_afterPad_afterRearrangeX_afterPad1_afterConv1_kernel1_bias1_in_qk_in_q_in_k_afterQKMultiplication_afterSoftmax_afterRearrangeX2_afterQKXMultiplication_afterRearrangeQKX_afterPad2_afterConv2_kernel2_bias2_afterAct2_QKV_buffer_out__tmp_vec.push_back(_xlx_tmp_sc);
  }
  int __xlx_size_param_afterPad1 = 15680;
  int __xlx_offset_param_afterPad1 = 31680;
  int __xlx_offset_byte_param_afterPad1 = 31680*4;
  for (int j = 0, e = 31360; j != e; ++j) {
    sc_bv<32> _xlx_tmp_sc;
    _xlx_tmp_sc.range(7, 0) = ((char*)__xlx_apatb_param_afterConv1)[j*4+0];
    _xlx_tmp_sc.range(15, 8) = ((char*)__xlx_apatb_param_afterConv1)[j*4+1];
    _xlx_tmp_sc.range(23, 16) = ((char*)__xlx_apatb_param_afterConv1)[j*4+2];
    _xlx_tmp_sc.range(31, 24) = ((char*)__xlx_apatb_param_afterConv1)[j*4+3];
    __xlx_norm1_mean_norm1_var_norm1_weight_norm1_bias_afterPad_afterRearrangeX_afterPad1_afterConv1_kernel1_bias1_in_qk_in_q_in_k_afterQKMultiplication_afterSoftmax_afterRearrangeX2_afterQKXMultiplication_afterRearrangeQKX_afterPad2_afterConv2_kernel2_bias2_afterAct2_QKV_buffer_out__tmp_vec.push_back(_xlx_tmp_sc);
  }
  int __xlx_size_param_afterConv1 = 31360;
  int __xlx_offset_param_afterConv1 = 47360;
  int __xlx_offset_byte_param_afterConv1 = 47360*4;
  for (int j = 0, e = 12800; j != e; ++j) {
    sc_bv<32> _xlx_tmp_sc;
    _xlx_tmp_sc.range(7, 0) = ((char*)__xlx_apatb_param_kernel1)[j*4+0];
    _xlx_tmp_sc.range(15, 8) = ((char*)__xlx_apatb_param_kernel1)[j*4+1];
    _xlx_tmp_sc.range(23, 16) = ((char*)__xlx_apatb_param_kernel1)[j*4+2];
    _xlx_tmp_sc.range(31, 24) = ((char*)__xlx_apatb_param_kernel1)[j*4+3];
    __xlx_norm1_mean_norm1_var_norm1_weight_norm1_bias_afterPad_afterRearrangeX_afterPad1_afterConv1_kernel1_bias1_in_qk_in_q_in_k_afterQKMultiplication_afterSoftmax_afterRearrangeX2_afterQKXMultiplication_afterRearrangeQKX_afterPad2_afterConv2_kernel2_bias2_afterAct2_QKV_buffer_out__tmp_vec.push_back(_xlx_tmp_sc);
  }
  int __xlx_size_param_kernel1 = 12800;
  int __xlx_offset_param_kernel1 = 78720;
  int __xlx_offset_byte_param_kernel1 = 78720*4;
  for (int j = 0, e = 160; j != e; ++j) {
    sc_bv<32> _xlx_tmp_sc;
    _xlx_tmp_sc.range(7, 0) = ((char*)__xlx_apatb_param_bias1)[j*4+0];
    _xlx_tmp_sc.range(15, 8) = ((char*)__xlx_apatb_param_bias1)[j*4+1];
    _xlx_tmp_sc.range(23, 16) = ((char*)__xlx_apatb_param_bias1)[j*4+2];
    _xlx_tmp_sc.range(31, 24) = ((char*)__xlx_apatb_param_bias1)[j*4+3];
    __xlx_norm1_mean_norm1_var_norm1_weight_norm1_bias_afterPad_afterRearrangeX_afterPad1_afterConv1_kernel1_bias1_in_qk_in_q_in_k_afterQKMultiplication_afterSoftmax_afterRearrangeX2_afterQKXMultiplication_afterRearrangeQKX_afterPad2_afterConv2_kernel2_bias2_afterAct2_QKV_buffer_out__tmp_vec.push_back(_xlx_tmp_sc);
  }
  int __xlx_size_param_bias1 = 160;
  int __xlx_offset_param_bias1 = 91520;
  int __xlx_offset_byte_param_bias1 = 91520*4;
  for (int j = 0, e = 31360; j != e; ++j) {
    sc_bv<32> _xlx_tmp_sc;
    _xlx_tmp_sc.range(7, 0) = ((char*)__xlx_apatb_param_in_qk)[j*4+0];
    _xlx_tmp_sc.range(15, 8) = ((char*)__xlx_apatb_param_in_qk)[j*4+1];
    _xlx_tmp_sc.range(23, 16) = ((char*)__xlx_apatb_param_in_qk)[j*4+2];
    _xlx_tmp_sc.range(31, 24) = ((char*)__xlx_apatb_param_in_qk)[j*4+3];
    __xlx_norm1_mean_norm1_var_norm1_weight_norm1_bias_afterPad_afterRearrangeX_afterPad1_afterConv1_kernel1_bias1_in_qk_in_q_in_k_afterQKMultiplication_afterSoftmax_afterRearrangeX2_afterQKXMultiplication_afterRearrangeQKX_afterPad2_afterConv2_kernel2_bias2_afterAct2_QKV_buffer_out__tmp_vec.push_back(_xlx_tmp_sc);
  }
  int __xlx_size_param_in_qk = 31360;
  int __xlx_offset_param_in_qk = 91680;
  int __xlx_offset_byte_param_in_qk = 91680*4;
  for (int j = 0, e = 15680; j != e; ++j) {
    sc_bv<32> _xlx_tmp_sc;
    _xlx_tmp_sc.range(7, 0) = ((char*)__xlx_apatb_param_in_q)[j*4+0];
    _xlx_tmp_sc.range(15, 8) = ((char*)__xlx_apatb_param_in_q)[j*4+1];
    _xlx_tmp_sc.range(23, 16) = ((char*)__xlx_apatb_param_in_q)[j*4+2];
    _xlx_tmp_sc.range(31, 24) = ((char*)__xlx_apatb_param_in_q)[j*4+3];
    __xlx_norm1_mean_norm1_var_norm1_weight_norm1_bias_afterPad_afterRearrangeX_afterPad1_afterConv1_kernel1_bias1_in_qk_in_q_in_k_afterQKMultiplication_afterSoftmax_afterRearrangeX2_afterQKXMultiplication_afterRearrangeQKX_afterPad2_afterConv2_kernel2_bias2_afterAct2_QKV_buffer_out__tmp_vec.push_back(_xlx_tmp_sc);
  }
  int __xlx_size_param_in_q = 15680;
  int __xlx_offset_param_in_q = 123040;
  int __xlx_offset_byte_param_in_q = 123040*4;
  for (int j = 0, e = 15680; j != e; ++j) {
    sc_bv<32> _xlx_tmp_sc;
    _xlx_tmp_sc.range(7, 0) = ((char*)__xlx_apatb_param_in_k)[j*4+0];
    _xlx_tmp_sc.range(15, 8) = ((char*)__xlx_apatb_param_in_k)[j*4+1];
    _xlx_tmp_sc.range(23, 16) = ((char*)__xlx_apatb_param_in_k)[j*4+2];
    _xlx_tmp_sc.range(31, 24) = ((char*)__xlx_apatb_param_in_k)[j*4+3];
    __xlx_norm1_mean_norm1_var_norm1_weight_norm1_bias_afterPad_afterRearrangeX_afterPad1_afterConv1_kernel1_bias1_in_qk_in_q_in_k_afterQKMultiplication_afterSoftmax_afterRearrangeX2_afterQKXMultiplication_afterRearrangeQKX_afterPad2_afterConv2_kernel2_bias2_afterAct2_QKV_buffer_out__tmp_vec.push_back(_xlx_tmp_sc);
  }
  int __xlx_size_param_in_k = 15680;
  int __xlx_offset_param_in_k = 138720;
  int __xlx_offset_byte_param_in_k = 138720*4;
  for (int j = 0, e = 38416; j != e; ++j) {
    sc_bv<32> _xlx_tmp_sc;
    _xlx_tmp_sc.range(7, 0) = ((char*)__xlx_apatb_param_afterQKMultiplication)[j*4+0];
    _xlx_tmp_sc.range(15, 8) = ((char*)__xlx_apatb_param_afterQKMultiplication)[j*4+1];
    _xlx_tmp_sc.range(23, 16) = ((char*)__xlx_apatb_param_afterQKMultiplication)[j*4+2];
    _xlx_tmp_sc.range(31, 24) = ((char*)__xlx_apatb_param_afterQKMultiplication)[j*4+3];
    __xlx_norm1_mean_norm1_var_norm1_weight_norm1_bias_afterPad_afterRearrangeX_afterPad1_afterConv1_kernel1_bias1_in_qk_in_q_in_k_afterQKMultiplication_afterSoftmax_afterRearrangeX2_afterQKXMultiplication_afterRearrangeQKX_afterPad2_afterConv2_kernel2_bias2_afterAct2_QKV_buffer_out__tmp_vec.push_back(_xlx_tmp_sc);
  }
  int __xlx_size_param_afterQKMultiplication = 38416;
  int __xlx_offset_param_afterQKMultiplication = 154400;
  int __xlx_offset_byte_param_afterQKMultiplication = 154400*4;
  for (int j = 0, e = 38416; j != e; ++j) {
    sc_bv<32> _xlx_tmp_sc;
    _xlx_tmp_sc.range(7, 0) = ((char*)__xlx_apatb_param_afterSoftmax)[j*4+0];
    _xlx_tmp_sc.range(15, 8) = ((char*)__xlx_apatb_param_afterSoftmax)[j*4+1];
    _xlx_tmp_sc.range(23, 16) = ((char*)__xlx_apatb_param_afterSoftmax)[j*4+2];
    _xlx_tmp_sc.range(31, 24) = ((char*)__xlx_apatb_param_afterSoftmax)[j*4+3];
    __xlx_norm1_mean_norm1_var_norm1_weight_norm1_bias_afterPad_afterRearrangeX_afterPad1_afterConv1_kernel1_bias1_in_qk_in_q_in_k_afterQKMultiplication_afterSoftmax_afterRearrangeX2_afterQKXMultiplication_afterRearrangeQKX_afterPad2_afterConv2_kernel2_bias2_afterAct2_QKV_buffer_out__tmp_vec.push_back(_xlx_tmp_sc);
  }
  int __xlx_size_param_afterSoftmax = 38416;
  int __xlx_offset_param_afterSoftmax = 192816;
  int __xlx_offset_byte_param_afterSoftmax = 192816*4;
  for (int j = 0, e = 15680; j != e; ++j) {
    sc_bv<32> _xlx_tmp_sc;
    _xlx_tmp_sc.range(7, 0) = ((char*)__xlx_apatb_param_afterRearrangeX2)[j*4+0];
    _xlx_tmp_sc.range(15, 8) = ((char*)__xlx_apatb_param_afterRearrangeX2)[j*4+1];
    _xlx_tmp_sc.range(23, 16) = ((char*)__xlx_apatb_param_afterRearrangeX2)[j*4+2];
    _xlx_tmp_sc.range(31, 24) = ((char*)__xlx_apatb_param_afterRearrangeX2)[j*4+3];
    __xlx_norm1_mean_norm1_var_norm1_weight_norm1_bias_afterPad_afterRearrangeX_afterPad1_afterConv1_kernel1_bias1_in_qk_in_q_in_k_afterQKMultiplication_afterSoftmax_afterRearrangeX2_afterQKXMultiplication_afterRearrangeQKX_afterPad2_afterConv2_kernel2_bias2_afterAct2_QKV_buffer_out__tmp_vec.push_back(_xlx_tmp_sc);
  }
  int __xlx_size_param_afterRearrangeX2 = 15680;
  int __xlx_offset_param_afterRearrangeX2 = 231232;
  int __xlx_offset_byte_param_afterRearrangeX2 = 231232*4;
  for (int j = 0, e = 15680; j != e; ++j) {
    sc_bv<32> _xlx_tmp_sc;
    _xlx_tmp_sc.range(7, 0) = ((char*)__xlx_apatb_param_afterQKXMultiplication)[j*4+0];
    _xlx_tmp_sc.range(15, 8) = ((char*)__xlx_apatb_param_afterQKXMultiplication)[j*4+1];
    _xlx_tmp_sc.range(23, 16) = ((char*)__xlx_apatb_param_afterQKXMultiplication)[j*4+2];
    _xlx_tmp_sc.range(31, 24) = ((char*)__xlx_apatb_param_afterQKXMultiplication)[j*4+3];
    __xlx_norm1_mean_norm1_var_norm1_weight_norm1_bias_afterPad_afterRearrangeX_afterPad1_afterConv1_kernel1_bias1_in_qk_in_q_in_k_afterQKMultiplication_afterSoftmax_afterRearrangeX2_afterQKXMultiplication_afterRearrangeQKX_afterPad2_afterConv2_kernel2_bias2_afterAct2_QKV_buffer_out__tmp_vec.push_back(_xlx_tmp_sc);
  }
  int __xlx_size_param_afterQKXMultiplication = 15680;
  int __xlx_offset_param_afterQKXMultiplication = 246912;
  int __xlx_offset_byte_param_afterQKXMultiplication = 246912*4;
  for (int j = 0, e = 15680; j != e; ++j) {
    sc_bv<32> _xlx_tmp_sc;
    _xlx_tmp_sc.range(7, 0) = ((char*)__xlx_apatb_param_afterRearrangeQKX)[j*4+0];
    _xlx_tmp_sc.range(15, 8) = ((char*)__xlx_apatb_param_afterRearrangeQKX)[j*4+1];
    _xlx_tmp_sc.range(23, 16) = ((char*)__xlx_apatb_param_afterRearrangeQKX)[j*4+2];
    _xlx_tmp_sc.range(31, 24) = ((char*)__xlx_apatb_param_afterRearrangeQKX)[j*4+3];
    __xlx_norm1_mean_norm1_var_norm1_weight_norm1_bias_afterPad_afterRearrangeX_afterPad1_afterConv1_kernel1_bias1_in_qk_in_q_in_k_afterQKMultiplication_afterSoftmax_afterRearrangeX2_afterQKXMultiplication_afterRearrangeQKX_afterPad2_afterConv2_kernel2_bias2_afterAct2_QKV_buffer_out__tmp_vec.push_back(_xlx_tmp_sc);
  }
  int __xlx_size_param_afterRearrangeQKX = 15680;
  int __xlx_offset_param_afterRearrangeQKX = 262592;
  int __xlx_offset_byte_param_afterRearrangeQKX = 262592*4;
  for (int j = 0, e = 15680; j != e; ++j) {
    sc_bv<32> _xlx_tmp_sc;
    _xlx_tmp_sc.range(7, 0) = ((char*)__xlx_apatb_param_afterPad2)[j*4+0];
    _xlx_tmp_sc.range(15, 8) = ((char*)__xlx_apatb_param_afterPad2)[j*4+1];
    _xlx_tmp_sc.range(23, 16) = ((char*)__xlx_apatb_param_afterPad2)[j*4+2];
    _xlx_tmp_sc.range(31, 24) = ((char*)__xlx_apatb_param_afterPad2)[j*4+3];
    __xlx_norm1_mean_norm1_var_norm1_weight_norm1_bias_afterPad_afterRearrangeX_afterPad1_afterConv1_kernel1_bias1_in_qk_in_q_in_k_afterQKMultiplication_afterSoftmax_afterRearrangeX2_afterQKXMultiplication_afterRearrangeQKX_afterPad2_afterConv2_kernel2_bias2_afterAct2_QKV_buffer_out__tmp_vec.push_back(_xlx_tmp_sc);
  }
  int __xlx_size_param_afterPad2 = 15680;
  int __xlx_offset_param_afterPad2 = 278272;
  int __xlx_offset_byte_param_afterPad2 = 278272*4;
  for (int j = 0, e = 47040; j != e; ++j) {
    sc_bv<32> _xlx_tmp_sc;
    _xlx_tmp_sc.range(7, 0) = ((char*)__xlx_apatb_param_afterConv2)[j*4+0];
    _xlx_tmp_sc.range(15, 8) = ((char*)__xlx_apatb_param_afterConv2)[j*4+1];
    _xlx_tmp_sc.range(23, 16) = ((char*)__xlx_apatb_param_afterConv2)[j*4+2];
    _xlx_tmp_sc.range(31, 24) = ((char*)__xlx_apatb_param_afterConv2)[j*4+3];
    __xlx_norm1_mean_norm1_var_norm1_weight_norm1_bias_afterPad_afterRearrangeX_afterPad1_afterConv1_kernel1_bias1_in_qk_in_q_in_k_afterQKMultiplication_afterSoftmax_afterRearrangeX2_afterQKXMultiplication_afterRearrangeQKX_afterPad2_afterConv2_kernel2_bias2_afterAct2_QKV_buffer_out__tmp_vec.push_back(_xlx_tmp_sc);
  }
  int __xlx_size_param_afterConv2 = 47040;
  int __xlx_offset_param_afterConv2 = 293952;
  int __xlx_offset_byte_param_afterConv2 = 293952*4;
  for (int j = 0, e = 19200; j != e; ++j) {
    sc_bv<32> _xlx_tmp_sc;
    _xlx_tmp_sc.range(7, 0) = ((char*)__xlx_apatb_param_kernel2)[j*4+0];
    _xlx_tmp_sc.range(15, 8) = ((char*)__xlx_apatb_param_kernel2)[j*4+1];
    _xlx_tmp_sc.range(23, 16) = ((char*)__xlx_apatb_param_kernel2)[j*4+2];
    _xlx_tmp_sc.range(31, 24) = ((char*)__xlx_apatb_param_kernel2)[j*4+3];
    __xlx_norm1_mean_norm1_var_norm1_weight_norm1_bias_afterPad_afterRearrangeX_afterPad1_afterConv1_kernel1_bias1_in_qk_in_q_in_k_afterQKMultiplication_afterSoftmax_afterRearrangeX2_afterQKXMultiplication_afterRearrangeQKX_afterPad2_afterConv2_kernel2_bias2_afterAct2_QKV_buffer_out__tmp_vec.push_back(_xlx_tmp_sc);
  }
  int __xlx_size_param_kernel2 = 19200;
  int __xlx_offset_param_kernel2 = 340992;
  int __xlx_offset_byte_param_kernel2 = 340992*4;
  for (int j = 0, e = 240; j != e; ++j) {
    sc_bv<32> _xlx_tmp_sc;
    _xlx_tmp_sc.range(7, 0) = ((char*)__xlx_apatb_param_bias2)[j*4+0];
    _xlx_tmp_sc.range(15, 8) = ((char*)__xlx_apatb_param_bias2)[j*4+1];
    _xlx_tmp_sc.range(23, 16) = ((char*)__xlx_apatb_param_bias2)[j*4+2];
    _xlx_tmp_sc.range(31, 24) = ((char*)__xlx_apatb_param_bias2)[j*4+3];
    __xlx_norm1_mean_norm1_var_norm1_weight_norm1_bias_afterPad_afterRearrangeX_afterPad1_afterConv1_kernel1_bias1_in_qk_in_q_in_k_afterQKMultiplication_afterSoftmax_afterRearrangeX2_afterQKXMultiplication_afterRearrangeQKX_afterPad2_afterConv2_kernel2_bias2_afterAct2_QKV_buffer_out__tmp_vec.push_back(_xlx_tmp_sc);
  }
  int __xlx_size_param_bias2 = 240;
  int __xlx_offset_param_bias2 = 360192;
  int __xlx_offset_byte_param_bias2 = 360192*4;
  for (int j = 0, e = 47040; j != e; ++j) {
    sc_bv<32> _xlx_tmp_sc;
    _xlx_tmp_sc.range(7, 0) = ((char*)__xlx_apatb_param_afterAct2)[j*4+0];
    _xlx_tmp_sc.range(15, 8) = ((char*)__xlx_apatb_param_afterAct2)[j*4+1];
    _xlx_tmp_sc.range(23, 16) = ((char*)__xlx_apatb_param_afterAct2)[j*4+2];
    _xlx_tmp_sc.range(31, 24) = ((char*)__xlx_apatb_param_afterAct2)[j*4+3];
    __xlx_norm1_mean_norm1_var_norm1_weight_norm1_bias_afterPad_afterRearrangeX_afterPad1_afterConv1_kernel1_bias1_in_qk_in_q_in_k_afterQKMultiplication_afterSoftmax_afterRearrangeX2_afterQKXMultiplication_afterRearrangeQKX_afterPad2_afterConv2_kernel2_bias2_afterAct2_QKV_buffer_out__tmp_vec.push_back(_xlx_tmp_sc);
  }
  int __xlx_size_param_afterAct2 = 47040;
  int __xlx_offset_param_afterAct2 = 360432;
  int __xlx_offset_byte_param_afterAct2 = 360432*4;
  for (int j = 0, e = 47040; j != e; ++j) {
    sc_bv<32> _xlx_tmp_sc;
    _xlx_tmp_sc.range(7, 0) = ((char*)__xlx_apatb_param_QKV)[j*4+0];
    _xlx_tmp_sc.range(15, 8) = ((char*)__xlx_apatb_param_QKV)[j*4+1];
    _xlx_tmp_sc.range(23, 16) = ((char*)__xlx_apatb_param_QKV)[j*4+2];
    _xlx_tmp_sc.range(31, 24) = ((char*)__xlx_apatb_param_QKV)[j*4+3];
    __xlx_norm1_mean_norm1_var_norm1_weight_norm1_bias_afterPad_afterRearrangeX_afterPad1_afterConv1_kernel1_bias1_in_qk_in_q_in_k_afterQKMultiplication_afterSoftmax_afterRearrangeX2_afterQKXMultiplication_afterRearrangeQKX_afterPad2_afterConv2_kernel2_bias2_afterAct2_QKV_buffer_out__tmp_vec.push_back(_xlx_tmp_sc);
  }
  int __xlx_size_param_QKV = 47040;
  int __xlx_offset_param_QKV = 407472;
  int __xlx_offset_byte_param_QKV = 407472*4;
  for (int j = 0, e = 47040; j != e; ++j) {
    sc_bv<32> _xlx_tmp_sc;
    _xlx_tmp_sc.range(7, 0) = ((char*)__xlx_apatb_param_buffer_out)[j*4+0];
    _xlx_tmp_sc.range(15, 8) = ((char*)__xlx_apatb_param_buffer_out)[j*4+1];
    _xlx_tmp_sc.range(23, 16) = ((char*)__xlx_apatb_param_buffer_out)[j*4+2];
    _xlx_tmp_sc.range(31, 24) = ((char*)__xlx_apatb_param_buffer_out)[j*4+3];
    __xlx_norm1_mean_norm1_var_norm1_weight_norm1_bias_afterPad_afterRearrangeX_afterPad1_afterConv1_kernel1_bias1_in_qk_in_q_in_k_afterQKMultiplication_afterSoftmax_afterRearrangeX2_afterQKXMultiplication_afterRearrangeQKX_afterPad2_afterConv2_kernel2_bias2_afterAct2_QKV_buffer_out__tmp_vec.push_back(_xlx_tmp_sc);
  }
  int __xlx_size_param_buffer_out = 47040;
  int __xlx_offset_param_buffer_out = 454512;
  int __xlx_offset_byte_param_buffer_out = 454512*4;
  int* __xlx_norm1_mean_norm1_var_norm1_weight_norm1_bias_afterPad_afterRearrangeX_afterPad1_afterConv1_kernel1_bias1_in_qk_in_q_in_k_afterQKMultiplication_afterSoftmax_afterRearrangeX2_afterQKXMultiplication_afterRearrangeQKX_afterPad2_afterConv2_kernel2_bias2_afterAct2_QKV_buffer_out__input_buffer= new int[__xlx_norm1_mean_norm1_var_norm1_weight_norm1_bias_afterPad_afterRearrangeX_afterPad1_afterConv1_kernel1_bias1_in_qk_in_q_in_k_afterQKMultiplication_afterSoftmax_afterRearrangeX2_afterQKXMultiplication_afterRearrangeQKX_afterPad2_afterConv2_kernel2_bias2_afterAct2_QKV_buffer_out__tmp_vec.size()];
  for (int i = 0; i < __xlx_norm1_mean_norm1_var_norm1_weight_norm1_bias_afterPad_afterRearrangeX_afterPad1_afterConv1_kernel1_bias1_in_qk_in_q_in_k_afterQKMultiplication_afterSoftmax_afterRearrangeX2_afterQKXMultiplication_afterRearrangeQKX_afterPad2_afterConv2_kernel2_bias2_afterAct2_QKV_buffer_out__tmp_vec.size(); ++i) {
    __xlx_norm1_mean_norm1_var_norm1_weight_norm1_bias_afterPad_afterRearrangeX_afterPad1_afterConv1_kernel1_bias1_in_qk_in_q_in_k_afterQKMultiplication_afterSoftmax_afterRearrangeX2_afterQKXMultiplication_afterRearrangeQKX_afterPad2_afterConv2_kernel2_bias2_afterAct2_QKV_buffer_out__input_buffer[i] = __xlx_norm1_mean_norm1_var_norm1_weight_norm1_bias_afterPad_afterRearrangeX_afterPad1_afterConv1_kernel1_bias1_in_qk_in_q_in_k_afterQKMultiplication_afterSoftmax_afterRearrangeX2_afterQKXMultiplication_afterRearrangeQKX_afterPad2_afterConv2_kernel2_bias2_afterAct2_QKV_buffer_out__tmp_vec[i].range(31, 0).to_uint64();
  }
  // DUT call
  kernel_attention(__xlx_buffer_DataIn_1_buffer_result__input_buffer, __xlx_afterNorm__input_buffer, __xlx_norm1_mean_norm1_var_norm1_weight_norm1_bias_afterPad_afterRearrangeX_afterPad1_afterConv1_kernel1_bias1_in_qk_in_q_in_k_afterQKMultiplication_afterSoftmax_afterRearrangeX2_afterQKXMultiplication_afterRearrangeQKX_afterPad2_afterConv2_kernel2_bias2_afterAct2_QKV_buffer_out__input_buffer, __xlx_offset_byte_param_buffer_DataIn_1, __xlx_offset_byte_param_afterNorm, __xlx_offset_byte_param_norm1_mean, __xlx_offset_byte_param_norm1_var, __xlx_offset_byte_param_norm1_weight, __xlx_offset_byte_param_norm1_bias, __xlx_offset_byte_param_afterPad, __xlx_offset_byte_param_afterRearrangeX, __xlx_offset_byte_param_afterPad1, __xlx_offset_byte_param_afterConv1, __xlx_offset_byte_param_kernel1, __xlx_offset_byte_param_bias1, __xlx_offset_byte_param_in_qk, __xlx_offset_byte_param_in_q, __xlx_offset_byte_param_in_k, __xlx_offset_byte_param_afterQKMultiplication, __xlx_offset_byte_param_afterSoftmax, __xlx_offset_byte_param_afterRearrangeX2, __xlx_offset_byte_param_afterQKXMultiplication, __xlx_offset_byte_param_afterRearrangeQKX, __xlx_offset_byte_param_afterPad2, __xlx_offset_byte_param_afterConv2, __xlx_offset_byte_param_kernel2, __xlx_offset_byte_param_bias2, __xlx_offset_byte_param_afterAct2, __xlx_offset_byte_param_QKV, __xlx_offset_byte_param_buffer_out, __xlx_offset_byte_param_buffer_result);
// print __xlx_apatb_param_buffer_DataIn_1
  sc_bv<32>*__xlx_buffer_DataIn_1_output_buffer = new sc_bv<32>[__xlx_size_param_buffer_DataIn_1];
  for (int i = 0; i < __xlx_size_param_buffer_DataIn_1; ++i) {
    __xlx_buffer_DataIn_1_output_buffer[i] = __xlx_buffer_DataIn_1_buffer_result__input_buffer[i+__xlx_offset_param_buffer_DataIn_1];
  }
  for (int i = 0; i < __xlx_size_param_buffer_DataIn_1; ++i) {
    ((char*)__xlx_apatb_param_buffer_DataIn_1)[i*4+0] = __xlx_buffer_DataIn_1_output_buffer[i].range(7, 0).to_uint();
    ((char*)__xlx_apatb_param_buffer_DataIn_1)[i*4+1] = __xlx_buffer_DataIn_1_output_buffer[i].range(15, 8).to_uint();
    ((char*)__xlx_apatb_param_buffer_DataIn_1)[i*4+2] = __xlx_buffer_DataIn_1_output_buffer[i].range(23, 16).to_uint();
    ((char*)__xlx_apatb_param_buffer_DataIn_1)[i*4+3] = __xlx_buffer_DataIn_1_output_buffer[i].range(31, 24).to_uint();
  }
// print __xlx_apatb_param_buffer_result
  sc_bv<32>*__xlx_buffer_result_output_buffer = new sc_bv<32>[__xlx_size_param_buffer_result];
  for (int i = 0; i < __xlx_size_param_buffer_result; ++i) {
    __xlx_buffer_result_output_buffer[i] = __xlx_buffer_DataIn_1_buffer_result__input_buffer[i+__xlx_offset_param_buffer_result];
  }
  for (int i = 0; i < __xlx_size_param_buffer_result; ++i) {
    ((char*)__xlx_apatb_param_buffer_result)[i*4+0] = __xlx_buffer_result_output_buffer[i].range(7, 0).to_uint();
    ((char*)__xlx_apatb_param_buffer_result)[i*4+1] = __xlx_buffer_result_output_buffer[i].range(15, 8).to_uint();
    ((char*)__xlx_apatb_param_buffer_result)[i*4+2] = __xlx_buffer_result_output_buffer[i].range(23, 16).to_uint();
    ((char*)__xlx_apatb_param_buffer_result)[i*4+3] = __xlx_buffer_result_output_buffer[i].range(31, 24).to_uint();
  }
// print __xlx_apatb_param_afterNorm
  sc_bv<32>*__xlx_afterNorm_output_buffer = new sc_bv<32>[__xlx_size_param_afterNorm];
  for (int i = 0; i < __xlx_size_param_afterNorm; ++i) {
    __xlx_afterNorm_output_buffer[i] = __xlx_afterNorm__input_buffer[i+__xlx_offset_param_afterNorm];
  }
  for (int i = 0; i < __xlx_size_param_afterNorm; ++i) {
    ((char*)__xlx_apatb_param_afterNorm)[i*4+0] = __xlx_afterNorm_output_buffer[i].range(7, 0).to_uint();
    ((char*)__xlx_apatb_param_afterNorm)[i*4+1] = __xlx_afterNorm_output_buffer[i].range(15, 8).to_uint();
    ((char*)__xlx_apatb_param_afterNorm)[i*4+2] = __xlx_afterNorm_output_buffer[i].range(23, 16).to_uint();
    ((char*)__xlx_apatb_param_afterNorm)[i*4+3] = __xlx_afterNorm_output_buffer[i].range(31, 24).to_uint();
  }
// print __xlx_apatb_param_norm1_mean
  sc_bv<32>*__xlx_norm1_mean_output_buffer = new sc_bv<32>[__xlx_size_param_norm1_mean];
  for (int i = 0; i < __xlx_size_param_norm1_mean; ++i) {
    __xlx_norm1_mean_output_buffer[i] = __xlx_norm1_mean_norm1_var_norm1_weight_norm1_bias_afterPad_afterRearrangeX_afterPad1_afterConv1_kernel1_bias1_in_qk_in_q_in_k_afterQKMultiplication_afterSoftmax_afterRearrangeX2_afterQKXMultiplication_afterRearrangeQKX_afterPad2_afterConv2_kernel2_bias2_afterAct2_QKV_buffer_out__input_buffer[i+__xlx_offset_param_norm1_mean];
  }
  for (int i = 0; i < __xlx_size_param_norm1_mean; ++i) {
    ((char*)__xlx_apatb_param_norm1_mean)[i*4+0] = __xlx_norm1_mean_output_buffer[i].range(7, 0).to_uint();
    ((char*)__xlx_apatb_param_norm1_mean)[i*4+1] = __xlx_norm1_mean_output_buffer[i].range(15, 8).to_uint();
    ((char*)__xlx_apatb_param_norm1_mean)[i*4+2] = __xlx_norm1_mean_output_buffer[i].range(23, 16).to_uint();
    ((char*)__xlx_apatb_param_norm1_mean)[i*4+3] = __xlx_norm1_mean_output_buffer[i].range(31, 24).to_uint();
  }
// print __xlx_apatb_param_norm1_var
  sc_bv<32>*__xlx_norm1_var_output_buffer = new sc_bv<32>[__xlx_size_param_norm1_var];
  for (int i = 0; i < __xlx_size_param_norm1_var; ++i) {
    __xlx_norm1_var_output_buffer[i] = __xlx_norm1_mean_norm1_var_norm1_weight_norm1_bias_afterPad_afterRearrangeX_afterPad1_afterConv1_kernel1_bias1_in_qk_in_q_in_k_afterQKMultiplication_afterSoftmax_afterRearrangeX2_afterQKXMultiplication_afterRearrangeQKX_afterPad2_afterConv2_kernel2_bias2_afterAct2_QKV_buffer_out__input_buffer[i+__xlx_offset_param_norm1_var];
  }
  for (int i = 0; i < __xlx_size_param_norm1_var; ++i) {
    ((char*)__xlx_apatb_param_norm1_var)[i*4+0] = __xlx_norm1_var_output_buffer[i].range(7, 0).to_uint();
    ((char*)__xlx_apatb_param_norm1_var)[i*4+1] = __xlx_norm1_var_output_buffer[i].range(15, 8).to_uint();
    ((char*)__xlx_apatb_param_norm1_var)[i*4+2] = __xlx_norm1_var_output_buffer[i].range(23, 16).to_uint();
    ((char*)__xlx_apatb_param_norm1_var)[i*4+3] = __xlx_norm1_var_output_buffer[i].range(31, 24).to_uint();
  }
// print __xlx_apatb_param_norm1_weight
  sc_bv<32>*__xlx_norm1_weight_output_buffer = new sc_bv<32>[__xlx_size_param_norm1_weight];
  for (int i = 0; i < __xlx_size_param_norm1_weight; ++i) {
    __xlx_norm1_weight_output_buffer[i] = __xlx_norm1_mean_norm1_var_norm1_weight_norm1_bias_afterPad_afterRearrangeX_afterPad1_afterConv1_kernel1_bias1_in_qk_in_q_in_k_afterQKMultiplication_afterSoftmax_afterRearrangeX2_afterQKXMultiplication_afterRearrangeQKX_afterPad2_afterConv2_kernel2_bias2_afterAct2_QKV_buffer_out__input_buffer[i+__xlx_offset_param_norm1_weight];
  }
  for (int i = 0; i < __xlx_size_param_norm1_weight; ++i) {
    ((char*)__xlx_apatb_param_norm1_weight)[i*4+0] = __xlx_norm1_weight_output_buffer[i].range(7, 0).to_uint();
    ((char*)__xlx_apatb_param_norm1_weight)[i*4+1] = __xlx_norm1_weight_output_buffer[i].range(15, 8).to_uint();
    ((char*)__xlx_apatb_param_norm1_weight)[i*4+2] = __xlx_norm1_weight_output_buffer[i].range(23, 16).to_uint();
    ((char*)__xlx_apatb_param_norm1_weight)[i*4+3] = __xlx_norm1_weight_output_buffer[i].range(31, 24).to_uint();
  }
// print __xlx_apatb_param_norm1_bias
  sc_bv<32>*__xlx_norm1_bias_output_buffer = new sc_bv<32>[__xlx_size_param_norm1_bias];
  for (int i = 0; i < __xlx_size_param_norm1_bias; ++i) {
    __xlx_norm1_bias_output_buffer[i] = __xlx_norm1_mean_norm1_var_norm1_weight_norm1_bias_afterPad_afterRearrangeX_afterPad1_afterConv1_kernel1_bias1_in_qk_in_q_in_k_afterQKMultiplication_afterSoftmax_afterRearrangeX2_afterQKXMultiplication_afterRearrangeQKX_afterPad2_afterConv2_kernel2_bias2_afterAct2_QKV_buffer_out__input_buffer[i+__xlx_offset_param_norm1_bias];
  }
  for (int i = 0; i < __xlx_size_param_norm1_bias; ++i) {
    ((char*)__xlx_apatb_param_norm1_bias)[i*4+0] = __xlx_norm1_bias_output_buffer[i].range(7, 0).to_uint();
    ((char*)__xlx_apatb_param_norm1_bias)[i*4+1] = __xlx_norm1_bias_output_buffer[i].range(15, 8).to_uint();
    ((char*)__xlx_apatb_param_norm1_bias)[i*4+2] = __xlx_norm1_bias_output_buffer[i].range(23, 16).to_uint();
    ((char*)__xlx_apatb_param_norm1_bias)[i*4+3] = __xlx_norm1_bias_output_buffer[i].range(31, 24).to_uint();
  }
// print __xlx_apatb_param_afterPad
  sc_bv<32>*__xlx_afterPad_output_buffer = new sc_bv<32>[__xlx_size_param_afterPad];
  for (int i = 0; i < __xlx_size_param_afterPad; ++i) {
    __xlx_afterPad_output_buffer[i] = __xlx_norm1_mean_norm1_var_norm1_weight_norm1_bias_afterPad_afterRearrangeX_afterPad1_afterConv1_kernel1_bias1_in_qk_in_q_in_k_afterQKMultiplication_afterSoftmax_afterRearrangeX2_afterQKXMultiplication_afterRearrangeQKX_afterPad2_afterConv2_kernel2_bias2_afterAct2_QKV_buffer_out__input_buffer[i+__xlx_offset_param_afterPad];
  }
  for (int i = 0; i < __xlx_size_param_afterPad; ++i) {
    ((char*)__xlx_apatb_param_afterPad)[i*4+0] = __xlx_afterPad_output_buffer[i].range(7, 0).to_uint();
    ((char*)__xlx_apatb_param_afterPad)[i*4+1] = __xlx_afterPad_output_buffer[i].range(15, 8).to_uint();
    ((char*)__xlx_apatb_param_afterPad)[i*4+2] = __xlx_afterPad_output_buffer[i].range(23, 16).to_uint();
    ((char*)__xlx_apatb_param_afterPad)[i*4+3] = __xlx_afterPad_output_buffer[i].range(31, 24).to_uint();
  }
// print __xlx_apatb_param_afterRearrangeX
  sc_bv<32>*__xlx_afterRearrangeX_output_buffer = new sc_bv<32>[__xlx_size_param_afterRearrangeX];
  for (int i = 0; i < __xlx_size_param_afterRearrangeX; ++i) {
    __xlx_afterRearrangeX_output_buffer[i] = __xlx_norm1_mean_norm1_var_norm1_weight_norm1_bias_afterPad_afterRearrangeX_afterPad1_afterConv1_kernel1_bias1_in_qk_in_q_in_k_afterQKMultiplication_afterSoftmax_afterRearrangeX2_afterQKXMultiplication_afterRearrangeQKX_afterPad2_afterConv2_kernel2_bias2_afterAct2_QKV_buffer_out__input_buffer[i+__xlx_offset_param_afterRearrangeX];
  }
  for (int i = 0; i < __xlx_size_param_afterRearrangeX; ++i) {
    ((char*)__xlx_apatb_param_afterRearrangeX)[i*4+0] = __xlx_afterRearrangeX_output_buffer[i].range(7, 0).to_uint();
    ((char*)__xlx_apatb_param_afterRearrangeX)[i*4+1] = __xlx_afterRearrangeX_output_buffer[i].range(15, 8).to_uint();
    ((char*)__xlx_apatb_param_afterRearrangeX)[i*4+2] = __xlx_afterRearrangeX_output_buffer[i].range(23, 16).to_uint();
    ((char*)__xlx_apatb_param_afterRearrangeX)[i*4+3] = __xlx_afterRearrangeX_output_buffer[i].range(31, 24).to_uint();
  }
// print __xlx_apatb_param_afterPad1
  sc_bv<32>*__xlx_afterPad1_output_buffer = new sc_bv<32>[__xlx_size_param_afterPad1];
  for (int i = 0; i < __xlx_size_param_afterPad1; ++i) {
    __xlx_afterPad1_output_buffer[i] = __xlx_norm1_mean_norm1_var_norm1_weight_norm1_bias_afterPad_afterRearrangeX_afterPad1_afterConv1_kernel1_bias1_in_qk_in_q_in_k_afterQKMultiplication_afterSoftmax_afterRearrangeX2_afterQKXMultiplication_afterRearrangeQKX_afterPad2_afterConv2_kernel2_bias2_afterAct2_QKV_buffer_out__input_buffer[i+__xlx_offset_param_afterPad1];
  }
  for (int i = 0; i < __xlx_size_param_afterPad1; ++i) {
    ((char*)__xlx_apatb_param_afterPad1)[i*4+0] = __xlx_afterPad1_output_buffer[i].range(7, 0).to_uint();
    ((char*)__xlx_apatb_param_afterPad1)[i*4+1] = __xlx_afterPad1_output_buffer[i].range(15, 8).to_uint();
    ((char*)__xlx_apatb_param_afterPad1)[i*4+2] = __xlx_afterPad1_output_buffer[i].range(23, 16).to_uint();
    ((char*)__xlx_apatb_param_afterPad1)[i*4+3] = __xlx_afterPad1_output_buffer[i].range(31, 24).to_uint();
  }
// print __xlx_apatb_param_afterConv1
  sc_bv<32>*__xlx_afterConv1_output_buffer = new sc_bv<32>[__xlx_size_param_afterConv1];
  for (int i = 0; i < __xlx_size_param_afterConv1; ++i) {
    __xlx_afterConv1_output_buffer[i] = __xlx_norm1_mean_norm1_var_norm1_weight_norm1_bias_afterPad_afterRearrangeX_afterPad1_afterConv1_kernel1_bias1_in_qk_in_q_in_k_afterQKMultiplication_afterSoftmax_afterRearrangeX2_afterQKXMultiplication_afterRearrangeQKX_afterPad2_afterConv2_kernel2_bias2_afterAct2_QKV_buffer_out__input_buffer[i+__xlx_offset_param_afterConv1];
  }
  for (int i = 0; i < __xlx_size_param_afterConv1; ++i) {
    ((char*)__xlx_apatb_param_afterConv1)[i*4+0] = __xlx_afterConv1_output_buffer[i].range(7, 0).to_uint();
    ((char*)__xlx_apatb_param_afterConv1)[i*4+1] = __xlx_afterConv1_output_buffer[i].range(15, 8).to_uint();
    ((char*)__xlx_apatb_param_afterConv1)[i*4+2] = __xlx_afterConv1_output_buffer[i].range(23, 16).to_uint();
    ((char*)__xlx_apatb_param_afterConv1)[i*4+3] = __xlx_afterConv1_output_buffer[i].range(31, 24).to_uint();
  }
// print __xlx_apatb_param_kernel1
  sc_bv<32>*__xlx_kernel1_output_buffer = new sc_bv<32>[__xlx_size_param_kernel1];
  for (int i = 0; i < __xlx_size_param_kernel1; ++i) {
    __xlx_kernel1_output_buffer[i] = __xlx_norm1_mean_norm1_var_norm1_weight_norm1_bias_afterPad_afterRearrangeX_afterPad1_afterConv1_kernel1_bias1_in_qk_in_q_in_k_afterQKMultiplication_afterSoftmax_afterRearrangeX2_afterQKXMultiplication_afterRearrangeQKX_afterPad2_afterConv2_kernel2_bias2_afterAct2_QKV_buffer_out__input_buffer[i+__xlx_offset_param_kernel1];
  }
  for (int i = 0; i < __xlx_size_param_kernel1; ++i) {
    ((char*)__xlx_apatb_param_kernel1)[i*4+0] = __xlx_kernel1_output_buffer[i].range(7, 0).to_uint();
    ((char*)__xlx_apatb_param_kernel1)[i*4+1] = __xlx_kernel1_output_buffer[i].range(15, 8).to_uint();
    ((char*)__xlx_apatb_param_kernel1)[i*4+2] = __xlx_kernel1_output_buffer[i].range(23, 16).to_uint();
    ((char*)__xlx_apatb_param_kernel1)[i*4+3] = __xlx_kernel1_output_buffer[i].range(31, 24).to_uint();
  }
// print __xlx_apatb_param_bias1
  sc_bv<32>*__xlx_bias1_output_buffer = new sc_bv<32>[__xlx_size_param_bias1];
  for (int i = 0; i < __xlx_size_param_bias1; ++i) {
    __xlx_bias1_output_buffer[i] = __xlx_norm1_mean_norm1_var_norm1_weight_norm1_bias_afterPad_afterRearrangeX_afterPad1_afterConv1_kernel1_bias1_in_qk_in_q_in_k_afterQKMultiplication_afterSoftmax_afterRearrangeX2_afterQKXMultiplication_afterRearrangeQKX_afterPad2_afterConv2_kernel2_bias2_afterAct2_QKV_buffer_out__input_buffer[i+__xlx_offset_param_bias1];
  }
  for (int i = 0; i < __xlx_size_param_bias1; ++i) {
    ((char*)__xlx_apatb_param_bias1)[i*4+0] = __xlx_bias1_output_buffer[i].range(7, 0).to_uint();
    ((char*)__xlx_apatb_param_bias1)[i*4+1] = __xlx_bias1_output_buffer[i].range(15, 8).to_uint();
    ((char*)__xlx_apatb_param_bias1)[i*4+2] = __xlx_bias1_output_buffer[i].range(23, 16).to_uint();
    ((char*)__xlx_apatb_param_bias1)[i*4+3] = __xlx_bias1_output_buffer[i].range(31, 24).to_uint();
  }
// print __xlx_apatb_param_in_qk
  sc_bv<32>*__xlx_in_qk_output_buffer = new sc_bv<32>[__xlx_size_param_in_qk];
  for (int i = 0; i < __xlx_size_param_in_qk; ++i) {
    __xlx_in_qk_output_buffer[i] = __xlx_norm1_mean_norm1_var_norm1_weight_norm1_bias_afterPad_afterRearrangeX_afterPad1_afterConv1_kernel1_bias1_in_qk_in_q_in_k_afterQKMultiplication_afterSoftmax_afterRearrangeX2_afterQKXMultiplication_afterRearrangeQKX_afterPad2_afterConv2_kernel2_bias2_afterAct2_QKV_buffer_out__input_buffer[i+__xlx_offset_param_in_qk];
  }
  for (int i = 0; i < __xlx_size_param_in_qk; ++i) {
    ((char*)__xlx_apatb_param_in_qk)[i*4+0] = __xlx_in_qk_output_buffer[i].range(7, 0).to_uint();
    ((char*)__xlx_apatb_param_in_qk)[i*4+1] = __xlx_in_qk_output_buffer[i].range(15, 8).to_uint();
    ((char*)__xlx_apatb_param_in_qk)[i*4+2] = __xlx_in_qk_output_buffer[i].range(23, 16).to_uint();
    ((char*)__xlx_apatb_param_in_qk)[i*4+3] = __xlx_in_qk_output_buffer[i].range(31, 24).to_uint();
  }
// print __xlx_apatb_param_in_q
  sc_bv<32>*__xlx_in_q_output_buffer = new sc_bv<32>[__xlx_size_param_in_q];
  for (int i = 0; i < __xlx_size_param_in_q; ++i) {
    __xlx_in_q_output_buffer[i] = __xlx_norm1_mean_norm1_var_norm1_weight_norm1_bias_afterPad_afterRearrangeX_afterPad1_afterConv1_kernel1_bias1_in_qk_in_q_in_k_afterQKMultiplication_afterSoftmax_afterRearrangeX2_afterQKXMultiplication_afterRearrangeQKX_afterPad2_afterConv2_kernel2_bias2_afterAct2_QKV_buffer_out__input_buffer[i+__xlx_offset_param_in_q];
  }
  for (int i = 0; i < __xlx_size_param_in_q; ++i) {
    ((char*)__xlx_apatb_param_in_q)[i*4+0] = __xlx_in_q_output_buffer[i].range(7, 0).to_uint();
    ((char*)__xlx_apatb_param_in_q)[i*4+1] = __xlx_in_q_output_buffer[i].range(15, 8).to_uint();
    ((char*)__xlx_apatb_param_in_q)[i*4+2] = __xlx_in_q_output_buffer[i].range(23, 16).to_uint();
    ((char*)__xlx_apatb_param_in_q)[i*4+3] = __xlx_in_q_output_buffer[i].range(31, 24).to_uint();
  }
// print __xlx_apatb_param_in_k
  sc_bv<32>*__xlx_in_k_output_buffer = new sc_bv<32>[__xlx_size_param_in_k];
  for (int i = 0; i < __xlx_size_param_in_k; ++i) {
    __xlx_in_k_output_buffer[i] = __xlx_norm1_mean_norm1_var_norm1_weight_norm1_bias_afterPad_afterRearrangeX_afterPad1_afterConv1_kernel1_bias1_in_qk_in_q_in_k_afterQKMultiplication_afterSoftmax_afterRearrangeX2_afterQKXMultiplication_afterRearrangeQKX_afterPad2_afterConv2_kernel2_bias2_afterAct2_QKV_buffer_out__input_buffer[i+__xlx_offset_param_in_k];
  }
  for (int i = 0; i < __xlx_size_param_in_k; ++i) {
    ((char*)__xlx_apatb_param_in_k)[i*4+0] = __xlx_in_k_output_buffer[i].range(7, 0).to_uint();
    ((char*)__xlx_apatb_param_in_k)[i*4+1] = __xlx_in_k_output_buffer[i].range(15, 8).to_uint();
    ((char*)__xlx_apatb_param_in_k)[i*4+2] = __xlx_in_k_output_buffer[i].range(23, 16).to_uint();
    ((char*)__xlx_apatb_param_in_k)[i*4+3] = __xlx_in_k_output_buffer[i].range(31, 24).to_uint();
  }
// print __xlx_apatb_param_afterQKMultiplication
  sc_bv<32>*__xlx_afterQKMultiplication_output_buffer = new sc_bv<32>[__xlx_size_param_afterQKMultiplication];
  for (int i = 0; i < __xlx_size_param_afterQKMultiplication; ++i) {
    __xlx_afterQKMultiplication_output_buffer[i] = __xlx_norm1_mean_norm1_var_norm1_weight_norm1_bias_afterPad_afterRearrangeX_afterPad1_afterConv1_kernel1_bias1_in_qk_in_q_in_k_afterQKMultiplication_afterSoftmax_afterRearrangeX2_afterQKXMultiplication_afterRearrangeQKX_afterPad2_afterConv2_kernel2_bias2_afterAct2_QKV_buffer_out__input_buffer[i+__xlx_offset_param_afterQKMultiplication];
  }
  for (int i = 0; i < __xlx_size_param_afterQKMultiplication; ++i) {
    ((char*)__xlx_apatb_param_afterQKMultiplication)[i*4+0] = __xlx_afterQKMultiplication_output_buffer[i].range(7, 0).to_uint();
    ((char*)__xlx_apatb_param_afterQKMultiplication)[i*4+1] = __xlx_afterQKMultiplication_output_buffer[i].range(15, 8).to_uint();
    ((char*)__xlx_apatb_param_afterQKMultiplication)[i*4+2] = __xlx_afterQKMultiplication_output_buffer[i].range(23, 16).to_uint();
    ((char*)__xlx_apatb_param_afterQKMultiplication)[i*4+3] = __xlx_afterQKMultiplication_output_buffer[i].range(31, 24).to_uint();
  }
// print __xlx_apatb_param_afterSoftmax
  sc_bv<32>*__xlx_afterSoftmax_output_buffer = new sc_bv<32>[__xlx_size_param_afterSoftmax];
  for (int i = 0; i < __xlx_size_param_afterSoftmax; ++i) {
    __xlx_afterSoftmax_output_buffer[i] = __xlx_norm1_mean_norm1_var_norm1_weight_norm1_bias_afterPad_afterRearrangeX_afterPad1_afterConv1_kernel1_bias1_in_qk_in_q_in_k_afterQKMultiplication_afterSoftmax_afterRearrangeX2_afterQKXMultiplication_afterRearrangeQKX_afterPad2_afterConv2_kernel2_bias2_afterAct2_QKV_buffer_out__input_buffer[i+__xlx_offset_param_afterSoftmax];
  }
  for (int i = 0; i < __xlx_size_param_afterSoftmax; ++i) {
    ((char*)__xlx_apatb_param_afterSoftmax)[i*4+0] = __xlx_afterSoftmax_output_buffer[i].range(7, 0).to_uint();
    ((char*)__xlx_apatb_param_afterSoftmax)[i*4+1] = __xlx_afterSoftmax_output_buffer[i].range(15, 8).to_uint();
    ((char*)__xlx_apatb_param_afterSoftmax)[i*4+2] = __xlx_afterSoftmax_output_buffer[i].range(23, 16).to_uint();
    ((char*)__xlx_apatb_param_afterSoftmax)[i*4+3] = __xlx_afterSoftmax_output_buffer[i].range(31, 24).to_uint();
  }
// print __xlx_apatb_param_afterRearrangeX2
  sc_bv<32>*__xlx_afterRearrangeX2_output_buffer = new sc_bv<32>[__xlx_size_param_afterRearrangeX2];
  for (int i = 0; i < __xlx_size_param_afterRearrangeX2; ++i) {
    __xlx_afterRearrangeX2_output_buffer[i] = __xlx_norm1_mean_norm1_var_norm1_weight_norm1_bias_afterPad_afterRearrangeX_afterPad1_afterConv1_kernel1_bias1_in_qk_in_q_in_k_afterQKMultiplication_afterSoftmax_afterRearrangeX2_afterQKXMultiplication_afterRearrangeQKX_afterPad2_afterConv2_kernel2_bias2_afterAct2_QKV_buffer_out__input_buffer[i+__xlx_offset_param_afterRearrangeX2];
  }
  for (int i = 0; i < __xlx_size_param_afterRearrangeX2; ++i) {
    ((char*)__xlx_apatb_param_afterRearrangeX2)[i*4+0] = __xlx_afterRearrangeX2_output_buffer[i].range(7, 0).to_uint();
    ((char*)__xlx_apatb_param_afterRearrangeX2)[i*4+1] = __xlx_afterRearrangeX2_output_buffer[i].range(15, 8).to_uint();
    ((char*)__xlx_apatb_param_afterRearrangeX2)[i*4+2] = __xlx_afterRearrangeX2_output_buffer[i].range(23, 16).to_uint();
    ((char*)__xlx_apatb_param_afterRearrangeX2)[i*4+3] = __xlx_afterRearrangeX2_output_buffer[i].range(31, 24).to_uint();
  }
// print __xlx_apatb_param_afterQKXMultiplication
  sc_bv<32>*__xlx_afterQKXMultiplication_output_buffer = new sc_bv<32>[__xlx_size_param_afterQKXMultiplication];
  for (int i = 0; i < __xlx_size_param_afterQKXMultiplication; ++i) {
    __xlx_afterQKXMultiplication_output_buffer[i] = __xlx_norm1_mean_norm1_var_norm1_weight_norm1_bias_afterPad_afterRearrangeX_afterPad1_afterConv1_kernel1_bias1_in_qk_in_q_in_k_afterQKMultiplication_afterSoftmax_afterRearrangeX2_afterQKXMultiplication_afterRearrangeQKX_afterPad2_afterConv2_kernel2_bias2_afterAct2_QKV_buffer_out__input_buffer[i+__xlx_offset_param_afterQKXMultiplication];
  }
  for (int i = 0; i < __xlx_size_param_afterQKXMultiplication; ++i) {
    ((char*)__xlx_apatb_param_afterQKXMultiplication)[i*4+0] = __xlx_afterQKXMultiplication_output_buffer[i].range(7, 0).to_uint();
    ((char*)__xlx_apatb_param_afterQKXMultiplication)[i*4+1] = __xlx_afterQKXMultiplication_output_buffer[i].range(15, 8).to_uint();
    ((char*)__xlx_apatb_param_afterQKXMultiplication)[i*4+2] = __xlx_afterQKXMultiplication_output_buffer[i].range(23, 16).to_uint();
    ((char*)__xlx_apatb_param_afterQKXMultiplication)[i*4+3] = __xlx_afterQKXMultiplication_output_buffer[i].range(31, 24).to_uint();
  }
// print __xlx_apatb_param_afterRearrangeQKX
  sc_bv<32>*__xlx_afterRearrangeQKX_output_buffer = new sc_bv<32>[__xlx_size_param_afterRearrangeQKX];
  for (int i = 0; i < __xlx_size_param_afterRearrangeQKX; ++i) {
    __xlx_afterRearrangeQKX_output_buffer[i] = __xlx_norm1_mean_norm1_var_norm1_weight_norm1_bias_afterPad_afterRearrangeX_afterPad1_afterConv1_kernel1_bias1_in_qk_in_q_in_k_afterQKMultiplication_afterSoftmax_afterRearrangeX2_afterQKXMultiplication_afterRearrangeQKX_afterPad2_afterConv2_kernel2_bias2_afterAct2_QKV_buffer_out__input_buffer[i+__xlx_offset_param_afterRearrangeQKX];
  }
  for (int i = 0; i < __xlx_size_param_afterRearrangeQKX; ++i) {
    ((char*)__xlx_apatb_param_afterRearrangeQKX)[i*4+0] = __xlx_afterRearrangeQKX_output_buffer[i].range(7, 0).to_uint();
    ((char*)__xlx_apatb_param_afterRearrangeQKX)[i*4+1] = __xlx_afterRearrangeQKX_output_buffer[i].range(15, 8).to_uint();
    ((char*)__xlx_apatb_param_afterRearrangeQKX)[i*4+2] = __xlx_afterRearrangeQKX_output_buffer[i].range(23, 16).to_uint();
    ((char*)__xlx_apatb_param_afterRearrangeQKX)[i*4+3] = __xlx_afterRearrangeQKX_output_buffer[i].range(31, 24).to_uint();
  }
// print __xlx_apatb_param_afterPad2
  sc_bv<32>*__xlx_afterPad2_output_buffer = new sc_bv<32>[__xlx_size_param_afterPad2];
  for (int i = 0; i < __xlx_size_param_afterPad2; ++i) {
    __xlx_afterPad2_output_buffer[i] = __xlx_norm1_mean_norm1_var_norm1_weight_norm1_bias_afterPad_afterRearrangeX_afterPad1_afterConv1_kernel1_bias1_in_qk_in_q_in_k_afterQKMultiplication_afterSoftmax_afterRearrangeX2_afterQKXMultiplication_afterRearrangeQKX_afterPad2_afterConv2_kernel2_bias2_afterAct2_QKV_buffer_out__input_buffer[i+__xlx_offset_param_afterPad2];
  }
  for (int i = 0; i < __xlx_size_param_afterPad2; ++i) {
    ((char*)__xlx_apatb_param_afterPad2)[i*4+0] = __xlx_afterPad2_output_buffer[i].range(7, 0).to_uint();
    ((char*)__xlx_apatb_param_afterPad2)[i*4+1] = __xlx_afterPad2_output_buffer[i].range(15, 8).to_uint();
    ((char*)__xlx_apatb_param_afterPad2)[i*4+2] = __xlx_afterPad2_output_buffer[i].range(23, 16).to_uint();
    ((char*)__xlx_apatb_param_afterPad2)[i*4+3] = __xlx_afterPad2_output_buffer[i].range(31, 24).to_uint();
  }
// print __xlx_apatb_param_afterConv2
  sc_bv<32>*__xlx_afterConv2_output_buffer = new sc_bv<32>[__xlx_size_param_afterConv2];
  for (int i = 0; i < __xlx_size_param_afterConv2; ++i) {
    __xlx_afterConv2_output_buffer[i] = __xlx_norm1_mean_norm1_var_norm1_weight_norm1_bias_afterPad_afterRearrangeX_afterPad1_afterConv1_kernel1_bias1_in_qk_in_q_in_k_afterQKMultiplication_afterSoftmax_afterRearrangeX2_afterQKXMultiplication_afterRearrangeQKX_afterPad2_afterConv2_kernel2_bias2_afterAct2_QKV_buffer_out__input_buffer[i+__xlx_offset_param_afterConv2];
  }
  for (int i = 0; i < __xlx_size_param_afterConv2; ++i) {
    ((char*)__xlx_apatb_param_afterConv2)[i*4+0] = __xlx_afterConv2_output_buffer[i].range(7, 0).to_uint();
    ((char*)__xlx_apatb_param_afterConv2)[i*4+1] = __xlx_afterConv2_output_buffer[i].range(15, 8).to_uint();
    ((char*)__xlx_apatb_param_afterConv2)[i*4+2] = __xlx_afterConv2_output_buffer[i].range(23, 16).to_uint();
    ((char*)__xlx_apatb_param_afterConv2)[i*4+3] = __xlx_afterConv2_output_buffer[i].range(31, 24).to_uint();
  }
// print __xlx_apatb_param_kernel2
  sc_bv<32>*__xlx_kernel2_output_buffer = new sc_bv<32>[__xlx_size_param_kernel2];
  for (int i = 0; i < __xlx_size_param_kernel2; ++i) {
    __xlx_kernel2_output_buffer[i] = __xlx_norm1_mean_norm1_var_norm1_weight_norm1_bias_afterPad_afterRearrangeX_afterPad1_afterConv1_kernel1_bias1_in_qk_in_q_in_k_afterQKMultiplication_afterSoftmax_afterRearrangeX2_afterQKXMultiplication_afterRearrangeQKX_afterPad2_afterConv2_kernel2_bias2_afterAct2_QKV_buffer_out__input_buffer[i+__xlx_offset_param_kernel2];
  }
  for (int i = 0; i < __xlx_size_param_kernel2; ++i) {
    ((char*)__xlx_apatb_param_kernel2)[i*4+0] = __xlx_kernel2_output_buffer[i].range(7, 0).to_uint();
    ((char*)__xlx_apatb_param_kernel2)[i*4+1] = __xlx_kernel2_output_buffer[i].range(15, 8).to_uint();
    ((char*)__xlx_apatb_param_kernel2)[i*4+2] = __xlx_kernel2_output_buffer[i].range(23, 16).to_uint();
    ((char*)__xlx_apatb_param_kernel2)[i*4+3] = __xlx_kernel2_output_buffer[i].range(31, 24).to_uint();
  }
// print __xlx_apatb_param_bias2
  sc_bv<32>*__xlx_bias2_output_buffer = new sc_bv<32>[__xlx_size_param_bias2];
  for (int i = 0; i < __xlx_size_param_bias2; ++i) {
    __xlx_bias2_output_buffer[i] = __xlx_norm1_mean_norm1_var_norm1_weight_norm1_bias_afterPad_afterRearrangeX_afterPad1_afterConv1_kernel1_bias1_in_qk_in_q_in_k_afterQKMultiplication_afterSoftmax_afterRearrangeX2_afterQKXMultiplication_afterRearrangeQKX_afterPad2_afterConv2_kernel2_bias2_afterAct2_QKV_buffer_out__input_buffer[i+__xlx_offset_param_bias2];
  }
  for (int i = 0; i < __xlx_size_param_bias2; ++i) {
    ((char*)__xlx_apatb_param_bias2)[i*4+0] = __xlx_bias2_output_buffer[i].range(7, 0).to_uint();
    ((char*)__xlx_apatb_param_bias2)[i*4+1] = __xlx_bias2_output_buffer[i].range(15, 8).to_uint();
    ((char*)__xlx_apatb_param_bias2)[i*4+2] = __xlx_bias2_output_buffer[i].range(23, 16).to_uint();
    ((char*)__xlx_apatb_param_bias2)[i*4+3] = __xlx_bias2_output_buffer[i].range(31, 24).to_uint();
  }
// print __xlx_apatb_param_afterAct2
  sc_bv<32>*__xlx_afterAct2_output_buffer = new sc_bv<32>[__xlx_size_param_afterAct2];
  for (int i = 0; i < __xlx_size_param_afterAct2; ++i) {
    __xlx_afterAct2_output_buffer[i] = __xlx_norm1_mean_norm1_var_norm1_weight_norm1_bias_afterPad_afterRearrangeX_afterPad1_afterConv1_kernel1_bias1_in_qk_in_q_in_k_afterQKMultiplication_afterSoftmax_afterRearrangeX2_afterQKXMultiplication_afterRearrangeQKX_afterPad2_afterConv2_kernel2_bias2_afterAct2_QKV_buffer_out__input_buffer[i+__xlx_offset_param_afterAct2];
  }
  for (int i = 0; i < __xlx_size_param_afterAct2; ++i) {
    ((char*)__xlx_apatb_param_afterAct2)[i*4+0] = __xlx_afterAct2_output_buffer[i].range(7, 0).to_uint();
    ((char*)__xlx_apatb_param_afterAct2)[i*4+1] = __xlx_afterAct2_output_buffer[i].range(15, 8).to_uint();
    ((char*)__xlx_apatb_param_afterAct2)[i*4+2] = __xlx_afterAct2_output_buffer[i].range(23, 16).to_uint();
    ((char*)__xlx_apatb_param_afterAct2)[i*4+3] = __xlx_afterAct2_output_buffer[i].range(31, 24).to_uint();
  }
// print __xlx_apatb_param_QKV
  sc_bv<32>*__xlx_QKV_output_buffer = new sc_bv<32>[__xlx_size_param_QKV];
  for (int i = 0; i < __xlx_size_param_QKV; ++i) {
    __xlx_QKV_output_buffer[i] = __xlx_norm1_mean_norm1_var_norm1_weight_norm1_bias_afterPad_afterRearrangeX_afterPad1_afterConv1_kernel1_bias1_in_qk_in_q_in_k_afterQKMultiplication_afterSoftmax_afterRearrangeX2_afterQKXMultiplication_afterRearrangeQKX_afterPad2_afterConv2_kernel2_bias2_afterAct2_QKV_buffer_out__input_buffer[i+__xlx_offset_param_QKV];
  }
  for (int i = 0; i < __xlx_size_param_QKV; ++i) {
    ((char*)__xlx_apatb_param_QKV)[i*4+0] = __xlx_QKV_output_buffer[i].range(7, 0).to_uint();
    ((char*)__xlx_apatb_param_QKV)[i*4+1] = __xlx_QKV_output_buffer[i].range(15, 8).to_uint();
    ((char*)__xlx_apatb_param_QKV)[i*4+2] = __xlx_QKV_output_buffer[i].range(23, 16).to_uint();
    ((char*)__xlx_apatb_param_QKV)[i*4+3] = __xlx_QKV_output_buffer[i].range(31, 24).to_uint();
  }
// print __xlx_apatb_param_buffer_out
  sc_bv<32>*__xlx_buffer_out_output_buffer = new sc_bv<32>[__xlx_size_param_buffer_out];
  for (int i = 0; i < __xlx_size_param_buffer_out; ++i) {
    __xlx_buffer_out_output_buffer[i] = __xlx_norm1_mean_norm1_var_norm1_weight_norm1_bias_afterPad_afterRearrangeX_afterPad1_afterConv1_kernel1_bias1_in_qk_in_q_in_k_afterQKMultiplication_afterSoftmax_afterRearrangeX2_afterQKXMultiplication_afterRearrangeQKX_afterPad2_afterConv2_kernel2_bias2_afterAct2_QKV_buffer_out__input_buffer[i+__xlx_offset_param_buffer_out];
  }
  for (int i = 0; i < __xlx_size_param_buffer_out; ++i) {
    ((char*)__xlx_apatb_param_buffer_out)[i*4+0] = __xlx_buffer_out_output_buffer[i].range(7, 0).to_uint();
    ((char*)__xlx_apatb_param_buffer_out)[i*4+1] = __xlx_buffer_out_output_buffer[i].range(15, 8).to_uint();
    ((char*)__xlx_apatb_param_buffer_out)[i*4+2] = __xlx_buffer_out_output_buffer[i].range(23, 16).to_uint();
    ((char*)__xlx_apatb_param_buffer_out)[i*4+3] = __xlx_buffer_out_output_buffer[i].range(31, 24).to_uint();
  }
}
