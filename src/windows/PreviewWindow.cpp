#include "PreviewWindow.h"

PreviewWindow::PreviewWindow() :
  heightmapSrv_(nullptr)
{ }


PreviewWindow::~PreviewWindow()
{
  delete heightmapSrv_;
}


void PreviewWindow::showWindow(ApplicationContext& context)
{
  regeneratePreview(context);

  ImGui::Begin("Preview");

  if (heightmapSrv_ != nullptr)
  {
    ImGui::Text("pointer = %p", heightmapSrv_);
    ImGui::Text("size = %d x %d", lastHeightmap_.width, lastHeightmap_.height);
    ImGui::Image((void*)heightmapSrv_, ImVec2(lastHeightmap_.width, lastHeightmap_.height));
  }

  ImGui::End();
}


void PreviewWindow::regeneratePreview(ApplicationContext& context)
{
  /*
  1. Compare the generation modules in the context's Pipeline with those in the
      preview Pipeline.
  2. If they are different, re-execute just the generation stage and copy the
      generated Heightmap into the Heightmap member.
  3. Add all the non-generation stage modules into the Pipeline and execute.
  4. Determine which Payloads exist that can be previewed (i.e. raw Heightmap
      or Coloured Heightmap) and draw the respective Payload data to the
      previews.
  */


  // 1. Clear pipeline and compare generation stages.
  previewPipeline_.clear();

  auto& previewPipeGenModules = lastModules_.getAll(0);
  auto& contextPipeGenModules = context.modules.getAll(0);

  // If the generation stages are the same size, then compare each module.
  bool genStageChanged = false;
  if (previewPipeGenModules.size() == contextPipeGenModules.size())
  {
    for (int i = 0; i < previewPipeGenModules.size(); i++)
    {
      if ((*previewPipeGenModules.at(i)) != contextPipeGenModules.at(i)->module)
        genStageChanged = true;
    }
  }
  else
  {
    genStageChanged = true;
  }


  // 2. Re-execute just the generation stage if there are changes.
  if (genStageChanged)
  {
    lastModules_.clear();
    // Copy generation stage to preview pipeline
    for (auto& wrapper : contextPipeGenModules)
    {
      auto modCopy = wrapper->module->clone();
      lastModules_.add(modCopy, 0);
      previewPipeline_.addModule(modCopy);
    }

    // Execute
    previewPipeline_.execute();

    // Extract generated heightmap from Pipeline
    auto payloadPtr = previewPipeline_.getPayload(std::type_index(typeid(mbc::Heightmap)));
    lastHeightmap_ = *std::dynamic_pointer_cast<mbc::Heightmap>(payloadPtr);

    // Clear pipeline
    previewPipeline_.clear();
  }


  // 3. Add all the non-generation stage modules into the Pipeline and execute.
  // Clear stages 2 and 3
  lastModules_.getAll(1).clear();
  lastModules_.getAll(2).clear();

  // Copy manipulation stage modules across
  for (auto& wrapper : context.modules.getAll(1))
  {
    auto modCopy = wrapper->module->clone();
    lastModules_.add(modCopy, 1);
    previewPipeline_.addModule(modCopy);
  }

  // Copy render stage modules across
  for (auto& wrapper : context.modules.getAll(2))
  {
    auto modCopy = wrapper->module->clone();
    lastModules_.add(modCopy, 2);
    previewPipeline_.addModule(modCopy);
  }

  // Inject heightmap into pipeline
  previewPipeline_.setPayload(std::make_shared<mbc::Heightmap>(lastHeightmap_));

  // Execute
  previewPipeline_.execute();


  // 4. Draw generated payloads
  util::loadHeightmapTexture(lastHeightmap_, &heightmapSrv_);

}