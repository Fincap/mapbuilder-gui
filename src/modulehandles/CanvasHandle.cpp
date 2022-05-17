#include "CanvasHandle.h"

CanvasHandle::CanvasHandle(ModuleWrapper wrapper) :
  _width(std::ref(std::dynamic_pointer_cast<mbc::Canvas>(wrapper.module)->width)),
  _height(std::ref(std::dynamic_pointer_cast<mbc::Canvas>(wrapper.module)->height))
{}


void CanvasHandle::showHandle()
{
  if (ImGui::CollapsingHeader("Canvas"))
  {
    ImGui::DragInt("Width", &_width, 1, 2, 2048, "%d", ImGuiSliderFlags_AlwaysClamp);
    ImGui::DragInt("Height", &_height, 1, 2, 2048, "%d", ImGuiSliderFlags_AlwaysClamp);
  }
}