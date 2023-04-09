// @author: gezhipeng @ 20230408
// @file: log_test.cc
// @brief: log_test

#include "log.h"
#include <gtest/gtest.h>

TEST(Glog, Single) {
  LOG_DEBUG << 1;
  LOG_INFO << "hello world";
  LOG_WARNING << 3.14f;
  LOG_ERROR << 12345678ul;
}

TEST(Glog, Batch) {
  LOG_DEBUG << "name: "
            << "gezhipeng"
            << " age: " << 18;
  LOG_INFO << "name: "
           << "gezhipeng"
           << " age: " << 18;
  LOG_WARNING << "name: "
              << "gezhipeng"
              << " age: " << 18;
  LOG_ERROR << "name: "
            << "gezhipeng"
            << " age: " << 18;
}