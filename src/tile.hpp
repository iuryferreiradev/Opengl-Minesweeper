#ifndef TILE_H
#define TILE_H

#include <glm/glm.hpp>
#include "renderer.hpp"

class Tile
{
  public:
    float X;
    float Y;
    float Width;
    float Height;
    glm::vec4 Color;
    Tile(float x, float y, float width, float height, glm::vec4 color);
    void Render(Renderer renderer);
    void Update(float deltaTime);
};

#endif