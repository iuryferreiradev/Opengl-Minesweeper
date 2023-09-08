#include "number.hpp"

Number::Number(float x, float y, float width, float height, std::string number, glm::vec4 color)
{
  this->x = x;
  this->y = y;
  this->width = width;
  this->height = height;
  this->number = number;
  this->color = color;
  this->hasPadding = true;
  this->sprites = {
    { '1', glm::vec4(TILE_SIZE * 0.0f, 0.0f, TILE_SIZE, TILE_SIZE) },
    { '2', glm::vec4(TILE_SIZE * 1.0f, 0.0f, TILE_SIZE, TILE_SIZE) },
    { '3', glm::vec4(TILE_SIZE * 2.0f, 0.0f, TILE_SIZE, TILE_SIZE) },
    { '4', glm::vec4(TILE_SIZE * 3.0f, 0.0f, TILE_SIZE, TILE_SIZE) },
    { '5', glm::vec4(TILE_SIZE * 4.0f, 0.0f, TILE_SIZE, TILE_SIZE) },
    { '6', glm::vec4(TILE_SIZE * 5.0f, 0.0f, TILE_SIZE, TILE_SIZE) },
    { '7', glm::vec4(TILE_SIZE * 6.0f, 0.0f, TILE_SIZE, TILE_SIZE) },
    { '8', glm::vec4(TILE_SIZE * 7.0f, 0.0f, TILE_SIZE, TILE_SIZE) },
    { '9', glm::vec4(TILE_SIZE * 8.0f, 0.0f, TILE_SIZE, TILE_SIZE) },
    { '0', glm::vec4(TILE_SIZE * 9.0f, 0.0f, TILE_SIZE, TILE_SIZE) },
  };
}

void Number::Render(Renderer renderer)
{
  float xpos = this->x;
  float xoffset = 0.0f;
  float yoffset = 0.0f;
  float woffset = 0.0f;
  float hoffset = 0.0f;

  if(!this->hasPadding)
  {
    xoffset = 5.0f;  // x would be 5.0f
    yoffset = 3.0f;  // y would be 3.0
    woffset = 10.0f; // Width would be 14
    hoffset = 5.0f;  // Height would be 18
  }

  std::string::const_iterator c;
  for(c = this->number.begin(); c != this->number.end(); c++)
  {
    glm::vec4 sprite = this->sprites[*c];
    renderer.DrawSprite("numbers", glm::vec2(xpos, this->y), glm::vec2(this->width - woffset, this->height - hoffset), glm::vec2(sprite.x + xoffset, sprite.y), glm::vec2(sprite.z - woffset, sprite.w - hoffset), this->color);
    xpos += TILE_SIZE - woffset;
  }
}