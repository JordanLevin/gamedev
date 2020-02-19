#include "ModelManager.hpp"
#include "ShaderManager.hpp"
#include "ShaderManager.hpp"

#include "../Rendering/Models/Triangle.hpp"
#include "../Rendering/Models/Quad.hpp"
#include "../Rendering/Models/Cube.hpp"
#include "../Rendering/Models/IndexCube.hpp"

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

  IndexCube* cube = new IndexCube();
  cube->setProgram(ShaderManager::getShader("cubeShader"));
  cube->create();
  gameModelList["cube"] = cube;

  //for(int i = -8; i < 8; i += 2){
  //for(int j = -8; j < 8; j += 2){
  //for(int k = -8; k < 8; k += 2){
    //Cube* cube1 = new Cube();
    //cube1->setProgram(ShaderManager::getShader("cubeShader"));
    //cube1->create(i,j,k);
    //gameModelList[std::string("cube") + 
      //std::to_string(i) + std::to_string(j) + std::to_string(k)] = cube1;
  //}
  //}
  //}

  Cube* cube1 = new Cube();
  cube1->setProgram(ShaderManager::getShader("cubeShader"));
  cube1->create(2,2,2);
  gameModelList["cube1"] = cube1;
}

void ModelManager::update(){
  for(auto& model: gameModelList){
    model.second->update();
  }
}

void ModelManager::draw(){
  for(auto& model: gameModelList){
    model.second->draw();
  }
}

void ModelManager::draw(const glm::mat4& projection_matrix, const glm::mat4& view_matrix){
  for(auto& model: gameModelList){
    model.second->draw(projection_matrix, view_matrix);
  }
}
