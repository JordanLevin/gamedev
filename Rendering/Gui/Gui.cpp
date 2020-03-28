#include "Gui.hpp"
#include "GuiElement.hpp"

void Gui::create(){
  for(auto& e: elements){
    e.create();
  }
}
void Gui::draw(){
  for(auto& e: elements){
    e.draw();
  }
}
void Gui::update(){
  for(auto& e: elements){
    e.update();
  }
}
void Gui::add(const GuiElement& g){
  elements.push_back(g);
}
