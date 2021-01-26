#include "CubeCluster.hpp"
#include "../../Lib/Serialize.hpp"
#include "../Mesher.hpp"

#include <string>
#include <fstream>
#include <algorithm>
#include <time.h>

CubeCluster::CubeCluster(int x, int y, int z){
  d_x = x;
  d_y = y;
  d_z = z;
  occupiedVec.reserve(DATA_SIZE);
  model_matrix = 
   {{1,0,0,0}, 
    {0,1,0,0}, 
    {0,0,1,0}, 
    {x*16,0,z*16,1}};
}


CubeCluster::CubeCluster(std::string path, int x, int y, int z){
  d_x = x;
  d_y = y;
  d_z = z;
  model_matrix = 
   {{1,0,0,0}, 
    {0,1,0,0}, 
    {0,0,1,0}, 
    {x*16,0,z*16,1}};
  std::fstream read;
  read.open(path, std::ios::in);
  Serialize::deserialize(read, cubes);
  Serialize::deserialize(read, occupiedVec);
  occupied = std::unordered_set(occupiedVec.begin(), occupiedVec.end());
}

CubeCluster::~CubeCluster(){
  glDeleteBuffers(this->vbos.size(), this->vbos.data());
  glDeleteVertexArrays(1, &(this->vao));
}

glm::vec3 CubeCluster::coordsInChunk(int x, int y, int z){
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
  return glm::vec3(cx,y,cz);
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

void CubeCluster::createMesh(){
  this->data = Mesher::createMesh(cubes, occupied);
  d_ready = 1;
}

void CubeCluster::createGL(){
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
  d_ready = 2;
}

void CubeCluster::create(){
  createMesh();
  createGL();
}

void CubeCluster::add(int x, int y, int z){
  add(x,y,z,3);
}

void CubeCluster::add(int x, int y, int z, int type){
  
  //With the new chunk coordinate system we shift negatives by 1 so instead of being [-16,-1]
  //theyre [-15,0], this fixes an off by 1 issue with the modulus, after this we ensure coordinates
  //ad in chunk space [0,15] and flip coordinates in negative chunks
  //We also add 0.5 so chunk corners are on integers, this hopefully will reduce other issues
  if(d_x < 0){
    x += 1;
    x = 15 - std::abs(x%16);
  }
  else
    x = std::abs(x%16);
  if(d_z < 0){
    z += 1;
    z = 15 - std::abs(z%16);
  }
  else
    z = std::abs(z%16);
  //y = std::abs(y%16);

  int ind = getIndex(x, y, z);
  cubes[ind] = {(float)x+0.5,(float)y+0.5,(float)z+0.5,type};
  occupied.insert(ind);
  occupiedVec.push_back(ind);
}

bool CubeCluster::remove(int x, int y, int z){
  glm::vec3 coords = coordsInChunk(x,y,z);
  int i = getIndex(coords[0],coords[1],coords[2]);
  if(occupied.count(i) != 1)
    return false;
  occupied.erase(i);
  occupiedVec.erase(std::find(occupiedVec.begin(), occupiedVec.end(), i));
  this->create();
  return true;
}

bool CubeCluster::edit(int x, int y, int z, int type){
  glm::vec3 coords = coordsInChunk(x,y,z);
  int i = getIndex(coords[0],coords[1],coords[2]);
  if(occupied.count(i) != 1)
    return false;
  cubes[i].type = type;
  this->create();
  return true;
}

int CubeCluster::get(int x, int y, int z){
  glm::vec3 coords = coordsInChunk(x,y,z);
  int i = getIndex(coords[0],coords[1],coords[2]);
  if(occupied.count(i) != 1)
    return 0;
  return 1;
}

void CubeCluster::update(){

}

void CubeCluster::draw(const glm::mat4& projection_matrix, const glm::mat4& view_matrix){
  //model_matrix[1][0] = std::sin((float)n++/100.0); //lmao just for fun
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
  //print_m(model_matrix);

  //glDrawElements(GL_TRIANGLES, allIndices.size(), GL_UNSIGNED_INT, 0);
  glUniform1i(glGetUniformLocation(program, "wireframe"),0);
  glDrawArrays(GL_TRIANGLES, 0, data.size());
}
