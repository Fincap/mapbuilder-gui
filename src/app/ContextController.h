#pragma once
#include <functional>
#include <filesystem>
#include <fstream>

#include <imgui.h>

#include "ApplicationContext.h"
#include "util\ContextHelpers.h"

class ContextController
{
public:
  ContextController(ApplicationContext&);

  ApplicationContext& getContext();

  void show();  // Display unsaved changes prompt if necessary.

  /* Interface to manipulate context. */
  void newContext();
  void openContext();
  void saveContext();
  void saveContextAs();
  void exitApplication(std::function<void()>);

private:
  /* Controls the prompt asking the user if they want to save any changes.
  Executes the callback if there are no unsaved changes. */
  void unsavedChangesPrompt();

  /* Callback that will be executed if Save/Don't Save selected on unsaved
  changes prompt, or if there are no unsaved changes. */
  std::function<void(ApplicationContext&)> callback_;

  ApplicationContext& context_;

  /* This is necessary as displaying of modal popups in menubar currently
  does not work. */
  //bool displayUnsavedPrompt = false;

};
