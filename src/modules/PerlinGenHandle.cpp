#include "PerlinGenHandle.h"

PerlinGenHandle::PerlinGenHandle(ModuleWrapper::Ptr wrapper) :
  seed_(std::ref(std::dynamic_pointer_cast<mbc::PerlinGen>(wrapper->module)->seed)),
  frequency_(std::ref(std::dynamic_pointer_cast<mbc::PerlinGen>(wrapper->module)->frequency)),
  octaves_(std::ref(std::dynamic_pointer_cast<mbc::PerlinGen>(wrapper->module)->octaves)),
  seedDistribution_(1, UINT32_MAX)
{}


bool PerlinGenHandle::showHandle(int pipelineNum)
{
  auto label = std::to_string(pipelineNum) + " Perlin Noise";

  ImGui::PushID(pipelineNum);
  if (ImGui::CollapsingHeader(label.c_str(), &alive_, ImGuiTreeNodeFlags_DefaultOpen))
  {
    // Copy original params to temporary locations to allow UI modification.
    float frequencyTemp = frequency_;
    int octavesTemp = octaves_;

    // Processing params - Seed
    ImGui::InputScalar("Seed", ImGuiDataType_U32, &seed_, NULL, NULL, "%u");
    ImGui::SameLine();
    if (ImGui::Button("Random"))
    {
      seed_ = seedDistribution_(seedEngine_);  // Generate random seed.
    }

    // Processing params - Frequency and Octaves
    ImGui::DragFloat("Frequency", &frequencyTemp, 0.07f, 0.2f, 8.0f, "%.2f", ImGuiSliderFlags_AlwaysClamp);
    ImGui::DragInt("Octaves", &octavesTemp, 0.1f, 1, 10, "%d", ImGuiSliderFlags_AlwaysClamp);

    // Apply modified params (implicit cast back to original type).
    frequency_ = frequencyTemp;
    octaves_ = octavesTemp;
  }
  ImGui::PopID();

  return alive_;
}
