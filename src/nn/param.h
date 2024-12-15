// @author: gezhipeng @ 20231002
// @file: param.h
// @brief: param
#ifndef SRC_NN_PARAM_H_
#define SRC_NN_PARAM_H_
#define MAX_PARAM_NUM 32
#include "gmat.h"
namespace gcode {
enum class ParamType {
  NONE = 0,
  INT = 1,
  FLOAT = 2,
  INT_ARRAY = 3,
  FLOAT_ARRAY = 4
};
struct ParamCell {
  ParamType type = ParamType::NONE;
  union {
    int i;
    float f;
  };
  Mat array;
  ParamCell &operator=(const ParamCell &c) {
    type = c.type;
    switch (type) {
    case ParamType::INT:
      i = c.i;
      break;
    case ParamType::FLOAT:
      f = c.f;
      break;
    case ParamType::INT_ARRAY:
      array = c.array;
      break;
    case ParamType::FLOAT_ARRAY:
      array = c.array;
      break;
    default:
      break;
    }
    return *this;
  }
};
class ParamData {
public:
  ParamData();
  virtual ~ParamData();
  ParamData(const ParamData &);
  ParamData &operator=(const ParamData &);
  const ParamCell &GetParam(const int &id) const;
  void SetParam(const int &id, const ParamCell &);

protected:
  void clear();

private:
  ParamCell params_[MAX_PARAM_NUM];
  ParamCell empty_param_;
};
} // namespace gcode
#endif // SRC_NN_PARAM_H_