#ifndef WORLD_H
#define WORLD_H

#include <glm/glm.hpp>

#include "../../Input/Camera.hpp"
#include "../../Rendering/Models/CubeCluster.hpp"
#include "../../Rendering/Models/SingleCube.hpp"
#include "../../Managers/ShaderManager.hpp"

#include <vector>
#include <map>
#include <unordered_map>
#include <utility>
#include <iostream>
#include <optional>

#define MAX_X 1000
#define MAX_Y 1000

class Camera;

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
    //The outlined cube
    SingleCube outlineCube;
    //A list of chunks that have been generated and saved in the world file
    std::map<glm::ivec2, bool, Comparator> generated;

  public:
    World() = default;
    ~World() = default;

    virtual void create() override final;
    void setCamera(Camera* camera_);
    void generate(int x, int y);
    void writeChunk(int x, int y);
    CubeCluster* readChunk(int x, int y);
    CubeCluster* getChunk(const glm::vec3& coords);
    virtual void draw(const glm::mat4& projection_matrix,
        const glm::mat4& view_matrix) override final;
    virtual void update() override final;
    float maxT(float f, bool dir);
    std::optional<glm::vec3> selectBlock(const glm::vec3& location,
        const glm::vec3& direction, int dist, bool exact);
    void breakBlock(const glm::vec3& location, const glm::vec3& direction);
    void placeBlock(const glm::vec3& location, const glm::vec3& direction);
    void outlineBlock(const glm::vec3& location, const glm::vec3& direction);
};


#endif
