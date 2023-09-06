#ifndef FILE_H
#define FILE_H

#include <iostream>
#include <filesystem>
#include <fstream>
#include <sstream>

class File
{
  public:
    static std::string Read(const char* path);
};

#endif