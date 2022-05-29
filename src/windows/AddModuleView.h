#pragma once
#include <functional>
#include <vector>
#include <iostream>
#include <string>

#include <imgui.h>
#include <MapBuilderCore\StageMap.h>
#include <MapBuilderCore\PipelineStage.h>

#include "util\APIHelpers.h"
#include "util\ModuleHelpers.h"
#include "modules\ModuleInfo.h"
#include "modules\ModuleWrapper.h"
#include "modules\ModuleProvider.h"
#include "modules\handles\AllHandles.h"

/*
This window provides a view of all modules that can be added to the Pipeline
grouped by their Pipeline Stages, and provides a small description of each.
The class will load in all the core Modules manually, and in future should have
the ability to load Modules dynamically created through add-ons.
*/
class AddModuleView
{
public:
  AddModuleView();
  ~AddModuleView();

  bool showWindow(mbc::StageMap<ModuleWrapper::Ptr>&);   // Display ImGui window.

private:
  bool displayModuleInfo(std::vector<ModuleWrapper::Ptr>&, ModuleInfo::Ptr, int&);

  // Loaded-in Modules grouped by Pipeline stage.
  std::vector<ModuleInfo::Ptr>* loadedModules_;

};

