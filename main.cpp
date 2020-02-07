#include "./core/ShaderLoader.hpp"
#include "./core/GameModels.hpp"
#include <GL/glew.h> 
#include <GL/freeglut.h> 
#include <iostream>

GameModels* gameModels;
GLuint program;

//temp hack
void idle(){
  glutPostRedisplay();
}

void renderScene(){
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glClearColor(0.0, 0.3, 0.3, 1.0);

  glBindVertexArray(gameModels->getModel("triangle1"));
  glUseProgram(program);

  glDrawArrays(GL_TRIANGLES, 0, 3);
  glutSwapBuffers();
}

void closeCallback(){
  std::cout << "FINISHED\n";
  glutLeaveMainLoop();
}

void Init(){
  glEnable(GL_DEPTH_TEST);

  gameModels = new GameModels();
  gameModels->createTriangleModel("triangle1");

  //load and compile shaders
  ShaderLoader shaderLoader;
  program = shaderLoader.CreateProgram("Shaders/vshader1.glsl",
      "Shaders/fshader1.glsl");
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

int main(int argc, char **argv)
{

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
  glutInitWindowPosition(500, 500);//optional
  glutInitWindowSize(800, 600); //optional
  glutInitContextVersion(4, 3);
  glutInitContextProfile( GLUT_CORE_PROFILE ); //use core opengl instead of old
  glutCreateWindow("OpenGL First Window");
  glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);

  glewInit();
  Init();

  //register callback
  glutDisplayFunc(renderScene);
  glutCloseFunc(closeCallback);
  glutIdleFunc(idle);
  glutMainLoop();

  delete gameModels;
  glDeleteProgram(program);

  return 0;
}
