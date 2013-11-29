# Auto-generate the configuration header
configure_file(config-auto.h.in "${CMAKE_CURRENT_BINARY_DIR}/cppunit/config-auto.h")
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/cppunit/config-auto.h" DESTINATION include/cppunit)

install(DIRECTORY cppunit DESTINATION include FILES_MATCHING PATTERN "*.h")
