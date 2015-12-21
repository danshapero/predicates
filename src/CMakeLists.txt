
set (SRCS
  constants.c
  predicates.c
  random.c
  printing.c)

add_library (predicates SHARED ${SRCS})

install (TARGETS predicates DESTINATION lib)
