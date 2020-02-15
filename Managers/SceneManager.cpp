#include "SceneManager.hpp"
#include "ModelManager.hpp"

SceneManager::SceneManager(){
  glEnable(GL_DEPTH_TEST);
  shaderManager.createProgram("vshader1.glsl",
                              "fshader1.glsl",
                              "colorShader");
  modelManager.init();
}

void SceneManager::notifyBeginFrame(){
  modelManager.update();
}

void SceneManager::notifyDisplayFrame(){
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glClearColor(0.0, 0.0, 0.0, 1.0);
  modelManager.draw();
}

void SceneManager::notifyEndFrame(){

}

void SceneManager::notifyReshape(int width, int height, 
    int pwidth, int pheight){

}
