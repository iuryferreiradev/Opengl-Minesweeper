#include "game.hpp"

void error_callback(int error, const char* description)
{
  std::cout << "ERROR::GLFW::CALLBACK\n" << description << std::endl;
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
}

void Game::render()
{
  // Set the clear color to white
  glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
  // Clear the window drawings
  glClear(GL_COLOR_BUFFER_BIT);
  // Swap the front buffer with the back buffer
  glfwSwapBuffers(window);
}

void Game::update(float deltaTime)
{

}

void Game::processInputs()
{
  // Manage window events: mousemove, clicks, keyboard, resize, close...
  glfwPollEvents();
}