#ifndef WORLD_H
#define WORLD_H

#include <glm/glm.hpp>

#include "../../Rendering/Models/CubeCluster.hpp"
#include "../../Input/Camera.hpp"
#include "../../Managers/ShaderManager.hpp"
#include "../../Lib/OctTree.hpp"

#include <vector>
#include <map>
#include <unordered_map>
#include <utility>
#include <iostream>

#define MAX_X 1000
#define MAX_Y 1000

struct Comparator{
  bool operator()(const glm::ivec2& a, const glm::ivec2& b)const noexcept
  {
    if(a.x < b.x)
      return true;
    if(a.x > b.x)
      return false;
    return a.y < b.y;
  }
};

struct NoiseGenerator{
  // Precomputed (or otherwise) gradient vectors at each grid node
  std::vector<std::vector<std::vector<float>>> gradient;

  void generateVectors();
  float lerp(float a0, float a1, float w);
  float dotGridGradient(int ix, int iy, float x, float y);
  float perlin(float x, float y);
};

class World : public Model{
  private:
    Camera* camera;
    NoiseGenerator noise;
    //A map of coordinates to world chunks that are currently in memory
    std::map<glm::ivec2, CubeCluster*, Comparator> cubes;
    //A list of chunks that have been generated and saved in the world file
    std::map<glm::ivec2, bool, Comparator> generated;

  public:
    World() = default;
    ~World() = default;

    void create(Camera* camera_);
    void generate(int x, int y);
    void writeChunk(int x, int y);
    CubeCluster* readChunk(int x, int y);
    virtual void draw(const glm::mat4& projection_matrix, const glm::mat4& view_matrix) override final;
    virtual void update() override final;
    

};


#endif
