#ifndef GUIELEMENT_H
#define GUIELEMENT_H

#include <vector>
#include <string>
#include <functional>

#include "../VertexFormat.hpp"
#include "../Models/Model.hpp"

#include <GL/glew.h>

class GuiElement : public Model{
  private:
    float x, y;
    float width, height;
    float r, g, b;
    std::string text;
    
    std::vector<Model*> children;
    //std::function<void(Settings*)> onclick;

    GLuint vao;
    GLuint program;
    std::vector<GLuint> vbos;

    std::vector<VertexFormat> vertices;

  public:
    GuiElement() = default;
    ~GuiElement() = default;
    GuiElement(float x_, float y_, float width_, float height_, float r_, float g_, float b_, Model* parent);

    void setProgram(GLuint shaderName);

    void create();
    void draw();
    void update();
    void add(Model* g);

    void setText(std::string text_);
    std::string getText();
    void setX(float x_);
    float getX();
    void setY(float x_);
    float getY();

};

#endif
