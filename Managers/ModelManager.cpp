#include "ModelManager.hpp"
#include "ShaderManager.hpp"
#include "ShaderManager.hpp"

#include "../Rendering/Models/Triangle.hpp"
#include "../Rendering/Models/Quad.hpp"

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
  Triangle* triangle = new Triangle();
  triangle->setProgram(ShaderManager::getShader("colorShader"));
  triangle->create();
  gameModelList["triangle"] = triangle;

  Quad* quad = new Quad();
  quad->setProgram(ShaderManager::getShader("colorShader"));
  quad->create();
  gameModelList["quad"] = quad;
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
