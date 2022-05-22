#include "BMP8OutHandle.h"

BMP8OutHandle::BMP8OutHandle(ModuleWrapper::Ptr wrapper) :
  outputFilepath_(std::ref(std::dynamic_pointer_cast<mbc::BMP8Out>(wrapper->module)->outputFilepath))
{}


bool BMP8OutHandle::showHandle(int pipelineNum)
{
  auto label = std::to_string(pipelineNum) + " 8-bit .bmp file";

  ImGui::PushID(pipelineNum);
  if (ImGui::CollapsingHeader(label.c_str(), &alive_, ImGuiTreeNodeFlags_DefaultOpen))
  {
    // Processing params
    ImGui::SetNextItemWidth(-125);
    ImGui::InputText("Filepath", &*outputFilepath_, _MAX_PATH);
    ImGui::SameLine();
    if (ImGui::Button("Browse..."))
    {
      getSaveFilepathWIN32(outputFilepath_, L"Bitmap (*.bmp)\0*.bmp\0", L"bmp");
    }

  }
  ImGui::PopID();

  return alive_;
}
