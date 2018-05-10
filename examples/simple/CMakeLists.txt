set(cppunit-simple_SOURCES
    ExampleTestCase.cpp
    ExampleTestCase.h
)

# Create the test executable
add_executable(cppunit-simple-bin Main.cpp ${cppunit-simple_SOURCES})
set_target_properties(cppunit-simple-bin PROPERTIES CXX_STANDARD ${CXX_STANDARD_DEFAULT})
target_link_libraries(cppunit-simple-bin cppunit)

# Create the test plugin
add_library(cppunit-simple-plugin MODULE SimplePlugIn.cpp ${cppunit-simple_SOURCES})
set_target_properties(cppunit-simple-plugin PROPERTIES CXX_STANDARD ${CXX_STANDARD_DEFAULT})
target_link_libraries(cppunit-simple-plugin cppunit)

# Create install target
install(TARGETS cppunit-simple-bin
    DESTINATION share/${CPPUNIT_VERSION}/examples COMPONENT examples)

install(TARGETS cppunit-simple-plugin
     DESTINATION share/${CPPUNIT_VERSION}/examples COMPONENT examples)
