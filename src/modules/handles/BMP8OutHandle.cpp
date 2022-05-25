#include "BMP8OutHandle.h"

BMP8OutHandle::BMP8OutHandle() :
  outputFilepath_(std::ref(std::make_shared<mbc::BMP8Out>()->outputFilepath))
{}


BMP8OutHandle::BMP8OutHandle(mbc::Module::Ptr mod) :
  outputFilepath_(std::ref(std::dynamic_pointer_cast<mbc::BMP8Out>(mod)->outputFilepath))
{}


bool BMP8OutHandle::showHandle(int pipelineNum, bool& changed)
{
  // Set previous values
  auto oldFilepath = std::string(outputFilepath_);

  auto label = std::to_string(pipelineNum) + ": 8-bit .bmp file";

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
      getSaveFilepathWIN32(outputFilepath_, L"Bitmap (*.bmp)\0*.bmp\0", L"bmp");
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


void BMP8OutHandle::pointAt(mbc::Module::Ptr mod)
{
  outputFilepath_ = std::ref(std::dynamic_pointer_cast<mbc::BMP8Out>(mod)->outputFilepath);
}
