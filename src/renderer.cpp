#include "renderer.hpp"

Renderer::Renderer()
{
  this->initRectData();
}

void Renderer::DrawRect(glm::vec2 position, glm::vec2 size, glm::vec4 color)
{
  Shader shader = ResourceManager::GetShader("rect");

  glm::mat4 model = glm::mat4(1.0);
  model = glm::translate(model, glm::vec3(position, 0.0f));
  model = glm::scale(model, glm::vec3(size, 0.0f));

  glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(SCREEN_WIDTH), static_cast<float>(SCREEN_HEIGHT), 0.0f, -1.0f, 1.0f);

  shader.Use();
  shader.SetMatrix4fv("projection", projection); // set the projection uniform
  shader.SetMatrix4fv("model", model); // set the model uniform
  shader.SetVec4f("color", color); // set the color uniform

  // Bind the rect VAO
  glBindVertexArray(this->arrays["rect"][0]);
  // Draw the outline if the mode is == stroke else, draw the filled rect
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

  // Unbind
  glBindVertexArray(0);
}

void Renderer::initRectData()
{
  float vertices[] = {
    0.0f, 1.0f, // Top left
    0.0f, 0.0f, // Bottom left
    1.0f, 1.0f, // Top right
    1.0f, 0.0f  // Bottom right
  };

  unsigned int indices[] = {
    0, 1, 2, // Top left triangle
    1, 2, 3  // Bottom right triangle
  };

  unsigned int VAO, VBO, EBO;
  // Generate arrays
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);
  // Bind VAO
  glBindVertexArray(VAO);
  // Bind VBO and set data
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  // Bind EBO and set data
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
  // Setting and enabling vertex attrib data
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
  // Unbind everything
  glBindVertexArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  // Setting the rect arrays for later use
  this->arrays["rect"][0] = VAO;
  this->arrays["rect"][1] = VBO;
  this->arrays["rect"][2] = EBO;
}