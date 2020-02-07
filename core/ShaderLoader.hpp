#ifndef SHADERLOADER_H
#define SHADERLOADER_H

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>
#include <string>

class ShaderLoader
{
  private:
    std::string ReadShader(const char *filename);
    GLuint CreateShader(GLenum shaderType,
        std::string source,
        const char* shaderName);

  public:
    ShaderLoader() = default;
    ~ShaderLoader() = default;
    GLuint CreateProgram(const char* VertexShaderFilename,
        const char* FragmentShaderFilename);

};
#endif
