// @author: gezhipeng @ 20230408
// @file: glog.h
// @brief: glog
#ifndef SRC_GLOG_H_
#define SRC_GLOG_H_
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>
namespace gcode {
enum class LogLevel {
  DEBUG = 0,
  INFO = 1,
  WARNING = 2,
  ERROR = 3,
};
const std::unordered_map<LogLevel, std::string> kLogLevelStringMap = {
    {LogLevel::DEBUG, "DEBUG"},
    {LogLevel::INFO, "INFO"},
    {LogLevel::WARNING, "WARNING"},
    {LogLevel::ERROR, "ERROR"},
};
const std::unordered_map<LogLevel, std::string> kLogLevelColorMap = {
    {LogLevel::DEBUG, "\033[0;34m"},
    {LogLevel::INFO, "\033[0;0m"},
    {LogLevel::WARNING, "\033[0;33m"},
    {LogLevel::ERROR, "\033[0;31m"},
};
class Logger {
public:
  explicit Logger(const LogLevel &level, const char *file, const char *func,
                  const int &line);
  ~Logger();
  template <typename T> Logger &operator<<(const T &value) {
    buffer_ << value;
    return *this;
  }
  template <typename T> Logger &operator<<(const std::vector<T> &value) {
    buffer_ << "[";
    for (const auto &item : value) {
      buffer_ << item << ", ";
    }
    buffer_ << "]";
    return *this;
  }

private:
  void AddPrefix(const char *file, const char *func, const int &line);
  LogLevel level_;
  std::ostringstream buffer_;
}; // class Logger
class LoggerDummy {
public:
  LoggerDummy() = default;
  ~LoggerDummy() = default;
  template <typename T> LoggerDummy &operator<<(const T &value) {
    return *this;
  }
  template <typename T> LoggerDummy &operator<<(const std::vector<T> &value) {
    return *this;
  }
}; // class LoggerDummy
#ifdef GLOG
#define LOG_DEBUG                                                              \
  gcode::Logger(gcode::LogLevel::DEBUG, __FILE__, __FUNCTION__, __LINE__)
#define LOG_INFO                                                               \
  gcode::Logger(gcode::LogLevel::INFO, __FILE__, __FUNCTION__, __LINE__)
#define LOG_WARNING                                                            \
  gcode::Logger(gcode::LogLevel::WARNING, __FILE__, __FUNCTION__, __LINE__)
#define LOG_ERROR                                                              \
  gcode::Logger(gcode::LogLevel::ERROR, __FILE__, __FUNCTION__, __LINE__)
#else
#define LOG_DEBUG gcode::LoggerDummy()
#define LOG_INFO gcode::LoggerDummy()
#define LOG_WARNING gcode::LoggerDummy()
#define LOG_ERROR gcode::LoggerDummy()
#endif
};     // namespace gcode
#endif // SRC_GLOG_H_