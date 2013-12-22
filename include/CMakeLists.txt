# Auto-generate the configuration header
configure_file(config-auto.h.in "${CMAKE_CURRENT_BINARY_DIR}/cppunit/config-auto.h")
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/cppunit/config-auto.h" DESTINATION include/cppunit)

install(DIRECTORY cppunit
    DESTINATION include
    FILES_MATCHING  PATTERN "*.h"
                    PATTERN "ui/qt" EXCLUDE
                    PATTERN "ui/mfc" EXCLUDE)

if(CPPUNIT_BUILD_QT_TESTRUNNER)
    install(DIRECTORY cppunit/ui/qt
        DESTINATION include/cppunit/ui
        FILES_MATCHING PATTERN "*.h")
endif()
