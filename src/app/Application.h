#pragma once

#include <imgui.h>
#include <imgui_impl_sdl.h>
#include <SDL.h>

#include <Windows.h>

#include "windows\AddModuleView.h"
#include "windows\OutputConsole.h"
#include "windows\PipelineView.h"
#include "windows\MainMenuBar.h"
#include "windows\PreviewWindow.h"
#include "app\ApplicationContext.h"
#include "app\ContextController.h"

class Application
{
public:
  Application();
  ~Application();

  void processEvents(SDL_Window*, std::function<void()>);   // Process SDL events
  void showWindow();      // Show all active Application views.
  bool isDone();          // Returns running state of Application.

private:
  ApplicationContext* context_;           // Application context
  ContextController* contextController_;  // Context controller

  // Windows
  PipelineView pipelineView_;       // Pipeline view
  AddModuleView addModuleView_;     // Add Module view
  OutputConsole outputConsole_;     // Output console
  MainMenuBar mainMenuBar_;         // Main menu bar
  PreviewWindow previewWindow_;     // Preview window

  void refreshWindowTitle();        // Show open file in window title
};

