#include "Mesher.hpp"
#include "VertexFormat.hpp"
#include "Cube.hpp"

#include <glm/glm.hpp>

#include <vector>
#include <unordered_set>

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
  return glm::vec4(1.0f,0.0f,0.0f,1.0f);
  
}

std::vector<VertexFormat> Mesher::createMesh(const std::vector<Cube>& chunk,
    const std::unordered_set<int>& occupied){
  std::vector<VertexFormat> ret;
  for(int i: occupied){
    int cx = (int)chunk[i].x % 16;
    int cy = (int)chunk[i].y % 16;
    int cz = (int)chunk[i].z % 16;
    int topN = getIndex(cx, cy+1, cz);
    int bottomN = getIndex(cx, cy-1, cz);
    int leftN =  getIndex(cx-1, cy, cz);
    int rightN =  getIndex(cx+1, cy, cz);
    int frontN =  getIndex(cx, cy, cz+1);
    int backN =  getIndex(cx, cy, cz-1);
    const Cube& curr = chunk[i];
    glm::vec4 color = getColor(curr);
    //Generate vertices for sides that are open to air
    if(occupied.count(topN) == 0){
      ret.push_back({{curr.x-0.5f, curr.y+0.5f, curr.z-0.5f},
        color[0], color[1], color[2], color[3]});
      ret.push_back({{curr.x+0.5f, curr.y+0.5f, curr.z-0.5f},
        color[0], color[1], color[2], color[3]});
      ret.push_back({{curr.x+0.5f, curr.y+0.5f, curr.z+0.5f},
        color[0], color[1], color[2], color[3]});

      ret.push_back({{curr.x+0.5f, curr.y+0.5f, curr.z+0.5f},
        color[0], color[1], color[2], color[3]});
      ret.push_back({{curr.x-0.5f, curr.y+0.5f, curr.z-0.5f},
        color[0], color[1], color[2], color[3]});
      ret.push_back({{curr.x-0.5f, curr.y+0.5f, curr.z+0.5f},
        color[0], color[1], color[2], color[3]});
    }
    if(occupied.count(bottomN) == 0){
      ret.push_back({{curr.x-0.5f, curr.y-0.5f, curr.z-0.5f},
        color[0], color[1], color[2], color[3]});
      ret.push_back({{curr.x+0.5f, curr.y-0.5f, curr.z-0.5f},
        color[0], color[1], color[2], color[3]});
      ret.push_back({{curr.x+0.5f, curr.y-0.5f, curr.z+0.5f},
        color[0], color[1], color[2], color[3]});

      ret.push_back({{curr.x+0.5f, curr.y-0.5f, curr.z+0.5f},
        color[0], color[1], color[2], color[3]});
      ret.push_back({{curr.x-0.5f, curr.y-0.5f, curr.z-0.5f},
        color[0], color[1], color[2], color[3]});
      ret.push_back({{curr.x-0.5f, curr.y-0.5f, curr.z+0.5f},
        color[0], color[1], color[2], color[3]});
    }
    if(occupied.count(leftN) == 0){
      ret.push_back({{curr.x-0.5f, curr.y+0.5f, curr.z+0.5f},
        color[0], color[1], color[2], color[3]});
      ret.push_back({{curr.x-0.5f, curr.y+0.5f, curr.z-0.5f},
        color[0], color[1], color[2], color[3]});
      ret.push_back({{curr.x-0.5f, curr.y-0.5f, curr.z-0.5f},
        color[0], color[1], color[2], color[3]});

      ret.push_back({{curr.x-0.5f, curr.y-0.5f, curr.z-0.5f},
        color[0], color[1], color[2], color[3]});
      ret.push_back({{curr.x-0.5f, curr.y+0.5f, curr.z+0.5f},
        color[0], color[1], color[2], color[3]});
      ret.push_back({{curr.x-0.5f, curr.y-0.5f, curr.z+0.5f},
        color[0], color[1], color[2], color[3]});
    }
    if(occupied.count(rightN) == 0){
      ret.push_back({{curr.x+0.5f, curr.y+0.5f, curr.z+0.5f},
        color[0], color[1], color[2], color[3]});
      ret.push_back({{curr.x+0.5f, curr.y+0.5f, curr.z-0.5f},
        color[0], color[1], color[2], color[3]});
      ret.push_back({{curr.x+0.5f, curr.y-0.5f, curr.z-0.5f},
        color[0], color[1], color[2], color[3]});

      ret.push_back({{curr.x+0.5f, curr.y-0.5f, curr.z-0.5f},
        color[0], color[1], color[2], color[3]});
      ret.push_back({{curr.x+0.5f, curr.y+0.5f, curr.z+0.5f},
        color[0], color[1], color[2], color[3]});
      ret.push_back({{curr.x+0.5f, curr.y-0.5f, curr.z+0.5f},
        color[0], color[1], color[2], color[3]});
    }
    if(occupied.count(frontN) == 0){
      ret.push_back({{curr.x+0.5f, curr.y+0.5f, curr.z+0.5f},
        color[0], color[1], color[2], color[3]});
      ret.push_back({{curr.x+0.5f, curr.y-0.5f, curr.z+0.5f},
        color[0], color[1], color[2], color[3]});
      ret.push_back({{curr.x-0.5f, curr.y-0.5f, curr.z+0.5f},
        color[0], color[1], color[2], color[3]});

      ret.push_back({{curr.x-0.5f, curr.y-0.5f, curr.z+0.5f},
        color[0], color[1], color[2], color[3]});
      ret.push_back({{curr.x+0.5f, curr.y+0.5f, curr.z+0.5f},
        color[0], color[1], color[2], color[3]});
      ret.push_back({{curr.x-0.5f, curr.y+0.5f, curr.z+0.5f},
        color[0], color[1], color[2], color[3]});
    }
    if(occupied.count(backN) == 0){
      ret.push_back({{curr.x+0.5f, curr.y+0.5f, curr.z-0.5f},
        color[0], color[1], color[2], color[3]});
      ret.push_back({{curr.x+0.5f, curr.y-0.5f, curr.z-0.5f},
        color[0], color[1], color[2], color[3]});
      ret.push_back({{curr.x-0.5f, curr.y-0.5f, curr.z-0.5f},
        color[0], color[1], color[2], color[3]});

      ret.push_back({{curr.x-0.5f, curr.y-0.5f, curr.z-0.5f},
        color[0], color[1], color[2], color[3]});
      ret.push_back({{curr.x+0.5f, curr.y+0.5f, curr.z-0.5f},
        color[0], color[1], color[2], color[3]});
      ret.push_back({{curr.x-0.5f, curr.y+0.5f, curr.z-0.5f},
        color[0], color[1], color[2], color[3]});
    }
  }
  return ret;
}
