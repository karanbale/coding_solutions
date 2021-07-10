cmake_minimum_required(VERSION 3.14)

set(PROJECT_DESCRIPTION "C Python Algorithms")

message("Setting CMAKE Compiler path to: ${CMAKE_C_COMPILER}\n")
# set(CMAKE_C_COMPILER "/usr/bin/clang")

# Defines the project name
project(c_python_algorithm_lib
        VERSION 0.1.0
        LANGUAGES C
        DESCRIPTION "Collection of coding challenges"
        )

set(LIBRARY_NAME c_python_algorithm)

message(STATUS "Lib name: ${LIBRARY_NAME}, Lib version: ${CMAKE_PROJECT_VERSION}")

option(BUILD_SHARED_LIBS "Build the shared library" OFF)

include(${PROJECT_SOURCE_DIR}/cmake/macros.cmake)

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
        message(STATUS "ccache not found, not using it.")
    endif ()

    message("Adding subdirectory C")
    add_subdirectory(C)
endif ()

configure_file(
        "${PROJECT_SOURCE_DIR}/cmake/version.h.in"
        "${PROJECT_SOURCE_DIR}/C/version.h"
        )

enable_testing()

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

write_basic_package_version_file(
    CPythonTargetsVersion.cmake
        VERSION ${PACKAGE_VERSION}
        COMPATIBILITY AnyNewerVersion
        )

install(TARGETS ${LIBRARY_NAME}
        EXPORT ${LIBRARY_NAME}Targets
        LIBRARY DESTINATION  ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION  ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION  ${CMAKE_INSTALL_BINDIR}
        )

install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(EXPORT ${LIBRARY_NAME}Targets
        FILE CPythonTargets.cmake
        NAMESPACE ${LIBRARY_NAME}::
        DESTINATION lib/cmake/${LIBRARY_NAME}
        )

install(FILES "${CMAKE_CURRENT_LIST_DIR}/cmake/CPythonTargets.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/CPythonTargetsVersion.cmake"
        DESTINATION lib/cmake/${LIBRARY_NAME}
        )
