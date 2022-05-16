#pragma once
#include <vector>

#include <MapBuilderCore.h>

#include "app\ModuleInfo.h"

class ModuleProvider
{
public:
  ModuleProvider();

  std::vector<ModuleInfo> getModules();
  ModuleInfo getModuleInfo(const std::string&);

private:
  std::vector<ModuleInfo> _registeredModules;

  void loadCoreModules();

  // To be implemented
  void loadAddonModules();

};