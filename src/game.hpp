#ifndef GAME_H
#define GAME_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>

#include "resource_manager.hpp"
#include "renderer.hpp"
#include "tile.hpp"
#include "state.hpp"

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
    std::vector<Tile> tiles;
    GLFWwindow* window;
};

#endif