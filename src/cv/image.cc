// @author: gezhipeng @ 20230409
// @file: image.cc
// @brief: image
#include "image.h"
#include "stb_image.h"
namespace gcode {
namespace cv {
unsigned char *imread(const char *filename, int flags) {
  int width, height, nrChannels;
  unsigned char *data = stbi_load(filename, &width, &height, &nrChannels, 0);
  return data;
}
int imwrite(const char *filename, int flags) { return 0; }
} // namespace cv
} // namespace gcode