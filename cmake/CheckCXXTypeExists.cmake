# Checks if a C++ type exists
# Contrary to CheckTypeSize, complex C++ types can be used here.
#
# The parameters have following meaning:
#  TYPE - the type like "std::tr1::shared_ptr<int>"
#  HEADER - the header to include, for example "tr1/memory"
#  VARIABLE - the name of the variable that is set to TRUE on success
#
# Example:
#  check_cxx_type_exists("std::tr1::array<int, 20>" "tr1/array" HAVE_STD_TR1_ARRAY)

macro(CHECK_CXX_TYPE_EXISTS TYPE HEADER VARIABLE)
    set(CHECK_CXX_TYPE_EXISTS_HEADER ${HEADER})
    set(CHECK_CXX_TYPE_EXISTS_TYPE ${TYPE})

    if(NOT DEFINED ${VARIABLE})
        message(STATUS "Looking for ${TYPE}")
        configure_file("${CMAKE_CURRENT_SOURCE_DIR}/cmake/CheckCXXTypeExists.cpp.in"
                       "${CMAKE_BINARY_DIR}/cmake/CheckCXXTypeExists_${VARIABLE}.cpp")

        try_compile(${VARIABLE}
                    "${CMAKE_BINARY_DIR}"
                    "${CMAKE_BINARY_DIR}/cmake/CheckCXXTypeExists_${VARIABLE}.cpp")

        if(${VARIABLE})
            message(STATUS "Looking for ${TYPE} - found")
        else ()
            message(STATUS "Looking for ${TYPE} - not found")
        endif()
        set(${var} "${${var}}" CACHE INTERNAL "CHECK_CXX_TYPE_EXISTS(${TYPE})")
    endif()
endmacro()
