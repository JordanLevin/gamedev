#ifndef CAMERA_H
#define CAMERA_H

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>

#include "../Core/Init/InitGlut.hpp"

class Camera {
  private:
    static glm::vec3 eyeVector;
    static glm::vec2 mousePosition;
    static bool isMousePressed;
    static float yaw;
    static float pitch;
    static float roll;
    static float mouseXSensitivity;
    static float mouseYSensitivity;

  public: 
    static void updateView();
    static void keyPress(const unsigned char key, int x, int y);
    static void mouseMove(int x, int y);
    static void mousePress(int button, int state, int x, int y);
};
#endif
