// @author: gezhipeng @ 20230409
// @file: mat.cc
// @brief: mat
#include "mat.h"
#include <string.h>
namespace gcode {
namespace base {
Mat Mat::clone(Allocator *_allocator) const {
  if (empty())
    return Mat();

  Mat m;
  if (dims == 1)
    m.create(w, elemsize, elempack, _allocator);
  else if (dims == 2)
    m.create(w, h, elemsize, elempack, _allocator);
  else if (dims == 3)
    m.create(w, h, c, elemsize, elempack, _allocator);
  else if (dims == 4)
    m.create(w, h, d, c, elemsize, elempack, _allocator);

  if (total() > 0) {
    if (cstep == m.cstep)
      memcpy(m.data, data, total() * elemsize);
    else {
      // copy by channel for differnet cstep
      size_t size = (size_t)w * h * d * elemsize;
      for (int i = 0; i < c; i++) {
        memcpy(m.channel(i), channel(i), size);
      }
    }
  }

  return m;
}

void Mat::clone_from(const Mat &mat, Allocator *allocator) {
  *this = mat.clone(allocator);
}

Mat Mat::reshape(int _w, Allocator *_allocator) const {
  if (w * h * d * c != _w)
    return Mat();

  if (dims >= 3 && cstep != (size_t)w * h * d) {
    Mat m;
    m.create(_w, elemsize, elempack, _allocator);

    // flatten
    for (int i = 0; i < c; i++) {
      const void *ptr = (unsigned char *)data + i * cstep * elemsize;
      void *mptr = (unsigned char *)m.data + (size_t)i * w * h * d * elemsize;
      memcpy(mptr, ptr, (size_t)w * h * d * elemsize);
    }

    return m;
  }

  Mat m = *this;

  m.dims = 1;
  m.w = _w;
  m.h = 1;
  m.d = 1;
  m.c = 1;

  m.cstep = _w;

  return m;
}

Mat Mat::reshape(int _w, int _h, Allocator *_allocator) const {
  if (w * h * d * c != _w * _h)
    return Mat();

  if (dims >= 3 && cstep != (size_t)w * h * d) {
    Mat m;
    m.create(_w, _h, elemsize, elempack, _allocator);

    // flatten
    for (int i = 0; i < c; i++) {
      const void *ptr = (unsigned char *)data + i * cstep * elemsize;
      void *mptr = (unsigned char *)m.data + (size_t)i * w * h * d * elemsize;
      memcpy(mptr, ptr, (size_t)w * h * d * elemsize);
    }

    return m;
  }

  Mat m = *this;

  m.dims = 2;
  m.w = _w;
  m.h = _h;
  m.d = 1;
  m.c = 1;

  m.cstep = (size_t)_w * _h;

  return m;
}

Mat Mat::reshape(int _w, int _h, int _c, Allocator *_allocator) const {
  if (w * h * d * c != _w * _h * _c)
    return Mat();

  if (dims < 3) {
    if ((size_t)_w * _h !=
        alignSize((size_t)_w * _h * elemsize, 16) / elemsize) {
      Mat m;
      m.create(_w, _h, _c, elemsize, elempack, _allocator);

      // align channel
      for (int i = 0; i < _c; i++) {
        const void *ptr =
            (unsigned char *)data + (size_t)i * _w * _h * elemsize;
        void *mptr = (unsigned char *)m.data + i * m.cstep * m.elemsize;
        memcpy(mptr, ptr, (size_t)_w * _h * elemsize);
      }

      return m;
    }
  } else if (c != _c) {
    // flatten and then align
    Mat tmp = reshape(_w * _h * _c, _allocator);
    return tmp.reshape(_w, _h, _c, _allocator);
  }

  Mat m = *this;

  m.dims = 3;
  m.w = _w;
  m.h = _h;
  m.d = 1;
  m.c = _c;

  m.cstep = alignSize((size_t)_w * _h * elemsize, 16) / elemsize;

  return m;
}

Mat Mat::reshape(int _w, int _h, int _d, int _c, Allocator *_allocator) const {
  if (w * h * d * c != _w * _h * _d * _c)
    return Mat();

  if (dims < 3) {
    if ((size_t)_w * _h * _d !=
        alignSize((size_t)_w * _h * _d * elemsize, 16) / elemsize) {
      Mat m;
      m.create(_w, _h, _d, _c, elemsize, elempack, _allocator);

      // align channel
      for (int i = 0; i < _c; i++) {
        const void *ptr =
            (unsigned char *)data + (size_t)i * _w * _h * _d * elemsize;
        void *mptr = (unsigned char *)m.data + i * m.cstep * m.elemsize;
        memcpy(mptr, ptr, (size_t)_w * _h * _d * elemsize);
      }

      return m;
    }
  } else if (c != _c) {
    // flatten and then align
    Mat tmp = reshape(_w * _h * _d * _c, _allocator);
    return tmp.reshape(_w, _h, _d, _c, _allocator);
  }

  Mat m = *this;

  m.dims = 4;
  m.w = _w;
  m.h = _h;
  m.d = _d;
  m.c = _c;

  m.cstep = alignSize((size_t)_w * _h * _d * elemsize, 16) / elemsize;

  return m;
}

void Mat::create(int _w, size_t _elemsize, Allocator *_allocator) {
  if (dims == 1 && w == _w && elemsize == _elemsize && elempack == 1 &&
      allocator == _allocator)
    return;

  release();

  elemsize = _elemsize;
  elempack = 1;
  allocator = _allocator;

  dims = 1;
  w = _w;
  h = 1;
  d = 1;
  c = 1;

  cstep = w;

  size_t totalsize = alignSize(total() * elemsize, 4);
  if (totalsize > 0) {
    if (allocator)
      data = allocator->fastMalloc(totalsize + (int)sizeof(*refcount));
    else
      data = fastMalloc(totalsize + (int)sizeof(*refcount));
  }

  if (data) {
    refcount = (int *)(((unsigned char *)data) + totalsize);
    *refcount = 1;
  }
}

void Mat::create(int _w, int _h, size_t _elemsize, Allocator *_allocator) {
  if (dims == 2 && w == _w && h == _h && elemsize == _elemsize &&
      elempack == 1 && allocator == _allocator)
    return;

  release();

  elemsize = _elemsize;
  elempack = 1;
  allocator = _allocator;

  dims = 2;
  w = _w;
  h = _h;
  d = 1;
  c = 1;

  cstep = (size_t)w * h;

  size_t totalsize = alignSize(total() * elemsize, 4);
  if (totalsize > 0) {
    if (allocator)
      data = allocator->fastMalloc(totalsize + (int)sizeof(*refcount));
    else
      data = fastMalloc(totalsize + (int)sizeof(*refcount));
  }

  if (data) {
    refcount = (int *)(((unsigned char *)data) + totalsize);
    *refcount = 1;
  }
}

void Mat::create(int _w, int _h, int _c, size_t _elemsize,
                 Allocator *_allocator) {
  if (dims == 3 && w == _w && h == _h && c == _c && elemsize == _elemsize &&
      elempack == 1 && allocator == _allocator)
    return;

  release();

  elemsize = _elemsize;
  elempack = 1;
  allocator = _allocator;

  dims = 3;
  w = _w;
  h = _h;
  d = 1;
  c = _c;

  cstep = alignSize((size_t)w * h * elemsize, 16) / elemsize;

  size_t totalsize = alignSize(total() * elemsize, 4);
  if (totalsize > 0) {
    if (allocator)
      data = allocator->fastMalloc(totalsize + (int)sizeof(*refcount));
    else
      data = fastMalloc(totalsize + (int)sizeof(*refcount));
  }

  if (data) {
    refcount = (int *)(((unsigned char *)data) + totalsize);
    *refcount = 1;
  }
}

void Mat::create(int _w, int _h, int _d, int _c, size_t _elemsize,
                 Allocator *_allocator) {
  if (dims == 4 && w == _w && h == _h && d == _d && c == _c &&
      elemsize == _elemsize && elempack == 1 && allocator == _allocator)
    return;

  release();

  elemsize = _elemsize;
  elempack = 1;
  allocator = _allocator;

  dims = 4;
  w = _w;
  h = _h;
  d = _d;
  c = _c;

  cstep = alignSize((size_t)w * h * d * elemsize, 16) / elemsize;

  size_t totalsize = alignSize(total() * elemsize, 4);
  if (totalsize > 0) {
    if (allocator)
      data = allocator->fastMalloc(totalsize + (int)sizeof(*refcount));
    else
      data = fastMalloc(totalsize + (int)sizeof(*refcount));
  }

  if (data) {
    refcount = (int *)(((unsigned char *)data) + totalsize);
    *refcount = 1;
  }
}

void Mat::create(int _w, size_t _elemsize, int _elempack,
                 Allocator *_allocator) {
  if (dims == 1 && w == _w && elemsize == _elemsize && elempack == _elempack &&
      allocator == _allocator)
    return;

  release();

  elemsize = _elemsize;
  elempack = _elempack;
  allocator = _allocator;

  dims = 1;
  w = _w;
  h = 1;
  d = 1;
  c = 1;

  cstep = w;

  size_t totalsize = alignSize(total() * elemsize, 4);
  if (totalsize > 0) {
    if (allocator)
      data = allocator->fastMalloc(totalsize + (int)sizeof(*refcount));
    else
      data = fastMalloc(totalsize + (int)sizeof(*refcount));
  }

  if (data) {
    refcount = (int *)(((unsigned char *)data) + totalsize);
    *refcount = 1;
  }
}

void Mat::create(int _w, int _h, size_t _elemsize, int _elempack,
                 Allocator *_allocator) {
  if (dims == 2 && w == _w && h == _h && elemsize == _elemsize &&
      elempack == _elempack && allocator == _allocator)
    return;

  release();

  elemsize = _elemsize;
  elempack = _elempack;
  allocator = _allocator;

  dims = 2;
  w = _w;
  h = _h;
  d = 1;
  c = 1;

  cstep = (size_t)w * h;

  size_t totalsize = alignSize(total() * elemsize, 4);
  if (totalsize > 0) {
    if (allocator)
      data = allocator->fastMalloc(totalsize + (int)sizeof(*refcount));
    else
      data = fastMalloc(totalsize + (int)sizeof(*refcount));
  }

  if (data) {
    refcount = (int *)(((unsigned char *)data) + totalsize);
    *refcount = 1;
  }
}

void Mat::create(int _w, int _h, int _c, size_t _elemsize, int _elempack,
                 Allocator *_allocator) {
  if (dims == 3 && w == _w && h == _h && c == _c && elemsize == _elemsize &&
      elempack == _elempack && allocator == _allocator)
    return;

  release();

  elemsize = _elemsize;
  elempack = _elempack;
  allocator = _allocator;

  dims = 3;
  w = _w;
  h = _h;
  d = 1;
  c = _c;

  cstep = alignSize((size_t)w * h * elemsize, 16) / elemsize;

  size_t totalsize = alignSize(total() * elemsize, 4);
  if (totalsize > 0) {
    if (allocator)
      data = allocator->fastMalloc(totalsize + (int)sizeof(*refcount));
    else
      data = fastMalloc(totalsize + (int)sizeof(*refcount));
  }

  if (data) {
    refcount = (int *)(((unsigned char *)data) + totalsize);
    *refcount = 1;
  }
}

void Mat::create(int _w, int _h, int _d, int _c, size_t _elemsize,
                 int _elempack, Allocator *_allocator) {
  if (dims == 4 && w == _w && h == _h && d == _d && c == _c &&
      elemsize == _elemsize && elempack == _elempack && allocator == _allocator)
    return;

  release();

  elemsize = _elemsize;
  elempack = _elempack;
  allocator = _allocator;

  dims = 4;
  w = _w;
  h = _h;
  d = _d;
  c = _c;

  cstep = alignSize((size_t)w * h * d * elemsize, 16) / elemsize;

  size_t totalsize = alignSize(total() * elemsize, 4);
  if (totalsize > 0) {
    if (allocator)
      data = allocator->fastMalloc(totalsize + (int)sizeof(*refcount));
    else
      data = fastMalloc(totalsize + (int)sizeof(*refcount));
  }

  if (data) {
    refcount = (int *)(((unsigned char *)data) + totalsize);
    *refcount = 1;
  }
}

void Mat::create_like(const Mat &m, Allocator *_allocator) {
  int _dims = m.dims;
  if (_dims == 1)
    create(m.w, m.elemsize, m.elempack, _allocator);
  if (_dims == 2)
    create(m.w, m.h, m.elemsize, m.elempack, _allocator);
  if (_dims == 3)
    create(m.w, m.h, m.c, m.elemsize, m.elempack, _allocator);
  if (_dims == 4)
    create(m.w, m.h, m.d, m.c, m.elemsize, m.elempack, _allocator);
}
} // namespace base
} // namespace gcode