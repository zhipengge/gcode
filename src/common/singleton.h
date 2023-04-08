// @author: gezhipeng @ 20230408
// @file: singleton.h
// @brief: singleton
#ifndef SRC_COMMON_SINGLETON_H_
#define SRC_COMMON_SINGLETON_H_
namespace gcode {
template <typename T> class Singleton {
public:
  Singleton() = delete;
  ~Singleton() = delete;
  static T &GetInstance() {
    static T instance;
    return instance;
  }

private:
  Singleton(const Singleton &) = delete;
  Singleton &operator=(const Singleton &) = delete;
}; // class Singleton
} // namespace gcode
#endif // SRC_COMMON_SINGLETON_H_