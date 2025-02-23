// @author: gezhipeng @ 20250222
// @file: geometry.h
// @brief: geometry

#ifndef SRC_ALGORITHM_GEOMETRY_H_
#define SRC_ALGORITHM_GEOMETRY_H_

#include <Eigen/Dense>
#include <cmath>
#include <limits>

namespace gcode {
typedef Eigen::Vector2d vector2d_t;
typedef Eigen::Vector3d vector3d_t;
typedef Eigen::Vector2f vector2f_t;
typedef Eigen::Vector3f vector3f_t;

template <typename T> using vector2_t = Eigen::Matrix<T, 2, 1, Eigen::ColMajor>;
template <typename T> using vector3_t = Eigen::Matrix<T, 3, 1, Eigen::ColMajor>;

typedef Eigen::Matrix<double, Eigen::Dynamic, 2, Eigen::ColMajor> points_2d_t;
typedef Eigen::Matrix<double, Eigen::Dynamic, 3, Eigen::ColMajor> points_3d_t;
typedef Eigen::Matrix<float, Eigen::Dynamic, 2, Eigen::ColMajor> points_2f_t;
typedef Eigen::Matrix<float, Eigen::Dynamic, 3, Eigen::ColMajor> points_3f_t;

template <typename T>
T DistanceToSegment(const vector2_t<T> &p, const vector2_t<T> &a,
                    const vector2_t<T> &b);

template <typename T>
T DistanceToSegment(const vector3_t<T> &p, const vector3_t<T> &a,
                    const vector3_t<T> &b);

template <typename T>
T DistanceToPolyLine(
    const vector2_t<T> &p,
    const Eigen::Matrix<T, Eigen::Dynamic, 2, Eigen::ColMajor> &poly_line,
    const bool &is_closed = false);

template <typename T>
T DistanceToPolyLine(
    const vector3_t<T> &p,
    const Eigen::Matrix<T, Eigen::Dynamic, 3, Eigen::ColMajor> &poly_line,
    const bool &is_closed = false);

template <typename T>
bool IsInterselected(const vector2_t<T> &a, const vector2_t<T> &b,
                     const vector2_t<T> &c, const vector2_t<T> &d,
                     vector2_t<T> &inter_point);

template <typename T>
bool IsPointInPolygon(
    const vector2_t<T> &p,
    const Eigen::Matrix<T, Eigen::Dynamic, 2, Eigen::ColMajor> &polygon);

template <typename T>
T DistanceToPolygon(
    const vector2_t<T> &p,
    const Eigen::Matrix<T, Eigen::Dynamic, 2, Eigen::ColMajor> &polygon);

template <typename T>
T DistanceToSegment(const vector2_t<T> &p, const vector2_t<T> &a,
                    const vector2_t<T> &b) {
  const vector2_t<T> ab = b - a;
  const vector2_t<T> ap = p - a;
  const vector2_t<T> bp = p - b;

  const T projection = ap.dot(ab); // 点 p 在 ab 上的投影长度
  const T ab_squared_length = ab.squaredNorm(); // ab 的长度的平方

  // 如果投影为负，点 p 在 a 的外侧
  if (projection <= 0) {
    return ap.norm();
  }

  // 如果投影大于 ab 的长度，点 p 在 b 的外侧
  if (projection >= ab_squared_length) {
    return bp.norm();
  }

  // 计算点 p 到线段 ab 的垂直距离
  return std::abs(ap.cross(ab)) / std::sqrt(ab_squared_length);
}

template <typename T>
T DistanceToSegment(const vector3_t<T> &p, const vector3_t<T> &a,
                    const vector3_t<T> &b) {
  const vector3_t<T> ab = b - a;
  const vector3_t<T> ap = p - a;
  const vector3_t<T> bp = p - b;

  const T projection = ap.dot(ab); // 点 p 在 ab 上的投影长度
  const T ab_squared_length = ab.squaredNorm(); // ab 的长度的平方

  // 如果投影为负，点 p 在 a 的外侧
  if (projection <= 0) {
    return ap.norm();
  }

  // 如果投影大于 ab 的长度，点 p 在 b 的外侧
  if (projection >= ab_squared_length) {
    return bp.norm();
  }

  // 计算点 p 到线段 ab 的垂直距离
  return (ap - ab * (projection / ab_squared_length)).norm();
}

// Implementation of DistanceToPolyLine for 2D
template <typename T>
T DistanceToPolyLine(
    const vector2_t<T> &p,
    const Eigen::Matrix<T, Eigen::Dynamic, 2, Eigen::ColMajor> &poly_line,
    const bool &is_closed) {
  if (poly_line.rows() == 0) {
    return std::numeric_limits<T>::max();
  }
  if (poly_line.rows() == 1) {
    return (vector2_t<T>(poly_line(0, 0), poly_line(0, 1)) - p).norm();
  }

  T min_distance = std::numeric_limits<T>::max();
  int points_num = poly_line.rows();
  int max_index = is_closed ? points_num : points_num - 1;

  for (int i = 0; i < max_index; ++i) {
    vector2_t<T> p1(poly_line(i, 0), poly_line(i, 1));
    vector2_t<T> p2(poly_line((i + 1) % points_num, 0),
                    poly_line((i + 1) % points_num, 1));
    T distance = DistanceToSegment(p, p1, p2);
    if (distance < min_distance) {
      min_distance = distance;
    }
  }
  return min_distance;
}

// Implementation of DistanceToPolyLine for 3D
template <typename T>
T DistanceToPolyLine(
    const vector3_t<T> &p,
    const Eigen::Matrix<T, Eigen::Dynamic, 3, Eigen::ColMajor> &poly_line,
    const bool &is_closed) {
  if (poly_line.rows() == 0) {
    return std::numeric_limits<T>::max();
  }
  if (poly_line.rows() == 1) {
    return (vector3_t<T>(poly_line(0, 0), poly_line(0, 1), poly_line(0, 2)) - p)
        .norm();
  }

  T min_distance = std::numeric_limits<T>::max();
  int points_num = poly_line.rows();
  int max_index = is_closed ? points_num : points_num - 1;

  for (int i = 0; i < max_index; ++i) {
    vector3_t<T> p1(poly_line(i, 0), poly_line(i, 1), poly_line(i, 2));
    vector3_t<T> p2(poly_line((i + 1) % points_num, 0),
                    poly_line((i + 1) % points_num, 1),
                    poly_line((i + 1) % points_num, 2));
    T distance = DistanceToSegment(p, p1, p2);
    if (distance < min_distance) {
      min_distance = distance;
    }
  }
  return min_distance;
}

// Implementation of IsInterselected
template <typename T>
bool IsInterselected(const vector2_t<T> &a, const vector2_t<T> &b,
                     const vector2_t<T> &c, const vector2_t<T> &d,
                     vector2_t<T> &inter_point) {
  vector2_t<T> ab = b - a;
  vector2_t<T> ac = c - a;
  vector2_t<T> ad = d - a;

  vector2_t<T> cd = d - c;
  vector2_t<T> ca = a - c;
  vector2_t<T> cb = b - c;

  // 计算叉乘
  T cross_ab_to_ac = ab.cross(ac);
  T cross_ab_to_ad = ab.cross(ad);
  T cross_cd_to_ca = cd.cross(ca);
  T cross_cd_to_cb = cd.cross(cb);

  // 相交
  if (cross_ab_to_ac * cross_ab_to_ad < 0 and
      cross_cd_to_ca * cross_cd_to_cb < 0) {
    T u = cross_ab_to_ac / cd.cross(ab);
    inter_point = c + u * cd;
    return true;
  }

  // 检查端点是否位于另一条线段上
  T epsilon = std::numeric_limits<T>::epsilon();
  if (cross_ab_to_ac < epsilon and cross_ab_to_ad < epsilon) {
    inter_point = a;
    return true;
  }
  if (cross_ab_to_ac > -epsilon and cross_ab_to_ad > -epsilon) {
    inter_point = b;
    return true;
  }
  if (cross_cd_to_ca < epsilon and cross_cd_to_cb < epsilon) {
    inter_point = c;
    return true;
  }
  if (cross_cd_to_ca > -epsilon and cross_cd_to_cb > -epsilon) {
    inter_point = d;
    return true;
  }
  return false;
}

// Implementation of IsPointInPolygon
template <typename T>
bool IsPointInPolygon(
    const vector2_t<T> &p,
    const Eigen::Matrix<T, Eigen::Dynamic, 2, Eigen::ColMajor> &polygon) {
  if (polygon.rows() < 3) {
    return false;
  }
  int count = 0;
  for (int i = 0; i < polygon.rows(); ++i) {
    vector2_t<T> p1(polygon(i, 0), polygon(i, 1));
    vector2_t<T> p2(polygon((i + 1) % polygon.rows(), 0),
                    polygon((i + 1) % polygon.rows(), 1));
    if (p1.y() == p2.y()) {
      continue;
    }
    if (p.y() < std::min(p1.y(), p2.y())) {
      continue;
    }
    if (p.y() >= std::max(p1.y(), p2.y())) {
      continue;
    }
    T x = (p.y() - p1.y()) * (p2.x() - p1.x()) / (p2.y() - p1.y()) + p1.x();
    if (x > p.x()) {
      count++;
    }
  }
  return count % 2 == 1;
}

// Implementation of DistanceToPolygon
template <typename T>
T DistanceToPolygon(
    const vector2_t<T> &p,
    const Eigen::Matrix<T, Eigen::Dynamic, 2, Eigen::ColMajor> &polygon) {
  if (IsPointInPolygon(p, polygon)) {
    return static_cast<T>(0);
  }
  return DistanceToPolyLine(p, polygon, true);
}

} // namespace gcode
#endif // SRC_ALGORITHM_GEOMETRY_H_