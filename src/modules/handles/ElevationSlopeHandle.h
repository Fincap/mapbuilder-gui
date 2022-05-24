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

private:
  double& slope_;
};


