#include "World.hpp"

#include <glm/glm.hpp>

#include <random>
#include <fstream>
#include <string>
#include <cmath>
#include <optional>


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

void World::create(){
  outlineCube.setProgram(ShaderManager::getShader("cubeShader"));
  noise.generateVectors();
  for(int x = -8; x < 8; x++){
    for(int y = -8; y < 8; y++){
      generate(x, y);
    }
  }
}

void World::setCamera(Camera* camera_){
  camera = camera_;
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
      if(cubes.count(glm::ivec2(row,col)) == 1)
        cubes[glm::ivec2(row,col)]->draw(projection_matrix, view_matrix);
      else{
        generate(row, col);
        cubes[glm::ivec2(row,col)]->draw(projection_matrix, view_matrix);
      }
    }
  }
  outlineCube.create();
  outlineCube.draw(projection_matrix, view_matrix);
}

//offset ceil/floor func, for dealing with how voxels are offset by 0.5
float World::maxT(float f, bool dir){
  if(dir)
    return std::ceil(f+0.5) - (f + 0.5);
  else
    return (f - 0.5) - std::floor(f - 0.5);
}

//POTENTIAL ISSUE, this does not work at the axis, potentially related to the cube
//coordinates overlapping
std::optional<glm::vec3> World::selectBlock(const glm::vec3& location, const glm::vec3& direction, int dist, bool exact){
  glm::vec3 point = location;
  //http://www.cse.yorku.ca/~amana/research/grid.pdf ray cast algo
  float tMaxX, tMaxY, tMaxZ;
  float stepx = (direction[0]> 0)*2-1;
  float stepy = (direction[1]> 0)*2-1;
  float stepz = (direction[2]> 0)*2-1;
  float tDeltaX = abs(1.0/direction[0]);
  float tDeltaY = abs(1.0/direction[1]);
  float tDeltaZ = abs(1.0/direction[2]);
  tMaxX = maxT(point[0], direction[0] > 0)/std::abs(direction[0]);
  tMaxY = maxT(point[1], direction[1] > 0)/std::abs(direction[1]);
  tMaxZ = maxT(point[2], direction[2] > 0)/std::abs(direction[2]);

  for(;;){
    //std::cout << "wooo\n" << point[0] << " "<<  point[1] <<" " << point[2] << std::endl;
    //std::cout << "ts\n" << tMaxX << " "<<  tMaxY <<" " << tMaxZ << std::endl;
    if(std::abs(glm::length(point-location)) > dist){
      return std::nullopt;
    }
    if(tMaxX < tMaxY) 
    {
      if(tMaxX < tMaxZ) 
      {
        point[0] = point[0]  + stepx;
        tMaxX= tMaxX + tDeltaX;
      } else  
      {
        point[2]= point[2] + stepz;
        tMaxZ= tMaxZ + tDeltaZ;
      }
    } 
    else  {
      if(tMaxY < tMaxZ) {
        point[1]= point[1] + stepy;
        tMaxY= tMaxY + tDeltaY;
      } else  
      {
        point[2]= point[2] + stepz;
        tMaxZ= tMaxZ + tDeltaZ;
      }
    }

    //find points chunk and check if non empty
    CubeCluster* chunk = getChunk(point);
    glm::vec3 ret = glm::vec3(std::round(point[0]), std::round(point[1]), std::round(point[2]));
    if(chunk->get(ret[0], ret[1], ret[2])){
      if(!exact)
        return ret;
      else
        return point;
    }
  }
}

void World::breakBlock(const glm::vec3& location, const glm::vec3& direction){
  auto block = selectBlock(location, direction, 5, false);
  if(!block)
    return;
  auto blockVal = block.value();
  CubeCluster* chunk = getChunk(blockVal);
  chunk->remove(blockVal[0], blockVal[1], blockVal[2]);
  outlineBlock(location, direction);
}

void World::placeBlock(const glm::vec3& location, const glm::vec3& direction){
  auto block = selectBlock(location, direction, 5, false);
  if(!block)
    return;
  auto blockVal = block.value();
  float stepx = (direction[0]> 0)*2-1;
  float stepy = (direction[1]> 0)*2-1;
  float stepz = (direction[2]> 0)*2-1;
  bool usex = false;
  bool usey = false;
  bool usez = false;
  //Determine the amount to scale direction to reach the x,y,z planes at the target voxel
  float tMaxX = std::abs((location[0]-blockVal[0] + 0.5*(stepx))/direction[0]);
  float tMaxY = std::abs((location[1]-blockVal[1] + 0.5*(stepy))/direction[1]);
  float tMaxZ = std::abs((location[2]-blockVal[2] + 0.5*(stepz))/direction[2]);

  //Attempt to try all 3 T values, the idea is to throw away the values where
  //the point reached isnt actually on the surface of the target voxel

  //std::cout << "tvals: " << tMaxX << " " << tMaxY << " " << tMaxZ << std::endl;
  //std::cout << "blockvals: " << blockVal[0] << " " << blockVal[1] << " " << blockVal[2] << std::endl;
  glm::vec3 temp = location;
  temp += direction*tMaxX;
  if(std::round(temp[1]) == blockVal[1] && std::round(temp[2]) == blockVal[2]){
    //std::cout << "temp: " << temp[0] << " " << temp[1] << " " << temp[2] << std::endl;
    usex = true;
  }
  temp = location;
  temp += direction*tMaxY;
  if(std::round(temp[0]) == blockVal[0] && std::round(temp[2]) == blockVal[2]){
    //std::cout << "temp: " << temp[0] << " " << temp[1] << " " << temp[2] << std::endl;
    usey = true;
  }
  temp = location;
  temp += direction*tMaxZ;
  if(std::round(temp[0]) == blockVal[0] && std::round(temp[1]) == blockVal[1]){
    usez = true;
    //std::cout << "temp: " << temp[0] << " " << temp[1] << " " << temp[2] << std::endl;
  }

  //There can theoretically be multiple candidates if the camera is between the 2 opposing
  //faces of the voxel (this results in the ray hitting a face that isnt actually visible)
  //TODO there must be a better way to handle this issue
  if(usex && usey){
    if(tMaxX < tMaxY)
      blockVal[0] -= stepx;
    else
      blockVal[1] -= stepy;
  }
  else if(usey && usez){
    if(tMaxY < tMaxZ)
      blockVal[1] -= stepy;
    else
      blockVal[2] -= stepz;
  }
  else if(usex && usez){
    if(tMaxX < tMaxZ)
      blockVal[0] -= stepx;
    else
      blockVal[2] -= stepz;
  }
  else if(usex)
    blockVal[0] -= stepx;
  else if(usey)
    blockVal[1] -= stepy;
  else if(usez)
    blockVal[2] -= stepz;
  //std::cout << "after: " << blockVal[0] << " " << blockVal[1] << " " << blockVal[2] << std::endl;
  CubeCluster* chunk = getChunk(blockVal);
  chunk->add(std::round(blockVal[0]), std::round(blockVal[1]), std::round(blockVal[2]), 5);
  chunk->create();
  outlineBlock(location, direction);
}

void World::outlineBlock(const glm::vec3& location, const glm::vec3& direction){
  auto block = selectBlock(location, direction, 5, false);
  if(!block){
    outlineCube.set(-1,-1,-1);
    return;
  }
  auto blockVal = block.value();
  outlineCube.set(blockVal[0], blockVal[1], blockVal[2]);
}

CubeCluster* World::getChunk(const glm::vec3& coords){
  int x, z;
  if(coords[0] > 0.0f)
    x = (int)coords[0]/16;
  else
    x = (int)coords[0]/16 - 1;
  if(coords[2] > 0.0f)
    z = (int)coords[2]/16;
  else
    z = (int)coords[2]/16 - 1;
  CubeCluster* chunk = cubes[glm::ivec2(x,z)];
  return chunk;
}

void World::update(){

}
