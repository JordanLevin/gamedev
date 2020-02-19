#include "Managers/ShaderManager.hpp"
#include "Managers/SceneManager.hpp"
#include "Core/Init/WindowInfo.hpp"
#include "Core/Init/ContextInfo.hpp"
#include "Core/Init/FrameBufferInfo.hpp"
#include "Core/Init/InitGlut.hpp"
#include "Core/Init/IListener.hpp"

#include <GL/glew.h> 
#include <GL/freeglut.h> 

#include <iostream>

int main(int argc, char **argv)
{
  WindowInfo window(std::string("OpenGL Tutorial "),
                         400, 200,//position
                         800, 600, //size
                         true);//reshape

  ContextInfo context(4, 5, true);
  FrameBufferInfo frameBufferInfo(true, true, true, true);
  InitGlut::init(window, context, frameBufferInfo);

  IListener* scene = new SceneManager();
  
  InitGlut::setListener(scene);

  InitGlut::run();

  delete scene;
  return 0;
}
