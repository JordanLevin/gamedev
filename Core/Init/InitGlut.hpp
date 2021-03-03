#ifndef INITGLUT_H
#define INITGLUT_H

#include "ContextInfo.hpp"
#include "FrameBufferInfo.hpp"
#include "WindowInfo.hpp"
#include "InitGlew.hpp"
#include "IListener.hpp"

#include <glm/glm.hpp>

#include <iostream>

class InitGlut{
  private:
    static IListener* listener;
    static WindowInfo windowInfo;

    static void idleCallback();
    static void displayCallback();
    static void reshapeCallback(int width, int height);
    static void closeCallback();
    static void updateView();
    static void keyDown(const unsigned char key, int x, int y);
    static void keyUp(const unsigned char key, int x, int y);
    static void mouseMove(int x, int y);
    static void mousePress(int button, int state, int x, int y);

  public:
    static void init(const WindowInfo& window,
                     const ContextInfo& context,
                     const FrameBufferInfo& frameBuffer);
    static void run();
    static void close();

    static void enterFullscreen();
    static void exitFullscreen();

    static void printOpenGLInfo(const WindowInfo& window,
                                const ContextInfo& context);
    static void setListener(IListener* listener);
};

#endif
