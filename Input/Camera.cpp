#include "Camera.hpp"

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

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
  return glm::vec3(
    (*view_matrix)[0][2],
    (*view_matrix)[1][2],
    (*view_matrix)[2][2]
  );
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
}

void Camera::keyPress(const unsigned char key, int x, int y){
  if(key == 'f'){
    if(mult != 20)
      mult = 20;
    else
      mult = 1;
  }
  float dx =0;
  float dz =0;
  switch (key){
    case 'w':
      dz = -2*mult;
      break;
    case 's':
      dz = 2*mult;
      break;
    case 'a':
      dx = -2*mult;
      break;
    case 'd':
      dx = 2*mult;
      break;
    default:
      break;
  }

  glm::mat4& mat = *view_matrix;
  glm::vec3 forward(mat[0][2], mat[1][2], mat[2][2]);
  glm::vec3 strafe(mat[0][0], mat[1][0], mat[2][0]);
  //std::cout << mat[0][2] << " " << mat[1][2] << " " << mat[2][2] << std::endl;

  const float speed = 0.12f;

  //make forward vector negative to look forward
  eyeVector += (-dz * forward + dx* strafe) * speed;

  std::cout << " x: " << eyeVector[0] << " y: " << eyeVector[1] << " z: " << eyeVector[2] << std::endl;

  updateView();
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
  updateView();
}

void Camera::mousePress(int button, int state, int x, int y){
  if (state == GLUT_DOWN){
    glm::vec3 window{1280/2,720/2,0};
    glm::vec4 viewport{0,0,1280,720};
    glm::vec3 point = glm::unProject(window, *view_matrix, *projection_matrix, viewport);
    //std::cout << point[0] << " " << point[1] << " " << point[2] << std::endl;
    glm::vec3 dir = getDirection();
    //world->breakBlock(point, dir);
  }
}
