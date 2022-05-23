#include "ElevationSlopeHandle.h"

ElevationSlopeHandle::ElevationSlopeHandle(ModuleWrapper::Ptr wrapper) :
  slope_(std::ref(std::dynamic_pointer_cast<mbc::ElevationSlope>(wrapper->module)->slope))
{}


bool ElevationSlopeHandle::showHandle(int pipelineNum)
{
  auto label = std::to_string(pipelineNum) + ": Elevation Slope";

  ImGui::PushID(pipelineNum);
  ImGui::AlignTextToFramePadding();
  if (ImGui::TreeNodeEx(label.c_str(), ImGuiTreeNodeFlags_DefaultOpen))
  {
    showDeleteButton();

    // Processing params
    const double min = 0.1;
    const double max = 4.0;

    ImGui::SliderScalar("Slope", ImGuiDataType_Double, &slope_, &min, &max, "%.1f");

    ImGui::TreePop();
  }
  else
  {
    showDeleteButton();
  }

  ImGui::Separator();
  ImGui::PopID();

  return alive_;
}
