// @author: gezhipeng @ 20230408
// @file: singleton_test.cc
// @brief: singleton_test
#include "src/singleton.h"
#include <iostream>
namespace gcode {
class Test {
public:
  Test() = default;
  ~Test() = default;
  void Print() { std::cout << "hello world" << std::endl; }

private:
  friend class Singleton<Test>;
}; // class Test
} // namespace gcode