#include "Camera.hpp"

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(glm::mat4* view_matrix_){
  view_matrix = view_matrix_;
}

void Camera::updateView(){
  glm::mat4 rollMat = glm::mat4(1.0f);
  glm::mat4 pitchMat = glm::mat4(1.0f);
  glm::mat4 yawMat = glm::mat4(1.0f);

  rollMat = glm::rotate(rollMat, roll, glm::vec3(0.0f, 0.0f, 1.0f));
  pitchMat = glm::rotate(pitchMat, pitch, glm::vec3(1.0f, 0.0f, 0.0f));
  yawMat = glm::rotate(yawMat, yaw, glm::vec3(0.0f, 1.0f, 0.0f));

  glm::mat4 rotate = rollMat * pitchMat * yawMat;

  glm::mat4 translate = glm::mat4(1.0f);
  translate = glm::translate(translate, -eyeVector);

  *view_matrix = (rotate * translate);
}

void Camera::keyPress(const unsigned char key, int x, int y){
  if(key == 'f'){
    mult = 5;
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

  const float speed = 0.12f;

  //make forward vector negative to look forward
  eyeVector += (-dz * forward + dx* strafe) * speed;

  updateView();
}

void Camera::mouseMove(int x, int y){
  if(isMousePressed == false)
    return;

  //mouseposition is last mouse pos
  glm::vec2 mouse_delta = glm::vec2(x, y) - mousePosition;

  //yaw and pitch are converted to radians in updateview by glm rotate
  yaw += mouseXSensitivity * mouse_delta.x;
  pitch += mouseYSensitivity * mouse_delta.y;

  mousePosition = glm::vec2(x, y);
  updateView();
}

void Camera::mousePress(int button, int state, int x, int y){
  if (state == GLUT_UP){
    isMousePressed = false;
  }
  if (state == GLUT_DOWN){
    isMousePressed = true;
    mousePosition.x = x;
    mousePosition.y = y;
  }
}
