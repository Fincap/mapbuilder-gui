#pragma once
#include <memory>
#include <string>
#include <map>

#include <imgui.h>
#include <MapBuilderCore\modules\ColourSetModule.h>

#include "modules\ModuleHandle.h"
#include "util\ImGuiHelpers.h"

class ColourSetHandle : public ModuleHandle
{
public:
  ColourSetHandle();
  ColourSetHandle(mbc::Module::Ptr);

  bool showHandle(int, bool&) override;

  template <typename Archive>
  void serialize(Archive& archive) {};

private:
  std::map<unsigned char, uint32_t>*& colourRanges_;

  unsigned char newHeight_ = 128;
  uint32_t newColour_ = 0xff00ff;
};


CEREAL_REGISTER_TYPE(ColourSetHandle);
CEREAL_REGISTER_POLYMORPHIC_RELATION(ModuleHandle, ColourSetHandle);
