// @author: gezhipeng @ 20230409
// @file: gimage.h
// @brief: gimage
#ifndef SRC_CV_GIMAGE_H_
#define SRC_CV_GIMAGE_H_
#include "gmat.h"
#define ReadImage_RGB 3
#define ReadImage_GRAY 1
namespace gcode {
Mat ReadImage(const std::string &filename, const int &mode = ReadImage_RGB);
void WriteImage(const std::string &filename, const Mat &m);
} // namespace gcode
#endif // SRC_CV_GIMAGE_H_