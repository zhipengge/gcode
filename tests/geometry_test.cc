// @author: gezhipeng @ 20250222
// @file: geometry_test.cc
// @brief: geometry_test

#include "algorithm/geometry.h"
#include <gtest/gtest.h>

TEST(GEOMETRY, GEOMETRY_BASED_DATA) {
  gcode::vector2d_t p(0, 0);
  gcode::vector2d_t a(1, 1);
  gcode::vector2d_t b(2, 2);
  double distance = gcode::DistanceToSegment(p, a, b);
  EXPECT_NEAR(distance, 1.4142135623730951, 1e-6);

  gcode::vector3d_t p3(0, 0, 0);
  gcode::vector3d_t a3(1, 1, 1);
  gcode::vector3d_t b3(2, 2, 2);
  double distance3 = gcode::DistanceToSegment(p3, a3, b3);
  EXPECT_NEAR(distance3, 1.7320508, 1e-6);
}