#ifndef SINGLECUBE_H
#define SINGLECUBE_H

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "Model.hpp"
#include "../Cube.hpp"
#include "../VertexFormat.hpp"

#include <stdarg.h>
#include <string>
#include <array>
#include <unordered_set>

class SingleCube: public Model {
  private:
    std::vector<VertexFormat> data;
    //Actual entire chunk of cubes
    WorldCube cube;

  public: 
    SingleCube() = default;
    ~SingleCube() = default;

    void create();
    void set(int x, int y, int z);
    virtual void draw(const glm::mat4& projection_matrix, const glm::mat4& view_matrix) override final;
    virtual void update() override final;
};

#endif
