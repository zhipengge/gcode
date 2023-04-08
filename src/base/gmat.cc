// @author: gezhipeng @ 20230930
// @file: gmat.cc
// @brief: gmat
#include "gmat.h"
#include "allocator.h"
#include "macro.h"
#include <cstring>
namespace gcode {
namespace base {
Mat::Mat() { release(); }

// vector
Mat::Mat(const size_t &_w, const size_t &_elemsize) {
  release();
  elemsize = _elemsize;
  dims = 1ul;
  w = wstride = _w;
  h = c = n = hstride = 1ul;
  create();
}
// 2d array
Mat::Mat(const size_t &_w, const size_t &_h, const size_t &_elemsize) {
  release();
  elemsize = _elemsize;
  dims = 2ul;
  w = _w;
  h = _h;
  c = n = 1ul;
  wstride = ALIGN_SIZE(w, ALIGN_STEP);
  hstride = ALIGN_SIZE(h, ALIGN_STEP);
  create();
}
// 3d array
Mat::Mat(const size_t &_w, const size_t &_h, const size_t &_c,
         const size_t &_elemsize) {
  release();
  elemsize = _elemsize;
  dims = 3ul;
  w = _w;
  h = _h;
  c = _c;
  n = 1ul;
  wstride = ALIGN_SIZE(w, ALIGN_STEP);
  hstride = ALIGN_SIZE(h, ALIGN_STEP);
  create();
}
// 4d array
Mat::Mat(const size_t &_w, const size_t &_h, const size_t &_c, const size_t &_n,
         const size_t &_elemsize) {
  release();
  elemsize = _elemsize;
  dims = 4ul;
  w = _w;
  h = _h;
  c = _c;
  n = _n;
  wstride = ALIGN_SIZE(w, ALIGN_STEP);
  hstride = ALIGN_SIZE(h, ALIGN_STEP);
  create();
}
// copy
Mat::Mat(const Mat &m)
    : data(m.data), refcount(m.refcount), elemsize(m.elemsize), dims(m.dims),
      w(m.w), h(m.h), c(m.c), n(m.n), wstride(m.wstride), hstride(m.hstride) {
  addref();
}
// vector
Mat::Mat(const size_t &_w, void *_data, const size_t &_elemsize) {
  release();
  if (_w > 0ul && _elemsize > 0ul && _data) {
    elemsize = _elemsize;
    dims = 1ul;
    w = wstride = _w;
    h = c = n = hstride = 1ul;
    create();
    if (data) {
      memcpy(data, _data, w * elemsize);
    }
  }
}
// 2d array
Mat::Mat(const size_t &_w, const size_t &_h, void *_data,
         const size_t &_elemsize) {
  release();
  if (_w > 0ul && _h > 0ul && _elemsize > 0ul && _data) {
    elemsize = _elemsize;
    dims = 2ul;
    w = _w;
    h = _h;
    c = n = 1ul;
    wstride = ALIGN_SIZE(w, ALIGN_STEP);
    hstride = ALIGN_SIZE(h, ALIGN_STEP);
    create();
    if (data) {
      for (size_t r = 0ul; r < h; ++r) {
        void *dst = Row(0ul, 0ul, r);
        void *src = (void *)((char *)_data + w * r * elemsize);
        memcpy(dst, src, w * elemsize);
      }
    }
  }
}
// 3d array
Mat::Mat(const size_t &_w, const size_t &_h, const size_t &_c, void *_data,
         const size_t &_elemsize) {
  release();
  if (_w > 0ul && _h > 0ul && _c > 0ul && _elemsize > 0ul && _data) {
    elemsize = _elemsize;
    dims = 3ul;
    w = _w;
    h = _h;
    c = _c;
    n = 1ul;
    wstride = ALIGN_SIZE(w, ALIGN_STEP);
    hstride = ALIGN_SIZE(h, ALIGN_STEP);
    create();
    if (data) {
      for (size_t ch = 0ul; ch < c; ++ch) {
        for (size_t r = 0ul; r < h; ++r) {
          void *dst = Row(0ul, ch, r);
          void *src = (void *)((char *)_data + (w * h * ch + w * r) * elemsize);
          memcpy(dst, src, w * elemsize);
        }
      }
    }
  }
}
// 4d array
Mat::Mat(const size_t &_w, const size_t &_h, const size_t &_c, const size_t &_n,
         void *_data, const size_t &_elemsize) {
  release();
  if (_w > 0ul && _h > 0ul && _c > 0ul && _n > 0ul && _elemsize > 0ul &&
      _data) {
    elemsize = _elemsize;
    dims = 4ul;
    w = _w;
    h = _h;
    c = _c;
    n = _n;
    wstride = ALIGN_SIZE(w, ALIGN_STEP);
    hstride = ALIGN_SIZE(h, ALIGN_STEP);
    create();
    if (data) {
      for (size_t bt = 0ul; bt < n; ++bt) {
        for (size_t ch = 0ul; ch < c; ++ch) {
          for (size_t r = 0ul; r < h; ++r) {
            void *dst = Row(bt, ch, r);
            void *src =
                (void *)((char *)_data +
                         (w * h * c * bt + w * h * ch + w * r) * elemsize);
            memcpy(dst, src, w * elemsize);
          }
        }
      }
    }
  }
}
// release
Mat::~Mat() { release(); }

void Mat::create() {
  size_t total_size = total() * elemsize;
  data = FastMalloc(total_size + sizeof(*refcount));
  if (data) {
    refcount = (size_t *)(((char *)data) + total_size);
    *refcount = 1ul;
  }
}

void Mat::addref() {
  if (refcount) {
    *refcount += 1;
  }
}

void Mat::release() {
  if (refcount && *refcount == 1) {
    FastFree(data);
  }
  data = nullptr;
  elemsize = 0;
  dims = w = h = c = n = wstride = hstride = 0ul;
  refcount = nullptr;
}

Mat &Mat::operator=(const Mat &m) {
  if (this == &m) {
    return *this;
  }
  if (m.refcount) {
    *m.refcount += 1;
  }
  release();
  data = m.data;
  refcount = m.refcount;
  elemsize = m.elemsize;
  dims = m.dims;
  w = m.w;
  h = m.h;
  c = m.c;
  n = m.n;
  wstride = m.wstride;
  hstride = m.hstride;
  return *this;
}

Mat Mat::clone() const {
  if (empty()) {
    return Mat();
  }
  Mat m;
  m.w = w;
  m.h = h;
  m.c = c;
  m.n = n;
  m.wstride = wstride;
  m.hstride = hstride;
  m.dims = dims;
  m.create();
  return m;
}

void Mat::from_image(unsigned char *_data, const size_t &_w, const size_t &_h,
                     const size_t &_ch) {
  release();
  if (_data && _w > 0 && _h > 0 && _ch > 0 && _ch <= 4ul) {
    w = _w;
    h = _h;
    c = _ch;
    n = 1ul;
    dims = 3ul;
    elemsize = sizeof(unsigned char);

    wstride = ALIGN_SIZE(w, ALIGN_STEP);
    hstride = ALIGN_SIZE(h, ALIGN_STEP);
    create();
    if (c == 1) {
      for (size_t r = 0ul; r < _h; ++r) {
        void *dst = (void *)((unsigned char *)data + r * wstride);
        void *src = (void *)(_data + r * w * elemsize);
        memcpy(dst, src, w * elemsize);
      }
    } else {
      for (size_t row = 0ul; row < _h; ++row) {
        size_t col = 0ul;
#ifdef ENABLE_ARM_NEON
        for (; col < _w - 15ul; col += 16) {
          uint8_t *src_ptr = _data + (row * _w + col) * c;
          if (c == 2ul) {
            uint8x16x2_t neon_pixels = vld2q_u8(src_ptr);
            for (size_t ch = 0; ch < c; ++ch) {
              vst1q_u8((unsigned char *)Row(0ul, ch, row) + col,
                       neon_pixels.val[ch]);
            }
          } else if (c == 3ul) {
            uint8x16x3_t neon_pixels = vld3q_u8(src_ptr);
            for (size_t ch = 0; ch < c; ++ch) {
              vst1q_u8((unsigned char *)Row(0ul, ch, row) + col,
                       neon_pixels.val[ch]);
            }
          } else if (c == 4ul) {
            uint8x16x4_t neon_pixels = vld4q_u8(src_ptr);
            for (size_t ch = 0; ch < c; ++ch) {
              vst1q_u8((unsigned char *)Row(0ul, ch, row) + col,
                       neon_pixels.val[ch]);
            }
          }
        }
#endif
        for (; col < _w; ++col) {
          for (size_t ch = 0ul; ch < _ch; ++ch) {
            size_t src_index = row * _w * _ch + col * _ch + ch;
            size_t dst_index = ch * w * h + row * w + col;
            ((unsigned char *)data)[dst_index] = _data[src_index];
          }
        }
      }
    }
  }
}

void Mat::to_image(unsigned char *_data, size_t *_w, size_t *_h,
                   size_t *_ch) const {
  if (nullptr == _data || empty()) {
    return;
  }
  *_w = w;
  *_h = h;
  *_ch = c;
  if (c == 1) {
    for (size_t r = 0ul; r < *_h; ++r) {
      void *src = (void *)((unsigned char *)data + r * wstride);
      void *dst = (void *)(_data + r * w);
      memcpy(dst, src, w * elemsize);
    }
  } else {
    for (size_t r = 0ul; r < *_h; ++r) {
      for (size_t col = 0ul; col < *_w; ++col) {
        for (size_t ch = 0ul; ch < *_ch; ++ch) {
          size_t dst_index = r * (*_w) * (*_ch) + col * (*_ch) + ch;
          size_t src_index = ch * w * h + r * w + col;
          _data[dst_index] = ((unsigned char *)data)[src_index];
        }
      }
    }
  }
}
} // namespace base
} // namespace gcode
