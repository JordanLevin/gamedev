#include "Player.hpp"

#include <cmath>

#include "Camera.hpp"
#include "../Rendering/Models/World.hpp"


Player::Player(World* world, Camera* camera):
  d_world{world},
  d_camera{camera}
{
  syncAABB();
}

void Player::syncAABB(){
  d_AABB = {
    glm::vec3{d_pos[0]-0.3,d_pos[1]-0.3,d_pos[2]-0.3},
    glm::vec3{d_pos[0]-0.3,d_pos[1]-0.3,d_pos[2]+0.3},
    glm::vec3{d_pos[0]-0.3,d_pos[1]+0.3,d_pos[2]-0.3},
    glm::vec3{d_pos[0]-0.3,d_pos[1]+0.3,d_pos[2]+0.3},
    glm::vec3{d_pos[0]+0.3,d_pos[1]-0.3,d_pos[2]-0.3},
    glm::vec3{d_pos[0]+0.3,d_pos[1]-0.3,d_pos[2]+0.3},
    glm::vec3{d_pos[0]+0.3,d_pos[1]+0.3,d_pos[2]-0.3},
    glm::vec3{d_pos[0]+0.3,d_pos[1]+0.3,d_pos[2]+0.3}
  };
}

void Player::syncCamera(){
  //d_player_mtx.lock();
  d_camera->eyeVector = d_pos;
  d_camera->updateView();
  //d_player_mtx.unlock();
}
void Player::incX(float x){
  d_pos[0] += x;
}
void Player::incY(float y){
  d_pos[1] += y;
}
void Player::incZ(float z){
  d_pos[2] += z;
}
bool Player::willCollide(){
  bool exists = false;
  for(const auto& point: d_AABB){
    glm::vec3 temp = point + d_vel;
    exists |= d_world->blockExists(temp);
  }
  return exists;
}

void Player::physicsUpdate(){
  if(d_world->blockExists(d_pos)){
    d_pos[1] = std::ceil(d_pos[1]+0.001);
  }
  if(willCollide()){
    d_vel = {0,0,0};
  }
  d_vel += d_acc;
  d_pos += d_vel;
  d_vel -= (glm::vec3(0.1,0.1,0.1)*d_vel);
  d_vel[1] -= 0.1;
  syncAABB();
  syncCamera();
}
void Player::setAcc(const glm::vec3& acc){
  d_acc = acc;
}
void Player::setPos(const glm::vec3& pos){
  d_pos = pos;
  syncCamera();
}
void Player::setVel(const glm::vec3& vel){
  d_vel = vel;
}
void Player::incVel(const glm::vec3& vel){
  d_vel += vel;
}
