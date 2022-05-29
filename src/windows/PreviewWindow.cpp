#include "PreviewWindow.h"

void PreviewWindow::showWindow(ApplicationContext& context)
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
      // TODO: this is adding a refence, need to add a copy.
      lastModules_.add(wrapper->module, 0);
      previewPipeline_.addModule(wrapper->module);
    }

    // Execute
    previewPipeline_.execute();

    // Extract generated heightmap from Pipeline
    auto payloadPtr = previewPipeline_.getPayload(std::type_index(typeid(mbc::Heightmap)));
    lastHeightmap_ = *std::dynamic_pointer_cast<mbc::Heightmap>(payloadPtr);

    // Clear pipeline
    previewPipeline_.clear();

    std::cerr << "NEW HEIGHTMAP GENERATED" << std::endl;
  }


  // 3. Add all the non-generation stage modules into the Pipeline and execute.
  // Clear stages 2 and 3
  lastModules_.getAll(1).clear();
  lastModules_.getAll(2).clear();

  // Copy manipulation stage modules across
  for (auto& manipWrapper : context.modules.getAll(1))
  {
    lastModules_.add(manipWrapper->module, 1);
    previewPipeline_.addModule(manipWrapper->module);
  }

  // Copy render stage modules across
  for (auto& renderWrapper : context.modules.getAll(2))
  {
    lastModules_.add(renderWrapper->module, 2);
    previewPipeline_.addModule(renderWrapper->module);
  }

  // Inject heightmap into pipeline
  previewPipeline_.setPayload(std::make_shared<mbc::Heightmap>(lastHeightmap_));

  // Execute
  previewPipeline_.execute();


  // 4. Draw generated payloads


}