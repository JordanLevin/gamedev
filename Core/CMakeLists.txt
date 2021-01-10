cmake_minimum_required(VERSION 2.8)

project(core)

add_library(init STATIC Init/InitGlew.cpp Init/InitGlut.cpp)

install(TARGETS init DESTINATION lib)

install(FILES Init/ContextInfo.hpp DESTINATION include)
install(FILES Init/DebugOutput.hpp DESTINATION include)
install(FILES Init/FrameBufferInfo.hpp DESTINATION include)
install(FILES Init/IListener.hpp DESTINATION include)
install(FILES Init/WindowInfo.hpp DESTINATION include)

install(FILES Init/InitGlew.hpp DESTINATION include)
install(FILES Init/InitGlut.hpp DESTINATION include)
