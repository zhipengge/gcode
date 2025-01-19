// @author: gezhipeng @ 20250118
// @file: plot2d.h
// @brief: plot2d
#ifndef SRC_PLOT_PLOT2D_H_
#define SRC_PLOT_PLOT2D_H_
#include "base/base_defines.h"
#include "cv/gimage.h"
#include <string>
#include <tuple>
#include <vector>

namespace gcode {
enum class PLOT_TYPE {
  IMAGE = 0,
  DATA = 1,
  VEHICLE = 2,
};
class Plot2D {
public:
  Plot2D(const size_t &width = 800, const size_t &height = 600,
         const std::string &title = "",
         const PLOT_TYPE &type = PLOT_TYPE::DATA);
  void Plot(const vector_t &ys, const CVColor &color = CVColor_BLUE,
            const PointsDrawType &draw_type = PointsDrawType::SOLID,
            const int &thickness = 1, const std::string &label = "");
  void Plot(const vector_t &xs, const vector_t &ys,
            const CVColor &color = CVColor_BLUE,
            const PointsDrawType &draw_type = PointsDrawType::SOLID,
            const int &thickness = 1, const std::string &label = "");

  void SetTitle(const std::string &title);

  void SetXLabel(const std::string &label);

  void SetYLabel(const std::string &label);

  void Save(const std::string &filename);

private:
  void GenTransform();
  void DrawHistory();
  void DrawAxes();
  void DrawLegend();
  void DrawLabelAndTitle();
  std::string ConvertToScientific(const geometry_precition_t &value);

  Mat image_;
  std::string title_;
  std::string x_label_;
  std::string y_label_;
  std::vector<std::tuple<std::string, CVColor, PointsDrawType, int>>
      legend_; // label, color, draw_type, thickness
  PLOT_TYPE plot_type_ = PLOT_TYPE::DATA;
  std::vector<points_2d_t> history_data_;
  geometry_precition_t x_relative_margin_ = 0.1f;
  geometry_precition_t y_relative_margin_ = 0.1f;
  geometry_precition_t x_min_ = 0.f;
  geometry_precition_t x_max_ = 0.f;
  geometry_precition_t y_min_ = 0.f;
  geometry_precition_t y_max_ = 0.f;
  geometry_precition_t x_range_ = 0.f;
  geometry_precition_t y_range_ = 0.f;
  geometry_precition_t x_scale_ = 1.f;
  geometry_precition_t y_scale_ = 1.f;

  CVPoint x_tick_offset_{0, 0};
  CVPoint y_tick_offset_{0, 0};
  int x_label_sign_ = 1;
  int y_label_sign_ = 1;
  std::function<CVPoint(geometry_precition_t, geometry_precition_t)> transform_;
  bool transform_valid_ = false;
};

} // namespace gcode

#endif // SRC_PLOT_PLOT2D_H_
