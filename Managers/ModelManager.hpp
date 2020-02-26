#ifndef MODELMANAGER_H
#define MODELMANAGER_H

#include "ShaderManager.hpp"
#include "../Rendering/IGameObject.hpp"
#include "../Input/Camera.hpp"

#include <map>

class ModelManager{
  private:
    std::map<std::string, IGameObject*> gameModelList;

  public:
    ModelManager() = default;
    ~ModelManager();

    void init(Camera* camera);
    void draw();
    void draw(const glm::mat4& projection_matrix, const glm::mat4& view_matrix);
    void update();
    void deleteModel(const std::string& modelName);
    const IGameObject& getModel(const std::string& modelName);
};

#endif
