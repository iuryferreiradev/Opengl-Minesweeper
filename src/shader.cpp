#include "shader.hpp"

Shader::Shader(const char* vShaderData, const char* fShaderData)
{
  this->Compile(vShaderData, fShaderData);
}

void Shader::Compile(const char* vShaderData, const char* fShaderData)
{
  unsigned int vShader, fShader;
  vShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vShader, 1, &vShaderData, NULL);
  glCompileShader(vShader);

  fShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fShader, 1, &fShaderData, NULL);
  glCompileShader(fShader);
  this->printErrors(fShader, "FRAGMENT");

  this->ProgramID = glCreateProgram();
  glAttachShader(this->ProgramID, vShader);
  glAttachShader(this->ProgramID, fShader);
  glLinkProgram(this->ProgramID);
  this->printErrors(this->ProgramID, "PROGRAM");

  glDeleteShader(vShader);
  glDeleteShader(fShader);
}

void Shader::Use()
{
  glUseProgram(this->ProgramID);
}


void Shader::SetVec3f(const char* name, glm::vec3 value)
{
  this->Use();
  glUniform3f(glGetUniformLocation(this->ProgramID, name), value.x, value.y, value.z);
}

void Shader::SetVec4f(const char* name, glm::vec4 value)
{
  this->Use();
  glUniform4f(glGetUniformLocation(this->ProgramID, name), value.x, value.y, value.z, value.w);
}

void Shader::SetMatrix4fv(const char* name, glm::mat4 matrix)
{
  this->Use();
  glUniformMatrix4fv(glGetUniformLocation(this->ProgramID, name), 1, false, glm::value_ptr(matrix));
}


void Shader::printErrors(unsigned int id, const char* type)
{
  int success;
  char infoLog[1024];

  if(type == "PROGRAM")
  {
    glGetProgramiv(id, GL_LINK_STATUS, &success);
    if(!success)
    {
      glGetProgramInfoLog(id, sizeof(infoLog), NULL, infoLog);
      std::cout << "ERROR::SHADER::" << type << std::endl << infoLog << std::endl;
    }

    return;
  }

  glGetShaderiv(id, GL_COMPILE_STATUS, &success);
  if(!success)
  {
    glGetShaderInfoLog(id, sizeof(infoLog), NULL, infoLog);
    std::cout << "ERROR::SHADER::" << type << std::endl << infoLog << std::endl;
  }
}