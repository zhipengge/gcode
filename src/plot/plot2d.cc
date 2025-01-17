// #include "plot/plot2d.h"
// #include <algorithm>
// #include <cmath>

// namespace gcode {

// Plot2D::Plot2D(int width, int height, const std::string& title)
//     : image_(height, width), title_(title),
//       x_min_(0), x_max_(1), y_min_(0), y_max_(1) {
//     image_.Fill(CVColor_WHITE); // 设置背景为白色
// }

// void Plot2D::Plot(const std::vector<double>& x, const std::vector<double>& y,
//                   const CVColor& color, const std::string& label) {
//     if (x.empty() || y.empty() || x.size() != y.size()) return;

//     AutoScale(x, y);
//     if (!label.empty()) {
//         legend_.emplace_back(label, color);
//     }

//     // 转换坐标
//     auto toPixelX = [this](double x) {
//         return static_cast<int>((x - x_min_) / (x_max_ - x_min_) *
//                               (image_.cols - 2 * margin_) + margin_);
//     };

//     auto toPixelY = [this](double y) {
//         return static_cast<int>((y_max_ - y) / (y_max_ - y_min_) *
//                               (image_.rows - 2 * margin_) + margin_);
//     };

//     // 绘制折线
//     for (size_t i = 1; i < x.size(); ++i) {
//         int x1 = toPixelX(x[i-1]);
//         int y1 = toPixelY(y[i-1]);
//         int x2 = toPixelX(x[i]);
//         int y2 = toPixelY(y[i]);
//         DrawLine(image_, {x1, y1}, {x2, y2}, color);
//     }

//     DrawAxes();
//     DrawLegend();
// }

// void Plot2D::Scatter(const std::vector<double>& x, const std::vector<double>&
// y,
//                      const CVColor& color, const std::string& label) {
//     if (x.empty() || y.empty() || x.size() != y.size()) return;

//     AutoScale(x, y);
//     if (!label.empty()) {
//         legend_.emplace_back(label, color);
//     }

//     // 转换坐标
//     auto toPixelX = [this](double x) {
//         return static_cast<int>((x - x_min_) / (x_max_ - x_min_) *
//                               (image_.Width() - 2 * margin_) + margin_);
//     };

//     auto toPixelY = [this](double y) {
//         return static_cast<int>((y_max_ - y) / (y_max_ - y_min_) *
//                               (image_.Height() - 2 * margin_) + margin_);
//     };

//     // 绘制散点
//     const int point_radius = 3;
//     for (size_t i = 0; i < x.size(); ++i) {
//         int px = toPixelX(x[i]);
//         int py = toPixelY(y[i]);
//         DrawCircle(image_, {px, py}, point_radius, color);
//     }

//     DrawAxes();
//     DrawLegend();
// }

// void Plot2D::SetTitle(const std::string& title) {
//     title_ = title;
// }

// void Plot2D::SetXLabel(const std::string& label) {
//     x_label_ = label;
// }

// void Plot2D::SetYLabel(const std::string& label) {
//     y_label_ = label;
// }

// void Plot2D::Show() {
//     image_.Show();
// }

// void Plot2D::Save(const std::string& filename) {
//     image_.Save(filename);
// }

// void Plot2D::DrawAxes() {
//     // 绘制坐标轴
//     int width = image_.Width();
//     int height = image_.Height();

//     // X轴
//     DrawLine(image_, {margin_, height - margin_}, {width - margin_, height -
//     margin_}, CVColor_BLACK);
//     // Y轴
//     DrawLine(image_, {margin_, margin_}, {margin_, height - margin_},
//     CVColor_BLACK);
// }

// void Plot2D::DrawLegend() {
//     // TODO: 实现图例绘制
// }

// void Plot2D::AutoScale(const std::vector<double>& x, const
// std::vector<double>& y) {
//     auto [x_min, x_max] = std::minmax_element(x.begin(), x.end());
//     auto [y_min, y_max] = std::minmax_element(y.begin(), y.end());

//     // 添加10%的边距
//     double x_range = *x_max - *x_min;
//     double y_range = *y_max - *y_min;

//     x_min_ = *x_min - 0.1 * x_range;
//     x_max_ = *x_max + 0.1 * x_range;
//     y_min_ = *y_min - 0.1 * y_range;
//     y_max_ = *y_max + 0.1 * y_range;
// }

// }  // namespace gcode
