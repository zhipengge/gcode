// @author: gezhipeng @ 20230930
// @file: gmat.h
// @brief: gmat
#ifndef SRC_BASE_GMAT_H_
#define SRC_BASE_GMAT_H_
#include <iostream>
#define ALIGN_SIZE(sz, n) ((sz + n - 1) & -n)
#define ALIGN_STEP 8
namespace gcode {
/**
 * class Mat
 * 4D at most:
 * 1D array, no align
 * 2D/3D/4D array force align to size 8
 */
class Mat {
public:
  Mat();
  // vector
  Mat(const size_t &_w, const size_t &_elemsize);
  // 2d array
  Mat(const size_t &_w, const size_t &_h, const size_t &_elemsize);
  // 3d array
  Mat(const size_t &_w, const size_t &_h, const size_t &_c,
      const size_t &_elemsize);
  // 4d array
  Mat(const size_t &_w, const size_t &_h, const size_t &_c, const size_t &_n,
      const size_t &_elemsize);
  // copy
  Mat(const Mat &m);
  // vector
  Mat(const size_t &_w, void *_data, const size_t &_elemsize);
  // 2d array
  Mat(const size_t &_w, const size_t &_h, void *_data, const size_t &_elemsize);
  // 3d array
  Mat(const size_t &_w, const size_t &_h, const size_t &_c, void *_data,
      const size_t &_elemsize);
  // 4d array
  Mat(const size_t &_w, const size_t &_h, const size_t &_c, const size_t &_n,
      void *_data, const size_t &_elemsize);
  // release
  ~Mat();
  // operator
  Mat &operator=(const Mat &m);
  // fill
  template <typename T> void fill(const T &v);
  void release();
  void create();
  // refcount++
  void addref();
  Mat clone() const;
  size_t total() const;
  bool empty() const;

  void *Batch(const size_t &bt) const;
  void *Channel(const size_t &bt, const size_t &ch) const;
  void *Row(const size_t &bt, const size_t &ch, const size_t &row) const;
  void FromImage(unsigned char *_data, const size_t &_w, const size_t &_h,
                 const size_t &_ch);
  void ToImage(unsigned char *_data, size_t *_w, size_t *_h, size_t *_ch) const;

public:
  void *data = nullptr;
  size_t *refcount = nullptr;
  size_t elemsize = 0u;

  size_t dims = 0u; // dimensions of mat
  size_t w = 0ul;   // width
  size_t h = 0ul;   // height
  size_t c = 0ul;   // channel
  size_t n = 0ul;   // batch size

  size_t wstride = 0ul;
  size_t hstride = 0ul;
};
inline size_t Mat::total() const { return wstride * hstride * c * n; }
template <typename T> inline void Mat::fill(const T &v) {
  T *ptr = (T *)data;
  for (size_t i = 0; i < total(); ++i) {
    ptr[i] = v;
  }
}
inline bool Mat::empty() const { return data == nullptr || total() == 0ul; }
inline void *Mat::Batch(const size_t &bt) const {
  if (empty() || bt > n) {
    return nullptr;
  }
  return (void *)((char *)data + (wstride * hstride * c * bt * elemsize));
}
inline void *Mat::Channel(const size_t &bt, const size_t &ch) const {
  if (empty() || bt > n || ch > c) {
    return nullptr;
  }
  return (void *)((char *)data +
                  (wstride * hstride * c * bt + wstride * hstride * ch) *
                      elemsize);
}
inline void *Mat::Row(const size_t &bt, const size_t &ch,
                      const size_t &r) const {
  if (empty() || bt > n || ch > c || r > hstride) {
    return nullptr;
  }
  return (void *)((char *)data + (wstride * hstride * c * bt +
                                  wstride * hstride * ch + wstride * r) *
                                     elemsize);
}
} // namespace gcode
#endif // SRC_BASE_GMAT_H_