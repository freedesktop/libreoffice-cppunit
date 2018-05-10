add_subdirectory(cppunit)
add_subdirectory(DllPlugInTester)

if(CPPUNIT_BUILD_QT_TESTRUNNER)
    add_subdirectory(qttestrunner)
endif()
