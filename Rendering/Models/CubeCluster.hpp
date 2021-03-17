#ifndef CUBECLUSTER_H
#define CUBECLUSTER_H

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "Model.hpp"
#include "../Cube.hpp"
#include "../VertexFormat.hpp"

#include <stdarg.h>
#include <string>
#include <array>
#include <unordered_set>

#define DATA_SIZE 16*16*128

class World;

class CubeCluster: public Model {
  private:
    World* d_world;

    uint32_t getIndex(const glm::vec3& coord);
    //convert global coordinates to chunk coordinates
    glm::vec3 coordsInChunk(const glm::vec3& coord);

    //Mesh data to render
    std::vector<uint32_t> d_opaqueMesh;
    std::vector<uint32_t> d_transparentMesh;
    int d_osz;

    //Actual entire chunk of cubes
    std::vector<Cube> d_cubes = std::vector<Cube>(DATA_SIZE);

    //Occupied cubes for the mesher to use, separate meshes are needed for transparent
    //due to how opengl works, itll be easiest to treat them totally separate
    std::unordered_set<int> d_occupiedOpaque;
    std::vector<int> d_occupiedVecOpaque;
    std::unordered_set<int> d_occupiedTransparent;
    std::vector<int> d_occupiedVecTransparent;

  public: 
    int d_x, d_y, d_z;
    glm::mat4 model_matrix;
    CubeCluster(int x, int y, int z);
    CubeCluster(std::string path, int x, int y, int z);
    ~CubeCluster();

    int d_ready = 0;
    void writeChunk(std::string path);
    void create(World* world);
    void createMesh(World* world);
    void createGL();
    void add(int x, int y, int z);
    void add(int x, int y, int z, int type);
    void addChunkSpace(uint8_t x, uint8_t y, uint8_t z, uint8_t type);
    void remeshNeighbors(int x, int y, int z);
    bool remove(int x, int y, int z);
    bool edit(int x, int y, int z, int type);
    bool get(int x, int y, int z);
    void drawTransparent(const glm::mat4& projection_matrix, const glm::mat4& view_matrix);
    virtual void draw(const glm::mat4& projection_matrix, const glm::mat4& view_matrix) override final;
    virtual void update() override final;

    //this is used for culling so only opaque matters
    const std::unordered_set<int>& getOccupiedO() const{
      return d_occupiedOpaque;
    }
    const std::unordered_set<int>& getOccupiedT() const{
      return d_occupiedTransparent;
    }
};

#endif
