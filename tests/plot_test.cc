// @author: gezhipeng @ 20250118
// @file: plot_test.cc
// @brief: plot_test
#include "plot/plot2d.h"
#include <gtest/gtest.h>
#include <cmath>

TEST(PLOT, PLOT2D) {
    gcode::Plot2D plot(500, 500, "test", gcode::PLOT_TYPE::DATA);
    plot.SetXLabel("x");
    plot.SetYLabel("y");
    vector_t xs(100);
    vector_t ys(100);
    for (int i = 0; i < xs.size(); ++i) {
        xs[i] = i - 50;
        ys[i] = xs[i] * xs[i];
    }
    plot.Plot(xs, ys, gcode::CVColor::BLUE, gcode::PointsDrawType::SOLID, 2, "y=x^2");
    vector_t ys2(100);
    for (int i = 0; i < xs.size(); ++i) {
        ys2[i] = std::sin(xs[i] / 10.0f) * 500;
    }
    plot.Plot(xs, ys2, gcode::CVColor::RED, gcode::PointsDrawType::DASH, 2, "y=sin(x/10)*500");
    plot.Save("plot2d.jpg");
}