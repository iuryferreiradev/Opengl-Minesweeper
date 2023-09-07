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


void Game::init()
{
  this->setupWindow();
  ResourceManager::LoadShader("rect", "assets/shaders/quad.vert", "assets/shaders/quad.frag");
  ResourceManager::LoadShader("sprite", "assets/shaders/sprite.vert", "assets/shaders/sprite.frag");
  ResourceManager::LoadTexture("flag", "assets/images/flag_spritesheet.png");

  this->renderer.Init();

  for(int j = 0; j < ROWS; j++)
  {
    for(int i = 0; i < COLS; i++)
    {
      bool isEven = (i + j) % 2 == 0;
      glm::vec4 color = isEven ? GREEN_ONE : GREEN_TWO;
      glm::vec4 revealedColor = isEven ? BROWN_ONE : BROWN_TWO;

      float x = j * TILE_SIZE;
      float y = OFFSET_Y + i * TILE_SIZE;

      this->tiles.push_back(Tile(x, y, TILE_SIZE, TILE_SIZE, color, revealedColor));
    }
  }
}

void Game::render()
{
  // Set the clear color to white
  glClearColor(BACKGROUND.x, BACKGROUND.y, BACKGROUND.z, BACKGROUND.w);
  // Clear the window drawings
  glClear(GL_COLOR_BUFFER_BIT);

  for(Tile &tile : this->tiles)
  {
    tile.Render(this->renderer);
  }

  this->renderer.DrawRect(glm::vec2(0.0f, 0.0f), glm::vec2(SCREEN_WIDTH, OFFSET_Y), DARKGREEN);
  // flag.Render(renderer);

  for(Flag &flag : this->flags)
  {
    flag.Render(renderer);
  }
  
  // Swap the front buffer with the back buffer
  glfwSwapBuffers(window);

  // V-Sync, i think..
  glfwSwapInterval(1);
}

int actions = 1;

void Game::update(float deltaTime)
{
  Tile* hovered = nullptr;

  for(Tile &tile : this->tiles)
  {
    tile.Update(deltaTime);

    if(tile.Contains(State::Mouse))
    {
      tile.IsHovered = true;
      hovered = &tile;
    }
  }

  if(hovered)
  {
    int right_btn = glfwGetMouseButton(this->window, GLFW_MOUSE_BUTTON_RIGHT);
    if(right_btn == GLFW_PRESS && !hovered->IsRevealed && actions > 0)
    {
      this->flags.push_back(Flag(hovered->X, hovered->Y, TILE_SIZE, TILE_SIZE));
      actions = 0;
    }

    int left_btn = glfwGetMouseButton(this->window, GLFW_MOUSE_BUTTON_LEFT);
    if(left_btn == GLFW_PRESS && actions > 0)
    {
      hovered->IsRevealed = true;
      actions = 0;
    }

    if(left_btn == GLFW_RELEASE && right_btn == GLFW_RELEASE)
    {
      actions = 1;
    }
  }

  for(Flag &flag : this->flags)
  {
    flag.Update(deltaTime);
  }
}

void Game::processInputs()
{
  // Manage window events: mousemove, clicks, keyboard, resize, close...
  glfwPollEvents();
}