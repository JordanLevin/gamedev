#ifndef CAMERA_H
#define CAMERA_H

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>

#include "../Rendering/Models/World.hpp"

class World;

class Camera {
  private:
    World* world;
    glm::mat4* view_matrix;
    glm::mat4* projection_matrix;
    glm::vec3 eyeVector{0,50,0};
    glm::vec2 mousePosition{0,0};
    bool isMousePressed{false};
    bool centeredCursor{false};
    float yaw{0};
    float pitch{0};
    float roll{0};
    float mouseXSensitivity{.01};
    float mouseYSensitivity{.01};
    float mult{1.0f};

  public: 
    Camera(glm::mat4* view_matrix_, glm::mat4* projection_matrix_);
    void updateView();
    void keyPress(const unsigned char key, int x, int y);
    void mouseMove(int x, int y);
    void mousePress(int button, int state, int x, int y);
    float getX();
    float getY();
    float getZ();
    glm::vec3 getDirection();
    void setWorld(World* world_);
};
#endif
