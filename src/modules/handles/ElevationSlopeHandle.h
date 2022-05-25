#pragma once
#include <memory>
#include <string>

#include <imgui.h>

#include "modules\ModuleHandle.h"
#include "modules\ModuleWrapper.h"

class ElevationSlopeHandle : public ModuleHandle
{
public:
  ElevationSlopeHandle(ModuleWrapper::Ptr);

  bool showHandle(int, bool&) override;

  template <typename Archive>
  void serialize(Archive& archive) {};

  template <class Archive>
  static void load_and_construct(Archive& ar, cereal::construct<ElevationSlopeHandle>& construct)
  {
    ModuleWrapper::Ptr x;
    ar(x);
    construct(x);
  }

private:
  double& slope_;
};


CEREAL_REGISTER_TYPE(ElevationSlopeHandle);
CEREAL_REGISTER_POLYMORPHIC_RELATION(ModuleHandle, ElevationSlopeHandle);
