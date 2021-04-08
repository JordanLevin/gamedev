#ifndef PHYSICSOBJECT_H
#define PHYSICSOBJECT_H

#include <glm/glm.hpp>

#include <array>
#include <functional>

#include "../Rendering/Models/World.hpp"

class PhysicsObject {
  public:
    World* d_world;
    glm::vec3 d_acc = {0,0,0};
    glm::vec3 d_vel = {0,0,0};
    glm::vec3 d_pos = {0,50,0};
    bool d_on_ground = false;
    float d_height = 0.5;

    std::function<void()> d_prePhysics;
    std::function<void()> d_postPhysics;

    //An axis aligned bounding box
    std::array<glm::vec3, 8> d_AABB;

    PhysicsObject() = default;
    PhysicsObject(std::function<void()> prePhysics, std::function<void()> postPhysics);
    virtual ~PhysicsObject() = default;
    virtual void setVel(const glm::vec3& vel);
    virtual void setPos(const glm::vec3& pos);
    virtual void setAcc(const glm::vec3& acc);
    virtual void incVel(const glm::vec3& vel);
    virtual void physicsUpdate();

    bool willCollide(const glm::vec3& vel);
    glm::vec3 calculateSlide(const glm::vec3& vel);
    void printPhys(std::string msg);
    void syncAABB();

};

#endif
