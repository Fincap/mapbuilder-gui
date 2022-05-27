#pragma once
#include <vector>

#include <imgui.h>
#include <core\StageMap.h>

#include "modules\ModuleWrapper.h"
#include "util\APIHelpers.h"

/*
Displays a view of all Modules in the application's pipeline. For each module
provided, the window will display collapsible sections for each pipeline stage
where each module can be re-ordered and their parameters modified. The
implementation of this UI is offloaded to each derived class of ModuleHandle.
*/
class PipelineView
{
public:
  bool showWindow(mbc::StageMap<ModuleWrapper::Ptr>&);

};

