#include "CanvasHandle.h"

CanvasHandle::CanvasHandle(ModuleWrapper::Ptr wrapper) :
  width_(std::ref(std::dynamic_pointer_cast<mbc::Canvas>(wrapper->module)->width)),
  height_(std::ref(std::dynamic_pointer_cast<mbc::Canvas>(wrapper->module)->height))
{}


bool CanvasHandle::showHandle(int pipelineNum)
{
  auto label = std::to_string(pipelineNum) + " Canvas";

  ImGui::PushID(pipelineNum);
  if (ImGui::CollapsingHeader(label.c_str(), &alive_, ImGuiTreeNodeFlags_DefaultOpen))
  {
    // Processing params
    ImGui::DragInt("Width", &width_, 1, 2, 2048, "%d", ImGuiSliderFlags_AlwaysClamp);
    ImGui::DragInt("Height", &height_, 1, 2, 2048, "%d", ImGuiSliderFlags_AlwaysClamp);
  }
  ImGui::PopID();

  return alive_;
}
