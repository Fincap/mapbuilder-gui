#pragma once
#include <vector>
#include <typeindex>

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
  ~PreviewWindow();

  void showWindow(ApplicationContext&);   // Display the Preview window.

private:
  void regeneratePreview(ApplicationContext&);  // Update the window's state.

  mbc::StageMap<mbc::Module::Ptr> lastModules_;   // Previous Modules state.
  mbc::Pipeline previewPipeline_;     // Pipeline used to generate Previews.
  mbc::Heightmap lastHeightmap_;      // Previous state of the Heightmap.

  ID3D11ShaderResourceView* heightmapSrv_;

};
