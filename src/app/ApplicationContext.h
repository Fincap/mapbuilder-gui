#pragma once
#include <vector>

#include <MapBuilderCore.h>

struct ApplicationContext
{
  mbc::Pipeline pipeline;
  std::vector<mbc::ModulePtr> modules;
};