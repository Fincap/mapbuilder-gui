#include "ModuleProvider.h"

ModuleProvider::ModuleProvider()
{
  // Load modules.
  loadCoreModules();
  loadAddonModules();
}


ModuleHandle::Ptr ModuleProvider::getNewHandle(const mbc::Module::Ptr& mod)
{
    return ModuleHandle::Ptr();
}


void ModuleProvider::loadCoreModules()
{
  ////////////////
  // GENERATION //
  ////////////////

  // Canvas
  loadedModules_["canvas"] = std::make_shared<ManualInfo<mbc::Canvas, CanvasHandle>>("Canvas",
    "Specifies the map's width and height and generates \
a basic heightmap of the given dimensions where each height value is set to \
the highest possible (255).\nNote that having more than one of these modules \
may lead to undefined behaviour.",
mbc::PipelineStage::GENERATION
);

  // Perlin Noise
  loadedModules_["perlin_gen"] = std::make_shared<ManualInfo<mbc::PerlinGen, PerlinGenHandle>>("Perlin Noise",
    "TODO - complete description",
    mbc::PipelineStage::GENERATION
    );


  //////////////////
  // MANIPULATION //
  //////////////////

  // Elevation slope
  loadedModules_["elevation_slope"] = std::make_shared<ManualInfo<mbc::ElevationSlope, ElevationSlopeHandle>>("Elevation Slope",
    "TODO - complete description",
    mbc::PipelineStage::MANIPULATION
    );


  ////////////
  // RENDER //
  ////////////



  ////////////
  // OUTPUT //
  ////////////

  // BMP8Out
  loadedModules_["bmp8_out"] = std::make_shared<ManualInfo<mbc::BMP8Out, BMP8OutHandle>>("8-bit .bmp file",
    "TODO - complete description",
    mbc::PipelineStage::OUTPUT
    );

}


void ModuleProvider::loadAddonModules()
{
  // Stub
}
