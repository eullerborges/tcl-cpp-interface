cmake_minimum_required(VERSION 3.8)

add_library(tclcommands OBJECT UnixCommandParser.cpp)
target_link_libraries(tclcommands PUBLIC ${CONAN_LIBS})
target_include_directories(tclcommands PUBLIC ../../include)

target_compile_features(tclcommands PUBLIC cxx_std_17)
# Using -fPIC to support linking to shared libraries
set_property(TARGET tclcommands PROPERTY POSITION_INDEPENDENT_CODE ON)
