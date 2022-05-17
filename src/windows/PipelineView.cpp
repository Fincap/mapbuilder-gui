#include "PipelineView.h"

void PipelineView::showWindow(std::vector<ModuleWrapper>& modules)
{
  ImGui::Begin("Pipeline");

  for (auto mod = modules.begin(); mod != modules.end();)
  {
    if (mod->handle->showHandle())
      mod = modules.erase(mod);   // Delete module if handle returns true.
    else
      mod++;
  }

  ImGui::End();
}