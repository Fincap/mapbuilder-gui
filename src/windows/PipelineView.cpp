#include "PipelineView.h"

void PipelineView::showWindow(mbc::StageMap<ModuleWrapper::Ptr>& modules)
{
  // TODO Add drag-and-drop reordering of Modules (ideally within their
  // respective Pipeline Stages).
  // Refer to lines 2319 through 2343 in imgui_demo.cpp
  ImGui::Begin("Pipeline");

  ImGui::PushItemWidth(100);
  int count = 1;

  for (int i = 0; i < MBC_NUM_STAGES; i++)
  {
    if (modules.getAll(i).size() == 0) continue;   // Don't show stages with no modules.
    if (ImGui::CollapsingHeader(pipelineStageToStringExtended((mbc::PipelineStage)i)))
    {
      for (auto mod = modules.getAll(i).begin(); mod != modules.getAll(i).end();)
      {
        if ((*mod)->handle->showHandle(count))
          mod++;
        else
          // Delete module if handle returns false (no longer alive).
          mod = modules.getAll(i).erase(mod);

        count++;
      }
    }
  }
  ImGui::PopItemWidth();

  ImGui::End();
}