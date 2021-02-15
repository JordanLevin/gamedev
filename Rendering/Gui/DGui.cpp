#include "DGui.hpp"


void DGui::add(float x,float y,float z, float xf,float yf,float zf){
  add(x,y,z,xf,yf,zf,0.5f,0.5f,0.5f);
}
void DGui::add(float x,float y,float z, float xf,float yf,float zf, 
    float r, float g, float b){
  vertices.push_back({{x,y,z}, {r,g,b,1}, {0,0,0}});
  vertices.push_back({{xf,yf,zf}, {r,g,b,1}, {0,0,0}});
}


void DGui::create(){
  GLuint vao;
  GLuint vbo;

  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);

  glBufferData(GL_ARRAY_BUFFER, sizeof(VertexFormat) * vertices.size(), &vertices[0], GL_DYNAMIC_DRAW);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)0);
  glEnableVertexAttribArray(1);
  //glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), 
      //(void*)(offsetof(VertexFormat, VertexFormat::color)));
  glBindVertexArray(0);
  this->vao = vao;
  this->vbos.push_back(vbo);

}

void DGui::update(){
}

void DGui::draw(const glm::mat4& projection_matrix, const glm::mat4& view_matrix){
  glUseProgram(program);
  glUniformMatrix4fv(glGetUniformLocation(program, "view_matrix"),
      1, false, &view_matrix[0][0]);
  glUniformMatrix4fv(glGetUniformLocation(program, "projection_matrix"), 
      1, false, &projection_matrix[0][0]);
  glBindVertexArray(vao);
  glDrawArrays(GL_LINES, 0, vertices.size());
}
