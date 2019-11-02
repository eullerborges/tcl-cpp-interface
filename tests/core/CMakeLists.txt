cmake_minimum_required(VERSION 3.8)

add_executable(core_test test.cpp)

find_package(Catch2 REQUIRED)

target_link_libraries(core_test tclcore Catch2::Catch2)

