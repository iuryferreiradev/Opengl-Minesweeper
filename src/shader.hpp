#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "file.hpp"

class Shader
{
  public:
    unsigned int ProgramID;
    Shader(){};
    Shader(const char* vShaderData, const char* fShaderData);
    void Compile(const char* vShaderData, const char* fShaderData);
    void Use();
    void SetVec4f(const char* name, glm::vec4 value);
    void SetVec3f(const char* name, glm::vec3 value);
    void SetMatrix4fv(const char* name, glm::mat4 matrix);
  private:
    void printErrors(unsigned int id, const char* type);
};

#endif