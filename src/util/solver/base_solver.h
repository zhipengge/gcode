// @author: gezhipeng @ 20241220
// @file: base_solver.h
// @brief: base_solver
#ifndef SRC_UTIL_SOLVER_BASE_SOLVER_H_
#define SRC_UTIL_SOLVER_BASE_SOLVER_H_
#include <Eigen/Core>
class BaseSolver {
public:
  BaseSolver() = default;
  ~BaseSolver() = default;
  virtual void Solve() = 0;
};
#endif // SRC_UTIL_SOLVER_BASE_SOLVER_H_