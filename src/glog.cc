// @author: gezhipeng @ 20230408
// @file: glog.cc
// @brief: glog
#include "glog.h"
#include <ctime>
namespace gcode {
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
  struct tm *local_time = localtime(&now);
  char time_str[64];
  strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", local_time);
  buffer_ << kLogLevelColorMap.at(level_) << time_str << " "
          << kLogLevelStringMap.at(level_) << " " << file << ":" << func << ":"
          << line << ":";
}
} // namespace gcode