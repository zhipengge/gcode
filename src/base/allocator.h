// @author: gezhipeng @ 20230930
// @file: allocator.h
// @brief: allocator
#ifndef SRC_BASE_ALLOCATOR_H_
#define SRC_BASE_ALLOCATOR_H_
#include <iostream>
namespace gcode {
namespace base {
void *FastMalloc(const size_t &sz);
void FastFree(void *ptr);
} // namespace base
} // namespace gcode

#endif // SRC_BASE_ALLOCATOR_H_