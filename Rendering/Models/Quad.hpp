#ifndef QUAD_H
#define QUAD_H

#include "Model.hpp"

class Quad : public Model {
  public:
    Quad() = default;
    ~Quad() = default;

    void create();
    virtual void draw() override final;
    virtual void update() override final;
};

#endif
