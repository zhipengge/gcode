// @author: gezhipeng @ 20250223
// @file: gauss_newton_test.cc
// @brief: gauss_newton_test
#include "gtime.h"
#include "optimizer/gauss_newton.h"
#include "plot/plot2d.h"
#include <gtest/gtest.h>

TEST(GAUSS_NEWTON, GAUSS_NEWTON_OPTIMIZER) {
  // 目标数据：y = 2x^3 - 3x^2 + 4x - 1 + noise
  int input_num_points = 10;
  Eigen::MatrixXf x_values(input_num_points, 1);
  Eigen::MatrixXf y_values(input_num_points, 1);
  for (size_t i = 0; i < input_num_points; ++i) {
    x_values(i) = i;
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
  TIMER_BLOCK_START(GAUSS_NEWTON)
  gcode::GaussNewtonOptimizer optimizer(func, jacobian, y_values, 1e-6f, 100);
  optimizer.InitializeParameters(Eigen::MatrixXf::Ones(4, 1));
  // 执行优化
  optimizer.Optimize();
  TIMER_BLOCK_END(GAUSS_NEWTON)

  // 输出优化结果
  Eigen::MatrixXf optimized_params = optimizer.GetParameters();

  gcode::Plot2D plot(500, 500, "test", gcode::PLOT_TYPE::DATA);
  plot.SetXLabel("x");
  plot.SetYLabel("y");
  Eigen::MatrixXf ys = func(optimized_params);
  plot.Plot(x_values, y_values, gcode::CVColor::BLUE,
            gcode::PointsDrawType::SOLID, 5, "Ground Truth");
  plot.Plot(x_values, y_values, gcode::CVColor::BLUE,
            gcode::PointsDrawType::NORMAL_DOT, 10, "");
  plot.Plot(x_values, ys, gcode::CVColor::RED, gcode::PointsDrawType::SOLID, 5,
            "Optimized Curve");
  plot.Save("gauss_newton.jpg");
}

TEST(GAUSS_NEWTON, VEHICLE_CURVE_FIT_POLYNOMIAL) {
  size_t input_num_points = 12;
  Eigen::MatrixXf x_values(input_num_points, 1);
  Eigen::MatrixXf y_values(input_num_points, 1);
  // simulation right turn
  x_values << 0.f, 20.f, 40.f, 60.f, 80.f, 100.f, 115.f, 125.f, 130.f, 132.f,
      133.f, 133.f;
  y_values << 0.f, 0.f, -1.f, -3.f, -7.f, -12.f, -20.f, -30.f, -40.f, -50.f,
      -60.f, -70.f;

  // truncate the data into 2 parts
  int num_keep_head = 5;
  int num_keep_tail = 5;
  Eigen::MatrixXf x_values_head = x_values.topRows(num_keep_head);
  Eigen::MatrixXf y_values_head = y_values.topRows(num_keep_head);
  Eigen::MatrixXf x_values_tail = x_values.bottomRows(num_keep_tail);
  Eigen::MatrixXf y_values_tail = y_values.bottomRows(num_keep_tail);
  Eigen::MatrixXf x_values_concate =
      Eigen::MatrixXf::Zero(num_keep_head + num_keep_tail, 1);
  Eigen::MatrixXf y_values_concate =
      Eigen::MatrixXf::Zero(num_keep_head + num_keep_tail, 1);
  x_values_concate << x_values_head, x_values_tail;
  y_values_concate << y_values_head, y_values_tail;

  // 参数方程：y = a*x^3 + b*x^2 + c*x + d
  gcode::Function func = [&x_values_concate](const Eigen::MatrixXf &params) {
    return params(0) * x_values_concate.array().pow(3) +
           params(1) * x_values_concate.array().pow(2) +
           params(2) * x_values_concate.array() + params(3);
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
  TIMER_BLOCK_START(GAUSS_NEWTON)
  gcode::GaussNewtonOptimizer optimizer(func, jacobian, y_values_concate, 1e-6f,
                                        100);
  optimizer.InitializeParameters(Eigen::MatrixXf::Ones(4, 1));
  // 执行优化
  optimizer.Optimize();
  TIMER_BLOCK_END(GAUSS_NEWTON)

  Eigen::MatrixXf optimized_params = optimizer.GetParameters();
  std::cout << "params: " << optimized_params << std::endl;
  Eigen::MatrixXf y_values_fit = func(optimized_params);

  gcode::Plot2D plot(500, 500, "test", gcode::PLOT_TYPE::VEHICLE);
  plot.SetXLabel("x");
  plot.SetYLabel("y");
  plot.Plot(x_values, y_values, gcode::CVColor::BLUE,
            gcode::PointsDrawType::SOLID, 2, "Ground Truth");
  plot.Plot(x_values, y_values, gcode::CVColor::BLUE,
            gcode::PointsDrawType::NORMAL_DOT, 10, "");
  plot.Plot(x_values, y_values_fit, gcode::CVColor::RED,
            gcode::PointsDrawType::SOLID, 2, "FIT");
  plot.Save("gauss_newton_fit.jpg");
}
