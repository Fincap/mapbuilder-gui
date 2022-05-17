#pragma once
#include <string>
#include <functional>

#include <MapBuilderCore.h>

#include "wrappers\ModuleWrapper.h"

/*
This structure contains information about Modules, and function references to
enable the instantiation of relevent ModuleWrapper objects.
*/
struct ModuleInfo
{
  // Convenience typing for a function that returns a pointer to a Module.
  using fn_CreateModuleWrapper = std::function<ModuleWrapper>;

  std::string name;               // Module name.
  std::string description;        // Short description of module.
  mbc::PipelineStage stage;       // Module's PipelineStage.
  fn_CreateModuleWrapper create;  // Function to create Module Wrapper.

};