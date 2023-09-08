#include "flag.hpp"

Flag::Flag(float x, float y, float width, float height)
{
  this->x = x;
  this->y = y;
  this->width = width;
  this->height = height;
  this->frames = {
    //        x             y     w      h
    glm::vec4(TILE_SIZE * 0.0f, 0.0f, TILE_SIZE, TILE_SIZE),
    glm::vec4(TILE_SIZE * 1.0f, 0.0f, TILE_SIZE, TILE_SIZE),
    glm::vec4(TILE_SIZE * 2.0f, 0.0f, TILE_SIZE, TILE_SIZE),
    glm::vec4(TILE_SIZE * 3.0f, 0.0f, TILE_SIZE, TILE_SIZE),
    glm::vec4(TILE_SIZE * 4.0f, 0.0f, TILE_SIZE, TILE_SIZE),
    glm::vec4(TILE_SIZE * 5.0f, 0.0f, TILE_SIZE, TILE_SIZE),
    glm::vec4(TILE_SIZE * 6.0f, 0.0f, TILE_SIZE, TILE_SIZE),
    glm::vec4(TILE_SIZE * 7.0f, 0.0f, TILE_SIZE, TILE_SIZE),
    glm::vec4(TILE_SIZE * 8.0f, 0.0f, TILE_SIZE, TILE_SIZE),
    glm::vec4(TILE_SIZE * 9.0f, 0.0f, TILE_SIZE, TILE_SIZE),
    glm::vec4(TILE_SIZE * 10.0f, 0.0f, TILE_SIZE, TILE_SIZE),
    glm::vec4(TILE_SIZE * 11.0f, 0.0f, TILE_SIZE, TILE_SIZE),
  };
  this->CurrentFrame = 0;
  this->animationTimer = 0.0f;
  this->shouldRemove = false;
}

void Flag::Render(Renderer renderer)
{
  glm::vec4 frame = this->frames[this->CurrentFrame];
  renderer.DrawSprite("flag", glm::vec2(x, y), glm::vec2(width, height), glm::vec2(frame.x, frame.y), glm::vec2(frame.z, frame.w), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
}

void Flag::Update(float deltaTime)
{
  // Setup a time state
  if(glfwGetTime() > this->animationTimer + 0.006) // 6ms delay between each frame
  {
    if(!this->shouldRemove && this->CurrentFrame < this->frames.size() -1)
    {
      this->animationTimer = glfwGetTime();
      this->CurrentFrame++;
    }
    if(this->shouldRemove && this->CurrentFrame > 0)
    {
      this->animationTimer = glfwGetTime();
      this->CurrentFrame--;
    }
  }
}