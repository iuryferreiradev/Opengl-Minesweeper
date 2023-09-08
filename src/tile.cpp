#include "tile.hpp"

Tile::Tile(float x, float y, float width, float height, glm::vec4 color, glm::vec4 revealedColor)
{
  this->X = x;
  this->Y = y;
  this->Width = width;
  this->Height = height;
  this->Color = color;
  this->IsRevealed = false;
  this->ReveladedColor = revealedColor;
}

void Tile::Render(Renderer renderer)
{
  renderer.DrawRect(glm::vec2(this->X, this->Y), glm::vec2(this->Width, this->Height), this->IsRevealed ? this->ReveladedColor : this->Color);

  if(this->IsHovered && !this->IsRevealed)
  {
    renderer.DrawRect(glm::vec2(this->X, this->Y), glm::vec2(this->Width, this->Height), HIGHLIGHT);
  }
}

void Tile::Update(float deltaTime)
{
  this->IsHovered = false;
}

bool Tile::Contains(glm::vec2 vector)
{
  if(
    vector.x > this->X && vector.x < this->X + this->Width && // Check if the vector.x is between left and right
    vector.y > this->Y && vector.y < this->Y + this->Height   // Check if the vector.y is between top and bottom
  )
  {
    return true;
  }
  else
  {
    return false;
  }
}