#include "Application.h"

void Application::showWindow()
{
  _showPlaceholderModal = false;

  showMainMenuBar();

  // Show placeholder if necessary
  if (_showPlaceholderModal)
    ImGui::OpenPopup("Placeholder");

  showPlaceholderModal();

}


void Application::showPlaceholderModal()
{
  if (ImGui::BeginPopupModal("Placeholder", NULL, ImGuiWindowFlags_AlwaysAutoResize))
  {
    ImGui::Text("Functionality to be implemented.\n\n");
    ImGui::Separator();

    if (ImGui::Button("OK", ImVec2(120, 0))) { ImGui::CloseCurrentPopup(); }
    ImGui::SetItemDefaultFocus();
    ImGui::EndPopup();
  }
}


void Application::showMainMenuBar()
{
  if (ImGui::BeginMainMenuBar())
  {
    if (ImGui::BeginMenu("File"))
    {
      if (ImGui::MenuItem("New", "CTRL+N")) { _showPlaceholderModal = true; }
      if (ImGui::MenuItem("Open", "CTRL+O")) { _showPlaceholderModal = true; }
      if (ImGui::MenuItem("Save", "CTRL+S")) { _showPlaceholderModal = true; }
      if (ImGui::MenuItem("Save As", "F12")) { _showPlaceholderModal = true; }
      ImGui::EndMenu();
    }
    if (ImGui::BeginMenu("Help"))
    {
      if (ImGui::MenuItem("About MapBuilder")) { _showPlaceholderModal = true; }
      ImGui::EndMenu();
    }
    ImGui::EndMainMenuBar();
  }
}