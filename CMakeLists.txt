# Project setup
project(cppunit C CXX)
cmake_minimum_required(VERSION 2.8.7)

# Add project specific CMake module path
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# Perform platform and compiler feature checks
include(PlatformChecks)

# Versioning
include(Versioning)

# Build options
option(BUILD_SHARED_LIBS    "Build cppunit as shared or static library"                ON)
option(CPPUNIT_BUILD_APIDOC "Adds a build target for generating the API documentation" OFF)

if(BUILD_SHARED_LIBS AND WIN32)
    add_definitions(-DCPPUNIT_BUILD_DLL)
endif()

# Include paths
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include")
include_directories("${CMAKE_CURRENT_BINARY_DIR}/include")

# Subdirectories
add_subdirectory(include)
add_subdirectory(src)

if(CPPUNIT_BUILD_APIDOC)
    add_subdirectory(doc)
endif()

# Export targets
include(ExportTargets)
