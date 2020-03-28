#include "GuiElement.hpp"

#include "../VertexFormat.hpp"

#include <GL/glew.h>

GuiElement::GuiElement(float x_, float y_, float width_, float height_, float r_, float g_, float b_){
  x = x_; y = y_; 
  width = width; height = height_;
  r = r_; g = g_; b = b_;
}

void GuiElement::setProgram(GLuint program_){
  program = program_;
}

void GuiElement::create(){
  for(auto& e: children){
    e.create();
  }

  //create this element
  GLuint vao;
  GLuint vbo;

  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);

  glBufferData(GL_ARRAY_BUFFER, sizeof(VertexFormat) * vertices.size(), &vertices[0], GL_DYNAMIC_DRAW);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)0);
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), 
      (void*)(offsetof(VertexFormat, VertexFormat::color)));
  glBindVertexArray(0);
  this->vao = vao;
  this->vbos.push_back(vbo);

}
void GuiElement::draw(){
  for(auto& e: children){
    e.draw();
  }
  glUseProgram(program);
  glBindVertexArray(vao);
  glDrawArrays(GL_TRIANGLES, 0, vertices.size());
}
void GuiElement::update(){
  for(auto& e: children){
    e.update();
  }
}
void GuiElement::add(const GuiElement& g){
  children.push_back(g);
}
