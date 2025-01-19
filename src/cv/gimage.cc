// @author: gezhipeng @ 20230409
// @file: gimage.cc
// @brief: gimage
#include "gimage.h"
#include "ascii_image.h"
#include "glog.h"
#include "stb_image.h"
#include "stb_image_write.h"
#include <cmath>
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

void DrawPoint(Mat &m, const CVPoint &p, const CVColor &color,
               const size_t &thickness, const float &alpha) {
  if (p.x < 0 || p.x >= m.w || p.y < 0 || p.y >= m.h) {
    LOG_ERROR << "point (" << p.x << ", " << p.y << ") is out of image range "
              << m.w << "x" << m.h;
    return;
  }
  if ((m.c != 1 and m.c != 3) or m.elemsize != sizeof(unsigned char) or
      m.n != 1) {
    LOG_ERROR << "image format is not supported. only support 1-channel or "
                 "3-channel uint8 image.";
    return;
  }
  if (alpha < 0.0f || alpha > 1.0f) {
    LOG_ERROR << "alpha value " << alpha << " is out of range [0, 1].";
    return;
  }
  if (thickness <= 0) {
    LOG_ERROR << "thickness " << thickness << " is invalid.";
    return;
  }
  const int half_thickness = thickness / 2;
  const int quarter_thickness_square = half_thickness * half_thickness / 4;
  float alpha_color[3] = {0.f, 0.f, 0.f};
  if (m.c == 3) {
    const float alpha_r = alpha * color.r;
    const float alpha_g = alpha * color.g;
    const float alpha_b = alpha * color.b;
    alpha_color[0] = alpha_r;
    alpha_color[1] = alpha_g;
    alpha_color[2] = alpha_b;
  } else if (m.c == 1) {
    const float alpha_black =
        alpha * (0.299f * color.r + 0.587f * color.g + 0.114f * color.b);
    alpha_color[0] = alpha_black;
    alpha_color[1] = alpha_black;
    alpha_color[2] = alpha_black;
  }
  const float one_minus_alpha = 1.0f - alpha;
  for (int ch = 0; ch < m.c; ++ch) {
    uint8_t *ptr = (uint8_t *)m.Channel(0, ch);
    const float alpha_ch = alpha_color[ch];
    for (int i = -half_thickness; i <= half_thickness; ++i) {
      for (int j = -half_thickness; j <= half_thickness; ++j) {
        if (i * i + j * j > quarter_thickness_square) {
          continue;
        }
        int new_x = p.x + j;
        int new_y = p.y + i;
        if (new_x < 0 || new_x >= m.w || new_y < 0 || new_y >= m.h) {
          continue;
        }
        size_t idx = new_y * m.wstride + new_x;
        auto &org = ptr[idx];
        org = (uint8_t)(alpha_ch + one_minus_alpha * org);
      }
    }
  }
}

void DrawLine(Mat &m, const CVPoint &p1, const CVPoint &p2,
              const CVColor &color, const int &thickness, const float &alpha) {
  // Bresenham's line algorithm
  int x0 = p1.x;
  int y0 = p1.y;
  int x1 = p2.x;
  int y1 = p2.y;
  const int dx = abs(x1 - x0);
  const int dy = abs(y1 - y0);
  const int sx = x0 < x1 ? 1 : -1;
  const int sy = y0 < y1 ? 1 : -1;
  int err = dx - dy;
  int e2;
  while (true) {
    DrawPoint(m, CVPoint{x0, y0}, color, thickness, alpha);
    if (x0 == x1 && y0 == y1) {
      break;
    }
    e2 = 2 * err;
    if (e2 > -dy) {
      err -= dy;
      x0 += sx;
    }
    if (e2 < dx) {
      err += dx;
      y0 += sy;
    }
  }
}

void DrawArrow(Mat &m, const CVPoint &p1, const CVPoint &p2,
               const CVColor &color, const int &thickness, const float &alpha) {
  DrawLine(m, p1, p2, color, thickness, alpha);
  constexpr float arrow_head_length = 10.f;
  constexpr float arrow_head_angle = 30.f;
  constexpr float arrow_head_angle_rad = arrow_head_angle * M_PI / 180.f;
  const float cos_angle = cos(arrow_head_angle_rad);
  const float sin_angle = sin(arrow_head_angle_rad);
  const float dx = p2.x - p1.x;
  const float dy = p2.y - p1.y;
  const float length = sqrt(dx * dx + dy * dy);
  const float arrow_head_length_ratio = arrow_head_length / length;
  const float arrow_head_dx = dx * arrow_head_length_ratio;
  const float arrow_head_dy = dy * arrow_head_length_ratio;
  const float arrow_head_dx1 =
      cos_angle * arrow_head_dx - sin_angle * arrow_head_dy;
  const float arrow_head_dy1 =
      sin_angle * arrow_head_dx + cos_angle * arrow_head_dy;
  const float arrow_head_dx2 =
      cos_angle * arrow_head_dx + sin_angle * arrow_head_dy;
  const float arrow_head_dy2 =
      -sin_angle * arrow_head_dx + cos_angle * arrow_head_dy;
  const CVPoint arrow_head1{int(p2.x - arrow_head_dx1),
                            int(p2.y - arrow_head_dy1)};
  const CVPoint arrow_head2{int(p2.x - arrow_head_dx2),
                            int(p2.y - arrow_head_dy2)};
  DrawLine(m, p2, arrow_head1, color, thickness, alpha);
  DrawLine(m, p2, arrow_head2, color, thickness, alpha);
}

void DrawRect(Mat &m, const CVPoint &p1, const CVPoint &p2,
              const CVColor &color, const int &thickness, const float &alpha) {
  const CVPoint p3{p1.x, p2.y};
  const CVPoint p4{p2.x, p1.y};
  DrawLine(m, p1, p3, color, thickness, alpha);
  DrawLine(m, p3, p2, color, thickness, alpha);
  DrawLine(m, p2, p4, color, thickness, alpha);
  DrawLine(m, p4, p1, color, thickness, alpha);
}

void DrawCircle(Mat &m, const CVPoint &center, const int &radius,
                const CVColor &color, const int &thickness,
                const float &alpha) {
  const int x0 = center.x;
  const int y0 = center.y;
  int x = radius;
  int y = 0;
  int err = 0;
  while (x >= y) {
    DrawPoint(m, CVPoint{x0 + x, y0 + y}, color, thickness, alpha);
    DrawPoint(m, CVPoint{x0 + y, y0 + x}, color, thickness, alpha);
    DrawPoint(m, CVPoint{x0 - y, y0 + x}, color, thickness, alpha);
    DrawPoint(m, CVPoint{x0 - x, y0 + y}, color, thickness, alpha);
    DrawPoint(m, CVPoint{x0 - x, y0 - y}, color, thickness, alpha);
    DrawPoint(m, CVPoint{x0 - y, y0 - x}, color, thickness, alpha);
    DrawPoint(m, CVPoint{x0 + y, y0 - x}, color, thickness, alpha);
    DrawPoint(m, CVPoint{x0 + x, y0 - y}, color, thickness, alpha);
    if (err <= 0) {
      y += 1;
      err += 2 * y + 1;
    }
    if (err > 0) {
      x -= 1;
      err -= 2 * x + 1;
    }
  }
}
void DrawPoints(Mat &m, const std::vector<CVPoint> &points,
                const CVColor &color, const size_t &thickness,
                const float &alpha, const PointsDrawType &type) {
  const size_t points_num = points.size();
  if (points_num == 0) {
    return;
  }
  if (type == PointsDrawType::NORMAL_DOT) {
    for (const auto &p : points) {
      DrawPoint(m, p, color, thickness, alpha);
    }
  } else if (type == PointsDrawType::DASH) {
    if (points_num == 1) {
      DrawPoint(m, points[0], color, thickness, alpha);
    } else {
      constexpr float dash_length = 10.f;
      for (size_t i = 0; i < points.size(); ++i) {
        if (i + 1 < points.size()) {
          const auto &p1 = points[i];
          const auto &p2 = points[i + 1];
          float x0 = p1.x;
          float y0 = p1.y;
          float x1 = p2.x;
          float y1 = p2.y;
          float dx = x1 - x0;
          float dy = y1 - y0;
          float length = sqrt(dx * dx + dy * dy);
          float dash_num = length / dash_length;
          dash_num = std::max(dash_num, 1.f);
          float dash_dx = dx / dash_num;
          float dash_dy = dy / dash_num;
          for (int j = 0; j < dash_num; j += 2) {
            int x = x0 + j * dash_dx;
            int y = y0 + j * dash_dy;
            int x_next = x0 + (j + 1) * dash_dx;
            int y_next = y0 + (j + 1) * dash_dy;
            DrawLine(m, CVPoint{x, y}, CVPoint{x_next, y_next}, color,
                     thickness, alpha);
          }
        }
      }
    }
  } else if (type == PointsDrawType::SOLID) {
    for (size_t i = 0; i < points.size(); i += 1) {
      if (i + 1 < points.size()) {
        DrawLine(m, points[i], points[i + 1], color, thickness, alpha);
      }
    }
  }
}

void DrawPolyline(Mat &m, const std::vector<CVPoint> &points,
                  const CVColor &color, const int &thickness,
                  const float &alpha) {
  const size_t points_num = points.size();
  for (size_t i = 0; i < points.size(); ++i) {
    DrawLine(m, points[i], points[(i + 1) % points_num], color, thickness,
             alpha);
  }
}
void Resize(const Mat &src, Mat &dst, const size_t &w, const size_t &h) {
  if (src.empty()) {
    LOG_ERROR << "src image is empty.";
    return;
  }
  if (w == 0 || h == 0) {
    LOG_ERROR << "resize width " << w << " or height " << h << " is invalid.";
    return;
  }
  if (src.w == w && src.h == h) {
    dst = src.clone();
    return;
  }
  if (&src == &dst) {
    LOG_ERROR << "src and dst image are the same.";
    return;
  }
  if (src.c != 1 && src.c != 3) {
    LOG_ERROR << "src image channel " << src.c << " is not supported.";
    return;
  }
  if (src.elemsize != sizeof(uint8_t)) {
    LOG_ERROR << "src image element size " << src.elemsize
              << " is not supported.";
    return;
  }
  if (src.n != 1) {
    LOG_ERROR << "src image n " << src.n << " is not supported.";
    return;
  }
  dst = Mat(w, h, src.c, src.elemsize);
  const float scale_x = (float)src.w / w;
  const float scale_y = (float)src.h / h;
  for (size_t ch = 0; ch < src.c; ++ch) {
    uint8_t *src_ptr = (uint8_t *)src.Channel(0, ch);
    uint8_t *dst_ptr = (uint8_t *)dst.Channel(0, ch);
    // bilinear interpolation
    for (size_t row = 0; row < h; ++row) {
      for (size_t col = 0; col < w; ++col) {
        float src_x = (col + 0.5f) * scale_x - 0.5f;
        float src_y = (row + 0.5f) * scale_y - 0.5f;
        int x0 = (int)src_x;
        int y0 = (int)src_y;
        int x1 = std::min(x0 + 1, (int)src.w - 1);
        int y1 = std::min(y0 + 1, (int)src.h - 1);
        float dx = src_x - x0;
        float dy = src_y - y0;
        float w00 = (1.0f - dx) * (1.0f - dy);
        float w01 = dx * (1.0f - dy);
        float w10 = (1.0f - dx) * dy;
        float w11 = dx * dy;
        size_t src_idx00 = y0 * src.w + x0;
        size_t src_idx01 = y0 * src.w + x1;
        size_t src_idx10 = y1 * src.w + x0;
        size_t src_idx11 = y1 * src.w + x1;
        size_t dst_idx = row * w + col;
        dst_ptr[dst_idx] =
            (uint8_t)(w00 * src_ptr[src_idx00] + w01 * src_ptr[src_idx01] +
                      w10 * src_ptr[src_idx10] + w11 * src_ptr[src_idx11]);
      }
    }
  }
}

void DrawText(Mat &m, const std::string &text, const CVPoint &p,
              const CVColor &color, const int &font_size, const float &alpha) {
  if (text.empty()) {
    return;
  }
  if (p.x < 0 || p.x >= m.w || p.y < 0 || p.y >= m.h) {
    LOG_ERROR << "point (" << p.x << ", " << p.y << ") is out of image range "
              << m.w << "x" << m.h;
    return;
  }
  if ((m.c != 1 and m.c != 3) or m.elemsize != sizeof(uint8_t) or m.n != 1) {
    LOG_ERROR << "image format is not supported. only support 1-channel or "
                 "3-channel uint8 image.";
    return;
  }
  if (alpha < 0.0f || alpha > 1.0f) {
    LOG_ERROR << "alpha value " << alpha << " is out of range [0, 1].";
    return;
  }
  int pix_size = adjust_font_size(font_size) * 8;
  int start_x = p.x;
  for (const auto &ch : text) {
    const unsigned char *font = get_ascii_image(font_size, ch);
    for (int i = 0; i < pix_size; ++i) {
      for (int j = 0; j < pix_size; ++j) {
        if (font[i * pix_size + j] > 0) {
          DrawPoint(m, CVPoint{start_x + j, p.y + i}, color, 1, alpha);
        }
      }
    }
    start_x += pix_size;
  }
}
CVSize GetTextSize(const std::string &str, const int &font_size) {
  CVSize size(0, 0);
  if (str.empty() or font_size < MIN_FONT_SIZE_VALUE or
      font_size > MAX_FONT_SIZE_VALUE) {
    return size;
  }
  size = CVSize(str.size() * font_size * 8, font_size * 8);
  return size;
}
} // namespace gcode