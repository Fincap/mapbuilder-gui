#pragma once
#include <vector>

#include <MapBuilderCore.h>

#include "wrappers\ModuleWrapper.h"

struct ApplicationContext
{
  mbc::Pipeline pipeline;
  std::vector<ModuleWrapper::Ptr> modules;
};
