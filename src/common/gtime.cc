// @author: gezhipeng @ 20230928
// @file: gtime.cc
// @brief: gtime
#include "gtime.h"
#include <chrono>
namespace gcode {
Timestamp GetCurrentTimestamp() {
  auto now = std::chrono::system_clock::now().time_since_epoch();
  timestamp_ns_t ns =
      std::chrono::duration_cast<std::chrono::nanoseconds>(now).count();
  return Timestamp(ns);
}
std::string TimestampToStr(const Timestamp &t, const TimeFormat &fmt_mode) {
  std::time_t ms = t.second();
  std::tm *timeinfo = std::localtime(&ms);
  std::string format =
      fmt_mode == TimeFormat::SIMPLE ? "%Y%m%d%H%M%S" : "%Y-%m-%d %H:%M:%S";
  // format
  char buffer[80];
  std::strftime(buffer, sizeof(buffer), format.c_str(), timeinfo);
  uint64_t milli_sec = static_cast<uint64_t>(t.milli_second()) % 1000ull;
  std::string ret = buffer + std::string(".") + std::to_string(milli_sec);
  return ret;
}
} // namespace gcode