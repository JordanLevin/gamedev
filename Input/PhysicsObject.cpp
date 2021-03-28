#include "PhysicsObject.hpp"

PhysicsObject::PhysicsObject(std::function<void()> prePhysics,
    std::function<void()> postPhysics):
  d_prePhysics{prePhysics},
  d_postPhysics{postPhysics}
{
}

void PhysicsObject::syncAABB(){
  d_AABB = {
    glm::vec3{d_pos[0]-0.3,d_pos[1]-d_height,d_pos[2]-0.3},
    glm::vec3{d_pos[0]-0.3,d_pos[1]-d_height,d_pos[2]+0.3},
    glm::vec3{d_pos[0]-0.3,d_pos[1]+d_height,d_pos[2]-0.3},
    glm::vec3{d_pos[0]-0.3,d_pos[1]+d_height,d_pos[2]+0.3},
    glm::vec3{d_pos[0]+0.3,d_pos[1]-d_height,d_pos[2]-0.3},
    glm::vec3{d_pos[0]+0.3,d_pos[1]-d_height,d_pos[2]+0.3},
    glm::vec3{d_pos[0]+0.3,d_pos[1]+d_height,d_pos[2]-0.3},
    glm::vec3{d_pos[0]+0.3,d_pos[1]+d_height,d_pos[2]+0.3}
  };
}

bool PhysicsObject::willCollide(const glm::vec3& vel){
  bool exists = false;
  for(const auto& point: d_AABB){
    glm::vec3 temp = point + vel;
    exists |= d_world->blockExists(temp);
  }
  return exists;
}

glm::vec3 PhysicsObject::calculateSlide(const glm::vec3& vel){
  bool exists = false;
  glm::vec3 res(0,0,0);
  for(const auto& point: d_AABB){
    glm::vec3 temp = point + vel;
    if(d_world->blockExists(temp)){
      exists = true;
      break;
    }
  }
  if(!exists)
    return vel;
  return res;
}

void PhysicsObject::physicsUpdate(){
  d_prePhysics();
  d_vel += d_acc;
  //printPhys("After update");

  //Handle if the player ends up clipped into a block, kinda hacky for now
  while(willCollide(glm::vec3(0,0,0))){
      d_pos[1] = std::ceil(d_pos[1] + 0.001)+0.001;
      syncAABB();
  }

  //Handle collisions so the player slides nicely
  if(willCollide(d_vel)){
    auto x_vel = glm::vec3(d_vel[0], 0, 0);
    auto y_vel = glm::vec3(0, d_vel[1], 0);
    auto z_vel = glm::vec3(0, 0, d_vel[2]);
    d_vel = calculateSlide(x_vel) + calculateSlide(y_vel) + calculateSlide(z_vel);
  }
  d_on_ground = std::abs(d_vel[1]) < 0.0001;
  //printPhys("After slide");
  d_pos += d_vel;
  syncAABB();

  //Update velocity for the next frame, unsure if this is the correct order
  d_vel -= (glm::vec3(0.2,0.1,0.2)*d_vel); //friction
  //as velocity approaches 0 make it exactly 0 to avoid clipping
  if(std::abs(d_vel[0]) < 0.001)
    d_vel[0] = 0;
  if(std::abs(d_vel[1]) < 0.001)
    d_vel[1] = 0;
  if(std::abs(d_vel[2]) < 0.001)
    d_vel[2] = 0;
  //printPhys("End update");

  d_postPhysics();
}

void PhysicsObject::setAcc(const glm::vec3& acc){
  d_acc = acc;
}
void PhysicsObject::setPos(const glm::vec3& pos){
  d_pos = pos;
  d_postPhysics();
}
void PhysicsObject::setVel(const glm::vec3& vel){
  d_vel = vel;
}
void PhysicsObject::incVel(const glm::vec3& vel){
  d_vel += vel;
}
