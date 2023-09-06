#ifndef GAME_H
#define GAME_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "resource_manager.hpp"

class Game
{
  public:
    int Width;
    int Height;
    const char* Name;
    Game(int width, int height, const char* name);
    ~Game();
    void Run();
  private:
    void init();
    void update(float deltaTime);
    void render();
    void setupWindow();
    void processInputs();
    void terminate();
    GLFWwindow* window;
};

#endif