
cmake_minimum_required (VERSION 2.8.11)

project (predicates)

list (APPEND CMAKE_C_FLAGS "-std=c99 -Wall")

set (LIBRARY_OUTPUT_PATH ${predicates_BINARY_DIR}/lib)
include_directories(${PROJECT_SOURCE_DIR}/include)

add_subdirectory (src)
add_subdirectory (demos)

enable_testing ()
add_subdirectory (test)
