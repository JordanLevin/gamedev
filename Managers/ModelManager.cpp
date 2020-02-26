#include "ModelManager.hpp"
#include "ShaderManager.hpp"
#include "ShaderManager.hpp"

#include "../Rendering/Models/Cube.hpp"
#include "../Rendering/Models/IndexCube.hpp"
#include "../Rendering/Models/CubeCluster.hpp"
#include "../Rendering/Models/World.hpp"

#include "../Lib/OctTree.hpp"

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
  world->create(camera);
  gameModelList["world"] = world;
  //IndexCube* cube = new IndexCube();
  //cube->setProgram(ShaderManager::getShader("cubeShader"));
  //cube->create(0,0,0);
  //gameModelList["cube"] = cube;

  //OctTree<myVec3> cubes;
  //for(int i = 0; i < 150; i += 4){
  //for(int j = 0; j < 150; j += 4){
  //for(int k = 0; k < 150; k += 4){
    //myVec3* v = new myVec3();
    //v->x = rand()%1000 - 500;
    //v->y = rand()%1000 - 500;
    //v->z = rand()%1000 - 500;
    //cubes.insert(v);
  //}
  //}
  //}

  //std::vector<CubeCluster*> clusters = cubes.getChunkAsCubeCluster();
  //int count = 0;
  //for(auto c: clusters){
    //c->setProgram(ShaderManager::getShader("cubeShader"));
    //c->create();
    //gameModelList[std::to_string(count)]  = c;
    //count++;
  //}
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
