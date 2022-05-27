#pragma once
#include <unordered_map>
#include <string>
#include <vector>
#include <exception>

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

  /* Get a pointer to the ModuleInfo for the given Module as per its name. */
  ModuleInfo::Ptr getInfo(const std::string&);

  /* Get a list of all ModuleInfo instances stored in the map. */
  std::vector<ModuleInfo::Ptr> getInfoAll();

private:
  ModuleProvider();   // Private constructor

  void loadCoreModules();     // Load Modules defined by mapbuilder-core.
  void loadAddonModules();    // Load Modules defined by user add-on.

  /* Map of Module name (from the Module's class definition) to instance of
  ModuleInfo class.*/
  std::map<std::string, ModuleInfo::Ptr> loadedModules_;

};
