// @author: gezhipeng @ 20231002
// @file: param.cc
// @brief: param
#include "param.h"
#include "glog.h"
namespace gcode {
ParamData::ParamData() {}
ParamData::~ParamData() { clear(); }
ParamData::ParamData(const ParamData &p) {
  for (int i = 0; i < MAX_PARAM_NUM; ++i) {
    params_[i] = p.GetParam(i);
  }
}
ParamData &ParamData::operator=(const ParamData &p) {
  for (int i = 0; i < MAX_PARAM_NUM; ++i) {
    params_[i] = p.GetParam(i);
  }
  return *this;
}
const ParamCell &ParamData::GetParam(const int &id) const {
  if (id >= MAX_PARAM_NUM || id < 0) {
    LOG_ERROR << "index " << id << " out of range " << MAX_PARAM_NUM;
    return empty_param_;
  }
  return params_[id];
}
void ParamData::SetParam(const int &id, const ParamCell &p) {
  if (id < 0 || id >= MAX_PARAM_NUM) {
    LOG_ERROR << "index " << id << " out of range " << MAX_PARAM_NUM;
  }
  params_[id] = p;
}
void ParamData::clear() {
  for (int i = 0; i < MAX_PARAM_NUM; ++i) {
    params_[i].type = ParamType::NONE;
    params_[i].array.release();
  }
}
} // namespace gcode