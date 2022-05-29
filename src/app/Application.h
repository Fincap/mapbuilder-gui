#pragma once

#include <imgui.h>

#include <Windows.h>

#include "windows\AddModuleView.h"
#include "windows\OutputConsole.h"
#include "windows\PipelineView.h"
#include "windows\MainMenuBar.h"
#include "windows\PreviewWindow.h"
#include "app\ApplicationContext.h"

class Application
{
public:
  Application();
  ~Application();

  void showWindow();      // Show all active Application views.

private:
  ApplicationContext* context_;     // Application context

  // Windows
  PipelineView pipelineView_;       // Pipeline view
  AddModuleView addModuleView_;     // Add Module view
  OutputConsole outputConsole_;     // Output console
  MainMenuBar mainMenuBar_;         // Main menu bar
  PreviewWindow previewWindow_;     // Preview window

  void refreshWindowTitle();        // Show open file in window title
};

