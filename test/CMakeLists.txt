
set (test_list
  orient2d.cpp)


foreach (test ${test_list})
  string (REPLACE ".cpp" "" test ${test})
  add_executable (${test} ${PROJECT_SOURCE_DIR}/test/${test}.cpp)
  target_link_libraries (${test} predicates m)
  add_test (${test} ${test})
endforeach (test)
