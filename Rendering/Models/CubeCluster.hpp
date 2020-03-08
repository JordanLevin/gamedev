#ifndef CUBECLUSTER_H
#define CUBECLUSTER_H

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "Model.hpp"

#include <stdarg.h>
#include <string>

class CubeCluster: public Model {
  private:
    std::vector<VertexFormat> allVertices;
    std::vector<unsigned int> allIndices;

  public: 
    CubeCluster();
    CubeCluster(std::string path);
    ~CubeCluster() = default;

    void writeChunk(std::string path);
    void create();
    void add(float x, float y, float z);
    void add(float x, float y, float z, float r, float g, float b);
    void remove(float x, float y, float z);
    virtual void draw(const glm::mat4& projection_matrix, const glm::mat4& view_matrix) override final;
    virtual void update() override final;
};

#endif
