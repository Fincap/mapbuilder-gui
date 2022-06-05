#include "PreviewWindow.h"

PreviewWindow::PreviewWindow()
{

}


void PreviewWindow::showWindow(ApplicationContext& context)
{
  regeneratePreview(context);

  ImGui::Begin("Preview");

  if (previewSrv_.srv != nullptr)
  {
    // Radio buttons
    static int view = 0;
    auto isColouredHeightmapNull = resClrdHeightmap_ == nullptr;

    if (isColouredHeightmapNull)
      view = 0;

    ImGui::RadioButton("Raw Heightmap", &view, 0); ImGui::SameLine();
    ImGui::BeginDisabled(isColouredHeightmapNull);
    ImGui::RadioButton("Coloured Heightmap", &view, 1);
    ImGui::EndDisabled();

    int width, height;

    switch (view)
    {
    case 0:
      width = resHeightmap_->width;
      height = resHeightmap_->height;
      util::loadHeightmapTexture(*resHeightmap_, previewSrv_);
      break;

    case 1:
      width = resClrdHeightmap_->width;
      height = resClrdHeightmap_->height;
      util::loadColouredHeightmapTexture(*resClrdHeightmap_, previewSrv_);
      break;

    }

    // Info
    ImGui::Text("pointer = %p", previewSrv_.srv);
    ImGui::Text("size = %d x %d", width, height);

    // Display image
    ImGui::Image((void*)previewSrv_.srv,
      ImVec2(width, height),
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
  // Extract final payloads from Pipeline.
  resHeightmap_.reset();
  resHeightmap_ = copyHeightmap(previewPipeline_.getPayload<mbc::Heightmap>());

  resClrdHeightmap_.reset();
  auto colouredHeightmap = previewPipeline_.getPayload<mbc::ColouredHeightmap>();
  if (colouredHeightmap != nullptr)
    resClrdHeightmap_ = copyClrdHeightmap(previewPipeline_.getPayload<mbc::ColouredHeightmap>());

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


std::shared_ptr<mbc::ColouredHeightmap> PreviewWindow::copyClrdHeightmap(mbc::Payload::Ptr payload)
{
  auto copy = std::make_shared<mbc::ColouredHeightmap>();
  auto ptr = std::dynamic_pointer_cast<mbc::ColouredHeightmap>(payload);

  copy->width = ptr->width;
  copy->height = ptr->height;
  copy->colouredPoints = new uint32_t[copy->width * copy->height];

  for (int i = 0; i < copy->width * copy->height; i++)
  {
    copy->colouredPoints[i] = ptr->colouredPoints[i];
  }

  return copy;
}
