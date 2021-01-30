cmake_minimum_required(VERSION 3.0.0)
project(C_PYTHON_ALGORITHMS VERSION 0.1.0)

include(CTest)
enable_testing()

add_library(C_PYTHON_ALGORITHMS C_PYTHON_ALGORITHMS.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
