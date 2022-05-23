#include "AddModuleView.h"

AddModuleView::AddModuleView()
{
  loadedModules_ = new std::vector<ModuleInfo*>[MBC_NUM_STAGES];
  loadCoreModules();
  loadAddonModules();
}


void AddModuleView::showWindow(mbc::StageMap<ModuleWrapper::Ptr>& modules)
{
  // Add default Canvas if one doesn't exist already
  // TODO this is more of a bandaid solution than a properly elegant one.
  if (modules.getAll(0).size() == 0)
  {
    modules.add(loadedModules_[0].at(0)->create(), 0);
  }

  ImGui::Begin("Add Module");

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

        displayModuleInfo(modules.getAll(i), *info, count);
      }
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
  loadedModules_[0].push_back(new ManualInfo<mbc::Canvas, CanvasHandle>("Canvas",
    "Specifies the map's width and height and generates \
a basic heightmap of the given dimensions where each height value is set to \
the highest possible (255).\nNote that having more than one of these modules \
may lead to undefined behaviour.",
    mbc::PipelineStage::GENERATION
  ));

  // Perlin Noise
  loadedModules_[0].push_back(new ManualInfo<mbc::PerlinGen, PerlinGenHandle>("Perlin Noise",
    "TODO - complete description",
    mbc::PipelineStage::GENERATION
  ));


  //////////////////
  // MANIPULATION //
  //////////////////

  // Elevation slope
  loadedModules_[1].push_back(new ManualInfo<mbc::ElevationSlope, ElevationSlopeHandle>("Elevation Slope",
    "TODO - complete description",
    mbc::PipelineStage::MANIPULATION
  ));


  ////////////
  // OUTPUT //
  ////////////

  // BMP8Out
  loadedModules_[3].push_back(new ManualInfo<mbc::BMP8Out, BMP8OutHandle>("8-bit .bmp file",
    "TODO - complete description",
    mbc::PipelineStage::OUTPUT
  ));

}


void AddModuleView::loadAddonModules()
{
  // Stub
}


void AddModuleView::displayModuleInfo(std::vector<ModuleWrapper::Ptr>& modules, ModuleInfo* info, int& count)
{
  ImGui::PushID(count);
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

  ImGui::PopID();
  count++;
}