#include "CubeCluster.hpp"
#include "../../Lib/Serialize.hpp"
#include "../Mesher.hpp"

#include <string>
#include <fstream>

CubeCluster::CubeCluster(){

}

CubeCluster::CubeCluster(int chunk_x, int chunk_z){
}

CubeCluster::CubeCluster(std::string path){
  //std::fstream read;
  //read.open(path, std::ios::in);
  //Serialize::deserialize(read, allVertices);
  //Serialize::deserialize(read, allIndices);
}

uint32_t CubeCluster::getIndex(uint32_t x, uint32_t y, uint32_t z){
  return y*16*16 + x*16 + z;
}

void CubeCluster::writeChunk(std::string path){
  //std::fstream write;
  //write.open(path, std::ios::out);
  //Serialize::serialize(write, allVertices);
  //Serialize::serialize(write, allIndices);
}

void CubeCluster::create(){
  this->data = Mesher::createMesh(cubes, occupied);

  GLuint vao;
  GLuint vbo;
  //GLuint ibo;
  //GLuint nbo;

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
  //glGenBuffers(1, &nbo);
  //glBindBuffer(GL_ARRAY_BUFFER, nbo);
  //glBufferData(GL_ARRAY_BUFFER,
      //sizeof(VertexFormat) * data.size(), &data[0][0][0], GL_STATIC_DRAW);

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat),
      (void*)0);
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), 
      (void*)(offsetof(VertexFormat, VertexFormat::color)));
  //glEnableVertexAttribArray(2);
  //glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat),
      //(void*)(offsetof(VertexFormat, VertexFormat::normal)));
  glBindVertexArray(0);

  this->vao = vao;
  this->vbos.push_back(vbo);
  //this->vbos.push_back(ibo);
  //this->vbos.push_back(nbo);
}

void CubeCluster::add(int x, int y, int z){
  add(x,y,z,3);
}

void CubeCluster::add(int x, int y, int z, int type){
  //find x and z in chunk space coordinates
  int x_c = std::abs(x)%16;
  int z_c = std::abs(z)%16;
  cubes[getIndex(x_c,y,z_c)] = {x,y,z,type};
  occupied.insert(getIndex(x_c,y,z_c));
  //transform worldspace coords into chunk space
  //uint32_t x_c = x%16;
  //uint32_t z_c = z%16;
  //data[getIndex(x_c,y,z_c)].color[0] = r;
  //data[getIndex(x_c,y,z_c)].color[1] = g;
  //data[getIndex(x_c,y,z_c)].color[2] = b;
  //uint32_t p1 = y*17*17 + x_c*17 + z_c;
  //uint32_t p2 = y*17*17 + x_c*17 + z_c+1;
  //uint32_t p3 = y*17*17 + (x_c+1)*17 + z_c;
  //uint32_t p4 = y*17*17 + (x_c+1)*17 + z_c+1;
  //uint32_t p5 = (y+1)*17*17 + x_c*17 + z_c;
  //uint32_t p6 = (y+1)*17*17 + x_c*17 + z_c+1;
  //uint32_t p7 = (y+1)*17*17 + (x_c+1)*17 + z_c;
  //uint32_t p8 = (y+1)*17*17 + (x_c+1)*17 + z_c+1;

  //std::cout << "DATAZ: " << 
    //data[p1].position[2] << " " << 
    //data[p2].position[2] << " " << std::endl;

  //std::cout << x << " " << z << std::endl;
  //std::cout << x_c << " " << z_c << std::endl;

  //indices_used[getIndex(x_c,y,z_c)] = allIndices.size();

  //std::vector<unsigned int> indices = { 
    //p1, p2, p3, p2, p3, p4, //top
    //p5, p6, p7, p6, p7, p8, //bottom
    //p3, p4, p7, p4, p7, p8, //front
    //p1, p2, p5, p2, p5, p6, //back
    //p2, p4, p8, p2, p8, p6, //right
    //p1, p3, p7, p1, p7, p5}; //left

  //allIndices.insert(allIndices.end(), indices.begin(), indices.end());
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
