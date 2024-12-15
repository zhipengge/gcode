// @author: gezhipeng @ 20230409
// @file: gimage.h
// @brief: gimage
#ifndef SRC_CV_GIMAGE_H_
#define SRC_CV_GIMAGE_H_
#include "gmat.h"
#define IMREAD_RGB 3
#define IMREAD_GRAY 1
namespace gcode {
Mat imread(const std::string &filename, const int &mode = IMREAD_RGB);
void imwrite(const std::string &filename, const Mat &m);
} // namespace gcode
#endif // SRC_CV_GIMAGE_H_