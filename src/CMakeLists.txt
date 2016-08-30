
set (predicates_SRCS
  ${predicates_SOURCE_DIR}/src/constants.c
  ${predicates_SOURCE_DIR}/src/predicates.c
  ${predicates_SOURCE_DIR}/src/random.c
  ${predicates_SOURCE_DIR}/src/printing.c
  )

set(predicates_HDRS
  ${predicates_SOURCE_DIR}/src/constants.h
  ${predicates_SOURCE_DIR}/include/predicates.h
  ${predicates_SOURCE_DIR}/include/predicates.hpp
)

add_library (predicates ${LIB_TYPE} ${predicates_SRCS} ${predicates_HDRS})

set(install_dir "bin")
set(lib_install_dir "lib")
if(WIN32)
    set(install_dir ".")
    set(lib_install_dir ".")
endif()

install (TARGETS predicates 
          COMPONENT Applications
          EXPORT PredicatesLibTargets
          RUNTIME DESTINATION ${install_dir}
          LIBRARY DESTINATION ${lib_install_dir}
          ARCHIVE DESTINATION ${lib_install_dir}
          BUNDLE DESTINATION ".")


# --------------------------------------------------------------------
include(CMakePackageConfigHelpers)

write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/Predicates/PredicatesLibTargetsConfigVersion.cmake"
  VERSION ${Predicates_VERSION}
  COMPATIBILITY AnyNewerVersion
)
if(BUILD_SHARED_LIBS)
  export(EXPORT PredicatesLibTargets
    FILE "${CMAKE_CURRENT_BINARY_DIR}/Predicates/PredicatesLibTargets.cmake"
    NAMESPACE Predicates::
  )
endif()

configure_file(cmake/PredicatesConfig.cmake
  "${CMAKE_CURRENT_BINARY_DIR}/Predicates/PredicatesConfig.cmake"
  COPYONLY
)

set(ConfigPackageLocation share/Predicates)

if(BUILD_SHARED_LIBS)
  install(EXPORT PredicatesLibTargets
    FILE
      PredicatesLibTargets.cmake
    NAMESPACE
      Predicates::
    DESTINATION
      ${ConfigPackageLocation}
  )

endif()

install(
  FILES
    cmake/PredicatesConfig.cmake
    "${CMAKE_CURRENT_BINARY_DIR}/Predicates/PredicatesLibTargetsConfigVersion.cmake"
  DESTINATION
    ${ConfigPackageLocation}
  COMPONENT
    Devel
)


