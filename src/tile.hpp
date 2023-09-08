#ifndef TILE_H
#define TILE_H

#include <glm/glm.hpp>

#include "renderer.hpp"
#include "state.hpp"

class Tile
{
  public:
    float X;
    float Y;
    float Width;
    float Height;
    bool IsHovered;
    glm::vec4 Color;
    glm::vec4 ReveladedColor;
    bool IsRevealed;
    bool HasBomb;
    Tile(){};
    Tile(float x, float y, float width, float height, glm::vec4 color, glm::vec4 revealedColor);
    void Render(Renderer renderer);
    void Update(float deltaTime);
    bool Contains(glm::vec2 vector);
  private:
    int neighborCount;
};

#endif