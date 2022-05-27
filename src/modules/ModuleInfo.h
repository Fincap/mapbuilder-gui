#pragma once
#include <string>
#include <memory>

#include <MapBuilderCore\PipelineStage.h>

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

  /* Returns a pointer to a new ModuleWrapper for the relevant Module. This
  must be implemented by the derived class. */
  virtual ModuleWrapper::Ptr createModule() = 0;

  /* Returns a pointer to a new ModuleHandle for the relevent module. This is
  useful for when a new ModueHandle needs to be instantiated separately to its
  related Module. This must be implemented by the derived class. */
  virtual ModuleHandle::Ptr getHandleToModule(mbc::Module::Ptr) = 0;

  // Convenience typing
  using Ptr = std::shared_ptr<ModuleInfo>;

};