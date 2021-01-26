#include "ModelManager.hpp"
#include "ShaderManager.hpp"
#include "ShaderManager.hpp"

#include "../Rendering/Models/CubeCluster.hpp"
#include "../Rendering/Models/World.hpp"
#include "../Rendering/Models/ScreenGui.hpp"
#include "../Rendering/Gui/Gui.hpp"
#include "../Rendering/Gui/GuiElement.hpp"
#include "../Rendering/Gui/TextElement.hpp"

#include <random>

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

void ModelManager::init(Camera* camera){
  World* world = new World();
  world->create();
  world->setCamera(camera);
  camera->setWorld(world);
  gameModelList["world"] = world;

  Gui* gui = new Gui();
  GuiElement* elem1 = new GuiElement(-1.0,-1.0,0.5,0.5,1.0f,0.0f,0.0f, nullptr);
  GuiElement* elem2 = new GuiElement(0.4,0.4,0.05,0.05,0.0f,0.0f,1.0f, elem1);
  elem1->create();
  elem1->setProgram(ShaderManager::getShader("guiShader"));
  elem2->create();
  elem2->setProgram(ShaderManager::getShader("guiShader"));
  elem1->add(elem2);
  gui->add(elem1);
  Model* test = new TextElement(100,100, "woo text", elem1);
  test->setProgram(ShaderManager::getShader("textShader"));
  test->create();
  elem1->add(test);
  gameModelList["gui"] = gui;
  gui->enable();

  //old screenspace gui?
  ScreenGui* sgui = new ScreenGui();
  sgui->add(0.0-0.03, 0, 0, 0.0+0.03, 0, 0, 0,0,1);
  sgui->add(0, 0.0-0.05, 0, 0, 0.0+0.05, 0, 0,0,1);
  sgui->setProgram(ShaderManager::getShader("guiShader"));
  sgui->create();
  gameModelList["sgui"] = sgui;

  //old worldspace gui for debugging
  DGui* dgui = new DGui();
  for(int i = -512; i < 512; i += 16){
    for(int j = -512; j < 512; j += 16){
      dgui->add(i,0,j, i,1000,j,1,0,0);
    }
  }
  dgui->setProgram(ShaderManager::getShader("lineShader"));
  dgui->create();
  gameModelList["dgui"] = dgui;
  camera->gui = dgui;

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
