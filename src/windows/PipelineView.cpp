#include "PipelineView.h"

void PipelineView::showWindow(std::vector<ModuleWrapper::Ptr>* modules)
{
  // TODO Add drag-and-drop reordering of Modules (ideally within their
  // respective Pipeline Stages).
  // Refer to lines 2319 through 2343 in imgui_demo.cpp
  ImGui::Begin("Pipeline");

  ImGui::PushItemWidth(100);
  int count = 1;
  for (int i = 0; i < MBC_NUM_STAGES; i++)
  {
    if (ImGui::CollapsingHeader(pipelineStageToStringExtended((mbc::PipelineStage)i)))
    {
      for (auto mod = modules[i].begin(); mod != modules[i].end();)
      {
        if ((*mod)->handle->showHandle(count))
          mod++;
        else
          // Delete module if handle returns false (no longer alive).
          mod = modules[i].erase(mod);

        count++;
      }
    }
  }
  ImGui::PopItemWidth();

  ImGui::End();
}