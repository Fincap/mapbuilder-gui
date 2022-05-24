#pragma once

#include <imgui.h>
#include <MapBuilderCore.h>

#include "app\ApplicationContext.h"

/*
This window displays the main menu bar across the top of the application, and
is responsible for implementing the application context manipulation functions
(New, Open, Save, Save As, etc.)
*/
class MainMenuBar
{
public:
  void showWindow(ApplicationContext&);

private:
  void contextNew(ApplicationContext&);
  void contextOpen(ApplicationContext&);
  void contextSave(ApplicationContext&);
  void contextSaveAs(ApplicationContext&);
  void exitApplication();

};
