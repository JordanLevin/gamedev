#include "World.hpp"

#include <glm/glm.hpp>

#include <random>
#include <fstream>
#include <string>
#include <cmath>

void NoiseGenerator::generateVectors(){
  gradient = std::vector<std::vector<std::vector<float>>>(MAX_X, 
      std::vector<std::vector<float>>(MAX_Y, std::vector<float>(2, 0.0)));
  for(int i = 0; i < MAX_X; i++){
    for(int j = 0; j < MAX_Y; j++){
      gradient[i][j][0] = (float)rand()/(float)RAND_MAX*2.0 - 1.0;
      gradient[i][j][1] = (float)rand()/(float)RAND_MAX*2.0 - 1.0;
    }
  }
}

float NoiseGenerator::lerp(float a0, float a1, float w) {
  return (1.0f - w)*a0 + w*a1;
}

// Computes the dot product of the distance and gradient vectors.
float NoiseGenerator::dotGridGradient(int ix, int iy, float x, float y) {


  // Compute the distance vector
  float dx = x - (float)ix;
  float dy = y - (float)iy;

  // Compute the dot-product
  return (dx*gradient[iy][ix][0] + dy*gradient[iy][ix][1]);
}

// Compute Perlin noise at coordinates x, y
float NoiseGenerator::perlin(float x, float y) {
  if(x < 0)
    x = -x;
  if(y < 0)
    y = -y;


  // Determine grid cell coordinates
  int x0 = (int)x;
  int x1 = x0 + 1;
  int y0 = (int)y;
  int y1 = y0 + 1;

  // Determine interpolation weights
  // Could also use higher order polynomial/s-curve here
  float sx = x - (float)x0;
  float sy = y - (float)y0;

  // Interpolate between grid point gradients
  float n0, n1, ix0, ix1, value;

  n0 = dotGridGradient(x0, y0, x, y);
  n1 = dotGridGradient(x1, y0, x, y);
  ix0 = lerp(n0, n1, sx);

  n0 = dotGridGradient(x0, y1, x, y);
  n1 = dotGridGradient(x1, y1, x, y);
  ix1 = lerp(n0, n1, sx);

  value = lerp(ix0, ix1, sy);
  return value;
}

void World::create(Camera* camera_){
  camera = camera_;
  noise.generateVectors();
  for(int x = -8; x < 8; x++){
    for(int y = -8; y < 8; y++){
      generate(x, y);
    }
  }
}

void World::writeChunk(int x, int z){
  glm::ivec2 coords(x,z);
  std::string path = std::string("WORLDDATA/") + std::to_string(x) + "_" + std::to_string(z);
  cubes[coords]->writeChunk(path);
  generated[coords] = true;
  delete cubes[coords];
}
CubeCluster* World::readChunk(int x, int z){
  std::string path = std::string("WORLDDATA/") + std::to_string(x) + "_" + std::to_string(z);
  CubeCluster* c = new CubeCluster(path);
  c->setProgram(ShaderManager::getShader("cubeShader"));
  c->create();
  return c;
}

void World::generate(int x, int z){
  glm::ivec2 coords(x,z);
  if(cubes.size() > 16*16){
    for(auto it = cubes.begin(); it != cubes.end(); it++){
      if(std::abs(it->first.x - camera->getX()/16) > 9 ||
          std::abs(it->first.y - camera->getZ()/16) > 9){
        writeChunk(it->first.x, it->first.y);
        cubes.erase(it);
        break;
      }
    }
  }

  //Check if this chunk was already generated and saved
  if(generated.find(coords) != generated.end()){
    cubes[coords] = readChunk(x,z);
    return;
  }
  
  //Generate a new chunk using perlin noise
  CubeCluster* c = new CubeCluster();
  c->setProgram(ShaderManager::getShader("cubeShader"));
  //c->add(0,0,0);
  for(int row = x*16; row < x*16 + 16; row++){
    for(int col = z*16; col < z*16 + 16; col++){
      c->add(row,0,col);
      float height = noise.perlin((float)row/10.0, (float)col/10.0)*50;
      for(int h = 1; h < height; h++){
        if(h > 8)
          c->add(row,h,col, 2);
        else
          c->add(row,h,col, 1);
      }
    }
  }
  c->create();
  cubes[coords] = c;
}

void World::draw(const glm::mat4& projection_matrix, const glm::mat4& view_matrix){
  int row_i = (camera->getX()/16) - 8; //arbitrary chunk size/render dist for now
  int row_f = (camera->getX()/16) + 8; //arbitrary chunk size/render dist for now
  int col_i = (camera->getZ()/16) - 8;
  int col_f = (camera->getZ()/16) + 8;
  for(int row = row_i; row < row_f; row++){
    for(int col = col_i; col < col_f; col++){
  //for(int row = -1; row < 0; row++){
    //for(int col = -1; col < 0; col++){
      if(cubes.count(glm::ivec2(row,col)) == 1)
        cubes[glm::ivec2(row,col)]->draw(projection_matrix, view_matrix);
      else{
        generate(row, col);
        cubes[glm::ivec2(row,col)]->draw(projection_matrix, view_matrix);
      }
    }
  }
}

void World::breakBlock(const glm::vec3& location, const glm::vec3& direction){
  //TODO
  //glm::vec3 point = location;
  //for(int i = 0; i < 5; i++){
    //point += direction;
    //IndexCube* chunk = chunkFromPoint(point);
    //if(chunk)
  //}
}

void World::update(){

}
