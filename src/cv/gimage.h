// @author: gezhipeng @ 20230409
// @file: gimage.h
// @brief: gimage
#ifndef SRC_CV_GIMAGE_H_
#define SRC_CV_GIMAGE_H_
#include "gmat.h"
#include <cmath>
#define ReadImage_RGB 3
#define ReadImage_GRAY 1
namespace gcode {
struct CVPoint {
  int x;
  int y;
};
struct CVColor {
  unsigned char r = 0;
  unsigned char g = 0;
  unsigned char b = 0;
};

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

enum class PointsDrawType { NORMAL_DOT = 0, DASH = 1, SOLID = 2 };

Mat ReadImage(const std::string &filename, const int &mode = ReadImage_RGB);
void WriteImage(const std::string &filename, const Mat &m);
void DrawPoint(Mat &m, const CVPoint &p, const CVColor &color,
               const size_t &thickness = 1, const float &alpha = 1.0f);
void DrawLine(Mat &m, const CVPoint &p1, const CVPoint &p2,
              const CVColor &color, const int &thickness = 1,
              const float &alpha = 1.0f);
void DrawArrow(Mat &m, const CVPoint &p1, const CVPoint &p2,
               const CVColor &color, const int &thickness = 1,
               const float &alpha = 1.0f);
void DrawRect(Mat &m, const CVPoint &p1, const CVPoint &p2,
              const CVColor &color, const int &thickness = 1,
              const float &alpha = 1.0f);
void DrawCircle(Mat &m, const CVPoint &center, const int &radius,
                const CVColor &color, const int &thickness = 1,
                const float &alpha = 1.0f);
void DrawPoints(Mat &m, const std::vector<CVPoint> &points,
                const CVColor &color, const size_t &thickness = 1,
                const float &alpha = 1.0f,
                const PointsDrawType &type = PointsDrawType::NORMAL_DOT);
void DrawPolyline(Mat &m, const std::vector<CVPoint> &points,
                  const CVColor &color, const int &thickness = 1,
                  const float &alpha = 1.0f);
void Resize(const Mat &src, Mat &dst, const size_t &w, const size_t &h);
/**
 * @brief: draw text on image
 * @param m: image
 * @param text: text
 * @param p: point, top-left corner of text
 * @param color: text color
 * @param scale: text scale
 * @param alpha: text alpha
 * @return: void
 */
void DrawText(Mat &m, const std::string &text, const CVPoint &p,
              const CVColor &color, const float &scale = 1.0f,
              const float &alpha = 1.0f);
} // namespace gcode
#endif // SRC_CV_GIMAGE_H_