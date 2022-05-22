#pragma once
#include <vector>

#include <MapBuilderCore.h>

#include "modules\ModuleWrapper.h"

struct ApplicationContext
{
  mbc::Pipeline pipeline;
  std::vector<ModuleWrapper::Ptr> modules;
};
