#include "PipelineView.h"

void PipelineView::showWindow(std::vector<ModuleWrapper>& modules)
{
  ImGui::Begin("Pipeline");

  for (auto mod = modules.begin(); mod != modules.end();)
  {
    if (mod->handle->showHandle())
      mod++;
    else
      // Delete module if handle returns false (no longer alive).
      mod = modules.erase(mod);
  }

  ImGui::End();
}