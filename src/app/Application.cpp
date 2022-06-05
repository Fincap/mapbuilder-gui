#include "Application.h"

Application::Application()
{
  context_ = new ApplicationContext();
}


Application::~Application()
{
  delete context_;
}


void Application::processEvents(bool& done, SDL_Window* window, std::function<void()> onClose)
{
  SDL_Event event;
  while (SDL_PollEvent(&event))
  {
    ImGui_ImplSDL2_ProcessEvent(&event);

    // Window quit
    if (event.type == SDL_QUIT)
      done = true;
    if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE && event.window.windowID == SDL_GetWindowID(window))
      done = true;

    // Window resize
    if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_RESIZED && event.window.windowID == SDL_GetWindowID(window))
    {
      onClose();
    }
  }
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

  previewWindow_.showWindow(*context_);

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

  if (context_->showMetricsWindow_)
    ImGui::ShowMetricsWindow(&context_->showMetricsWindow_);
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