#pragma once

#include <imgui.h>

#include "wrappers\ModuleWrapper.h"

/*
The base class for UI components displayed in the PipelineView, containing
a ModuleWrapper and module display definition. Derived classes are responsible
for constructing and maintaining the references in the ModuleWrapper member,
as well as constructing a valid UI.
*/
class ModuleHandle
{
public:
  virtual void showHandle() = 0;  // Must be implemented by derived.

private:
  ModuleWrapper _wrapper;
};
