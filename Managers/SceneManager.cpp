#include "SceneManager.hpp"
#include "ModelManager.hpp"
#include "../Input/Camera.hpp"
#include "../Rendering/Gui/Text.hpp"

#include <chrono>
#include <cmath>

using namespace std::chrono;

SceneManager::SceneManager(){
  Text::init(); //setup characters for erndering, probably do elsewhere
  glEnable(GL_DEPTH_TEST);
  shaderManager.createProgram("textvshader.glsl",
                              "textfshader.glsl",
                              "textShader");
  shaderManager.createProgram("simplelinevshader.glsl",
                              "fshader1.glsl",
                              "guiShader");
  shaderManager.createProgram("linevshader.glsl",
                              "fshader1.glsl",
                              "lineShader");
  shaderManager.createProgram("cubevshader.glsl",
                              "fshader1.glsl",
                              "cubeShader");
  shaderManager.createProgram("uncompressedcubevshader.glsl",
                              "fshader1.glsl",
                              "cubeShader2");
  view_matrix = glm::mat4(1.0f, 0.0f, 0.0f, 0.0f,
      0.0f, 1.0f, 0.0f, 0.0f,
      0.0f, 0.0f, -1.0f, 0.0f,
      //0.0f, 0.0f, 10.0f, 1.0f);
      0.0f, 0.0f, 0.0f, 1.0f);
  modelManager.init(&camera);
}

void SceneManager::setViewMatrix(glm::mat4 view_matrix_){
  view_matrix = view_matrix_;
}

glm::mat4 SceneManager::getViewMatrix(){
  return view_matrix;
}

Camera& SceneManager::getCamera(){
  return camera;
}
void SceneManager::setCamera(const Camera& cam){
  camera = cam;
}

void SceneManager::notifyBeginFrame(){
  frameStart = high_resolution_clock::now();
  modelManager.update();
}

void SceneManager::notifyDisplayFrame(){
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glClearColor(0.0, 0.0, 0.0, 1.0);
  modelManager.draw(projection_matrix, view_matrix);
  modelManager.draw();
}

void SceneManager::notifyEndFrame(){
  auto end = high_resolution_clock::now();
  auto duration = ::duration_cast<milliseconds>(end - frameStart); 
  //std::cout << duration.count() << std::endl; 
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

