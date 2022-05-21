#pragma once
#include <vector>

#include <MapBuilderCore.h>

#include "modules\ModuleHandle.h"

/*
ModuleWrapper is a handle to a Module and ModuleHandle window, both of
which are instantiated by the AddModule window. The ModuleHandle class is
responsible for ensuring that all references to the Module are casted
and updated correctly.
*/
struct ModuleWrapper
{
  mbc::Module::Ptr module;
  ModuleHandle::Ptr handle;

  using Ptr = std::shared_ptr<ModuleWrapper>;
};
