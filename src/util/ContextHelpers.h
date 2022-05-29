#pragma once
#include <filesystem>

#include <cereal\cereal.hpp>
#include <cereal\archives\xml.hpp>

#include "app\ApplicationContext.h"
#include "util\FileDialogHelpers.h"

namespace util
{
  inline void loadFileIntoContext(ApplicationContext& context)
  {
    std::filesystem::path openedFile;
    char buffer[MBC_MAX_PATH] = { 0 };
    getOpenFilepathWIN32(buffer, L"MapBuilder File (*.mbc)\0*.mbc\0");
    openedFile = buffer;

    if (openedFile.empty())   // If no filepath was selected, exit early
    {
      return;
    }

    // Deserialize
    {
      std::ifstream is(openedFile);

      cereal::XMLInputArchive archive(is);
      try {
        archive(context.modules);
      }
      catch (cereal::Exception)
      {
        std::cerr << "Could not open selected file\n";
        return;
      }
    }

    // Clean up
    context.filename = openedFile;
    context.isUnsaved = false;
    context.pipeline.clear();
  }


  inline void saveContextIntoFile(ApplicationContext& context, bool newPath = false)
  {
    if (newPath || context.filename.empty())
    {
      // Open Save file dialog
      char buffer[MBC_MAX_PATH] = { 0 };
      getSaveFilepathWIN32(buffer, L"MapBuilder File (*.mbc)\0*.mbc\0", L"mbc");
      if (buffer[0] == '\0')  // If "Cancel" in file dialog pressed, exit early.
        return;
      context.filename = buffer;
    }

    // Serialize 
    {
      std::ofstream os(context.filename);
      if (!os.is_open())
      {
        std::cerr << "Could not save to selected file\n";
        return;
      }

      cereal::XMLOutputArchive archive(os);
      archive(context.modules);
    }

    // Clean up
    context.isUnsaved = false;
  }
}