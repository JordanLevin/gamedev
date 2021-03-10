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
    Camera* d_camera;
    std::mutex d_player_mtx;
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
    /**
      * Calculate the vector to slide the player to avoid overlapping with the world
      */
    glm::vec3 calculateSlide(const glm::vec3& vel);

    void inputUpdate();
};

#endif
