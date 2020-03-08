#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include "ShaderManager.hpp"
#include "ModelManager.hpp"
#include "../Core/Init/IListener.hpp"
#include "../Input/Camera.hpp"

#include <chrono>

class SceneManager: public IListener{
  private:
    ShaderManager shaderManager;
    ModelManager modelManager;
    glm::mat4 view_matrix;
    glm::mat4 projection_matrix;
    Camera camera{&view_matrix, &projection_matrix};
    std::chrono::high_resolution_clock::time_point frameStart;
  public:
    SceneManager();
    ~SceneManager() = default;

    virtual void notifyBeginFrame();
    virtual void notifyDisplayFrame();
    virtual void notifyEndFrame();
    virtual void notifyReshape(int width, int height, 
                               int pwidth, int pheight);

    void setViewMatrix(glm::mat4 view_matrix_);
    glm::mat4 getViewMatrix();

    Camera& getCamera();
    void setCamera(const Camera& cam);
};

#endif
