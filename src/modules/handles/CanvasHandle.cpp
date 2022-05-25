#include "CanvasHandle.h"

CanvasHandle::CanvasHandle() :
  width_(std::ref(std::make_shared<mbc::Canvas>()->width)),
  height_(std::ref(std::make_shared<mbc::Canvas>()->height))
{}


CanvasHandle::CanvasHandle(mbc::Module::Ptr mod) :
  width_(std::ref(std::dynamic_pointer_cast<mbc::Canvas>(mod)->width)),
  height_(std::ref(std::dynamic_pointer_cast<mbc::Canvas>(mod)->height))
{}


bool CanvasHandle::showHandle(int pipelineNum, bool& changed)
{
  // Set previous values
  auto oldWidth = width_;
  auto oldHeight = height_;

  auto label = std::to_string(pipelineNum) + ": Canvas";

  ImGui::PushID(pipelineNum);
  // This particular module isn't attached to alive flag because it should not
  // be deletable.
  ImGui::AlignTextToFramePadding();
  if (ImGui::TreeNodeEx(label.c_str(), ImGuiTreeNodeFlags_DefaultOpen))
  {
    // Processing params
    ImGui::DragInt("Width", &width_, 1, 2, 2048, "%d", ImGuiSliderFlags_AlwaysClamp);
    ImGui::DragInt("Height", &height_, 1, 2, 2048, "%d", ImGuiSliderFlags_AlwaysClamp);

    ImGui::TreePop();
  }
  ImGui::Separator();
  ImGui::PopID();

  // Update changed flag if any values have changes
  changed = (
    width_ != oldWidth ||
    height_ != oldHeight ||
    !alive_
  );

  return alive_;
}


void CanvasHandle::pointAt(mbc::Module::Ptr mod)
{
  width_ = std::ref(std::dynamic_pointer_cast<mbc::Canvas>(mod)->width);
  height_ = std::ref(std::dynamic_pointer_cast<mbc::Canvas>(mod)->height);
}
