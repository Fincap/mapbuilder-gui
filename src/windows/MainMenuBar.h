#pragma once
#include <functional>
#include <filesystem>
#include <fstream>

#include <imgui.h>

#include "app\ContextController.h"

/*
This window displays the main menu bar across the top of the application, and
is responsible for implementing the application context manipulation functions
(New, Open, Save, Save As, etc.)
*/
class MainMenuBar
{
public:
  void showWindow(ContextController&);

};
