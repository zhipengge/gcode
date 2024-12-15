// @author: gezhipeng @ 20231002
// @file: gimage_test.cc
// @brief: gimage_test
#include "gimage.h"
#include "gtime.h"
#include <gtest/gtest.h>

TEST(GIMAGE, IMREAD_WRITE) {
  std::string filename = "../../images/lena.jpg";
  TIMER_BLOCK_START(imread)
  gcode::Mat m = gcode::imread(filename, IMREAD_RGB);
  TIMER_BLOCK_END(imread)
  std::string output = "lena.jpg";
  gcode::imwrite(output, m);
}
