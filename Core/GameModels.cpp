#include "GameModels.hpp"
#include "VertexFormat.hpp"

#include <GL/glew.h> 

#include <string>
#include <map>
#include <vector>

GameModels::GameModels(){}

GameModels::~GameModels(){
  for(auto it = gameModelList.begin(); it != gameModelList.end(); ++it){
    //delete vao and vbos
    unsigned int* p = &it->second.vao;
    glDeleteVertexArrays(1,p);
    glDeleteBuffers(it->second.vbos.size(), &it->second.vbos[0]);
    it->second.vbos.clear();
  }
  gameModelList.clear();
}

void GameModels::createTriangleModel(const std::string& gameModelName){
  unsigned int vao;
  unsigned int vbo;

  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  std::vector<VertexFormat> vertices;//our vertex positions
  vertices.push_back(VertexFormat(glm::vec3( 0.25, -0.25, 0.0),
                                  glm::vec4(1,0,0,1)));
  vertices.push_back(VertexFormat(glm::vec3(-0.25, -0.25, 0.0),
                                  glm::vec4(0,1,0,1)));
  vertices.push_back(VertexFormat(glm::vec3( 0.25, 0.25, 0.0),
                                  glm::vec4(0,0,1,1)));

  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(VertexFormat)*3, &vertices[0], GL_STATIC_DRAW);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)0);
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)12);

  //Add vao, vbo, and add to the map
  Model myModel;
  myModel.vao = vao;
  myModel.vbos.push_back(vbo);
  gameModelList[gameModelName] = myModel;
}

void GameModels::deleteModel(const std::string& gameModelName){
  Model model = gameModelList[gameModelName];
  unsigned int p = model.vao;
  glDeleteVertexArrays(1, &p);
  glDeleteBuffers(model.vbos.size(), &model.vbos[0]);
  model.vbos.clear();
  gameModelList.erase(gameModelName);
}

unsigned int GameModels::getModel(const std::string& gameModelName){
  return gameModelList[gameModelName].vao;
}
