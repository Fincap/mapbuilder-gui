#pragma once
#include <vector>

#include <imgui.h>

#include "wrappers\ModuleWrapper.h"

/*
Displays a view of all Modules in the application's pipeline. For each module
provided, the window will display collapsible sections for each pipeline stage
where each module can be re-ordered and their parameters modified. The
implementation of this UI is offloaded to each derived class of ModuleHandle.
*/
class PipelineView
{
public:
  void showWindow(std::vector<ModuleWrapper>);

};

