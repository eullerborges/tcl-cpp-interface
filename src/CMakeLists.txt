cmake_minimum_required(VERSION 3.8)

add_subdirectory(core)

target_compile_features(tclcore PRIVATE cxx_std_17)

add_executable(tcl_test main.cpp)
target_link_libraries(tcl_test PRIVATE tclcore)

