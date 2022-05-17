#pragma once

#include <imgui.h>

#include <MapBuilderCore.h>

#include "windows\AddModuleView.h"
#include "windows\OutputConsole.h"
#include "windows\PipelineView.h"
#include "app\ApplicationContext.h"

#include "modules\CanvasHandle.h"

class Application
{
public:
  Application();
  ~Application();

  void showWindow();      // Show all active Application views.

private:
#ifdef _DEBUG
  // Demo window toggle if compiled in Debug mode.
  bool _showDemoWindow = false;
#endif

  // Placeholder popup
  bool _showPlaceholderModal = false;
  void showPlaceholderModal();

  void showMainMenuBar();           // Main menu bar

  ApplicationContext* _context;     // Application context

  // Windows
  PipelineView _pipelineView;       // Pipeline view
  AddModuleView _addModuleView;     // Add Module view
  OutputConsole _outputConsole;     // Output console
};

