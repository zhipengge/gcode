// @author: gezhipeng @ 20231002
// @file: layer.cc
// @brief: layer
#include "layer.h"
namespace gcode {
namespace nn {
Layer::Layer() {}
Layer::~Layer() {}
int Layer::LoadParam(const ParamData &param) { return 0; }
int Layer::LoadModel(const ModelData &model) { return 0; }
int Layer::Build(const ModelOptions &options) { return 0; }
int Layer::Destroy(const ModelOptions &options) { return 0; }
int Layer::Forward(const std::vector<base::Mat> &bottoms,
                   std::vector<base::Mat> *tops,
                   const ModelOptions &options) const {
  return 0;
}
} // namespace nn
} // namespace gcode