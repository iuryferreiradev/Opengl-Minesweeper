#ifndef RENDERER_H
#define RENDERER_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <map>
#include <iostream>

#include "resource_manager.hpp"
#include "constants.hpp"

class Renderer
{
  public:
    Renderer();
    void DrawRect(glm::vec2 position, glm::vec2 size, glm::vec4 color);
  private:
    std::map<std::string, unsigned int[3]> arrays;
    void initRectData();
};

#endif