#include "World.hpp"

#include <glm/glm.hpp>

#include <random>
#include <fstream>
#include <string>
#include <cmath>
#include <optional>
#include <thread>
#include <random>
#include <utility>
#include <algorithm>
#include <time.h>

PerlinNoise::PerlinNoise()
{
  unsigned seed = (int)time(NULL);
  std::mt19937 generator(seed);
  std::uniform_real_distribution distribution;
  auto dice = std::bind(distribution, generator);
  float gradientLen2;
  for (unsigned i = 0; i < tableSize; ++i) {
    do {
      gradients[i] = glm::vec2(2 * dice() - 1, 2 * dice() - 1);
      gradientLen2 = std::pow(glm::dot(gradients[i], gradients[i]), 2);
    } while (gradientLen2 > 1);
    gradients[i] /= sqrtf(gradientLen2); // normalize gradient
    permutationTable[i] = i;
  }

  std::uniform_int_distribution distributionInt;
  auto diceInt = std::bind(distributionInt, generator);
  // create permutation table
  for (unsigned i = 0; i < tableSize; ++i)
    std::swap(permutationTable[i], permutationTable[diceInt() & tableSizeMask]);
  // extend the permutation table in the index range [256:512]
  for (unsigned i = 0; i < tableSize; ++i) {
    permutationTable[tableSize + i] = permutationTable[i];
  }
}
float PerlinNoise::eval(const glm::vec2 &p) const
{
  int xi0 = ((int)std::floor(p.x)) & tableSizeMask;
  int yi0 = ((int)std::floor(p.y)) & tableSizeMask;

  int xi1 = (xi0 + 1) & tableSizeMask;
  int yi1 = (yi0 + 1) & tableSizeMask;

  float tx = p.x - ((int)std::floor(p.x));
  float ty = p.y - ((int)std::floor(p.y));

  float u = smoothstep(tx);
  float v = smoothstep(ty);

  // gradients at the corner of the cell
  const glm::vec2 &c00 = gradients[hash(xi0, yi0)];
  const glm::vec2 &c01 = gradients[hash(xi1, yi0)];
  const glm::vec2 &c10 = gradients[hash(xi0, yi1)];
  const glm::vec2 &c11 = gradients[hash(xi1, yi1)];

  // generate vectors going from the grid points to p
  float x0 = tx, x1 = tx - 1;
  float y0 = ty, y1 = ty - 1;

  glm::vec2 p00 = glm::vec2(x0, y0);
  glm::vec2 p01 = glm::vec2(x1, y0);
  glm::vec2 p10 = glm::vec2(x0, y1);
  glm::vec2 p11 = glm::vec2(x1, y1);

  // linear interpolation
  float a = lerp(dot(p00, c00), dot(p01, c01), u);
  float b = lerp(dot(p10, c10), dot(p11, c11), u);

  return lerp(a, b, v);
}

void World::deleteChunks(int thread){
  std::unique_lock<std::mutex> lock(d_mtx_delete);
  while(true){
    if(!camera){
      continue;
    }
    cv.wait(lock);

    for(int i = 0; i < 10; i++){
      if(d_write_q.empty()){
        break;
      }
      const std::pair<glm::ivec2, CubeCluster*> chunk = d_write_q.front();
      //std::cout << "writing " << chunk.first.x << " " << chunk.first.y << std::endl;
      d_write_q.pop_front();
      lock.unlock();
      writeChunk(chunk);
      lock.lock();
      d_erased_q.push_back(chunk);
    }
  }
}

void World::generateMeshes(){
  std::unique_lock<std::mutex> lock(d_mtx_mesh);
  while(true){
    if(!camera){
      continue;
    }
    cv.wait(lock);

    std::list<CubeCluster*> chunks;
    while(true){
        if(d_needmesh_q.empty()){
          break;
        }
        std::pair<glm::ivec2, CubeCluster*> chunk = d_needmesh_q.front();
        CubeCluster* c = chunk.second;
        d_needmesh_q.pop_front();
        lock.unlock();
        c->createMesh(this);
        d_meshed_q.push_back(chunk);
        lock.lock();
    }
  }

}

void World::generateChunks(int thread){
  std::unique_lock<std::mutex> lock(d_mtx_create);
  while(true){
    if(!camera){
      continue;
    }
    cv.wait(lock);

    while(true){
        if(d_needed_q.empty()){
          break;
        }
        const glm::ivec2 coords = d_needed_q.front();
        d_needed_q.pop_front();
        lock.unlock();
        CubeCluster* c = generate(coords.x, coords.y);
        lock.lock();
        d_generated_q.push_back(std::make_pair(coords, c));
    }
  }
}

CubeCluster* World::generate(int x, int z){
  glm::ivec2 coords(x,z);

  //Check if this chunk was already generated and saved 
  //TODO this will need work
  d_mtx_create.lock();
  bool found = generated.find(coords) != generated.end();
  //if someone else already genreated the chunk return it
  //if(cubes.find(coords)){
    //d_mtx_create.unlock();
    //return cubes.at(coords);
  //}
  d_mtx_create.unlock();
  if(found){
    CubeCluster* c = readChunk(x,z);
    return c;
  }

  CubeCluster* c = new CubeCluster(x, 0, z);
  c->setProgram(ShaderManager::getShader("cubeShader"));
  for(int row = 0; row < 16; row++){
    for(int col = 0; col < 16; col++){
      c->addChunkSpace(row,0,col, 3);
      //c->addChunkSpace(row,1,col, 3);
      int rowWorld = x*16 + row;
      int colWorld = z*16 + col;
      //overlap use varying perlin noise frequencies
      float height = noise.eval(glm::vec2((float)rowWorld/100.0, (float)colWorld/100.0))*30;
      height += noise.eval(glm::vec2((float)rowWorld/60.0, (float)colWorld/100.0))*4;
      height += noise.eval(glm::vec2((float)rowWorld/70.0, (float)colWorld/100.0))*4;
      height += noise.eval(glm::vec2((float)rowWorld/30.0, (float)colWorld/30.0))*3;
      height += noise.eval(glm::vec2((float)rowWorld/10.0, (float)colWorld/10.0))*1.1;
      height += 10;
      height = std::max((int)height, 9);
      height = std::min((int)height, 127);
        
      for(int h = 1; h < height; h++){
        if(height < 10)
          c->addChunkSpace(row,h,col, 7);
        else if(h > 40)
          c->addChunkSpace(row,h,col, 2);
        else if(h > 20)
          c->addChunkSpace(row,h,col,3);
        else if(h <= 3)
          c->addChunkSpace(row,h,col,6);
        else
          c->addChunkSpace(row,h,col, 1);
      }
    }
  }
  std::cout << "GENERATING " << x << " " << z << std::endl;
  c->d_ready = 0;
  return c;
}

void World::create(){
  outlineCube.setProgram(ShaderManager::getShader("cubeShader2"));
  int max_threads = 4;
  int gen_threads = (int)(max_threads-1)/2;
  int mesh_threads = std::min(max_threads-gen_threads-1, 1);
  int write_threads = std::min(max_threads-gen_threads-mesh_threads-1, 1);
  for(int i = 0; i < gen_threads; i++){
    d_world_gen.push_back(std::thread(&World::generateChunks, this, i));
    d_world_gen[i].detach();
  }
  for(int i = 0; i < mesh_threads; i++){
    d_world_gen.push_back(std::thread(&World::generateMeshes, this));
    d_world_gen[i+gen_threads].detach();
  }
  for(int i = 0; i < write_threads; i++){
    d_world_gen.push_back(std::thread(&World::deleteChunks, this, i));
    d_world_gen[i+gen_threads+mesh_threads].detach();
  }
}

void World::setCamera(Camera* camera_){
  camera = camera_;
}

void World::writeChunk(std::pair<glm::ivec2, CubeCluster*> chunk){
  std::string path = std::string("WORLDDATA/") + std::to_string(chunk.first.x) 
    + "_" + std::to_string(chunk.first.y);
    chunk.second->writeChunk(path);
}
CubeCluster* World::readChunk(int x, int z){
  std::string path = std::string("WORLDDATA/") + std::to_string(x) + "_" + std::to_string(z);
  CubeCluster* c = new CubeCluster(path, x, 0, z);
  c->setProgram(ShaderManager::getShader("cubeShader"));
  //c->createMesh(this);
  return c;
}

void World::draw(const glm::mat4& projection_matrix, const glm::mat4& view_matrix){
  int row_i = (camera->getX()/16) - d_render_dist;
  int row_f = (camera->getX()/16) + d_render_dist;
  int col_i = (camera->getZ()/16) - d_render_dist;
  int col_f = (camera->getZ()/16) + d_render_dist;
  std::vector<CubeCluster*> ready;

  std::cout << "Erased: " << d_erased_q.size() << std::endl;
  std::cout << "write: " << d_write_q.size() << std::endl;
  std::cout << "needed: " << d_needed_q.size() << std::endl;
  std::cout << "generated: " << d_generated_q.size() << std::endl;
  std::cout << "generated2: " << d_generated2_q.size() << std::endl;
  std::cout << "needmesh: " << d_needmesh_q.size() << std::endl;

  d_mtx_create.lock();
  while(!d_generated_q.empty()){
    const std::pair<glm::ivec2, CubeCluster*> elem = d_generated_q.front();
    d_generated_q.pop_front();
    d_generated2_q.push_back(elem);
    std::cout << "SETTING " << elem.first.x << " " << elem.first.y << " " << elem.second << std::endl;
    cubes[elem.first] = elem.second;
  }
  d_mtx_create.unlock();
  d_mtx_mesh.lock();
  auto it2 = d_generated2_q.begin();
  while(it2 != d_generated2_q.end()){
    //Need to verify chunks are both in cubes AND not null..kinda a mess
    auto chunk1it = cubes.find(glm::ivec2(it2->first[0]+1, it2->first[1]));
    auto chunk2it = cubes.find(glm::ivec2(it2->first[0]-1, it2->first[1]));
    auto chunk3it = cubes.find(glm::ivec2(it2->first[0], it2->first[1]+1));
    auto chunk4it = cubes.find(glm::ivec2(it2->first[0], it2->first[1]-1));

    bool chunk1 = false;
    bool chunk2 = false;
    bool chunk3 = false;
    bool chunk4 = false;
    if(chunk1it != cubes.end()){
      chunk1 = chunk1it->second != nullptr;
    }
    if(chunk2it != cubes.end()){
      chunk2 = chunk2it->second != nullptr;
    }
    if(chunk3it != cubes.end()){
      chunk3 = chunk3it->second != nullptr;
    }
    if(chunk4it != cubes.end()){
      chunk4 = chunk4it->second != nullptr;
    }

    if(chunk1 && chunk2 && chunk3 && chunk4){
      std::cout << "REQUESTING MESH " << it2->first[0] << " " << it2->first[1] << std::endl;
      d_needmesh_q.push_back(*it2);
      it2 = d_generated2_q.erase(it2);
    }
    else{
      it2++;
    }
  }
  d_mtx_mesh.unlock();
  for(auto it: cubes){
    std::cout << it.first[0] << " " << it.first[1] << " " << it.second << std::endl;
  }
  for(int row = row_i; row < row_f; row++){
    for(int col = col_i; col < col_f; col++){
      glm::ivec2 coords(row, col);
      if(cubes.count(coords) == 1){
        CubeCluster* c = cubes.at(coords);
        if(c != nullptr){
          if(c->d_ready == 1){
            c->createGL();
          }
          if(c->d_ready == 2){
            ready.push_back(c);
          }
        }
      }
      else{
        d_mtx_create.lock();
        std::cout << "ADDING TO NEEDED " << coords.x << " " << coords.y << std::endl;
        d_needed_q.push_back(coords);
        cubes[coords] = nullptr;
        d_mtx_create.unlock();
      }
  }
  }
  d_mtx_delete.lock();
  auto it = cubes.begin();
  while(it != cubes.end()){
    if(it->first.x > row_f + 2 || it->first.x < row_i - 2 ||
        it->first.y > col_f + 2 || it->first.y < col_i - 2){
      if(it->second)
        d_write_q.push_back(*it);
      it = cubes.erase(cubes.find(it->first));
    }
    else{
      it++;
    }
  }
  d_mtx_delete.unlock();

  //Signal worldgen threads if chunks need to be loaded or unloaded
  if(!d_needed_q.empty() || !d_write_q.empty()){
    cv.notify_all(); 
  }

  auto comp = [this](CubeCluster* a, CubeCluster* b){
    auto a_loc = glm::vec2(a->d_x, a->d_z);
    auto b_loc = glm::vec2(b->d_x, b->d_z);
    auto cam_loc = glm::vec2(this->camera->getX(), this->camera->getY());
    return glm::length(cam_loc - a_loc) > glm::length(cam_loc - b_loc);
  };
  std::make_heap(ready.begin(), ready.end(), comp);
  for(CubeCluster* chunk: ready){
    chunk->draw(projection_matrix, view_matrix);
  }
  for(CubeCluster* chunk: ready){
    chunk->drawTransparent(projection_matrix, view_matrix);
  }

  d_mtx_delete.lock();
  auto it1 = d_erased_q.begin();
  while(it1 != d_erased_q.end()){
    const auto& chunk = *it1;
    if(chunk.second->d_ready == 2){
      std::cout << "deleting " << chunk.first.x << " " << chunk.first.y << std::endl;
      delete chunk.second;
      it1 = d_erased_q.erase(it1);
    }
    else{
      it1++;
    }
  }
  d_mtx_delete.unlock();
  outlineCube.create();
  outlineCube.draw(projection_matrix, view_matrix);

}

//offset ceil/floor func, for dealing with how voxels are offset by 0.5
float World::maxT(float f, bool dir){
  if(dir)
    return std::ceil(f) - (f);
  else
    return (f) - std::floor(f);
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
    CubeCluster* chunk = getChunkFromWorldSpace(point);
    if(!chunk){
      //chunk may not exist due to multithreading
      return std::nullopt;
    }
    glm::vec3 ret = glm::vec3(std::floor(point[0]), std::floor(point[1]), std::floor(point[2]));
    if(chunk->get(ret[0], ret[1], ret[2])){
      if(!exact)
        return ret;
      else
        return point;
    }
  }
}

bool World::blockExists(const glm::vec3& coords) const{
  CubeCluster* chunk = getChunkFromWorldSpace(coords);
  if(!chunk)
    return false;
  bool exists = chunk->get(std::floor(coords[0]), std::floor(coords[1]), std::floor(coords[2]));
  return exists;
}

void World::breakBlock(const glm::vec3& location, const glm::vec3& direction){
  auto block = selectBlock(location, direction, 5, false);
  if(!block)
    return;
  auto blockVal = block.value();
  std::cout << "BREAKBLOCK: " << blockVal[0] << " " << blockVal[1] << " "  << blockVal[2] << std::endl;
  CubeCluster* chunk = getChunkFromWorldSpace(blockVal);
  std::cout << "CHUNK: " << chunk->d_x << " " << chunk->d_z << std::endl;
  bool res = chunk->remove(blockVal[0], blockVal[1], blockVal[2]);
  std::cout << res << std::endl;
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
  float tMaxX = std::abs((location[0]-blockVal[0] + (stepx))/direction[0]);
  float tMaxY = std::abs((location[1]-blockVal[1] + (stepy))/direction[1]);
  float tMaxZ = std::abs((location[2]-blockVal[2] + (stepz))/direction[2]);

  //Attempt to try all 3 T values, the idea is to throw away the values where
  //the point reached isnt actually on the surface of the target voxel

  //std::cout << "tvals: " << tMaxX << " " << tMaxY << " " << tMaxZ << std::endl;
  //std::cout << "blockvals: " << blockVal[0] << " " << blockVal[1] << " " << blockVal[2] << std::endl;
  glm::vec3 temp = location;
  temp += direction*tMaxX;
  if(std::floor(temp[1]) == blockVal[1] && std::floor(temp[2]) == blockVal[2]){
    //std::cout << "temp: " << temp[0] << " " << temp[1] << " " << temp[2] << std::endl;
    usex = true;
  }
  temp = location;
  temp += direction*tMaxY;
  if(std::floor(temp[0]) == blockVal[0] && std::floor(temp[2]) == blockVal[2]){
    //std::cout << "temp: " << temp[0] << " " << temp[1] << " " << temp[2] << std::endl;
    usey = true;
  }
  temp = location;
  temp += direction*tMaxZ;
  if(std::floor(temp[0]) == blockVal[0] && std::floor(temp[1]) == blockVal[1]){
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
  CubeCluster* chunk = getChunkFromWorldSpace(blockVal);
  if(!chunk)
    return;
  chunk->add(std::floor(blockVal[0]), std::floor(blockVal[1]), std::floor(blockVal[2]), 5);
  chunk->create(this);
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

/**Convert world coordinates to coordinates of chunk that voxel is in
  *chunk 1,1 contains voxels 0,0 through 15,15
  *chunk -1,-1 contains voxels -1,-1 through -16,-16
  */
CubeCluster* World::getChunkFromWorldSpace(const glm::vec3& coords) const{
  int x, z;
  if(coords[0] >= 0.0f)
    x = std::floor(coords[0])/16;
  else
    x = std::floor(coords[0]+1)/16 - 1;
  if(coords[2] >= 0.0f)
    z = std::floor(coords[2])/16;
  else
    z = std::floor(coords[2]+1)/16 - 1;
  try{
    CubeCluster* chunk = cubes.at(glm::ivec2(x,z));
    return chunk;
  }
  catch (const std::exception& e){
    std::cout << "getChunkFromWorldSpace failed: x: " << x << " z: " << z <<std::endl;
  }
  return nullptr;
}

/**
  * Return a chunk from chunk coordinates (vec3 for future conversion to 3d chunk coords)
  */
CubeCluster* World::getChunk(const glm::ivec3& coords) const{
  try{
    CubeCluster* chunk = cubes.at(glm::ivec2(coords[0],coords[2]));
    return chunk;
  }
  catch (const std::exception& e){
    //This fails often during efficient meshing
    //std::cout << "getChunk failed: chunkX: " << coords[0] << " chunkZ: " << coords[2] <<std::endl;
  }
  return nullptr;

}

void World::update(){

}
