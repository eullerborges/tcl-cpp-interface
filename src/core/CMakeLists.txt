cmake_minimum_required(VERSION 3.8)

add_library(tclcore Interp.cpp NumericTypes.cpp Object.cpp String.cpp List.cpp Dict.cpp)
target_link_libraries(tclcore PUBLIC ${CONAN_LIBS})
target_include_directories(tclcore PUBLIC ../../include)

target_compile_features(tclcore PUBLIC cxx_std_17)
# Using -fPIC to support linking to shared libraries
set_property(TARGET tclcore PROPERTY POSITION_INDEPENDENT_CODE ON)
