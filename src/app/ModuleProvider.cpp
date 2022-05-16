#include "ModuleProvider.h"

ModuleProvider::ModuleProvider()
{
  loadCoreModules();
  loadAddonModules();
}


std::vector<ModuleInfo> ModuleProvider::getModules()
{
  return _registeredModules;
}


ModuleInfo ModuleProvider::getModuleInfo(const std::string& moduleName)
{
  for (auto mod : _registeredModules)
  {
    if (mod.name == moduleName)
      return mod;
  }
}


void ModuleProvider::loadCoreModules()
{
  // SRUB
}


void ModuleProvider::loadAddonModules()
{
  // STUB
}
