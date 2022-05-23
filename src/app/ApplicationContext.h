#pragma once
#include <vector>

#include <MapBuilderCore.h>

#include "modules\ModuleWrapper.h"

struct ApplicationContext
{
  mbc::Pipeline pipeline;
  mbc::StageMap<ModuleWrapper::Ptr> modules;

  /*ApplicationContext()
  {
    modules = new mbc::StageMap<ModuleWrapper::Ptr>();
  }

  ~ApplicationContext()
  {
    delete modules;
  }*/
};
