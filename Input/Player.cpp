#include "Player.hpp"

#include <cmath>

#include "../Rendering/Models/World.hpp"
#include "Camera.hpp"


Player::Player(World* world, Camera* camera): PhysicsObject()
{
  d_world = world;
  d_camera = camera;
  syncAABB();
}

void Player::printPhys(std::string msg){
  std::cout << msg << std::endl;
  std::cout << "POS x: " << d_pos[0] << " y: " << d_pos[1] << " z: " << d_pos[2] << "  " << 
               "VEL x: " << d_vel[0] << " y: " << d_vel[1] << " z: " << d_vel[2] <<
               "| g: " << d_on_ground << std::endl;
}

void Player::syncAABB(){
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
bool Player::willCollide(const glm::vec3& vel){
  bool exists = false;
  for(const auto& point: d_AABB){
    glm::vec3 temp = point + vel;
    exists |= d_world->blockExists(temp);
  }
  return exists;
}

glm::vec3 Player::calculateSlide(const glm::vec3& vel){
  bool exists = false;
  glm::vec3 res(0,0,0);
  for(const auto& point: d_AABB){
    glm::vec3 temp = point + vel;
    glm::vec3 temp2 = point;
    if(d_world->blockExists(temp)){
      std::cout << "collide: " << temp[0] << " " << temp[1] << " " << temp[2] << std::endl;
      temp2[0] += vel[0];
      if(!d_world->blockExists(temp2)){
        res[0] = vel[0];
      }
      temp2[0] -= vel[0];
      temp2[1] += vel[1];
      if(!d_world->blockExists(temp2)){
        res[1] = vel[1];
      }
      temp2[1] -= vel[1];
      temp2[2] += vel[2];
      if(!d_world->blockExists(temp2)){
        res[2] = vel[2];
      }
      exists = true;
      break;
    }
    else{
      std::cout << "no collide: " << temp[0] << " " << temp[1] << " " << temp[2] << std::endl;
    }
  }

  if(!exists){
    return vel;
  }
  return res;

}

void Player::physicsUpdate(){
  inputUpdate();
  d_vel += d_acc;
  printPhys("After update");
  //Calculate collision for this frame and update pos
  if(willCollide(d_vel)){
    d_vel = calculateSlide(d_vel);
  }
  printPhys("After slide");
  d_pos += d_vel;
  syncAABB();
  syncCamera();

  //Update velocity for the next frame, unsure if this is the correct order
  d_vel -= (glm::vec3(0.1,0.1,0.1)*d_vel); //friction
  //as velocity approaches 0 make it exactly 0 to avoid clipping
  if(std::abs(d_vel[0]) < 0.001)
    d_vel[0] = 0;
  if(std::abs(d_vel[1]) < 0.001)
    d_vel[1] = 0;
  if(std::abs(d_vel[2]) < 0.001)
    d_vel[2] = 0;
  //if(!d_on_ground){
    //d_vel[1] -= 0.3;
  //}
  //while(willCollide(glm::vec3(0,0,0))){
    //d_pos[1] = std::ceil(d_pos[1]-d_height + 0.001) + d_height;
    //syncAABB();
  //}
  d_on_ground = d_world->blockExists(glm::vec3(d_pos[0], d_pos[1]-.001, d_pos[2]));
  printPhys("End update");
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

void Player::inputUpdate(){
  float mult = 20*d_keys.count('f')+1;

  float dx = 0;
  float dz = 0;
  float dy = 0;
  //dz = -2;
  dz = -2*mult*d_keys.count('w') + 2*mult*d_keys.count('s');
  dx = -2*mult*d_keys.count('a') + 2*mult*d_keys.count('d');
  dy = 1*mult*d_keys.count(' ');

  glm::mat4& mat = *(d_camera->view_matrix);
  glm::vec3 forward(mat[0][2], mat[1][2], mat[2][2]);
  glm::vec3 strafe(mat[0][0], mat[1][0], mat[2][0]);
  //std::cout << mat[0][2] << " " << mat[1][2] << " " << mat[2][2] << std::endl;

  const float speed = 0.02;

  //make forward vector negative to look forward
  glm::vec3 acc = (-dz * forward + dx* strafe) * speed;
  if(!d_flying)
    acc[1] = -0.0098;
  setAcc(acc);
}
