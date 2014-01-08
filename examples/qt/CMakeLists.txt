# Include the current binary dir, so files produced by moc can be found
include_directories(${CMAKE_CURRENT_BINARY_DIR})

# Common source files
set(cppunit-qt-example_SOURCES
    ExampleTestCases.cpp
    Main.cpp
)

# Create the test runner executable
add_executable(cppunit-qt-example ${cppunit-qt-example_SOURCES})
target_link_libraries(cppunit-qt-example cppunit-qttestrunner)

if(Qt5_POSITION_INDEPENDENT_CODE)
    set_target_properties(cppunit-qt-example PROPERTIES POSITION_INDEPENDENT_CODE ON)
endif()

# Create install target
install(TARGETS cppunit-qt-example
    DESTINATION share/${CPPUNIT_VERSION}/examples COMPONENT examples)
