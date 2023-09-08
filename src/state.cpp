#include "state.hpp"

glm::vec2 State::Mouse = glm::vec2(0.0f);
int State::flagCount = BOMB_AMOUNT;
bool State::isGameOver = false;
bool State::didWin = false;