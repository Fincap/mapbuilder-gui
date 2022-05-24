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
  // Push style vars
  ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 4);
  ImGui::PushStyleVar(ImGuiStyleVar_TabRounding, 4);

  showMainMenuBar();

  context_->isUnsaved |= pipelineView_.showWindow(context_->modules);
  context_->isUnsaved |= addModuleView_.showWindow(context_->modules);

  outputConsole_.showWindow();

  ImGui::Begin("Execute");
  if (ImGui::Button("Run pipeline"))
  {
    for (auto& mod : context_->modules.getAll())
    {
      context_->pipeline.addModule(mod->module);
    }
    context_->pipeline.execute();
    context_->pipeline.clear(); // Clear Pipeline on completion
  }

#ifdef _DEBUG // Show demo window in Debug build
  if (context_->showDemoWindow_)
    ImGui::ShowDemoWindow(&context_->showDemoWindow_);
#endif

  ImGui::End();

  // Pop style vars
  ImGui::PopStyleVar(2);

  refreshWindowTitle();

}


void Application::showMainMenuBar()
{
  if (ImGui::BeginMainMenuBar())
  {
    if (ImGui::BeginMenu("File"))
    {
      if (ImGui::MenuItem("New", "CTRL+N")) { std::cout << "New!" << std::endl; }
      if (ImGui::MenuItem("Open", "CTRL+O")) { std::clog << "Open!" << std::endl; }
      if (ImGui::MenuItem("Save", "CTRL+S")) { std::cerr << "Save!" << std::endl; context_->isUnsaved = false; }
      if (ImGui::MenuItem("Save As", "F12")) { std::cout << "Save As!" << std::endl; }
      ImGui::EndMenu();
    }
    if (ImGui::BeginMenu("Help"))
    {
      if (ImGui::MenuItem("About MapBuilder")) { std::cout << "About!" << std::endl; }
#ifdef _DEBUG // Only show menu option in Debug build
      if (ImGui::MenuItem("Show ImGui Demo")) { context_->showDemoWindow_ = true; }
#endif
      ImGui::EndMenu();
    }
    ImGui::EndMainMenuBar();
  }
}


void Application::refreshWindowTitle()
{
  std::wstring windowText = L"MapBuilder - ";
  if (context_->filename.empty())
    windowText += L"Untitled";
  else
    windowText += context_->filename.c_str();

  if (context_->isUnsaved)
    windowText += L"*";

  SetWindowText(GetActiveWindow(), windowText.c_str());
}