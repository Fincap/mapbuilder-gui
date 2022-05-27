#pragma once

#include <MapBuilderCore.h>

#include "modules\ModuleInfo.h"


/*
Templated ModuleInfo struct used for manual registration of ModuleInfo.
Type M is a derived class of mbc::Module.
Type H is a derived class of ModuleHandle.
*/
template <typename M, typename H>
struct ManualInfo : public ModuleInfo
{
  ManualInfo(const char* _name, const char* _description, mbc::PipelineStage _stage)
  {
    name = _name;
    description = _description;
    stage = _stage;
  }

  ModuleWrapper::Ptr create()
  {
    auto wrapper = std::make_shared<ModuleWrapper>();
    wrapper->module = std::make_shared<M>();;
    wrapper->handle = std::make_shared<H>(wrapper->module);
    std::clog << name << " module address: " << &wrapper->module << std::endl;
    std::clog << name << " handle address: " << &wrapper->handle << std::endl;
    std::clog << "Finished adding " << name << std::endl;
    return wrapper;
  }

  ModuleHandle::Ptr getHandleToModule(mbc::Module::Ptr mod)
  {
    return std::make_shared<H>(mod);
  }
};