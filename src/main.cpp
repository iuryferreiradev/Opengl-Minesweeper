#include "constants.hpp"
#include "game.hpp"

int main()
{
  Game game(SCREEN_WIDTH, SCREEN_HEIGHT, "Minesweeper");
  game.Run();
  return 0;
}
