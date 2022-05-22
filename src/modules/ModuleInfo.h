#pragma once
#include <string>

#include <MapBuilderCore.h>

#include "modules\ModuleWrapper.h"

/*
This structure contains information about Modules, and a virtual create
function to instantiate the relevent ModuleWrapper, to be implemented by the
derived class. Intended to be inherited by classes defined inline the Add
Module View.
*/
struct ModuleInfo
{
  const char* name;               // Module name.
  const char* description;        // Short description of module.
  mbc::PipelineStage stage;       // Module's PipelineStage.

  // Returns a pointer to a new ModuleWrapper for the relevant Module. This
  // must be implemented by the derived class.
  virtual ModuleWrapper::Ptr create() = 0;

};