// @author: gezhipeng @ 20230408
// @file: singleton_test.cc
// @brief: singleton_test
#include "singleton.h"
#include <gtest/gtest.h>
#include <iostream>

namespace gcode {
class SingletonTest {
public:
  SingletonTest() = default;
  ~SingletonTest() = default;
  bool Print() {
    std::cout << "hello world" << std::endl;
    return true;
  }

private:
  friend class Singleton<SingletonTest>;
}; // class Test

} // namespace gcode
TEST(SINGLETON, BASE) {
  EXPECT_TRUE(gcode::Singleton<gcode::SingletonTest>::GetInstance().Print());
}