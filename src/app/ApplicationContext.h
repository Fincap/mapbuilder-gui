#pragma once
#include <vector>
#include <filesystem>

#include <MapBuilderCore.h>

#include "modules\ModuleWrapper.h"

struct ApplicationContext
{
  mbc::Pipeline pipeline;
  mbc::StageMap<ModuleWrapper::Ptr> modules;
  std::filesystem::path filename;
  bool isUnsaved = false;

#ifdef _DEBUG
  // Demo window toggle if compiled in Debug mode.
  bool showDemoWindow_ = false;
#endif
};
