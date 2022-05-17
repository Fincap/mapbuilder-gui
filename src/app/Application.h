#pragma once

#include <imgui.h>

#include <MapBuilderCore.h>

#include "windows\OutputConsole.h"
#include "windows\PipelineView.h"
#include "app\ApplicationContext.h"

#include "modules\CanvasHandle.h"

class Application
{
public:
  Application();
  ~Application();

  void showWindow();

private:
#ifdef _DEBUG
  // Demo window toggle if compiled in Debug mode.
  bool _showDemoWindow = false;
#endif

  // Placeholder popup
  bool _showPlaceholderModal = false;
  void showPlaceholderModal();

  // Main menu bar
  void showMainMenuBar();

  // Application context
  ApplicationContext* _context;

  // Pipeview view
  PipelineView _pipelineView;

  // Output console
  OutputConsole _outputConsole;
};

