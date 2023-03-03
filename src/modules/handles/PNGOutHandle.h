#pragma once
#include <memory>
#include <string>

#include <imgui.h>
#include <MapBuilderCore\modules\PNGOut.h>

#include "modules\ModuleHandle.h"
#include "util\FileDialogHelpers.h"

class PNGOutHandle : public ModuleHandle
{
public:
  PNGOutHandle();
  PNGOutHandle(mbc::Module::Ptr);

  bool showHandle(int, bool&) override;

  template <typename Archive>
  void serialize(Archive& archive) {};

private:
  char*& outputFilepath_;
};


CEREAL_REGISTER_TYPE(PNGOutHandle);
CEREAL_REGISTER_POLYMORPHIC_RELATION(ModuleHandle, PNGOutHandle);
