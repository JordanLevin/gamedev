#ifndef CUBE_H
#define CUBE_H

#include <GL/glew.h>

#include "Model.hpp"

#include <stdarg.h>

class Cube: public Model {
  private:
    glm::vec3 rotation, rotation_speed;

  public: 
    Cube() = default;
    ~Cube() = default;

    void create(float x, float y, float z);
    virtual void draw(const glm::mat4& projection_matrix, const glm::mat4& view_matrix) override final;
    virtual void update() override final;
};

#endif
