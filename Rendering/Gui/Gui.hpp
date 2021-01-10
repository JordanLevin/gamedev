#ifndef GUI_H
#define GUI_H

#include "GuiElement.hpp"
#include "../Models/Model.hpp"

#include <vector>

class Gui : public Model {
  private:
    std::vector<Model*> elements;
  public:
    bool enabled = false;

    Gui() = default;
    ~Gui() = default;

    virtual void create();
    virtual void draw() override final;
    virtual void update() override final;
    void add(Model* g);
    void enable();
    void disable();

};

#endif
