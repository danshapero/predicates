#------------------------------------------------------------------------------
# Macro set set the library properties
macro(LibraryProperties targetName DEBUG_EXTENSION)
  if( NOT BUILD_SHARED_LIBS AND MSVC)
    SET_TARGET_PROPERTIES( ${targetName}
      PROPERTIES
      DEBUG_OUTPUT_NAME lib${targetName}
      RELEASE_OUTPUT_NAME lib${targetName}  )
  endif()

  set_target_properties( ${targetName} PROPERTIES FOLDER ${targetName}Proj)


  #-- Set the Debug and Release names for the libraries
  SET_TARGET_PROPERTIES( ${targetName}
      PROPERTIES
      DEBUG_POSTFIX ${DEBUG_EXTENSION} )

  if(BUILD_SHARED_LIBS)
    if(APPLE)
      # use, i.e. don't skip the full RPATH for the build tree
      SET(CMAKE_SKIP_BUILD_RPATH  FALSE)

      # when building, don't use the install RPATH already
      # (but later on when installing)
      SET(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE)

      SET(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")

      # add the automatically determined parts of the RPATH
      # which point to directories outside the build tree to the install RPATH
      SET(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

    endif(APPLE)

    if(CMAKE_SYSTEM_NAME MATCHES "Linux")
      set(CMAKE_INSTALL_RPATH "\$ORIGIN/../lib")
      SET_TARGET_PROPERTIES( ${targetName}
                PROPERTIES
                INSTALL_RPATH \$ORIGIN/../lib)
    endif()

  endif( BUILD_SHARED_LIBS)

endmacro(LibraryProperties DEBUG_EXTENSION)



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
  ${predicates_SOURCE_DIR}/include/predicatesDLLExport.h
)

add_library (predicates ${LIB_TYPE} ${predicates_SRCS} ${predicates_HDRS})
LibraryProperties(predicates "_d")

set(install_dir "bin")
set(lib_install_dir "lib")

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


