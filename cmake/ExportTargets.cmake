# Export targets
if(WIN32 AND NOT CYGWIN)
    set(INSTALL_CMAKE_DIR CMake)
else()
    set(INSTALL_CMAKE_DIR lib/cmake/cppunit)
endif()

file(RELATIVE_PATH CONF_REL_INCLUDE_DIR
    "${CMAKE_INSTALL_PREFIX}/${INSTALL_CMAKE_DIR}"
    "${CMAKE_INSTALL_PREFIX}/include")
configure_file(cppunitConfig.cmake.in
    "${PROJECT_BINARY_DIR}/cppunitConfig.cmake" @ONLY)
configure_file(cppunitConfigVersion.cmake.in
    "${PROJECT_BINARY_DIR}/cppunitConfigVersion.cmake" @ONLY)

install(FILES
    "${PROJECT_BINARY_DIR}/cppunitConfig.cmake"
    "${PROJECT_BINARY_DIR}/cppunitConfigVersion.cmake"
    DESTINATION "${INSTALL_CMAKE_DIR}" COMPONENT dev)

install(EXPORT cppunitLibraryDepends DESTINATION "${INSTALL_CMAKE_DIR}")
