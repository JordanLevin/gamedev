#include "Cube.hpp"

#define PI 3.14159265

void Cube::create(float x, float y, float z){
  GLuint vao;
  GLuint vbo;

  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  std::vector<VertexFormat> vertices;
  //vertices for the front face of the cube
  vertices.push_back(VertexFormat(glm::vec3(-1.0+x, -1.0+y, 1.0+z),
                                  glm::vec4( 0.0,  0.0, 1.0, 1.0)));
  vertices.push_back(VertexFormat(glm::vec3(1.0+x, -1.0+y, 1.0+z),
                                  glm::vec4(1.0,  0.0, 1.0, 1.0)));
  vertices.push_back(VertexFormat(glm::vec3(1.0+x, 1.0+y, 1.0+z),
                                  glm::vec4(1.0, 1.0, 1.0, 1.0)));

  vertices.push_back(VertexFormat(glm::vec3(-1.0+x, 1.0+y, 1.0+z),
                                  glm::vec4( 0.0, 1.0, 1.0, 1.0)));
  vertices.push_back(VertexFormat(glm::vec3(1.0+x, 1.0+y, 1.0+z),
                                  glm::vec4(1.0, 1.0, 1.0, 1.0)));
  vertices.push_back(VertexFormat(glm::vec3(-1.0+x, -1.0+y, 1.0+z),
                                  glm::vec4( 0.0,  0.0, 1.0, 1.0)));

  //vertices for the right face of the cube
  vertices.push_back(VertexFormat(glm::vec3(1.0+x, 1.0+y, 1.0+z),
                                  glm::vec4(1.0, 1.0, 1.0, 1.0)));
  vertices.push_back(VertexFormat(glm::vec3(1.0+x, 1.0+y, -1.0+z),
                                  glm::vec4(1.0, 1.0,  0.0, 1.0)));
  vertices.push_back(VertexFormat(glm::vec3(1.0+x, -1.0+y, -1.0+z),
                                  glm::vec4(1.0,  0.0 , 0.0, 1.0)));

  vertices.push_back(VertexFormat(glm::vec3(1.0+x, 1.0+y, 1.0+z),
                                  glm::vec4(1.0, 1.0, 1.0, 1.0)));
  vertices.push_back(VertexFormat(glm::vec3(1.0+x, -1.0+y, -1.0+z),
                                  glm::vec4(1.0,  0.0, 0.0, 1.0)));
  vertices.push_back(VertexFormat(glm::vec3(1.0+x, -1.0+y, 1.0+z),
                                  glm::vec4(1.0,  0.0, 1.0, 1.0)));

  //vertices for the back face of the cube
  vertices.push_back(VertexFormat(glm::vec3(-1.0+x, -1.0+y, -1.0+z),
                                  glm::vec4( 0.0,  0.0,  0.0, 1.0)));
  vertices.push_back(VertexFormat(glm::vec3(1.0+x, -1.0+y, -1.0+z),
                                  glm::vec4(1.0,  0.0,  0.0, 1.0)));
  vertices.push_back(VertexFormat(glm::vec3(1.0+x, 1.0+y, -1.0+z),
                                  glm::vec4(1.0, 1.0,  0.0, 1.0)));

  vertices.push_back(VertexFormat(glm::vec3(-1.0+x, -1.0+y, -1.0+z),
                                  glm::vec4( 0.0,  0.0,  0.0, 1.0)));
  vertices.push_back(VertexFormat(glm::vec3(1.0+x, 1.0+y, -1.0+z),
                                  glm::vec4(1.0, 1.0,  0.0, 1.0)));
  vertices.push_back(VertexFormat(glm::vec3(-1.0+x, 1.0+y, -1.0+z),
                                  glm::vec4( 0.0, 1.0,  0.0, 1.0)));

 //vertices for the left face of the cube
  vertices.push_back(VertexFormat(glm::vec3(-1.0+x, -1.0+y, -1.0+z),
                                  glm::vec4( 0.0, 0.0, 0.0, 1.0)));
  vertices.push_back(VertexFormat(glm::vec3(-1.0+x, -1.0+y, 1.0+z),
                                  glm::vec4( 0.0,  0.0, 1.0, 1.0)));
  vertices.push_back(VertexFormat(glm::vec3(-1.0+x, 1.0+y, 1.0+z),
                                  glm::vec4( 0.0, 1.0, 1.0, 1.0)));

  vertices.push_back(VertexFormat(glm::vec3(-1.0+x, -1.0+y, -1.0+z),
                                  glm::vec4( 0.0,  0.0,  0.0, 1.0)));
  vertices.push_back(VertexFormat(glm::vec3(-1.0+x, 1.0+y, 1.0+z),
                                  glm::vec4( 0.0, 1.0, 1.0, 1.0)));
  vertices.push_back(VertexFormat(glm::vec3(-1.0+x, 1.0+y, -1.0+z),
                                  glm::vec4(0.0, 1.0, 0.0, 1.0)));

 //vertices for the upper face of the cube
  vertices.push_back(VertexFormat(glm::vec3(1.0+x, 1.0+y, 1.0+z),
                                  glm::vec4(1.0, 1.0, 1.0, 1.0)));
  vertices.push_back(VertexFormat(glm::vec3(-1.0+x, 1.0+y, 1.0+z),
                                  glm::vec4( 0.0, 1.0, 1.0, 1.0)));
  vertices.push_back(VertexFormat(glm::vec3(1.0+x, 1.0+y, -1.0+z),
                                  glm::vec4(1.0, 1.0,  0.0, 1.0)));

  vertices.push_back(VertexFormat(glm::vec3(-1.0+x, 1.0+y, 1.0+z),
                                  glm::vec4( 0.0, 1.0, 1.0, 1.0)));
  vertices.push_back(VertexFormat(glm::vec3(1.0+x, 1.0+y, -1.0+z),
                                  glm::vec4(1.0, 1.0,  0.0, 1.0)));
  vertices.push_back(VertexFormat(glm::vec3(-1.0+x, 1.0+y, -1.0+z),
                                    glm::vec4( 0.0, 1.0, 0.0, 1.0)));

  //vertices for the bottom face of the cube
  vertices.push_back(VertexFormat(glm::vec3(-1.0+x, -1.0+y, -1.0+z),
                                  glm::vec4( 0.0,  0.0, 0.0, 1.0)));
  vertices.push_back(VertexFormat(glm::vec3(1.0+x, -1.0+y, -1.0+z),
                                  glm::vec4(1.0,  0.0,  0.0, 1.0)));
  vertices.push_back(VertexFormat(glm::vec3(-1.0+x, -1.0+y, 1.0+z),
                                  glm::vec4( 0.0,  0.0, 1.0, 1.0)));

  vertices.push_back(VertexFormat(glm::vec3(1.0+x, -1.0+y, -1.0+z),
                                  glm::vec4(1.0,  0.0, 0.0, 1.0)));
  vertices.push_back(VertexFormat(glm::vec3(-1.0+x, -1.0+y, 1.0+z),
                                  glm::vec4( 0.0,  0.0, 1.0, 1.0)));
  vertices.push_back(VertexFormat(glm::vec3(1.0+x, -1.0+y, 1.0+z),
                                  glm::vec4(1.0,  0.0, 1.0, 1.0)));

  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);

  glBufferData(GL_ARRAY_BUFFER, sizeof(VertexFormat) * 36, &vertices[0], GL_STATIC_DRAW);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)0);
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), 
      (void*)(offsetof(VertexFormat, VertexFormat::color)));
  glBindVertexArray(0);
  this->vao = vao;
  this->vbos.push_back(vbo);

  rotation_speed = glm::vec3(90.0, 90.0, 90.0);
  rotation = glm::vec3(0.0, 0.0, 0.0);

}

void Cube::update(){

}

void Cube::draw(const glm::mat4& projection_matrix, const glm::mat4& view_matrix){
  rotation = 0.01f * rotation_speed + rotation;
  glm::vec3 rotation_sin = 
    glm::vec3(rotation.x*PI/180, rotation.y*PI/180, rotation.z*PI/180);

  glUseProgram(program);
  glUniform3f(glGetUniformLocation(program, "rotation"),
      rotation_sin.x,
      rotation_sin.y,
      rotation_sin.z);
  glUniformMatrix4fv(glGetUniformLocation(program, "view_matrix"),
      1, false, &view_matrix[0][0]);
  glUniformMatrix4fv(glGetUniformLocation(program, "projection_matrix"), 
      1, false, &projection_matrix[0][0]);
  glBindVertexArray(vao);
  glDrawArrays(GL_TRIANGLES, 0, 36);

}
