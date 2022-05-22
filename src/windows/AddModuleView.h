#pragma once
#include <functional>
#include <vector>
#include <iostream>
#include <string>

#include <imgui.h>
#include <MapBuilderCore.h>

#include "util\APIHelpers.h"
#include "util\ModuleInfoHelpers.h"
#include "modules\ModuleInfo.h"
#include "wrappers\ModuleWrapper.h"
#include "modules\CanvasHandle.h"
#include "modules\PerlinGenHandle.h"
#include "modules\ElevationSlopeHandle.h"
#include "modules\BMP8OutHandle.h"

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

  void showWindow(std::vector<ModuleWrapper::Ptr>&);   // Display ImGui window.

private:
  void loadCoreModules();     // Load Modules defined by mapbuilder-core.
  void loadAddonModules();    // Load Modules defined by user add-on.

  std::vector<ModuleInfo*> loadedModules_;   // Loaded-in Modules.

};

