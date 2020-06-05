#include "Gui.hpp"
#include "GuiElement.hpp"

void Gui::create(){
  for(Model* e: elements){
    e->create();
  }
}
void Gui::draw(){
  if(!enabled)
    return;
  for(Model* e: elements){
    e->draw();
  }
}
void Gui::update(){
  if(!enabled)
    return;
  for(Model* e: elements){
    e->update();
  }
}
void Gui::add(Model* g){
  elements.push_back(g);
}
void Gui::enable(){
  enabled = true;
}
void Gui::disable(){
  enabled = false;
}
