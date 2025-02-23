// @author: gezhipeng @ 20231002
// @file: layer.h
// @brief: layer
#include <vector>

#include "gmat.h"
#include "model.h"
#include "options.h"
#include "param.h"
namespace gcode {
class Layer {
public:
  /// @brief constructor
  Layer();
  /// @brief destructor
  virtual ~Layer();
  /// @brief load param dict
  /// @param param
  /// @return
  virtual int LoadParam(const ParamData &param);
  /// @brief load model struct
  /// @param model
  /// @return
  virtual int LoadModel(const ModelData &model);
  /// @brief build model ppl
  /// @param options
  /// @return
  virtual int Build(const ModelOptions &options);
  /// @brief destroy model ppl
  /// @param options
  /// @return
  virtual int Destroy(const ModelOptions &options);
  /// @brief
  /// @param bottoms
  /// @param tops
  /// @return
  virtual int Forward(const std::vector<Mat> &bottoms, std::vector<Mat> *tops,
                      const ModelOptions &options) const;

private:
};
} // namespace gcode