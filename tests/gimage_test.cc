// @author: gezhipeng @ 20231002
// @file: gimage_test.cc
// @brief: gimage_test
#include "gimage.h"
#include "gtime.h"
#include <gtest/gtest.h>

TEST(GIMAGE, ReadImage_WRITE) {
  std::string filename = "../../asserts/images/lena.jpg";
  TIMER_BLOCK_START(ReadImage)
  gcode::Mat m = gcode::ReadImage(filename, ReadImage_RGB);
  TIMER_BLOCK_END(ReadImage)
  gcode::Mat m1;
  gcode::Resize(m, m1, 800, 800);
  gcode::DrawCircle(m1, {400, 400}, 100, gcode::CVColor_RED, 5);
  std::vector<gcode::CVPoint> points;
  points.push_back({100, 100});
  points.push_back({200, 200});
  points.push_back({300, 300});
  points.push_back({400, 400});
  points.push_back({500, 500});
  points.push_back({600, 600});
  points.push_back({700, 700});
  gcode::DrawPoints(m1, points, gcode::CVColor_GREEN, 5, 1.0f,
                    gcode::PointsDrawType::DASH);
  gcode::DrawText(m1, "12345", {100, 100}, gcode::CVColor_BLUE, 0.2f, 1.f);
  std::string output = "lena.jpg";
  gcode::WriteImage(output, m1);
}
