#pragma once
#include <string>

#include <MapBuilderCore.h>

#include "wrappers\ModuleWrapper.h"

/*
This structure contains information about Modules, and function references to
enable the instantiation of relevent ModuleWrapper objects.
*/
struct ModuleInfo
{
  // Convenience typing for a function that returns a pointer to a Module.
  using fn_CreateModuleWrapper = ModuleWrapper (*)();

  const char* name;               // Module name.
  const char* description;        // Short description of module.
  mbc::PipelineStage stage;       // Module's PipelineStage.
  fn_CreateModuleWrapper create;  // Function to create Module Wrapper.

};