#ifndef PLAYER_H
#define PLAYER_H

#include <glm/glm.hpp>

#include <mutex>
#include <set>

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
    bool d_flying = false;

    /**
      * Debug funcs
      */
    void printPhys(std::string msg);

  public:
    std::set<uint8_t> d_keys;

    Player(World* world, Camera* camera);
    ~Player() = default;
    void syncCamera();
    void syncAABB();
    void incX(float x);
    void incY(float y);
    void incZ(float z);
    bool willCollide(const glm::vec3& vel);
    /**
      * Calculate the vector to slide the player to avoid overlapping with the world
      */
    glm::vec3 calculateSlide(const glm::vec3& vel);

    void physicsUpdate() override;
    void setAcc(const glm::vec3& acc)override;
    void setPos(const glm::vec3& pos)override;
    void setVel(const glm::vec3& vel)override;
    void incVel(const glm::vec3& vel)override;

    void inputUpdate();
};

#endif
