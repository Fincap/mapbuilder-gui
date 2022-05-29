#pragma once
#include <memory>

#include <MapBuilderCore\Module.h>
#include <MapBuilderCore\PipelineStage.h>

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

  mbc::Module::Ptr createModule()
  {
    return std::make_shared<M>();
  }

  ModuleHandle::Ptr getHandleToModule(mbc::Module::Ptr mod)
  {
    return std::make_shared<H>(mod);
  }
};