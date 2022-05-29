#pragma once
#include <memory>

#include "modules\ModuleInfo.h"
#include "modules\ModuleWrapper.h"

namespace util
{
  /* Helper function to generate a ModuleWrapper for the given ModuleInfo. */
  inline ModuleWrapper::Ptr wrapModuleInfo(ModuleInfo::Ptr info)
  {
    auto wrapper = std::make_shared<ModuleWrapper>();
    wrapper->module = info->createModule();
    wrapper->handle = info->getHandleToModule(wrapper->module);
    return wrapper;
  }
}