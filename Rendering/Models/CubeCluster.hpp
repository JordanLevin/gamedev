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

class CubeCluster: public Model {
  private:
    uint32_t getIndex(uint32_t x, uint32_t y, uint32_t z);
    glm::vec3 coordsInChunk(int x, int y, int z);

    std::vector<VertexFormat> data;
    std::vector<Cube> cubes = std::vector<Cube>(DATA_SIZE);
    std::unordered_set<int> occupied;
    std::vector<int> occupiedVec;

  public: 
    CubeCluster();
    CubeCluster(std::string path);
    ~CubeCluster() = default;

    void writeChunk(std::string path);
    void create();
    void add(int x, int y, int z);
    void add(int x, int y, int z, int type);
    bool remove(int x, int y, int z);
    bool edit(int x, int y, int z, int type);
    virtual void draw(const glm::mat4& projection_matrix, const glm::mat4& view_matrix) override final;
    virtual void update() override final;
};

#endif