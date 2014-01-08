# Project setup
project(cppunit C CXX)
cmake_minimum_required(VERSION 2.8.7)

# Add project specific CMake module path
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")

# Perform platform and compiler feature checks
include(PlatformChecks)

# Versioning
include(Versioning)

# Build options
option(BUILD_SHARED_LIBS           "Build cppunit as shared or static library"                ON)
option(CPPUNIT_BUILD_APIDOC        "Adds a build target for generating the API documentation" OFF)
option(CPPUNIT_BUILD_QT_TESTRUNNER "Build the Qt test runner library"                         OFF)
option(CPPUNIT_BUILD_EXAMPLES      "Build the examples shipped with cppunit"                  OFF)
option(CPPUNIT_BUILD_TESTING       "Enables testing with CTest and adds a 'test' target"      OFF)

if(CPPUNIT_BUILD_TESTING)
    enable_testing()
endif()

if(BUILD_SHARED_LIBS AND WIN32)
    add_definitions(-DCPPUNIT_BUILD_DLL)
endif()

if(CPPUNIT_BUILD_QT_TESTRUNNER)
    include(SelectQtVersion)
endif()

# Include paths
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include")
include_directories("${CMAKE_CURRENT_BINARY_DIR}/include")

# Subdirectories
add_subdirectory(include)
add_subdirectory(src)

if(CPPUNIT_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

if(CPPUNIT_BUILD_APIDOC)
    add_subdirectory(doc)
endif()

# Export targets
include(ExportTargets)
