#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

const int WIDTH = 800, HEIGHT = 600;

void error_callback(int error, const char* description)
{
  std::cout << "ERROR::GLFW::CALLBACK\n" << description << std::endl;
}

int main()
{
  glfwSetErrorCallback(error_callback);

  // Initializing window manager library
  if(!glfwInit())
  {
    std::cout << "ERROR::GLFW::INIT" << std::endl;
    return -1;
  }

  // Creating game window
  GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Minesweeper", NULL, NULL);
  if(!window)
  {
    std::cout << "ERROR::GLFW::WINDOW" << std::endl;
    return -1;
  }

  // Setting opengl version and profile
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // Disabling window resizing
  glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

  // Make the context of the window the current context
  glfwMakeContextCurrent(window);

  // Load opengl
  if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
  {
    std::cout << "ERROR::GLAD::LOAD" << std::endl;
    return -1;
  }

  glViewport(0, 0, WIDTH, HEIGHT);

  // Main loop
  while(!glfwWindowShouldClose(window))
  {
    // Manage window events: mousemove, clicks, keyboard, resize, close...
    glfwPollEvents();

    // Set the clear color to white
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    // Clear the window drawings
    glClear(GL_COLOR_BUFFER_BIT);

    // Swap the front buffer with the back buffer
    glfwSwapBuffers(window);
  }


  // Cleanup
  glfwDestroyWindow(window);
  glfwTerminate();

  return 0;
}
