#ifndef SCREENGUI_H
#define SCREENGUI_H

#include <GL/glew.h>

#include "Model.hpp"

#include <stdarg.h>

class ScreenGui: public Model {
  private:

  public: 
    ScreenGui() = default;
    ~ScreenGui() = default;

    std::vector<VertexFormat> vertices;

    void add(float x,float y,float z, float xf,float yf,float zf);
    void add(float x,float y,float z, float xf,float yf,float zf, 
        float r, float g, float b);
    void create();
    virtual void draw() override final;
    virtual void update() override final;
};

#endif
