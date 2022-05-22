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
    ImGui::InputText("Filepath", &*outputFilepath_, 256);
    ImGui::SameLine();
    ImGui::Button("Browse...");   // TODO add file select window

  }
  ImGui::PopID();

  return alive_;
}
