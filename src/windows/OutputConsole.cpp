#include "OutputConsole.h"

OutputConsole::OutputConsole()
{
  // Turn off sync with standard IO
  std::ios_base::sync_with_stdio(false);

  // Initialise captured string streams
  std::function<void(std::string, int)> boundFunc = [this](const std::string& value, int level)
  {
    this->addToOutputs(value, level);
  };

  coutStream_ = new util::ofunctionstream(boundFunc, 0);
  clogStream_ = new util::ofunctionstream(boundFunc, 1);
  cerrStream_ = new util::ofunctionstream(boundFunc, 2);

  // Redirect stdout/stderr to string streams
  oldCout_ = std::cout.rdbuf(coutStream_->rdbuf());
  oldClog_ = std::clog.rdbuf(clogStream_->rdbuf());
  oldCerr_ = std::cerr.rdbuf(cerrStream_->rdbuf());

  // Disable automatic flushing for cerr
  // This is done to have consistency in how the output is treated by the stream
  // If this is not disabled, adding std::endl to the cerr stream will result
  // in duplicated new-lines.
  std::cerr << std::nounitbuf;
}


OutputConsole::~OutputConsole()
{
  // Delete captured string streams
  delete coutStream_;
  delete clogStream_;
  delete cerrStream_;

  // Redirect stdout/stderr back to original buffers
  std::cout.rdbuf(oldCout_);
  std::clog.rdbuf(oldClog_);
  std::cerr.rdbuf(oldCerr_);

  // Re-enable automatic flushing for cerr
  std::cerr << std::unitbuf;
}


void OutputConsole::showWindow()
{
  ImGui::Begin("Output");

  // Options bar
  ImGui::Checkbox("Auto-scroll", &autoScroll_);
  ImGui::SameLine();
  if (ImGui::Button("Clear"))
    pastOutputs_.clear();

  // Filters menu
  ImGui::SameLine();
  if (ImGui::BeginPopup("Filters"))
  {
    ImGui::Checkbox("Info", &visibleLevels_[0]);
    ImGui::Checkbox("Debug", &visibleLevels_[1]);
    ImGui::Checkbox("Error", &visibleLevels_[2]);
    ImGui::EndPopup();
  }

  if (ImGui::Button("Filters"))
    ImGui::OpenPopup("Filters");

  ImGui::Separator();

  // Text output
  ImGui::BeginChild("scrolling", ImVec2(0, 0), false, ImGuiWindowFlags_HorizontalScrollbar);
  for (auto& [line, level] :pastOutputs_)
  {
    if (visibleLevels_[level])
    {
      std::string levelText = MESSAGE_LEVELS[level];
      std::string output = levelText += line;
      ImGui::TextUnformatted(output.c_str());
    }
  }

  // Auto-scroll to bottom
  if (autoScroll_ && ImGui::GetScrollY() >= ImGui::GetScrollMaxY())
    ImGui::SetScrollHereY(1.0f);

  ImGui::EndChild();
  ImGui::End();
}


void OutputConsole::addToOutputs(std::string const& value, int level)
{
  if (value.length() == 0)
    return;

  pastOutputs_.push_back(std::make_pair(value, level));
}
