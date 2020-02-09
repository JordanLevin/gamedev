#include "Managers/ShaderManager.hpp"
#include "Managers/SceneManager.hpp"
#include "Core/GameModels.hpp"
#include "Core/Init/WindowInfo.hpp"
#include "Core/Init/ContextInfo.hpp"
#include "Core/Init/FrameBufferInfo.hpp"
#include "Core/Init/InitGlut.hpp"
#include "Core/Init/IListener.hpp"

#include <GL/glew.h> 
#include <GL/freeglut.h> 

#include <iostream>

//GameModels* gameModels;
//ShaderManager shaderManager;
//GLuint program;

////temp hack
//void idle(){
  //glutPostRedisplay();
//}

//void renderScene(){
  //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  //glClearColor(0.0, 0.3, 0.3, 1.0);

  //glBindVertexArray(gameModels->getModel("triangle1"));
  //glUseProgram(program);

  //glDrawArrays(GL_TRIANGLES, 0, 3);
  //glutSwapBuffers();
//}

//void closeCallback(){
  //std::cout << "FINISHED\n";
  //glutLeaveMainLoop();
//}

//void Init(){
  //glEnable(GL_DEPTH_TEST);

  //gameModels = new GameModels();
  //gameModels->createTriangleModel("triangle1");

  ////load and compile shaders
  //shaderManager.createProgram("Shaders/vshader1.glsl",
                              //"Shaders/fshader1.glsl",
                              //"colorShader");
  //program = shaderManager.getShader("colorShader");
  //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
//}

//int main(int argc, char **argv)
//{

  //glutInit(&argc, argv);
  //glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
  //glutInitWindowPosition(500, 500);//optional
  //glutInitWindowSize(800, 600); //optional
  //glutInitContextVersion(4, 3);
  //glutInitContextProfile( GLUT_CORE_PROFILE ); //use core opengl instead of old
  //glutCreateWindow("OpenGL First Window");
  //glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);

  //glewInit();
  //Init();

  ////register callback
  //glutDisplayFunc(renderScene);
  //glutCloseFunc(closeCallback);
  //glutIdleFunc(idle);
  //glutMainLoop();

  //delete gameModels;
  //glDeleteProgram(program);

  //return 0;
//}

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
