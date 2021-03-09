include(${CMAKE_CURRENT_LIST_DIR}/sanitizers.cmake)

# ThreadSanitizer
set(CMAKE_C_FLAGS_DEBUG
    "-ggdb -O0"
    CACHE STRING "Flags used by the C compiler during Debug builds.")

set(CMAKE_CXX_FLAGS_DEBUG
    "-ggdb -O0"
    CACHE STRING "Flags used by the C++ compiler during Debug builds.")
