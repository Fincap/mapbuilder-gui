#pragma once
#include <memory>
#include <string>
#include <random>

#include <imgui.h>

#include "modules\ModuleHandle.h"
#include "modules\ModuleWrapper.h"

/*
Handle for PerlinGen module.
*/
class PerlinGenHandle : public ModuleHandle
{
public:
  PerlinGenHandle();
  PerlinGenHandle(mbc::Module::Ptr);

  /* Display Handle view on screen.
  int parameter is Module's order in the pipeline.*/
  bool showHandle(int, bool&) override;

  template <typename Archive>
  void serialize(Archive& archive) {};

private:
  // Processing parameters
  uint32_t& seed_;
  double& frequency_;
  uint32_t& octaves_;

  // Random seed engine/distribution
  std::default_random_engine seedEngine_;
  std::uniform_int_distribution<unsigned int> seedDistribution_;
};


CEREAL_REGISTER_TYPE(PerlinGenHandle);
CEREAL_REGISTER_POLYMORPHIC_RELATION(ModuleHandle, PerlinGenHandle);
