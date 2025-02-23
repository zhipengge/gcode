// @author: gezhipeng @ 20250223
// @file: optimizer.cc
// @brief: optimizer
#include "optimizer.h"
namespace gcode {
Optimizer::Optimizer(Function func, JacobianFunction jacobian,
                     const MatrixXf &target, const float &loss_threshold,
                     const int &max_iterations)
    : func_(func), jacobian_(jacobian), target_(target),
      loss_threshold_(loss_threshold), max_iterations_(max_iterations) {}

} // namespace gcode