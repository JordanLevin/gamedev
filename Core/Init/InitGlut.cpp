#include "InitGlut.hpp"
#include "InitGlew.hpp"
#include "WindowInfo.hpp"
#include "ContextInfo.hpp"
#include "FrameBufferInfo.hpp"

//Define static members (its a weird c++ thing)
IListener* InitGlut::listener = nullptr;
WindowInfo InitGlut::windowInfo;

void InitGlut::init(const WindowInfo& window,
                    const ContextInfo& context,
                    const FrameBufferInfo& frameBuffer){
  windowInfo = window;

  //Make fake argv/argc for glut init
  int argc = 1;
  char* argv[] = {"empty", NULL};
  glutInit(&argc, argv);

  if(context.core){
    glutInitContextVersion(context.major_version, context.minor_version);
    glutInitContextProfile(GLUT_CORE_PROFILE);
  }
  else{
    glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);
  }
  
  glutInitDisplayMode(frameBuffer.flags);
  glutInitWindowPosition(window.posx, window.posy);
  glutInitWindowSize(window.width, window.height);
  glutCreateWindow(window.name.c_str());

  std::cout << "GLUT: initalized" << std::endl;

  glutIdleFunc(idleCallback);
  glutCloseFunc(closeCallback);
  glutDisplayFunc(displayCallback);
  glutReshapeFunc(reshapeCallback);

  InitGlew::init();

  glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);

  printOpenGLInfo(window, context);
}

void InitGlut::run(){
  std::cout << "GLUT: Started Running" << std::endl;
  glutMainLoop();
}

void InitGlut::close(){
  std::cout << "GLUT: Finished" << std::endl;
  glutLeaveMainLoop();
}

void InitGlut::idleCallback(){
  glutPostRedisplay();
}

void InitGlut::displayCallback()
{
  if(listener != nullptr){
    listener->notifyBeginFrame();
    listener->notifyDisplayFrame();

    glutSwapBuffers();

    listener->notifyEndFrame();
  }
  //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  //glClearColor(0.0, 0.0, 0.0, 1);
  //glutSwapBuffers();
}

void InitGlut::reshapeCallback(int width, int height){
  if(windowInfo.reshapable && listener != nullptr){
    listener->notifyReshape(width, height, windowInfo.width, windowInfo.height);
    windowInfo.width = width;
    windowInfo.height = height;
  }
}

void InitGlut::closeCallback(){
  close();
}

void InitGlut::enterFullscreen(){
  glutFullScreen();
}

void InitGlut::exitFullscreen(){
  glutLeaveFullScreen();
}

void InitGlut::printOpenGLInfo(const WindowInfo& window,
                                      const ContextInfo& context){

 const unsigned char* renderer = glGetString(GL_RENDERER);
 const unsigned char* vendor = glGetString(GL_VENDOR);
 const unsigned char* version = glGetString(GL_VERSION);

 std::cout << "******************************************************"<< std::endl;
 std::cout << "GLUT:Initialize" << std::endl;
 std::cout << "GLUT:\tVendor : " << vendor << std::endl;
 std::cout << "GLUT:\tRenderer : " << renderer << std::endl;
 std::cout << "GLUT:\tOpenGl version: " << version << std::endl;
}

void InitGlut::setListener(IListener* listener_){
  listener = listener_;
}
