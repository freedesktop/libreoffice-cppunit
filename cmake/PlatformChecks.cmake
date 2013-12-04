##########################
# C platform checks
##########################

# C header Checks
include(CheckIncludeFile)
check_include_file(sys/types.h CPPUNIT_HAVE_SYS_TYPES_H)
check_include_file(sys/stat.h CPPUNIT_HAVE_SYS_STAT_H)
check_include_file(stdlib.h CPPUNIT_HAVE_STDLIB_H)
check_include_file(string.h CPPUNIT_HAVE_STRING_H)
check_include_file(memory.h CPPUNIT_HAVE_MEMORY_H)
check_include_file(strings.h CPPUNIT_HAVE_STRINGS_H)
check_include_file(inttypes.h CPPUNIT_HAVE_INTTYPES_H)
check_include_file(stdint.h CPPUNIT_HAVE_STDINT_H)
check_include_file(unistd.h CPPUNIT_HAVE_UNISTD_H)
check_include_file(dlfcn.h CPPUNIT_HAVE_DLFCN_H)
check_include_file(math.h CPPUNIT_HAVE_MATH_H)
check_include_file(ieeefp.h CPPUNIT_HAVE_IEEEFP_H)

# C library checks
include(CheckLibraryExists)
check_library_exists(dl dlopen dlfcn.h CPPUNIT_HAVE_LIBDL)
check_library_exists(dl dlerror dlfcn.h CPPUNIT_HAVE_DLERROR)
if(CPPUNIT_HAVE_LIBDL)
    list(APPEND CPPUNIT_COMMON_LIBS "dl")
endif()

if(NOT CPPUNIT_HAVE_LIBDL)
    check_library_exists(svld dlopen dlfcn.h CPPUNIT_HAVE_LIBDL)
    check_library_exists(svld dlerror dlfcn.h CPPUNIT_HAVE_DLERROR)
    if(CPPUNIT_HAVE_LIBDL)
        list(APPEND CPPUNIT_COMMON_LIBS "svld")
    endif()
endif()

check_library_exists(dld dld_link dld.h CPPUNIT_HAVE_DLD)
check_library_exists(dld shl_load dld.h CPPUNIT_HAVE_UNIX_SHL_LOADER)
if(CPPUNIT_HAVE_UNIX_SHL_LOADER)
    list(APPEND CPPUNIT_COMMON_LIBS "dld")
endif()

# C function checks
include(CheckFunctionExists)
check_function_exists(finite CPPUNIT_HAVE_FINITE)
check_function_exists(_finite CPPUNIT_HAVE__FINITE)

# C symbol checks
include(CheckSymbolExists)
if(CPPUNIT_HAVE_MATH_H)
    set(_header math.h)
elseif(CPPUNIT_HAVE_IEEEFP_H)
    set(_header ieeefp.h)
else()
    set(_unsupported_compiler 1)
endif()

if(CPPUNIT_HAVE_MATH_H OR CPPUNIT_HAVE_IEEEFP_H)
    check_symbol_exists(isfinite ${_header} CPPUNIT_HAVE_ISFINITE)
endif()

# MinGW depends on the MS Visual C Runtime.
# Unfortunately on Windows XP the default runtime does not support the Microsoft secure API.
# That's why it's explicitly disabled for all Windows versions < 6.0 (Vista) here.
if(MINGW AND ${CMAKE_SYSTEM_VERSION} VERSION_LESS "6.0")
    set(CPPUNIT_HAVE_SPRINTF_S FALSE CACHE INTERNAL "MinGW on Windows < 6.0 does not support this")
        message(STATUS "Building for ${CMAKE_SYSTEM} with MinGW - disabling Secure API")
else()
        check_symbol_exists(sprintf_s "stdio.h" CPPUNIT_HAVE_SPRINTF_S)
endif()

##########################
# C++ platform checks
##########################

# C++ header checks
include(CheckIncludeFileCXX)
check_include_file_cxx(strstream CPPUNIT_HAVE_STRSTREAM)
check_include_file_cxx(cmath CPPUNIT_HAVE_CMATH)
check_include_file_cxx(memory.h CPPUNIT_HAVE_MEMORY_H)
check_include_file_cxx(cxxabi.h CPPUNIT_HAVE_CXXABI_H)
check_include_file_cxx(typeinfo CPPUNIT_HAVE_TYPEINFO)

# C++ symbol checks
include(CheckCXXSymbolExists)
if(CPPUNIT_HAVE_CXXABI_H)
    check_cxx_symbol_exists(abi::__cxa_demangle cxxabi.h CPPUNIT_HAVE_GCC_ABI_DEMANGLE)
endif()

# C++ type checks
include(CheckCXXTypeExists)
check_cxx_type_exists(std::stringstream sstream CPPUNIT_HAVE_SSTREAM)
if(CPPUNIT_HAVE_STRSTREAM)
    set(_header strstream)
else()
    set(_header strstream.h)
endif()
check_cxx_type_exists(std::ostrstream ${_header} CPPUNIT_HAVE_CLASS_STRSTREAM)

# C++ feature checks
include(CheckCXXSourcefileCompiles)
check_cxx_sourcefile_compiles(${PROJECT_SOURCE_DIR}/cmake/have_namespaces.cpp
                              CPPUNIT_HAVE_NAMESPACES)
check_cxx_sourcefile_compiles(${PROJECT_SOURCE_DIR}/cmake/have_casts.cpp
                              CPPUNIT_HAVE_CPP_CAST)
check_cxx_sourcefile_compiles(${PROJECT_SOURCE_DIR}/cmake/string_compare_signature.cpp
                              CPPUNIT_FUNC_STRING_COMPARE_SIZE_FIRST)
check_cxx_sourcefile_compiles(${PROJECT_SOURCE_DIR}/cmake/have_default_template_args.cpp
                              CPPUNIT_HAVE_DEFAULT_TEMPLATE_ARGS)

if(NOT CPPUNIT_HAVE_DEFAULT_TEMPLATE_ARGS)
    set(CPPUNIT_STD_NEED_ALLOCATOR 1 CACHE INTERNAL "Default template parameters not supported")
endif()

if(NOT CPPUNIT_FUNC_STRING_COMPARE_SIZE_FIRST)
    set(CPPUNIT_FUNC_STRING_COMPARE_STRING_FIRST 1
        CACHE INTERNAL "define if library uses std::string::compare(string,pos,n)")
endif()

if(CPPUNIT_HAVE_TYPEINFO)
    check_cxx_sourcefile_compiles(${PROJECT_SOURCE_DIR}/cmake/have_rtti.cpp
                                  CPPUNIT_HAVE_RTTI)
endif()

if(_unsupported_compiler)
    message(FATAL_ERROR "Your compiler does not support all features required to build cppunit!")
endif()
