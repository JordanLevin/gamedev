#ifndef CAMERA_H
#define CAMERA_H

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>

#include "../Rendering/Models/World.hpp"
#include "../Rendering/Gui/Gui.hpp"
#include "../Rendering/Gui/DGui.hpp"
//#include "../Rendering/Models/Gui.hpp"

class World;
class Player;

class Camera {
  public: 
    World* world = nullptr;
    Player* d_player = nullptr;
    glm::mat4* view_matrix = nullptr;
    glm::mat4* projection_matrix = nullptr;
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

    DGui* gui;
    Camera(glm::mat4* view_matrix_, glm::mat4* projection_matrix_);
    void updateView();
    float getX();
    float getY();
    float getZ();
    glm::vec3 getDirection();
    void setWorld(World* world_);
    void setPlayer(Player* player_);
    void keyPress(const unsigned char key, int x, int y);
    void mouseMove(int x, int y);
    void mousePress(int button, int state, int x, int y);
};
#endif
