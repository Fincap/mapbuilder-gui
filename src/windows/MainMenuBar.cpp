#include "MainMenuBar.h"

void MainMenuBar::showWindow(ApplicationContext& context)
{
  // Show menu bar
  if (ImGui::BeginMainMenuBar())
  {
    if (ImGui::BeginMenu("File"))
    {
      if (ImGui::MenuItem("New", "CTRL+N")) menuNew(context);
      if (ImGui::MenuItem("Open", "CTRL+O")) menuOpen(context);
      if (ImGui::MenuItem("Save", "CTRL+S")) menuSave(context);
      if (ImGui::MenuItem("Save As", "F12")) menuSaveAs(context);
      ImGui::Separator();
      if (ImGui::MenuItem("Exit", "ALT+F4")) exitApplication(context);
      ImGui::EndMenu();
    }
    if (ImGui::BeginMenu("Help"))
    {
      if (ImGui::MenuItem("About MapBuilder")) { std::cout << "About!" << std::endl; }
#ifdef _DEBUG // Only show menu option in Debug build
      if (ImGui::MenuItem("Show ImGui Demo")) { context.showDemoWindow_ = true; }
#endif
      ImGui::EndMenu();
    }
    ImGui::EndMainMenuBar();
  }

  if (displayUnsavedPrompt)
  {
    ImGui::OpenPopup("Unsaved Changes");
    displayUnsavedPrompt = false;
  }

  // Show unsaved changes prompt
  // Always center this window when appearing
  ImVec2 center = ImGui::GetMainViewport()->GetCenter();
  ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));

  if (ImGui::BeginPopupModal("Unsaved Changes", NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoMove))
  {
    ImGui::Text("You have unsaved changes. Do you want to save your changes?\n\n");
    ImGui::Separator();

    if (ImGui::Button("Save", ImVec2(120, 0)))
    {
      // Save context and then do callback.
      contextSave(context);
      callback_(context);
      ImGui::CloseCurrentPopup();
    }
    ImGui::SetItemDefaultFocus();
    ImGui::SameLine();
    if (ImGui::Button("Don't Save", ImVec2(120, 0)))
    {
      // Don't save context and then do callback.
      callback_(context);
      ImGui::CloseCurrentPopup();
    }
    ImGui::SameLine();
    if (ImGui::Button("Cancel", ImVec2(120, 0)))
    {
      // Don't save context and don't do callback.
      ImGui::CloseCurrentPopup();
    }
    ImGui::EndPopup();
  }
}


void MainMenuBar::menuNew(ApplicationContext& context)
{
  callback_ = [&](ApplicationContext& context)
  {
    context.pipeline.clear();
    context.modules.clear();
    context.filename.clear();
    context.isUnsaved = false;
  };
  unsavedChangesPrompt(context);
}


void MainMenuBar::menuOpen(ApplicationContext& context)
{
  callback_ = [&](ApplicationContext& context)
  {
    contextOpen(context);
  };
  unsavedChangesPrompt(context);
}


void MainMenuBar::menuSave(ApplicationContext& context)
{
  contextSave(context);
}


void MainMenuBar::menuSaveAs(ApplicationContext& context)
{
  contextSave(context, true);
}


void MainMenuBar::exitApplication(ApplicationContext& context)
{
  callback_ = [&](ApplicationContext& context)
  {
    exit(0);
  };
  unsavedChangesPrompt(context);
}


void MainMenuBar::unsavedChangesPrompt(ApplicationContext& context)
{
  if (context.isUnsaved)
    displayUnsavedPrompt = true;
  else
    callback_(context);
}


void MainMenuBar::contextOpen(ApplicationContext& context)
{
  std::filesystem::path openedFile;
  char buffer[MBC_MAX_PATH] = {0};
  getOpenFilepathWIN32(buffer, L"MapBuilder File (*.mbc)\0*.mbc\0");
  openedFile = buffer;

  if (openedFile.empty())   // If no filepath was selected, exit early
  {
    return;
  }

  // Deserialize
  {
    std::ifstream is(openedFile);

    cereal::XMLInputArchive archive(is);
    try {
      archive(context.modules);
    }
    catch (cereal::Exception)
    {
      std::cerr << "Could not open selected file\n";
      return;
    }
  }

  // Clean up
  context.filename = openedFile;
  context.isUnsaved = false;
  context.pipeline.clear();
}


void MainMenuBar::contextSave(ApplicationContext& context, bool newPath)
{
  if (newPath || context.filename.empty())
  {
    // Open Save file dialog
    char buffer[MBC_MAX_PATH] = {0};
    getSaveFilepathWIN32(buffer, L"MapBuilder File (*.mbc)\0*.mbc\0", L"mbc");
    context.filename = buffer;
  }

  // Serialize 
  {
    std::ofstream os(context.filename);
    if (!os.is_open())
    {
      std::cerr << "Could not save to selected file\n";
      return;
    }

    cereal::XMLOutputArchive archive(os);
    archive(context.modules);
  }

  // Clean up
  context.isUnsaved = false;
}
