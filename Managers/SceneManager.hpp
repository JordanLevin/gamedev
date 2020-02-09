#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include "ShaderManager.hpp"
#include "../Core/Init/IListener.hpp"

class SceneManager: public IListener{
  private:
    ShaderManager shaderManager;
  public:
    SceneManager();
    ~SceneManager() = default;

    virtual void notifyBeginFrame();
    virtual void notifyDisplayFrame();
    virtual void notifyEndFrame();
    virtual void notifyReshape(int width, int height, 
                               int pwidth, int pheight);
};

#endif
