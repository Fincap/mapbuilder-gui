#pragma once
#include <functional>

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
  /* Triggered by menu items. */
  void menuNew(ApplicationContext&);
  void menuOpen(ApplicationContext&);
  void menuSave(ApplicationContext&);
  void menuSaveAs(ApplicationContext&);
  void exitApplication(ApplicationContext&);

  /* Controls the prompt asking the user if they want to save any changes.
  Executes the callback if there are no unsaved changes. */
  void unsavedChangesPrompt(ApplicationContext&);

  /* Save/load files */
  void contextSave(ApplicationContext&);
  void contextOpen(ApplicationContext&);

  /* Callback that will be executed if Save/Don't Save selected on unsaved
  changes prompt, or if there are no unsaved changes. */
  std::function<void(ApplicationContext&)> callback_;

  /* This is necessary as displaying of modal popups in menubar currently
  does not work. */
  bool displayUnsavedPrompt = false;

};
