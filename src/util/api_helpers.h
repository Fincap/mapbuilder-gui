#pragma once

#include <MapBuilderCore.h>

const char* pipelineStageToString(mbc::PipelineStage stage)
{
  switch (stage)
  {
  case mbc::PipelineStage::GENERATION:
    return "Generation";

  case mbc::PipelineStage::MANIPULATION:
    return "Manipulation";

  case mbc::PipelineStage::RENDER:
    return "Render";

  case mbc::PipelineStage::OUTPUT:
    return "Output";

  default:
    return "";
  }
}


int pipelineStageToInt(mbc::PipelineStage stage)
{
  switch (stage)
  {
  case mbc::PipelineStage::GENERATION:
    return 1;

  case mbc::PipelineStage::MANIPULATION:
    return 2;

  case mbc::PipelineStage::RENDER:
    return 3;

  case mbc::PipelineStage::OUTPUT:
    return 4;

  default:
    return -1;
  }
}
