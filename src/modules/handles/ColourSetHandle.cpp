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
  std::map<unsigned char, uint32_t> oldRanges = *colourRanges_;

  auto label = std::to_string(pipelineNum) + ": Colour by Height";

  ImGui::PushID(pipelineNum);
  ImGui::AlignTextToFramePadding();
  if (ImGui::TreeNodeEx(label.c_str(), ImGuiTreeNodeFlags_DefaultOpen))
  {
    showDeleteButton();

    const int step = 1;
    auto skipNew = colourRanges_->end();    // Default to end - like NaN

    for (auto it = colourRanges_->begin(); it != colourRanges_->end();)
    {
      if (it == skipNew)
      {
        it++;
        continue;
      }

      auto& [height, colour] = *it;
      ImGui::PushID(height);

      bool showDelete = true;

      // Modify copy of key then apply new height after as map key is const.
      auto newHeight = height;

      // Convert colour to ImVec4 then apply after.
      ImVec4 newColour = ImGui::ColorConvertU32ToFloat4(colour);

      ImGuiInputTextFlags heightFlags = ImGuiInputTextFlags_EnterReturnsTrue;
      if (height == 255)
      {
        heightFlags |= ImGuiInputTextFlags_ReadOnly;
        showDelete = false;
      }

      // Processing parameters
      bool heightChanged = ImGui::InputScalar("", ImGuiDataType_U8, &newHeight, &step, NULL, "%u", heightFlags);
      ImGui::SameLine();
      ImGui::ColorEdit3("Colour", (float*)&newColour,
        ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoTooltip |
        ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoOptions
      );

      // Delete button
      if (showDelete)
      {
        ImGui::SameLine(0.f, 25.f);
        ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(7.0f, 0.6f, 0.6f));
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(7.0f, 0.7f, 0.7f));
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(7.0f, 0.8f, 0.8f));
        ImGui::PushID(height);
        if (ImGui::Button("-", ImVec2(23, 23)))
        {
          it = colourRanges_->erase(it);
          ImGui::PopStyleColor(3);
          ImGui::PopID();
          ImGui::PopID();
          continue;
        }
        ImGui::PopStyleColor(3);
        ImGui::PopID();
      }

      // Update map key if changed
      if (heightChanged)
      {
        bool swapped = false;

        // Swap values if new value overlaps with other key
        if (colourRanges_->contains(newHeight))
        {
          auto otherColour = colourRanges_->at(newHeight);
          (*colourRanges_)[height] = otherColour;
          swapped = true;
        }

        // Move colour into new key
        colourRanges_->insert_or_assign(newHeight, colour);
        colour = ImGui::ColorConvertFloat4ToU32(newColour);

        // Delete if no swap
        if (!swapped)
        {
          it = colourRanges_->erase(it);
          skipNew = it;
        }
        else it++;
      }
      else
      {
        colour = ImGui::ColorConvertFloat4ToU32(newColour);
        it++;
      }

      ImGui::PopID();
    }

    // Show add new button
    auto colourBuffer = ImGui::ColorConvertU32ToFloat4(newColour_);

    ImGui::Spacing();
    ImGui::Text("New value");
    ImGui::InputScalar(" ", ImGuiDataType_U8, &newHeight_, &step, NULL, "%u");
    ImGui::SameLine();
    ImGui::ColorEdit3("Colour", (float*)&colourBuffer,
      ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoTooltip |
      ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoOptions
    );

    newColour_ = ImGui::ColorConvertFloat4ToU32(colourBuffer);

    ImGui::SameLine(0.f, 25.f);
    bool disable = false;
    if (colourRanges_->contains(newHeight_))
      disable = true;

    if (disable)
      ImGui::BeginDisabled();

    if (ImGui::Button("+", ImVec2(23, 23)))
      (*colourRanges_)[newHeight_] = newColour_;

    if (disable)
      ImGui::EndDisabled();

    ImGui::TreePop();
  }
  else showDeleteButton();

  ImGui::Separator();
  ImGui::PopID();

  // Update changed flag if any values have changes
  changed = (
    *colourRanges_ != oldRanges ||
    !alive_
    );

  return alive_;
}
