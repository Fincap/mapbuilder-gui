#pragma once
#include <memory>
#include <string>

#include <imgui.h>

#include "modules\ModuleHandle.h"
#include "modules\ModuleWrapper.h"

class CanvasHandle : public ModuleHandle
{
public:
  CanvasHandle();
  CanvasHandle(mbc::Module::Ptr);

  bool showHandle(int, bool&) override;

  template <typename Archive>
  void serialize(Archive& archive) {};

private:
  int& width_;
  int& height_;
};


CEREAL_REGISTER_TYPE(CanvasHandle);
CEREAL_REGISTER_POLYMORPHIC_RELATION(ModuleHandle, CanvasHandle);
