// @author: gezhipeng @ 20230408
// @file: main.cc
// @brief: main

#include "glog.h"
#include "gtime.h"
#include "macro.h"
#include "singleton.h"
#include <eigen/Core>
#include <iostream>

using namespace std;
using namespace gcode;

int main() {
  LOG_DEBUG << "hello world";
#ifdef ENABLE_X86_SSE
  std::cout << "ENABLE_X86_SSE" << std::endl;
#endif
#ifdef ENABLE_ARM_NEON
  std::cout << "ENABLE_ARM_NEON" << std::endl;
#endif
  return 0;
}