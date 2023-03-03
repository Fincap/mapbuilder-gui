#include "HeightmapOutHandle.h"

HeightmapOutHandle::HeightmapOutHandle() :
  outputFilepath_(std::ref(std::make_shared<mbc::HeightmapOut>()->outputFilepath))
{}


HeightmapOutHandle::HeightmapOutHandle(mbc::Module::Ptr mod) :
  outputFilepath_(std::ref(std::dynamic_pointer_cast<mbc::HeightmapOut>(mod)->outputFilepath))
{}


bool HeightmapOutHandle::showHandle(int pipelineNum, bool& changed)
{
  // Set previous values
  auto oldFilepath = std::string(outputFilepath_);

  auto label = std::to_string(pipelineNum) + ": Raw heightmap file";

  ImGui::PushID(pipelineNum);
  ImGui::AlignTextToFramePadding();
  if (ImGui::TreeNodeEx(label.c_str(), ImGuiTreeNodeFlags_DefaultOpen))
  {
    showDeleteButton();

    // Processing params
    ImGui::SetNextItemWidth(-125);
    ImGui::InputText("Filepath", &*outputFilepath_, MBC_MAX_PATH);
    ImGui::SameLine();
    if (ImGui::Button("Browse..."))
    {
      util::getSaveFilepathWIN32(outputFilepath_, L"Heightmap (*.hmp)\0*.hmp\0", L"hmp");
    }
    ImGui::TreePop();
  }
  else
  {
    showDeleteButton();
  }

  ImGui::Separator();
  ImGui::PopID();
  // Update changed flag if any values have changes
  changed = (
    std::string(outputFilepath_) != oldFilepath ||
    !alive_
    );

  return alive_;
}
