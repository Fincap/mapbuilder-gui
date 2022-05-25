#pragma once
#include <vector>
#include <typeindex>

#include <cereal\cereal.hpp>
#include <cereal\archives\xml.hpp>
#include <cereal\types\memory.hpp>
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

  template <typename Archive>
  void save(Archive& archive) const;

  template <typename Archive>
  void load(Archive& archive);
};


template <typename Archive>
inline void ModuleWrapper::save(Archive& archive) const
{
  archive(module, handle);
}


template <typename Archive>
inline void ModuleWrapper::load(Archive& archive)
{
  archive(module, handle);

  auto type = std::type_index(typeid(module));
  std::cout << type.name() << " " << type.hash_code() << std::endl;

  handle->pointAt(module);

}
