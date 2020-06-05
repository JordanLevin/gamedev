#ifndef TEXTELEMENT_H
#define TEXTELEMENT_H

#include <vector>
#include <string>
#include <functional>

#include "../VertexFormat.hpp"
#include "../Models/Model.hpp"
#include "Gui.hpp"

#include <GL/glew.h>

class TextElement : public Model {
  private:
    float x{0}, y{0};
    std::string text;
    
    
    GLuint vao;
    GLuint program;
    std::vector<GLuint> vbos;

  public:
    ~TextElement() = default;
    TextElement(float x_, float y_, std::string text_, Model* parent);

    void setProgram(GLuint shaderName);

    virtual void create();
    virtual void draw() override final;
    virtual void update() override final;
    void RenderText(float x, float y, float scale, glm::vec3 color);

    void setText(std::string text_);
    std::string getText();
    void setX(float x_);
    float getX();
    void setY(float x_);
    float getY();

};

#endif
