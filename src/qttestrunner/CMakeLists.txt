# Include the current binary dir, so files produced by moc can be found
include_directories(${CMAKE_CURRENT_BINARY_DIR})

# Common source files
set(qttestrunner_SOURCES
    QtTestFailure.cpp
    QtTestListener.cpp
    QtTestRunner.cpp
    TestBrowser.cpp
    TestFailureTableModel.cpp
    TestRunnerThread.cpp
    TestRunnerWindow.cpp
    TestRunnerWindowPrivate.cpp
)

set(qttestrunner_FORMS
    TestRunnerWindow.ui
    TestBrowser.ui
)

if(WITH_QT EQUAL 4)
    qt4_wrap_ui(qttestrunner_UI_MOC ${qttestrunner_FORMS})
elseif(WITH_QT EQUAL 5)
    qt5_wrap_ui(qttestrunner_UI_MOC ${qttestrunner_FORMS})
endif()

# Create the test runner executable
add_library(cppunit-qttestrunner ${qttestrunner_SOURCES} ${qttestrunner_UI_MOC})
target_link_libraries(cppunit-qttestrunner cppunit ${QT_LIBRARIES})
set_target_properties(cppunit-qttestrunner PROPERTIES
    AUTOMOC ON
    VERSION ${CPPUNIT_SOVERSION_MAJOR}.${CPPUNIT_SOVERSION_MINOR}.${CPPUNIT_SOVERSION_PATCH}
    SOVERSION ${CPPUNIT_SOVERSION_MAJOR})

if(WIN32)
    set_target_properties(cppunit-qttestrunner DEBUG_POSTFIX "d")
endif()

# Create install target
install(TARGETS cppunit-qttestrunner
    LIBRARY DESTINATION lib COMPONENT testrunners
    ARCHIVE DESTINATION lib COMPONENT testrunners
    RUNTIME DESTINATION bin COMPONENT testrunners)
