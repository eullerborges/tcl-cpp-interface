cmake_minimum_required(VERSION 3.8)

add_executable(core_test main.cpp list.cpp string.cpp string_rep.cpp object.cpp)

find_package(Catch2 REQUIRED)

target_link_libraries(core_test tclcore Catch2::Catch2)

include(Catch)
catch_discover_tests(core_test)
