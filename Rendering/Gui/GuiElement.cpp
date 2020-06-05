#include "GuiElement.hpp"

#include "../VertexFormat.hpp"
#include "TextElement.hpp"

#include <GL/glew.h>

GuiElement::GuiElement(float x_, float y_, float width_, float height_, float r_, float g_, float b_, Model* parent){
  if(parent != nullptr){
    x = x_ + dynamic_cast<GuiElement*>(parent)->getX();
    y = y_ + dynamic_cast<GuiElement*>(parent)->getY();
  }
  else{
    x = x_;
    y = y_;
  }
  width = width_;
  height = height_;
  r = r_; 
  g = g_; 
  b = b_;
  vertices.push_back({{x,y,0.0f},{r,g,b,1.0f}});
  vertices.push_back({{x+width,y,0.0f},{r,g,b,1.0f}});
  vertices.push_back({{x,y+height,0.0f},{r,g,b,1.0f}});

  vertices.push_back({{x+width,y,0.0f},{r,g,b,1.0f}});
  vertices.push_back({{x,y+height,0.0f},{r,g,b,1.0f}});
  vertices.push_back({{x+width,y+height,0.0f},{r,g,b,1.0f}});
}

void GuiElement::setProgram(GLuint program_){
  program = program_;
}

void GuiElement::create(){
  for(Model* e: children){
    e->create();
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
  for(Model* e: children){
    e->draw();
  }
  glUseProgram(program);
  glBindVertexArray(vao);
  glDrawArrays(GL_TRIANGLES, 0, vertices.size());
}
void GuiElement::update(){
  for(Model* e: children){
    e->update();
  }
}
void GuiElement::add(Model* g){
  children.push_back(g);
}

void GuiElement::setText(std::string text_){
  text = text_;
}
std::string GuiElement::getText(){
  return text;
}
void GuiElement::setX(float x_){
  x = x_;
}
float GuiElement::getX(){
  return x;
}
void GuiElement::setY(float y_){
  y = y_;
}
float GuiElement::getY(){
  return y;
}
