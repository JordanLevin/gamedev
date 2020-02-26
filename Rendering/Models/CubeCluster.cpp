#include "CubeCluster.hpp"
#include "../../Lib/Serialize.hpp"

#include <string>
#include <fstream>

CubeCluster::CubeCluster(){
}

CubeCluster::CubeCluster(std::string path){
  std::fstream read{path};
  Serialize::deserialize(read, allVertices);
  Serialize::deserialize(read, allIndices);
  
}

void CubeCluster::writeChunk(std::string path){
  std::fstream write{path};
  Serialize::serialize(write, allVertices);
  Serialize::serialize(write, allIndices);
}

void CubeCluster::create(){
  GLuint vao;
  GLuint vbo;
  GLuint ibo;

  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, 
      sizeof(VertexFormat) * allVertices.size(), &allVertices[0], GL_STATIC_DRAW);

  glGenBuffers(1, &ibo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, 
      sizeof(unsigned int) * allIndices.size(), &allIndices[0], GL_STATIC_DRAW);

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)0);
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), 
      (void*)(offsetof(VertexFormat, VertexFormat::color)));
  glBindVertexArray(0);

  this->vao = vao;
  this->vbos.push_back(vbo);
  this->vbos.push_back(ibo);
}

void CubeCluster::add(float x, float y, float z){
  add(x,y,z, 0.5, 0.5, 0.5);
}

void CubeCluster::add(float x, float y, float z, float r, float g, float b){
  unsigned int s = allVertices.size();
  std::vector<unsigned int> indices = { 
      0+s, 1+s, 2+s, 0+s, 2+s, 3+s, //front
      4+s, 5+s, 6+s, 4+s, 6+s, 7+s, //right
      8+s, 9+s, 10+s, 8+s, 10+s, 11+s, //back
      12+s, 13+s, 14+s, 12+s, 14+s, 15+s, //left
      16+s, 17+s, 18+s, 16+s, 18+s, 19+s, //upper
      20+s, 21+s, 22+s, 20+s, 22+s, 23+s}; //bottom
  allIndices.insert(allIndices.end(), indices.begin(), indices.end());

  std::vector<VertexFormat> vertices;
  //front
  vertices.push_back(VertexFormat(glm::vec3(-1.0+x, -1.0+y, 1.0+z),
                                  glm::vec4(r, g, b, 1)));
  vertices.push_back(VertexFormat(glm::vec3( 1.0+x, -1.0+y, 1.0+z),
                                  glm::vec4(r, g, b, 1)));
  vertices.push_back(VertexFormat(glm::vec3( 1.0+x, 1.0+y, 1.0+z),
                                  glm::vec4(r, g, b, 1)));
  vertices.push_back(VertexFormat(glm::vec3(-1.0+x, 1.0+y, 1.0+z),
                                  glm::vec4(r, g, b, 1)));

  //right
  vertices.push_back(VertexFormat(glm::vec3(1.0+x, 1.0+y, 1.0+z),
                                  glm::vec4(r, g, b, 1)));
  vertices.push_back(VertexFormat(glm::vec3(1.0+x, 1.0+y, -1.0+z),
                                  glm::vec4(r, g, b, 1)));
  vertices.push_back(VertexFormat(glm::vec3(1.0+x, -1.0+y, -1.0+z),
                                  glm::vec4(r, g, b, 1)));
  vertices.push_back(VertexFormat(glm::vec3(1.0+x, -1.0+y, 1.0+z),
                                  glm::vec4(r, g, b, 1)));

  //back
  vertices.push_back(VertexFormat(glm::vec3(-1.0+x, -1.0+y, -1.0+z),
                                  glm::vec4(r, g, b, 1)));
  vertices.push_back(VertexFormat(glm::vec3( 1.0+x, -1.0+y, -1.0+z),
                                  glm::vec4(r, g, b, 1)));
  vertices.push_back(VertexFormat(glm::vec3( 1.0+x, 1.0+y, -1.0+z),
                                  glm::vec4(r, g, b, 1)));
  vertices.push_back(VertexFormat(glm::vec3(-1.0+x, 1.0+y, -1.0+z),
                                  glm::vec4(r, g, b, 1)));

  //left
  vertices.push_back(VertexFormat(glm::vec3(-1.0+x, -1.0+y, -1.0+z),
                                  glm::vec4(r, g, b, 1)));
  vertices.push_back(VertexFormat(glm::vec3(-1.0+x, -1.0+y, 1.0+z),
                                  glm::vec4(r, g, b, 1)));
  vertices.push_back(VertexFormat(glm::vec3(-1.0+x, 1.0+y, 1.0+z),
                                  glm::vec4(r, g, b, 1)));
  vertices.push_back(VertexFormat(glm::vec3(-1.0+x, 1.0+y, -1.0+z),
                                  glm::vec4(r, g, b, 1)));

  //upper
  vertices.push_back(VertexFormat(glm::vec3( 1.0+x, 1.0+y, 1.0+z),
                                  glm::vec4(r, g, b, 1)));
  vertices.push_back(VertexFormat(glm::vec3(-1.0+x, 1.0+y, 1.0+z),
                                  glm::vec4(r, g, b, 1)));
  vertices.push_back(VertexFormat(glm::vec3(-1.0+x, 1.0+y, -1.0+z),
                                  glm::vec4(r, g, b, 1)));
  vertices.push_back(VertexFormat(glm::vec3( 1.0+x, 1.0+y, -1.0+z),
                                  glm::vec4(r, g, b, 1)));

  //bottom
  vertices.push_back(VertexFormat(glm::vec3(-1.0+x, -1.0+y, -1.0+z),
                                  glm::vec4(r, g, b, 1)));
  vertices.push_back(VertexFormat(glm::vec3( 1.0+x, -1.0+y, -1.0+z),
                                  glm::vec4(r, g, b, 1)));
  vertices.push_back(VertexFormat(glm::vec3( 1.0+x, -1.0+y, 1.0+z),
                                  glm::vec4(r, g, b, 1)));
  vertices.push_back(VertexFormat(glm::vec3(-1.0+x, -1.0+y, 1.0+z),
                                  glm::vec4(r, g, b, 1)));

  allVertices.insert(allVertices.end(), vertices.begin(), vertices.end());
}

void CubeCluster::update(){

}

void CubeCluster::draw(const glm::mat4& projection_matrix, const glm::mat4& view_matrix){
  //std::cout << "ind: " << allIndices.size() << " vert: " << allVertices.size() << std::endl;
  glUseProgram(program);
  glUniform3f(glGetUniformLocation(program, "rotation"),0,0,0);
  glUniformMatrix4fv(glGetUniformLocation(program, "view_matrix"),
      1, false, &view_matrix[0][0]);
  glUniformMatrix4fv(glGetUniformLocation(program, "projection_matrix"), 
      1, false, &projection_matrix[0][0]);
  glBindVertexArray(vao);
  glDrawElements(GL_TRIANGLES, allIndices.size(), GL_UNSIGNED_INT, 0);
}
