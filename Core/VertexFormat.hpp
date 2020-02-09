#ifndef VERTEXFORMAT_H
#define VERTEXFORMAT_H

#include <glm/glm.hpp>

struct VertexFormat{
  glm::vec3 position;
  glm::vec4 color;

  VertexFormat(const glm::vec3& pos){
    position = pos;
  }
  VertexFormat(const glm::vec3& pos, const glm::vec4& col){
    position = pos;
    color = col;
  }
};

#endif
