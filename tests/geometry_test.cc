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

TEST(GEOMETRY, DISTANCE_TO_POLY_LINE) {
  gcode::points_2d_t poly_line(3, 2);
  poly_line << 0, 0, 1, 1, 2, 0;
  gcode::vector2d_t p(0, 1);
  double distance = gcode::DistanceToPolyLine(p, poly_line);
  EXPECT_NEAR(distance, 0.7071067811865476, 1e-6);

  gcode::points_3d_t poly_line3(3, 3);
  poly_line3 << 0, 0, 0, 1, 1, 1, 2, 0, 2;
  gcode::vector3d_t p3(0, 1, 0);
  double distance3 = gcode::DistanceToPolyLine(p3, poly_line3);
  EXPECT_NEAR(distance3, 0.816496580927726, 1e-6);
}

TEST(GEOMETRY, IS_INTERSELECTED) {
  gcode::vector2d_t a(0, 0);
  gcode::vector2d_t b(1, 1);
  gcode::vector2d_t c(0, 1);
  gcode::vector2d_t d(1, 0);
  gcode::vector2d_t inter_point;
  bool is_interselected = gcode::IsInterselected(a, b, c, d, inter_point);
  EXPECT_TRUE(is_interselected);
  EXPECT_NEAR(inter_point(0), 0.5, 1e-6);
  EXPECT_NEAR(inter_point(1), 0.5, 1e-6);
}

TEST(GEOMETRY, IS_POINT_IN_POLYGON) {
  gcode::points_2d_t polygon(3, 2);
  polygon << 0, 0, 1, 1, 2, 0;
  gcode::vector2d_t p(0.5, 0.5);
  bool is_point_in_polygon = gcode::IsPointInPolygon(p, polygon);
  EXPECT_TRUE(is_point_in_polygon);
  double distance = gcode::DistanceToPolygon(p, polygon);
  EXPECT_NEAR(distance, 0, 1e-6);
}

TEST(GEOMETRY, DISTANCE_TO_POLYGON) {
  gcode::points_2d_t polygon(3, 2);
  polygon << 0, 0, 1, 1, 2, 0;
  gcode::vector2d_t p(0.5, 0.5);
  double distance = gcode::DistanceToPolygon(p, polygon);
  EXPECT_NEAR(distance, 0, 1e-6);
}