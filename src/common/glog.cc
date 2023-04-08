// @author: gezhipeng @ 20230408
// @file: log.cc
// @brief: log
#include "glog.h"
#include <ctime>
namespace gcode {
namespace common {
Logger::Logger(const LogLevel &level, const char *file, const char *func,
               const int &line) {
  level_ = level;
  AddPrefix(file, func, line);
}
Logger::~Logger() {
  printf("%s\n", buffer_.str().c_str()); // NOTE: printf is thread safe
}
void Logger::AddPrefix(const char *file, const char *func, const int &line) {
  time_t now = time(nullptr);
  tm tm{};
  std::lock_guard<std::mutex> lock(mtx);
  localtime_r(&now, &tm);
  char time_str[64];
  strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", &tm);
  buffer_ << kLogLevelColorMap.at(level_) << time_str << " ["
          << kLogLevelStringMap.at(level_) << "] " << file << " " << func << " "
          << line << ": ";
}
} // namespace common
} // namespace gcode