#ifndef GUI_H
#define GUI_H

#include <GL/glew.h>

#include "Model.hpp"

#include <stdarg.h>

class Gui: public Model {
  private:

  public: 
    Gui();
    ~Gui() = default;

    std::vector<VertexFormat> vertices;

    void add(float x,float y,float z, float xf,float yf,float zf);
    void add(float x,float y,float z, float xf,float yf,float zf, 
        float r, float g, float b);
    void create();
    virtual void draw(const glm::mat4& projection_matrix, const glm::mat4& view_matrix) override final;
    virtual void update() override final;
};

#endif
