#include "OutputConsole.h"

OutputConsole::OutputConsole()
{
  // Initialise captured string streams
  std::function<void(std::string, int)> boundFunc = [this](const std::string& value, int level)
  {
    this->addToOutputs(value, level);
  };

  _coutStream = new ofunctionstream(boundFunc, 0);
  _clogStream = new ofunctionstream(boundFunc, 1);
  _cerrStream = new ofunctionstream(boundFunc, 2);

  // Redirect stdout/stderr to string streams
  _oldCout = std::cout.rdbuf(_coutStream->rdbuf());
  _oldClog = std::clog.rdbuf(_clogStream->rdbuf());
  _oldCerr = std::cerr.rdbuf(_cerrStream->rdbuf());

  // Disable automatic flushing for cerr
  // This is done to have consistency in how the output is treated by the stream
  // If this is not disabled, adding std::endl to the cerr stream will result
  // in duplicated new-lines.
  std::cerr << std::nounitbuf;
}


OutputConsole::~OutputConsole()
{
  // Delete captured string streams
  delete _coutStream;
  delete _clogStream;
  delete _cerrStream;

  // Redirect stdout/stderr back to original buffers
  std::cout.rdbuf(_oldCout);
  std::clog.rdbuf(_oldClog);
  std::cerr.rdbuf(_oldCerr);

  // Re-enable automatic flushing for cerr
  std::cerr << std::unitbuf;
}


void OutputConsole::showWindow()
{
  ImGui::Begin("Console Output");
  ImGui::BeginChild("scrolling", ImVec2(0, 0), false, ImGuiWindowFlags_HorizontalScrollbar);

  if (ImGui::Button("Clear"))
    _pastOutputs.clear();

  for (auto& [line, level] :_pastOutputs)
  {
    std::string levelText = MESSAGE_LEVELS[level];
    std::string output = levelText += line;
    ImGui::TextUnformatted(output.c_str());
  }

  ImGui::EndChild();
  ImGui::End();
}


void OutputConsole::addToOutputs(std::string const& value, int level)
{
  if (value.length() == 0)
    return;

  _pastOutputs.push_back(std::make_pair(value, level));
}
