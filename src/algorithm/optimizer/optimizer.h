// @author: gezhipeng @ 20250223
// @file: optimizer.h
// @brief: optimizer
#ifndef SRC_ALGORITHM_OPTIMIZER_OPTIMIZER_H_
#define SRC_ALGORITHM_OPTIMIZER_OPTIMIZER_H_
#include <Eigen/Dense>
#include <functional>
#include <iostream>
namespace gcode {
using MatrixXf = Eigen::MatrixXf;
using Function = std::function<MatrixXf(const MatrixXf &)>;
using JacobianFunction = std::function<MatrixXf(const MatrixXf &)>;
class Optimizer {
public:
  Optimizer() = default;
  ~Optimizer() = default;
  Optimizer(Function func, JacobianFunction jacobian, const MatrixXf &target,
            const float &loss_threshold = 1e-6f,
            const int &max_iterations = 100);
  Optimizer(const Optimizer &) = delete;
  Optimizer &operator=(const Optimizer &) = delete;
  void Reset();
  inline void SetLossThreshold(const float &loss_threshold) {
    loss_threshold_ = loss_threshold;
  }
  inline void SetMaxIterations(const int &max_iterations) {
    max_iterations_ = max_iterations;
  }
  inline void SetTarget(const MatrixXf &target) { target_ = target; }
  inline void SetFunction(const Function &func) { func_ = func; }
  inline void SetJacobianFunction(const JacobianFunction &jacobian) {
    jacobian_ = jacobian;
  }
  inline void InitializeParameters(const MatrixXf &params) { params_ = params; }

  inline void SetParameters(const MatrixXf &params) { params_ = params; }

  inline const MatrixXf &GetParameters() const { return params_; }

  virtual void Optimize() = 0;

protected:
  Function func_;                // 参数方程
  JacobianFunction jacobian_;    // 雅可比矩阵函数
  MatrixXf target_;              // 目标值
  MatrixXf params_;              // 优化参数
  float loss_threshold_ = 1e-6f; // 目标函数 loss 阈值
  int max_iterations_ = 100;     // 最大迭代次数
};
} // namespace gcode
#endif // SRC_ALGORITHM_OPTIMIZER_OPTIMIZER_H_