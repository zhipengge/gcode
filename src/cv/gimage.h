// @author: gezhipeng @ 20230409
// @file: gimage.h
// @brief: gimage
#ifndef SRC_CV_GIMAGE_H_
#define SRC_CV_GIMAGE_H_
#include "color.h"
#include "gmat.h"
#include <cmath>
#include <vector>
#define ReadImage_RGB 3
#define ReadImage_GRAY 1
namespace gcode {
struct CVPoint {
  int x;
  int y;
};

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
              const CVColor &color, const int &font_size = 1,
              const float &alpha = 1.0f);
} // namespace gcode
#endif // SRC_CV_GIMAGE_H_