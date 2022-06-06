#include "ContextController.h"

ContextController::ContextController(ApplicationContext& context) :
  context_(context)
{}


ApplicationContext& ContextController::getContext()
{
  return context_;
}


void ContextController::show()
{
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
      util::saveContextIntoFile(context_);
      callback_(context_);
      ImGui::CloseCurrentPopup();
    }
    ImGui::SetItemDefaultFocus();
    ImGui::SameLine();
    if (ImGui::Button("Don't Save", ImVec2(120, 0)))
    {
      // Don't save context and then do callback.
      callback_(context_);
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


void ContextController::newContext()
{
  callback_ = [&](ApplicationContext& context)
  {
    context.pipeline.clear();
    context.modules.clear();
    context.filename.clear();
    context.isUnsaved = false;
  };
  unsavedChangesPrompt();
}


void ContextController::openContext()
{
  callback_ = [&](ApplicationContext& context)
  {
    util::loadFileIntoContext(context);
  };
  unsavedChangesPrompt();
}


void ContextController::saveContext()
{
  util::saveContextIntoFile(context_);
}


void ContextController::saveContextAs()
{
  util::saveContextIntoFile(context_, true);
}


void ContextController::exitApplication(std::function<void()> onClose)
{
  callback_ = [&](ApplicationContext& context)
  {
    onClose();
  };
  unsavedChangesPrompt();
}


void ContextController::unsavedChangesPrompt()
{
  if (context_.isUnsaved)
    ImGui::OpenPopup("Unsaved Changes");
  else
    callback_(context_);
}
