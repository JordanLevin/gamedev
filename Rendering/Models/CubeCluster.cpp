#include "CubeCluster.hpp"
#include "../../Lib/Serialize.hpp"
#include "../Mesher.hpp"

#include <string>
#include <fstream>

CubeCluster::CubeCluster(){
  occupiedVec.reserve(100'000);
}

CubeCluster::CubeCluster(std::string path){
  std::fstream read;
  read.open(path, std::ios::in);
  Serialize::deserialize(read, cubes);
  Serialize::deserialize(read, occupiedVec);
  occupied = std::unordered_set(occupiedVec.begin(), occupiedVec.end());
}

uint32_t CubeCluster::getIndex(uint32_t x, uint32_t y, uint32_t z){
  return y*16*16 + x*16 + z;
}

void CubeCluster::writeChunk(std::string path){
  std::fstream write;
  write.open(path, std::ios::out);
  Serialize::serialize(write, cubes);
  Serialize::serialize(write, occupiedVec);
}

void CubeCluster::create(){
  this->data = Mesher::createMesh(cubes, occupied);

  GLuint vao;
  GLuint vbo;
  //GLuint ibo;
  GLuint nbo;

  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  //Vertex buffer
  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, 
      sizeof(VertexFormat) * data.size(), &data[0], GL_STATIC_DRAW);

  //Index buffer
  //glGenBuffers(1, &ibo);
  //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
  //glBufferData(GL_ELEMENT_ARRAY_BUFFER, 
      //sizeof(unsigned int) * allIndices.size(), &allIndices[0], GL_STATIC_DRAW);

  //Normal buffer
  glGenBuffers(1, &nbo);
  glBindBuffer(GL_ARRAY_BUFFER, nbo);
  glBufferData(GL_ARRAY_BUFFER,
      sizeof(VertexFormat) * data.size(), &data[0], GL_STATIC_DRAW);

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat),
      (void*)0);
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), 
      (void*)(offsetof(VertexFormat, VertexFormat::color)));
  glEnableVertexAttribArray(2);
  glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat),
      (void*)(offsetof(VertexFormat, VertexFormat::normal)));
  glBindVertexArray(0);

  this->vao = vao;
  this->vbos.push_back(vbo);
  //this->vbos.push_back(ibo);
  this->vbos.push_back(nbo);
}

void CubeCluster::add(int x, int y, int z){
  add(x,y,z,3);
}

void CubeCluster::add(int x, int y, int z, int type){
  //find x and z in chunk space coordinates, funky math is so negative and positive chunksuse same sytem
  int cx;
  int cz;
  if(x < 0)
    cx = 15 - (-x - 1)%16;
  else
    cx = x%16;
  if(z < 0)
    cz = 15 - (-z - 1)%16;
  else
    cz = z%16;
  int ind = getIndex(cx, y, cz);
  cubes[ind] = {x,y,z,type};
  occupied.insert(ind);
  occupiedVec.push_back(ind);
}

void CubeCluster::remove(int x, int y, int z){
  //int x_c = x%16;
  //int z_c = z%16;
  //int i = indices_used[getIndex(x_c,y,z_c)];
  
}

void CubeCluster::update(){

}

void CubeCluster::draw(const glm::mat4& projection_matrix, const glm::mat4& view_matrix){
  glUseProgram(program);
  glm::vec3 light_dir = glm::normalize(glm::vec3(-1.0f, 1.0f, -1.0f));
  glUniform3f(glGetUniformLocation(program, "light_dir"),light_dir.x, light_dir.y, light_dir.z);
  glUniform4f(glGetUniformLocation(program, "light_color_in"),1.0f,1.0f,0.98f, 1.0f);
  glUniform1f(glGetUniformLocation(program, "light_power_in"),1.5f);
  glUniformMatrix4fv(glGetUniformLocation(program, "view_matrix"),
      1, false, &view_matrix[0][0]);
  glUniformMatrix4fv(glGetUniformLocation(program, "projection_matrix"), 
      1, false, &projection_matrix[0][0]);
  glBindVertexArray(vao);

  //glDrawElements(GL_TRIANGLES, allIndices.size(), GL_UNSIGNED_INT, 0);
  glDrawArrays(GL_TRIANGLES, 0, data.size());
}
