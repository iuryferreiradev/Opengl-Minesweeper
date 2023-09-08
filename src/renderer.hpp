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
    Renderer(){};
    void DrawRect(glm::vec2 position, glm::vec2 size, glm::vec4 color);
    void DrawSprite(std::string name, glm::vec2 position, glm::vec2 size);
    void DrawSprite(std::string name, glm::vec2 position, glm::vec2 size, glm::vec2 location);
    void DrawSprite(std::string name, glm::vec2 position, glm::vec2 size, glm::vec2 location, glm::vec2 dimension, glm::vec4 color);
    void Init();
  private:
    std::map<std::string, unsigned int[3]> arrays;
    void initRectData();
    void initSpriteData();
};

#endif