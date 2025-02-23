#include "plot/plot2d.h"

#include <algorithm>
#include <cmath>
#include <iomanip>
#include <sstream>

#include "glog.h"
namespace gcode {
constexpr size_t kPrecision = 0;
constexpr int kFontSize = 2;
constexpr int kTickSize = 5;
constexpr geometry_precition_t kVehicleLeft = -80.f;
constexpr geometry_precition_t kVehicleRight = 80.f;
constexpr geometry_precition_t kVehicleBottom = -50.f;
constexpr geometry_precition_t kVehicleTop = 200.f;
Plot2D::Plot2D(const size_t &width, const size_t &height,
               const std::string &title, const PLOT_TYPE &type)
    : image_(width, height, 3, sizeof(uint8_t)), title_(title),
      plot_type_(type) {
  image_.fill<uint8_t>(255);
}

void Plot2D::Reset() {
  history_data_.clear();
  legend_.clear();
  title_ = "";
  x_label_ = "";
  y_label_ = "";
  x_relative_margin_ = 0.1f;
  y_relative_margin_ = 0.1f;
  x_min_ = 0.f;
  x_max_ = 0.f;
  y_min_ = 0.f;
  y_max_ = 0.f;
  x_range_ = 0.f;
  y_range_ = 0.f;
  x_scale_ = 1.f;
  y_scale_ = 1.f;

  transform_valid_ = false;
  x_tick_offset_ = CVPoint(0, 0);
  y_tick_offset_ = CVPoint(0, 0);
  x_label_sign_ = 1;
  y_label_sign_ = 1;
}

void Plot2D::Plot(const vector_t &ys, const CVColor &color,
                  const PointsDrawType &draw_type, const int &thickness,
                  const std::string &label) {
  vector_t xs(ys.size());
  for (size_t i = 0; i < xs.size(); ++i) {
    xs[i] = i;
  }
  Plot(xs, ys, color, draw_type, thickness, label);
}

void Plot2D::Plot(const vector_t &xs, const vector_t &ys, const CVColor &color,
                  const PointsDrawType &draw_type, const int &thickness,
                  const std::string &label) {
  if (xs.size() != ys.size()) {
    LOG_ERROR << "The size of x and y must be the same: " << xs.size() << " vs "
              << ys.size();
    return;
  }
  if (xs.size() == 0) {
    LOG_ERROR << "The size of x and y must be greater than 0";
    return;
  }
  legend_.emplace_back(label, color, draw_type, thickness);
  history_data_.push_back(points_2d_t(xs.size(), 2));
  auto &data = history_data_.back();
  data.col(0).array() = xs;
  data.col(1).array() = ys;
}

void Plot2D::SetTitle(const std::string &title) { title_ = title; }

void Plot2D::SetXLabel(const std::string &label) { x_label_ = label; }

void Plot2D::SetYLabel(const std::string &label) { y_label_ = label; }

void Plot2D::Save(const std::string &filename) {
  GenTransform();
  if (not transform_valid_) {
    LOG_ERROR << "Failed to generate transform";
    return;
  }
  DrawHistory();
  DrawAxes();
  DrawLegend();
  DrawLabelAndTitle();
  WriteImage(filename, image_);
}

void Plot2D::GenTransform() {
  transform_valid_ = false;
  if (history_data_.empty()) {
    return;
  }
  if (plot_type_ == PLOT_TYPE::VEHICLE) {
    x_min_ = kVehicleBottom;
    y_min_ = kVehicleLeft;
    x_max_ = kVehicleTop;
    y_max_ = kVehicleRight;
    x_range_ = x_max_ - x_min_;
    y_range_ = y_max_ - y_min_;
  } else {
    x_min_ = std::numeric_limits<geometry_precition_t>::max();
    x_max_ = std::numeric_limits<geometry_precition_t>::lowest();
    y_min_ = std::numeric_limits<geometry_precition_t>::max();
    y_max_ = std::numeric_limits<geometry_precition_t>::lowest();
    for (const auto &data : history_data_) {
      x_min_ = std::min(x_min_, data.col(0).minCoeff());
      x_max_ = std::max(x_max_, data.col(0).maxCoeff());
      y_min_ = std::min(y_min_, data.col(1).minCoeff());
      y_max_ = std::max(y_max_, data.col(1).maxCoeff());
    }
    x_range_ = x_max_ - x_min_;
    y_range_ = y_max_ - y_min_;
    if (x_range_ == 0 or y_range_ == 0) {
      x_range_ = 2.f * std::fabs(x_min_);
      y_range_ = 2.f * std::fabs(y_min_);
    }
    geometry_precition_t x_margin = x_range_ * x_relative_margin_;
    geometry_precition_t y_margin = y_range_ * y_relative_margin_;
    x_min_ -= x_margin;
    x_max_ += x_margin;
    y_min_ -= y_margin;
    y_max_ += y_margin;
    x_range_ = x_max_ - x_min_;
    y_range_ = y_max_ - y_min_;
  }
  switch (plot_type_) {
  case PLOT_TYPE::DATA: {
    // x -> right, y -> up
    x_scale_ = image_.w / x_range_;
    y_scale_ = image_.h / y_range_;
    transform_ = [&](geometry_precition_t x, geometry_precition_t y) {
      int x_image = static_cast<int>((x - x_min_) * x_scale_);
      int y_image = static_cast<int>(image_.h - (y - y_min_) * y_scale_);
      return CVPoint(x_image, y_image);
    };
    x_tick_offset_ = CVPoint(0, -kTickSize);
    y_tick_offset_ = CVPoint(kTickSize, 0);
    x_label_sign_ = 1;
    y_label_sign_ = -1;
    break;
  }
  case PLOT_TYPE::IMAGE: {
    // x -> right, y -> down
    x_scale_ = image_.w / x_range_;
    y_scale_ = image_.h / y_range_;
    transform_ = [&](geometry_precition_t x, geometry_precition_t y) {
      int x_image = static_cast<int>((x - x_min_) * x_scale_);
      int y_image = static_cast<int>((y - y_min_) * y_scale_);
      return CVPoint(x_image, y_image);
    };
    x_tick_offset_ = CVPoint(0, kTickSize);
    y_tick_offset_ = CVPoint(kTickSize, 0);
    x_label_sign_ = 1;
    y_label_sign_ = 1;
    break;
  }
  case PLOT_TYPE::VEHICLE: {
    // x -> up, y -> left
    y_scale_ = image_.w / y_range_;
    x_scale_ = image_.h / x_range_;
    transform_ = [&](geometry_precition_t x, geometry_precition_t y) {
      int y_image = static_cast<int>(image_.h - (x - x_min_) * x_scale_);
      int x_image = static_cast<int>(image_.w - (y - y_min_) * y_scale_);
      return CVPoint(x_image, y_image);
    };
    x_tick_offset_ = CVPoint(kTickSize, 0);
    y_tick_offset_ = CVPoint(0, -kTickSize);
    x_label_sign_ = -1;
    y_label_sign_ = -1;
    break;
  }
  default: {
    LOG_ERROR << "Unknown plot type: " << static_cast<int>(plot_type_);
    return;
  }
  }
  transform_valid_ = true;
}

void Plot2D::DrawHistory() {
  if (not transform_valid_) {
    LOG_ERROR << "Failed to generate transform";
    return;
  }
  if (history_data_.empty()) {
    return;
  }
  for (size_t i = 0; i < history_data_.size(); ++i) {
    const auto &data = history_data_[i];
    const auto &label = std::get<0>(legend_[i]);
    const auto &color = std::get<1>(legend_[i]);
    const auto &draw_type = std::get<2>(legend_[i]);
    const auto &thickness = std::get<3>(legend_[i]);
    const auto &alpha = 1.0f;
    std::vector<CVPoint> points;
    points.reserve(data.rows());
    for (size_t j = 0; j < data.rows(); ++j) {
      points.push_back(transform_(data(j, 0), data(j, 1)));
    }
    DrawPoints(image_, points, color, thickness, alpha, draw_type);
  }
}

void Plot2D::DrawAxes() {
  if (not transform_valid_) {
    LOG_ERROR << "Failed to generate transform";
    return;
  }
  // x axis
  geometry_precition_t start_x = x_min_;
  geometry_precition_t start_y = 0;
  geometry_precition_t end_x = x_max_;
  geometry_precition_t end_y = 0;
  CVPoint start = transform_(start_x, start_y);
  CVPoint end = transform_(end_x, end_y);
  DrawArrow(image_, start, end, CVColor::BLACK, 1, 1.0f);
  geometry_precition_t x_step = std::pow(10, std::floor(std::log10(x_range_)));
  constexpr size_t kMinTicks = 5;
  size_t x_ticks = static_cast<size_t>(x_range_ / x_step);
  while (x_ticks < kMinTicks) {
    x_step /= 2;
    x_ticks = static_cast<size_t>(x_range_ / x_step);
  }
  for (geometry_precition_t x = 0; x >= x_min_; x -= x_step) {
    geometry_precition_t y = 0;
    start = transform_(x, y);
    end = start + x_tick_offset_;
    DrawLine(image_, start, end, CVColor::BLACK, 1, 1.0f);
    std::string text = ConvertToScientific(x);
    CVSize text_size = GetTextSize(text, kFontSize);
    text_size.width /= 2;
    text_size.height /= 2;
    CVPoint text_loc = start - x_tick_offset_ * (1.f / kTickSize) * text_size;
    DrawText(image_, text, text_loc, CVColor::BLACK, kFontSize, 1.0f);
  }
  for (geometry_precition_t x = x_step; x <= x_max_; x += x_step) {
    geometry_precition_t y = 0;
    start = transform_(x, y);
    end = start + x_tick_offset_;
    DrawLine(image_, start, end, CVColor::BLACK, 1, 1.0f);
    std::string text = ConvertToScientific(x);
    CVSize text_size = GetTextSize(text, kFontSize);
    text_size.width /= 2;
    text_size.height /= 2;
    CVPoint text_loc = start - x_tick_offset_ * (1.f / kTickSize) * text_size;
    DrawText(image_, text, text_loc, CVColor::BLACK, kFontSize, 1.0f);
  }
  // y axis
  start_x = 0;
  start_y = y_min_;
  end_x = 0;
  end_y = y_max_;
  DrawArrow(image_, transform_(start_x, start_y), transform_(end_x, end_y),
            CVColor::BLACK, 1, 1.0f);
  geometry_precition_t y_step = std::pow(10, std::floor(std::log10(y_range_)));
  size_t y_ticks = static_cast<size_t>(y_range_ / y_step);
  while (y_ticks < kMinTicks) {
    y_step /= 2;
    y_ticks = static_cast<size_t>(y_range_ / y_step);
  }
  for (geometry_precition_t y = -y_step; y >= y_min_; y -= y_step) {
    geometry_precition_t x = 0;
    start = transform_(x, y);
    end = start + y_tick_offset_;
    DrawLine(image_, start, end, CVColor::BLACK, 1, 1.0f);
    std::string text = ConvertToScientific(y);
    CVSize text_size = GetTextSize(text, kFontSize);
    text_size.width /= 2;
    text_size.height /= 2;
    CVPoint text_loc = start - y_tick_offset_ * (1.f / kTickSize) * text_size;
    DrawText(image_, text, text_loc, CVColor::BLACK, kFontSize, 1.0f);
  }
  for (geometry_precition_t y = y_step; y <= y_max_; y += y_step) {
    geometry_precition_t x = 0;
    start = transform_(x, y);
    end = start + y_tick_offset_;
    DrawLine(image_, start, end, CVColor::BLACK, 1, 1.0f);
    std::string text = ConvertToScientific(y);
    CVSize text_size = GetTextSize(text, kFontSize);
    text_size.width /= 2;
    text_size.height /= 2;
    CVPoint text_loc = start - y_tick_offset_ * (1.f / kTickSize) * text_size;
    DrawText(image_, text, text_loc, CVColor::BLACK, kFontSize, 1.0f);
  }
}

void Plot2D::DrawLegend() {
  if (not transform_valid_) {
    LOG_ERROR << "Failed to generate transform";
    return;
  }
  const int start_x = 20;
  const int start_y = 20;
  const int delta_y = kFontSize * 8 * 2;
  int index = 0;
  for (size_t i = 0; i < legend_.size(); ++i) {
    const auto &legend = legend_[i];
    const auto &label = std::get<0>(legend);
    if (label.empty()) {
      continue;
    }
    const auto &color = std::get<1>(legend);
    const auto &draw_type = std::get<2>(legend);
    const auto &thickness = std::get<3>(legend);
    CVPoint start(start_x, start_y + index * delta_y);
    CVPoint end(start_x + 20, start_y + index * delta_y);
    DrawPoints(image_, {start, end}, color, thickness, 1.0f, draw_type);
    DrawText(image_, label, CVPoint(end.x + 5, end.y - kFontSize * 4), color,
             kFontSize, 1.0f);
    index++;
  }
}

void Plot2D::DrawLabelAndTitle() {
  if (not transform_valid_) {
    LOG_ERROR << "Failed to generate transform";
    return;
  }
  if (not title_.empty()) {
    size_t text_size = kFontSize * 8 * title_.size();
    DrawText(image_, title_,
             CVPoint(image_.w / 2 - text_size / 2, kFontSize * 8),
             CVColor::CYAN, kFontSize, 1.0f);
  }
  if (not x_label_.empty()) {
    size_t text_size = kFontSize * 8 * x_label_.size();
    CVPoint point = transform_(x_max_, 0);
    point.x -= text_size * x_label_sign_;
    DrawText(image_, x_label_, point, CVColor::CYAN, kFontSize, 1.0f);
  }
  if (not y_label_.empty()) {
    CVPoint point = transform_(0, y_max_);
    point.y -= kFontSize * 8 * y_label_sign_;
    DrawText(image_, y_label_, point, CVColor::CYAN, kFontSize, 1.0f);
  }
}

std::string Plot2D::ConvertToScientific(const geometry_precition_t &value) {
  // std::ostringstream oss;
  // oss << std::scientific << std::setprecision(kPrecision) << value;
  // return oss.str();
  return std::to_string(int(value));
}
} // namespace gcode
