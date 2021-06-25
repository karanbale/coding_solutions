cmake_minimum_required(VERSION 3.14)

set(PROJECT_DESCRIPTION "C Python Algorithms")

message("Generating header file: ${CMAKE_BINARY_DIR}/config.h")
set(PROJECT_VERSION_MAJOR "2")
set(PROJECT_VERSION_MINOR "1")
configure_file(config.h.in config.h)

project(c_python_algorithm
        LANGUAGES C
        VERSION 0.1.0
)

# set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/modules")
message(STATUS "lib${LIBRARY_NAME} ${CMAKE_PROJECT_VERSION}")

option(BUILD_SHARED_LIBS "Build the shared library" OFF)

if (CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    set(CMAKE_C_STANDARD 99)
    set(CMAKE_C_EXTENSIONS OFF)
    set_property(GLOBAL PROPERTY USE_FOLDERS ON)
    include(CTest)

    find_package(Doxygen)
    if (Doxygen_FOUND)
        add_subdirectory(docs)
    else ()
        message(STATUS "Doxygen not found, not building docs")
    endif ()

    find_program(CCACHE_PROGRAM ccache)
    if(CCACHE_PROGRAM)
        set(CMAKE_CXX_COMPILE_FEATURES "${CCACHE_PROGRAM")
    else ()
        message(STATUS "ccahe not found, not using it.")
    endif ()

    add_subdirectory(codesignal)
    add_subdirectory(C)
endif ()

# enable_testing()

# if ((CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME OR c_python_algorithm_lib_BUILD_TESTING) AND BUILD_TESTING)
#     add_subdirectory(tests)
# endif ()

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

# set(CPACK_PROJECT_NAME ${PROJECT_NAME})
# set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
# include(CPack)
