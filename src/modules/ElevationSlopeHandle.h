#pragma once
#include <memory>
#include <string>

#include <imgui.h>

#include "modules\ModuleHandle.h"
#include "wrappers\ModuleWrapper.h"

class ElevationSlopeHandle : public ModuleHandle
{
public:
  ElevationSlopeHandle(ModuleWrapper::Ptr);

  bool showHandle(int);

private:
  double& slope_;
};


