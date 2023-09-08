#ifndef GAME_H
#define GAME_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <random>

#include "resource_manager.hpp"
#include "renderer.hpp"
#include "tile.hpp"
#include "state.hpp"
#include "flag.hpp"
#include "number.hpp"

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
    void resetGame();
    Renderer renderer;
    std::vector<std::vector<Tile>> tiles;
    std::vector<Flag> flags;
    GLFWwindow* window;
};

#endif