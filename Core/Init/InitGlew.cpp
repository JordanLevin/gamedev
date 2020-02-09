#include "InitGlew.hpp"

#include <GL/glew.h> 
#include <GL/freeglut.h> 

#include <iostream>

void InitGlew::init(){
  glewExperimental = true;
  if(glewInit() == GLEW_OK){
    std::cout << "GLEW: INITIALIZED" << std::endl;
  }
  if(glewIsSupported("GL_VERSION_4_3")){
    std::cout << "GLEW VERSION 4.3" << std::endl;
  }
  else{
    std::cout << "GLEW VERSION 4.3 NOT SUPPORTED" << std::endl;
  }
}
