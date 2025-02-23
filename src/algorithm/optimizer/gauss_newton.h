// @author: gezhipeng @ 20250223
// @file: gauss_newton.h
// @brief: gauss_newton
#ifndef SRC_ALGORITHM_OPTIMIZER_GAUSS_NEWTON_H_
#define SRC_ALGORITHM_OPTIMIZER_GAUSS_NEWTON_H_
#include "optimizer.h"
namespace gcode {
// 高斯牛顿法优化器
class GaussNewtonOptimizer : public Optimizer {
public:
  using Optimizer::Optimizer;
  void Optimize() override;
};
} // namespace gcode
#endif // SRC_ALGORITHM_OPTIMIZER_GAUSS_NEWTON_H_