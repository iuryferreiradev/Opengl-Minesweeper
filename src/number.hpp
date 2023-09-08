#ifndef NUMBER_H
#define NUMBER_H

#include <glm/glm.hpp>
#include <iostream>
#include <map>

#include "renderer.hpp"

class Number
{
  public:
    float x;
    float y;
    float width;
    float height;
    bool hasPadding;
    std::string number;
    glm::vec4 color;
    Number(float x, float y, float width, float height, std::string number, glm::vec4 color);
    void Render(Renderer renderer);
    void Update(float deltaTime);
  private:
    std::map<char, glm::vec4> sprites;
};

#endif