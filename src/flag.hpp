#ifndef FLAG_H
#define FLAG_H

#include "renderer.hpp"
#include <vector>
#include <GLFW/glfw3.h>

class Flag
{
  public:
    float x;
    float y;
    float width;
    float height;
    Flag(float x, float y, float width, float height);
    void Render(Renderer renderer);
    void Update(float deltaTime);
  private:
    std::vector<glm::vec4> frames;
    int currentFrame;
    float animationTimer;
    bool isReverse;
};

#endif