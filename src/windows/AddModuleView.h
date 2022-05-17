#pragma once
#include <vector>

#include <imgui.h>
#include <MapBuilderCore.h>

#include "wrappers/ModuleWrapper.h"

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

private:
  void loadCoreModules();
  void loadAddonModules();

};

