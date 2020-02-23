#include "ModelManager.hpp"
#include "ShaderManager.hpp"
#include "ShaderManager.hpp"

#include "../Rendering/Models/Triangle.hpp"
#include "../Rendering/Models/Quad.hpp"
#include "../Rendering/Models/Cube.hpp"
#include "../Rendering/Models/IndexCube.hpp"
#include "../Rendering/Models/CubeCluster.hpp"

ModelManager::~ModelManager(){
  for(auto model: gameModelList){
    delete model.second;
  }
  gameModelList.clear();
}

void ModelManager::deleteModel(const std::string& modelName){
  IGameObject* model = gameModelList[modelName];
  model->destroy();
  gameModelList.erase(modelName);
}

const IGameObject& ModelManager::getModel(const std::string& modelName){
  return (*gameModelList[modelName]);
}

void ModelManager::init(){
  //Triangle* triangle = new Triangle();
  //triangle->setProgram(ShaderManager::getShader("colorShader"));
  //triangle->create();
  //gameModelList["triangle"] = triangle;

  //Quad* quad = new Quad();
  //quad->setProgram(ShaderManager::getShader("colorShader"));
  //quad->create();
  //gameModelList["quad"] = quad;

  //IndexCube* cube = new IndexCube();
  //cube->setProgram(ShaderManager::getShader("cubeShader"));
  //cube->create(0,0,0);
  //gameModelList["cube"] = cube;

  CubeCluster* cube1 = new CubeCluster();
  cube1->setProgram(ShaderManager::getShader("cubeShader"));
  for(int i = -200; i < 200; i += 2){
    for(int j = -200; j < 200; j += 2){
      for(int k = -10; k < 10; k += 2){
      cube1->add(i,j,0);
      }
    }
  }
  cube1->create();
  //gameModelList[std::string("cube") + 
    //std::to_string(i) + ":" + std::to_string(j)] = cube1;
  gameModelList["cube1"]  = cube1;

  //Cube* cube1 = new Cube();
  //cube1->setProgram(ShaderManager::getShader("cubeShader"));
  //cube1->create(2,2,2);
  //gameModelList["cube1"] = cube1;
}

void ModelManager::update(){
  for(auto& model: gameModelList){
    model.second->update();
  }
}

void ModelManager::draw(){
  for(const auto& model: gameModelList){
    model.second->draw();
  }
}

void ModelManager::draw(const glm::mat4& projection_matrix, const glm::mat4& view_matrix){
  for(const auto& model: gameModelList){
    model.second->draw(projection_matrix, view_matrix);
  }
}
