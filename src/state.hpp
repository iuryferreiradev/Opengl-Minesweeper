#ifndef STATE_H
#define STATE_H

#include "constants.hpp"

#include <glm/glm.hpp>

class State
{
  public:
    static glm::vec2 Mouse;
    static int flagCount;
    static bool isGameOver;
    static bool didWin;
};

#endif