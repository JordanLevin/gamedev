#ifndef CAMERA_H
#define CAMERA_H

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>

class Camera {
  private:
    glm::mat4* view_matrix;
    glm::vec3 eyeVector{0,0,0};
    glm::vec2 mousePosition{0,0};
    bool isMousePressed = false;
    float yaw{0};
    float pitch{0};
    float roll{0};
    float mouseXSensitivity{.01};
    float mouseYSensitivity{.01};

  public: 
    Camera(glm::mat4* view_matrix_);
    void updateView();
    void keyPress(const unsigned char key, int x, int y);
    void mouseMove(int x, int y);
    void mousePress(int button, int state, int x, int y);
};
#endif
