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
    //std::vector<VertexFormat> allVertices;
    //std::vector<unsigned int> allIndices;

    //std::array<std::array<std::array<VertexFormat, 16>, 128>, 16> data;

    uint32_t getIndex(uint32_t x, uint32_t y, uint32_t z);
    //std::vector<VertexFormat> data = std::vector<VertexFormat>(DATA_SIZE);
    //std::vector<uint32_t> indices_used = std::vector<uint32_t>(DATA_SIZE);
    std::vector<VertexFormat> data;
    std::vector<Cube> cubes = std::vector<Cube>(DATA_SIZE);
    std::unordered_set<int> occupied;
    //VertexFormat data[DATA_SIZE];

  public: 
    CubeCluster();
    CubeCluster(int chunk_x, int chunk_z);
    CubeCluster(std::string path);
    ~CubeCluster() = default;

    void writeChunk(std::string path);
    void create();
    void add(int x, int y, int z);
    void add(int x, int y, int z, int type);
    void remove(int x, int y, int z);
    virtual void draw(const glm::mat4& projection_matrix, const glm::mat4& view_matrix) override final;
    virtual void update() override final;
};

#endif
