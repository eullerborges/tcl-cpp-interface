cmake_minimum_required(VERSION 2.8.12)
project(TclWrapper)

add_definitions("-std=c++17")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_executable(tcl_test src/main.cpp src/Interp.cpp src/Object.cpp src/String.cpp src/List.cpp src/Dict.cpp)
target_link_libraries(tcl_test ${CONAN_LIBS})
