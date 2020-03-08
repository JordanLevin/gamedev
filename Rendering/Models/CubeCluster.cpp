#include "CubeCluster.hpp"
#include "../../Lib/Serialize.hpp"

#include <string>
#include <fstream>

CubeCluster::CubeCluster(){
}

CubeCluster::CubeCluster(std::string path){
  std::fstream read;
  read.open(path, std::ios::in);
  Serialize::deserialize(read, allVertices);
  Serialize::deserialize(read, allIndices);

}

void CubeCluster::writeChunk(std::string path){
  std::fstream write;
  write.open(path, std::ios::out);
  Serialize::serialize(write, allVertices);
  Serialize::serialize(write, allIndices);
}

void CubeCluster::create(){
  GLuint vao;
  GLuint vbo;
  GLuint ibo;
  GLuint nbo;

  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  //Vertex buffer
  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, 
      sizeof(VertexFormat) * allVertices.size(), &allVertices[0], GL_STATIC_DRAW);

  //Index buffer
  glGenBuffers(1, &ibo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, 
      sizeof(unsigned int) * allIndices.size(), &allIndices[0], GL_STATIC_DRAW);

  //Normal buffer
  glGenBuffers(1, &nbo);
  glBindBuffer(GL_ARRAY_BUFFER, nbo);
  glBufferData(GL_ARRAY_BUFFER,
      sizeof(VertexFormat) * allVertices.size(), &allVertices[0], GL_STATIC_DRAW);

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
  this->vbos.push_back(ibo);
  this->vbos.push_back(nbo);
}

void CubeCluster::add(float x, float y, float z){
  add(x,y,z, 0.5, 0.5, 0.5);
}

void CubeCluster::add(float x, float y, float z, float r, float g, float b){
  unsigned int s = allVertices.size();

  std::vector<VertexFormat> vertices;
  std::vector<unsigned int> indices = { 
    0+s, 1+s, 2+s, 0+s, 2+s, 3+s, //front
    4+s, 5+s, 6+s, 4+s, 6+s, 7+s, //right
    8+s, 9+s, 10+s, 8+s, 10+s, 11+s, //back
    12+s, 13+s, 14+s, 12+s, 14+s, 15+s, //left
    16+s, 17+s, 18+s, 16+s, 18+s, 19+s, //upper
    20+s, 21+s, 22+s, 20+s, 22+s, 23+s}; //bottom

  //experimental optimization that doesnt look like itll work out
  //std::vector<unsigned int> indices = { 
    //0+s, 1+s, 2+s, 0+s, 2+s, 3+s, //front
    //1+s, 5+s, 6+s, 1+s, 6+s, 2+s, //right
    //4+s, 5+s, 6+s, 4+s, 6+s, 7+s, //back
    //0+s, 4+s, 7+s, 0+s, 7+s, 3+s, //left
    //0+s, 4+s, 5+s, 0+s, 5+s, 1+s, //upper
    //3+s, 7+s, 6+s, 3+s, 6+s, 2+s}; //bottom
  //experimental optimization that doesnt look like itll work out
  //front
  //vertices.push_back({{-1.0f+x, -1.0f+y, 1.0f+z},
      //{r, g, b, 1},
      //{-1.0f, -1.0f, 1.0f}});
  //vertices.push_back({{ 1.0f+x, -1.0f+y, 1.0f+z},
      //{r, g, b, 1},
      //{1.0f, -1.0f, 1.0f}});
  //vertices.push_back({{ 1.0f+x, 1.0f+y, 1.0f+z},
      //{r, g, b, 1},
      //{1.0f, 1.0f, 1.0f}});
  //vertices.push_back({{-1.0f+x, 1.0f+y, 1.0f+z},
      //{r, g, b, 1},
      //{-1.0f, 1.0f, 1.0f}});

  ////back
  //vertices.push_back({{-1.0f+x, -1.0f+y, -1.0f+z},
      //{r, g, b, 1},
      //{-1.0f, -1.0f, -1.0f}});
  //vertices.push_back({{ 1.0f+x, -1.0f+y, -1.0f+z},
      //{r, g, b, 1},
      //{1.0f, -1.0f, -1.0f}});
  //vertices.push_back({{ 1.0f+x, 1.0f+y, -1.0f+z},
      //{r, g, b, 1},
      //{1.0f, 1.0f, -1.0f}});
  //vertices.push_back({{-1.0f+x, 1.0f+y, -1.0f+z},
      //{r, g, b, 1},
      //{-1.0f, 1.0f, -1.0f}});

  allIndices.insert(allIndices.end(), indices.begin(), indices.end());



  //front
  vertices.push_back({{-0.5f+x, -0.5f+y, 0.5f+z},
      {r, g, b, 1},
      {0.0f, 0.0f, 1.0f}});
  vertices.push_back({{ 0.5f+x, -0.5f+y, 0.5f+z},
      {r, g, b, 1},
      {0.0f, 0.0f, 1.0f}});
  vertices.push_back({{ 0.5f+x, 0.5f+y, 0.5f+z},
      {r, g, b, 1},
      {0.0f, 0.0f, 1.0f}});
  vertices.push_back({{-0.5f+x, 0.5f+y, 0.5f+z},
      {r, g, b, 1},
      {0.0f, 0.0f, 1.0f}});

  //right
  vertices.push_back({{0.5f+x, 0.5f+y, 0.5f+z},
      {r, g, b, 1},
      {1.0f, 0.0f, 0.0f}});
  vertices.push_back({{0.5f+x, 0.5f+y, -0.5f+z},
      {r, g, b, 1},
      {1.0f, 0.0f, 0.0f}});
  vertices.push_back({{0.5f+x, -0.5f+y, -0.5f+z},
      {r, g, b, 1},
      {1.0f, 0.0f, 0.0f}});
  vertices.push_back({{0.5f+x, -0.5f+y, 0.5f+z},
      {r, g, b, 1},
      {1.0f, 0.0f, 0.0f}});

  //back
  vertices.push_back({{-0.5f+x, -0.5f+y, -0.5f+z},
      {r, g, b, 1},
      {0.0f, 0.0f, -1.0f}});
  vertices.push_back({{ 0.5f+x, -0.5f+y, -0.5f+z},
      {r, g, b, 1},
      {0.0f, 0.0f, -1.0f}});
  vertices.push_back({{ 0.5f+x, 0.5f+y, -0.5f+z},
      {r, g, b, 1},
      {0.0f, 0.0f, -1.0f}});
  vertices.push_back({{-0.5f+x, 0.5f+y, -0.5f+z},
      {r, g, b, 1},
      {0.0f, 0.0f, -1.0f}});

  //left
  vertices.push_back({{-0.5f+x, -0.5f+y, -0.5f+z},
      {r, g, b, 1},
      {-1.0f, 0.0f, 0.0f}});
  vertices.push_back({{-0.5f+x, -0.5f+y, 0.5f+z},
      {r, g, b, 1},
      {-1.0f, 0.0f, 0.0f}});
  vertices.push_back({{-0.5f+x, 0.5f+y, 0.5f+z},
      {r, g, b, 1},
      {-1.0f, 0.0f, 0.0f}});
  vertices.push_back({{-0.5f+x, 0.5f+y, -0.5f+z},
      {r, g, b, 1},
      {-1.0f, 0.0f, 0.0f}});

  //upper
  vertices.push_back({{ 0.5f+x, 0.5f+y, 0.5f+z},
      {r, g, b, 1},
      {0.0f, 1.0f, 0.0f}});
  vertices.push_back({{-0.5f+x, 0.5f+y, 0.5f+z},
      {r, g, b, 1},
      {0.0f, 1.0f, 0.0f}});
  vertices.push_back({{-0.5f+x, 0.5f+y, -0.5f+z},
      {r, g, b, 1},
      {0.0f, 1.0f, 0.0f}});
  vertices.push_back({{ 0.5f+x, 0.5f+y, -0.5f+z},
      {r, g, b, 1},
      {0.0f, 1.0f, 0.0f}});

  //bottom
  vertices.push_back({{-0.5f+x, -0.5f+y, -0.5f+z},
      {r, g, b, 1},
      {0.0f, -1.0f, 0.0f}});
  vertices.push_back({{ 0.5f+x, -0.5f+y, -0.5f+z},
      {r, g, b, 1},
      {0.0f, -1.0f, 0.0f}});
  vertices.push_back({{ 0.5f+x, -0.5f+y, 0.5f+z},
      {r, g, b, 1},
      {0.0f, -1.0f, 0.0f}});
  vertices.push_back({{-0.5f+x, -0.5f+y, 0.5f+z},
      {r, g, b, 1},
      {0.0f, -1.0f, 0.0f}});

  allVertices.insert(allVertices.end(), vertices.begin(), vertices.end());
}

void CubeCluster::remove(float x, float y, float z){
  //find the vertices????????????????????????
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

  glDrawElements(GL_TRIANGLES, allIndices.size(), GL_UNSIGNED_INT, 0);
}
