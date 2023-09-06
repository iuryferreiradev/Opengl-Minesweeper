#include "file.hpp"

namespace fs = std::filesystem;

std::string File::Read(const char* path)
{
  std::string contents;
  try
  {
    fs::path filePath(path);
    if(!fs::exists(filePath) || !fs::is_regular_file(filePath))
    {
      std::cout << "ERROR::FILE: File not found - " << path << std::endl;
      return contents;
    }

    std::ifstream file(filePath);
    if(!file.is_open())
    {
      std::cout << "ERROR::FILE: Could not open file - " << path << std::endl;
      return contents;
    }

    std::ostringstream sstream;

    sstream << file.rdbuf();

    contents = sstream.str();
  }
  catch(const std::exception& e)
  {
    std::cerr << e.what() << std::endl;
  }

  return contents;
}