#pragma once
#include <iostream>
#include <vector>
#include <functional>

#include <imgui.h>

#include "util\FunctionBuffer.h"


class OutputConsole
{
public:
  OutputConsole();
  ~OutputConsole();

  // ImGui display
  void showWindow();

  // Callback for ofunctionstreams
  void addToOutputs(std::string const&, int);

private:
  // Store old buffers so that they can be reset on class destruction.
  std::streambuf* oldCout_;
  std::streambuf* oldClog_;
  std::streambuf* oldCerr_;

  // Captured string streams
  util::ofunctionstream* coutStream_;
  util::ofunctionstream* clogStream_;
  util::ofunctionstream* cerrStream_;

  // Internal string log
  std::vector<std::pair<std::string, int>> pastOutputs_;

  // Window options
  bool autoScroll_ = true;
  bool visibleLevels_[3] = {true, true, true};

  // For converting message level to string
  const std::string MESSAGE_LEVELS[3] =
  {
    "[INFO] ",
    "[DEBUG] ",
    "[ERROR] "
  };
};