#ifndef PLAYER_H
#define PLAYER_H

#include <glm/glm.hpp>

#include <mutex>

#include "PhysicsObject.hpp"

class World;
class Camera;

class Player : public PhysicsObject {
  private:
    World* d_world;
    Camera* d_camera;
    std::mutex d_player_mtx;
    bool d_on_ground = false;
    float d_height = 0.5;

  public:
    Player(World* world, Camera* camera);
    ~Player() = default;
    void syncCamera();
    void syncAABB();
    void incX(float x);
    void incY(float y);
    void incZ(float z);
    bool willCollide(const glm::vec3& vel);
    glm::vec3 calculateSlide();

    void physicsUpdate() override;
    void setAcc(const glm::vec3& acc)override;
    void setPos(const glm::vec3& pos)override;
    void setVel(const glm::vec3& vel)override;
    void incVel(const glm::vec3& vel)override;
};

#endif
