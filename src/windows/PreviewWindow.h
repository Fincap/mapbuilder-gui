#pragma once
#include <vector>
#include <typeindex>
#include <exception>

#include <imgui.h>
#include <imgui_impl_dx11.h>
#include <d3d11.h>
#include <MapBuilderCore\Pipeline.h>
#include <MapBuilderCore\PipelineStage.h>
#include <MapBuilderCore\Payload.h>
#include <MapBuilderCore\payloads\Heightmap.h>
#include <MapBuilderCore\util\ModuleHelpers.h>

#include "app\ApplicationContext.h"
#include "util\PreviewHelpers.h"

/*
This window contains the various previews for each specific type of payloads,
such as coloured heightmap, raw heightmap, etc. The class contains a copy of
the main Pipeline that will track changes in the Generation stage and at
regular intervals the Manipulation and Render stages of the copied Pipeline
will be executed and displayed to the preview windows.
*/
class PreviewWindow
{
public:
  PreviewWindow();

  void showWindow(ApplicationContext&);           // Display the Preview window.

private:
  void regeneratePreview(ApplicationContext&);    // Update the window's state.
  
  // Create a copy of the given Heightmap
  std::shared_ptr<mbc::Heightmap> copyHeightmap(mbc::Payload::Ptr);
  std::shared_ptr<mbc::ColouredHeightmap> copyClrdHeightmap(mbc::Payload::Ptr);

  mbc::Pipeline previewPipeline_;                 // Pipeline used to generate Previews.

  util::SrvProps previewSrv_;   // Preview image D3D properties

  std::shared_ptr<mbc::Heightmap> lastHeightmap_; // Previous state of the Heightmap.
  std::shared_ptr<mbc::Heightmap> resHeightmap_;  // Resulting Heightmap from the Pipeline.

  std::shared_ptr<mbc::ColouredHeightmap> lastClrdHeightmap_; // Previous state of the ColouredHeightmap.
  std::shared_ptr<mbc::ColouredHeightmap> resClrdHeightmap_;  // Resulting ColouredHeightmap from the Pipeline.
};
