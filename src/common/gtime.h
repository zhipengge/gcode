// @author: gezhipeng @ 20230928
// @file: gtime.h
// @brief: gtime

#ifndef SRC_COMMON_GTIME_H_
#define SRC_COMMON_GTIME_H_
#include "glog.h"
#include <iostream>
#include <string>
// Timer for different block
#define TIMER_BLOCK_START(identifier)                                          \
  auto start_##identifier = std::chrono::high_resolution_clock::now();         \
  bool started_##identifier = true;

#define TIMER_BLOCK_END(identifier)                                            \
  if (started_##identifier) {                                                  \
    auto end_##identifier = std::chrono::high_resolution_clock::now();         \
    auto duration_##identifier =                                               \
        std::chrono::duration_cast<std::chrono::microseconds>(                 \
            end_##identifier - start_##identifier) /                           \
        1000.0;                                                                \
    LOG_INFO << #identifier << " cost " << duration_##identifier.count()       \
             << " ms";                                                         \
  } else {                                                                     \
    LOG_INFO << #identifier << " not set start, start from now";               \
    started_##identifier = true;                                               \
    auto start_##identifier = std::chrono::high_resolution_clock::now();       \
  }

namespace gcode {
namespace common {
typedef uint64_t timestamp_ns_t;
typedef double timestamp_ms_t;
typedef double timestamp_sec_t;
enum class TimeFormat { SIMPLE = 0, YMHMS = 1 };
class Timestamp;
Timestamp GetCurrentTimestamp();
std::string TimestampToStr(const Timestamp &t,
                           const TimeFormat &fmt_mode = TimeFormat::SIMPLE);
class Timestamp {
public:
  Timestamp() = default;
  Timestamp(const Timestamp &) = default;
  Timestamp(Timestamp &&) = default;
  explicit Timestamp(const timestamp_ns_t &ns) { this->SetNanoSecond(ns); }
  ~Timestamp() = default;
  Timestamp &operator=(const Timestamp &t) = default;
  inline bool operator==(const Timestamp &t) const {
    return t.nano_second() == this->ns_;
  }
  inline bool operator!=(const Timestamp &t) const {
    return t.nano_second() != this->ns_;
  }
  inline bool operator>(const Timestamp &t) const {
    return this->ns_ > t.nano_second();
  }
  inline bool operator<(const Timestamp &t) const {
    return this->ns_ < t.nano_second();
  }
  inline bool operator>=(const Timestamp &t) const { return !(*this < t); }
  inline bool operator<=(const Timestamp &t) const { return !(*this > t); }
  inline void SetNanoSecond(const timestamp_ns_t &ns) {
    ns_ = ns;
    ms_ = ns_ / 1e6;
    sec_ = ns / 1e9;
  }
  inline const timestamp_ns_t &nano_second() const { return ns_; }
  inline const timestamp_ms_t &milli_second() const { return ms_; }
  inline const timestamp_sec_t &second() const { return sec_; }

private:
  timestamp_ns_t ns_ = 0ull;
  timestamp_ms_t ms_ = 0.0;
  timestamp_sec_t sec_ = 0.0;
};

} // namespace common
} // namespace gcode
#endif // SRC_COMMON_GTIME_H_