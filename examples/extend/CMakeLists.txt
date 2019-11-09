add_library(math_example SHARED main.cpp)

target_link_libraries(math_example PUBLIC ${CONAN_LIBS} tclcore)
target_include_directories(math_example PUBLIC ../../include)
