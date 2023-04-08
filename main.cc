// @author: gezhipeng @ 20230408
// @file: main.cc
// @brief: main

#include "singleton.h"
#include "src/glog.h"
#include <iostream>

using namespace std;

int main() {
  LOG_DEBUG << "hello world";
  LOG_INFO << "hello world";
  LOG_WARNING << "hello world";
  LOG_ERROR << "hello world"
            << " programmer";
  return 0;
}