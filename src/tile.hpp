#ifndef TILE_H
#define TILE_H

#include "renderer.hpp"
#include "state.hpp"
#include "number.hpp"
#include "flag.hpp"

#include <glm/glm.hpp>
#include <vector>


class Tile
{
  public:
    float X;
    float Y;
    float Width;
    float Height;
    bool IsHovered;
    bool IsRevealed;
    bool HasBomb;
    bool HasFlag;
    int NeighborCount;
    glm::vec4 Color;
    glm::vec4 ReveladedColor;
    Tile(){};
    Tile(float x, float y, float width, float height, glm::vec4 color, glm::vec4 revealedColor);
    void Render(Renderer renderer);
    void Update(float deltaTime);
    bool Contains(glm::vec2 vector);
    void Reveal(std::vector<std::vector<Tile>>& tiles);
  private:
    glm::vec4 bombColor;
};

#endif