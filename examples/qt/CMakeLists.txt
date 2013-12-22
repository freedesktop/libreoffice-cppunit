# Include the current binary dir, so files produced by moc can be found
include_directories(${CMAKE_CURRENT_BINARY_DIR})

# Common source files
set(qt_example_SOURCES
    ExampleTestCases.cpp
    Main.cpp
)

# Create the test runner executable
add_executable(qt_example ${qt_example_SOURCES})
target_link_libraries(qt_example cppunit-qttestrunner)

if(Qt5_POSITION_INDEPENDENT_CODE)
    set_target_properties(qt_example PROPERTIES POSITION_INDEPENDENT_CODE ON)
endif()

# Create install target
install(TARGETS qt_example
    RUNTIME DESTINATION bin
    COMPONENT examples)
