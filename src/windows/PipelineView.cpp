#include "PipelineView.h"

void PipelineView::showWindow(std::vector<ModuleWrapper::Ptr>& modules)
{
  // TODO Add drag-and-drop reordering of Modules (ideally within their
  // respective Pipeline Stages).
  // Refer to lines 2319 through 2343 in imgui_demo.cpp
  ImGui::Begin("Pipeline");

  for (auto mod = modules.begin(); mod != modules.end();)
  {
    if (mod->get()->handle->showHandle())
      mod++;
    else
      // Delete module if handle returns false (no longer alive).
      mod = modules.erase(mod);
  }

  ImGui::End();
}