#pragma once
#include <vector>
#include <filesystem>

#include <MapBuilderCore\Pipeline.h>

#include "modules\ModuleWrapper.h"

struct ApplicationContext
{
  mbc::Pipeline pipeline;
  mbc::StageMap<ModuleWrapper::Ptr> modules;
  std::filesystem::path filename;
  bool isUnsaved = false;
  float previewZoom = 1.f;

#ifdef _DEBUG
  // Demo window toggle if compiled in Debug mode.
  bool showDemoWindow_ = false;
  bool showMetricsWindow_ = false;
#endif
};
