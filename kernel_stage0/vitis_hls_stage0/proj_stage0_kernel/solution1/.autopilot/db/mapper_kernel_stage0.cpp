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
extern "C" void kernel_stage0(int*, int*, int*, int*, int*, int, int, int, int, int, int, int, int, int, int, int, int, int, int, int, int, int, int, int, int, int, int, int, int, int, int, int, int, int);
extern "C" void apatb_kernel_stage0_hw(volatile void * __xlx_apatb_param_X_data, volatile void * __xlx_apatb_param_msp_conv_weight, volatile void * __xlx_apatb_param_msp_conv_bias, volatile void * __xlx_apatb_param_msp_norm_weight, volatile void * __xlx_apatb_param_msp_norm_bias, volatile void * __xlx_apatb_param_msp_norm_running_mean, volatile void * __xlx_apatb_param_msp_norm_running_var, volatile void * __xlx_apatb_param_dw_conv_weight, volatile void * __xlx_apatb_param_norm_1_weight, volatile void * __xlx_apatb_param_norm_1_bias, volatile void * __xlx_apatb_param_norm_1_running_mean, volatile void * __xlx_apatb_param_norm_1_running_var, volatile void * __xlx_apatb_param_se_conv_reduce_weight, volatile void * __xlx_apatb_param_se_conv_reduce_bias, volatile void * __xlx_apatb_param_se_conv_expand_weight, volatile void * __xlx_apatb_param_se_conv_expand_bias, volatile void * __xlx_apatb_param_proj_conv_weight, volatile void * __xlx_apatb_param_Y_msp_conv, volatile void * __xlx_apatb_param_Y_msp_norm, volatile void * __xlx_apatb_param_Y_dw_conv, volatile void * __xlx_apatb_param_Y_dw_norm, volatile void * __xlx_apatb_param_Y_dw_act, volatile void * __xlx_apatb_param_Y_mean, volatile void * __xlx_apatb_param_Y_reduce, volatile void * __xlx_apatb_param_Y_relu, volatile void * __xlx_apatb_param_Y_expand, volatile void * __xlx_apatb_param_Y_sigmoid, volatile void * __xlx_apatb_param_Y_se, volatile void * __xlx_apatb_param_Y_proj) {
  // Collect __xlx_X_data_Y_dw_norm_Y_relu_Y_proj__tmp_vec
  vector<sc_bv<32> >__xlx_X_data_Y_dw_norm_Y_relu_Y_proj__tmp_vec;
  for (int j = 0, e = 150528; j != e; ++j) {
    sc_bv<32> _xlx_tmp_sc;
    _xlx_tmp_sc.range(7, 0) = ((char*)__xlx_apatb_param_X_data)[j*4+0];
    _xlx_tmp_sc.range(15, 8) = ((char*)__xlx_apatb_param_X_data)[j*4+1];
    _xlx_tmp_sc.range(23, 16) = ((char*)__xlx_apatb_param_X_data)[j*4+2];
    _xlx_tmp_sc.range(31, 24) = ((char*)__xlx_apatb_param_X_data)[j*4+3];
    __xlx_X_data_Y_dw_norm_Y_relu_Y_proj__tmp_vec.push_back(_xlx_tmp_sc);
  }
  int __xlx_size_param_X_data = 150528;
  int __xlx_offset_param_X_data = 0;
  int __xlx_offset_byte_param_X_data = 0*4;
  for (int j = 0, e = 301056; j != e; ++j) {
    sc_bv<32> _xlx_tmp_sc;
    _xlx_tmp_sc.range(7, 0) = ((char*)__xlx_apatb_param_Y_dw_norm)[j*4+0];
    _xlx_tmp_sc.range(15, 8) = ((char*)__xlx_apatb_param_Y_dw_norm)[j*4+1];
    _xlx_tmp_sc.range(23, 16) = ((char*)__xlx_apatb_param_Y_dw_norm)[j*4+2];
    _xlx_tmp_sc.range(31, 24) = ((char*)__xlx_apatb_param_Y_dw_norm)[j*4+3];
    __xlx_X_data_Y_dw_norm_Y_relu_Y_proj__tmp_vec.push_back(_xlx_tmp_sc);
  }
  int __xlx_size_param_Y_dw_norm = 301056;
  int __xlx_offset_param_Y_dw_norm = 150528;
  int __xlx_offset_byte_param_Y_dw_norm = 150528*4;
  for (int j = 0, e = 24; j != e; ++j) {
    sc_bv<32> _xlx_tmp_sc;
    _xlx_tmp_sc.range(7, 0) = ((char*)__xlx_apatb_param_Y_relu)[j*4+0];
    _xlx_tmp_sc.range(15, 8) = ((char*)__xlx_apatb_param_Y_relu)[j*4+1];
    _xlx_tmp_sc.range(23, 16) = ((char*)__xlx_apatb_param_Y_relu)[j*4+2];
    _xlx_tmp_sc.range(31, 24) = ((char*)__xlx_apatb_param_Y_relu)[j*4+3];
    __xlx_X_data_Y_dw_norm_Y_relu_Y_proj__tmp_vec.push_back(_xlx_tmp_sc);
  }
  int __xlx_size_param_Y_relu = 24;
  int __xlx_offset_param_Y_relu = 451584;
  int __xlx_offset_byte_param_Y_relu = 451584*4;
  for (int j = 0, e = 301056; j != e; ++j) {
    sc_bv<32> _xlx_tmp_sc;
    _xlx_tmp_sc.range(7, 0) = ((char*)__xlx_apatb_param_Y_proj)[j*4+0];
    _xlx_tmp_sc.range(15, 8) = ((char*)__xlx_apatb_param_Y_proj)[j*4+1];
    _xlx_tmp_sc.range(23, 16) = ((char*)__xlx_apatb_param_Y_proj)[j*4+2];
    _xlx_tmp_sc.range(31, 24) = ((char*)__xlx_apatb_param_Y_proj)[j*4+3];
    __xlx_X_data_Y_dw_norm_Y_relu_Y_proj__tmp_vec.push_back(_xlx_tmp_sc);
  }
  int __xlx_size_param_Y_proj = 301056;
  int __xlx_offset_param_Y_proj = 451608;
  int __xlx_offset_byte_param_Y_proj = 451608*4;
  int* __xlx_X_data_Y_dw_norm_Y_relu_Y_proj__input_buffer= new int[__xlx_X_data_Y_dw_norm_Y_relu_Y_proj__tmp_vec.size()];
  for (int i = 0; i < __xlx_X_data_Y_dw_norm_Y_relu_Y_proj__tmp_vec.size(); ++i) {
    __xlx_X_data_Y_dw_norm_Y_relu_Y_proj__input_buffer[i] = __xlx_X_data_Y_dw_norm_Y_relu_Y_proj__tmp_vec[i].range(31, 0).to_uint64();
  }
  // Collect __xlx_msp_conv_weight_msp_conv_bias_msp_norm_weight_msp_norm_bias_msp_norm_running_mean_msp_norm_running_var_dw_conv_weight_norm_1_weight_norm_1_bias_norm_1_running_mean_norm_1_running_var_se_conv_reduce_weight_se_conv_reduce_bias_se_conv_expand_weight_se_conv_expand_bias_proj_conv_weight__tmp_vec
  vector<sc_bv<32> >__xlx_msp_conv_weight_msp_conv_bias_msp_norm_weight_msp_norm_bias_msp_norm_running_mean_msp_norm_running_var_dw_conv_weight_norm_1_weight_norm_1_bias_norm_1_running_mean_norm_1_running_var_se_conv_reduce_weight_se_conv_reduce_bias_se_conv_expand_weight_se_conv_expand_bias_proj_conv_weight__tmp_vec;
  for (int j = 0, e = 648; j != e; ++j) {
    sc_bv<32> _xlx_tmp_sc;
    _xlx_tmp_sc.range(7, 0) = ((char*)__xlx_apatb_param_msp_conv_weight)[j*4+0];
    _xlx_tmp_sc.range(15, 8) = ((char*)__xlx_apatb_param_msp_conv_weight)[j*4+1];
    _xlx_tmp_sc.range(23, 16) = ((char*)__xlx_apatb_param_msp_conv_weight)[j*4+2];
    _xlx_tmp_sc.range(31, 24) = ((char*)__xlx_apatb_param_msp_conv_weight)[j*4+3];
    __xlx_msp_conv_weight_msp_conv_bias_msp_norm_weight_msp_norm_bias_msp_norm_running_mean_msp_norm_running_var_dw_conv_weight_norm_1_weight_norm_1_bias_norm_1_running_mean_norm_1_running_var_se_conv_reduce_weight_se_conv_reduce_bias_se_conv_expand_weight_se_conv_expand_bias_proj_conv_weight__tmp_vec.push_back(_xlx_tmp_sc);
  }
  int __xlx_size_param_msp_conv_weight = 648;
  int __xlx_offset_param_msp_conv_weight = 0;
  int __xlx_offset_byte_param_msp_conv_weight = 0*4;
  for (int j = 0, e = 24; j != e; ++j) {
    sc_bv<32> _xlx_tmp_sc;
    _xlx_tmp_sc.range(7, 0) = ((char*)__xlx_apatb_param_msp_conv_bias)[j*4+0];
    _xlx_tmp_sc.range(15, 8) = ((char*)__xlx_apatb_param_msp_conv_bias)[j*4+1];
    _xlx_tmp_sc.range(23, 16) = ((char*)__xlx_apatb_param_msp_conv_bias)[j*4+2];
    _xlx_tmp_sc.range(31, 24) = ((char*)__xlx_apatb_param_msp_conv_bias)[j*4+3];
    __xlx_msp_conv_weight_msp_conv_bias_msp_norm_weight_msp_norm_bias_msp_norm_running_mean_msp_norm_running_var_dw_conv_weight_norm_1_weight_norm_1_bias_norm_1_running_mean_norm_1_running_var_se_conv_reduce_weight_se_conv_reduce_bias_se_conv_expand_weight_se_conv_expand_bias_proj_conv_weight__tmp_vec.push_back(_xlx_tmp_sc);
  }
  int __xlx_size_param_msp_conv_bias = 24;
  int __xlx_offset_param_msp_conv_bias = 648;
  int __xlx_offset_byte_param_msp_conv_bias = 648*4;
  for (int j = 0, e = 24; j != e; ++j) {
    sc_bv<32> _xlx_tmp_sc;
    _xlx_tmp_sc.range(7, 0) = ((char*)__xlx_apatb_param_msp_norm_weight)[j*4+0];
    _xlx_tmp_sc.range(15, 8) = ((char*)__xlx_apatb_param_msp_norm_weight)[j*4+1];
    _xlx_tmp_sc.range(23, 16) = ((char*)__xlx_apatb_param_msp_norm_weight)[j*4+2];
    _xlx_tmp_sc.range(31, 24) = ((char*)__xlx_apatb_param_msp_norm_weight)[j*4+3];
    __xlx_msp_conv_weight_msp_conv_bias_msp_norm_weight_msp_norm_bias_msp_norm_running_mean_msp_norm_running_var_dw_conv_weight_norm_1_weight_norm_1_bias_norm_1_running_mean_norm_1_running_var_se_conv_reduce_weight_se_conv_reduce_bias_se_conv_expand_weight_se_conv_expand_bias_proj_conv_weight__tmp_vec.push_back(_xlx_tmp_sc);
  }
  int __xlx_size_param_msp_norm_weight = 24;
  int __xlx_offset_param_msp_norm_weight = 672;
  int __xlx_offset_byte_param_msp_norm_weight = 672*4;
  for (int j = 0, e = 24; j != e; ++j) {
    sc_bv<32> _xlx_tmp_sc;
    _xlx_tmp_sc.range(7, 0) = ((char*)__xlx_apatb_param_msp_norm_bias)[j*4+0];
    _xlx_tmp_sc.range(15, 8) = ((char*)__xlx_apatb_param_msp_norm_bias)[j*4+1];
    _xlx_tmp_sc.range(23, 16) = ((char*)__xlx_apatb_param_msp_norm_bias)[j*4+2];
    _xlx_tmp_sc.range(31, 24) = ((char*)__xlx_apatb_param_msp_norm_bias)[j*4+3];
    __xlx_msp_conv_weight_msp_conv_bias_msp_norm_weight_msp_norm_bias_msp_norm_running_mean_msp_norm_running_var_dw_conv_weight_norm_1_weight_norm_1_bias_norm_1_running_mean_norm_1_running_var_se_conv_reduce_weight_se_conv_reduce_bias_se_conv_expand_weight_se_conv_expand_bias_proj_conv_weight__tmp_vec.push_back(_xlx_tmp_sc);
  }
  int __xlx_size_param_msp_norm_bias = 24;
  int __xlx_offset_param_msp_norm_bias = 696;
  int __xlx_offset_byte_param_msp_norm_bias = 696*4;
  for (int j = 0, e = 24; j != e; ++j) {
    sc_bv<32> _xlx_tmp_sc;
    _xlx_tmp_sc.range(7, 0) = ((char*)__xlx_apatb_param_msp_norm_running_mean)[j*4+0];
    _xlx_tmp_sc.range(15, 8) = ((char*)__xlx_apatb_param_msp_norm_running_mean)[j*4+1];
    _xlx_tmp_sc.range(23, 16) = ((char*)__xlx_apatb_param_msp_norm_running_mean)[j*4+2];
    _xlx_tmp_sc.range(31, 24) = ((char*)__xlx_apatb_param_msp_norm_running_mean)[j*4+3];
    __xlx_msp_conv_weight_msp_conv_bias_msp_norm_weight_msp_norm_bias_msp_norm_running_mean_msp_norm_running_var_dw_conv_weight_norm_1_weight_norm_1_bias_norm_1_running_mean_norm_1_running_var_se_conv_reduce_weight_se_conv_reduce_bias_se_conv_expand_weight_se_conv_expand_bias_proj_conv_weight__tmp_vec.push_back(_xlx_tmp_sc);
  }
  int __xlx_size_param_msp_norm_running_mean = 24;
  int __xlx_offset_param_msp_norm_running_mean = 720;
  int __xlx_offset_byte_param_msp_norm_running_mean = 720*4;
  for (int j = 0, e = 24; j != e; ++j) {
    sc_bv<32> _xlx_tmp_sc;
    _xlx_tmp_sc.range(7, 0) = ((char*)__xlx_apatb_param_msp_norm_running_var)[j*4+0];
    _xlx_tmp_sc.range(15, 8) = ((char*)__xlx_apatb_param_msp_norm_running_var)[j*4+1];
    _xlx_tmp_sc.range(23, 16) = ((char*)__xlx_apatb_param_msp_norm_running_var)[j*4+2];
    _xlx_tmp_sc.range(31, 24) = ((char*)__xlx_apatb_param_msp_norm_running_var)[j*4+3];
    __xlx_msp_conv_weight_msp_conv_bias_msp_norm_weight_msp_norm_bias_msp_norm_running_mean_msp_norm_running_var_dw_conv_weight_norm_1_weight_norm_1_bias_norm_1_running_mean_norm_1_running_var_se_conv_reduce_weight_se_conv_reduce_bias_se_conv_expand_weight_se_conv_expand_bias_proj_conv_weight__tmp_vec.push_back(_xlx_tmp_sc);
  }
  int __xlx_size_param_msp_norm_running_var = 24;
  int __xlx_offset_param_msp_norm_running_var = 744;
  int __xlx_offset_byte_param_msp_norm_running_var = 744*4;
  for (int j = 0, e = 216; j != e; ++j) {
    sc_bv<32> _xlx_tmp_sc;
    _xlx_tmp_sc.range(7, 0) = ((char*)__xlx_apatb_param_dw_conv_weight)[j*4+0];
    _xlx_tmp_sc.range(15, 8) = ((char*)__xlx_apatb_param_dw_conv_weight)[j*4+1];
    _xlx_tmp_sc.range(23, 16) = ((char*)__xlx_apatb_param_dw_conv_weight)[j*4+2];
    _xlx_tmp_sc.range(31, 24) = ((char*)__xlx_apatb_param_dw_conv_weight)[j*4+3];
    __xlx_msp_conv_weight_msp_conv_bias_msp_norm_weight_msp_norm_bias_msp_norm_running_mean_msp_norm_running_var_dw_conv_weight_norm_1_weight_norm_1_bias_norm_1_running_mean_norm_1_running_var_se_conv_reduce_weight_se_conv_reduce_bias_se_conv_expand_weight_se_conv_expand_bias_proj_conv_weight__tmp_vec.push_back(_xlx_tmp_sc);
  }
  int __xlx_size_param_dw_conv_weight = 216;
  int __xlx_offset_param_dw_conv_weight = 768;
  int __xlx_offset_byte_param_dw_conv_weight = 768*4;
  for (int j = 0, e = 24; j != e; ++j) {
    sc_bv<32> _xlx_tmp_sc;
    _xlx_tmp_sc.range(7, 0) = ((char*)__xlx_apatb_param_norm_1_weight)[j*4+0];
    _xlx_tmp_sc.range(15, 8) = ((char*)__xlx_apatb_param_norm_1_weight)[j*4+1];
    _xlx_tmp_sc.range(23, 16) = ((char*)__xlx_apatb_param_norm_1_weight)[j*4+2];
    _xlx_tmp_sc.range(31, 24) = ((char*)__xlx_apatb_param_norm_1_weight)[j*4+3];
    __xlx_msp_conv_weight_msp_conv_bias_msp_norm_weight_msp_norm_bias_msp_norm_running_mean_msp_norm_running_var_dw_conv_weight_norm_1_weight_norm_1_bias_norm_1_running_mean_norm_1_running_var_se_conv_reduce_weight_se_conv_reduce_bias_se_conv_expand_weight_se_conv_expand_bias_proj_conv_weight__tmp_vec.push_back(_xlx_tmp_sc);
  }
  int __xlx_size_param_norm_1_weight = 24;
  int __xlx_offset_param_norm_1_weight = 984;
  int __xlx_offset_byte_param_norm_1_weight = 984*4;
  for (int j = 0, e = 24; j != e; ++j) {
    sc_bv<32> _xlx_tmp_sc;
    _xlx_tmp_sc.range(7, 0) = ((char*)__xlx_apatb_param_norm_1_bias)[j*4+0];
    _xlx_tmp_sc.range(15, 8) = ((char*)__xlx_apatb_param_norm_1_bias)[j*4+1];
    _xlx_tmp_sc.range(23, 16) = ((char*)__xlx_apatb_param_norm_1_bias)[j*4+2];
    _xlx_tmp_sc.range(31, 24) = ((char*)__xlx_apatb_param_norm_1_bias)[j*4+3];
    __xlx_msp_conv_weight_msp_conv_bias_msp_norm_weight_msp_norm_bias_msp_norm_running_mean_msp_norm_running_var_dw_conv_weight_norm_1_weight_norm_1_bias_norm_1_running_mean_norm_1_running_var_se_conv_reduce_weight_se_conv_reduce_bias_se_conv_expand_weight_se_conv_expand_bias_proj_conv_weight__tmp_vec.push_back(_xlx_tmp_sc);
  }
  int __xlx_size_param_norm_1_bias = 24;
  int __xlx_offset_param_norm_1_bias = 1008;
  int __xlx_offset_byte_param_norm_1_bias = 1008*4;
  for (int j = 0, e = 24; j != e; ++j) {
    sc_bv<32> _xlx_tmp_sc;
    _xlx_tmp_sc.range(7, 0) = ((char*)__xlx_apatb_param_norm_1_running_mean)[j*4+0];
    _xlx_tmp_sc.range(15, 8) = ((char*)__xlx_apatb_param_norm_1_running_mean)[j*4+1];
    _xlx_tmp_sc.range(23, 16) = ((char*)__xlx_apatb_param_norm_1_running_mean)[j*4+2];
    _xlx_tmp_sc.range(31, 24) = ((char*)__xlx_apatb_param_norm_1_running_mean)[j*4+3];
    __xlx_msp_conv_weight_msp_conv_bias_msp_norm_weight_msp_norm_bias_msp_norm_running_mean_msp_norm_running_var_dw_conv_weight_norm_1_weight_norm_1_bias_norm_1_running_mean_norm_1_running_var_se_conv_reduce_weight_se_conv_reduce_bias_se_conv_expand_weight_se_conv_expand_bias_proj_conv_weight__tmp_vec.push_back(_xlx_tmp_sc);
  }
  int __xlx_size_param_norm_1_running_mean = 24;
  int __xlx_offset_param_norm_1_running_mean = 1032;
  int __xlx_offset_byte_param_norm_1_running_mean = 1032*4;
  for (int j = 0, e = 24; j != e; ++j) {
    sc_bv<32> _xlx_tmp_sc;
    _xlx_tmp_sc.range(7, 0) = ((char*)__xlx_apatb_param_norm_1_running_var)[j*4+0];
    _xlx_tmp_sc.range(15, 8) = ((char*)__xlx_apatb_param_norm_1_running_var)[j*4+1];
    _xlx_tmp_sc.range(23, 16) = ((char*)__xlx_apatb_param_norm_1_running_var)[j*4+2];
    _xlx_tmp_sc.range(31, 24) = ((char*)__xlx_apatb_param_norm_1_running_var)[j*4+3];
    __xlx_msp_conv_weight_msp_conv_bias_msp_norm_weight_msp_norm_bias_msp_norm_running_mean_msp_norm_running_var_dw_conv_weight_norm_1_weight_norm_1_bias_norm_1_running_mean_norm_1_running_var_se_conv_reduce_weight_se_conv_reduce_bias_se_conv_expand_weight_se_conv_expand_bias_proj_conv_weight__tmp_vec.push_back(_xlx_tmp_sc);
  }
  int __xlx_size_param_norm_1_running_var = 24;
  int __xlx_offset_param_norm_1_running_var = 1056;
  int __xlx_offset_byte_param_norm_1_running_var = 1056*4;
  for (int j = 0, e = 576; j != e; ++j) {
    sc_bv<32> _xlx_tmp_sc;
    _xlx_tmp_sc.range(7, 0) = ((char*)__xlx_apatb_param_se_conv_reduce_weight)[j*4+0];
    _xlx_tmp_sc.range(15, 8) = ((char*)__xlx_apatb_param_se_conv_reduce_weight)[j*4+1];
    _xlx_tmp_sc.range(23, 16) = ((char*)__xlx_apatb_param_se_conv_reduce_weight)[j*4+2];
    _xlx_tmp_sc.range(31, 24) = ((char*)__xlx_apatb_param_se_conv_reduce_weight)[j*4+3];
    __xlx_msp_conv_weight_msp_conv_bias_msp_norm_weight_msp_norm_bias_msp_norm_running_mean_msp_norm_running_var_dw_conv_weight_norm_1_weight_norm_1_bias_norm_1_running_mean_norm_1_running_var_se_conv_reduce_weight_se_conv_reduce_bias_se_conv_expand_weight_se_conv_expand_bias_proj_conv_weight__tmp_vec.push_back(_xlx_tmp_sc);
  }
  int __xlx_size_param_se_conv_reduce_weight = 576;
  int __xlx_offset_param_se_conv_reduce_weight = 1080;
  int __xlx_offset_byte_param_se_conv_reduce_weight = 1080*4;
  for (int j = 0, e = 24; j != e; ++j) {
    sc_bv<32> _xlx_tmp_sc;
    _xlx_tmp_sc.range(7, 0) = ((char*)__xlx_apatb_param_se_conv_reduce_bias)[j*4+0];
    _xlx_tmp_sc.range(15, 8) = ((char*)__xlx_apatb_param_se_conv_reduce_bias)[j*4+1];
    _xlx_tmp_sc.range(23, 16) = ((char*)__xlx_apatb_param_se_conv_reduce_bias)[j*4+2];
    _xlx_tmp_sc.range(31, 24) = ((char*)__xlx_apatb_param_se_conv_reduce_bias)[j*4+3];
    __xlx_msp_conv_weight_msp_conv_bias_msp_norm_weight_msp_norm_bias_msp_norm_running_mean_msp_norm_running_var_dw_conv_weight_norm_1_weight_norm_1_bias_norm_1_running_mean_norm_1_running_var_se_conv_reduce_weight_se_conv_reduce_bias_se_conv_expand_weight_se_conv_expand_bias_proj_conv_weight__tmp_vec.push_back(_xlx_tmp_sc);
  }
  int __xlx_size_param_se_conv_reduce_bias = 24;
  int __xlx_offset_param_se_conv_reduce_bias = 1656;
  int __xlx_offset_byte_param_se_conv_reduce_bias = 1656*4;
  for (int j = 0, e = 576; j != e; ++j) {
    sc_bv<32> _xlx_tmp_sc;
    _xlx_tmp_sc.range(7, 0) = ((char*)__xlx_apatb_param_se_conv_expand_weight)[j*4+0];
    _xlx_tmp_sc.range(15, 8) = ((char*)__xlx_apatb_param_se_conv_expand_weight)[j*4+1];
    _xlx_tmp_sc.range(23, 16) = ((char*)__xlx_apatb_param_se_conv_expand_weight)[j*4+2];
    _xlx_tmp_sc.range(31, 24) = ((char*)__xlx_apatb_param_se_conv_expand_weight)[j*4+3];
    __xlx_msp_conv_weight_msp_conv_bias_msp_norm_weight_msp_norm_bias_msp_norm_running_mean_msp_norm_running_var_dw_conv_weight_norm_1_weight_norm_1_bias_norm_1_running_mean_norm_1_running_var_se_conv_reduce_weight_se_conv_reduce_bias_se_conv_expand_weight_se_conv_expand_bias_proj_conv_weight__tmp_vec.push_back(_xlx_tmp_sc);
  }
  int __xlx_size_param_se_conv_expand_weight = 576;
  int __xlx_offset_param_se_conv_expand_weight = 1680;
  int __xlx_offset_byte_param_se_conv_expand_weight = 1680*4;
  for (int j = 0, e = 24; j != e; ++j) {
    sc_bv<32> _xlx_tmp_sc;
    _xlx_tmp_sc.range(7, 0) = ((char*)__xlx_apatb_param_se_conv_expand_bias)[j*4+0];
    _xlx_tmp_sc.range(15, 8) = ((char*)__xlx_apatb_param_se_conv_expand_bias)[j*4+1];
    _xlx_tmp_sc.range(23, 16) = ((char*)__xlx_apatb_param_se_conv_expand_bias)[j*4+2];
    _xlx_tmp_sc.range(31, 24) = ((char*)__xlx_apatb_param_se_conv_expand_bias)[j*4+3];
    __xlx_msp_conv_weight_msp_conv_bias_msp_norm_weight_msp_norm_bias_msp_norm_running_mean_msp_norm_running_var_dw_conv_weight_norm_1_weight_norm_1_bias_norm_1_running_mean_norm_1_running_var_se_conv_reduce_weight_se_conv_reduce_bias_se_conv_expand_weight_se_conv_expand_bias_proj_conv_weight__tmp_vec.push_back(_xlx_tmp_sc);
  }
  int __xlx_size_param_se_conv_expand_bias = 24;
  int __xlx_offset_param_se_conv_expand_bias = 2256;
  int __xlx_offset_byte_param_se_conv_expand_bias = 2256*4;
  for (int j = 0, e = 576; j != e; ++j) {
    sc_bv<32> _xlx_tmp_sc;
    _xlx_tmp_sc.range(7, 0) = ((char*)__xlx_apatb_param_proj_conv_weight)[j*4+0];
    _xlx_tmp_sc.range(15, 8) = ((char*)__xlx_apatb_param_proj_conv_weight)[j*4+1];
    _xlx_tmp_sc.range(23, 16) = ((char*)__xlx_apatb_param_proj_conv_weight)[j*4+2];
    _xlx_tmp_sc.range(31, 24) = ((char*)__xlx_apatb_param_proj_conv_weight)[j*4+3];
    __xlx_msp_conv_weight_msp_conv_bias_msp_norm_weight_msp_norm_bias_msp_norm_running_mean_msp_norm_running_var_dw_conv_weight_norm_1_weight_norm_1_bias_norm_1_running_mean_norm_1_running_var_se_conv_reduce_weight_se_conv_reduce_bias_se_conv_expand_weight_se_conv_expand_bias_proj_conv_weight__tmp_vec.push_back(_xlx_tmp_sc);
  }
  int __xlx_size_param_proj_conv_weight = 576;
  int __xlx_offset_param_proj_conv_weight = 2280;
  int __xlx_offset_byte_param_proj_conv_weight = 2280*4;
  int* __xlx_msp_conv_weight_msp_conv_bias_msp_norm_weight_msp_norm_bias_msp_norm_running_mean_msp_norm_running_var_dw_conv_weight_norm_1_weight_norm_1_bias_norm_1_running_mean_norm_1_running_var_se_conv_reduce_weight_se_conv_reduce_bias_se_conv_expand_weight_se_conv_expand_bias_proj_conv_weight__input_buffer= new int[__xlx_msp_conv_weight_msp_conv_bias_msp_norm_weight_msp_norm_bias_msp_norm_running_mean_msp_norm_running_var_dw_conv_weight_norm_1_weight_norm_1_bias_norm_1_running_mean_norm_1_running_var_se_conv_reduce_weight_se_conv_reduce_bias_se_conv_expand_weight_se_conv_expand_bias_proj_conv_weight__tmp_vec.size()];
  for (int i = 0; i < __xlx_msp_conv_weight_msp_conv_bias_msp_norm_weight_msp_norm_bias_msp_norm_running_mean_msp_norm_running_var_dw_conv_weight_norm_1_weight_norm_1_bias_norm_1_running_mean_norm_1_running_var_se_conv_reduce_weight_se_conv_reduce_bias_se_conv_expand_weight_se_conv_expand_bias_proj_conv_weight__tmp_vec.size(); ++i) {
    __xlx_msp_conv_weight_msp_conv_bias_msp_norm_weight_msp_norm_bias_msp_norm_running_mean_msp_norm_running_var_dw_conv_weight_norm_1_weight_norm_1_bias_norm_1_running_mean_norm_1_running_var_se_conv_reduce_weight_se_conv_reduce_bias_se_conv_expand_weight_se_conv_expand_bias_proj_conv_weight__input_buffer[i] = __xlx_msp_conv_weight_msp_conv_bias_msp_norm_weight_msp_norm_bias_msp_norm_running_mean_msp_norm_running_var_dw_conv_weight_norm_1_weight_norm_1_bias_norm_1_running_mean_norm_1_running_var_se_conv_reduce_weight_se_conv_reduce_bias_se_conv_expand_weight_se_conv_expand_bias_proj_conv_weight__tmp_vec[i].range(31, 0).to_uint64();
  }
  // Collect __xlx_Y_msp_conv_Y_dw_act_Y_expand__tmp_vec
  vector<sc_bv<32> >__xlx_Y_msp_conv_Y_dw_act_Y_expand__tmp_vec;
  for (int j = 0, e = 301056; j != e; ++j) {
    sc_bv<32> _xlx_tmp_sc;
    _xlx_tmp_sc.range(7, 0) = ((char*)__xlx_apatb_param_Y_msp_conv)[j*4+0];
    _xlx_tmp_sc.range(15, 8) = ((char*)__xlx_apatb_param_Y_msp_conv)[j*4+1];
    _xlx_tmp_sc.range(23, 16) = ((char*)__xlx_apatb_param_Y_msp_conv)[j*4+2];
    _xlx_tmp_sc.range(31, 24) = ((char*)__xlx_apatb_param_Y_msp_conv)[j*4+3];
    __xlx_Y_msp_conv_Y_dw_act_Y_expand__tmp_vec.push_back(_xlx_tmp_sc);
  }
  int __xlx_size_param_Y_msp_conv = 301056;
  int __xlx_offset_param_Y_msp_conv = 0;
  int __xlx_offset_byte_param_Y_msp_conv = 0*4;
  for (int j = 0, e = 301056; j != e; ++j) {
    sc_bv<32> _xlx_tmp_sc;
    _xlx_tmp_sc.range(7, 0) = ((char*)__xlx_apatb_param_Y_dw_act)[j*4+0];
    _xlx_tmp_sc.range(15, 8) = ((char*)__xlx_apatb_param_Y_dw_act)[j*4+1];
    _xlx_tmp_sc.range(23, 16) = ((char*)__xlx_apatb_param_Y_dw_act)[j*4+2];
    _xlx_tmp_sc.range(31, 24) = ((char*)__xlx_apatb_param_Y_dw_act)[j*4+3];
    __xlx_Y_msp_conv_Y_dw_act_Y_expand__tmp_vec.push_back(_xlx_tmp_sc);
  }
  int __xlx_size_param_Y_dw_act = 301056;
  int __xlx_offset_param_Y_dw_act = 301056;
  int __xlx_offset_byte_param_Y_dw_act = 301056*4;
  for (int j = 0, e = 24; j != e; ++j) {
    sc_bv<32> _xlx_tmp_sc;
    _xlx_tmp_sc.range(7, 0) = ((char*)__xlx_apatb_param_Y_expand)[j*4+0];
    _xlx_tmp_sc.range(15, 8) = ((char*)__xlx_apatb_param_Y_expand)[j*4+1];
    _xlx_tmp_sc.range(23, 16) = ((char*)__xlx_apatb_param_Y_expand)[j*4+2];
    _xlx_tmp_sc.range(31, 24) = ((char*)__xlx_apatb_param_Y_expand)[j*4+3];
    __xlx_Y_msp_conv_Y_dw_act_Y_expand__tmp_vec.push_back(_xlx_tmp_sc);
  }
  int __xlx_size_param_Y_expand = 24;
  int __xlx_offset_param_Y_expand = 602112;
  int __xlx_offset_byte_param_Y_expand = 602112*4;
  int* __xlx_Y_msp_conv_Y_dw_act_Y_expand__input_buffer= new int[__xlx_Y_msp_conv_Y_dw_act_Y_expand__tmp_vec.size()];
  for (int i = 0; i < __xlx_Y_msp_conv_Y_dw_act_Y_expand__tmp_vec.size(); ++i) {
    __xlx_Y_msp_conv_Y_dw_act_Y_expand__input_buffer[i] = __xlx_Y_msp_conv_Y_dw_act_Y_expand__tmp_vec[i].range(31, 0).to_uint64();
  }
  // Collect __xlx_Y_msp_norm_Y_mean_Y_sigmoid__tmp_vec
  vector<sc_bv<32> >__xlx_Y_msp_norm_Y_mean_Y_sigmoid__tmp_vec;
  for (int j = 0, e = 301056; j != e; ++j) {
    sc_bv<32> _xlx_tmp_sc;
    _xlx_tmp_sc.range(7, 0) = ((char*)__xlx_apatb_param_Y_msp_norm)[j*4+0];
    _xlx_tmp_sc.range(15, 8) = ((char*)__xlx_apatb_param_Y_msp_norm)[j*4+1];
    _xlx_tmp_sc.range(23, 16) = ((char*)__xlx_apatb_param_Y_msp_norm)[j*4+2];
    _xlx_tmp_sc.range(31, 24) = ((char*)__xlx_apatb_param_Y_msp_norm)[j*4+3];
    __xlx_Y_msp_norm_Y_mean_Y_sigmoid__tmp_vec.push_back(_xlx_tmp_sc);
  }
  int __xlx_size_param_Y_msp_norm = 301056;
  int __xlx_offset_param_Y_msp_norm = 0;
  int __xlx_offset_byte_param_Y_msp_norm = 0*4;
  for (int j = 0, e = 24; j != e; ++j) {
    sc_bv<32> _xlx_tmp_sc;
    _xlx_tmp_sc.range(7, 0) = ((char*)__xlx_apatb_param_Y_mean)[j*4+0];
    _xlx_tmp_sc.range(15, 8) = ((char*)__xlx_apatb_param_Y_mean)[j*4+1];
    _xlx_tmp_sc.range(23, 16) = ((char*)__xlx_apatb_param_Y_mean)[j*4+2];
    _xlx_tmp_sc.range(31, 24) = ((char*)__xlx_apatb_param_Y_mean)[j*4+3];
    __xlx_Y_msp_norm_Y_mean_Y_sigmoid__tmp_vec.push_back(_xlx_tmp_sc);
  }
  int __xlx_size_param_Y_mean = 24;
  int __xlx_offset_param_Y_mean = 301056;
  int __xlx_offset_byte_param_Y_mean = 301056*4;
  for (int j = 0, e = 24; j != e; ++j) {
    sc_bv<32> _xlx_tmp_sc;
    _xlx_tmp_sc.range(7, 0) = ((char*)__xlx_apatb_param_Y_sigmoid)[j*4+0];
    _xlx_tmp_sc.range(15, 8) = ((char*)__xlx_apatb_param_Y_sigmoid)[j*4+1];
    _xlx_tmp_sc.range(23, 16) = ((char*)__xlx_apatb_param_Y_sigmoid)[j*4+2];
    _xlx_tmp_sc.range(31, 24) = ((char*)__xlx_apatb_param_Y_sigmoid)[j*4+3];
    __xlx_Y_msp_norm_Y_mean_Y_sigmoid__tmp_vec.push_back(_xlx_tmp_sc);
  }
  int __xlx_size_param_Y_sigmoid = 24;
  int __xlx_offset_param_Y_sigmoid = 301080;
  int __xlx_offset_byte_param_Y_sigmoid = 301080*4;
  int* __xlx_Y_msp_norm_Y_mean_Y_sigmoid__input_buffer= new int[__xlx_Y_msp_norm_Y_mean_Y_sigmoid__tmp_vec.size()];
  for (int i = 0; i < __xlx_Y_msp_norm_Y_mean_Y_sigmoid__tmp_vec.size(); ++i) {
    __xlx_Y_msp_norm_Y_mean_Y_sigmoid__input_buffer[i] = __xlx_Y_msp_norm_Y_mean_Y_sigmoid__tmp_vec[i].range(31, 0).to_uint64();
  }
  // Collect __xlx_Y_dw_conv_Y_reduce_Y_se__tmp_vec
  vector<sc_bv<32> >__xlx_Y_dw_conv_Y_reduce_Y_se__tmp_vec;
  for (int j = 0, e = 301056; j != e; ++j) {
    sc_bv<32> _xlx_tmp_sc;
    _xlx_tmp_sc.range(7, 0) = ((char*)__xlx_apatb_param_Y_dw_conv)[j*4+0];
    _xlx_tmp_sc.range(15, 8) = ((char*)__xlx_apatb_param_Y_dw_conv)[j*4+1];
    _xlx_tmp_sc.range(23, 16) = ((char*)__xlx_apatb_param_Y_dw_conv)[j*4+2];
    _xlx_tmp_sc.range(31, 24) = ((char*)__xlx_apatb_param_Y_dw_conv)[j*4+3];
    __xlx_Y_dw_conv_Y_reduce_Y_se__tmp_vec.push_back(_xlx_tmp_sc);
  }
  int __xlx_size_param_Y_dw_conv = 301056;
  int __xlx_offset_param_Y_dw_conv = 0;
  int __xlx_offset_byte_param_Y_dw_conv = 0*4;
  for (int j = 0, e = 24; j != e; ++j) {
    sc_bv<32> _xlx_tmp_sc;
    _xlx_tmp_sc.range(7, 0) = ((char*)__xlx_apatb_param_Y_reduce)[j*4+0];
    _xlx_tmp_sc.range(15, 8) = ((char*)__xlx_apatb_param_Y_reduce)[j*4+1];
    _xlx_tmp_sc.range(23, 16) = ((char*)__xlx_apatb_param_Y_reduce)[j*4+2];
    _xlx_tmp_sc.range(31, 24) = ((char*)__xlx_apatb_param_Y_reduce)[j*4+3];
    __xlx_Y_dw_conv_Y_reduce_Y_se__tmp_vec.push_back(_xlx_tmp_sc);
  }
  int __xlx_size_param_Y_reduce = 24;
  int __xlx_offset_param_Y_reduce = 301056;
  int __xlx_offset_byte_param_Y_reduce = 301056*4;
  for (int j = 0, e = 301056; j != e; ++j) {
    sc_bv<32> _xlx_tmp_sc;
    _xlx_tmp_sc.range(7, 0) = ((char*)__xlx_apatb_param_Y_se)[j*4+0];
    _xlx_tmp_sc.range(15, 8) = ((char*)__xlx_apatb_param_Y_se)[j*4+1];
    _xlx_tmp_sc.range(23, 16) = ((char*)__xlx_apatb_param_Y_se)[j*4+2];
    _xlx_tmp_sc.range(31, 24) = ((char*)__xlx_apatb_param_Y_se)[j*4+3];
    __xlx_Y_dw_conv_Y_reduce_Y_se__tmp_vec.push_back(_xlx_tmp_sc);
  }
  int __xlx_size_param_Y_se = 301056;
  int __xlx_offset_param_Y_se = 301080;
  int __xlx_offset_byte_param_Y_se = 301080*4;
  int* __xlx_Y_dw_conv_Y_reduce_Y_se__input_buffer= new int[__xlx_Y_dw_conv_Y_reduce_Y_se__tmp_vec.size()];
  for (int i = 0; i < __xlx_Y_dw_conv_Y_reduce_Y_se__tmp_vec.size(); ++i) {
    __xlx_Y_dw_conv_Y_reduce_Y_se__input_buffer[i] = __xlx_Y_dw_conv_Y_reduce_Y_se__tmp_vec[i].range(31, 0).to_uint64();
  }
  // DUT call
  kernel_stage0(__xlx_X_data_Y_dw_norm_Y_relu_Y_proj__input_buffer, __xlx_msp_conv_weight_msp_conv_bias_msp_norm_weight_msp_norm_bias_msp_norm_running_mean_msp_norm_running_var_dw_conv_weight_norm_1_weight_norm_1_bias_norm_1_running_mean_norm_1_running_var_se_conv_reduce_weight_se_conv_reduce_bias_se_conv_expand_weight_se_conv_expand_bias_proj_conv_weight__input_buffer, __xlx_Y_msp_conv_Y_dw_act_Y_expand__input_buffer, __xlx_Y_msp_norm_Y_mean_Y_sigmoid__input_buffer, __xlx_Y_dw_conv_Y_reduce_Y_se__input_buffer, __xlx_offset_byte_param_X_data, __xlx_offset_byte_param_msp_conv_weight, __xlx_offset_byte_param_msp_conv_bias, __xlx_offset_byte_param_msp_norm_weight, __xlx_offset_byte_param_msp_norm_bias, __xlx_offset_byte_param_msp_norm_running_mean, __xlx_offset_byte_param_msp_norm_running_var, __xlx_offset_byte_param_dw_conv_weight, __xlx_offset_byte_param_norm_1_weight, __xlx_offset_byte_param_norm_1_bias, __xlx_offset_byte_param_norm_1_running_mean, __xlx_offset_byte_param_norm_1_running_var, __xlx_offset_byte_param_se_conv_reduce_weight, __xlx_offset_byte_param_se_conv_reduce_bias, __xlx_offset_byte_param_se_conv_expand_weight, __xlx_offset_byte_param_se_conv_expand_bias, __xlx_offset_byte_param_proj_conv_weight, __xlx_offset_byte_param_Y_msp_conv, __xlx_offset_byte_param_Y_msp_norm, __xlx_offset_byte_param_Y_dw_conv, __xlx_offset_byte_param_Y_dw_norm, __xlx_offset_byte_param_Y_dw_act, __xlx_offset_byte_param_Y_mean, __xlx_offset_byte_param_Y_reduce, __xlx_offset_byte_param_Y_relu, __xlx_offset_byte_param_Y_expand, __xlx_offset_byte_param_Y_sigmoid, __xlx_offset_byte_param_Y_se, __xlx_offset_byte_param_Y_proj);
// print __xlx_apatb_param_X_data
  sc_bv<32>*__xlx_X_data_output_buffer = new sc_bv<32>[__xlx_size_param_X_data];
  for (int i = 0; i < __xlx_size_param_X_data; ++i) {
    __xlx_X_data_output_buffer[i] = __xlx_X_data_Y_dw_norm_Y_relu_Y_proj__input_buffer[i+__xlx_offset_param_X_data];
  }
  for (int i = 0; i < __xlx_size_param_X_data; ++i) {
    ((char*)__xlx_apatb_param_X_data)[i*4+0] = __xlx_X_data_output_buffer[i].range(7, 0).to_uint();
    ((char*)__xlx_apatb_param_X_data)[i*4+1] = __xlx_X_data_output_buffer[i].range(15, 8).to_uint();
    ((char*)__xlx_apatb_param_X_data)[i*4+2] = __xlx_X_data_output_buffer[i].range(23, 16).to_uint();
    ((char*)__xlx_apatb_param_X_data)[i*4+3] = __xlx_X_data_output_buffer[i].range(31, 24).to_uint();
  }
// print __xlx_apatb_param_Y_dw_norm
  sc_bv<32>*__xlx_Y_dw_norm_output_buffer = new sc_bv<32>[__xlx_size_param_Y_dw_norm];
  for (int i = 0; i < __xlx_size_param_Y_dw_norm; ++i) {
    __xlx_Y_dw_norm_output_buffer[i] = __xlx_X_data_Y_dw_norm_Y_relu_Y_proj__input_buffer[i+__xlx_offset_param_Y_dw_norm];
  }
  for (int i = 0; i < __xlx_size_param_Y_dw_norm; ++i) {
    ((char*)__xlx_apatb_param_Y_dw_norm)[i*4+0] = __xlx_Y_dw_norm_output_buffer[i].range(7, 0).to_uint();
    ((char*)__xlx_apatb_param_Y_dw_norm)[i*4+1] = __xlx_Y_dw_norm_output_buffer[i].range(15, 8).to_uint();
    ((char*)__xlx_apatb_param_Y_dw_norm)[i*4+2] = __xlx_Y_dw_norm_output_buffer[i].range(23, 16).to_uint();
    ((char*)__xlx_apatb_param_Y_dw_norm)[i*4+3] = __xlx_Y_dw_norm_output_buffer[i].range(31, 24).to_uint();
  }
// print __xlx_apatb_param_Y_relu
  sc_bv<32>*__xlx_Y_relu_output_buffer = new sc_bv<32>[__xlx_size_param_Y_relu];
  for (int i = 0; i < __xlx_size_param_Y_relu; ++i) {
    __xlx_Y_relu_output_buffer[i] = __xlx_X_data_Y_dw_norm_Y_relu_Y_proj__input_buffer[i+__xlx_offset_param_Y_relu];
  }
  for (int i = 0; i < __xlx_size_param_Y_relu; ++i) {
    ((char*)__xlx_apatb_param_Y_relu)[i*4+0] = __xlx_Y_relu_output_buffer[i].range(7, 0).to_uint();
    ((char*)__xlx_apatb_param_Y_relu)[i*4+1] = __xlx_Y_relu_output_buffer[i].range(15, 8).to_uint();
    ((char*)__xlx_apatb_param_Y_relu)[i*4+2] = __xlx_Y_relu_output_buffer[i].range(23, 16).to_uint();
    ((char*)__xlx_apatb_param_Y_relu)[i*4+3] = __xlx_Y_relu_output_buffer[i].range(31, 24).to_uint();
  }
// print __xlx_apatb_param_Y_proj
  sc_bv<32>*__xlx_Y_proj_output_buffer = new sc_bv<32>[__xlx_size_param_Y_proj];
  for (int i = 0; i < __xlx_size_param_Y_proj; ++i) {
    __xlx_Y_proj_output_buffer[i] = __xlx_X_data_Y_dw_norm_Y_relu_Y_proj__input_buffer[i+__xlx_offset_param_Y_proj];
  }
  for (int i = 0; i < __xlx_size_param_Y_proj; ++i) {
    ((char*)__xlx_apatb_param_Y_proj)[i*4+0] = __xlx_Y_proj_output_buffer[i].range(7, 0).to_uint();
    ((char*)__xlx_apatb_param_Y_proj)[i*4+1] = __xlx_Y_proj_output_buffer[i].range(15, 8).to_uint();
    ((char*)__xlx_apatb_param_Y_proj)[i*4+2] = __xlx_Y_proj_output_buffer[i].range(23, 16).to_uint();
    ((char*)__xlx_apatb_param_Y_proj)[i*4+3] = __xlx_Y_proj_output_buffer[i].range(31, 24).to_uint();
  }
// print __xlx_apatb_param_msp_conv_weight
  sc_bv<32>*__xlx_msp_conv_weight_output_buffer = new sc_bv<32>[__xlx_size_param_msp_conv_weight];
  for (int i = 0; i < __xlx_size_param_msp_conv_weight; ++i) {
    __xlx_msp_conv_weight_output_buffer[i] = __xlx_msp_conv_weight_msp_conv_bias_msp_norm_weight_msp_norm_bias_msp_norm_running_mean_msp_norm_running_var_dw_conv_weight_norm_1_weight_norm_1_bias_norm_1_running_mean_norm_1_running_var_se_conv_reduce_weight_se_conv_reduce_bias_se_conv_expand_weight_se_conv_expand_bias_proj_conv_weight__input_buffer[i+__xlx_offset_param_msp_conv_weight];
  }
  for (int i = 0; i < __xlx_size_param_msp_conv_weight; ++i) {
    ((char*)__xlx_apatb_param_msp_conv_weight)[i*4+0] = __xlx_msp_conv_weight_output_buffer[i].range(7, 0).to_uint();
    ((char*)__xlx_apatb_param_msp_conv_weight)[i*4+1] = __xlx_msp_conv_weight_output_buffer[i].range(15, 8).to_uint();
    ((char*)__xlx_apatb_param_msp_conv_weight)[i*4+2] = __xlx_msp_conv_weight_output_buffer[i].range(23, 16).to_uint();
    ((char*)__xlx_apatb_param_msp_conv_weight)[i*4+3] = __xlx_msp_conv_weight_output_buffer[i].range(31, 24).to_uint();
  }
// print __xlx_apatb_param_msp_conv_bias
  sc_bv<32>*__xlx_msp_conv_bias_output_buffer = new sc_bv<32>[__xlx_size_param_msp_conv_bias];
  for (int i = 0; i < __xlx_size_param_msp_conv_bias; ++i) {
    __xlx_msp_conv_bias_output_buffer[i] = __xlx_msp_conv_weight_msp_conv_bias_msp_norm_weight_msp_norm_bias_msp_norm_running_mean_msp_norm_running_var_dw_conv_weight_norm_1_weight_norm_1_bias_norm_1_running_mean_norm_1_running_var_se_conv_reduce_weight_se_conv_reduce_bias_se_conv_expand_weight_se_conv_expand_bias_proj_conv_weight__input_buffer[i+__xlx_offset_param_msp_conv_bias];
  }
  for (int i = 0; i < __xlx_size_param_msp_conv_bias; ++i) {
    ((char*)__xlx_apatb_param_msp_conv_bias)[i*4+0] = __xlx_msp_conv_bias_output_buffer[i].range(7, 0).to_uint();
    ((char*)__xlx_apatb_param_msp_conv_bias)[i*4+1] = __xlx_msp_conv_bias_output_buffer[i].range(15, 8).to_uint();
    ((char*)__xlx_apatb_param_msp_conv_bias)[i*4+2] = __xlx_msp_conv_bias_output_buffer[i].range(23, 16).to_uint();
    ((char*)__xlx_apatb_param_msp_conv_bias)[i*4+3] = __xlx_msp_conv_bias_output_buffer[i].range(31, 24).to_uint();
  }
// print __xlx_apatb_param_msp_norm_weight
  sc_bv<32>*__xlx_msp_norm_weight_output_buffer = new sc_bv<32>[__xlx_size_param_msp_norm_weight];
  for (int i = 0; i < __xlx_size_param_msp_norm_weight; ++i) {
    __xlx_msp_norm_weight_output_buffer[i] = __xlx_msp_conv_weight_msp_conv_bias_msp_norm_weight_msp_norm_bias_msp_norm_running_mean_msp_norm_running_var_dw_conv_weight_norm_1_weight_norm_1_bias_norm_1_running_mean_norm_1_running_var_se_conv_reduce_weight_se_conv_reduce_bias_se_conv_expand_weight_se_conv_expand_bias_proj_conv_weight__input_buffer[i+__xlx_offset_param_msp_norm_weight];
  }
  for (int i = 0; i < __xlx_size_param_msp_norm_weight; ++i) {
    ((char*)__xlx_apatb_param_msp_norm_weight)[i*4+0] = __xlx_msp_norm_weight_output_buffer[i].range(7, 0).to_uint();
    ((char*)__xlx_apatb_param_msp_norm_weight)[i*4+1] = __xlx_msp_norm_weight_output_buffer[i].range(15, 8).to_uint();
    ((char*)__xlx_apatb_param_msp_norm_weight)[i*4+2] = __xlx_msp_norm_weight_output_buffer[i].range(23, 16).to_uint();
    ((char*)__xlx_apatb_param_msp_norm_weight)[i*4+3] = __xlx_msp_norm_weight_output_buffer[i].range(31, 24).to_uint();
  }
// print __xlx_apatb_param_msp_norm_bias
  sc_bv<32>*__xlx_msp_norm_bias_output_buffer = new sc_bv<32>[__xlx_size_param_msp_norm_bias];
  for (int i = 0; i < __xlx_size_param_msp_norm_bias; ++i) {
    __xlx_msp_norm_bias_output_buffer[i] = __xlx_msp_conv_weight_msp_conv_bias_msp_norm_weight_msp_norm_bias_msp_norm_running_mean_msp_norm_running_var_dw_conv_weight_norm_1_weight_norm_1_bias_norm_1_running_mean_norm_1_running_var_se_conv_reduce_weight_se_conv_reduce_bias_se_conv_expand_weight_se_conv_expand_bias_proj_conv_weight__input_buffer[i+__xlx_offset_param_msp_norm_bias];
  }
  for (int i = 0; i < __xlx_size_param_msp_norm_bias; ++i) {
    ((char*)__xlx_apatb_param_msp_norm_bias)[i*4+0] = __xlx_msp_norm_bias_output_buffer[i].range(7, 0).to_uint();
    ((char*)__xlx_apatb_param_msp_norm_bias)[i*4+1] = __xlx_msp_norm_bias_output_buffer[i].range(15, 8).to_uint();
    ((char*)__xlx_apatb_param_msp_norm_bias)[i*4+2] = __xlx_msp_norm_bias_output_buffer[i].range(23, 16).to_uint();
    ((char*)__xlx_apatb_param_msp_norm_bias)[i*4+3] = __xlx_msp_norm_bias_output_buffer[i].range(31, 24).to_uint();
  }
// print __xlx_apatb_param_msp_norm_running_mean
  sc_bv<32>*__xlx_msp_norm_running_mean_output_buffer = new sc_bv<32>[__xlx_size_param_msp_norm_running_mean];
  for (int i = 0; i < __xlx_size_param_msp_norm_running_mean; ++i) {
    __xlx_msp_norm_running_mean_output_buffer[i] = __xlx_msp_conv_weight_msp_conv_bias_msp_norm_weight_msp_norm_bias_msp_norm_running_mean_msp_norm_running_var_dw_conv_weight_norm_1_weight_norm_1_bias_norm_1_running_mean_norm_1_running_var_se_conv_reduce_weight_se_conv_reduce_bias_se_conv_expand_weight_se_conv_expand_bias_proj_conv_weight__input_buffer[i+__xlx_offset_param_msp_norm_running_mean];
  }
  for (int i = 0; i < __xlx_size_param_msp_norm_running_mean; ++i) {
    ((char*)__xlx_apatb_param_msp_norm_running_mean)[i*4+0] = __xlx_msp_norm_running_mean_output_buffer[i].range(7, 0).to_uint();
    ((char*)__xlx_apatb_param_msp_norm_running_mean)[i*4+1] = __xlx_msp_norm_running_mean_output_buffer[i].range(15, 8).to_uint();
    ((char*)__xlx_apatb_param_msp_norm_running_mean)[i*4+2] = __xlx_msp_norm_running_mean_output_buffer[i].range(23, 16).to_uint();
    ((char*)__xlx_apatb_param_msp_norm_running_mean)[i*4+3] = __xlx_msp_norm_running_mean_output_buffer[i].range(31, 24).to_uint();
  }
// print __xlx_apatb_param_msp_norm_running_var
  sc_bv<32>*__xlx_msp_norm_running_var_output_buffer = new sc_bv<32>[__xlx_size_param_msp_norm_running_var];
  for (int i = 0; i < __xlx_size_param_msp_norm_running_var; ++i) {
    __xlx_msp_norm_running_var_output_buffer[i] = __xlx_msp_conv_weight_msp_conv_bias_msp_norm_weight_msp_norm_bias_msp_norm_running_mean_msp_norm_running_var_dw_conv_weight_norm_1_weight_norm_1_bias_norm_1_running_mean_norm_1_running_var_se_conv_reduce_weight_se_conv_reduce_bias_se_conv_expand_weight_se_conv_expand_bias_proj_conv_weight__input_buffer[i+__xlx_offset_param_msp_norm_running_var];
  }
  for (int i = 0; i < __xlx_size_param_msp_norm_running_var; ++i) {
    ((char*)__xlx_apatb_param_msp_norm_running_var)[i*4+0] = __xlx_msp_norm_running_var_output_buffer[i].range(7, 0).to_uint();
    ((char*)__xlx_apatb_param_msp_norm_running_var)[i*4+1] = __xlx_msp_norm_running_var_output_buffer[i].range(15, 8).to_uint();
    ((char*)__xlx_apatb_param_msp_norm_running_var)[i*4+2] = __xlx_msp_norm_running_var_output_buffer[i].range(23, 16).to_uint();
    ((char*)__xlx_apatb_param_msp_norm_running_var)[i*4+3] = __xlx_msp_norm_running_var_output_buffer[i].range(31, 24).to_uint();
  }
// print __xlx_apatb_param_dw_conv_weight
  sc_bv<32>*__xlx_dw_conv_weight_output_buffer = new sc_bv<32>[__xlx_size_param_dw_conv_weight];
  for (int i = 0; i < __xlx_size_param_dw_conv_weight; ++i) {
    __xlx_dw_conv_weight_output_buffer[i] = __xlx_msp_conv_weight_msp_conv_bias_msp_norm_weight_msp_norm_bias_msp_norm_running_mean_msp_norm_running_var_dw_conv_weight_norm_1_weight_norm_1_bias_norm_1_running_mean_norm_1_running_var_se_conv_reduce_weight_se_conv_reduce_bias_se_conv_expand_weight_se_conv_expand_bias_proj_conv_weight__input_buffer[i+__xlx_offset_param_dw_conv_weight];
  }
  for (int i = 0; i < __xlx_size_param_dw_conv_weight; ++i) {
    ((char*)__xlx_apatb_param_dw_conv_weight)[i*4+0] = __xlx_dw_conv_weight_output_buffer[i].range(7, 0).to_uint();
    ((char*)__xlx_apatb_param_dw_conv_weight)[i*4+1] = __xlx_dw_conv_weight_output_buffer[i].range(15, 8).to_uint();
    ((char*)__xlx_apatb_param_dw_conv_weight)[i*4+2] = __xlx_dw_conv_weight_output_buffer[i].range(23, 16).to_uint();
    ((char*)__xlx_apatb_param_dw_conv_weight)[i*4+3] = __xlx_dw_conv_weight_output_buffer[i].range(31, 24).to_uint();
  }
// print __xlx_apatb_param_norm_1_weight
  sc_bv<32>*__xlx_norm_1_weight_output_buffer = new sc_bv<32>[__xlx_size_param_norm_1_weight];
  for (int i = 0; i < __xlx_size_param_norm_1_weight; ++i) {
    __xlx_norm_1_weight_output_buffer[i] = __xlx_msp_conv_weight_msp_conv_bias_msp_norm_weight_msp_norm_bias_msp_norm_running_mean_msp_norm_running_var_dw_conv_weight_norm_1_weight_norm_1_bias_norm_1_running_mean_norm_1_running_var_se_conv_reduce_weight_se_conv_reduce_bias_se_conv_expand_weight_se_conv_expand_bias_proj_conv_weight__input_buffer[i+__xlx_offset_param_norm_1_weight];
  }
  for (int i = 0; i < __xlx_size_param_norm_1_weight; ++i) {
    ((char*)__xlx_apatb_param_norm_1_weight)[i*4+0] = __xlx_norm_1_weight_output_buffer[i].range(7, 0).to_uint();
    ((char*)__xlx_apatb_param_norm_1_weight)[i*4+1] = __xlx_norm_1_weight_output_buffer[i].range(15, 8).to_uint();
    ((char*)__xlx_apatb_param_norm_1_weight)[i*4+2] = __xlx_norm_1_weight_output_buffer[i].range(23, 16).to_uint();
    ((char*)__xlx_apatb_param_norm_1_weight)[i*4+3] = __xlx_norm_1_weight_output_buffer[i].range(31, 24).to_uint();
  }
// print __xlx_apatb_param_norm_1_bias
  sc_bv<32>*__xlx_norm_1_bias_output_buffer = new sc_bv<32>[__xlx_size_param_norm_1_bias];
  for (int i = 0; i < __xlx_size_param_norm_1_bias; ++i) {
    __xlx_norm_1_bias_output_buffer[i] = __xlx_msp_conv_weight_msp_conv_bias_msp_norm_weight_msp_norm_bias_msp_norm_running_mean_msp_norm_running_var_dw_conv_weight_norm_1_weight_norm_1_bias_norm_1_running_mean_norm_1_running_var_se_conv_reduce_weight_se_conv_reduce_bias_se_conv_expand_weight_se_conv_expand_bias_proj_conv_weight__input_buffer[i+__xlx_offset_param_norm_1_bias];
  }
  for (int i = 0; i < __xlx_size_param_norm_1_bias; ++i) {
    ((char*)__xlx_apatb_param_norm_1_bias)[i*4+0] = __xlx_norm_1_bias_output_buffer[i].range(7, 0).to_uint();
    ((char*)__xlx_apatb_param_norm_1_bias)[i*4+1] = __xlx_norm_1_bias_output_buffer[i].range(15, 8).to_uint();
    ((char*)__xlx_apatb_param_norm_1_bias)[i*4+2] = __xlx_norm_1_bias_output_buffer[i].range(23, 16).to_uint();
    ((char*)__xlx_apatb_param_norm_1_bias)[i*4+3] = __xlx_norm_1_bias_output_buffer[i].range(31, 24).to_uint();
  }
// print __xlx_apatb_param_norm_1_running_mean
  sc_bv<32>*__xlx_norm_1_running_mean_output_buffer = new sc_bv<32>[__xlx_size_param_norm_1_running_mean];
  for (int i = 0; i < __xlx_size_param_norm_1_running_mean; ++i) {
    __xlx_norm_1_running_mean_output_buffer[i] = __xlx_msp_conv_weight_msp_conv_bias_msp_norm_weight_msp_norm_bias_msp_norm_running_mean_msp_norm_running_var_dw_conv_weight_norm_1_weight_norm_1_bias_norm_1_running_mean_norm_1_running_var_se_conv_reduce_weight_se_conv_reduce_bias_se_conv_expand_weight_se_conv_expand_bias_proj_conv_weight__input_buffer[i+__xlx_offset_param_norm_1_running_mean];
  }
  for (int i = 0; i < __xlx_size_param_norm_1_running_mean; ++i) {
    ((char*)__xlx_apatb_param_norm_1_running_mean)[i*4+0] = __xlx_norm_1_running_mean_output_buffer[i].range(7, 0).to_uint();
    ((char*)__xlx_apatb_param_norm_1_running_mean)[i*4+1] = __xlx_norm_1_running_mean_output_buffer[i].range(15, 8).to_uint();
    ((char*)__xlx_apatb_param_norm_1_running_mean)[i*4+2] = __xlx_norm_1_running_mean_output_buffer[i].range(23, 16).to_uint();
    ((char*)__xlx_apatb_param_norm_1_running_mean)[i*4+3] = __xlx_norm_1_running_mean_output_buffer[i].range(31, 24).to_uint();
  }
// print __xlx_apatb_param_norm_1_running_var
  sc_bv<32>*__xlx_norm_1_running_var_output_buffer = new sc_bv<32>[__xlx_size_param_norm_1_running_var];
  for (int i = 0; i < __xlx_size_param_norm_1_running_var; ++i) {
    __xlx_norm_1_running_var_output_buffer[i] = __xlx_msp_conv_weight_msp_conv_bias_msp_norm_weight_msp_norm_bias_msp_norm_running_mean_msp_norm_running_var_dw_conv_weight_norm_1_weight_norm_1_bias_norm_1_running_mean_norm_1_running_var_se_conv_reduce_weight_se_conv_reduce_bias_se_conv_expand_weight_se_conv_expand_bias_proj_conv_weight__input_buffer[i+__xlx_offset_param_norm_1_running_var];
  }
  for (int i = 0; i < __xlx_size_param_norm_1_running_var; ++i) {
    ((char*)__xlx_apatb_param_norm_1_running_var)[i*4+0] = __xlx_norm_1_running_var_output_buffer[i].range(7, 0).to_uint();
    ((char*)__xlx_apatb_param_norm_1_running_var)[i*4+1] = __xlx_norm_1_running_var_output_buffer[i].range(15, 8).to_uint();
    ((char*)__xlx_apatb_param_norm_1_running_var)[i*4+2] = __xlx_norm_1_running_var_output_buffer[i].range(23, 16).to_uint();
    ((char*)__xlx_apatb_param_norm_1_running_var)[i*4+3] = __xlx_norm_1_running_var_output_buffer[i].range(31, 24).to_uint();
  }
// print __xlx_apatb_param_se_conv_reduce_weight
  sc_bv<32>*__xlx_se_conv_reduce_weight_output_buffer = new sc_bv<32>[__xlx_size_param_se_conv_reduce_weight];
  for (int i = 0; i < __xlx_size_param_se_conv_reduce_weight; ++i) {
    __xlx_se_conv_reduce_weight_output_buffer[i] = __xlx_msp_conv_weight_msp_conv_bias_msp_norm_weight_msp_norm_bias_msp_norm_running_mean_msp_norm_running_var_dw_conv_weight_norm_1_weight_norm_1_bias_norm_1_running_mean_norm_1_running_var_se_conv_reduce_weight_se_conv_reduce_bias_se_conv_expand_weight_se_conv_expand_bias_proj_conv_weight__input_buffer[i+__xlx_offset_param_se_conv_reduce_weight];
  }
  for (int i = 0; i < __xlx_size_param_se_conv_reduce_weight; ++i) {
    ((char*)__xlx_apatb_param_se_conv_reduce_weight)[i*4+0] = __xlx_se_conv_reduce_weight_output_buffer[i].range(7, 0).to_uint();
    ((char*)__xlx_apatb_param_se_conv_reduce_weight)[i*4+1] = __xlx_se_conv_reduce_weight_output_buffer[i].range(15, 8).to_uint();
    ((char*)__xlx_apatb_param_se_conv_reduce_weight)[i*4+2] = __xlx_se_conv_reduce_weight_output_buffer[i].range(23, 16).to_uint();
    ((char*)__xlx_apatb_param_se_conv_reduce_weight)[i*4+3] = __xlx_se_conv_reduce_weight_output_buffer[i].range(31, 24).to_uint();
  }
// print __xlx_apatb_param_se_conv_reduce_bias
  sc_bv<32>*__xlx_se_conv_reduce_bias_output_buffer = new sc_bv<32>[__xlx_size_param_se_conv_reduce_bias];
  for (int i = 0; i < __xlx_size_param_se_conv_reduce_bias; ++i) {
    __xlx_se_conv_reduce_bias_output_buffer[i] = __xlx_msp_conv_weight_msp_conv_bias_msp_norm_weight_msp_norm_bias_msp_norm_running_mean_msp_norm_running_var_dw_conv_weight_norm_1_weight_norm_1_bias_norm_1_running_mean_norm_1_running_var_se_conv_reduce_weight_se_conv_reduce_bias_se_conv_expand_weight_se_conv_expand_bias_proj_conv_weight__input_buffer[i+__xlx_offset_param_se_conv_reduce_bias];
  }
  for (int i = 0; i < __xlx_size_param_se_conv_reduce_bias; ++i) {
    ((char*)__xlx_apatb_param_se_conv_reduce_bias)[i*4+0] = __xlx_se_conv_reduce_bias_output_buffer[i].range(7, 0).to_uint();
    ((char*)__xlx_apatb_param_se_conv_reduce_bias)[i*4+1] = __xlx_se_conv_reduce_bias_output_buffer[i].range(15, 8).to_uint();
    ((char*)__xlx_apatb_param_se_conv_reduce_bias)[i*4+2] = __xlx_se_conv_reduce_bias_output_buffer[i].range(23, 16).to_uint();
    ((char*)__xlx_apatb_param_se_conv_reduce_bias)[i*4+3] = __xlx_se_conv_reduce_bias_output_buffer[i].range(31, 24).to_uint();
  }
// print __xlx_apatb_param_se_conv_expand_weight
  sc_bv<32>*__xlx_se_conv_expand_weight_output_buffer = new sc_bv<32>[__xlx_size_param_se_conv_expand_weight];
  for (int i = 0; i < __xlx_size_param_se_conv_expand_weight; ++i) {
    __xlx_se_conv_expand_weight_output_buffer[i] = __xlx_msp_conv_weight_msp_conv_bias_msp_norm_weight_msp_norm_bias_msp_norm_running_mean_msp_norm_running_var_dw_conv_weight_norm_1_weight_norm_1_bias_norm_1_running_mean_norm_1_running_var_se_conv_reduce_weight_se_conv_reduce_bias_se_conv_expand_weight_se_conv_expand_bias_proj_conv_weight__input_buffer[i+__xlx_offset_param_se_conv_expand_weight];
  }
  for (int i = 0; i < __xlx_size_param_se_conv_expand_weight; ++i) {
    ((char*)__xlx_apatb_param_se_conv_expand_weight)[i*4+0] = __xlx_se_conv_expand_weight_output_buffer[i].range(7, 0).to_uint();
    ((char*)__xlx_apatb_param_se_conv_expand_weight)[i*4+1] = __xlx_se_conv_expand_weight_output_buffer[i].range(15, 8).to_uint();
    ((char*)__xlx_apatb_param_se_conv_expand_weight)[i*4+2] = __xlx_se_conv_expand_weight_output_buffer[i].range(23, 16).to_uint();
    ((char*)__xlx_apatb_param_se_conv_expand_weight)[i*4+3] = __xlx_se_conv_expand_weight_output_buffer[i].range(31, 24).to_uint();
  }
// print __xlx_apatb_param_se_conv_expand_bias
  sc_bv<32>*__xlx_se_conv_expand_bias_output_buffer = new sc_bv<32>[__xlx_size_param_se_conv_expand_bias];
  for (int i = 0; i < __xlx_size_param_se_conv_expand_bias; ++i) {
    __xlx_se_conv_expand_bias_output_buffer[i] = __xlx_msp_conv_weight_msp_conv_bias_msp_norm_weight_msp_norm_bias_msp_norm_running_mean_msp_norm_running_var_dw_conv_weight_norm_1_weight_norm_1_bias_norm_1_running_mean_norm_1_running_var_se_conv_reduce_weight_se_conv_reduce_bias_se_conv_expand_weight_se_conv_expand_bias_proj_conv_weight__input_buffer[i+__xlx_offset_param_se_conv_expand_bias];
  }
  for (int i = 0; i < __xlx_size_param_se_conv_expand_bias; ++i) {
    ((char*)__xlx_apatb_param_se_conv_expand_bias)[i*4+0] = __xlx_se_conv_expand_bias_output_buffer[i].range(7, 0).to_uint();
    ((char*)__xlx_apatb_param_se_conv_expand_bias)[i*4+1] = __xlx_se_conv_expand_bias_output_buffer[i].range(15, 8).to_uint();
    ((char*)__xlx_apatb_param_se_conv_expand_bias)[i*4+2] = __xlx_se_conv_expand_bias_output_buffer[i].range(23, 16).to_uint();
    ((char*)__xlx_apatb_param_se_conv_expand_bias)[i*4+3] = __xlx_se_conv_expand_bias_output_buffer[i].range(31, 24).to_uint();
  }
// print __xlx_apatb_param_proj_conv_weight
  sc_bv<32>*__xlx_proj_conv_weight_output_buffer = new sc_bv<32>[__xlx_size_param_proj_conv_weight];
  for (int i = 0; i < __xlx_size_param_proj_conv_weight; ++i) {
    __xlx_proj_conv_weight_output_buffer[i] = __xlx_msp_conv_weight_msp_conv_bias_msp_norm_weight_msp_norm_bias_msp_norm_running_mean_msp_norm_running_var_dw_conv_weight_norm_1_weight_norm_1_bias_norm_1_running_mean_norm_1_running_var_se_conv_reduce_weight_se_conv_reduce_bias_se_conv_expand_weight_se_conv_expand_bias_proj_conv_weight__input_buffer[i+__xlx_offset_param_proj_conv_weight];
  }
  for (int i = 0; i < __xlx_size_param_proj_conv_weight; ++i) {
    ((char*)__xlx_apatb_param_proj_conv_weight)[i*4+0] = __xlx_proj_conv_weight_output_buffer[i].range(7, 0).to_uint();
    ((char*)__xlx_apatb_param_proj_conv_weight)[i*4+1] = __xlx_proj_conv_weight_output_buffer[i].range(15, 8).to_uint();
    ((char*)__xlx_apatb_param_proj_conv_weight)[i*4+2] = __xlx_proj_conv_weight_output_buffer[i].range(23, 16).to_uint();
    ((char*)__xlx_apatb_param_proj_conv_weight)[i*4+3] = __xlx_proj_conv_weight_output_buffer[i].range(31, 24).to_uint();
  }
// print __xlx_apatb_param_Y_msp_conv
  sc_bv<32>*__xlx_Y_msp_conv_output_buffer = new sc_bv<32>[__xlx_size_param_Y_msp_conv];
  for (int i = 0; i < __xlx_size_param_Y_msp_conv; ++i) {
    __xlx_Y_msp_conv_output_buffer[i] = __xlx_Y_msp_conv_Y_dw_act_Y_expand__input_buffer[i+__xlx_offset_param_Y_msp_conv];
  }
  for (int i = 0; i < __xlx_size_param_Y_msp_conv; ++i) {
    ((char*)__xlx_apatb_param_Y_msp_conv)[i*4+0] = __xlx_Y_msp_conv_output_buffer[i].range(7, 0).to_uint();
    ((char*)__xlx_apatb_param_Y_msp_conv)[i*4+1] = __xlx_Y_msp_conv_output_buffer[i].range(15, 8).to_uint();
    ((char*)__xlx_apatb_param_Y_msp_conv)[i*4+2] = __xlx_Y_msp_conv_output_buffer[i].range(23, 16).to_uint();
    ((char*)__xlx_apatb_param_Y_msp_conv)[i*4+3] = __xlx_Y_msp_conv_output_buffer[i].range(31, 24).to_uint();
  }
// print __xlx_apatb_param_Y_dw_act
  sc_bv<32>*__xlx_Y_dw_act_output_buffer = new sc_bv<32>[__xlx_size_param_Y_dw_act];
  for (int i = 0; i < __xlx_size_param_Y_dw_act; ++i) {
    __xlx_Y_dw_act_output_buffer[i] = __xlx_Y_msp_conv_Y_dw_act_Y_expand__input_buffer[i+__xlx_offset_param_Y_dw_act];
  }
  for (int i = 0; i < __xlx_size_param_Y_dw_act; ++i) {
    ((char*)__xlx_apatb_param_Y_dw_act)[i*4+0] = __xlx_Y_dw_act_output_buffer[i].range(7, 0).to_uint();
    ((char*)__xlx_apatb_param_Y_dw_act)[i*4+1] = __xlx_Y_dw_act_output_buffer[i].range(15, 8).to_uint();
    ((char*)__xlx_apatb_param_Y_dw_act)[i*4+2] = __xlx_Y_dw_act_output_buffer[i].range(23, 16).to_uint();
    ((char*)__xlx_apatb_param_Y_dw_act)[i*4+3] = __xlx_Y_dw_act_output_buffer[i].range(31, 24).to_uint();
  }
// print __xlx_apatb_param_Y_expand
  sc_bv<32>*__xlx_Y_expand_output_buffer = new sc_bv<32>[__xlx_size_param_Y_expand];
  for (int i = 0; i < __xlx_size_param_Y_expand; ++i) {
    __xlx_Y_expand_output_buffer[i] = __xlx_Y_msp_conv_Y_dw_act_Y_expand__input_buffer[i+__xlx_offset_param_Y_expand];
  }
  for (int i = 0; i < __xlx_size_param_Y_expand; ++i) {
    ((char*)__xlx_apatb_param_Y_expand)[i*4+0] = __xlx_Y_expand_output_buffer[i].range(7, 0).to_uint();
    ((char*)__xlx_apatb_param_Y_expand)[i*4+1] = __xlx_Y_expand_output_buffer[i].range(15, 8).to_uint();
    ((char*)__xlx_apatb_param_Y_expand)[i*4+2] = __xlx_Y_expand_output_buffer[i].range(23, 16).to_uint();
    ((char*)__xlx_apatb_param_Y_expand)[i*4+3] = __xlx_Y_expand_output_buffer[i].range(31, 24).to_uint();
  }
// print __xlx_apatb_param_Y_msp_norm
  sc_bv<32>*__xlx_Y_msp_norm_output_buffer = new sc_bv<32>[__xlx_size_param_Y_msp_norm];
  for (int i = 0; i < __xlx_size_param_Y_msp_norm; ++i) {
    __xlx_Y_msp_norm_output_buffer[i] = __xlx_Y_msp_norm_Y_mean_Y_sigmoid__input_buffer[i+__xlx_offset_param_Y_msp_norm];
  }
  for (int i = 0; i < __xlx_size_param_Y_msp_norm; ++i) {
    ((char*)__xlx_apatb_param_Y_msp_norm)[i*4+0] = __xlx_Y_msp_norm_output_buffer[i].range(7, 0).to_uint();
    ((char*)__xlx_apatb_param_Y_msp_norm)[i*4+1] = __xlx_Y_msp_norm_output_buffer[i].range(15, 8).to_uint();
    ((char*)__xlx_apatb_param_Y_msp_norm)[i*4+2] = __xlx_Y_msp_norm_output_buffer[i].range(23, 16).to_uint();
    ((char*)__xlx_apatb_param_Y_msp_norm)[i*4+3] = __xlx_Y_msp_norm_output_buffer[i].range(31, 24).to_uint();
  }
// print __xlx_apatb_param_Y_mean
  sc_bv<32>*__xlx_Y_mean_output_buffer = new sc_bv<32>[__xlx_size_param_Y_mean];
  for (int i = 0; i < __xlx_size_param_Y_mean; ++i) {
    __xlx_Y_mean_output_buffer[i] = __xlx_Y_msp_norm_Y_mean_Y_sigmoid__input_buffer[i+__xlx_offset_param_Y_mean];
  }
  for (int i = 0; i < __xlx_size_param_Y_mean; ++i) {
    ((char*)__xlx_apatb_param_Y_mean)[i*4+0] = __xlx_Y_mean_output_buffer[i].range(7, 0).to_uint();
    ((char*)__xlx_apatb_param_Y_mean)[i*4+1] = __xlx_Y_mean_output_buffer[i].range(15, 8).to_uint();
    ((char*)__xlx_apatb_param_Y_mean)[i*4+2] = __xlx_Y_mean_output_buffer[i].range(23, 16).to_uint();
    ((char*)__xlx_apatb_param_Y_mean)[i*4+3] = __xlx_Y_mean_output_buffer[i].range(31, 24).to_uint();
  }
// print __xlx_apatb_param_Y_sigmoid
  sc_bv<32>*__xlx_Y_sigmoid_output_buffer = new sc_bv<32>[__xlx_size_param_Y_sigmoid];
  for (int i = 0; i < __xlx_size_param_Y_sigmoid; ++i) {
    __xlx_Y_sigmoid_output_buffer[i] = __xlx_Y_msp_norm_Y_mean_Y_sigmoid__input_buffer[i+__xlx_offset_param_Y_sigmoid];
  }
  for (int i = 0; i < __xlx_size_param_Y_sigmoid; ++i) {
    ((char*)__xlx_apatb_param_Y_sigmoid)[i*4+0] = __xlx_Y_sigmoid_output_buffer[i].range(7, 0).to_uint();
    ((char*)__xlx_apatb_param_Y_sigmoid)[i*4+1] = __xlx_Y_sigmoid_output_buffer[i].range(15, 8).to_uint();
    ((char*)__xlx_apatb_param_Y_sigmoid)[i*4+2] = __xlx_Y_sigmoid_output_buffer[i].range(23, 16).to_uint();
    ((char*)__xlx_apatb_param_Y_sigmoid)[i*4+3] = __xlx_Y_sigmoid_output_buffer[i].range(31, 24).to_uint();
  }
// print __xlx_apatb_param_Y_dw_conv
  sc_bv<32>*__xlx_Y_dw_conv_output_buffer = new sc_bv<32>[__xlx_size_param_Y_dw_conv];
  for (int i = 0; i < __xlx_size_param_Y_dw_conv; ++i) {
    __xlx_Y_dw_conv_output_buffer[i] = __xlx_Y_dw_conv_Y_reduce_Y_se__input_buffer[i+__xlx_offset_param_Y_dw_conv];
  }
  for (int i = 0; i < __xlx_size_param_Y_dw_conv; ++i) {
    ((char*)__xlx_apatb_param_Y_dw_conv)[i*4+0] = __xlx_Y_dw_conv_output_buffer[i].range(7, 0).to_uint();
    ((char*)__xlx_apatb_param_Y_dw_conv)[i*4+1] = __xlx_Y_dw_conv_output_buffer[i].range(15, 8).to_uint();
    ((char*)__xlx_apatb_param_Y_dw_conv)[i*4+2] = __xlx_Y_dw_conv_output_buffer[i].range(23, 16).to_uint();
    ((char*)__xlx_apatb_param_Y_dw_conv)[i*4+3] = __xlx_Y_dw_conv_output_buffer[i].range(31, 24).to_uint();
  }
// print __xlx_apatb_param_Y_reduce
  sc_bv<32>*__xlx_Y_reduce_output_buffer = new sc_bv<32>[__xlx_size_param_Y_reduce];
  for (int i = 0; i < __xlx_size_param_Y_reduce; ++i) {
    __xlx_Y_reduce_output_buffer[i] = __xlx_Y_dw_conv_Y_reduce_Y_se__input_buffer[i+__xlx_offset_param_Y_reduce];
  }
  for (int i = 0; i < __xlx_size_param_Y_reduce; ++i) {
    ((char*)__xlx_apatb_param_Y_reduce)[i*4+0] = __xlx_Y_reduce_output_buffer[i].range(7, 0).to_uint();
    ((char*)__xlx_apatb_param_Y_reduce)[i*4+1] = __xlx_Y_reduce_output_buffer[i].range(15, 8).to_uint();
    ((char*)__xlx_apatb_param_Y_reduce)[i*4+2] = __xlx_Y_reduce_output_buffer[i].range(23, 16).to_uint();
    ((char*)__xlx_apatb_param_Y_reduce)[i*4+3] = __xlx_Y_reduce_output_buffer[i].range(31, 24).to_uint();
  }
// print __xlx_apatb_param_Y_se
  sc_bv<32>*__xlx_Y_se_output_buffer = new sc_bv<32>[__xlx_size_param_Y_se];
  for (int i = 0; i < __xlx_size_param_Y_se; ++i) {
    __xlx_Y_se_output_buffer[i] = __xlx_Y_dw_conv_Y_reduce_Y_se__input_buffer[i+__xlx_offset_param_Y_se];
  }
  for (int i = 0; i < __xlx_size_param_Y_se; ++i) {
    ((char*)__xlx_apatb_param_Y_se)[i*4+0] = __xlx_Y_se_output_buffer[i].range(7, 0).to_uint();
    ((char*)__xlx_apatb_param_Y_se)[i*4+1] = __xlx_Y_se_output_buffer[i].range(15, 8).to_uint();
    ((char*)__xlx_apatb_param_Y_se)[i*4+2] = __xlx_Y_se_output_buffer[i].range(23, 16).to_uint();
    ((char*)__xlx_apatb_param_Y_se)[i*4+3] = __xlx_Y_se_output_buffer[i].range(31, 24).to_uint();
  }
}
