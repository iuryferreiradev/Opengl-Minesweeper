#include "flag.hpp"

Flag::Flag(float x, float y, float width, float height)
{
  this->x = x;
  this->y = y;
  this->width = width;
  this->height = height;
  this->frames = {
    //        x             y     w      h
    glm::vec4(24.0f * 0.0f, 0.0f, 24.0f, 24.0f),
    glm::vec4(24.0f * 1.0f, 0.0f, 24.0f, 24.0f),
    glm::vec4(24.0f * 2.0f, 0.0f, 24.0f, 24.0f),
    glm::vec4(24.0f * 3.0f, 0.0f, 24.0f, 24.0f),
    glm::vec4(24.0f * 4.0f, 0.0f, 24.0f, 24.0f),
    glm::vec4(24.0f * 5.0f, 0.0f, 24.0f, 24.0f),
    glm::vec4(24.0f * 6.0f, 0.0f, 24.0f, 24.0f),
    glm::vec4(24.0f * 7.0f, 0.0f, 24.0f, 24.0f),
    glm::vec4(24.0f * 8.0f, 0.0f, 24.0f, 24.0f),
    glm::vec4(24.0f * 9.0f, 0.0f, 24.0f, 24.0f),
    glm::vec4(24.0f * 10.0f, 0.0f, 24.0f, 24.0f),
    glm::vec4(24.0f * 11.0f, 0.0f, 24.0f, 24.0f),
  };
  this->currentFrame = 0;
  this->animationTimer = 0.0f;
}

void Flag::Render(Renderer renderer)
{
  glm::vec4 frame = this->frames[this->currentFrame];
  renderer.DrawSprite("flag", glm::vec2(x, y), glm::vec2(width, height), glm::vec2(frame.x, frame.y), glm::vec2(frame.z, frame.w));
}

void Flag::Update(float deltaTime)
{
  // Setup a time state
  if(glfwGetTime() > this->animationTimer + 0.060) // 60ms delay between each frame
  {
    if(this->currentFrame < this->frames.size() -1)
    {
      this->animationTimer = glfwGetTime();
      this->currentFrame++;
    }
  }
}