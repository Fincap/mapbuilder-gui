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

  // Show windows
  mainMenuBar_.showWindow(*context_);

  context_->isUnsaved |= pipelineView_.showWindow(context_->modules);
  context_->isUnsaved |= addModuleView_.showWindow(context_->modules);

  outputConsole_.showWindow();

  // Show execute window
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