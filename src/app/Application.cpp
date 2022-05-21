#include "Application.h"

Application::Application()
{
  context_ = new ApplicationContext();
}


Application::~Application()
{
  delete context_;
}


void Application::showWindow()
{
  showPlaceholderModal_ = false;

  showMainMenuBar();

  pipelineView_.showWindow(context_->modules);
  addModuleView_.showWindow(context_->modules);
  outputConsole_.showWindow();

#ifdef _DEBUG // Show demo window in Debug build
  if (showDemoWindow_)
    ImGui::ShowDemoWindow(&showDemoWindow_);
#endif

  // Show placeholder if necessary
  if (showPlaceholderModal_)
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
      if (ImGui::MenuItem("New", "CTRL+N")) { showPlaceholderModal_ = true; std::cout << "New!" << std::endl; }
      if (ImGui::MenuItem("Open", "CTRL+O")) { showPlaceholderModal_ = true; std::clog << "Open!" << std::endl; }
      if (ImGui::MenuItem("Save", "CTRL+S")) { showPlaceholderModal_ = true; std::cerr << "Save!" << std::endl; }
      if (ImGui::MenuItem("Save As", "F12")) { showPlaceholderModal_ = true; std::cout << "Save As!" << std::endl; }
      ImGui::EndMenu();
    }
    if (ImGui::BeginMenu("Help"))
    {
      if (ImGui::MenuItem("About MapBuilder")) { showPlaceholderModal_ = true; std::cout << "About!" << std::endl; }
#ifdef _DEBUG // Only show menu option in Debug build
      if (ImGui::MenuItem("Show ImGui Demo")) { showDemoWindow_ = true; }
#endif
      ImGui::EndMenu();
    }
    ImGui::EndMainMenuBar();
  }
}