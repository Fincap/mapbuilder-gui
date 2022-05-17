#include "AddModuleView.h"

AddModuleView::AddModuleView()
{
  loadCoreModules();
  loadAddonModules();
}


void AddModuleView::showWindow(std::vector<ModuleWrapper::Ptr>& modules)
{
  ImGui::Begin("Add Module");

  // TODO properly sort this out by Pipeline Stage.
  if (ImGui::CollapsingHeader("1 Generation", ImGuiTreeNodeFlags_DefaultOpen))
  {
    for (auto& info : _loadedModules)
    {
      ImGui::BeginGroup();

      ImGui::Text(info->name);

      ImGui::SameLine(ImGui::GetWindowContentRegionMax().x - 50);
      if (ImGui::Button("Add"))
        modules.push_back(info->create());

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
    }
  }

  ImGui::End();
}


void AddModuleView::loadCoreModules()
{
  ////////////////
  // GENERATION //
  ////////////////
  
  // Canvas
  struct CanvasInfo : public ModuleInfo
  {
    CanvasInfo()
    {
      name = "Canvas";
      description = "Specifies the map's width and height and generates\
 a basic heightmap of the given dimensions where each height value is set to\
 the highest possible (255).\nNote that having more than one of these modules\
 may lead to undefined behaviour.";
      stage = mbc::PipelineStage::GENERATION;
    }

    ModuleWrapper::Ptr create()
    {
      auto wrapper = std::make_shared<ModuleWrapper>();
      wrapper->module = std::make_shared<mbc::Canvas>();;
      wrapper->handle = std::make_shared<CanvasHandle>(wrapper);
      std::clog << "Canvas module address: " << &wrapper->module << std::endl;
      std::clog << "Canvas handle address: " << &wrapper->handle << std::endl;
      std::clog << "Finished adding Canvas." << std::endl;
      return wrapper;
    }
  };
  _loadedModules.push_back(new CanvasInfo());

}


void AddModuleView::loadAddonModules()
{
  // Stub
}