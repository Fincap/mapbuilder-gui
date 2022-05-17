#include "PipelineView.h"

void PipelineView::showWindow(std::vector<ModuleWrapper> modules)
{
  ImGui::Begin("Pipeline");

  for (auto& mod : modules)
  {
    mod.handle->showHandle();
  }

  ImGui::End();
}