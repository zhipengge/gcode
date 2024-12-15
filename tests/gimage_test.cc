// @author: gezhipeng @ 20231002
// @file: gimage_test.cc
// @brief: gimage_test
#include "gimage.h"
#include "gtime.h"
#include <gtest/gtest.h>

TEST(GIMAGE, ReadImage_WRITE) {
  std::string filename = "../../images/lena.jpg";
  TIMER_BLOCK_START(ReadImage)
  gcode::Mat m = gcode::ReadImage(filename, ReadImage_RGB);
  TIMER_BLOCK_END(ReadImage)
  std::string output = "lena.jpg";
  gcode::WriteImage(output, m);
}
