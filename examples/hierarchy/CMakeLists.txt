# Common source files
set(cppunit-hierarchy-example-SOURCES
    BoardGame.cpp
    Chess.cpp
    main.cpp
    BoardGame.h
    Chess.h
    BoardGameTest.h
    ChessTest.h
)

# Create the test executable
add_executable(cppunit-hierarchy-example ${cppunit-hierarchy-example-SOURCES})
target_link_libraries(cppunit-hierarchy-example cppunit)

# Create install target
install(TARGETS cppunit-hierarchy-example
    DESTINATION share/${CPPUNIT_VERSION}/examples COMPONENT examples)
