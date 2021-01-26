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
    //convert global coordinates to chunk coordinates (?)
    glm::vec3 coordsInChunk(int x, int y, int z);

    //Mesh data to render
    std::vector<VertexFormat> data;
    std::vector<VertexFormat> selectedCube;
    //Actual entire chunk of cubes
    std::vector<Cube> cubes = std::vector<Cube>(DATA_SIZE);
    //Occupied cubes for the mesher to use
    std::unordered_set<int> occupied;
    std::vector<int> occupiedVec;
    int n = 0; //lmao just for fun
    int d_x, d_y, d_z;

    glm::mat4 model_matrix;

  public: 
    CubeCluster(int x, int y, int z);
    CubeCluster(std::string path, int x, int y, int z);
    ~CubeCluster();

    int d_ready = 0;
    void writeChunk(std::string path);
    void create();
    void createMesh();
    void createGL();
    void add(int x, int y, int z);
    void add(int x, int y, int z, int type);
    bool remove(int x, int y, int z);
    bool edit(int x, int y, int z, int type);
    int get(int x, int y, int z);
    virtual void draw(const glm::mat4& projection_matrix, const glm::mat4& view_matrix) override final;
    virtual void update() override final;
};

#endif
