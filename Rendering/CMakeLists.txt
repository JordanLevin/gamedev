cmake_minimum_required(VERSION 2.8)

project(rendering)
file(GLOB_RECURSE renderingcpps CONFIGURE_DEPENDS "*.cpp")
file(GLOB_RECURSE renderinghpps CONFIGURE_DEPENDS "*.hpp")

add_library(renderinglib STATIC ${renderingcpps})
#set(SOURCES Gui/Text.hpp ${FREETYPE_INCLUDE_DIRS})

install(TARGETS renderinglib DESTINATION lib)

install(FILES ${renderinghpps} DESTINATION include)

