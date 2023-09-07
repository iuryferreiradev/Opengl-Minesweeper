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
  renderer.DrawRect(glm::vec2(this->X, this->Y), glm::vec2(this->Width, this->Height), !this->isHovered ? this->Color : HIGHLIGHT);
}

void Tile::Update(float deltaTime)
{
  if(
    State::Mouse.x > this->X && State::Mouse.x < this->X + this->Width && // Check if the mouse is between left and right
    State::Mouse.y > this->Y && State::Mouse.y < this->Y + this->Height   // Check if the mouse is between top and bottom
  )
  {
    this->isHovered = true;
  }
  else
  {
    this->isHovered = false;
  }
}

