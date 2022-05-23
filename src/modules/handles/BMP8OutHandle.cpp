#include "BMP8OutHandle.h"

BMP8OutHandle::BMP8OutHandle(ModuleWrapper::Ptr wrapper) :
  outputFilepath_(std::ref(std::dynamic_pointer_cast<mbc::BMP8Out>(wrapper->module)->outputFilepath))
{}


bool BMP8OutHandle::showHandle(int pipelineNum)
{
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

  return alive_;
}
