#include "CanvasHandle.h"

CanvasHandle::CanvasHandle(ModuleWrapper::Ptr wrapper) :
  width_(std::ref(std::dynamic_pointer_cast<mbc::Canvas>(wrapper->module)->width)),
  height_(std::ref(std::dynamic_pointer_cast<mbc::Canvas>(wrapper->module)->height))
{}


bool CanvasHandle::showHandle(int pipelineNum)
{
  auto label = std::to_string(pipelineNum) + ": Canvas";

  ImGui::PushID(pipelineNum);
  // This particular module isn't attached to alive flag because it should not
  // be deletable.
  ImGui::AlignTextToFramePadding();
  if (ImGui::TreeNodeEx(label.c_str(), ImGuiTreeNodeFlags_DefaultOpen))
  {
    // Processing params
    ImGui::DragInt("Width", &width_, 1, 2, 2048, "%d", ImGuiSliderFlags_AlwaysClamp);
    ImGui::DragInt("Height", &height_, 1, 2, 2048, "%d", ImGuiSliderFlags_AlwaysClamp);

    ImGui::TreePop();
  }
  ImGui::Separator();
  ImGui::PopID();

  return alive_;
}
