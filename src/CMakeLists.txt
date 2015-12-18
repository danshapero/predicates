
set (SRCS
  predicates.c)

add_executable (make_constants_h make_constants_h.c)
add_custom_command (OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/constants.h
  COMMAND ${CMAKE_CURRENT_BINARY_DIR}/make_constants_h ${CMAKE_CURRENT_BINARY_DIR}/constants.h
  DEPENDS make_constants_h)
add_custom_target (constants_h ALL DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/constants.h)

include_directories(${CMAKE_CURRENT_BINARY_DIR})
add_library (predicates SHARED ${SRCS})
add_dependencies (predicates constants_h)

install (TARGETS predicates DESTINATION lib)
