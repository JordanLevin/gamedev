#ifndef IGAMEOBJECT_H
#define IGAMEOBJECT_H

#include "VertexFormat.hpp"

#include <GL/glew.h>
#include <GL/freeglut.h>

#include <vector>
#include <iostream>

class IGameObject{
  public:
    virtual ~IGameObject() = 0;

    virtual void draw() = 0;
    virtual void draw(const glm::mat4& projection_matrix, const glm::mat4& view_matrix) = 0;
    virtual void update() = 0;
    virtual void setProgram(GLuint shaderName) = 0;
    virtual void destroy() = 0;

    virtual GLuint  getVao() const = 0;
    virtual const std::vector<GLuint>&  getVbos() const = 0;
};

inline IGameObject::~IGameObject(){
}

#endif
