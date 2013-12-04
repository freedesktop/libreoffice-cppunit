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
    XmlOutputterHook.cpp)

# Platform specific source files
# Microsoft Windows
if(WIN32)
    set(cppunit_SOURCES ${cppunit_SOURCES}
        DllMain.cpp
        Win32DynamicLibraryManager.cpp)
# Unix based systems
elseif(UNIX)
    set(cppunit_SOURCES ${cppunit_SOURCES}
        UnixDynamicLibraryManager.cpp)
    if(CPPUNIT_HAVE_UNIX_SHL_LOADER)
        set(cppunit_SOURCES ${cppunit_SOURCES}
            ShlDynamicLibraryManager.cpp)
    endif()
# BeOS
elseif(CMAKE_SYSTEM_NAME MATCHES "BeOS.*")
    set(cppunit_SOURCES ${cppunit_SOURCES}
        BeOsDynamicLibraryManager.cpp)
endif()

# Create the library
add_library(cppunit ${cppunit_SOURCES})
target_link_libraries(cppunit ${CPPUNIT_COMMON_LIBS})

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
