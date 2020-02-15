#ifndef SHADERMANAGER_H
#define SHADERMANAGER_H

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>
#include <string>
#include <map>

class ShaderManager
{
  private:
    static std::map<std::string, GLuint> programs;

    std::string readShader(const std::string& filename);
    GLuint createShader(GLenum shaderType,
                        const std::string& source,
                        const std::string& shaderName);

  public:
    ShaderManager() = default;
    ~ShaderManager();
    void createProgram(const std::string& VertexShaderFilename,
                         const std::string& FragmentShaderFilename, 
                         const std::string& shaderName);
    static GLuint getShader(const std::string& shaderName);

};
#endif
