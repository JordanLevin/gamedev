#include "CubeCluster.hpp"
#include "World.hpp"
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

//With the new chunk coordinate system we shift negatives by 1 so instead of being [-16,-1]
//theyre [-15,0], this fixes an off by 1 issue with the modulus, after this we ensure coordinates
//ad in chunk space [0,15] and flip coordinates in negative chunks
glm::vec3 CubeCluster::coordsInChunk(const glm::vec3& coord){
  int x = coord[0];
  int y = coord[1];
  int z = coord[2];
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
  return glm::vec3(x,y,z);
}

uint32_t CubeCluster::getIndex(const glm::vec3& coords){
  return coords[1]*16*16 + coords[0]*16 + coords[2];
}

void CubeCluster::writeChunk(std::string path){
  std::fstream write;
  write.open(path, std::ios::out);
  Serialize::serialize(write, cubes);
  Serialize::serialize(write, occupiedVec);
}

void CubeCluster::createMesh(World* world){
  std::cout << "CREATE MESH " << d_x << " " << d_y << std::endl;
  d_world = world;
  this->data = Mesher::createMesh(cubes, occupied, world, d_x, d_z);
  d_ready = 1;
}

void CubeCluster::createGL(){
  //Cleanup buffers on remesh, well this segfaults, probably a threading issue sooo
  //if(!this->vbos.empty()){
    //this->~CubeCluster();
  //}

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
      sizeof(uint32_t) * data.size(), &data[0], GL_STATIC_DRAW);

  //Index buffer
  //glGenBuffers(1, &ibo);
  //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
  //glBufferData(GL_ELEMENT_ARRAY_BUFFER, 
      //sizeof(unsigned int) * allIndices.size(), &allIndices[0], GL_STATIC_DRAW);

  //Normal buffer
  //glGenBuffers(1, &nbo);
  //glBindBuffer(GL_ARRAY_BUFFER, nbo);
  //glBufferData(GL_ARRAY_BUFFER,
      //sizeof(uint32_t) * data.size(), &data[0], GL_STATIC_DRAW);

  glEnableVertexAttribArray(0);
  glVertexAttribIPointer(0, 1, GL_UNSIGNED_INT, sizeof(uint32_t), (void*)0);
  //glEnableVertexAttribArray(1);
  //glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(uint32_t), 
      //(void*)(offsetof(uint32_t, uint32_t::color)));
  //glEnableVertexAttribArray(2);
  //glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(uint32_t),
      //(void*)(offsetof(uint32_t, uint32_t::normal)));
  glBindVertexArray(0);

  this->vao = vao;
  this->vbos.push_back(vbo);
  //this->vbos.push_back(ibo);
  //this->vbos.push_back(nbo);
  d_ready = 2;
}

void CubeCluster::create(World* world){
  d_world = world;
  createMesh(world);
  createGL();
}

void CubeCluster::add(int x, int y, int z){
  add(x,y,z,3);
}

void CubeCluster::add(int x, int y, int z, int type){
  
  glm::vec3 coord(x,y,z);
  glm::vec3 chunk_coord = coordsInChunk(coord);

  int ind = getIndex(chunk_coord);
  cubes[ind] = {chunk_coord[0],chunk_coord[1],chunk_coord[2],type};
  occupied.insert(ind);
  occupiedVec.push_back(ind);
}

void CubeCluster::addChunkSpace(uint8_t x, uint8_t y, uint8_t z, uint8_t type){
  int ind = getIndex(glm::vec3(x,y,z));
  cubes[ind] = {x,y,z,type};
  occupied.insert(ind);
  occupiedVec.push_back(ind);
}

/**
  *
  */
void CubeCluster::remeshNeighbors(int x, int y, int z){
  //TODO
  glm::vec3 coordsC = coordsInChunk(glm::vec3(x,y,z));
  if(coordsC[0] == 15){
    CubeCluster* c = d_world->getChunkFromWorldSpace(glm::vec3(x+1,y,z));
    c->create(d_world);
  }
  if(coordsC[0] == 0){
    CubeCluster* c = d_world->getChunkFromWorldSpace(glm::vec3(x-1,y,z));
    c->create(d_world);
  }
  //if(coordsC[1] == 15){
    //CubeCluster* c = world->getChunkFromWorldSpace(x,y-1,z);
  //}
  //if(coordsC[1] == 0){
    //CubeCluster* c = world->getChunkFromWorldSpace(x,y+1,z);
  //}
  if(coordsC[2] == 15){
    CubeCluster* c = d_world->getChunkFromWorldSpace(glm::vec3(x,y,z+1));
    c->create(d_world);
  }
  if(coordsC[2] == 0){
    CubeCluster* c = d_world->getChunkFromWorldSpace(glm::vec3(x,y,z-1));
    c->create(d_world);
  }
}

bool CubeCluster::remove(int x, int y, int z){
  glm::vec3 coords = coordsInChunk(glm::vec3(x,y,z));
  std::cout << "REMOVE: " << coords[0] << " " << coords[2] << std::endl;
  int i = getIndex(coords);
  if(occupied.count(i) != 1)
    return false;
  occupied.erase(i);
  occupiedVec.erase(std::find(occupiedVec.begin(), occupiedVec.end(), i));
  this->create(d_world);
  remeshNeighbors(x,y,z);
  return true;
}

bool CubeCluster::edit(int x, int y, int z, int type){
  glm::vec3 coords = coordsInChunk(glm::vec3(x,y,z));
  int i = getIndex(coords);
  if(occupied.count(i) != 1)
    return false;
  cubes[i].type = type;
  this->create(d_world);
  remeshNeighbors(x,y,z);
  return true;
}

int CubeCluster::get(int x, int y, int z){
  glm::vec3 coords = coordsInChunk(glm::vec3(x,y,z));
  int i = getIndex(coords);
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
