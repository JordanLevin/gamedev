cmake_minimum_required(VERSION 2.8)

project(managers)

file(GLOB_RECURSE managercpps CONFIGURE_DEPENDS "*.cpp")
file(GLOB_RECURSE managerhpps CONFIGURE_DEPENDS "*.hpp")

add_library(managerlib STATIC ${managercpps})

install(TARGETS managerlib DESTINATION lib)

install(FILES ${managerhpps} DESTINATION include)
