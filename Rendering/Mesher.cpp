#include "Mesher.hpp"
#include "VertexFormat.hpp"
#include "Cube.hpp"

#include <glm/glm.hpp>

#include <vector>
#include <unordered_set>
#include <iostream>

int Mesher::getIndex(int x, int y, int z){
  return y*16*16 + x*16 + z;
}

glm::vec4 Mesher::getColor(const Cube& c){
  if(c.type == 1)
    return glm::vec4(0.0f,1.0f,0.0f,1.0f);
  if(c.type == 2)
    return glm::vec4(1.0f,1.0f,1.0f,1.0f);
  if(c.type == 3)
    return glm::vec4(0.5f,0.5f,0.5f,1.0f);
  if(c.type == 4)
    return glm::vec4(0.3f,1.0f,1.0f,0.8f);
  return glm::vec4(1.0f,0.0f,0.0f,1.0f);
  
}

std::vector<VertexFormat> Mesher::createMesh(const std::vector<Cube>& chunk,
    const std::unordered_set<int>& occupied){
  std::vector<VertexFormat> ret;
  for(int i: occupied){
    //this funky cx cz math is to make sure relative and positive blocks are tracked the same way
    int cx;
    int cz;
    if(chunk[i].x < 0)
      cx = 15 - ((int)-chunk[i].x - 1)%16;
    else
      cx = (int)chunk[i].x%16;
    if(chunk[i].z < 0)
      cz = 15 - ((int)-chunk[i].z - 1)%16;
    else
      cz = (int)chunk[i].z%16;
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
      ret.push_back({{curr.x-0.5f, curr.y+0.5f, curr.z-0.5f},
        {c0, c1, c2, c3},{0,1,0}});
      ret.push_back({{curr.x+0.5f, curr.y+0.5f, curr.z-0.5f},
        {c0, c1, c2, c3},{0,1,0}});
      ret.push_back({{curr.x+0.5f, curr.y+0.5f, curr.z+0.5f},
        {c0, c1, c2, c3},{0,1,0}});

      ret.push_back({{curr.x+0.5f, curr.y+0.5f, curr.z+0.5f},
        {c0, c1, c2, c3},{0,1,0}});
      ret.push_back({{curr.x-0.5f, curr.y+0.5f, curr.z-0.5f},
        {c0, c1, c2, c3},{0,1,0}});
      ret.push_back({{curr.x-0.5f, curr.y+0.5f, curr.z+0.5f},
        {c0, c1, c2, c3},{0,1,0}});
    }
    if(occupied.count(bottomN) == 0 || cy == 0){
      ret.push_back({{curr.x-0.5f, curr.y-0.5f, curr.z-0.5f},
        {c0, c1, c2, c3},{0,-1,0}});
      ret.push_back({{curr.x+0.5f, curr.y-0.5f, curr.z-0.5f},
        {c0, c1, c2, c3},{0,-1,0}});
      ret.push_back({{curr.x+0.5f, curr.y-0.5f, curr.z+0.5f},
        {c0, c1, c2, c3},{0,-1,0}});

      ret.push_back({{curr.x+0.5f, curr.y-0.5f, curr.z+0.5f},
        {c0, c1, c2, c3},{0,-1,0}});
      ret.push_back({{curr.x-0.5f, curr.y-0.5f, curr.z-0.5f},
        {c0, c1, c2, c3},{0,-1,0}});
      ret.push_back({{curr.x-0.5f, curr.y-0.5f, curr.z+0.5f},
        {c0, c1, c2, c3},{0,-1,0}});
    }
    if(occupied.count(leftN) == 0 || cx == 0 || cx == 15){
      ret.push_back({{curr.x-0.5f, curr.y+0.5f, curr.z+0.5f},
        {c0, c1, c2, c3},{-1,0,0}});
      ret.push_back({{curr.x-0.5f, curr.y+0.5f, curr.z-0.5f},
        {c0, c1, c2, c3},{-1,0,0}});
      ret.push_back({{curr.x-0.5f, curr.y-0.5f, curr.z-0.5f},
        {c0, c1, c2, c3},{-1,0,0}});

      ret.push_back({{curr.x-0.5f, curr.y-0.5f, curr.z-0.5f},
        {c0, c1, c2, c3},{-1,0,0}});
      ret.push_back({{curr.x-0.5f, curr.y+0.5f, curr.z+0.5f},
        {c0, c1, c2, c3},{-1,0,0}});
      ret.push_back({{curr.x-0.5f, curr.y-0.5f, curr.z+0.5f},
        {c0, c1, c2, c3},{-1,0,0}});
    }
    if(occupied.count(rightN) == 0 || cx == 0 || cx == 15){
      ret.push_back({{curr.x+0.5f, curr.y+0.5f, curr.z+0.5f},
        {c0, c1, c2, c3},{1,0,0}});
      ret.push_back({{curr.x+0.5f, curr.y+0.5f, curr.z-0.5f},
        {c0, c1, c2, c3},{1,0,0}});
      ret.push_back({{curr.x+0.5f, curr.y-0.5f, curr.z-0.5f},
        {c0, c1, c2, c3},{1,0,0}});

      ret.push_back({{curr.x+0.5f, curr.y-0.5f, curr.z-0.5f},
        {c0, c1, c2, c3},{1,0,0}});
      ret.push_back({{curr.x+0.5f, curr.y+0.5f, curr.z+0.5f},
        {c0, c1, c2, c3},{1,0,0}});
      ret.push_back({{curr.x+0.5f, curr.y-0.5f, curr.z+0.5f},
        {c0, c1, c2, c3},{1,0,0}});
    }
    if(occupied.count(frontN) == 0 || cz == 0 || cz == 15){
      ret.push_back({{curr.x+0.5f, curr.y+0.5f, curr.z+0.5f},
        {c0, c1, c2, c3},{0,0,1}});
      ret.push_back({{curr.x+0.5f, curr.y-0.5f, curr.z+0.5f},
        {c0, c1, c2, c3},{0,0,1}});
      ret.push_back({{curr.x-0.5f, curr.y-0.5f, curr.z+0.5f},
        {c0, c1, c2, c3},{0,0,1}});

      ret.push_back({{curr.x-0.5f, curr.y-0.5f, curr.z+0.5f},
        {c0, c1, c2, c3},{0,0,1}});
      ret.push_back({{curr.x+0.5f, curr.y+0.5f, curr.z+0.5f},
        {c0, c1, c2, c3},{0,0,1}});
      ret.push_back({{curr.x-0.5f, curr.y+0.5f, curr.z+0.5f},
        {c0, c1, c2, c3},{0,0,1}});
    }
    if(occupied.count(backN) == 0 || cz == 0 || cz == 15){
      ret.push_back({{curr.x+0.5f, curr.y+0.5f, curr.z-0.5f},
        {c0, c1, c2, c3},{0,0,-1}});
      ret.push_back({{curr.x+0.5f, curr.y-0.5f, curr.z-0.5f},
        {c0, c1, c2, c3},{0,0,-1}});
      ret.push_back({{curr.x-0.5f, curr.y-0.5f, curr.z-0.5f},
        {c0, c1, c2, c3},{0,0,-1}});

      ret.push_back({{curr.x-0.5f, curr.y-0.5f, curr.z-0.5f},
        {c0, c1, c2, c3},{0,0,-1}});
      ret.push_back({{curr.x+0.5f, curr.y+0.5f, curr.z-0.5f},
        {c0, c1, c2, c3},{0,0,-1}});
      ret.push_back({{curr.x-0.5f, curr.y+0.5f, curr.z-0.5f},
        {c0, c1, c2, c3},{0,0,-1}});
    }
  }
  return ret;
}
