#ifndef VERTEXFORMAT_H
#define VERTEXFORMAT_H

#include <glm/glm.hpp>

struct VertexFormat{
  float position[3];
  float color[4];
  //float normal[3];
  //glm::vec3 position;
  //glm::vec4 color;

  //VertexFormat(const glm::vec3& pos){
    //position = pos;
  //}
  //VertexFormat(const glm::vec3& pos, const glm::vec4& col){
    //position = pos;
    //color = col;
  //}
};

#endif
