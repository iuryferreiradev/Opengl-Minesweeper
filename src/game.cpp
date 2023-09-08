#include "game.hpp"

void error_callback(int error, const char* description)
{
  std::cout << "ERROR::GLFW::CALLBACK\n" << description << std::endl;
}

void cursor_position_callback(GLFWwindow *window, double xpos, double ypos)
{
  State::Mouse = glm::vec2(xpos, ypos);
}

Game::Game(int width, int height, const char* name)
{
  this->Height = height;
  this->Width = width;
  this->Name = name;
  this->window = nullptr;
  this->tiles = std::vector(ROWS, std::vector<Tile>(COLS));

  this->init();
}

Game::~Game()
{
  this->terminate();
}

void Game::terminate()
{
  glfwDestroyWindow(this->window);
  glfwTerminate();
}

void Game::setupWindow()
{
  glfwSetErrorCallback(error_callback);

  // Initializing window manager library
  if(!glfwInit())
  {
    std::cout << "ERROR::GLFW::INIT" << std::endl;
    this->terminate();
  }

  // Creating game window
  this->window = glfwCreateWindow(this->Width, this->Height, this->Name, NULL, NULL);
  if(!window)
  {
    std::cout << "ERROR::GLFW::WINDOW" << std::endl;
    this->terminate();
  }

  // Callback to update mouse position
  glfwSetCursorPosCallback(this->window, cursor_position_callback);

  // Setting opengl version and profile
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // Disabling window resizing
  glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

  // Make the context of the window the current context
  glfwMakeContextCurrent(window);

  // Load opengl
  if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
  {
    std::cout << "ERROR::GLAD::LOAD" << std::endl;
    this->terminate();
  }

  // Enable blending for transparency
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  glViewport(0, 0, this->Width, this->Height);
}

void Game::Run()
{
  float deltaTime = 0.0f;
  float lastTime = glfwGetTime();

  while(!glfwWindowShouldClose(this->window))
  {
    float currentTime = glfwGetTime();
    deltaTime = currentTime - lastTime;
    lastTime = currentTime;

    this->processInputs();
    this->update(deltaTime);
    this->render();
  }
}

void Game::resetGame()
{
  // Create tile grid
  for(int j = 0; j < ROWS; j++)
  {
    for(int i = 0; i < COLS; i++)
    {
      bool isEven = (i + j) % 2 == 0;
      glm::vec4 color = isEven ? GREEN_ONE : GREEN_TWO;
      glm::vec4 revealedColor = isEven ? BROWN_ONE : BROWN_TWO;

      float x = j * TILE_SIZE;
      float y = OFFSET_Y + i * TILE_SIZE;

      this->tiles[j][i] = Tile(x, y, TILE_SIZE, TILE_SIZE, color, revealedColor);
    }
  }

  // Set bombs
  int totalBombs = 40;
  while(totalBombs > 0)
  {
    std::random_device rd;
    std::mt19937 mt(rd());

    std::uniform_int_distribution<int> dist(0, 15);

    int col = dist(mt);
    int row = dist(mt);

    if(!this->tiles[col][row].HasBomb)
    {
      this->tiles[col][row].HasBomb = true;
      totalBombs--;
    }
  }

  // Calculate neighbor count
  for(int j = 0; j < ROWS; j++)
  {
    for(int i = 0; i < COLS; i++)
    {
      int bombCount = 0;
      // up left
      if(j - 1 >= 0 && i - 1 >= 0 && this->tiles[j - 1][i - 1].HasBomb)
        bombCount++;
      // up
      if(i - 1 >= 0 && this->tiles[j][i - 1].HasBomb)
        bombCount++;
      // up right
      if(j + 1 <= ROWS - 1 && i - 1 >= 0 && this->tiles[j + 1][i - 1].HasBomb)
        bombCount++;
      // left
      if(j - 1 >= 0 && this->tiles[j - 1][i].HasBomb)
        bombCount++;
      // right
      if(j + 1 <= ROWS - 1 && this->tiles[j + 1][i].HasBomb)
        bombCount++;
      // bottom left
      if(j - 1 >= 0 && i + 1 <= COLS - 1 && this->tiles[j - 1][i + 1].HasBomb)
        bombCount++;
      // bottom
      if(i + 1 <= COLS - 1 && this->tiles[j][i + 1].HasBomb)
        bombCount++;
      // bottom right
      if(j + 1 <= ROWS - 1 && i + 1 <= COLS - 1 && this->tiles[j + 1][i + 1].HasBomb)
        bombCount++;

      this->tiles[j][i].NeighborCount = bombCount;
    }
  }

  // Reset flags and timer
  this->flags = std::vector<Flag>();
}

void Game::init()
{
  this->setupWindow();
  ResourceManager::LoadShader("rect", "assets/shaders/quad.vert", "assets/shaders/quad.frag");
  ResourceManager::LoadShader("sprite", "assets/shaders/sprite.vert", "assets/shaders/sprite.frag");
  ResourceManager::LoadTexture("flag", "assets/images/flag_spritesheet.png");
  ResourceManager::LoadTexture("bomb", "assets/images/bomb.png");
  ResourceManager::LoadTexture("numbers", "assets/images/numbers.png");

  this->renderer.Init();
  this->resetGame();
}


void Game::render()
{
  // Set the clear color to white
  glClearColor(BACKGROUND.x, BACKGROUND.y, BACKGROUND.z, BACKGROUND.w);
  // Clear the window drawings
  glClear(GL_COLOR_BUFFER_BIT);

  for(int j = 0; j < ROWS; j++)
  {
    for(int i = 0; i < COLS; i++)
    {
      this->tiles[j][i].Render(renderer);
    }
  }

  this->renderer.DrawRect(glm::vec2(0.0f, 0.0f), glm::vec2(SCREEN_WIDTH, OFFSET_Y), DARKGREEN);
  // flag.Render(renderer);

  for(Flag &flag : this->flags)
  {
    flag.Render(renderer);
  }

  Flag flagIcon(24.0f, 24.0f, 24.0f, 24.0f);
  flagIcon.CurrentFrame = 11;
  Number flagCount(48.0f, 24.0f, 24.0f, 24.0f, std::to_string(State::flagCount), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
  flagCount.hasPadding = false;
  flagCount.Render(renderer);
  flagIcon.Render(renderer);
  // Swap the front buffer with the back buffer
  glfwSwapBuffers(window);

  // V-Sync, i think..
  glfwSwapInterval(1);
}

int actions = 1;

void Game::update(float deltaTime)
{
  Tile* hovered = nullptr;

  for(int j = 0; j < ROWS; j++)
  {
    for(int i = 0; i < COLS; i++)
    {
      this->tiles[j][i].Update(deltaTime);
      if(this->tiles[j][i].Contains(State::Mouse))
      {
        this->tiles[j][i].IsHovered = true;
        hovered = &this->tiles[j][i];
      }
    }
  }

  if(hovered)
  {
    Flag *currentFlag = nullptr;
    for(int i = 0; i < this->flags.size(); i++)
    {
      if(this->flags[i].x == hovered->X && this->flags[i].y == hovered->Y) 
      {
        currentFlag = &this->flags[i];
        break;
      }
    }

    // Right click - place flag
    int right_btn = glfwGetMouseButton(this->window, GLFW_MOUSE_BUTTON_RIGHT);
    if(!currentFlag && right_btn == GLFW_PRESS && !hovered->IsRevealed && actions > 0 && State::flagCount > 0)
    {
      this->flags.push_back(Flag(hovered->X, hovered->Y, TILE_SIZE, TILE_SIZE));
      State::flagCount--;
      actions = 0;
    }

    // right click - remove flag 
    if(right_btn == GLFW_PRESS && currentFlag && actions > 0)
    {
      // Remove flag from array
      currentFlag->shouldRemove = true;
      actions = 0;
    }

    // Left click reveal tile
    int left_btn = glfwGetMouseButton(this->window, GLFW_MOUSE_BUTTON_LEFT);
    if(!currentFlag && left_btn == GLFW_PRESS && actions > 0)
    {
      hovered->Reveal(this->tiles);
      actions = 0;
    }

    // Reset actions on mouse buttons release
    if(left_btn == GLFW_RELEASE && right_btn == GLFW_RELEASE)
    {
      actions = 1;
    }
  }

  for(int i = 0; i < this->flags.size(); i++)
  {
    this->flags[i].Update(deltaTime);
    if(this->flags[i].shouldRemove && this->flags[i].CurrentFrame == 0)
    {
      this->flags.erase(this->flags.begin() + i);
      State::flagCount++;
    }
  }
}

void Game::processInputs()
{
  // Manage window events: mousemove, clicks, keyboard, resize, close...
  glfwPollEvents();

  int key_f5 = glfwGetKey(this->window, GLFW_KEY_F5);
  if(key_f5 == GLFW_PRESS)
  {
    this->resetGame();
  }
}