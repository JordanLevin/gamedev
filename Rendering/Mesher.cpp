#include "Mesher.hpp"
#include "VertexFormat.hpp"
#include "Cube.hpp"

#include <glm/glm.hpp>

#include <vector>
#include <unordered_set>
#include <iostream>
#include <cstdlib>
#include <bitset>

int Mesher::getIndex(int x, int y, int z){
  return y*16*16 + x*16 + z;
}

glm::vec4 Mesher::getColor(const Cube& c){
  if(c.type == 1)
    return glm::vec4(0.066f, 0.396f, 0.043f, 1.0f);
  if(c.type == 2)
    return glm::vec4(1.0f,1.0f,1.0f,1.0f);
  if(c.type == 3)
    return glm::vec4(0.5f,0.5f,0.5f,1.0f);
  if(c.type == 4)
    return glm::vec4(0.3f,1.0f,1.0f,0.8f);
  if(c.type == 6)
    return glm::vec4(0.909, 0.843, 0.172, 1.0f); // yellow
  if(c.type == 7)
    return glm::vec4(0.094, 0.141, 0.725, 1.0f); // blue
  return glm::vec4(std::rand()/(float)RAND_MAX,std::rand()/(float)RAND_MAX,std::rand()/(float)RAND_MAX,1.0f);
}

//Compress a vertex into a uint32, assume that all coordinates are in chunkspace (<16)
uint32_t Mesher::compressVertex(VertexFormat in, uint8_t type){
  uint32_t ret = 0;
  //add coords
  ret |= ((int)(in.position[0]) & 0b1111);
  ret |= (((int)(in.position[1]) >> 4) & 0b1111);
  ret |= (((int)(in.position[2]) >> 8) & 0b1111);
  //add colors, lets just give a type and do colors in the shader
  ret |= ((type >> 12) & 0b1111);
  //add normals
  uint8_t norm = ((int)in.normal[0] << 0) | ((int)in.normal[1] << 1) | ((int)in.normal[2] << 2);
  ret |= ((norm & 0b111) << 16);

  return ret;
}

std::vector<uint32_t> Mesher::createMesh(const std::vector<Cube>& chunk,
    const std::unordered_set<int>& occupied){
  std::vector<uint32_t> ret;
  for(int i: occupied){
    //this funky cx cz math is to make sure relative and positive blocks are tracked the same way
    int cx = chunk[i].x;
    int cz = chunk[i].z;
    //if(chunk[i].x < 0)
      //cx = 15 - ((int)-chunk[i].x - 1)%16;
    //else
      //cx = (int)chunk[i].x%16;
    //if(chunk[i].z < 0)
      //cz = 15 - ((int)-chunk[i].z - 1)%16;
    //else
      //cz = (int)chunk[i].z%16;
    int cy = chunk[i].y;
    int topN = getIndex(cx, cy+1, cz);
    int bottomN = getIndex(cx, cy-1, cz);
    int leftN =  getIndex(cx-1, cy, cz);
    int rightN =  getIndex(cx+1, cy, cz);
    int frontN =  getIndex(cx, cy, cz+1);
    int backN =  getIndex(cx, cy, cz-1);
    const Cube& curr = chunk[i];
    glm::vec4 color = getColor(curr);
    //Generate vertices for sides that are open to air
    float c0 = color[0];
    float c1 = color[1];
    float c2 = color[2];
    float c3 = color[3];
    if(occupied.count(topN) == 0 || cy == 127){
      ret.push_back(compressVertex({{curr.x-0.5f, curr.y+0.5f, curr.z-0.5f},
        {c0, c1, c2, c3},{0,1,0}}, curr.type));
      ret.push_back(compressVertex({{curr.x+0.5f, curr.y+0.5f, curr.z-0.5f},
        {c0, c1, c2, c3},{0,1,0}}, curr.type));
      ret.push_back(compressVertex({{curr.x+0.5f, curr.y+0.5f, curr.z+0.5f},
        {c0, c1, c2, c3},{0,1,0}}, curr.type));

      ret.push_back(compressVertex({{curr.x+0.5f, curr.y+0.5f, curr.z+0.5f},
        {c0, c1, c2, c3},{0,1,0}}, curr.type));
      ret.push_back(compressVertex({{curr.x-0.5f, curr.y+0.5f, curr.z-0.5f},
        {c0, c1, c2, c3},{0,1,0}}, curr.type));
      ret.push_back(compressVertex({{curr.x-0.5f, curr.y+0.5f, curr.z+0.5f},
        {c0, c1, c2, c3},{0,1,0}}, curr.type));
      std::bitset<32> tmp{ret[0]};
      std::cout << tmp << std::endl;
    }
    if(occupied.count(bottomN) == 0 || cy == 0){
      ret.push_back(compressVertex({{curr.x-0.5f, curr.y-0.5f, curr.z-0.5f},
        {c0, c1, c2, c3},{0,-1,0}}, curr.type));
      ret.push_back(compressVertex({{curr.x+0.5f, curr.y-0.5f, curr.z-0.5f},
        {c0, c1, c2, c3},{0,-1,0}}, curr.type));
      ret.push_back(compressVertex({{curr.x+0.5f, curr.y-0.5f, curr.z+0.5f},
        {c0, c1, c2, c3},{0,-1,0}}, curr.type));

      ret.push_back(compressVertex({{curr.x+0.5f, curr.y-0.5f, curr.z+0.5f},
        {c0, c1, c2, c3},{0,-1,0}}, curr.type));
      ret.push_back(compressVertex({{curr.x-0.5f, curr.y-0.5f, curr.z-0.5f},
        {c0, c1, c2, c3},{0,-1,0}}, curr.type));
      ret.push_back(compressVertex({{curr.x-0.5f, curr.y-0.5f, curr.z+0.5f},
        {c0, c1, c2, c3},{0,-1,0}}, curr.type));
    }
    if(occupied.count(leftN) == 0 || cx == 0 || cx == 15){
      ret.push_back(compressVertex({{curr.x-0.5f, curr.y+0.5f, curr.z+0.5f},
        {c0, c1, c2, c3},{-1,0,0}}, curr.type));
      ret.push_back(compressVertex({{curr.x-0.5f, curr.y+0.5f, curr.z-0.5f},
        {c0, c1, c2, c3},{-1,0,0}}, curr.type));
      ret.push_back(compressVertex({{curr.x-0.5f, curr.y-0.5f, curr.z-0.5f},
        {c0, c1, c2, c3},{-1,0,0}}, curr.type));

      ret.push_back(compressVertex({{curr.x-0.5f, curr.y-0.5f, curr.z-0.5f},
        {c0, c1, c2, c3},{-1,0,0}}, curr.type));
      ret.push_back(compressVertex({{curr.x-0.5f, curr.y+0.5f, curr.z+0.5f},
        {c0, c1, c2, c3},{-1,0,0}}, curr.type));
      ret.push_back(compressVertex({{curr.x-0.5f, curr.y-0.5f, curr.z+0.5f},
        {c0, c1, c2, c3},{-1,0,0}}, curr.type));
    }
    if(occupied.count(rightN) == 0 || cx == 0 || cx == 15){
      ret.push_back(compressVertex({{curr.x+0.5f, curr.y+0.5f, curr.z+0.5f},
        {c0, c1, c2, c3},{1,0,0}}, curr.type));
      ret.push_back(compressVertex({{curr.x+0.5f, curr.y+0.5f, curr.z-0.5f},
        {c0, c1, c2, c3},{1,0,0}}, curr.type));
      ret.push_back(compressVertex({{curr.x+0.5f, curr.y-0.5f, curr.z-0.5f},
        {c0, c1, c2, c3},{1,0,0}}, curr.type));

      ret.push_back(compressVertex({{curr.x+0.5f, curr.y-0.5f, curr.z-0.5f},
        {c0, c1, c2, c3},{1,0,0}}, curr.type));
      ret.push_back(compressVertex({{curr.x+0.5f, curr.y+0.5f, curr.z+0.5f},
        {c0, c1, c2, c3},{1,0,0}}, curr.type));
      ret.push_back(compressVertex({{curr.x+0.5f, curr.y-0.5f, curr.z+0.5f},
        {c0, c1, c2, c3},{1,0,0}}, curr.type));
    }
    if(occupied.count(frontN) == 0 || cz == 0 || cz == 15){
      ret.push_back(compressVertex({{curr.x+0.5f, curr.y+0.5f, curr.z+0.5f},
        {c0, c1, c2, c3},{0,0,1}}, curr.type));
      ret.push_back(compressVertex({{curr.x+0.5f, curr.y-0.5f, curr.z+0.5f},
        {c0, c1, c2, c3},{0,0,1}}, curr.type));
      ret.push_back(compressVertex({{curr.x-0.5f, curr.y-0.5f, curr.z+0.5f},
        {c0, c1, c2, c3},{0,0,1}}, curr.type));

      ret.push_back(compressVertex({{curr.x-0.5f, curr.y-0.5f, curr.z+0.5f},
        {c0, c1, c2, c3},{0,0,1}}, curr.type));
      ret.push_back(compressVertex({{curr.x+0.5f, curr.y+0.5f, curr.z+0.5f},
        {c0, c1, c2, c3},{0,0,1}}, curr.type));
      ret.push_back(compressVertex({{curr.x-0.5f, curr.y+0.5f, curr.z+0.5f},
        {c0, c1, c2, c3},{0,0,1}}, curr.type));
    }
    if(occupied.count(backN) == 0 || cz == 0 || cz == 15){
      ret.push_back(compressVertex({{curr.x+0.5f, curr.y+0.5f, curr.z-0.5f},
        {c0, c1, c2, c3},{0,0,-1}}, curr.type));
      ret.push_back(compressVertex({{curr.x+0.5f, curr.y-0.5f, curr.z-0.5f},
        {c0, c1, c2, c3},{0,0,-1}}, curr.type));
      ret.push_back(compressVertex({{curr.x-0.5f, curr.y-0.5f, curr.z-0.5f},
        {c0, c1, c2, c3},{0,0,-1}}, curr.type));

      ret.push_back(compressVertex({{curr.x-0.5f, curr.y-0.5f, curr.z-0.5f},
        {c0, c1, c2, c3},{0,0,-1}}, curr.type));
      ret.push_back(compressVertex({{curr.x+0.5f, curr.y+0.5f, curr.z-0.5f},
        {c0, c1, c2, c3},{0,0,-1}}, curr.type));
      ret.push_back(compressVertex({{curr.x-0.5f, curr.y+0.5f, curr.z-0.5f},
        {c0, c1, c2, c3},{0,0,-1}}, curr.type));
    }
  }
  return ret;
}
