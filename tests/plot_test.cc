// @author: gezhipeng @ 20250118
// @file: plot_test.cc
// @brief: plot_test
#include "plot/plot2d.h"
#include <gtest/gtest.h>
#include <cmath>

TEST(PLOT, PLOT2D) {
    gcode::Plot2D plot(500, 500, "test", gcode::PLOT_TYPE::VEHICLE);
    plot.SetXLabel("x");
    plot.SetYLabel("y");
    size_t num_points = 100;
    float step = 250 / num_points;
    vector_t xs(num_points);
    vector_t ys1(num_points);
    vector_t ys2(num_points);
    for (size_t i = 0; i < num_points; ++i) {
        xs[i] = i * step - 25.f;
        ys1[i] = std::sin(xs[i] / 10.f) * 50;
        ys2[i] = std::cos(xs[i] / 10.f) * 50;
    }
    plot.Plot(xs, ys1, gcode::CVColor::BLUE, gcode::PointsDrawType::DASH, 2, "y=50*sin(x/10)");
    plot.Plot(xs, ys2, gcode::CVColor::RED, gcode::PointsDrawType::SOLID, 2, "y=50*sin(x/10)");
    plot.Save("plot2d.jpg");
}