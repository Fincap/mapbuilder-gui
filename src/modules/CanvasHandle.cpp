#include "CanvasHandle.h"

CanvasHandle::CanvasHandle(ModuleWrapper::Ptr wrapper) :
  _width(std::ref(std::dynamic_pointer_cast<mbc::Canvas>(wrapper->module)->width)),
  _height(std::ref(std::dynamic_pointer_cast<mbc::Canvas>(wrapper->module)->height))
{}


bool CanvasHandle::showHandle()
{
  if (ImGui::CollapsingHeader("Canvas", &_alive))
  {
    // Processing params
    ImGui::DragInt("Width", &_width, 1, 2, 2048, "%d", ImGuiSliderFlags_AlwaysClamp);
    ImGui::DragInt("Height", &_height, 1, 2, 2048, "%d", ImGuiSliderFlags_AlwaysClamp);
  }

  return _alive;
}
