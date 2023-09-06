#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <map>
#include <iostream>

#include "shader.hpp"
#include "file.hpp"


class ResourceManager
{
  public:
    static std::map<std::string, Shader> Shaders;
    static void LoadShader(std::string name, const char* vShaderPath, const char* fShaderPath);
    static Shader GetShader(std::string name);
};

#endif