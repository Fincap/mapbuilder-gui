#include "ModuleProvider.h"

ModuleProvider::ModuleProvider()
{
  // Load modules.
  loadCoreModules();
  loadAddonModules();
}


ModuleInfo::Ptr ModuleProvider::getInfo(const std::string& moduleName)
{
  try {
    return loadedModules_.at(moduleName);
  }
  catch (const std::out_of_range& e)
  {
    std::cerr << e.what() << std::endl;
    return std::shared_ptr<ModuleInfo>(nullptr);
  }
}


std::vector<ModuleInfo::Ptr> ModuleProvider::getInfoAll()
{
  std::vector<ModuleInfo::Ptr> infoAll;

  for (const auto& [name, info] : loadedModules_)
  {
    infoAll.push_back(info);
  }

  return infoAll;

}


ModuleHandle::Ptr ModuleProvider::getNewHandle(const mbc::Module::Ptr& mod)
{
  try {
    return loadedModules_.at(mod->getModuleName())->getHandleToModule(mod);
  }
  catch (const std::out_of_range& e)
  {
    std::cerr << e.what() << std::endl;
    return std::shared_ptr<ModuleHandle>(nullptr);
  }
}


void ModuleProvider::loadCoreModules()
{
  ////////////////
  // GENERATION //
  ////////////////

  // Canvas
  loadedModules_["canvas"] = std::make_shared<util::ManualInfo<mbc::Canvas, CanvasHandle>>("Canvas",
    "Specifies the map's width and height and generates \
a basic heightmap of the given dimensions where each height value is set to \
the highest possible (255).\nNote that having more than one of these modules \
may lead to undefined behaviour.",
mbc::PipelineStage::GENERATION
);

  // Perlin Noise
  loadedModules_["perlin_gen"] = std::make_shared<util::ManualInfo<mbc::PerlinGen, PerlinGenHandle>>("Perlin Noise",
    "TODO - complete description",
    mbc::PipelineStage::GENERATION
    );


  //////////////////
  // MANIPULATION //
  //////////////////

  // Elevation slope
  loadedModules_["elevation_slope"] = std::make_shared<util::ManualInfo<mbc::ElevationSlope, ElevationSlopeHandle>>("Elevation Slope",
    "TODO - complete description",
    mbc::PipelineStage::MANIPULATION
    );

  // Gradient Square
  loadedModules_["gradient_square"] = std::make_shared<util::ManualInfo<mbc::GradientSquare, GradientSquareHandle>>("Island Gradient - Square",
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
  loadedModules_["bmp8_out"] = std::make_shared<util::ManualInfo<mbc::BMP8Out, BMP8OutHandle>>("8-bit .bmp file",
    "TODO - complete description",
    mbc::PipelineStage::OUTPUT
    );

}


void ModuleProvider::loadAddonModules()
{
  // Stub
}
