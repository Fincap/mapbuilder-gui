#pragma once

#include <imgui.h>

#include <MapBuilderCore.h>

#include "windows\OutputConsole.h"

class Application
{
public:
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

  // Output console
  OutputConsole outputConsole;
};

