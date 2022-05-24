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
  PerlinGenHandle(ModuleWrapper::Ptr);

  /* Display Handle view on screen.
  int parameter is Module's order in the pipeline.*/
  bool showHandle(int, bool&) override;

private:
  // Processing parameters
  uint32_t& seed_;
  double& frequency_;
  uint32_t& octaves_;

  // Random seed engine/distribution
  std::default_random_engine seedEngine_;
  std::uniform_int_distribution<unsigned int> seedDistribution_;
};


