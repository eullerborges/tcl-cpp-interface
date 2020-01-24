cmake_minimum_required(VERSION 3.8)

add_executable(commands_test main.cpp unix_cmd_parser.cpp)

find_package(Catch2 REQUIRED)

target_link_libraries(commands_test tcl++ Catch2::Catch2)

include(Catch)
catch_discover_tests(commands_test)
