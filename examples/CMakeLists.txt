add_subdirectory(cppunittest)
add_subdirectory(DumperPlugIn)

if(CPPUNIT_BUILD_QT_TESTRUNNER)
    add_subdirectory(qt)
endif()
