#include "texture.hpp"

Texture2D::Texture2D(int width, int height, int nrChannels, unsigned char* data)
{
  this->Generate(width, height, nrChannels, data);
}

void Texture2D::Generate(int width, int height, int nrChannels, unsigned char* data)
{
  // Set width and height for later use
  this->Width = width;
  this->Height = height;
  // Generate texture
  glGenTextures(1, &this->ID);
  // Bind texture
  glBindTexture(GL_TEXTURE_2D, this->ID);
  // Set texture data
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
  // Setting parameters
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  // Unbind
  glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture2D::Bind()
{
  glBindTexture(GL_TEXTURE_2D, this->ID);
}