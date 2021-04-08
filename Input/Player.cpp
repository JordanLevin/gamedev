#include "Player.hpp"

#include <cmath>
#include <functional>

#include "../Rendering/Models/World.hpp"
#include "Camera.hpp"
#include "../Lib/Logger.hpp"


Player::Player(World* world, Camera* camera): PhysicsObject(
    std::bind(&Player::inputUpdate, this),
    std::bind(&Player::syncCamera, this))
{
  d_world = world;
  d_camera = camera;
}


void Player::syncCamera(){
  //d_player_mtx.lock();
  d_camera->eyeVector = d_pos;
  d_camera->updateView();
  //d_player_mtx.unlock();
}

void Player::inputUpdate(){
  float mult = 20*d_keys.count('f')+1;

  float dx = 0;
  float dz = 0;
  float dy = 0;
  //dz = -2;
  dz = -2*mult*d_keys.count('w') + 2*mult*d_keys.count('s');
  dx = -2*mult*d_keys.count('a') + 2*mult*d_keys.count('d');
  dy = 0.4*mult*d_keys.count(' ');

  glm::mat4& mat = *(d_camera->view_matrix);
  glm::vec3 forward(mat[0][2], mat[1][2], mat[2][2]);
  glm::vec3 strafe(mat[0][0], mat[1][0], mat[2][0]);
  //std::cout << mat[0][2] << " " << mat[1][2] << " " << mat[2][2] << std::endl;

  const float speed = 0.02;

  //make forward vector negative to look forward
  glm::vec3 acc = (-dz * forward + dx* strafe) * speed;
  if(!d_flying){
    acc[1] = 3*-0.0098;
    if(d_on_ground){
      acc[1] += dy;
    }
  }
  setAcc(acc);
}
