// @author: gezhipeng @ 20230408
// @file: main.cc
// @brief: main

#include "glog.h"
#include "gtime.h"
#include "macro.h"
#include "singleton.h"
#include <Eigen/Core>
#include <Eigen/Dense>
#include <iostream>

using namespace std;
using namespace gcode;

int main() {
  Eigen::Matrix<int, 2, 2, Eigen::ColMajor> m;
  m << 1, 2, 3, 4;
  cout << m << endl;
  cout << m.row(0) << endl;
  cout << m.row(1) << endl;
  return 0;
}