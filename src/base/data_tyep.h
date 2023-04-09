// @author: gezhipeng @ 20230409
// @file: data_tyep.h
// @brief: data_tyep

#ifndef SRC_BASE_DATA_TYEP_H_
#define SRC_BASE_DATA_TYEP_H_
namespace gcode {
namespace base {
unsigned short float32_to_float16(float value);
// convert half precision floating point to float
float float16_to_float32(unsigned short value);
// convert float to brain half
inline unsigned short float32_to_bfloat16(float value) {
  // 16 : 16
  union {
    unsigned int u;
    float f;
  } tmp;
  tmp.f = value;
  return tmp.u >> 16;
}
// convert brain half to float
inline float bfloat16_to_float32(unsigned short value) {
  // 16 : 16
  union {
    unsigned int u;
    float f;
  } tmp;
  tmp.u = value << 16;
  return tmp.f;
}

} // namespace base
} // namespace gcode
#endif // SRC_BASE_DATA_TYEP_H_