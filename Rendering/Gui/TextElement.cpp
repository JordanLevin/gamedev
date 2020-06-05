#include "TextElement.hpp"
#include "Text.hpp"

#include <iostream>

#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>

TextElement::TextElement(float x_, float y_, std::string text_, Model* parent){
  if(parent != nullptr){
    x = x_ + dynamic_cast<GuiElement*>(parent)->getX();
    y = y_ + dynamic_cast<GuiElement*>(parent)->getY();
  }
  else {
    x = x_;
    y = y_;
  }
  text = text_;
}

void TextElement::setProgram(GLuint program_){
  program = program_;
}

void TextElement::create(){
  GLuint vao;
  GLuint vbo;

  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);

  glBufferData(GL_ARRAY_BUFFER, sizeof(float)*6*4, NULL, GL_DYNAMIC_DRAW);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4*sizeof(float), (void*)0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
  this->vao = vao;
  this->vbos.push_back(vbo);
}

void TextElement::draw(){
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  glUseProgram(program);
  glm::mat4 projection = glm::ortho(0.0f, 1280.0f, 0.0f, 720.0f);
  glUniformMatrix4fv(glGetUniformLocation(program, "projection"), 
      1, false, &projection[0][0]);

  std::cout << x << " " << y << std::endl;
  RenderText(x,y,1, glm::vec3{1,0,0});

  glDisable(GL_BLEND);
}

void TextElement::RenderText(float x, float y, float scale, glm::vec3 color)
{
    glUniform3f(glGetUniformLocation(program, "textColor"), color.x, color.y, color.z);
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(this->vao);

    // iterate through all characters
    std::string::const_iterator c;
    for (c = text.begin(); c != text.end(); c++)
    {
        Character ch = Text::Characters[*c];

        float xpos = x + ch.Bearing.x * scale;
        float ypos = y - (ch.Size.y - ch.Bearing.y) * scale;

        float w = ch.Size.x * scale;
        float h = ch.Size.y * scale;
        // update VBO for each character
        float vertices[6][4] = {
            { xpos,     ypos + h,   0.0f, 0.0f },
            { xpos,     ypos,       0.0f, 1.0f },
            { xpos + w, ypos,       1.0f, 1.0f },

            { xpos,     ypos + h,   0.0f, 0.0f },
            { xpos + w, ypos,       1.0f, 1.0f },
            { xpos + w, ypos + h,   1.0f, 0.0f }
        };
        // render glyph texture over quad
        glBindTexture(GL_TEXTURE_2D, ch.TextureID);
        // update content of VBO memory
        glBindBuffer(GL_ARRAY_BUFFER, this->vbos[0]); //vbos prob shouldnt be a vec TODO
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        // render quad
        glDrawArrays(GL_TRIANGLES, 0, 6);
        // now advance cursors for next glyph (note that advance is number of 1/64 pixels)
        x += (ch.Advance >> 6) * scale; // bitshift by 6 to get value in pixels (2^6 = 64)
    }
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}


void TextElement::update(){
}
void TextElement::setText(std::string text_){
  text = text_;
}
std::string TextElement::getText(){
  return text;
}
void TextElement::setX(float x_){
  x = x_;
}
float TextElement::getX(){
  return x;
}
void TextElement::setY(float y_){
  y = y_;
}
float TextElement::getY(){
  return y;
}
