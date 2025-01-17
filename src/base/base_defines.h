// @author: gezhipeng @ 20250117
// @file: base_defines.h
// @brief: base_defines
#ifndef SRC_BASE_BASE_DEFINES_H_
#define SRC_BASE_BASE_DEFINES_H_
#include <Eigen/Core>
using geometry_precition_t = float;
using vector_t = Eigen::VectorX<geometry_precition_t>;
using point_2d_t = Eigen::Matrix<geometry_precition_t, 1, 2, Eigen::RowMajor>;
using point_3d_t = Eigen::Matrix<geometry_precition_t, 1, 3, Eigen::RowMajor>;
using point_4d_t = Eigen::Matrix<geometry_precition_t, 1, 4, Eigen::RowMajor>;
using points_2d_t =
    Eigen::Matrix<geometry_precition_t, Eigen::Dynamic, 2, Eigen::RowMajor>;
using points_3d_t =
    Eigen::Matrix<geometry_precition_t, Eigen::Dynamic, 3, Eigen::RowMajor>;
using points_4d_t =
    Eigen::Matrix<geometry_precition_t, Eigen::Dynamic, 4, Eigen::RowMajor>;
#endif // SRC_BASE_BASE_DEFINES_H_