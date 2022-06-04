#include "GradientSquareHandle.h"

GradientSquareHandle::GradientSquareHandle() :
  fullness_(std::ref(std::make_shared<mbc::GradientSquare>()->fullness)),
  size_(std::ref(std::make_shared<mbc::GradientSquare>()->size))
{}


GradientSquareHandle::GradientSquareHandle(mbc::Module::Ptr mod) :
  fullness_(std::ref(std::dynamic_pointer_cast<mbc::GradientSquare>(mod)->fullness)),
  size_(std::ref(std::dynamic_pointer_cast<mbc::GradientSquare>(mod)->size))
{}


bool GradientSquareHandle::showHandle(int pipelineNum, bool& changed)
{
  // Set previous values
  auto oldFullness = fullness_;
  auto oldSize = size_;

  auto label = std::to_string(pipelineNum) + ": Island Gradient - Square";

  ImGui::PushID(pipelineNum);
  // This particular module isn't attached to alive flag because it should not
  // be deletable.
  ImGui::AlignTextToFramePadding();
  if (ImGui::TreeNodeEx(label.c_str(), ImGuiTreeNodeFlags_DefaultOpen))
  {
    showDeleteButton();

    // Processing params
    const double min = 0.1;
    const double max = 10.0;

    ImGui::SliderScalar("Fullness", ImGuiDataType_Double, &fullness_, &min, &max, "%.1f");
    ImGui::SliderScalar("Size", ImGuiDataType_Double, &size_, &min, &max, "%.1f");

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
    fullness_ != oldFullness ||
    size_ != oldSize ||
    !alive_
    );

  return alive_;
}


void GradientSquareHandle::pointAt(mbc::Module::Ptr mod)
{
  fullness_ = std::ref(std::make_shared<mbc::GradientSquare>()->fullness);
  size_ = std::ref(std::make_shared<mbc::GradientSquare>()->size);
}
