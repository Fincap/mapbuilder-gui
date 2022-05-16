#pragma once
#include <vector>

#include <MapBuilderCore.h>

/*
ModuleWrapper points to a Module instance, and contains a list of references
to the Module's processing parameters. It is up to the owner of the wrapper
to correctly construct the references in params, as well as cast them to
their correct types.
*/
struct ModuleWrapper
{
  mbc::ModulePtr module;
  std::vector<std::reference_wrapper<std::any>> params;
};

