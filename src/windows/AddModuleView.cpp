#include "AddModuleView.h"

AddModuleView::AddModuleView()
{
  loadedModules_ = new std::vector<ModuleInfo::Ptr>[MBC_NUM_STAGES];

  // Sort modules loaded by Provider instance into their respective stages.
  for (const auto& mod : ModuleProvider::instance().getInfoAll())
  {
    loadedModules_[(int)mod->stage].push_back(mod);
  }
}


AddModuleView::~AddModuleView()
{
  delete[] loadedModules_;
}


bool AddModuleView::showWindow(mbc::StageMap<ModuleWrapper::Ptr>& modules)
{
  // Add default Canvas if one doesn't exist already
  // TODO this is more of a bandaid solution than a properly elegant one.
  if (modules.getAll(0).size() == 0)
  {
    modules.add(loadedModules_[0].at(0)->createModule(), 0);
  }

  ImGui::Begin("Add Module");

  bool newModule = false;
  int count = 0;

  for (int i = 0; i < MBC_NUM_STAGES; i++)
  {
    if (ImGui::CollapsingHeader(pipelineStageToStringExtended((mbc::PipelineStage)i)))
    {
      for (auto info = loadedModules_[i].begin(); info != loadedModules_[i].end(); info++)
      {
        // Increment past first value in Generation stage (where Canvas is stored),
        // as it should not appear in the list of possible modules.
        if (i == 0 && info == loadedModules_[0].begin())
          info++;

        if (displayModuleInfo(modules.getAll(i), *info, count))
          newModule = true;
      }
    }
  }

  ImGui::End();

  return newModule;
}


bool AddModuleView::displayModuleInfo(std::vector<ModuleWrapper::Ptr>& modules, ModuleInfo::Ptr info, int& count)
{
  bool newModule = false;

  ImGui::PushID(count);
  ImGui::BeginGroup();

  ImGui::Text(info->name);

  ImGui::SameLine(ImGui::GetWindowContentRegionMax().x - 50);
  if (ImGui::Button("Add"))
  {
    modules.push_back(info->createModule());
    newModule = true;
  }

  ImGui::EndGroup();
  if (ImGui::IsItemHovered())
  {
    ImGui::BeginTooltip();
    ImGui::PushTextWrapPos(ImGui::GetFontSize() * 25.0f);
    ImGui::TextUnformatted(info->description);
    ImGui::PopTextWrapPos();
    ImGui::EndTooltip();
  }

  ImGui::Separator();

  ImGui::PopID();
  count++;

  return newModule;
}