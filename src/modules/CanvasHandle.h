#pragma once
#include <memory>

#include <imgui.h>

#include "modules\ModuleHandle.h"
#include "wrappers\ModuleWrapper.h"

class CanvasHandle : public ModuleHandle
{
public:
  CanvasHandle(ModuleWrapper);

  bool showHandle();

private:
  int& _width;
  int& _height;
};


