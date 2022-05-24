#pragma once

#include <imgui.h>

#include <MapBuilderCore.h>
#include <Windows.h>

#include "windows\AddModuleView.h"
#include "windows\OutputConsole.h"
#include "windows\PipelineView.h"
#include "app\ApplicationContext.h"

class Application
{
public:
  Application();
  ~Application();

  void showWindow();      // Show all active Application views.

private:
#ifdef _DEBUG
  // Demo window toggle if compiled in Debug mode.
  bool showDemoWindow_ = false;
#endif

  ApplicationContext* context_;     // Application context

  // Windows
  PipelineView pipelineView_;       // Pipeline view
  AddModuleView addModuleView_;     // Add Module view
  OutputConsole outputConsole_;     // Output console

  void showMainMenuBar();           // Main menu bar

  void refreshWindowTitle();        // Show open file in window title
};

