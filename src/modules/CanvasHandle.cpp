#include "CanvasHandle.h"

CanvasHandle::CanvasHandle(ModuleWrapper::Ptr wrapper) :
  _width(std::ref(std::dynamic_pointer_cast<mbc::Canvas>(wrapper->module)->width)),
  _height(std::ref(std::dynamic_pointer_cast<mbc::Canvas>(wrapper->module)->height))
{}


bool CanvasHandle::showHandle(int pipelineNum)
{
  auto label = std::to_string(pipelineNum) + " Canvas";

  ImGui::PushID(pipelineNum);
  if (ImGui::CollapsingHeader(label.c_str(), &_alive))
  {
    // Processing params
    ImGui::DragInt("Width", &_width, 1, 2, 2048, "%d", ImGuiSliderFlags_AlwaysClamp);
    ImGui::DragInt("Height", &_height, 1, 2, 2048, "%d", ImGuiSliderFlags_AlwaysClamp);
  }
  ImGui::PopID();

  return _alive;
}
