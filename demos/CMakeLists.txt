
set (demo_list)

find_package(PNG)
if (PNG_FOUND)
  include_directories(${PNG_INCLUDE_DIRS})
  set (demo_list
    orient2d_demo.cpp
    incircle_demo.cpp
    )
endif(PNG_FOUND)


foreach (demo ${demo_list})
  string (REPLACE ".cpp" "" demo ${demo})
  add_executable (${demo}
    ${PROJECT_SOURCE_DIR}/demos/${demo}.cpp
    ${PROJECT_SOURCE_DIR}/demos/write_png.c)
  target_link_libraries (${demo} predicates m ${PNG_LIBRARIES})
endforeach (demo)
