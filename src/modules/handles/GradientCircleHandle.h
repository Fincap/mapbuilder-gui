#pragma once
#include <memory>
#include <string>

#include <imgui.h>
#include <MapBuilderCore\modules\GradientCircle.h>

#include "modules\ModuleHandle.h"

class GradientCircleHandle : public ModuleHandle
{
public:
  GradientCircleHandle();
  GradientCircleHandle(mbc::Module::Ptr);

  bool showHandle(int, bool&) override;

  template <typename Archive>
  void serialize(Archive& archive) {};

private:
  double& fullness_;
  double& size_;
};


CEREAL_REGISTER_TYPE(GradientCircleHandle);
CEREAL_REGISTER_POLYMORPHIC_RELATION(ModuleHandle, GradientCircleHandle);
