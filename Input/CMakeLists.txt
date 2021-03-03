cmake_minimum_required(VERSION 2.8)

project(input)

file(GLOB_RECURSE playercpps CONFIGURE_DEPENDS "*.cpp")
file(GLOB_RECURSE playerhpps CONFIGURE_DEPENDS "*.hpp")

add_library(playerlib OBJECT ${playercpps})

install(TARGETS playerlib DESTINATION lib)

install(FILES ${playerhpps} DESTINATION include)
