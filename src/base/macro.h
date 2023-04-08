// @author: gezhipeng @ 20231003
// @file: macro.h
// @brief: macro
#ifndef SRC_BASE_MACRO_H_
#define SRC_BASE_MACRO_H_
#if (defined(__ARM_NEON) &&                                                    \
     defined(__aarch64__)) // check compiler supports arm neon or not
#include <arm_neon.h>
#define ENABLE_ARM_NEON
#endif

#if (defined(__SSE3__) && defined(__x86__))
#define ENABLE_X86_SSE
#endif

#endif // SRC_BASE_MACRO_H_