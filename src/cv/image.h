// @author: gezhipeng @ 20230409
// @file: image.h
// @brief: image
#ifndef SRC_CV_IMAGE_H_
#define SRC_CV_IMAGE_H_
#include "mat.h"
namespace gcode {
namespace cv {
using gcode::base::Mat;
unsigned char *imread(const char *filename, int flags, int *width, int *height,
                      int *nrChannels);
int imwrite(const char *filename, int flags);
// convert yuv420sp(nv21) to rgb, the fast approximate version
void yuv420sp2rgb(const unsigned char *yuv420sp, int w, int h,
                  unsigned char *rgb);
// convert yuv420sp(nv12) to rgb, the fast approximate version
void yuv420sp2rgb_nv12(const unsigned char *yuv420sp, int w, int h,
                       unsigned char *rgb);
// convert yuv420sp(nv21) to rgb with half resize, the faster approximate
// version
void yuv420sp2rgb_half(const unsigned char *yuv420sp, int w, int h,
                       unsigned char *rgb);
// image pixel bilinear resize
void resize_bilinear_c1(const unsigned char *src, int srcw, int srch,
                        unsigned char *dst, int w, int h);
void resize_bilinear_c2(const unsigned char *src, int srcw, int srch,
                        unsigned char *dst, int w, int h);
void resize_bilinear_c3(const unsigned char *src, int srcw, int srch,
                        unsigned char *dst, int w, int h);
void resize_bilinear_c4(const unsigned char *src, int srcw, int srch,
                        unsigned char *dst, int w, int h);
// image pixel bilinear resize with stride(bytes-per-row) parameter
void resize_bilinear_c1(const unsigned char *src, int srcw, int srch,
                        int srcstride, unsigned char *dst, int w, int h,
                        int stride);
void resize_bilinear_c2(const unsigned char *src, int srcw, int srch,
                        int srcstride, unsigned char *dst, int w, int h,
                        int stride);
void resize_bilinear_c3(const unsigned char *src, int srcw, int srch,
                        int srcstride, unsigned char *dst, int w, int h,
                        int stride);
void resize_bilinear_c4(const unsigned char *src, int srcw, int srch,
                        int srcstride, unsigned char *dst, int w, int h,
                        int stride);
// image pixel bilinear resize, convenient wrapper for yuv420sp(nv21/nv12)
void resize_bilinear_yuv420sp(const unsigned char *src, int srcw, int srch,
                              unsigned char *dst, int w, int h);
void draw_rectangle_c1(unsigned char *pixels, int w, int h, int rx, int ry,
                       int rw, int rh, unsigned int color, int thickness);
void draw_rectangle_c2(unsigned char *pixels, int w, int h, int rx, int ry,
                       int rw, int rh, unsigned int color, int thickness);
void draw_rectangle_c3(unsigned char *pixels, int w, int h, int rx, int ry,
                       int rw, int rh, unsigned int color, int thickness);
void draw_rectangle_c4(unsigned char *pixels, int w, int h, int rx, int ry,
                       int rw, int rh, unsigned int color, int thickness);
// draw rectangle with stride(bytes-per-row) parameter, set thickness -1 for
// filled rectangle, the color RGBA is little-endian encoded
void draw_rectangle_c1(unsigned char *pixels, int w, int h, int stride, int rx,
                       int ry, int rw, int rh, unsigned int color,
                       int thickness);
void draw_rectangle_c2(unsigned char *pixels, int w, int h, int stride, int rx,
                       int ry, int rw, int rh, unsigned int color,
                       int thickness);
void draw_rectangle_c3(unsigned char *pixels, int w, int h, int stride, int rx,
                       int ry, int rw, int rh, unsigned int color,
                       int thickness);
void draw_rectangle_c4(unsigned char *pixels, int w, int h, int stride, int rx,
                       int ry, int rw, int rh, unsigned int color,
                       int thickness);
// draw rectangle, convenient wrapper for yuv420sp(nv21/nv12), set thickness -1
// for filled rectangle, the color YUV_ is little-endian encoded
void draw_rectangle_yuv420sp(unsigned char *yuv420sp, int w, int h, int rx,
                             int ry, int rw, int rh, unsigned int color,
                             int thickness);
// draw circle, set thickness -1 for filled circle, the color RGBA is
// little-endian encoded
void draw_circle_c1(unsigned char *pixels, int w, int h, int cx, int cy,
                    int radius, unsigned int color, int thickness);
void draw_circle_c2(unsigned char *pixels, int w, int h, int cx, int cy,
                    int radius, unsigned int color, int thickness);
void draw_circle_c3(unsigned char *pixels, int w, int h, int cx, int cy,
                    int radius, unsigned int color, int thickness);
void draw_circle_c4(unsigned char *pixels, int w, int h, int cx, int cy,
                    int radius, unsigned int color, int thickness);
// draw circle with stride(bytes-per-row) parameter, set thickness -1 for filled
// circle, the color RGBA is little-endian encoded
void draw_circle_c1(unsigned char *pixels, int w, int h, int stride, int cx,
                    int cy, int radius, unsigned int color, int thickness);
void draw_circle_c2(unsigned char *pixels, int w, int h, int stride, int cx,
                    int cy, int radius, unsigned int color, int thickness);
void draw_circle_c3(unsigned char *pixels, int w, int h, int stride, int cx,
                    int cy, int radius, unsigned int color, int thickness);
void draw_circle_c4(unsigned char *pixels, int w, int h, int stride, int cx,
                    int cy, int radius, unsigned int color, int thickness);
// draw circle, convenient wrapper for yuv420sp(nv21/nv12), set thickness -1 for
// filled circle, the color YUV_ is little-endian encoded
void draw_circle_yuv420sp(unsigned char *yuv420sp, int w, int h, int cx, int cy,
                          int radius, unsigned int color, int thickness);
// draw line, the color RGBA is little-endian encoded
void draw_line_c1(unsigned char *pixels, int w, int h, int x0, int y0, int x1,
                  int y1, unsigned int color, int thickness);
void draw_line_c2(unsigned char *pixels, int w, int h, int x0, int y0, int x1,
                  int y1, unsigned int color, int thickness);
void draw_line_c3(unsigned char *pixels, int w, int h, int x0, int y0, int x1,
                  int y1, unsigned int color, int thickness);
void draw_line_c4(unsigned char *pixels, int w, int h, int x0, int y0, int x1,
                  int y1, unsigned int color, int thickness);
// draw line with stride(bytes-per-row) parameter, the color RGBA is
// little-endian encoded
void draw_line_c1(unsigned char *pixels, int w, int h, int stride, int x0,
                  int y0, int x1, int y1, unsigned int color, int thickness);
void draw_line_c2(unsigned char *pixels, int w, int h, int stride, int x0,
                  int y0, int x1, int y1, unsigned int color, int thickness);
void draw_line_c3(unsigned char *pixels, int w, int h, int stride, int x0,
                  int y0, int x1, int y1, unsigned int color, int thickness);
void draw_line_c4(unsigned char *pixels, int w, int h, int stride, int x0,
                  int y0, int x1, int y1, unsigned int color, int thickness);
// draw line, convenient wrapper for yuv420sp(nv21/nv12), the color YUV_ is
// little-endian encoded
void draw_line_yuv420sp(unsigned char *yuv420sp, int w, int h, int x0, int y0,
                        int x1, int y1, unsigned int color, int thickness);
// resolve text bounding box size
void get_text_drawing_size(const char *text, int fontpixelsize, int *w, int *h);
// draw ascii printables and newline, the color RGBA is little-endian encoded
void draw_text_c1(unsigned char *pixels, int w, int h, const char *text, int x,
                  int y, int fontpixelsize, unsigned int color);
void draw_text_c2(unsigned char *pixels, int w, int h, const char *text, int x,
                  int y, int fontpixelsize, unsigned int color);
void draw_text_c3(unsigned char *pixels, int w, int h, const char *text, int x,
                  int y, int fontpixelsize, unsigned int color);
void draw_text_c4(unsigned char *pixels, int w, int h, const char *text, int x,
                  int y, int fontpixelsize, unsigned int color);
// draw ascii printables and newline with stride(bytes-per-row) parameter, the
// color RGBA is little-endian encoded
void draw_text_c1(unsigned char *pixels, int w, int h, int stride,
                  const char *text, int x, int y, int fontpixelsize,
                  unsigned int color);
void draw_text_c2(unsigned char *pixels, int w, int h, int stride,
                  const char *text, int x, int y, int fontpixelsize,
                  unsigned int color);
void draw_text_c3(unsigned char *pixels, int w, int h, int stride,
                  const char *text, int x, int y, int fontpixelsize,
                  unsigned int color);
void draw_text_c4(unsigned char *pixels, int w, int h, int stride,
                  const char *text, int x, int y, int fontpixelsize,
                  unsigned int color);
// draw ascii printables and newline, convenient wrapper for
// yuv420sp(nv21/nv12), the color YUV_ is little-endian encoded
void draw_text_yuv420sp(unsigned char *yuv420sp, int w, int h, const char *text,
                        int x, int y, int fontpixelsize, unsigned int color);
} // namespace cv
} // namespace gcode
#endif // SRC_CV_IMAGE_H_