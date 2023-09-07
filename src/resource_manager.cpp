#include "resource_manager.hpp"

// Load static maps
std::map<std::string, Shader> ResourceManager::Shaders;
std::map<std::string, Texture2D> ResourceManager::Textures;

void ResourceManager::LoadShader(std::string name, const char* vShaderPath, const char* fShaderPath)
{
  // Get the shaders code from file
  std::string vShaderCode = File::Read(vShaderPath);
  std::string fShaderCode = File::Read(fShaderPath);

  // Create a new shader and add to the static Shader map
  Shader shader(vShaderCode.c_str(), fShaderCode.c_str());
  Shaders.insert(std::make_pair(name, shader));

  // If one of the code strings are empty the shader is not valid
  if(vShaderCode.empty() || fShaderCode.empty())
  {
    std::cout << "ERROR::RESOURCE_MANAGER::LOAD_SHADER: Could not load shader - " << name << std::endl;
  }
  else
  {
    std::cout << "Shader loaded successfully. Name: " << name << std::endl;
  }
}

Shader ResourceManager::GetShader(std::string name)
{
  // Check if the shader with the provided name exists
  auto iterator = Shaders.find(name);
  if(iterator == Shaders.end())
  {
    std::cout << "ERROR::RESOURCE_MANAGER::GET_SHADER: Shader with name: " << name << " not found!" << std::endl;
  }

  return Shaders[name];
}

void ResourceManager::LoadTexture(std::string name, const char* texturePath)
{
  int width, height, nrChannels;
  unsigned char* data = stbi_load(texturePath, &width, &height, &nrChannels, 0);
  if(data)
  {
    Texture2D texture(width, height, nrChannels, data);
    Textures[name] = texture;
    std::cout << "Texture loaded successfully. Name: " << name << std::endl;
  }
  else
  {
    std::cout << "ERROR::RESOURCE_MANAGER::LOAD_TEXTURE: Could not load texture - " << name << std::endl;
  }
}

Texture2D ResourceManager::GetTexture(std::string name)
{
  auto iterator = Textures.find(name);
  if(iterator == Textures.end())
  {
    std::cout << "ERROR::RESOURCE_MANAGER::GET_TEXTURE: Texture with name: " << name << " not found!" << std::endl;
  }
  
  return Textures[name];
}