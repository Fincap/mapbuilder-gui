#include "MainMenuBar.h"

void MainMenuBar::showWindow(ApplicationContext& context)
{
  if (ImGui::BeginMainMenuBar())
  {
    if (ImGui::BeginMenu("File"))
    {
      if (ImGui::MenuItem("New", "CTRL+N")) { std::cout << "New!" << std::endl; }
      if (ImGui::MenuItem("Open", "CTRL+O")) { std::clog << "Open!" << std::endl; }
      if (ImGui::MenuItem("Save", "CTRL+S")) { std::cerr << "Save!" << std::endl; context.isUnsaved = false; }
      if (ImGui::MenuItem("Save As", "F12")) { std::cout << "Save As!" << std::endl; }
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

}
