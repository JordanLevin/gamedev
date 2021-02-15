cmake_minimum_required(VERSION 2.8)

project(game)

find_package(Freetype REQUIRED)
include_directories(${FREETYPE_INCLUDE_DIRS})
message(STATUS "FREETYPE_INCLUDE_DIRS: ${FREETYPE_INCLUDE_DIRS}")
message(STATUS "gcc -v ${CMAKE_CXX_COMPILER_VERSION}")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_compile_options(-Wall -Wextra -pedantic --std=c++17 -lstdc++fs -Wno-unused-parameter -g)

add_subdirectory(Managers)
add_subdirectory(Core)
add_subdirectory(Rendering)
add_subdirectory(Input)

add_executable(game main.cpp)

target_link_libraries(game init playerlib managerlib renderinglib)

find_library(GLUT glut)
find_library(OPENGL GL)
find_library(GLEW GLEW)
find_library(MATH m)
find_library(PTHREAD pthread)


target_link_libraries(game ${PTHREAD} ${GLUT} ${OPENGL} ${GLEW} ${MATH} ${FREETYPE_LIBRARIES} stdc++fs)

add_definitions(${GCC_FLAGS})

add_custom_target(copy-glsl ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/Shaders ${CMAKE_BINARY_DIR}/Shaders
    DEPENDS ${MY_TARGET})
