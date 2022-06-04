#include "PerlinGenHandle.h"

PerlinGenHandle::PerlinGenHandle() :
  seed_(std::ref(std::make_shared<mbc::PerlinGen>()->seed)),
  frequency_(std::ref(std::make_shared<mbc::PerlinGen>()->frequency)),
  octaves_(std::ref(std::make_shared<mbc::PerlinGen>()->octaves)),
  seedDistribution_(1, UINT32_MAX)
{}


PerlinGenHandle::PerlinGenHandle(mbc::Module::Ptr mod) :
  seed_(std::ref(std::dynamic_pointer_cast<mbc::PerlinGen>(mod)->seed)),
  frequency_(std::ref(std::dynamic_pointer_cast<mbc::PerlinGen>(mod)->frequency)),
  octaves_(std::ref(std::dynamic_pointer_cast<mbc::PerlinGen>(mod)->octaves)),
  seedDistribution_(1, UINT32_MAX)
{}


bool PerlinGenHandle::showHandle(int pipelineNum, bool& changed)
{
  // Set previous values
  auto oldSeed = seed_;
  auto oldFrequency = frequency_;
  auto oldOctaves = octaves_;

  auto label = std::to_string(pipelineNum) + ": Perlin Noise";

  ImGui::PushID(pipelineNum);
  ImGui::AlignTextToFramePadding();
  if (ImGui::TreeNodeEx(label.c_str(), ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_AllowItemOverlap))
  {
    showDeleteButton();

    // Processing params - Seed
    ImGui::InputScalar("Seed", ImGuiDataType_U32, &seed_, NULL, NULL, "%u");
    ImGui::SameLine();
    if (ImGui::Button("Random"))
    {
      seed_ = seedDistribution_(seedEngine_);  // Generate random seed.
    }

    // Processing params - Frequency and Octaves
    const double frequencyMin = 0.2;  const double frequencyMax = 8.0;
    const uint32_t octavesMin = 1;    const uint32_t octavesMax = 6;

    ImGui::SliderScalar("Frequency", ImGuiDataType_Double, &frequency_, &frequencyMin, &frequencyMax, "%.1f");
    ImGui::SliderScalar("Octaves", ImGuiDataType_U32, &octaves_, &octavesMin, &octavesMax, "%d");

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
    seed_ != oldSeed ||
    frequency_ != oldFrequency ||
    octaves_ != oldOctaves ||
    !alive_
  );

  return alive_;
}
