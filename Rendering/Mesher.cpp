#include "Mesher.hpp"
#include "VertexFormat.hpp"
#include "Cube.hpp"
#include "Models/World.hpp"

#include <glm/glm.hpp>

#include <vector>
#include <unordered_set>
#include <iostream>
#include <bitset>
#include <cstdlib>

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
  //std::cout << in.position[0] << "  " << in.position[1] << " " << in.position[2] << std::endl;
  uint32_t ret = 0;
  //add coords, WE NEED AN EXTRA BIT BECAUSE 16 CUBES = 17 VERTEX POSSIBILITIES
  ret |= ((int)(in.position[0]) & 0b11111);
  ret |= (((int)(in.position[1]) & 0b1111111) << 5); //WHATEVER JUST USE 7 BITS HERE FOR NOW CUZ Y COORD IS WEIRD
  ret |= (((int)(in.position[2]) & 0b11111) << 12);
  //add colors, lets just give a type and do colors in the shader
  ret |= ((type & 0b1111) << 17);
  //add normals
  uint8_t norm = ((int)in.normal[0] << 0) | ((int)in.normal[1] << 1) | ((int)in.normal[2] << 2);
  ret |= ((norm & 0b111) << 21);

  //std::bitset<32> tmp{ret};
  //std::cout << tmp << std::endl;
  return ret;
}

std::vector<uint32_t> Mesher::createMesh(const std::vector<Cube>& chunk,
    const std::unordered_set<int>& occupied, 
    const World* world, 
    int chunkX, 
    int chunkZ)
{
  std::vector<uint32_t> ret;
  for(int i: occupied){
    int cx = chunk[i].x;
    int cz = chunk[i].z;
    int cy = chunk[i].y;
    int topN = getIndex(cx, cy+1, cz);
    int bottomN = getIndex(cx, cy-1, cz);
    int leftN =  getIndex(cx-1, cy, cz);
    int rightN =  getIndex(cx+1, cy, cz);
    int frontN =  getIndex(cx, cy, cz+1);
    int backN =  getIndex(cx, cy, cz-1);
    const Cube& curr = chunk[i];
    glm::vec4 color = getColor(curr);
    float c0 = color[0];
    float c1 = color[1];
    float c2 = color[2];
    float c3 = color[3];

    //We add 0.5 so chunk corners are on integers, this hopefully will reduce other issues (this was moved from cubecluster to compress cubes from 16 bytes to 4 bytes)
    float currx = curr.x + 0.5;
    float curry = curr.y + 0.5;
    float currz = curr.z + 0.5;

    //Generate vertices for sides that are open to air
    if(occupied.count(topN) == 0 || cy == 127){
      ret.push_back(compressVertex({{currx-0.5f, curry+0.5f, currz-0.5f},
        {c0, c1, c2, c3},{0,1,0}}, curr.type));
      ret.push_back(compressVertex({{currx+0.5f, curry+0.5f, currz-0.5f},
        {c0, c1, c2, c3},{0,1,0}}, curr.type));
      ret.push_back(compressVertex({{currx+0.5f, curry+0.5f, currz+0.5f},
        {c0, c1, c2, c3},{0,1,0}}, curr.type));

      ret.push_back(compressVertex({{currx+0.5f, curry+0.5f, currz+0.5f},
        {c0, c1, c2, c3},{0,1,0}}, curr.type));
      ret.push_back(compressVertex({{currx-0.5f, curry+0.5f, currz-0.5f},
        {c0, c1, c2, c3},{0,1,0}}, curr.type));
      ret.push_back(compressVertex({{currx-0.5f, curry+0.5f, currz+0.5f},
        {c0, c1, c2, c3},{0,1,0}}, curr.type));
    }
    if(occupied.count(bottomN) == 0 || cy == 0){
      ret.push_back(compressVertex({{currx-0.5f, curry-0.5f, currz-0.5f},
        {c0, c1, c2, c3},{0,-1,0}}, curr.type));
      ret.push_back(compressVertex({{currx+0.5f, curry-0.5f, currz-0.5f},
        {c0, c1, c2, c3},{0,-1,0}}, curr.type));
      ret.push_back(compressVertex({{currx+0.5f, curry-0.5f, currz+0.5f},
        {c0, c1, c2, c3},{0,-1,0}}, curr.type));

      ret.push_back(compressVertex({{currx+0.5f, curry-0.5f, currz+0.5f},
        {c0, c1, c2, c3},{0,-1,0}}, curr.type));
      ret.push_back(compressVertex({{currx-0.5f, curry-0.5f, currz-0.5f},
        {c0, c1, c2, c3},{0,-1,0}}, curr.type));
      ret.push_back(compressVertex({{currx-0.5f, curry-0.5f, currz+0.5f},
        {c0, c1, c2, c3},{0,-1,0}}, curr.type));
    }
    if(occupied.count(leftN) == 0 || cx == 0){
      bool renderVertices = true;
      if(cx == 0){
        CubeCluster* neighborChunk = world->getChunk(glm::ivec3(chunkX-1, 0, chunkZ));
        if(neighborChunk){
          int neighborChunkIndex = getIndex(15, cy, cz);
          if(neighborChunk->getOccupied().count(neighborChunkIndex) != 0){
            renderVertices = false;
          }
        }
      }

      if(renderVertices){
      ret.push_back(compressVertex({{currx-0.5f, curry+0.5f, currz+0.5f},
        {c0, c1, c2, c3},{-1,0,0}}, curr.type));
      ret.push_back(compressVertex({{currx-0.5f, curry+0.5f, currz-0.5f},
        {c0, c1, c2, c3},{-1,0,0}}, curr.type));
      ret.push_back(compressVertex({{currx-0.5f, curry-0.5f, currz-0.5f},
        {c0, c1, c2, c3},{-1,0,0}}, curr.type));

      ret.push_back(compressVertex({{currx-0.5f, curry-0.5f, currz-0.5f},
        {c0, c1, c2, c3},{-1,0,0}}, curr.type));
      ret.push_back(compressVertex({{currx-0.5f, curry+0.5f, currz+0.5f},
        {c0, c1, c2, c3},{-1,0,0}}, curr.type));
      ret.push_back(compressVertex({{currx-0.5f, curry-0.5f, currz+0.5f},
        {c0, c1, c2, c3},{-1,0,0}}, curr.type));
      }
    }
    if(occupied.count(rightN) == 0 || cx == 15){
      bool renderVertices = true;
      if(cx == 15){
        CubeCluster* rightChunk = world->getChunk(glm::ivec3(chunkX+1, 0, chunkZ));
        if(rightChunk){
          int rightChunkIndex = getIndex(0, cy, cz);
          if(rightChunk->getOccupied().count(rightChunkIndex) != 0){
            renderVertices = false;
          }
        }
      }

      if(renderVertices){
        ret.push_back(compressVertex({{currx+0.5f, curry+0.5f, currz+0.5f},
          {c0, c1, c2, c3},{1,0,0}}, curr.type));
        ret.push_back(compressVertex({{currx+0.5f, curry+0.5f, currz-0.5f},
          {c0, c1, c2, c3},{1,0,0}}, curr.type));
        ret.push_back(compressVertex({{currx+0.5f, curry-0.5f, currz-0.5f},
          {c0, c1, c2, c3},{1,0,0}}, curr.type));

        ret.push_back(compressVertex({{currx+0.5f, curry-0.5f, currz-0.5f},
          {c0, c1, c2, c3},{1,0,0}}, curr.type));
        ret.push_back(compressVertex({{currx+0.5f, curry+0.5f, currz+0.5f},
          {c0, c1, c2, c3},{1,0,0}}, curr.type));
        ret.push_back(compressVertex({{currx+0.5f, curry-0.5f, currz+0.5f},
          {c0, c1, c2, c3},{1,0,0}}, curr.type));
      }
    }
    if(occupied.count(frontN) == 0 || cz == 15){
      bool renderVertices = true;
      if(cz == 15){
        CubeCluster* neighborChunk = world->getChunk(glm::ivec3(chunkX, 0, chunkZ+1));
        if(neighborChunk){
          int neighborChunkIndex = getIndex(cx, cy, 0);
          if(neighborChunk->getOccupied().count(neighborChunkIndex) != 0){
            renderVertices = false;
          }
        }
      }

      if(renderVertices){
      ret.push_back(compressVertex({{currx+0.5f, curry+0.5f, currz+0.5f},
        {c0, c1, c2, c3},{0,0,1}}, curr.type));
      ret.push_back(compressVertex({{currx+0.5f, curry-0.5f, currz+0.5f},
        {c0, c1, c2, c3},{0,0,1}}, curr.type));
      ret.push_back(compressVertex({{currx-0.5f, curry-0.5f, currz+0.5f},
        {c0, c1, c2, c3},{0,0,1}}, curr.type));

      ret.push_back(compressVertex({{currx-0.5f, curry-0.5f, currz+0.5f},
        {c0, c1, c2, c3},{0,0,1}}, curr.type));
      ret.push_back(compressVertex({{currx+0.5f, curry+0.5f, currz+0.5f},
        {c0, c1, c2, c3},{0,0,1}}, curr.type));
      ret.push_back(compressVertex({{currx-0.5f, curry+0.5f, currz+0.5f},
        {c0, c1, c2, c3},{0,0,1}}, curr.type));
    }
    }
    if(occupied.count(backN) == 0 || cz == 0){
      bool renderVertices = true;
      if(cz == 0){
        CubeCluster* neighborChunk = world->getChunk(glm::ivec3(chunkX, 0, chunkZ-1));
        if(neighborChunk){
          int neighborChunkIndex = getIndex(cx, cy, 15);
          if(neighborChunk->getOccupied().count(neighborChunkIndex) != 0){
            renderVertices = false;
          }
        }
      }

      if(renderVertices){
      ret.push_back(compressVertex({{currx+0.5f, curry+0.5f, currz-0.5f},
        {c0, c1, c2, c3},{0,0,-1}}, curr.type));
      ret.push_back(compressVertex({{currx+0.5f, curry-0.5f, currz-0.5f},
        {c0, c1, c2, c3},{0,0,-1}}, curr.type));
      ret.push_back(compressVertex({{currx-0.5f, curry-0.5f, currz-0.5f},
        {c0, c1, c2, c3},{0,0,-1}}, curr.type));

      ret.push_back(compressVertex({{currx-0.5f, curry-0.5f, currz-0.5f},
        {c0, c1, c2, c3},{0,0,-1}}, curr.type));
      ret.push_back(compressVertex({{currx+0.5f, curry+0.5f, currz-0.5f},
        {c0, c1, c2, c3},{0,0,-1}}, curr.type));
      ret.push_back(compressVertex({{currx-0.5f, curry+0.5f, currz-0.5f},
        {c0, c1, c2, c3},{0,0,-1}}, curr.type));
      }
    }
  }
  return ret;
}

std::vector<VertexFormat> Mesher::createUncompressedMesh(const std::vector<WorldCube>& chunk,
    const std::unordered_set<int>& occupied)
{
  std::vector<VertexFormat> ret;
  for(int i: occupied){
    int cx = chunk[i].x;
    int cz = chunk[i].z;
    int cy = chunk[i].y;
    int topN = getIndex(cx, cy+1, cz);
    int bottomN = getIndex(cx, cy-1, cz);
    int leftN =  getIndex(cx-1, cy, cz);
    int rightN =  getIndex(cx+1, cy, cz);
    int frontN =  getIndex(cx, cy, cz+1);
    int backN =  getIndex(cx, cy, cz-1);
    const WorldCube& curr = chunk[i];
    //glm::vec4 color = getColor(curr);
    glm::vec4 color = {1,1,1,1};
    float c0 = color[0];
    float c1 = color[1];
    float c2 = color[2];
    float c3 = color[3];

    //We add 0.5 so chunk corners are on integers, this hopefully will reduce other issues (this was moved from cubecluster to compress cubes from 16 bytes to 4 bytes)
    float currx = curr.x + 0.5;
    float curry = curr.y + 0.5;
    float currz = curr.z + 0.5;

    //Generate vertices for sides that are open to air
    if(occupied.count(topN) == 0 || cy == 127){
      ret.push_back({{currx-0.5f, curry+0.5f, currz-0.5f},
        {c0, c1, c2, c3},{0,1,0}});
      ret.push_back({{currx+0.5f, curry+0.5f, currz-0.5f},
        {c0, c1, c2, c3},{0,1,0}});
      ret.push_back({{currx+0.5f, curry+0.5f, currz+0.5f},
        {c0, c1, c2, c3},{0,1,0}});

      ret.push_back({{currx+0.5f, curry+0.5f, currz+0.5f},
        {c0, c1, c2, c3},{0,1,0}});
      ret.push_back({{currx-0.5f, curry+0.5f, currz-0.5f},
        {c0, c1, c2, c3},{0,1,0}});
      ret.push_back({{currx-0.5f, curry+0.5f, currz+0.5f},
        {c0, c1, c2, c3},{0,1,0}});
    }
    if(occupied.count(bottomN) == 0 || cy == 0){
      ret.push_back({{currx-0.5f, curry-0.5f, currz-0.5f},
        {c0, c1, c2, c3},{0,-1,0}});
      ret.push_back({{currx+0.5f, curry-0.5f, currz-0.5f},
        {c0, c1, c2, c3},{0,-1,0}});
      ret.push_back({{currx+0.5f, curry-0.5f, currz+0.5f},
        {c0, c1, c2, c3},{0,-1,0}});

      ret.push_back({{currx+0.5f, curry-0.5f, currz+0.5f},
        {c0, c1, c2, c3},{0,-1,0}});
      ret.push_back({{currx-0.5f, curry-0.5f, currz-0.5f},
        {c0, c1, c2, c3},{0,-1,0}});
      ret.push_back({{currx-0.5f, curry-0.5f, currz+0.5f},
        {c0, c1, c2, c3},{0,-1,0}});
    }
    if(occupied.count(leftN) == 0 || cx == 0){
      ret.push_back({{currx-0.5f, curry+0.5f, currz+0.5f},
        {c0, c1, c2, c3},{-1,0,0}});
      ret.push_back({{currx-0.5f, curry+0.5f, currz-0.5f},
        {c0, c1, c2, c3},{-1,0,0}});
      ret.push_back({{currx-0.5f, curry-0.5f, currz-0.5f},
        {c0, c1, c2, c3},{-1,0,0}});

      ret.push_back({{currx-0.5f, curry-0.5f, currz-0.5f},
        {c0, c1, c2, c3},{-1,0,0}});
      ret.push_back({{currx-0.5f, curry+0.5f, currz+0.5f},
        {c0, c1, c2, c3},{-1,0,0}});
      ret.push_back({{currx-0.5f, curry-0.5f, currz+0.5f},
        {c0, c1, c2, c3},{-1,0,0}});
    }
    if(occupied.count(rightN) == 0 || cx == 15){
        ret.push_back({{currx+0.5f, curry+0.5f, currz+0.5f},
          {c0, c1, c2, c3},{1,0,0}});
        ret.push_back({{currx+0.5f, curry+0.5f, currz-0.5f},
          {c0, c1, c2, c3},{1,0,0}});
        ret.push_back({{currx+0.5f, curry-0.5f, currz-0.5f},
          {c0, c1, c2, c3},{1,0,0}});

        ret.push_back({{currx+0.5f, curry-0.5f, currz-0.5f},
          {c0, c1, c2, c3},{1,0,0}});
        ret.push_back({{currx+0.5f, curry+0.5f, currz+0.5f},
          {c0, c1, c2, c3},{1,0,0}});
        ret.push_back({{currx+0.5f, curry-0.5f, currz+0.5f},
          {c0, c1, c2, c3},{1,0,0}});
    }
    if(occupied.count(frontN) == 0 || cz == 15){
      ret.push_back({{currx+0.5f, curry+0.5f, currz+0.5f},
        {c0, c1, c2, c3},{0,0,1}});
      ret.push_back({{currx+0.5f, curry-0.5f, currz+0.5f},
        {c0, c1, c2, c3},{0,0,1}});
      ret.push_back({{currx-0.5f, curry-0.5f, currz+0.5f},
        {c0, c1, c2, c3},{0,0,1}});

      ret.push_back({{currx-0.5f, curry-0.5f, currz+0.5f},
        {c0, c1, c2, c3},{0,0,1}});
      ret.push_back({{currx+0.5f, curry+0.5f, currz+0.5f},
        {c0, c1, c2, c3},{0,0,1}});
      ret.push_back({{currx-0.5f, curry+0.5f, currz+0.5f},
        {c0, c1, c2, c3},{0,0,1}});
    }
    if(occupied.count(backN) == 0 || cz == 0){
      ret.push_back({{currx+0.5f, curry+0.5f, currz-0.5f},
        {c0, c1, c2, c3},{0,0,-1}});
      ret.push_back({{currx+0.5f, curry-0.5f, currz-0.5f},
        {c0, c1, c2, c3},{0,0,-1}});
      ret.push_back({{currx-0.5f, curry-0.5f, currz-0.5f},
        {c0, c1, c2, c3},{0,0,-1}});

      ret.push_back({{currx-0.5f, curry-0.5f, currz-0.5f},
        {c0, c1, c2, c3},{0,0,-1}});
      ret.push_back({{currx+0.5f, curry+0.5f, currz-0.5f},
        {c0, c1, c2, c3},{0,0,-1}});
      ret.push_back({{currx-0.5f, curry+0.5f, currz-0.5f},
        {c0, c1, c2, c3},{0,0,-1}});
    }
  }
  return ret;
}
