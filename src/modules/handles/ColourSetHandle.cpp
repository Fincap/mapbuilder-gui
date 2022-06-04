#include "ColourSetHandle.h"

ColourSetHandle::ColourSetHandle() :
  colourRanges_(std::ref(std::make_shared<mbc::ColourSetModule>()->colourRanges))
{}


ColourSetHandle::ColourSetHandle(mbc::Module::Ptr mod) :
  colourRanges_(std::ref(std::dynamic_pointer_cast<mbc::ColourSetModule>(mod)->colourRanges))
{}


bool ColourSetHandle::showHandle(int pipelineNum, bool& changed)
{
  // Set previous values
  auto oldRanges = colourRanges_;

  auto label = std::to_string(pipelineNum) + ": Colour by Height";

  ImGui::PushID(pipelineNum);
  ImGui::AlignTextToFramePadding();
  if (ImGui::TreeNodeEx(label.c_str(), ImGuiTreeNodeFlags_DefaultOpen))
  {
    showDeleteButton();

    // Processing params
    const int step = 1;

    for (auto& [height, colour] : *colourRanges_)
    {
      ImGui::PushID(height);

      // Modify copy of key then apply new height after as map key is const.
      auto newHeight = height;

      // Convert colour to ImVec4 then apply after.
      ImVec4 newColour = ImGui::ColorConvertU32ToFloat4(colour);

      // Processing parameters
      ImGui::InputScalar("", ImGuiDataType_U8, &newHeight, &step, NULL, "%u");
      ImGui::SameLine();
      ImGui::ColorEdit3("Colour", (float*)&newColour,
        ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoTooltip |
        ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoOptions
      );

      // Update colours
      colour = ImGui::ColorConvertFloat4ToU32(newColour);

      // Update map key if changed


      ImGui::PopID();
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
    colourRanges_ != oldRanges ||
    !alive_
    );

  return alive_;
}
