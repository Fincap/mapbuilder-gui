#pragma once
#include <vector>

#include <imgui.h>
#include <MapBuilderCore.h>

#include "modules\ModuleInfo.h"
#include "wrappers\ModuleWrapper.h"

/*
This window provides a view of all modules that can be added to the Pipeline
grouped by their Pipeline Stages, and provides a small description of each.
The class will load in all the core Modules manually, and in future should have
the ability to load Modules dynamically created through add-ons.
*/
class AddModuleView
{
  // Convenience typing for a function that adds a new ModuleWrapper to the
  // Application's context.
  using fn_AddModuleWrapperToContext = std::function<void(ModuleWrapper)>;

public:
  AddModuleView(fn_AddModuleWrapperToContext);

  void showWindow();          // Display ImGui window.

private:
  void loadCoreModules();     // Load Modules defined by mapbuilder-core.
  void loadAddonModules();    // Load Modules defined by user add-on.

  std::vector<ModuleInfo> _modules;   // Loaded-in Modules.

  // Function to be called when a new Module is to be added to the Application
  // context.
  // This function should be provided by the calling Application.
  fn_AddModuleWrapperToContext _addModuleWrapperToContext;

};

