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
#include <list>
#include <iostream>
#include <optional>
#include <thread>
#include <mutex>
#include <condition_variable>

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

class PerlinNoise
{
    static const unsigned tableSize = 256;
    static const unsigned tableSizeMask = tableSize - 1;
    std::array<glm::vec2, tableSize> gradients;
    unsigned permutationTable[tableSize * 2];


    /* inline */
    int hash(const int &x, const int &y) const
    { return permutationTable[permutationTable[x] + y]; }
    float lerp(float a0, float a1, float w) const {
      return (1.0f - w)*a0 + w*a1;
    }
    float smoothstep(const float &t) const
    {
        return t * t * (3 - 2 * t);
    }

  public:
    float eval(const glm::vec2 &p) const;
    PerlinNoise();
};

class World : public Model{
  private:
    Camera* camera;
    PerlinNoise noise;
    //A map of coordinates to world chunks that are currently in memory
    std::map<glm::ivec2, CubeCluster*, Comparator> cubes;
    //The outlined cube
    SingleCube outlineCube;
    //A list of chunks that have been generated and saved in the world file
    std::map<glm::ivec2, bool, Comparator> generated;

    void generateChunks(int thread);
    void deleteChunks(int thread);
    int d_render_dist = 10;
    std::list<std::pair<glm::ivec2, CubeCluster*>> d_erased_q; // chunk coords safe to deallocate
    std::list<std::pair<glm::ivec2, CubeCluster*>> d_write_q; // chunk coords to write to disk
    std::list<glm::ivec2> d_needed_q; //chunk coords we need to genreate
    std::list<std::pair<glm::ivec2, CubeCluster*>> d_generated_q; // chunks that got generated
    std::vector<std::thread> d_world_gen;
    std::mutex d_mtx_create;
    std::mutex d_mtx_delete;
    std::condition_variable cv;

  public:
    World() = default;
    ~World() = default;

    virtual void create() override final;
    void setCamera(Camera* camera_);
    CubeCluster* generate(int x, int y);
    void writeChunk(std::pair<glm::ivec2, CubeCluster*> chunk);
    CubeCluster* readChunk(int x, int y);
    bool blockExists(const glm::vec3& coords) const;
    CubeCluster* getChunkFromWorldSpace(const glm::vec3& coords) const;
    CubeCluster* getChunk(const glm::ivec3& coords) const;
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
