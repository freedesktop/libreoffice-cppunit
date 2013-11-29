# - Check if given C++ source in the specified file compiles and links into an executable
# CHECK_CXX_SOURCEFILE_COMPILES(<file> <var> [FAIL_REGEX <fail-regex>])
#  <file>       - source file to try to compile, must define 'main'
#  <var>        - variable to store whether the source code compiled
#  <fail-regex> - fail if test output matches this regex
# The following variables may be set before calling this macro to
# modify the way the check is run:
#
#  CMAKE_REQUIRED_FLAGS = string of compile command line flags
#  CMAKE_REQUIRED_DEFINITIONS = list of macros to define (-DFOO=bar)
#  CMAKE_REQUIRED_INCLUDES = list of include directories
#  CMAKE_REQUIRED_LIBRARIES = list of libraries to link

macro(CHECK_CXX_SOURCEFILE_COMPILES SOURCEFILE VAR)
  if("${VAR}" MATCHES "^${VAR}$")
    set(_FAIL_REGEX)
    set(_key)
    foreach(arg ${ARGN})
      if("${arg}" MATCHES "^(FAIL_REGEX)$")
        set(_key "${arg}")
      elseif(_key)
        list(APPEND _${_key} "${arg}")
      else()
        message(FATAL_ERROR "Unknown argument:\n  ${arg}\n")
      endif()
    endforeach()

    if(NOT EXISTS ${SOURCEFILE})
        message(FATAL_ERROR "Could not find file ${SOURCEFILE}")
    endif()

    set(MACRO_CHECK_FUNCTION_DEFINITIONS
      "-D${VAR} ${CMAKE_REQUIRED_FLAGS}")
    if(CMAKE_REQUIRED_LIBRARIES)
      set(CHECK_CXX_SOURCE_COMPILES_ADD_LIBRARIES
        LINK_LIBRARIES ${CMAKE_REQUIRED_LIBRARIES})
    else()
      set(CHECK_CXX_SOURCE_COMPILES_ADD_LIBRARIES)
    endif()
    if(CMAKE_REQUIRED_INCLUDES)
      set(CHECK_CXX_SOURCE_COMPILES_ADD_INCLUDES
        "-DINCLUDE_DIRECTORIES:STRING=${CMAKE_REQUIRED_INCLUDES}")
    else()
      set(CHECK_CXX_SOURCE_COMPILES_ADD_INCLUDES)
    endif()

    message(STATUS "Performing Test ${VAR}")
    try_compile(${VAR}
      ${CMAKE_CURRENT_BINARY_DIR}
      ${SOURCEFILE}
      COMPILE_DEFINITIONS ${CMAKE_REQUIRED_DEFINITIONS}
      ${CHECK_CXX_SOURCE_COMPILES_ADD_LIBRARIES}
      CMAKE_FLAGS -DCOMPILE_DEFINITIONS:STRING=${MACRO_CHECK_FUNCTION_DEFINITIONS}
      "${CHECK_CXX_SOURCE_COMPILES_ADD_INCLUDES}"
      OUTPUT_VARIABLE OUTPUT)

    foreach(_regex ${_FAIL_REGEX})
      if("${OUTPUT}" MATCHES "${_regex}")
        set(${VAR} 0)
      endif()
    endforeach()

    if(${VAR})
      set(${VAR} 1 CACHE INTERNAL "Test ${VAR}")
      message(STATUS "Performing Test ${VAR} - Success")
      file(APPEND ${CMAKE_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/CMakeOutput.log
        "Performing C++ SOURCE FILE Test ${VAR} succeded with the following output:\n"
        "${OUTPUT}\n"
        "Source file was:\n${SOURCEFILE}\n")
    else()
      message(STATUS "Performing Test ${VAR} - Failed")
      set(${VAR} "" CACHE INTERNAL "Test ${VAR}")
      file(APPEND ${CMAKE_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/CMakeError.log
        "Performing C++ SOURCE FILE Test ${VAR} failed with the following output:\n"
        "${OUTPUT}\n"
        "Source file was:\n${SOURCEFILE}\n")
    endif()
  endif()
endmacro()

