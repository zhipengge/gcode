// @author: gezhipeng @ 20250117
// @file: color.h
// @brief: color
#ifndef SRC_CV_COLOR_H_
#define SRC_CV_COLOR_H_
#include <iostream>
#include <vector>
namespace gcode {
struct CVColor {
  unsigned char r = 0;
  unsigned char g = 0;
  unsigned char b = 0;
  CVColor() = default;
  CVColor(unsigned char _r, unsigned char _g, unsigned char _b)
      : r(_r), g(_g), b(_b) {}

  friend std::ostream &operator<<(std::ostream &os, const CVColor &color) {
    os << "CVColor RGB(" << static_cast<int>(color.r) << ", "
       << static_cast<int>(color.g) << ", " << static_cast<int>(color.b) << ")";
    return os;
  }
  // declare some common colors
  static const CVColor WHITE;
  static const CVColor BLACK;
  static const CVColor RED;
  static const CVColor GREEN;
  static const CVColor BLUE;
  static const CVColor YELLOW;
  static const CVColor CYAN;
  static const CVColor PURPLE;
  static const CVColor ORANGE;
  static const CVColor GRAY;
  static const CVColor DARK_GRAY;
  static const CVColor LIGHT_GRAY;

  static const std::vector<CVColor> COLORS;
};
// define some common colors
inline const CVColor CVColor::WHITE = CVColor(255, 255, 255);
inline const CVColor CVColor::BLACK = CVColor(0, 0, 0);
inline const CVColor CVColor::RED = CVColor(255, 0, 0);
inline const CVColor CVColor::GREEN = CVColor(0, 255, 0);
inline const CVColor CVColor::BLUE = CVColor(0, 0, 255);
inline const CVColor CVColor::YELLOW = CVColor(255, 255, 0);
inline const CVColor CVColor::CYAN = CVColor(0, 255, 255);
inline const CVColor CVColor::PURPLE = CVColor(255, 0, 255);
inline const CVColor CVColor::ORANGE = CVColor(255, 165, 0);
inline const CVColor CVColor::GRAY = CVColor(128, 128, 128);
inline const CVColor CVColor::DARK_GRAY = CVColor(64, 64, 64);
inline const CVColor CVColor::LIGHT_GRAY = CVColor(192, 192, 192);
inline const std::vector<CVColor> CVColor::COLORS = {
    CVColor::WHITE,  CVColor::BLACK,  CVColor::RED,       CVColor::GREEN,
    CVColor::BLUE,   CVColor::YELLOW, CVColor::CYAN,      CVColor::PURPLE,
    CVColor::ORANGE, CVColor::GRAY,   CVColor::DARK_GRAY, CVColor::LIGHT_GRAY};
#define CVColor_WHITE                                                          \
  CVColor { 255, 255, 255 }
#define CVColor_BLACK                                                          \
  CVColor { 0, 0, 0 }
#define CVColor_RED                                                            \
  CVColor { 255, 0, 0 }
#define CVColor_GREEN                                                          \
  CVColor { 0, 255, 0 }
#define CVColor_BLUE                                                           \
  CVColor { 0, 0, 255 }
#define CVColor_YELLOW                                                         \
  CVColor { 255, 255, 0 }
#define CVColor_CYAN                                                           \
  CVColor { 0, 255, 255 }
#define CVColor_PURPLE                                                         \
  CVColor { 255, 0, 255 }
#define CVColor_ORANGE                                                         \
  CVColor { 255, 165, 0 }
#define CVColor_GRAY                                                           \
  CVColor { 128, 128, 128 }
#define CVColor_DARK_GRAY                                                      \
  CVColor { 64, 64, 64 }
#define CVColor_LIGHT_GRAY                                                     \
  CVColor { 192, 192, 192 }
} // namespace gcode
#endif // SRC_CV_COLOR_H_