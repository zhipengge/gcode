// @author: gezhipeng @ 20250223
// @file: gauss_newton_test.cc
// @brief: gauss_newton_test
#include "optimizer/gauss_newton.h"
#include "plot/plot2d.h"
#include <gtest/gtest.h>

TEST(GAUSS_NEWTON, GAUSS_NEWTON_OPTIMIZER) {
  // 目标数据：y = 2x^3 - 3x^2 + 4x - 1 + noise
  Eigen::MatrixXf x_values(10, 1);
  Eigen::MatrixXf y_values(10, 1);
  x_values << 0, 1, 2, 3, 4, 5, 6, 7, 8, 9;
  for (size_t i = 0; i < 10; ++i) {
    y_values(i) = 2 * std::pow(x_values(i), 3) - 3 * std::pow(x_values(i), 2) +
                  4 * x_values(i) - 1 + std::rand() % 100 - 50.f;
  }

  // 参数方程：y = a*x^3 + b*x^2 + c*x + d
  gcode::Function func = [&x_values](const Eigen::MatrixXf &params) {
    return params(0) * x_values.array().pow(3) +
           params(1) * x_values.array().pow(2) + params(2) * x_values.array() +
           params(3);
  };

  // 雅可比矩阵函数
  gcode::JacobianFunction jacobian =
      [&x_values](const Eigen::MatrixXf &params) {
        Eigen::MatrixXf J(x_values.rows(), params.rows());
        J.col(0) = x_values.array().pow(3);                   // ∂y/∂a = x^3
        J.col(1) = x_values.array().pow(2);                   // ∂y/∂b = x^2
        J.col(2) = x_values.array();                          // ∂y/∂c = x
        J.col(3) = Eigen::MatrixXf::Ones(x_values.rows(), 1); // ∂y/∂d = 1
        return J;
      };

  // 初始化优化器
  gcode::GaussNewtonOptimizer optimizer(func, jacobian, y_values, 1e-6f, 100);
  optimizer.InitializeParameters(Eigen::MatrixXf::Ones(4, 1));
  // 执行优化
  optimizer.Optimize();

  // 输出优化结果
  Eigen::MatrixXf optimized_params = optimizer.GetParameters();

  gcode::Plot2D plot(500, 500, "test", gcode::PLOT_TYPE::DATA);
  plot.SetXLabel("x");
  plot.SetYLabel("y");
  size_t num_points = 100;
  float step = 10.f / num_points;
  Eigen::MatrixXf xs(num_points, 1);
  Eigen::MatrixXf ys(num_points, 1);
  for (size_t i = 0; i < num_points; ++i) {
    xs(i) = i * step;
    ys(i) = optimized_params(0) * std::pow(xs(i), 3) +
            optimized_params(1) * std::pow(xs(i), 2) +
            optimized_params(2) * xs(i) + optimized_params(3);
  }
  plot.Plot(x_values, y_values, gcode::CVColor::BLUE,
            gcode::PointsDrawType::SOLID, 2, "Ground Truth");
  plot.Plot(xs, ys, gcode::CVColor::RED, gcode::PointsDrawType::DASH, 2,
            "Optimized Curve");
  plot.Save("gauss_newton.jpg");
}
