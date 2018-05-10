# Common source files
set(cppunit_SOURCES
    AdditionalMessage.cpp
    Asserter.cpp
    BriefTestProgressListener.cpp
    CompilerOutputter.cpp
    DefaultProtector.cpp
    DynamicLibraryManager.cpp
    DynamicLibraryManagerException.cpp
    Exception.cpp
    Message.cpp
    PlugInManager.cpp
    PlugInParameters.cpp
    ProtectorChain.cpp
    Protector.cpp
    RepeatedTest.cpp
    SourceLine.cpp
    StringTools.cpp
    SynchronizedObject.cpp
    TestAssert.cpp
    TestCase.cpp
    TestCaseDecorator.cpp
    TestComposite.cpp
    Test.cpp
    TestDecorator.cpp
    TestFactoryRegistry.cpp
    TestFailure.cpp
    TestLeaf.cpp
    TestNamer.cpp
    TestPath.cpp
    TestPlugInDefaultImpl.cpp
    TestResultCollector.cpp
    TestResult.cpp
    TestRunner.cpp
    TestSetUp.cpp
    TestSuccessListener.cpp
    TestSuiteBuilderContext.cpp
    TestSuite.cpp
    TextOutputter.cpp
    TextTestProgressListener.cpp
    TextTestResult.cpp
    TextTestRunner.cpp
    TypeInfoHelper.cpp
    XmlDocument.cpp
    XmlElement.cpp
    XmlOutputter.cpp
    XmlOutputterHook.cpp
    DefaultProtector.h
    ProtectorChain.h
    ProtectorContext.h
    # interface header at PROJECT_SOURCE_DIR
    ${PROJECT_SOURCE_DIR}/include/cppunit/AdditionalMessage.h
    ${PROJECT_SOURCE_DIR}/include/cppunit/Asserter.h
    ${PROJECT_SOURCE_DIR}/include/cppunit/BriefTestProgressListener.h
    ${PROJECT_SOURCE_DIR}/include/cppunit/CompilerOutputter.h
    ${PROJECT_SOURCE_DIR}/include/cppunit/Exception.h
    ${PROJECT_SOURCE_DIR}/include/cppunit/Message.h
    ${PROJECT_SOURCE_DIR}/include/cppunit/Outputter.h
    ${PROJECT_SOURCE_DIR}/include/cppunit/Portability.h
    ${PROJECT_SOURCE_DIR}/include/cppunit/Protector.h
    ${PROJECT_SOURCE_DIR}/include/cppunit/SourceLine.h
    ${PROJECT_SOURCE_DIR}/include/cppunit/SynchronizedObject.h
    ${PROJECT_SOURCE_DIR}/include/cppunit/Test.h
    ${PROJECT_SOURCE_DIR}/include/cppunit/TestAssert.h
    ${PROJECT_SOURCE_DIR}/include/cppunit/TestCaller.h
    ${PROJECT_SOURCE_DIR}/include/cppunit/TestCase.h
    ${PROJECT_SOURCE_DIR}/include/cppunit/TestComposite.h
    ${PROJECT_SOURCE_DIR}/include/cppunit/TestFailure.h
    ${PROJECT_SOURCE_DIR}/include/cppunit/TestFixture.h
    ${PROJECT_SOURCE_DIR}/include/cppunit/TestLeaf.h
    ${PROJECT_SOURCE_DIR}/include/cppunit/TestListener.h
    ${PROJECT_SOURCE_DIR}/include/cppunit/TestPath.h
    ${PROJECT_SOURCE_DIR}/include/cppunit/TestResult.h
    ${PROJECT_SOURCE_DIR}/include/cppunit/TestResultCollector.h
    ${PROJECT_SOURCE_DIR}/include/cppunit/TestRunner.h
    ${PROJECT_SOURCE_DIR}/include/cppunit/TestSuccessListener.h
    ${PROJECT_SOURCE_DIR}/include/cppunit/TestSuite.h
    ${PROJECT_SOURCE_DIR}/include/cppunit/TextOutputter.h
    ${PROJECT_SOURCE_DIR}/include/cppunit/TextTestProgressListener.h
    ${PROJECT_SOURCE_DIR}/include/cppunit/TextTestResult.h
    ${PROJECT_SOURCE_DIR}/include/cppunit/TextTestRunner.h
    ${PROJECT_SOURCE_DIR}/include/cppunit/XmlOutputter.h
    ${PROJECT_SOURCE_DIR}/include/cppunit/XmlOutputterHook.h
    ${PROJECT_SOURCE_DIR}/include/cppunit/config/CppUnitApi.h
    ${PROJECT_SOURCE_DIR}/include/cppunit/config/SelectDllLoader.h
    ${PROJECT_SOURCE_DIR}/include/cppunit/config/SourcePrefix.h
    # library config header at PROJECT_BINARY_DIR
    ${PROJECT_BINARY_DIR}/include/cppunit/config-auto.h
)

# Platform specific source files
# Microsoft Windows
if(WIN32)
    list(APPEND cppunit_SOURCES
        DllMain.cpp
        Win32DynamicLibraryManager.cpp
        ${PROJECT_SOURCE_DIR}/include/cppunit/config/config-msvc6.h
        ###NO! ${PROJECT_SOURCE_DIR}/include/cppunit/config/config-evc4.h
    )
# Unix based systems
elseif(UNIX)
    list(APPEND cppunit_SOURCES
        UnixDynamicLibraryManager.cpp
        ShlDynamicLibraryManager.cpp
        ${PROJECT_SOURCE_DIR}/include/cppunit/config/config-mac.h
    )
# BeOS
elseif(CMAKE_SYSTEM_NAME MATCHES "BeOS.*")
    list(APPEND cppunit_SOURCES BeOsDynamicLibraryManager.cpp)
endif()

# Create the library
add_library(cppunit ${cppunit_SOURCES})
target_link_libraries(cppunit ${CPPUNIT_COMMON_LIBS})
set_target_properties(cppunit PROPERTIES CXX_STANDARD ${CXX_STANDARD_DEFAULT})

set_target_properties(cppunit PROPERTIES
    VERSION ${CPPUNIT_SOVERSION_MAJOR}.${CPPUNIT_SOVERSION_MINOR}.${CPPUNIT_SOVERSION_PATCH}
    SOVERSION ${CPPUNIT_SOVERSION_MAJOR})

# Append a debug postfix to the library filename on Windows
if(WIN32)
    set_target_properties(cppunit PROPERTIES DEBUG_POSTFIX "d")
endif()

# Create install target
install(TARGETS cppunit
    EXPORT cppunitLibraryDepends
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin)
