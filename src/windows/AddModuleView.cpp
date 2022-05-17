#include "AddModuleView.h"

AddModuleView::AddModuleView()
{
  loadCoreModules();
  loadAddonModules();
}


void AddModuleView::showWindow(std::vector<ModuleWrapper::Ptr>& modules)
{
  ImGui::Begin("Add Module");

  for (auto& info : _loadedModules)
  {
    if (ImGui::CollapsingHeader(info->name))
    {
      ImGui::TextWrapped(info->description);
      ImGui::Text(std::to_string(pipelineStageToInt(info->stage)).c_str());
      ImGui::SameLine(ImGui::GetWindowContentRegionMax().x - 30);
      if (ImGui::Button("Add"))
        modules.push_back(info->create());
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
  struct CanvasInfo : public ModuleInfo
  {
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
  auto canvasInfo = new CanvasInfo();
  canvasInfo->name = "Canvas";
  canvasInfo->description = "Specifies the map's width and height and generates a basic heightmap\
of the given dimensions where each height value is set to the highest possible\
(255)";
  canvasInfo->stage = mbc::PipelineStage::GENERATION;
  _loadedModules.push_back(canvasInfo);


}


void AddModuleView::loadAddonModules()
{
  // Stub
}