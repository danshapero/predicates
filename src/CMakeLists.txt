
set (SRCS
  predicates.c)

add_library (predicates SHARED ${SRCS})
install (TARGETS predicates DESTINATION lib)
