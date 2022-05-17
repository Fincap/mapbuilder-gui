#include "CanvasHandle.h"

CanvasHandle::CanvasHandle(ModuleWrapper wrapper) :
  _width(std::ref(std::dynamic_pointer_cast<mbc::Canvas>(wrapper.module)->width)),
  _height(std::ref(std::dynamic_pointer_cast<mbc::Canvas>(wrapper.module)->height))
{}


bool CanvasHandle::showHandle()
{
  bool willDelete = false;

  if (ImGui::CollapsingHeader("Canvas"))
  {
    // Delete button
    ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(0.0f, 0.6f, 0.6f));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(0.0f, 0.7f, 0.7f));
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(0.0f, 0.8f, 0.8f));
    if (ImGui::Button("X")) willDelete = true;
    ImGui::PopStyleColor(3);

    // Processing params
    ImGui::DragInt("Width", &_width, 1, 2, 2048, "%d", ImGuiSliderFlags_AlwaysClamp);
    ImGui::DragInt("Height", &_height, 1, 2, 2048, "%d", ImGuiSliderFlags_AlwaysClamp);
  }

  return willDelete;
}
