#include "Application.h"

void Application::showWindow()
{
  _showPlaceholderModal = false;

  showMainMenuBar();
  outputConsole.showWindow();

#ifdef _DEBUG // Show demo window in Debug build
  if (_showDemoWindow)
    ImGui::ShowDemoWindow(&_showDemoWindow);
#endif

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
      if (ImGui::MenuItem("New", "CTRL+N")) { _showPlaceholderModal = true; std::cout << "New!" << std::endl; }
      if (ImGui::MenuItem("Open", "CTRL+O")) { _showPlaceholderModal = true; std::clog << "Open!" << std::endl; }
      if (ImGui::MenuItem("Save", "CTRL+S")) { _showPlaceholderModal = true; std::cerr << "Save!" << std::endl; }
      if (ImGui::MenuItem("Save As", "F12")) { _showPlaceholderModal = true; std::cout << "Save As!" << std::endl; }
      ImGui::EndMenu();
    }
    if (ImGui::BeginMenu("Help"))
    {
      if (ImGui::MenuItem("About MapBuilder")) { _showPlaceholderModal = true; std::cout << "About!" << std::endl; }
#ifdef _DEBUG // Only show menu option in Debug build
      if (ImGui::MenuItem("Show ImGui Demo")) { _showDemoWindow = true; }
#endif
      ImGui::EndMenu();
    }
    ImGui::EndMainMenuBar();
  }
}