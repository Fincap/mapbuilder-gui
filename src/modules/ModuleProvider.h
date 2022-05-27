#pragma once
#include <unordered_map>
#include <string>
#include <core\Module.h>

#include "modules\ModuleInfo.h"
#include "modules\ModuleHandle.h"

class ModuleProvider
{
public:
  // Delete copy/move constructors
  ModuleProvider(const ModuleProvider&)             = delete;
  ModuleProvider& operator=(const ModuleProvider&)  = delete;
  ModuleProvider(ModuleProvider&&)                  = delete;
  ModuleProvider& operator=(ModuleProvider&&)       = delete;

  // Get Singleton instance
  static auto& instance()
  {
    static ModuleProvider moduleProvider;
    return moduleProvider;
  }

  ModuleHandle::Ptr getNewHandle(mbc::Module::Ptr);

private:
  ModuleProvider();   // Private constructor

  void loadCoreModules();     // Load Modules defined by mapbuilder-core.
  void loadAddonModules();    // Load Modules defined by user add-on.

  std::map<std::string, ModuleInfo> loadedModules_;

};
