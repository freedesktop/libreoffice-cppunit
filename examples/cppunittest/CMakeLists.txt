# Common source files
set(cppunit-test-objlib_SOURCES
    assertion_traitsTest.cpp
    BaseTestCase.cpp
    CppUnitTestSuite.cpp
    ExceptionTestCaseDecoratorTest.cpp
    ExceptionTest.cpp
    HelperMacrosTest.cpp
    MessageTest.cpp
    MockTestCase.cpp
    MockTestListener.cpp
    OrthodoxTest.cpp
    RepeatedTestTest.cpp
    StringToolsTest.cpp
    SubclassedTestCase.cpp
    TestAssertTest.cpp
    TestCallerTest.cpp
    TestCaseTest.cpp
    TestDecoratorTest.cpp
    TestFailureTest.cpp
    TestPathTest.cpp
    TestResultCollectorTest.cpp
    TestResultTest.cpp
    TestSetUpTest.cpp
    TestSuiteTest.cpp
    TestTest.cpp
    TrackedTestCase.cpp
    XmlElementTest.cpp
    XmlOutputterTest.cpp
    XmlUniformiser.cpp
    XmlUniformiserTest.cpp
)

# Create a common object library
add_library(cppunit-test-objlib OBJECT ${cppunit-test-objlib_SOURCES})

# Create the test executable
add_executable(cppunit-test-bin CppUnitTestMain.cpp $<TARGET_OBJECTS:cppunit-test-objlib>)
target_link_libraries(cppunit-test-bin cppunit)
if(CPPUNIT_BUILD_TESTING)
    add_test(NAME cppunit-test-bin COMMAND cppunit-test-bin)
endif()

# Create the test plugin
add_library(cppunit-test-plugin MODULE CppUnitTestPlugIn.cpp $<TARGET_OBJECTS:cppunit-test-objlib>)
target_link_libraries(cppunit-test-plugin cppunit)

# Create install target
install(TARGETS cppunit-test-bin
    DESTINATION share/${CPPUNIT_VERSION}/examples COMPONENT examples)

install(TARGETS cppunit-test-plugin
     DESTINATION share/${CPPUNIT_VERSION}/examples COMPONENT examples)
