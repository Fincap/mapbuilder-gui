#pragma once
#include <memory>
#include <string>

#include <imgui.h>

#include "modules\ModuleHandle.h"
#include "modules\ModuleWrapper.h"
#include "util\FileDialogHelpers.h"

class BMP8OutHandle : public ModuleHandle
{
public:
  BMP8OutHandle();
  BMP8OutHandle(ModuleWrapper::Ptr);

  bool showHandle(int, bool&) override;

  template <typename Archive>
  void serialize(Archive& archive) {};

private:
  char*& outputFilepath_;
};


CEREAL_REGISTER_TYPE(BMP8OutHandle);
CEREAL_REGISTER_POLYMORPHIC_RELATION(ModuleHandle, BMP8OutHandle);
