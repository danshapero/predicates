
cmake_minimum_required (VERSION 2.8.11)

project (predicates)

set (LIBRARY_OUTPUT_PATH ${predicates_BINARY_DIR}/lib)

add_subdirectory(src)

include_directories(${CMAKE_SOURCE_DIRECTORY}/include)
