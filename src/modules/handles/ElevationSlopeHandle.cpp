#include "ElevationSlopeHandle.h"

ElevationSlopeHandle::ElevationSlopeHandle() :
  slope_(std::ref(std::make_shared<mbc::ElevationSlope>()->slope))
{}


ElevationSlopeHandle::ElevationSlopeHandle(mbc::Module::Ptr mod) :
  slope_(std::ref(std::dynamic_pointer_cast<mbc::ElevationSlope>(mod)->slope))
{}


bool ElevationSlopeHandle::showHandle(int pipelineNum, bool& changed)
{
  // Set previous values
  auto oldSlope = slope_;

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

  // Update changed flag if any values have changes
  changed = (
    slope_ != oldSlope ||
    !alive_
  );

  return alive_;
}


void ElevationSlopeHandle::pointAt(mbc::Module::Ptr mod)
{
  slope_ = std::ref(std::dynamic_pointer_cast<mbc::ElevationSlope>(mod)->slope);
}
