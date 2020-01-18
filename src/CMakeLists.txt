cmake_minimum_required(VERSION 3.8)

add_subdirectory(core)
add_subdirectory(commands)

add_library(tcl++)
target_link_libraries(tcl++ tclcore tclcommands)

# TEMP
add_executable(tcl_test main.cpp)
target_link_libraries(tcl_test PRIVATE tclcore)
