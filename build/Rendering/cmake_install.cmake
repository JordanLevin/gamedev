# Install script for directory: /home/jordan/Desktop/ProgrammingStuff/opengltest/test1/Rendering

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/home/jordan/Desktop/ProgrammingStuff/opengltest/test1/build/Rendering/librenderinglib.a")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE FILE FILES
    "/home/jordan/Desktop/ProgrammingStuff/opengltest/test1/Rendering/Cube.hpp"
    "/home/jordan/Desktop/ProgrammingStuff/opengltest/test1/Rendering/Gui/Gui.hpp"
    "/home/jordan/Desktop/ProgrammingStuff/opengltest/test1/Rendering/Gui/GuiElement.hpp"
    "/home/jordan/Desktop/ProgrammingStuff/opengltest/test1/Rendering/Gui/Text.hpp"
    "/home/jordan/Desktop/ProgrammingStuff/opengltest/test1/Rendering/Gui/TextElement.hpp"
    "/home/jordan/Desktop/ProgrammingStuff/opengltest/test1/Rendering/IGameObject.hpp"
    "/home/jordan/Desktop/ProgrammingStuff/opengltest/test1/Rendering/Mesher.hpp"
    "/home/jordan/Desktop/ProgrammingStuff/opengltest/test1/Rendering/Models/CubeCluster.hpp"
    "/home/jordan/Desktop/ProgrammingStuff/opengltest/test1/Rendering/Models/Model.hpp"
    "/home/jordan/Desktop/ProgrammingStuff/opengltest/test1/Rendering/Models/ScreenGui.hpp"
    "/home/jordan/Desktop/ProgrammingStuff/opengltest/test1/Rendering/Models/World.hpp"
    "/home/jordan/Desktop/ProgrammingStuff/opengltest/test1/Rendering/Models/temp.hpp"
    "/home/jordan/Desktop/ProgrammingStuff/opengltest/test1/Rendering/VertexFormat.hpp"
    )
endif()

