#include "MainMenuBar.h"

void MainMenuBar::showWindow(ContextController& contextController)
{
  auto& context = contextController.getContext();

  // Show menu bar
  if (ImGui::BeginMainMenuBar())
  {
    if (ImGui::BeginMenu("File"))
    {
      if (ImGui::MenuItem("New", "CTRL+N")) contextController.newContext();
      if (ImGui::MenuItem("Open", "CTRL+O")) contextController.openContext();
      if (ImGui::MenuItem("Save", "CTRL+S")) contextController.saveContext();
      if (ImGui::MenuItem("Save As", "CTRL+SHIFT+S")) contextController.saveContextAs();
      ImGui::Separator();
      if (ImGui::MenuItem("Exit")) contextController.exitApplication();
      ImGui::EndMenu();
    }
    if (ImGui::BeginMenu("Help"))
    {
      if (ImGui::MenuItem("About MapBuilder")) { std::cout << "About!" << std::endl; }
#ifdef _DEBUG // Only show menu option in Debug build
      if (ImGui::MenuItem("Show ImGui Demo")) { context.showDemoWindow_ = true; }
      if (ImGui::MenuItem("Show ImGui Metrics")) { context.showMetricsWindow_ = true; }
#endif
      ImGui::EndMenu();
    }
    ImGui::EndMainMenuBar();
  }

}
