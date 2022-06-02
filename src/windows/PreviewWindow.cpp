#include "PreviewWindow.h"

PreviewWindow::PreviewWindow()
{

}


void PreviewWindow::showWindow(ApplicationContext& context)
{
  regeneratePreview(context);

  ImGui::Begin("Preview");

  if (heightmapProps_.outSrv != nullptr)
  {
    ImGui::Text("pointer = %p", heightmapProps_.outSrv);
    ImGui::Text("size = %d x %d", resHeightmap_->width, resHeightmap_->height);
    ImGui::Image((void*)heightmapProps_.outSrv, 
      ImVec2(resHeightmap_->width, resHeightmap_->height),
      ImVec2(0.0f, 0.0f), ImVec2(1.0f, 1.0f),
      ImVec4(1.0f, 1.0f, 1.0f, 1.0f),
      ImVec4(1.0f, 1.0f, 1.0f, 0.5f));
  }

  ImGui::End();
}


void PreviewWindow::regeneratePreview(ApplicationContext& context)
{
  /*
  1. Compare the generation modules in the context's Pipeline with those in the
      preview Pipeline.
  2. Copy the entire context Pipeline into preview Pipeline.
  2. If they are different, re-execute just the generation stage and copy the
      generated Heightmap into the Heightmap member.
  3. Execute the Manipulation and Render stages.
  4. Determine which Payloads exist that can be previewed (i.e. raw Heightmap
      or Coloured Heightmap) and draw the respective Payload data to the
      previews.
  */


  // 1. Clear pipeline and compare generation stages.
  auto& previewPipeGenModules = previewPipeline_.getModuleMap().getAll(0);
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

  previewPipeline_.clear();


  // 2. Copy the entire context Pipeline into preview Pipeline.
  for (auto& wrapper : context.modules.getAll())
  {
    auto copy = wrapper->module->clone();
    previewPipeline_.addModule(copy);
  }


  // 3. Re-execute just the generation stage if there are changes.
  if (genStageChanged)
  {
    // Execute
    previewPipeline_.executeStage(0);

    // Extract generated heightmap from Pipeline
    lastHeightmap_.reset();
    lastHeightmap_ = copyHeightmap(previewPipeline_.getPayload<mbc::Heightmap>());
  }


  // 4. Execute Manipulation and Render stages.
  // Inject copy of heightmap into pipeline
  auto copy = copyHeightmap(lastHeightmap_);
  previewPipeline_.setPayload<mbc::Heightmap>(copy);

  // Execute
  previewPipeline_.executeStage(1);
  previewPipeline_.executeStage(2);


  // 5. Draw generated payloads
  // Extract final heightmap from Pipeline.
  resHeightmap_.reset();
  resHeightmap_ = copyHeightmap(previewPipeline_.getPayload<mbc::Heightmap>());

  //if (resHeightmap_->width == 0 && resHeightmap_->height == 0)
  //resHeightmap_ = lastHeightmap_;

  // Load payloads into texture.
  util::loadHeightmapTexture(*resHeightmap_, heightmapProps_);

}


std::shared_ptr<mbc::Heightmap> PreviewWindow::copyHeightmap(mbc::Payload::Ptr payload)
{
  auto copy = std::make_shared<mbc::Heightmap>();
  auto ptr = std::dynamic_pointer_cast<mbc::Heightmap>(payload);

  copy->width = ptr->width;
  copy->height= ptr->height;
  copy->points = new unsigned char[copy->width * copy->height];

  for (int i = 0; i < copy->width * copy->height; i++)
  {
    copy->points[i] = ptr->points[i];
  }

  return copy;
}
