// @author: gezhipeng @ 20231002
// @file: gmat_test.cc
// @brief: gmat_test
#include "gmat.h"
#include <gtest/gtest.h>
using Mat = gcode::base::Mat;
TEST(MAT, BASE_CONSTRUCTOR) {
  // default
  Mat m{};
  EXPECT_TRUE(m.refcount == nullptr);

  size_t w = 224ul;
  size_t h = 224ul;
  size_t c = 3ul;
  size_t n = 2ul;
  size_t elemsize = 4ul; // float
  // vector
  Mat m1(w, elemsize);
  EXPECT_EQ(m1.w, w);
  EXPECT_EQ(m1.h, 1ul);
  EXPECT_EQ(m1.c, 1ul);
  EXPECT_EQ(m1.n, 1ul);
  EXPECT_EQ(m1.wstride, w);
  EXPECT_EQ(m1.hstride, 1ul);
  EXPECT_EQ(*m1.refcount, 1ul);
  EXPECT_EQ(m1.total(), m1.wstride * m1.hstride * m1.c * m1.n);
  // 2d array
  Mat m2(w, h, elemsize);
  EXPECT_EQ(m2.w, w);
  EXPECT_EQ(m2.h, h);
  EXPECT_EQ(m2.c, 1ul);
  EXPECT_EQ(m2.n, 1ul);
  EXPECT_EQ(m2.wstride, ALIGN_SIZE(w, ALIGN_STEP));
  EXPECT_EQ(m2.hstride, ALIGN_SIZE(h, ALIGN_STEP));
  EXPECT_EQ(*m2.refcount, 1ul);
  EXPECT_EQ(m2.total(), m2.wstride * m2.hstride * m2.c * m2.n);
  // 3d array
  Mat m3(w, h, c, elemsize);
  EXPECT_EQ(m3.w, w);
  EXPECT_EQ(m3.h, h);
  EXPECT_EQ(m3.c, c);
  EXPECT_EQ(m3.n, 1ul);
  EXPECT_EQ(m3.wstride, ALIGN_SIZE(w, ALIGN_STEP));
  EXPECT_EQ(m3.hstride, ALIGN_SIZE(h, ALIGN_STEP));
  EXPECT_EQ(*m3.refcount, 1ul);
  EXPECT_EQ(m3.total(), m3.wstride * m3.hstride * m3.c * m3.n);
  // 4d array
  Mat m4(w, h, c, n, elemsize);
  EXPECT_EQ(m4.w, w);
  EXPECT_EQ(m4.h, h);
  EXPECT_EQ(m4.c, c);
  EXPECT_EQ(m4.n, n);
  EXPECT_EQ(m4.wstride, ALIGN_SIZE(w, ALIGN_STEP));
  EXPECT_EQ(m4.hstride, ALIGN_SIZE(h, ALIGN_STEP));
  EXPECT_EQ(*m4.refcount, 1ul);
  EXPECT_EQ(m4.total(), m4.wstride * m4.hstride * m4.c * m4.n);
}

TEST(MAT, COPY_CONSTRUCTOR) {
  size_t w = 224ul;
  size_t h = 224ul;
  size_t c = 3ul;
  size_t n = 2ul;
  size_t elemsize = sizeof(float);
  float vec[w];
  float array2d[h][w];
  float array3d[c][h][w];
  float array4d[n][c][h][w];
  // vector
  Mat m1(w, (void *)vec, elemsize);
  EXPECT_EQ(m1.w, w);
  EXPECT_EQ(m1.h, 1ul);
  EXPECT_EQ(m1.c, 1ul);
  EXPECT_EQ(m1.n, 1ul);
  EXPECT_EQ(m1.wstride, w);
  EXPECT_EQ(m1.hstride, 1ul);
  EXPECT_EQ(*m1.refcount, 1ul);
  EXPECT_EQ(m1.total(), m1.wstride * m1.hstride * m1.c * m1.n);
  // 2d array
  Mat m2(w, h, (void *)array2d, elemsize);
  EXPECT_EQ(m2.w, w);
  EXPECT_EQ(m2.h, h);
  EXPECT_EQ(m2.c, 1ul);
  EXPECT_EQ(m2.n, 1ul);
  EXPECT_EQ(m2.wstride, ALIGN_SIZE(w, ALIGN_STEP));
  EXPECT_EQ(m2.hstride, ALIGN_SIZE(h, ALIGN_STEP));
  EXPECT_EQ(*m2.refcount, 1ul);
  EXPECT_EQ(m2.total(), m2.wstride * m2.hstride * m2.c * m2.n);
  // 3d array
  Mat m3(w, h, c, (void *)array3d, elemsize);
  EXPECT_EQ(m3.w, w);
  EXPECT_EQ(m3.h, h);
  EXPECT_EQ(m3.c, c);
  EXPECT_EQ(m3.n, 1ul);
  EXPECT_EQ(m3.wstride, ALIGN_SIZE(w, ALIGN_STEP));
  EXPECT_EQ(m3.hstride, ALIGN_SIZE(h, ALIGN_STEP));
  EXPECT_EQ(*m3.refcount, 1ul);
  EXPECT_EQ(m3.total(), m3.wstride * m3.hstride * m3.c * m3.n);
  // 4d array
  Mat m4(w, h, c, n, (void *)array4d, elemsize);
  EXPECT_EQ(m4.w, w);
  EXPECT_EQ(m4.h, h);
  EXPECT_EQ(m4.c, c);
  EXPECT_EQ(m4.n, n);
  EXPECT_EQ(m4.wstride, ALIGN_SIZE(w, ALIGN_STEP));
  EXPECT_EQ(m4.hstride, ALIGN_SIZE(h, ALIGN_STEP));
  EXPECT_EQ(*m4.refcount, 1ul);
  EXPECT_EQ(m4.total(), m4.wstride * m4.hstride * m4.c * m4.n);
}

TEST(MAT, COPY_CONSTRUCTOR2) {
  size_t w = 224ul;
  size_t h = 224ul;
  size_t c = 3ul;
  size_t n = 2ul;
  size_t elemsize = sizeof(float);
  Mat m(w, elemsize);
  EXPECT_EQ(*m.refcount, 1ul);
  Mat m2(m);
  EXPECT_EQ(*m.refcount, 2ul);
  EXPECT_EQ(*m2.refcount, 2ul);
  Mat m3 = m;
  EXPECT_EQ(*m.refcount, 3ul);
  EXPECT_EQ(*m2.refcount, 3ul);
  EXPECT_EQ(*m3.refcount, 3ul);
}

TEST(MAT, FILL) {
  size_t w = 224ul;
  size_t h = 224ul;
  size_t c = 3ul;
  size_t n = 2ul;
  size_t elemsize = sizeof(unsigned char);
  Mat m(w, elemsize);
  m.fill<unsigned char>(255);
  EXPECT_EQ(*m.refcount, 1ul);
  unsigned char *data = (unsigned char *)m.data;
  EXPECT_EQ(data[w - 1], 255);
}