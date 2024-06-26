#pragma once
#include <memory>
#include <string>

#include <imgui.h>
#include <MapBuilderCore\modules\HeightmapOut.h>

#include "modules\ModuleHandle.h"
#include "util\FileDialogHelpers.h"

class HeightmapOutHandle : public ModuleHandle
{
public:
  HeightmapOutHandle();
  HeightmapOutHandle(mbc::Module::Ptr);

  bool showHandle(int, bool&) override;

  template <typename Archive>
  void serialize(Archive& archive) {};

private:
  char*& outputFilepath_;
};


CEREAL_REGISTER_TYPE(HeightmapOutHandle);
CEREAL_REGISTER_POLYMORPHIC_RELATION(ModuleHandle, HeightmapOutHandle);
