// @author: gezhipeng @ 20230409
// @file: gimage.cc
// @brief: gimage
#include "gimage.h"
#include "glog.h"
#include "stb_image.h"
#include "stb_image_write.h"
#include <filesystem>
#include <iostream>

namespace gcode {
Mat ReadImage(const std::string &filename, const int &mode) {
  Mat m;
  if (!std::filesystem::exists(filename)) {
    LOG_ERROR << filename << " not existed.";
    return m;
  }
  int req_comp = 0;
  if (mode == ReadImage_GRAY) {
    req_comp = 1;
  } else if (mode == ReadImage_RGB) {
    req_comp = 3;
  }
  if (req_comp == 0) {
    LOG_ERROR << "input mode " << mode << " is not supported.";
    return m;
  }
  size_t elemsize = sizeof(unsigned char);
  int width = 0;
  int height = 0;
  int channel = 0;
  unsigned char *data =
      stbi_load(filename.c_str(), &width, &height, &channel, req_comp);
  m.FromImage(data, width, height, (size_t)req_comp);
  free(data);
  return m;
}
void WriteImage(const std::string &filename, const Mat &m) {
  // Mat to array
  size_t w = m.w;
  size_t h = m.h;
  size_t ch = m.c;
  void *data = malloc(w * h * ch * sizeof(unsigned char));
  m.ToImage((unsigned char *)data, &w, &h, &ch);
  int ret = stbi_write_jpg(filename.c_str(), w, h, ch, data, 90);
  free(data);
}
} // namespace gcode