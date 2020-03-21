

function(AddPredicatesUnitTest)
    set(options)
    set(oneValueArgs TESTNAME FOLDER)
    set(multiValueArgs SOURCES LINK_LIBRARIES)
    cmake_parse_arguments(Z "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN} )

    add_executable( ${Z_TESTNAME} "${Z_SOURCES}")
    target_link_libraries( ${Z_TESTNAME} ${Z_LINK_LIBRARIES})
    if("${Z_FOLDER}" STREQUAL "")
        set(Z_FOLDER "Test")
    endif()
    set_target_properties( ${Z_TESTNAME} PROPERTIES FOLDER ${Z_FOLDER})
    add_test(${Z_TESTNAME} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${Z_TESTNAME})

endfunction()


set(Predicates_LINK_LIBRARIES "predicates")
if(NOT WIN32)
  set(Predicates_LINK_LIBRARIES predicates m)
endif()


AddPredicatesUnitTest(TESTNAME orient2d
                      SOURCES ${predicates_SOURCE_DIR}/test/orient2d.cpp
                      FOLDER "Predicates/Test"
                      LINK_LIBRARIES ${Predicates_LINK_LIBRARIES} )

AddPredicatesUnitTest(TESTNAME incircle
                      SOURCES ${predicates_SOURCE_DIR}/test/incircle.cpp
                      FOLDER "Predicates/Test"
                      LINK_LIBRARIES ${Predicates_LINK_LIBRARIES} )

AddPredicatesUnitTest(TESTNAME orient3d
                      SOURCES ${predicates_SOURCE_DIR}/test/orient3d.cpp
                      FOLDER "Predicates/Test"
                      LINK_LIBRARIES ${Predicates_LINK_LIBRARIES} )
