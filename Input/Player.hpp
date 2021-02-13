#ifndef PLAYER_H
#define PLAYER_H

#include <glm/glm.hpp>

#include <mutex>

#include "PhysicsObject.hpp"

class World;
class Camera;

class Player : public PhysicsObject {
  World* d_world = nullptr;
  Camera* d_camera = nullptr;
  std::mutex d_player_mtx;

  public:
    ~Player() = default;
    Player(World* world, Camera* camera);
    void syncCamera();
    void incX(float x);
    void incY(float y);
    void incZ(float z);
    bool willCollide();

    void physicsUpdate() override;
    void setPos(const glm::vec3& pos)/*override*/;
    void setVel(const glm::vec3& vel)/*override*/;
};

#endif
