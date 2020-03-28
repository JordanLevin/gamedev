#ifndef GUIELEMENT_H
#define GUIELEMENT_H

#include <vector>

#include <GL/glew.h>

class GuiElement {
  private:
    int x, y;
    int width, height;
    float r, g, b;
    std::vector<GuiElement> children;

    GLuint vao;
    GLuint program;
    std::vector<GLuint> vbos;

  public:
    GuiElement() = default;
    ~GuiElement() = default;
    GuiElement(float x_, float y_, float width_, float height_, float r_, float g_, float b_);

    void setProgram(GLuint shaderName);

    void create();
    void draw();
    void update();
    void add(const GuiElement& g);

};

#endif
