#pragma once
#include <memory>
#include <string>

#include <imgui.h>

#include "modules\ModuleHandle.h"
#include "modules\ModuleWrapper.h"
#include "util\FileDialogHelpers.h"

class BMP8OutHandle : public ModuleHandle
{
public:
  BMP8OutHandle(ModuleWrapper::Ptr);

  bool showHandle(int, bool&) override;

private:
  char*& outputFilepath_;
};


