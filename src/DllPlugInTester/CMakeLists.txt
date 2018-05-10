# Create plugin tester executable
set(cppunit-plugintester_SOURCES
    CommandLineParser.cpp
    CommandLineParser.h
    DllPlugInTester.cpp
)

add_executable(cppunit-plugintester ${cppunit-plugintester_SOURCES})
set_target_properties(cppunit-plugintester PROPERTIES CXX_STANDARD ${CXX_STANDARD_DEFAULT})
target_link_libraries(cppunit-plugintester cppunit)

install(TARGETS cppunit-plugintester
    RUNTIME DESTINATION bin COMPONENT misc)

if(CPPUNIT_BUILD_TESTING)
    # Create plugin tester test executable
    set(cppunit-plugintester-test_SOURCES
        CommandLineParser.cpp
        CommandLineParser.h
        CommandLineParserTest.cpp
        CommandLineParserTest.h
        DllPlugInTesterTest.cpp
    )

    add_executable(cppunit-plugintester-test ${cppunit-plugintester-test_SOURCES})
    set_target_properties(cppunit-plugintester-test PROPERTIES CXX_STANDARD ${CXX_STANDARD_DEFAULT})
    target_link_libraries(cppunit-plugintester-test cppunit)

    add_test(NAME cppunit-plugintester-test COMMAND cppunit-plugintester-test)
endif()
