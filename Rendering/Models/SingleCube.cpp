#include "SingleCube.hpp"
#include "../Mesher.hpp"

#include <string>
#include <algorithm>

void SingleCube::create(){
  this->data = Mesher::createMesh({cube}, {0});

  GLuint vao;
  GLuint vbo;
  GLuint nbo;

  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  //Vertex buffer
  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, 
      sizeof(VertexFormat) * data.size(), &data[0], GL_STATIC_DRAW);

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat),
      (void*)0);
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), 
      (void*)(offsetof(VertexFormat, VertexFormat::color)));
  glBindVertexArray(0);

  this->vao = vao;
  this->vbos.push_back(vbo);
}

void SingleCube::set(int x, int y, int z){
  cube = {x+0.5,y+0.5,z+0.5,4};
  //std::vector<Cube> outline;
  //std::unordered_set<int> occ{1};
  //outline.push_back({x,y,z,-1});
  //this->selectedCube = Mesher::createMesh(outline, occ);
}

void SingleCube::update(){

}

void SingleCube::draw(const glm::mat4& projection_matrix, const glm::mat4& view_matrix){
  glm::mat4 model_matrix = {
    {1,0,0,0},
    {0,1,0,0},
    {0,0,1,0},
    {0,0,0,1}
  };
  glUseProgram(program);
  glm::vec3 light_dir = glm::normalize(glm::vec3(-1.0f, 1.0f, -1.0f));
  glUniform3f(glGetUniformLocation(program, "light_dir"),light_dir.x, light_dir.y, light_dir.z);
  glUniform4f(glGetUniformLocation(program, "light_color_in"),1.0f,1.0f,0.98f, 1.0f);
  glUniform1f(glGetUniformLocation(program, "light_power_in"),1.5f);
  glUniformMatrix4fv(glGetUniformLocation(program, "model_matrix"),
      1, false, &model_matrix[0][0]);
  glUniformMatrix4fv(glGetUniformLocation(program, "view_matrix"),
      1, false, &view_matrix[0][0]);
  glUniformMatrix4fv(glGetUniformLocation(program, "projection_matrix"), 
      1, false, &projection_matrix[0][0]);
  glBindVertexArray(vao);

  glDisable(GL_DEPTH_TEST);
  glUniform1i(glGetUniformLocation(program, "wireframe"),1);
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  glDrawArrays(GL_TRIANGLES, 0, data.size());
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  glEnable(GL_DEPTH_TEST);
}
