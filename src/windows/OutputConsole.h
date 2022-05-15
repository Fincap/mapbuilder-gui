#pragma once
#include <iostream>
#include <vector>
#include <functional>

#include <imgui.h>

#include "util\functionbuf.h"


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
  std::streambuf* _oldCout;
  std::streambuf* _oldClog;
  std::streambuf* _oldCerr;

  // Captured string streams
  ofunctionstream* _coutStream;
  ofunctionstream* _clogStream;
  ofunctionstream* _cerrStream;

  // Internal string log
  std::vector<std::pair<std::string, int>> _pastOutputs;

  // Window options
  bool _autoScroll = true;

  // For converting message level to string
  const std::string MESSAGE_LEVELS[3] =
  {
    "[INFO] ",
    "[DEBUG] ",
    "[ERROR] "
  };
};