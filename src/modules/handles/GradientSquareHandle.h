#pragma once
#include <memory>
#include <string>

#include <imgui.h>
#include <MapBuilderCore\modules\GradientSquare.h>

#include "modules\ModuleHandle.h"

class GradientSquareHandle : public ModuleHandle
{
public:
  GradientSquareHandle();
  GradientSquareHandle(mbc::Module::Ptr);

  bool showHandle(int, bool&) override;

  template <typename Archive>
  void serialize(Archive& archive) {};

private:
  double& fullness_;
  double& size_;
};


CEREAL_REGISTER_TYPE(GradientSquareHandle);
CEREAL_REGISTER_POLYMORPHIC_RELATION(ModuleHandle, GradientSquareHandle);
