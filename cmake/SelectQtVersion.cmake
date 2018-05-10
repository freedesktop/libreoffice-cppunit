##
# Projectname - Redmine:Administration
# Author      - Bernhard Sessler <bernhard.sessler@corscience.de>
# Description - Depending on the variable WITH_QT5 search either for Qt5 or Qt4 libs
#
# (c) 2013, Corscience GmbH & Co. KG
##

if(NOT WITH_QT)
    set(WITH_QT 5)
endif()

# Find Qt5
if(WITH_QT EQUAL 5)
    set(QT5_REQUIRED_MODULES Widgets)

    find_package(Qt5 REQUIRED COMPONENTS ${QT5_REQUIRED_MODULES})

    foreach(_submodule ${QT5_REQUIRED_MODULES})
       include_directories(${Qt5${_submodule}_INCLUDE_DIRS})
       list(APPEND QT_LIBRARIES ${Qt5${_submodule}_LIBRARIES})
    endforeach()

    set(QT_LIBRARIES_FOUND ${Qt5Widgets_FOUND})

# Find Qt4
elseif(WITH_QT EQUAL 4)
    set(QT4_REQUIRED_MODULES QtCore QtGui)

    find_package(Qt4 REQUIRED COMPONENTS ${QT4_REQUIRED_MODULES})
    include(${QT_USE_FILE})

    foreach(_submodule ${QT4_REQUIRED_MODULES})
       string(TOUPPER _submodule _var)
       list(APPEND QT_LIBRARIES ${QT_${_var}_LIBRARY})
    endforeach()

    set(QT_LIBRARIES_FOUND ${QT_QTGUI_FOUND})

# Unsupported version
else()
    message(SEND_ERROR "Unsupported Qt version specified. Set WITH_QT to either 4 or 5")
endif()
