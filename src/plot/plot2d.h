// #ifndef SRC_PLOT_PLOT2D_H_
// #define SRC_PLOT_PLOT2D_H_
// #include "base/base_defines.h"
// #include "cv/gimage.h"
// #include <vector>
// #include <string>

// namespace gcode {
// enum class PLOT_TYPE {
//     IMAGE = 0,
//     DATA = 1,
//     VEHICLE = 2,
// };
// class Plot2D {
// public:
//     Plot2D(int width = 800, int height = 600, const std::string& title = "",
//     const PLOT_TYPE& type = PLOT_TYPE::DATA); void Plot(const vector_t& ys,
//     const CVColor& color = CVColor_BLUE, const PointsDrawType&
//     marker=PointsDrawType::SOLID, const std::string& label = ""); void
//     Plot(const vector_t& xs, const vector_t& ys, const CVColor& color =
//     CVColor_BLUE, const PointsDrawType& marker=PointsDrawType::SOLID, const
//     std::string& label = "");

//     // 设置标题
//     void SetTitle(const std::string& title);

//     // 设置x轴标签
//     void SetXLabel(const std::string& label);

//     // 设置y轴标签
//     void SetYLabel(const std::string& label);

//     // 显示图像
//     void Show();

//     // 保存图像
//     void Save(const std::string& filename);

// private:
//     void DrawAxes();
//     void DrawLegend();
//     void AutoScale(const std::vector<double>& x, const std::vector<double>&
//     y);

//     Mat image_;
//     std::string title_;
//     std::string x_label_;
//     std::string y_label_;
//     std::vector<std::pair<std::string, CVColor>> legend_;

//     double x_min_, x_max_;
//     double y_min_, y_max_;
//     int margin_ = 50;
// };

// }  // namespace gcode

// #endif  // SRC_PLOT_PLOT2D_H_
