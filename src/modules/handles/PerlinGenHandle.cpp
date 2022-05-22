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
    // Processing params - Seed
    ImGui::InputScalar("Seed", ImGuiDataType_U32, &seed_, NULL, NULL, "%u");
    ImGui::SameLine();
    if (ImGui::Button("Random"))
    {
      seed_ = seedDistribution_(seedEngine_);  // Generate random seed.
    }

    // Processing params - Frequency and Octaves
    const double frequencyMin = 0.2;  const double frequencyMax = 8.0;
    const uint32_t octavesMin = 1;    const uint32_t octavesMax = 10;

    ImGui::SliderScalar("Frequency", ImGuiDataType_Double, &frequency_, &frequencyMin, &frequencyMax, "%.1f");
    ImGui::SliderScalar("Octaves", ImGuiDataType_U32, &octaves_, &octavesMin, &octavesMax, "%d");

  }
  ImGui::PopID();

  return alive_;
}
