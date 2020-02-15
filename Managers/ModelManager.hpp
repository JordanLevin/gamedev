#ifndef MODELMANAGER_H
#define MODELMANAGER_H

#include "ShaderManager.hpp"
#include "../Rendering/IGameObject.hpp"
#include "../Rendering/Models/Triangle.hpp"
#include "../Rendering/Models/Quad.hpp"

#include <map>

class ModelManager{
  private:
    std::map<std::string, IGameObject*> gameModelList;

  public:
    ModelManager() = default;
    ~ModelManager();

    void init();
    void draw();
    void update();
    void deleteModel(const std::string& modelName);
    const IGameObject& getModel(const std::string& modelName);
};

#endif