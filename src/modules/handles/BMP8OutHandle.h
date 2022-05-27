#pragma once
#include <memory>
#include <string>

#include <imgui.h>
#include <MapBuilderCore\modules\BMP8Out.h>

#include "modules\ModuleHandle.h"
#include "util\FileDialogHelpers.h"

class BMP8OutHandle : public ModuleHandle
{
public:
  BMP8OutHandle();
  BMP8OutHandle(mbc::Module::Ptr);

  bool showHandle(int, bool&) override;

  void pointAt(mbc::Module::Ptr) override;

  template <typename Archive>
  void serialize(Archive& archive) {};

private:
  char*& outputFilepath_;
};


CEREAL_REGISTER_TYPE(BMP8OutHandle);
CEREAL_REGISTER_POLYMORPHIC_RELATION(ModuleHandle, BMP8OutHandle);
