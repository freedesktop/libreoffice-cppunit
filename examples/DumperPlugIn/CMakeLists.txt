# Common source files
set(cppunit-dumper-plugin_SOURCES
    DumperListener.cpp
    DumperPlugIn.cpp
    DumperListener.h
)

# Create the test plugin
add_library(cppunit-dumper-plugin MODULE ${cppunit-dumper-plugin_SOURCES})
set_target_properties(cppunit-dumper-plugin PROPERTIES CXX_STANDARD ${CXX_STANDARD_DEFAULT})
target_link_libraries(cppunit-dumper-plugin cppunit)

install(TARGETS cppunit-dumper-plugin
    DESTINATION share/${CPPUNIT_VERSION}/examples COMPONENT examples)
