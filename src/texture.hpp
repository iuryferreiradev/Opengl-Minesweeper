#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/glad.h>

class Texture2D
{
  public:
    unsigned int ID;
    int Width;
    int Height;
    Texture2D(){};
    Texture2D(int width, int height, int nrChannels, unsigned char* data);
    void Bind();
    void Generate(int width, int height, int nrChannels, unsigned char* data);
};

#endif