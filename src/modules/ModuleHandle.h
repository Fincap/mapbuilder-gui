#pragma once
#include <memory>

/*
Interface for displaying module handles. Derived classes are responsible for
constructing and maintaining the references to the wrapped module, as well as
constructing a valid UI based on CollapsingHeader sections.
*/
class ModuleHandle
{
public:
  using Ptr = std::shared_ptr<ModuleHandle>;

  // Return Handle's alive status. If false, then Wrapper should delete.
  // int parameter is a number representing the order which the related
  // Module is executed in the Pipeline.
  virtual bool showHandle(int) = 0;  // Must be implemented by derived.

protected:
  bool alive_;    // Determines if the Module should be deleted.

  virtual void showDeleteButton() final;    // Displays a delete button for the tree node.
};


inline void ModuleHandle::showDeleteButton()
{
  // Delete button
  ImGui::SameLine(ImGui::GetWindowContentRegionWidth() - 10);
  ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(7.0f, 0.6f, 0.6f));
  ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(7.0f, 0.7f, 0.7f));
  ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(7.0f, 0.8f, 0.8f));
  if (ImGui::Button("X"))
    alive_ = false;
  ImGui::PopStyleColor(3);
}