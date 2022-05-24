#pragma once
#include <memory>
#include <string>

#include <imgui.h>

#include "modules\ModuleHandle.h"
#include "modules\ModuleWrapper.h"

class CanvasHandle : public ModuleHandle
{
public:
  CanvasHandle(ModuleWrapper::Ptr);

  bool showHandle(int, bool&) override;

private:
  int& width_;
  int& height_;
};


