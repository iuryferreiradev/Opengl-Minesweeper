#include "tile.hpp"

Tile::Tile(float x, float y, float width, float height, glm::vec4 color, glm::vec4 revealedColor)
{
  this->X = x;
  this->Y = y;
  this->Width = width;
  this->Height = height;
  this->Color = color;
  this->IsRevealed = false;
  this->HasBomb = false;
  this->ReveladedColor = revealedColor;
  this->NeighborCount = 0;
  this->bombColor = glm::vec4(1.0f); // white
}

void Tile::Render(Renderer renderer)
{
  renderer.DrawRect(glm::vec2(this->X, this->Y), glm::vec2(this->Width, this->Height), this->IsRevealed ? this->ReveladedColor : this->Color);

  // Show hover state
  if(this->IsHovered && !this->IsRevealed && !State::isGameOver)
  {
    renderer.DrawRect(glm::vec2(this->X, this->Y), glm::vec2(this->Width, this->Height), HIGHLIGHT);
  }

  // Show bombs
  if(this->HasBomb && this->IsRevealed)
  {
    renderer.DrawSprite("bomb", glm::vec2(this->X, this->Y), glm::vec2(TILE_SIZE, TILE_SIZE), glm::vec2(0.0f), glm::vec2(TILE_SIZE, TILE_SIZE), this->bombColor);
  }

  // Show numbers
  if(!this->HasBomb && this->NeighborCount > 0 && this->IsRevealed)
  {
    Number(this->X, this->Y, TILE_SIZE, TILE_SIZE, std::to_string(this->NeighborCount), NUMBER_COLORS[this->NeighborCount -1]).Render(renderer);
  }
}

void Tile::Update(float deltaTime)
{
  this->IsHovered = false;
}

bool Tile::Contains(glm::vec2 vector)
{
  if(
    vector.x > this->X && vector.x < this->X + this->Width && // Check if the vector.x is between left and right
    vector.y > this->Y && vector.y < this->Y + this->Height   // Check if the vector.y is between top and bottom
  )
  {
    return true;
  }
  else
  {
    return false;
  }
}

void Tile::Reveal(std::vector<std::vector<Tile>>& tiles)
{
  int j = this->X / TILE_SIZE;
  int i = (this->Y - OFFSET_Y) / TILE_SIZE;

  this->IsRevealed = true;

  if(State::isGameOver)
  {
    // Change this bombs color to red
    this->bombColor = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
    // Reveal all remaining bombs
    for(int j = 0; j < ROWS; j++)
    {
      for(int i = 0; i < COLS; i++)
      {
        if(tiles[j][i].HasBomb && !tiles[j][i].HasFlag)
        {
          tiles[j][i].IsRevealed = true;
        }
      }
    }
  }

  // If the tile is not empty leave
  if(this->HasBomb || this->NeighborCount > 0)
    return;

  //Check neighbors
  // up left
  if(j - 1 >= 0 && i - 1 >= 0 && !tiles[j - 1][i - 1].IsRevealed)
    tiles[j - 1][i - -1].Reveal(tiles);
  // up
  if(i - 1 >= 0 && !tiles[j][i - 1].IsRevealed)
    tiles[j][i - 1].Reveal(tiles);
  // up right
  if(j + 1 <= ROWS - 1 && i - 1 >= 0 && !tiles[j + 1][i - 1].IsRevealed)
    tiles[j + 1][i - 1].Reveal(tiles);
  // left
  if(j - 1 >= 0 && !tiles[j - 1][i].IsRevealed)
    tiles[j - 1][i].Reveal(tiles);
  // right
  if(j + 1 <= ROWS - 1 && !tiles[j + 1][i].IsRevealed)
    tiles[j + 1][i].Reveal(tiles);
  // bottom left
  if(j - 1 >= 0 && i + 1 <= COLS - 1 && !tiles[j - 1][i + 1].IsRevealed)
    tiles[j - 1][i + 1].Reveal(tiles);
  // bottom
  if(i + 1 <= COLS - 1 && !tiles[j][i + 1].IsRevealed)
    tiles[j][i + 1].Reveal(tiles);
  // bottom right
  if(j + 1 <= ROWS - 1 && i + 1 <= COLS - 1 && !tiles[j + 1][i + 1].IsRevealed)
    tiles[j + 1][i + 1].Reveal(tiles);
}