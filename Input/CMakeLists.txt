cmake_minimum_required(VERSION 2.8)

project(input)

add_library(camera STATIC Camera.cpp)

install(TARGETS camera DESTINATION lib)

install(FILES Camera.hpp DESTINATION include)
