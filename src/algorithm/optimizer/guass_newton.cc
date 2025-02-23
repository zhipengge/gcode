// @author: gezhipeng @ 20250223
// @file: guass_newton.cc
// @brief: guass_newton

#include "optimizer/gauss_newton.h"

namespace gcode {
void GaussNewtonOptimizer::Optimize() {
  // 将参数矩阵展平为向量
  Eigen::Map<Eigen::VectorXf> params_flat(params_.data(), params_.size());

  for (int iter = 0; iter < max_iterations_; ++iter) {
    // 计算残差
    MatrixXf residual = func_(params_) - target_;
    Eigen::Map<Eigen::VectorXf> residual_flat(residual.data(), residual.size());

    // 计算雅可比矩阵
    MatrixXf J = jacobian_(params_);

    // 高斯牛顿法更新参数
    Eigen::VectorXf delta =
        (J.transpose() * J).ldlt().solve(J.transpose() * residual_flat);
    params_flat -= delta;

    // 计算当前 loss
    float loss = residual_flat.squaredNorm();
    std::cout << "inter " << iter << "/" << max_iterations_ << ":" << loss
              << std::endl;

    // 判断是否收敛
    if (loss < loss_threshold_) {
      break;
    }
  }
}
} // namespace gcode