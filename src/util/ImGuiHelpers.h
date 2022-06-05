#pragma once
#include <cstdint>

#include <imgui.h>

namespace util
{
  /*
  Show a question mark box with a tooltip on hover.
  Copied from imgui_demo.cpp
  */
  static void HelpMarker(const char* desc)
  {
    ImGui::TextDisabled("(?)");
    if (ImGui::IsItemHovered())
    {
      ImGui::BeginTooltip();
      ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
      ImGui::TextUnformatted(desc);
      ImGui::PopTextWrapPos();
      ImGui::EndTooltip();
    }
  }

  /* Convert uint32_t 0xRRGGBB to ImVec4 for ImGui ColorEdit. */
  inline ImVec4 ConvertRGBToFloat4(uint32_t in)
  {
    float s = 1.0f / 255.0f;
    return ImVec4(
      ((in >> 16)  & 0xFF) * s,
      ((in >> 8)   & 0xFF) * s,
      ((in)        & 0xFF) * s,
                    (0xFF) * s);
  }

  /* Convert ImVec4 to uint32_t 0xRRGGBB for ImGui ColorEdit. */
  inline uint32_t ConvertFloat4ToRGB(ImVec4 in)
  {
    unsigned char r = in.x * 255.f;
    unsigned char g = in.y * 255.f;
    unsigned char b = in.z * 255.f;

    return ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff);
  }
}