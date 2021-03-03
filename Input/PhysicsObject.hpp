#ifndef PHYSICSOBJECT_H
#define PHYSICSOBJECT_H

#include <glm/glm.hpp>

#include <array>

class PhysicsObject {
  public:
    glm::vec3 d_acc = {0,0,0};
    glm::vec3 d_vel = {0,0,0};
    glm::vec3 d_pos = {0,50,0};

    //An axis aligned bounding box
    std::array<glm::vec3, 8> d_AABB;

    PhysicsObject() = default;
    virtual ~PhysicsObject() = default;
    virtual void physicsUpdate() = 0;
    virtual void setVel(const glm::vec3& vel) = 0;
    virtual void setPos(const glm::vec3& pos) = 0;
    virtual void setAcc(const glm::vec3& acc) = 0;
    virtual void incVel(const glm::vec3& vel) = 0;

};

#endif
