cmake_minimum_required(VERSION 2.8)

project(lib)
#file(GLOB_RECURSE renderingcpps CONFIGURE_DEPENDS "*.cpp")
file(GLOB_RECURSE libhpps CONFIGURE_DEPENDS "Logger.hpp")

#add_library(renderinglib STATIC ${renderingcpps})
#set(SOURCES Gui/Text.hpp ${FREETYPE_INCLUDE_DIRS})

#install(TARGETS renderinglib DESTINATION lib)

install(FILES ${libhpps} DESTINATION include)
