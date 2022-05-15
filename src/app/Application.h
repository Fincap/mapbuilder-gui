#pragma once

#include <imgui.h>

#include <MapBuilderCore.h>

class Application
{
public:
  void showWindow();

private:
  // Placeholder popup
  bool _showPlaceholderModal = false;
  void showPlaceholderModal();

  // Main menu bar
  void showMainMenuBar();
};

