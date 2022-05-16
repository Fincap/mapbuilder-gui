#pragma once
#include <string>
#include <functional>

#include <MapBuilderCore.h>

struct ModuleInfo
{
  std::string name;
  mbc::PipelineStage stage;
  std::function<mbc::ModulePtr(void)> constructor;
};
