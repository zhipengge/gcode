// @author: gezhipeng @ 20230930
// @file: allocator.cc
// @brief: allocator
#include <allocator.h>

namespace gcode {
namespace base {
void *FastMalloc(const size_t &sz) { return malloc(sz); }
void FastFree(void *ptr) { free(ptr); }
} // namespace base
} // namespace gcode