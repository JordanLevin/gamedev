#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Model.hpp"

class Triangle : public Model{
  public: 
    Triangle() = default;
    ~Triangle() = default;

    void create();
    virtual void update() override final;
    virtual void draw() override final;
};

#endif
