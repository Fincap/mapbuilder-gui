#include "AddModuleView.h"

AddModuleView::AddModuleView()
{
  loadCoreModules();
  loadAddonModules();
}


void AddModuleView::showWindow(std::vector<ModuleWrapper>& modules)
{
  ImGui::Begin("Add Module");

  for (auto& info : _loadedModules)
  {
    if (ImGui::CollapsingHeader(info.name))
    {
      ImGui::TextWrapped(info.description);
      ImGui::Text(std::to_string(pipelineStageToInt(info.stage)).c_str());
      ImGui::SameLine(ImGui::GetWindowContentRegionMax().x - 30);
      if (ImGui::Button("Add"))
        modules.push_back(info.create());
    }
    ImGui::Separator();
  }

  ImGui::End();
}


void AddModuleView::loadCoreModules()
{
  ////////////////
  // GENERATION //
  ////////////////
  
  // Canvas
  _loadedModules.push_back(ModuleInfo
    {
      "Canvas",
      "Specifies the map's width and height and generates a basic heightmap\
 of the given dimensions where each height value is set to the highest possible\
 (255)",
    mbc::PipelineStage::GENERATION,
    [](){
      std::clog << "Added new Canvas module." << std::endl;
      auto wrapper = ModuleWrapper();
      wrapper.module = std::make_shared<mbc::Canvas>();;
      wrapper.handle = std::make_shared<CanvasHandle>(wrapper);
      return wrapper;
    }
  });


}


void AddModuleView::loadAddonModules()
{
  // Stub
}