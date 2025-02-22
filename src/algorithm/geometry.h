// @author: gezhipeng @ 20250222
// @file: geometry.h
// @brief: geometry

#ifndef SRC_ALGORITHM_GEOMETRY_H_
#define SRC_ALGORITHM_GEOMETRY_H_
#include <Eigen/Dense>
namespace gcode {
typedef Eigen::Vector2d vector2d_t;
typedef Eigen::Vector3d vector3d_t;
typedef Eigen::Vector2f vector2f_t;
typedef Eigen::Vector3f vector3f_t;

typedef Eigen::Matrix<double, Eigen::Dynamic, 2, Eigen::RowMajor> points_2d_t;
typedef Eigen::Matrix<double, Eigen::Dynamic, 3, Eigen::RowMajor> points_3d_t;
typedef Eigen::Matrix<float, Eigen::Dynamic, 2, Eigen::RowMajor> points_2f_t;
typedef Eigen::Matrix<float, Eigen::Dynamic, 3, Eigen::RowMajor> points_3f_t;

template <typename T>
T DistanceToSegment(const Eigen::Vector2<T> &p, const Eigen::Vector2<T> &a,
                    const Eigen::Vector2<T> &b) {
  Eigen::Vector2<T> ab = b - a;
  Eigen::Vector2<T> ap = p - a;
  Eigen::Vector2<T> bp = p - b;

  T e = ap.dot(ab);
  if (e <= 0) {
    return ap.norm();
  }

  T f = ab.dot(ab);
  if (e >= f) {
    return bp.norm();
  }

  if (f <= std::numeric_limits<T>::epsilon()) {
    return ap.norm();
  }

  return std::abs(ap.cross(ab)) / std::sqrt(f);
}

template <typename T>
T DistanceToSegment(const Eigen::Vector3<T> &p, const Eigen::Vector3<T> &a,
                    const Eigen::Vector3<T> &b) {
  Eigen::Vector3<T> ab = b - a;
  Eigen::Vector3<T> ap = p - a;
  Eigen::Vector3<T> bp = p - b;
  T e = ap.dot(ab);
  if (e <= 0) {
    return ap.norm();
  }
  T f = ab.dot(ab);
  if (e >= f) {
    return bp.norm();
  }
  return (ap - ab * e / f).norm();
}

template <typename T>
T DistanceToPolyLine(const Eigen::Vector2<T> &p,
                     const Eigen::Matrix<double, Eigen::Dynamic, 2,
                                         Eigen::RowMajor> &poly_line) {
  if (poly_line.rows() == 0) {
    return std::numeric_limits<T>::max();
  }
  if (poly_line.rows() == 1) {
    return (poly_line.row(0).transpose() - p).norm();
  }
  T min_distance = std::numeric_limits<T>::max();
  for (int i = 0; i < poly_line.rows() - 1; ++i) {
    T distance = DistanceToSegment(p, poly_line.row(i), poly_line.row(i + 1));
    if (distance < min_distance) {
      min_distance = distance;
    }
  }
  return min_distance;
}

template <typename T>
T DistanceToPolyLine(const Eigen::Vector3<T> &p,
                     const Eigen::Matrix<double, Eigen::Dynamic, 3,
                                         Eigen::RowMajor> &poly_line) {
  if (poly_line.rows() == 0) {
    return std::numeric_limits<T>::max();
  }
  if (poly_line.rows() == 1) {
    return (poly_line.row(0).transpose() - p).norm();
  }
  T min_distance = std::numeric_limits<T>::max();
  for (int i = 0; i < poly_line.rows() - 1; ++i) {
    T distance = DistanceToSegment(p, poly_line.row(i), poly_line.row(i + 1));
    if (distance < min_distance) {
      min_distance = distance;
    }
  }
  return min_distance;
}
} // namespace gcode
#endif // SRC_ALGORITHM_GEOMETRY_H_