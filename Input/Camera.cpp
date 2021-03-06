#include "Camera.hpp"

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

#include "Player.hpp"

void printmat(glm::mat4& mat){
  for(int i = 0; i < 4; i++){
    for(int j = 0; j < 4; j++){
      std::cout << mat[i][j] << " ";
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
}

Camera::Camera(glm::mat4* view_matrix_, glm::mat4* projection_matrix_){
  view_matrix = view_matrix_;
  projection_matrix = projection_matrix_;
}

glm::vec3 Camera::getDirection(){
  return glm::normalize(glm::vec3(
        (*view_matrix)[0][2],
        (*view_matrix)[1][2],
        (*view_matrix)[2][2]
        ));
}

float Camera::getX(){
  return eyeVector[0];
}
float Camera::getY(){
  return eyeVector[1];
}
float Camera::getZ(){
  return eyeVector[2];
}

void Camera::setWorld(World* world_){
  world = world_;
}
void Camera::setPlayer(Player* player_){
  d_player = player_;
}

void Camera::updateView(){
  //glm::mat4 rollMat = glm::mat4(1.0f);
  //rollMat = glm::rotate(rollMat, roll, glm::vec3(0.0f, 0.0f, 1.0f));
  glm::mat4 pitchMat = glm::mat4(1.0f);
  glm::mat4 yawMat = glm::mat4(1.0f);
  pitchMat = glm::rotate(pitchMat, pitch, glm::vec3(1.0f, 0.0f, 0.0f));
  yawMat = glm::rotate(yawMat, yaw, glm::vec3(0.0f, 1.0f, 0.0f));

  glm::mat4 rotate = pitchMat * yawMat;

  //std::cout << "rot " << std::endl;
  //printmat(rotate);

  glm::mat4 translate = glm::mat4(1.0f);
  translate = glm::translate(translate, -eyeVector);

  *view_matrix = (rotate * translate);
  world->outlineBlock(eyeVector, getDirection());
}

void Camera::keyUp(const unsigned char key, int x, int y){
  d_player->d_keys.erase(key);
}
void Camera::keyDown(const unsigned char key, int x, int y){
  d_player->d_keys.insert(key);
}

void Camera::mouseMove(int x, int y){
  //This whole centered cursor thing is a hack to fix the wrap around when cursor
  //goes offscreen. Theres an issue where glutwarppointer doesnt seem to take affect
  //immediately so we need to ignore the couple mousemove calls after we recenter
  if(centeredCursor && (x >= 1000 || x<=100 || y>=600 || y<=100))
    return;
  else if(centeredCursor)
    centeredCursor = false;

  //mouseposition is last mouse pos
  glm::vec2 mouse_delta = glm::vec2(x, y) - mousePosition;
  mousePosition.x = x;
  mousePosition.y = y;

  //yaw and pitch are converted to radians in updateview by glm rotate
  yaw -= mouseXSensitivity * (mouse_delta.x);
  pitch -= mouseYSensitivity * (mouse_delta.y);

  if(x >= 1000 || x <= 100 || y >= 600 || y <= 100){
    centeredCursor = true;
    mousePosition.x = 1280/2;
    mousePosition.y = 720/2;
    glutWarpPointer(1280/2,720/2);
  }

  glm::vec3 point = eyeVector;
  glm::vec3 dir = getDirection();

  updateView();
}

void Camera::mousePress(int button, int state, int x, int y){
  //if (gui->enabled) {
  //gui->mousePress(button, state, x, y);
  //}
  if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
    glm::vec3 point = eyeVector;
    glm::vec3 dir = getDirection();
    world->breakBlock(point, dir);
    //gui->add(point[0], point[1], point[2], point[0]+dir[0], point[1]+dir[1], point[2]+dir[2], 0.3, 1, 1);
    //gui->create();
  }
  else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN){
    glm::vec3 point = eyeVector;
    glm::vec3 dir = getDirection();
    world->placeBlock(point, dir);
  }
}

