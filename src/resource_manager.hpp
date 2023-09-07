#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <map>
#include <iostream>
#include <stb/stb_image.h>

#include "shader.hpp"
#include "file.hpp"
#include "texture.hpp"

class ResourceManager
{
  public:
    static std::map<std::string, Shader> Shaders;
    static std::map<std::string, Texture2D> Textures;
    static void LoadShader(std::string name, const char* vShaderPath, const char* fShaderPath);
    static Shader GetShader(std::string name);
    static void LoadTexture(std::string name, const char* texturePath);
    static Texture2D GetTexture(std::string name);
};

#endif