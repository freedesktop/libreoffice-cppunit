add_subdirectory(cppunittest)
add_subdirectory(hierarchy)
add_subdirectory(simple)
add_subdirectory(DumperPlugIn)

if(CPPUNIT_BUILD_QT_TESTRUNNER)
    add_subdirectory(qt)
endif()
