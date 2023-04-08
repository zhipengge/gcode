// @author: gezhipeng @ 20230408
// @file: log_test.cc
// @brief: log_test

#include "glog.h"
#include <gtest/gtest.h>

TEST(LOG, SINGLE) {
  LOG_DEBUG << 1;
  LOG_INFO << "hello world";
  LOG_WARNING << 3.14f;
  LOG_ERROR << 12345678ul;
}

TEST(LOG, BATCH) {
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