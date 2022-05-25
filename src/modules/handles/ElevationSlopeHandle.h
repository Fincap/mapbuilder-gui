#pragma once
#include <memory>
#include <string>

#include <imgui.h>

#include "modules\ModuleHandle.h"
#include "modules\ModuleWrapper.h"

class ElevationSlopeHandle : public ModuleHandle
{
public:
  ElevationSlopeHandle();
  ElevationSlopeHandle(mbc::Module::Ptr);

  bool showHandle(int, bool&) override;

  template <typename Archive>
  void serialize(Archive& archive) {};

private:
  double& slope_;
};


CEREAL_REGISTER_TYPE(ElevationSlopeHandle);
CEREAL_REGISTER_POLYMORPHIC_RELATION(ModuleHandle, ElevationSlopeHandle);
