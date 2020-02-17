#include "SceneManager.hpp"
#include "ModelManager.hpp"

#include <cmath>

SceneManager::SceneManager(){
  glEnable(GL_DEPTH_TEST);
  shaderManager.createProgram("vshader1.glsl",
                              "fshader1.glsl",
                              "colorShader");
  shaderManager.createProgram("cubevshader.glsl",
                              "fshader1.glsl",
                              "cubeShader");
  view_matrix = glm::mat4(1.0f, 0.0f, 0.0f, 0.0f,
      0.0f, 1.0f, 0.0f, 0.0f,
      0.0f, 0.0f, -1.0f, 0.0f,
      0.0f, 0.0f, 10.0f, 1.0f);
  modelManager.init();
}

void SceneManager::notifyBeginFrame(){
  modelManager.update();
}

void SceneManager::notifyDisplayFrame(){
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glClearColor(0.0, 0.0, 0.0, 1.0);
  modelManager.draw();
  modelManager.draw(projection_matrix, view_matrix);
}

void SceneManager::notifyEndFrame(){

}

void SceneManager::notifyReshape(int width, int height, 
    int pwidth, int pheight){
  float ar = (float)glutGet(GLUT_WINDOW_WIDTH) /
             (float)glutGet(GLUT_WINDOW_HEIGHT);
  float angle = 45.0f, near1 = 0.1f, far1 = 2000.0f;

  for(int row = 0; row < 4; row++){
    for(int col = 0; col < 4; col++){
      projection_matrix[row][col] = 0;
    }
  }
  projection_matrix[0][0] = 1.0f / (ar * std::tan(angle / 2.0f));
  projection_matrix[1][1] = 1.0f / std::tan(angle / 2.0f);
  projection_matrix[2][2] = (-near1 - far1) / (near1 - far1);
  projection_matrix[2][3] = 1.0f;
  projection_matrix[3][2] = 2.0f * near1 * far1 / (near1 - far1);

}
