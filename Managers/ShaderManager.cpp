#include "ShaderManager.hpp"

#include <GL/glew.h>
#include <GL/freeglut.h>

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <filesystem>

std::map<std::string, GLuint> ShaderManager::programs; //static definition

std::string ShaderManager::readShader(const std::string& filename){
  std::string shaderCode;
  std::string path = std::string("Shaders/") + filename;
  std::ifstream file { path };
  if(!file)
  {
    std::cout<<"Can't read file "<<filename<<std::endl;
    std::cout << "Path: " << std::filesystem::absolute(path) << std::endl;
    std::cout << "fs cur wd path: " << std::filesystem::current_path() << std::endl;
    std::terminate();
  }

  file.seekg(0, std::ios::end);
  shaderCode.resize((unsigned int)file.tellg());
  file.seekg(0, std::ios::beg);
  file.read(&shaderCode[0], shaderCode.size());
  file.close();
  return shaderCode;
}

GLuint ShaderManager::createShader(GLenum shaderType, const std::string& source, 
    const std::string& shaderName){
  int compile_result = 0;

  GLuint shader = glCreateShader(shaderType);
  const char* shader_code_ptr = source.c_str();
  const int shader_code_size = source.size();

  glShaderSource(shader, 1, &shader_code_ptr, &shader_code_size);
  glCompileShader(shader);
  glGetShaderiv(shader, GL_COMPILE_STATUS, &compile_result);

  //check for errors
  if (compile_result == GL_FALSE)
  {

    int info_log_length = 0;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &info_log_length);
    std::vector<char> shader_log(info_log_length);
    glGetShaderInfoLog(shader, info_log_length, NULL, &shader_log[0]);
    std::cout << "ERROR compiling shader: " << shaderName << std::endl << &shader_log[0] << std::endl;
    return 0;
  }
  return shader;
}

void ShaderManager::createProgram(const std::string& vertexShaderFilename,
    const std::string& fragmentShaderFilename, const std::string& shaderName){
  //read the shader files and save the code
  std::string vertex_shader_code = readShader(vertexShaderFilename.c_str());
  std::string fragment_shader_code = readShader(fragmentShaderFilename.c_str());

  GLuint vertex_shader = createShader(GL_VERTEX_SHADER, vertex_shader_code, "vertex shader");
  GLuint fragment_shader = createShader(GL_FRAGMENT_SHADER, fragment_shader_code, "fragment shader");

  //create the program handle, attatch the shaders and link it
  GLuint program = glCreateProgram();
  glAttachShader(program, vertex_shader);
  glAttachShader(program, fragment_shader);

  int link_result = 0;
  glLinkProgram(program);
  glGetProgramiv(program, GL_LINK_STATUS, &link_result);
  //check for link errors
  if (link_result == GL_FALSE)
  {

    int info_log_length = 0;
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &info_log_length);
    std::vector<char> program_log(info_log_length);
    glGetProgramInfoLog(program, info_log_length, NULL, &program_log[0]);
    std::cout << "Shader Manager : LINK ERROR" << std::endl << &program_log[0] << std::endl;
    return;
  }
  programs[shaderName] = program;
}

GLuint ShaderManager::getShader(const std::string& shaderName){
  return programs[shaderName];
}

ShaderManager::~ShaderManager(){
  for(auto it = programs.begin(); it != programs.end(); it++){
    glDeleteProgram(it->second);
  }
  programs.clear();
}
