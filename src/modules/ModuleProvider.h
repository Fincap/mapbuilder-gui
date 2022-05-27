#pragma once
#include <unordered_map>
#include <string>
#include <core\Module.h>

#include "modules\ModuleInfo.h"
#include "modules\ModuleHandle.h"
#include "modules\handles\AllHandles.h"
#include "util\ModuleInfoHelpers.h"

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

  /* Instantiate a new ModuleHandle to the given Module pointer. */
  ModuleHandle::Ptr getNewHandle(const mbc::Module::Ptr&);

private:
  ModuleProvider();   // Private constructor

  void loadCoreModules();     // Load Modules defined by mapbuilder-core.
  void loadAddonModules();    // Load Modules defined by user add-on.

  std::map<std::string, ModuleInfo> loadedModules_;

};
