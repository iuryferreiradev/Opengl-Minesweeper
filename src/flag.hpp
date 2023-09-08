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
    bool shouldRemove;
    int CurrentFrame;
    Flag(float x, float y, float width, float height);
    void Render(Renderer renderer);
    void Update(float deltaTime);
  private:
    std::vector<glm::vec4> frames;
    float animationTimer;
    bool isReverse;
};

#endif