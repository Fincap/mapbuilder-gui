#include "MainMenuBar.h"

void MainMenuBar::showWindow(ApplicationContext& context)
{
  if (ImGui::BeginMainMenuBar())
  {
    if (ImGui::BeginMenu("File"))
    {
      if (ImGui::MenuItem("New", "CTRL+N")) contextNew(context);
      if (ImGui::MenuItem("Open", "CTRL+O")) contextOpen(context);
      if (ImGui::MenuItem("Save", "CTRL+S")) contextSave(context);
      if (ImGui::MenuItem("Save As", "F12")) contextSaveAs(context);
      ImGui::Separator();
      if (ImGui::MenuItem("Exit", "ALT+F4")) exitApplication();
      ImGui::EndMenu();
    }
    if (ImGui::BeginMenu("Help"))
    {
      if (ImGui::MenuItem("About MapBuilder")) { std::cout << "About!" << std::endl; }
#ifdef _DEBUG // Only show menu option in Debug build
      if (ImGui::MenuItem("Show ImGui Demo")) { context.showDemoWindow_ = true; }
#endif
      ImGui::EndMenu();
    }
    ImGui::EndMainMenuBar();
  }
}


void MainMenuBar::contextNew(ApplicationContext& context)
{

}


void MainMenuBar::contextOpen(ApplicationContext& context)
{

}


void MainMenuBar::contextSave(ApplicationContext& context)
{

}


void MainMenuBar::contextSaveAs(ApplicationContext& context)
{

}


void MainMenuBar::exitApplication()
{
  exit(0);
}
