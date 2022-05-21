#include "AddModuleView.h"

AddModuleView::AddModuleView()
{
  loadCoreModules();
  loadAddonModules();
}


void AddModuleView::showWindow(std::vector<ModuleWrapper::Ptr>& modules)
{
  ImGui::Begin("Add Module");

  int count = 0;

  // TODO properly sort this out by Pipeline Stage.
  if (ImGui::CollapsingHeader("1 Generation", ImGuiTreeNodeFlags_DefaultOpen))
  {
    for (auto& info : loadedModules_)
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
  }

  ImGui::End();
}


void AddModuleView::loadCoreModules()
{
  ////////////////
  // GENERATION //
  ////////////////
  
  // Canvas
  loadedModules_.push_back(new ManualInfo<mbc::Canvas, CanvasHandle>("Canvas",
    "Specifies the map's width and height and generates \
a basic heightmap of the given dimensions where each height value is set to \
the highest possible (255).\nNote that having more than one of these modules \
may lead to undefined behaviour.",
    mbc::PipelineStage::GENERATION
  ));

  // Perlin Noise
  loadedModules_.push_back(new ManualInfo<mbc::PerlinGen, PerlinGenHandle>("Perlin Noise",
    "TODO - complete description",
    mbc::PipelineStage::GENERATION
  ));


  //////////////////
  // MANIPULATION //
  //////////////////

  // Elevation slope
  loadedModules_.push_back(new ManualInfo<mbc::ElevationSlope, ElevationSlopeHandle>("Elevation Slope",
    "TODO - complete description",
    mbc::PipelineStage::MANIPULATION
  ));


  ////////////
  // OUTPUT //
  ////////////

  // BMP8Out
  loadedModules_.push_back(new ManualInfo<mbc::BMP8Out, BMP8OutHandle>("8-bit .bmp file",
    "TODO - complete description",
    mbc::PipelineStage::OUTPUT
  ));

}


void AddModuleView::loadAddonModules()
{
  // Stub
}