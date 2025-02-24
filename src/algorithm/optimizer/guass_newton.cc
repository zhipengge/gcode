// @author: gezhipeng @ 20250223
// @file: guass_newton.cc
// @brief: guass_newton

#include "optimizer/gauss_newton.h"

#include "optimizer/gauss_newton.h"

namespace gcode {
void GaussNewtonOptimizer::Optimize() {
  // 将参数矩阵展平为向量
  Eigen::Map<Eigen::VectorXf> params_flat(params_.data(), params_.size());

  for (int iter = 0; iter < max_iterations_; ++iter) {
    // 计算残差
    MatrixXf residual = func_(params_) - target_;
    if (residual.rows() != target_.rows() ||
        residual.cols() != target_.cols()) {
      std::cerr << "Error: Residual dimension mismatch!" << std::endl;
      return;
    }
    Eigen::Map<Eigen::VectorXf> residual_flat(residual.data(), residual.size());

    // 计算雅可比矩阵
    MatrixXf J = jacobian_(params_);
    if (J.rows() != residual.size() || J.cols() != params_flat.size()) {
      std::cerr << "Error: Jacobian dimension mismatch!" << std::endl;
      return;
    }

    // 高斯牛顿法更新参数
    Eigen::VectorXf delta =
        (J.transpose() * J).ldlt().solve(J.transpose() * residual_flat);
    params_flat -= delta;

    // 计算当前 loss
    float loss = residual_flat.squaredNorm();
    std::cout << "Iter " << iter << "/" << max_iterations_
              << ": Loss = " << loss << std::endl;

    // 判断是否收敛
    if (loss < loss_threshold_) {
      std::cout << "Converged at iteration " << iter << " with loss = " << loss
                << std::endl;
      break;
    }

    // 检查参数是否合理
    if (params_flat.array().isNaN().any()) {
      std::cerr << "Error: Parameters contain NaN values!" << std::endl;
      return;
    }
  }
}
} // namespace gcode