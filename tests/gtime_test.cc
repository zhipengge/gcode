// @author: gezhipeng @ 20230408
// @file: log_test.cc
// @brief: log_test

#include "gtime.h"
#include <gtest/gtest.h>

TEST(GTIME, BASE) {
  gcode::common::Timestamp t1{0ull};
  gcode::common::Timestamp t2(t1);
  EXPECT_EQ(t1, t2);
  t2.SetNanoSecond(1ull);
  EXPECT_TRUE(t1 != t2);
  EXPECT_GT(t2, t1);
}

TEST(GTIME, TIMER) {
  TIMER_BLOCK_START(GTEST)
  for (uint64_t i = 0; i < 100000000ull; ++i) {
  }
  TIMER_BLOCK_END(GTEST)
}
