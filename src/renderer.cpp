#include "renderer.hpp"

void Renderer::Init()
{
  this->initRectData();
  this->initSpriteData();
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

void Renderer::DrawSprite(std::string name, glm::vec2 position, glm::vec2 size)
{
  this->DrawSprite(name, position, size, glm::vec2(0.0f), size, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
}

void Renderer::DrawSprite(std::string name, glm::vec2 position, glm::vec2 size, glm::vec2 location)
{
  this->DrawSprite(name, position, size, location, size, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
}

void Renderer::DrawSprite(std::string name, glm::vec2 position, glm::vec2 size, glm::vec2 location, glm::vec2 dimension, glm::vec4 color)
{
  Texture2D texture = ResourceManager::GetTexture(name);

  float sheetWidth = texture.Width;
  float sheetHeight = texture.Height;

  float vertices[] = {
    0.0f, 1.0f, location.x / sheetWidth, (location.y + dimension.y) / sheetHeight, // Top left
    0.0f, 0.0f, location.x / sheetWidth, location.y / sheetHeight, // Bottom0.0f, 1.0f, 0.0f, 1.0f, // Top left
    1.0f, 1.0f, (location.x + dimension.x) / sheetWidth, (location.y + dimension.y) / sheetHeight, // Top right
    1.0f, 0.0f, (location.x + dimension.x) / sheetWidth, location.y / sheetHeight  // Bottom right
  };

  // Bind vertex array
  glBindVertexArray(this->arrays["sprite"][0]);
  // Bind VBO and set vertices data
  glBindBuffer(GL_ARRAY_BUFFER, this->arrays["sprite"][1]);
  glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
  // Translate and scale
  glm::mat4 model = glm::mat4(1.0f);
  model = glm::translate(model, glm::vec3(position, 0.0f));
  model = glm::scale(model, glm::vec3(size, 0.0f));
  // 2D projection
  glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(SCREEN_WIDTH), static_cast<float>(SCREEN_HEIGHT), 0.0f, -1.0f, 1.0f);
  Shader shader = ResourceManager::GetShader("sprite");
  // Use the shader program
  shader.Use();
  shader.SetMatrix4fv("model", model);
  shader.SetMatrix4fv("projection", projection);

  shader.SetVec4f("color", color);
  // Bind the texture
  texture.Bind();
  // Draw the sprite
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
  // Unbind
  glBindVertexArray(0);
  glBindTexture(GL_TEXTURE_2D, 0);
}

void Renderer::initSpriteData()
{
  unsigned int VAO, VBO, EBO;

  float vertices[] = {
    0.0f, 1.0f, 0.0f, 1.0f, // Top left
    0.0f, 0.0f, 0.0f, 0.0f, // Bottom left
    1.0f, 1.0f, 1.0f, 1.0f, // Top right
    1.0f, 0.0f, 1.0f, 0.0f  // Bottom right
  };

  unsigned int indices[] = {
    0, 1, 2, // Top left triangle
    1, 2, 3  // Bottom right triangle
  };
  // Generate arrays
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);
  // Bind vertex array
  glBindVertexArray(VAO);
  // Bind and set array buffer data
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
  // Bind and set element array buffer data
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
  // Set and enable vertex attrib data
  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
  // Unbind arrays
  glBindVertexArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  // Set the sprite arrays for later use
  this->arrays["sprite"][0] = VAO;
  this->arrays["sprite"][1] = VBO;
  this->arrays["sprite"][2] = EBO;
}