#include "tile.hpp"

Tile::Tile(float x, float y, float width, float height, glm::vec4 color)
{
  this->X = x;
  this->Y = y;
  this->Width = width;
  this->Height = height;
  this->Color = color;
}

void Tile::Render(Renderer renderer)
{
  renderer.DrawRect(glm::vec2(this->X, this->Y), glm::vec2(this->Width, this->Height), this->Color);
}

void Tile::Update(float deltaTime)
{

}

