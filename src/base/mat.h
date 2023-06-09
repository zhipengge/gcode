// @author: gezhipeng @ 20230409
// @file: mat.h
// @brief: mat
#ifndef SRC_BASE_MAT_H_
#define SRC_BASE_MAT_H_
#include "allocator.h"
#include "pixel.h"
#include <iostream>
namespace gcode {
namespace base {
// class for Mat
class Mat {
public:
  // empty
  Mat();
  // vec
  Mat(int w, size_t elemsize = 4u, Allocator *allocator = 0);
  // image
  Mat(int w, int h, size_t elemsize = 4u, Allocator *allocator = 0);
  // dim
  Mat(int w, int h, int c, size_t elemsize = 4u, Allocator *allocator = 0);
  // cube
  Mat(int w, int h, int d, int c, size_t elemsize = 4u,
      Allocator *allocator = 0);
  // packed vec
  Mat(int w, size_t elemsize, int elempack, Allocator *allocator = 0);
  // packed image
  Mat(int w, int h, size_t elemsize, int elempack, Allocator *allocator = 0);
  // packed dim
  Mat(int w, int h, int c, size_t elemsize, int elempack,
      Allocator *allocator = 0);
  // packed cube
  Mat(int w, int h, int d, int c, size_t elemsize, int elempack,
      Allocator *allocator = 0);
  // copy
  Mat(const Mat &m);
  // external vec
  Mat(int w, void *data, size_t elemsize = 4u, Allocator *allocator = 0);
  // external image
  Mat(int w, int h, void *data, size_t elemsize = 4u, Allocator *allocator = 0);
  // external dim
  Mat(int w, int h, int c, void *data, size_t elemsize = 4u,
      Allocator *allocator = 0);
  // external cube
  Mat(int w, int h, int d, int c, void *data, size_t elemsize = 4u,
      Allocator *allocator = 0);
  // external packed vec
  Mat(int w, void *data, size_t elemsize, int elempack,
      Allocator *allocator = 0);
  // external packed image
  Mat(int w, int h, void *data, size_t elemsize, int elempack,
      Allocator *allocator = 0);
  // external packed dim
  Mat(int w, int h, int c, void *data, size_t elemsize, int elempack,
      Allocator *allocator = 0);
  // external packed cube
  Mat(int w, int h, int d, int c, void *data, size_t elemsize, int elempack,
      Allocator *allocator = 0);
  // release
  ~Mat();
  // assign
  Mat &operator=(const Mat &m);
  // set all
  void fill(float v);
  void fill(int v);
  template <typename T> void fill(T v);
  // deep copy
  Mat clone(Allocator *allocator = 0) const;
  // deep copy from other mat, inplace
  void clone_from(const Mat &mat, Allocator *allocator = 0);
  // reshape vec
  Mat reshape(int w, Allocator *allocator = 0) const;
  // reshape image
  Mat reshape(int w, int h, Allocator *allocator = 0) const;
  // reshape dim
  Mat reshape(int w, int h, int c, Allocator *allocator = 0) const;
  // reshape cube
  Mat reshape(int w, int h, int d, int c, Allocator *allocator = 0) const;
  // allocate vec
  void create(int w, size_t elemsize = 4u, Allocator *allocator = 0);
  // allocate image
  void create(int w, int h, size_t elemsize = 4u, Allocator *allocator = 0);
  // allocate dim
  void create(int w, int h, int c, size_t elemsize = 4u,
              Allocator *allocator = 0);
  // allocate cube
  void create(int w, int h, int d, int c, size_t elemsize = 4u,
              Allocator *allocator = 0);
  // allocate packed vec
  void create(int w, size_t elemsize, int elempack, Allocator *allocator = 0);
  // allocate packed image
  void create(int w, int h, size_t elemsize, int elempack,
              Allocator *allocator = 0);
  // allocate packed dim
  void create(int w, int h, int c, size_t elemsize, int elempack,
              Allocator *allocator = 0);
  // allocate packed cube
  void create(int w, int h, int d, int c, size_t elemsize, int elempack,
              Allocator *allocator = 0);
  // allocate like
  void create_like(const Mat &m, Allocator *allocator = 0);
  // refcount++
  void addref();
  // refcount--
  void release();

  bool empty() const;
  size_t total() const;

  // bits per element
  int elembits() const;

  // shape only
  Mat shape() const;

  // data reference
  Mat channel(int c);
  const Mat channel(int c) const;
  Mat depth(int z);
  const Mat depth(int z) const;
  float *row(int y);
  const float *row(int y) const;
  template <typename T> T *row(int y);
  template <typename T> const T *row(int y) const;

  // range reference
  Mat channel_range(int c, int channels);
  const Mat channel_range(int c, int channels) const;
  Mat depth_range(int z, int depths);
  const Mat depth_range(int z, int depths) const;
  Mat row_range(int y, int rows);
  const Mat row_range(int y, int rows) const;
  Mat range(int x, int n);
  const Mat range(int x, int n) const;

  // access raw data
  template <typename T> operator T *();
  template <typename T> operator const T *() const;

  // convenient access float vec element
  float &operator[](size_t i);
  const float &operator[](size_t i) const;
  // convenient construct from pixel data
  static Mat from_pixels(const unsigned char *pixels, int type, int w, int h,
                         Allocator *allocator = 0);
  // convenient construct from pixel data with stride(bytes-per-row) parameter
  static Mat from_pixels(const unsigned char *pixels, int type, int w, int h,
                         int stride, Allocator *allocator = 0);
  // convenient construct from pixel data and resize to specific size
  static Mat from_pixels_resize(const unsigned char *pixels, int type, int w,
                                int h, int target_width, int target_height,
                                Allocator *allocator = 0);
  // convenient construct from pixel data and resize to specific size with
  // stride(bytes-per-row) parameter
  static Mat from_pixels_resize(const unsigned char *pixels, int type, int w,
                                int h, int stride, int target_width,
                                int target_height, Allocator *allocator = 0);
  // convenient construct from pixel data roi
  static Mat from_pixels_roi(const unsigned char *pixels, int type, int w,
                             int h, int roix, int roiy, int roiw, int roih,
                             Allocator *allocator = 0);
  // convenient construct from pixel data roi with stride(bytes-per-row)
  // parameter
  static Mat from_pixels_roi(const unsigned char *pixels, int type, int w,
                             int h, int stride, int roix, int roiy, int roiw,
                             int roih, Allocator *allocator = 0);
  // convenient construct from pixel data roi and resize to specific size
  static Mat from_pixels_roi_resize(const unsigned char *pixels, int type,
                                    int w, int h, int roix, int roiy, int roiw,
                                    int roih, int target_width,
                                    int target_height,
                                    Allocator *allocator = 0);
  // convenient construct from pixel data roi and resize to specific size with
  // stride(bytes-per-row) parameter
  static Mat from_pixels_roi_resize(const unsigned char *pixels, int type,
                                    int w, int h, int stride, int roix,
                                    int roiy, int roiw, int roih,
                                    int target_width, int target_height,
                                    Allocator *allocator = 0);

  // convenient export to pixel data
  void to_pixels(unsigned char *pixels, int type) const;
  // convenient export to pixel data with stride(bytes-per-row) parameter
  void to_pixels(unsigned char *pixels, int type, int stride) const;
  // convenient export to pixel data and resize to specific size
  void to_pixels_resize(unsigned char *pixels, int type, int target_width,
                        int target_height) const;
  // convenient export to pixel data and resize to specific size with
  // stride(bytes-per-row) parameter
  void to_pixels_resize(unsigned char *pixels, int type, int target_width,
                        int target_height, int target_stride) const;
  // substract channel-wise mean values, then multiply by normalize values, pass
  // 0 to skip
  void substract_mean_normalize(const float *mean_vals, const float *norm_vals);

  // convenient construct from half precision floating point data
  static Mat from_float16(const unsigned short *data, int size);

  // pointer to the data
  void *data;

  // pointer to the reference counter
  // when points to user-allocated data, the pointer is NULL
  int *refcount;

  // element size in bytes
  // 4 = float32/int32
  // 2 = float16
  // 1 = int8/uint8
  // 0 = empty
  size_t elemsize;

  // packed count inside element
  // c/1-d-h-w-1  c/1-h-w-1  h/1-w-1  w/1-1  scalar
  // c/4-d-h-w-4  c/4-h-w-4  h/4-w-4  w/4-4  sse/neon
  // c/8-d-h-w-8  c/8-h-w-8  h/8-w-8  w/8-8  avx/fp16
  int elempack;

  // the allocator
  Allocator *allocator;

  // the dimension rank
  int dims;

  int w;
  int h;
  int d;
  int c;

  size_t cstep;

}; // class Mat
inline Mat::Mat()
    : data(0), refcount(0), elemsize(0), elempack(0), allocator(0), dims(0),
      w(0), h(0), d(0), c(0), cstep(0) {}

inline Mat::Mat(int _w, size_t _elemsize, Allocator *_allocator)
    : data(0), refcount(0), elemsize(0), elempack(0), allocator(0), dims(0),
      w(0), h(0), d(0), c(0), cstep(0) {
  create(_w, _elemsize, _allocator);
}

inline Mat::Mat(int _w, int _h, size_t _elemsize, Allocator *_allocator)
    : data(0), refcount(0), elemsize(0), elempack(0), allocator(0), dims(0),
      w(0), h(0), d(0), c(0), cstep(0) {
  create(_w, _h, _elemsize, _allocator);
}

inline Mat::Mat(int _w, int _h, int _c, size_t _elemsize, Allocator *_allocator)
    : data(0), refcount(0), elemsize(0), elempack(0), allocator(0), dims(0),
      w(0), h(0), d(0), c(0), cstep(0) {
  create(_w, _h, _c, _elemsize, _allocator);
}

inline Mat::Mat(int _w, int _h, int _d, int _c, size_t _elemsize,
                Allocator *_allocator)
    : data(0), refcount(0), elemsize(0), elempack(0), allocator(0), dims(0),
      w(0), h(0), d(0), c(0), cstep(0) {
  create(_w, _h, _d, _c, _elemsize, _allocator);
}

inline Mat::Mat(int _w, size_t _elemsize, int _elempack, Allocator *_allocator)
    : data(0), refcount(0), elemsize(0), elempack(0), allocator(0), dims(0),
      w(0), h(0), d(0), c(0), cstep(0) {
  create(_w, _elemsize, _elempack, _allocator);
}

inline Mat::Mat(int _w, int _h, size_t _elemsize, int _elempack,
                Allocator *_allocator)
    : data(0), refcount(0), elemsize(0), elempack(0), allocator(0), dims(0),
      w(0), h(0), d(0), c(0), cstep(0) {
  create(_w, _h, _elemsize, _elempack, _allocator);
}

inline Mat::Mat(int _w, int _h, int _c, size_t _elemsize, int _elempack,
                Allocator *_allocator)
    : data(0), refcount(0), elemsize(0), elempack(0), allocator(0), dims(0),
      w(0), h(0), d(0), c(0), cstep(0) {
  create(_w, _h, _c, _elemsize, _elempack, _allocator);
}

inline Mat::Mat(int _w, int _h, int _d, int _c, size_t _elemsize, int _elempack,
                Allocator *_allocator)
    : data(0), refcount(0), elemsize(0), elempack(0), allocator(0), dims(0),
      w(0), h(0), d(0), c(0), cstep(0) {
  create(_w, _h, _d, _c, _elemsize, _elempack, _allocator);
}

inline Mat::Mat(const Mat &m)
    : data(m.data), refcount(m.refcount), elemsize(m.elemsize),
      elempack(m.elempack), allocator(m.allocator), dims(m.dims), w(m.w),
      h(m.h), d(m.d), c(m.c), cstep(m.cstep) {
  addref();
}

inline Mat::Mat(int _w, void *_data, size_t _elemsize, Allocator *_allocator)
    : data(_data), refcount(0), elemsize(_elemsize), elempack(1),
      allocator(_allocator), dims(1), w(_w), h(1), d(1), c(1) {
  cstep = w;
}

inline Mat::Mat(int _w, int _h, void *_data, size_t _elemsize,
                Allocator *_allocator)
    : data(_data), refcount(0), elemsize(_elemsize), elempack(1),
      allocator(_allocator), dims(2), w(_w), h(_h), d(1), c(1) {
  cstep = (size_t)w * h;
}

inline Mat::Mat(int _w, int _h, int _c, void *_data, size_t _elemsize,
                Allocator *_allocator)
    : data(_data), refcount(0), elemsize(_elemsize), elempack(1),
      allocator(_allocator), dims(3), w(_w), h(_h), d(1), c(_c) {
  cstep = alignSize((size_t)w * h * elemsize, 16) / elemsize;
}

inline Mat::Mat(int _w, int _h, int _d, int _c, void *_data, size_t _elemsize,
                Allocator *_allocator)
    : data(_data), refcount(0), elemsize(_elemsize), elempack(1),
      allocator(_allocator), dims(4), w(_w), h(_h), d(_d), c(_c) {
  cstep = alignSize((size_t)w * h * d * elemsize, 16) / elemsize;
}

inline Mat::Mat(int _w, void *_data, size_t _elemsize, int _elempack,
                Allocator *_allocator)
    : data(_data), refcount(0), elemsize(_elemsize), elempack(_elempack),
      allocator(_allocator), dims(1), w(_w), h(1), d(1), c(1) {
  cstep = w;
}

inline Mat::Mat(int _w, int _h, void *_data, size_t _elemsize, int _elempack,
                Allocator *_allocator)
    : data(_data), refcount(0), elemsize(_elemsize), elempack(_elempack),
      allocator(_allocator), dims(2), w(_w), h(_h), d(1), c(1) {
  cstep = (size_t)w * h;
}

inline Mat::Mat(int _w, int _h, int _c, void *_data, size_t _elemsize,
                int _elempack, Allocator *_allocator)
    : data(_data), refcount(0), elemsize(_elemsize), elempack(_elempack),
      allocator(_allocator), dims(3), w(_w), h(_h), d(1), c(_c) {
  cstep = alignSize((size_t)w * h * elemsize, 16) / elemsize;
}

inline Mat::Mat(int _w, int _h, int _d, int _c, void *_data, size_t _elemsize,
                int _elempack, Allocator *_allocator)
    : data(_data), refcount(0), elemsize(_elemsize), elempack(_elempack),
      allocator(_allocator), dims(4), w(_w), h(_h), d(_d), c(_c) {
  cstep = alignSize((size_t)w * h * d * elemsize, 16) / elemsize;
}

inline Mat::~Mat() { release(); }

inline void Mat::fill(float _v) {
  int size = (int)total();
  float *ptr = (float *)data;

  int i = 0;
  for (; i < size; i++) {
    *ptr++ = _v;
  }
}

inline void Mat::fill(int _v) {
  int size = (int)total();
  int *ptr = (int *)data;

  int i = 0;
  for (; i < size; i++) {
    *ptr++ = _v;
  }
}
template <typename T> inline void Mat::fill(T _v) {
  int size = (int)total();
  T *ptr = (T *)data;
  for (int i = 0; i < size; i++) {
    ptr[i] = _v;
  }
}

inline Mat &Mat::operator=(const Mat &m) {
  if (this == &m)
    return *this;

  if (m.refcount)
    NCNN_XADD(m.refcount, 1);

  release();

  data = m.data;
  refcount = m.refcount;
  elemsize = m.elemsize;
  elempack = m.elempack;
  allocator = m.allocator;

  dims = m.dims;
  w = m.w;
  h = m.h;
  d = m.d;
  c = m.c;

  cstep = m.cstep;

  return *this;
}

inline void Mat::addref() {
  if (refcount)
    NCNN_XADD(refcount, 1);
}

inline void Mat::release() {
  if (refcount && NCNN_XADD(refcount, -1) == 1) {
    if (allocator)
      allocator->fastFree(data);
    else
      fastFree(data);
  }

  data = 0;

  elemsize = 0;
  elempack = 0;

  dims = 0;
  w = 0;
  h = 0;
  d = 0;
  c = 0;

  cstep = 0;

  refcount = 0;
}

inline bool Mat::empty() const { return data == 0 || total() == 0; }

inline size_t Mat::total() const { return cstep * c; }

inline int Mat::elembits() const {
  return elempack ? static_cast<int>(elemsize * 8) / elempack : 0;
}

inline Mat Mat::shape() const {
  if (dims == 1)
    return Mat(w * elempack, (void *)0);
  if (dims == 2)
    return Mat(w, h * elempack, (void *)0);
  if (dims == 3)
    return Mat(w, h, c * elempack, (void *)0);
  if (dims == 4)
    return Mat(w, h, d, c * elempack, (void *)0);

  return Mat();
}

inline Mat Mat::channel(int _c) {
  Mat m(w, h, d, (unsigned char *)data + cstep * _c * elemsize, elemsize,
        elempack, allocator);
  m.dims = dims - 1;
  if (dims == 4)
    m.cstep = (size_t)w * h;
  return m;
}

inline const Mat Mat::channel(int _c) const {
  Mat m(w, h, d, (unsigned char *)data + cstep * _c * elemsize, elemsize,
        elempack, allocator);
  m.dims = dims - 1;
  if (dims == 4)
    m.cstep = (size_t)w * h;
  return m;
}

inline Mat Mat::depth(int z) {
  return Mat(w, h, (unsigned char *)data + (size_t)w * h * z * elemsize,
             elemsize, elempack, allocator);
}

inline const Mat Mat::depth(int z) const {
  return Mat(w, h, (unsigned char *)data + (size_t)w * h * z * elemsize,
             elemsize, elempack, allocator);
}

inline float *Mat::row(int y) {
  return (float *)((unsigned char *)data + (size_t)w * y * elemsize);
}

inline const float *Mat::row(int y) const {
  return (const float *)((unsigned char *)data + (size_t)w * y * elemsize);
}

template <typename T> inline T *Mat::row(int y) {
  return (T *)((unsigned char *)data + (size_t)w * y * elemsize);
}

template <typename T> inline const T *Mat::row(int y) const {
  return (const T *)((unsigned char *)data + (size_t)w * y * elemsize);
}

inline Mat Mat::channel_range(int _c, int channels) {
  Mat m(w, h, d, channels, (unsigned char *)data + cstep * _c * elemsize,
        elemsize, elempack, allocator);
  m.dims = dims;
  return m;
}

inline const Mat Mat::channel_range(int _c, int channels) const {
  Mat m(w, h, d, channels, (unsigned char *)data + cstep * _c * elemsize,
        elemsize, elempack, allocator);
  m.dims = dims;
  return m;
}

inline Mat Mat::depth_range(int z, int depths) {
  Mat m(w, h, depths, (unsigned char *)data + (size_t)w * h * z * elemsize,
        elemsize, elempack, allocator);
  m.cstep = (size_t)w * h;
  return m;
}

inline const Mat Mat::depth_range(int z, int depths) const {
  Mat m(w, h, depths, (unsigned char *)data + (size_t)w * h * z * elemsize,
        elemsize, elempack, allocator);
  m.cstep = (size_t)w * h;
  return m;
}

inline Mat Mat::row_range(int y, int rows) {
  return Mat(w, rows, (unsigned char *)data + (size_t)w * y * elemsize,
             elemsize, elempack, allocator);
}

inline const Mat Mat::row_range(int y, int rows) const {
  return Mat(w, rows, (unsigned char *)data + (size_t)w * y * elemsize,
             elemsize, elempack, allocator);
}

inline Mat Mat::range(int x, int n) {
  return Mat(n, (unsigned char *)data + x * elemsize, elemsize, elempack,
             allocator);
}

inline const Mat Mat::range(int x, int n) const {
  return Mat(n, (unsigned char *)data + x * elemsize, elemsize, elempack,
             allocator);
}

template <typename T> inline Mat::operator T *() { return (T *)data; }

template <typename T> inline Mat::operator const T *() const {
  return (const T *)data;
}

inline float &Mat::operator[](size_t i) { return ((float *)data)[i]; }

inline const float &Mat::operator[](size_t i) const {
  return ((const float *)data)[i];
}
} // namespace base

} // namespace gcode

#endif // SRC_BASE_MAT_H_