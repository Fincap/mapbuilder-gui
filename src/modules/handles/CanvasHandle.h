#pragma once
#include <memory>
#include <string>

#include <imgui.h>

#include "modules\ModuleHandle.h"
#include "modules\ModuleWrapper.h"

class CanvasHandle : public ModuleHandle
{
public:
  CanvasHandle(ModuleWrapper::Ptr);

  bool showHandle(int, bool&) override;

  template <typename Archive>
  void serialize(Archive& archive) {};

  template <class Archive>
  static void load_and_construct( Archive & ar, cereal::construct<CanvasHandle> & construct )
  {
    ModuleWrapper::Ptr x;
    ar( x );
    construct( x );
  }

private:
  int& width_;
  int& height_;
};


CEREAL_REGISTER_TYPE(CanvasHandle);
CEREAL_REGISTER_POLYMORPHIC_RELATION(ModuleHandle, CanvasHandle);
