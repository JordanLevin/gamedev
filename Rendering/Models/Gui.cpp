#include "Gui.hpp"

Gui::Gui(Camera* camera_){
  camera = camera_;
}

void Gui::add(float x,float y,float z, float xf,float yf,float zf){
  add(x,y,z,xf,yf,zf,0.5f,0.5f,0.5f);
}
void Gui::add(float x,float y,float z, float xf,float yf,float zf, 
    float r, float g, float b){
  vertices.push_back({
      {x,y,z}, {r,g,b,1}, {0,0,0}
      });
  vertices.push_back({
      {xf,yf,zf}, {r,g,b,1}, {0,0,0}
      });
}

void Gui::create(){

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
  glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), 
      (void*)(offsetof(VertexFormat, VertexFormat::color)));
  glBindVertexArray(0);
  this->vao = vao;
  this->vbos.push_back(vbo);

}

void Gui::update(){
  //if(camera->getY() > 50)
    //return;
  //vertices[0].position[0] = 0;
  //vertices[0].position[1] = 0;
  //vertices[0].position[2] = 0;
  //vertices[1].position[0] = camera->getX();
  //vertices[1].position[1] = camera->getY();
  //vertices[1].position[2] = camera->getZ();
  //vertices[0].position[0] = camera->getX();
  //vertices[0].position[1] = camera->getY();
  //vertices[0].position[2] = camera->getZ();
  //glm::vec3 dir = camera->getDirection();
  //vertices[1].position[0] = vertices[0].position[0]+dir[0];
  //vertices[1].position[1] = vertices[0].position[1]+dir[1];
  //vertices[1].position[2] = vertices[0].position[2]+dir[2];
  //vertices[1].position[0] = vertices[0].position[0]-1;
  //vertices[1].position[1] = vertices[0].position[1]-1;
  //vertices[1].position[2] = vertices[0].position[2]-1;
  //glNamedBufferSubData(vbos[0], 0, 2*sizeof(VertexFormat), (void*)&(vertices[0]));
  //create();
}

void Gui::draw(const glm::mat4& projection_matrix, const glm::mat4& view_matrix){
  glUseProgram(program);
  glUniformMatrix4fv(glGetUniformLocation(program, "view_matrix"),
      1, false, &view_matrix[0][0]);
  glUniformMatrix4fv(glGetUniformLocation(program, "projection_matrix"), 
      1, false, &projection_matrix[0][0]);
  glBindVertexArray(vao);
  glDrawArrays(GL_LINES, 0, vertices.size());
}
