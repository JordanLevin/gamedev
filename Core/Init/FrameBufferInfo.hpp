#ifndef FRAMEBUFFERINFO_H
#define FRAMEBUFFERINFO_H

#include <GL/glew.h> 
#include <GL/freeglut.h> 

struct FrameBufferInfo{
  unsigned int flags;
  bool msaa;

  FrameBufferInfo(){
    flags = GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH;
    msaa = false;
  }

  FrameBufferInfo(bool color, bool depth, bool stencil, bool msaa_){
    flags = GLUT_DOUBLE; //this flag is essential?
    if(color)
      flags |= GLUT_RGBA | GLUT_ALPHA;
    if(depth)
      flags |= GLUT_DEPTH;
    if(stencil)
      flags |= GLUT_STENCIL;
    if(msaa_)
      flags |= GLUT_MULTISAMPLE;
    msaa = msaa_;
  }

  FrameBufferInfo(const FrameBufferInfo& frameBufferInfo) = default;
  FrameBufferInfo& operator=(const FrameBufferInfo& frameBufferInfo) = default;
};

#endif

