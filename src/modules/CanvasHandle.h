#pragma once
#include <memory>
#include <string>

#include <imgui.h>

#include "modules\ModuleHandle.h"
#include "wrappers\ModuleWrapper.h"

class CanvasHandle : public ModuleHandle
{
public:
  CanvasHandle(ModuleWrapper::Ptr);

  bool showHandle(int);

private:
  int& _width;
  int& _height;
};


