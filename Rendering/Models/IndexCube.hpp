#ifndef INDEX_CUBE_H
#define INDEX_CUBE_H

#include <GL/glew.h>

#include "Model.hpp"

#include <stdarg.h>

class IndexCube: public Model {
  private:
    glm::vec3 rotation, rotation_speed;

  public: 
    IndexCube() = default;
    ~IndexCube() = default;

    void create();
    virtual void draw(const glm::mat4& projection_matrix, const glm::mat4& view_matrix) override final;
    virtual void update() override final;
};

#endif
