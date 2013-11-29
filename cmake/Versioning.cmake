# Set package name and soversion information
set(CPPUNIT_PACKAGE "cppunit" CACHE INTERNAL "The library package name")
set(CPPUNIT_SOVERSION_MAJOR 1)
set(CPPUNIT_SOVERSION_MINOR 0)
set(CPPUNIT_SOVERSION_PATCH 0)

if(EXISTS "${PROJECT_SOURCE_DIR}/.version")
    file(READ "${PROJECT_SOURCE_DIR}/.version" _version)
    string(STRIP ${_version} _version)
endif()

if(NOT _version)
    find_package(Git)
    if(GIT_FOUND)
        execute_process(
            COMMAND             ${GIT_EXECUTABLE} describe
            WORKING_DIRECTORY   ${PROJECT_SOURCE_DIR}
            OUTPUT_VARIABLE     _version
            OUTPUT_STRIP_TRAILING_WHITESPACE
            RESULT_VARIABLE     CPPUNIT_VERSION_RESULT)
    endif()
endif()

if(NOT _version)
    set(_version "unknown")
endif()

set(CPPUNIT_VERSION "${_version}" CACHE INTERNAL "The cppunit library version")
message(STATUS "Building cppunit version: ${CPPUNIT_VERSION}")
